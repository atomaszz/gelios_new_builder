//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsXml.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2002 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "uGlsXml.h"


bool TGlsXmlBase::condenseWhiteSpace = true;

void TGlsXmlBase::PutString( const TGLSXML_STRING& str, TGLSXML_OSTREAM* stream )
{
	TGLSXML_STRING buffer;
	PutString( str, &buffer );
	(*stream) << buffer;
}

void TGlsXmlBase::PutString( const TGLSXML_STRING& str, TGLSXML_STRING* outString )
{
	int i=0;

	while( i<(int)str.length() )
	{
		unsigned char c = (unsigned char) str[i];

		if (    c == '&' 
		     && i < ( (int)str.length() - 2 )
			 && str[i+1] == '#'
			 && str[i+2] == 'x' )
		{
			// Hexadecimal character reference.
			// Pass through unchanged.
			// &#xA9;	-- copyright symbol, for example.
			//
			// The -1 is a bug fix from Rob Laveaux. It keeps
			// an overflow from happening if there is no ';'.
			// There are actually 2 ways to exit this loop -
			// while fails (error case) and break (semicolon found).
			// However, there is no mechanism (currently) for
			// this function to return an error.
			while ( i<(int)str.length()-1 )
			{
				outString->append( str.c_str() + i, 1 );
				++i;
				if ( str[i] == ';' )
					break;
			}
		}
		else if ( c == '&' )
		{
			outString->append( entity[0].str, entity[0].strLength );
			++i;
		}
		else if ( c == '<' )
		{
			outString->append( entity[1].str, entity[1].strLength );
			++i;
		}
		else if ( c == '>' )
		{
			outString->append( entity[2].str, entity[2].strLength );
			++i;
		}
		else if ( c == '\"' )
		{
			outString->append( entity[3].str, entity[3].strLength );
			++i;
		}
		else if ( c == '\'' )
		{
			outString->append( entity[4].str, entity[4].strLength );
			++i;
		}
		else if ( c < 32 )
		{
			// Easy pass at non-alpha/numeric/symbol
			// Below 32 is symbolic.
			char buf[ 32 ];
			sprintf( buf, "&#x%02X;", (unsigned) ( c & 0xff ) );
			//*ME:	warning C4267: convert 'size_t' to 'int'
			//*ME:	Int-Cast to make compiler happy ...
			outString->append( buf, (int)strlen( buf ) );
			++i;
		}
		else
		{
			//char realc = (char) c;
			//outString->append( &realc, 1 );
			*outString += (char) c;	// somewhat more efficient function call.
			++i;
		}
	}
}


// <-- Strange class for a bug fix. Search for STL_STRING_BUG
TGlsXmlBase::StringToBuffer::StringToBuffer( const TGLSXML_STRING& str )
{
	buffer = new char[ str.length()+1 ];
	if ( buffer )
	{
		strcpy( buffer, str.c_str() );
	}
}


TGlsXmlBase::StringToBuffer::~StringToBuffer()
{
	delete [] buffer;
}
// End strange bug fix. -->


TGlsXmlNode::TGlsXmlNode( NodeType _type ) : TGlsXmlBase()
{
	parent = 0;
	type = _type;
	firstChild = 0;
	lastChild = 0;
	prev = 0;
	next = 0;
}


TGlsXmlNode::~TGlsXmlNode()
{
	TGlsXmlNode* node = firstChild;
	TGlsXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}	
}


void TGlsXmlNode::CopyTo( TGlsXmlNode* target ) const
{
	target->SetValue (value.c_str() );
	target->userData = userData; 
}


void TGlsXmlNode::Clear()
{
	TGlsXmlNode* node = firstChild;
	TGlsXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}	

	firstChild = 0;
	lastChild = 0;
}


TGlsXmlNode* TGlsXmlNode::LinkEndChild( TGlsXmlNode* node )
{
	node->parent = this;

	node->prev = lastChild;
	node->next = 0;

	if ( lastChild )
		lastChild->next = node;
	else
		firstChild = node;			// it was an empty list.

	lastChild = node;
	return node;
}


TGlsXmlNode* TGlsXmlNode::InsertEndChild( const TGlsXmlNode& addThis )
{
	TGlsXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;

	return LinkEndChild( node );
}


TGlsXmlNode* TGlsXmlNode::InsertBeforeChild( TGlsXmlNode* beforeThis, const TGlsXmlNode& addThis )
{	
	if ( !beforeThis || beforeThis->parent != this )
		return 0;

	TGlsXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->next = beforeThis;
	node->prev = beforeThis->prev;
	if ( beforeThis->prev )
	{
		beforeThis->prev->next = node;
	}
	else
	{
		assert( firstChild == beforeThis );
		firstChild = node;
	}
	beforeThis->prev = node;
	return node;
}


TGlsXmlNode* TGlsXmlNode::InsertAfterChild( TGlsXmlNode* afterThis, const TGlsXmlNode& addThis )
{
	if ( !afterThis || afterThis->parent != this )
		return 0;

	TGlsXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->prev = afterThis;
	node->next = afterThis->next;
	if ( afterThis->next )
	{
		afterThis->next->prev = node;
	}
	else
	{
		assert( lastChild == afterThis );
		lastChild = node;
	}
	afterThis->next = node;
	return node;
}


TGlsXmlNode* TGlsXmlNode::ReplaceChild( TGlsXmlNode* replaceThis, const TGlsXmlNode& withThis )
{
	if ( replaceThis->parent != this )
		return 0;

	TGlsXmlNode* node = withThis.Clone();
	if ( !node )
		return 0;

	node->next = replaceThis->next;
	node->prev = replaceThis->prev;

	if ( replaceThis->next )
		replaceThis->next->prev = node;
	else
		lastChild = node;

	if ( replaceThis->prev )
		replaceThis->prev->next = node;
	else
		firstChild = node;

	delete replaceThis;
	node->parent = this;
	return node;
}


bool TGlsXmlNode::RemoveChild( TGlsXmlNode* removeThis )
{
	if ( removeThis->parent != this )
	{	
		assert( 0 );
		return false;
	}

	if ( removeThis->next )
		removeThis->next->prev = removeThis->prev;
	else
		lastChild = removeThis->prev;

	if ( removeThis->prev )
		removeThis->prev->next = removeThis->next;
	else
		firstChild = removeThis->next;

	delete removeThis;
	return true;
}

const TGlsXmlNode* TGlsXmlNode::FirstChild( const char * _value ) const
{
	const TGlsXmlNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}


TGlsXmlNode* TGlsXmlNode::FirstChild( const char * _value )
{
	TGlsXmlNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}


const TGlsXmlNode* TGlsXmlNode::LastChild( const char * _value ) const
{
	const TGlsXmlNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TGlsXmlNode* TGlsXmlNode::LastChild( const char * _value )
{
	TGlsXmlNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

const TGlsXmlNode* TGlsXmlNode::IterateChildren( const TGlsXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}

TGlsXmlNode* TGlsXmlNode::IterateChildren( TGlsXmlNode* previous )
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}

const TGlsXmlNode* TGlsXmlNode::IterateChildren( const char * val, const TGlsXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}

TGlsXmlNode* TGlsXmlNode::IterateChildren( const char * val, TGlsXmlNode* previous )
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}

const TGlsXmlNode* TGlsXmlNode::NextSibling( const char * _value ) const
{
	const TGlsXmlNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TGlsXmlNode* TGlsXmlNode::NextSibling( const char * _value )
{
	TGlsXmlNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

const TGlsXmlNode* TGlsXmlNode::PreviousSibling( const char * _value ) const
{
	const TGlsXmlNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

TGlsXmlNode* TGlsXmlNode::PreviousSibling( const char * _value )
{
	TGlsXmlNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( node->SValue() == _value )
			return node;
	}
	return 0;
}

void TGlsXmlElement::RemoveAttribute( const char * name )
{
	TGlsXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		attributeSet.Remove( node );
		delete node;
	}
}

const TGlsXmlElement* TGlsXmlNode::FirstChildElement() const
{
	const TGlsXmlNode* node;

	for (	node = FirstChild();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TGlsXmlElement* TGlsXmlNode::FirstChildElement()
{
	TGlsXmlNode* node;

	for (	node = FirstChild();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TGlsXmlElement* TGlsXmlNode::FirstChildElement( const char * _value ) const
{
	const TGlsXmlNode* node;

	for (	node = FirstChild( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TGlsXmlElement* TGlsXmlNode::FirstChildElement( const char * _value )
{
	TGlsXmlNode* node;

	for (	node = FirstChild( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TGlsXmlElement* TGlsXmlNode::NextSiblingElement() const
{
	const TGlsXmlNode* node;

	for (	node = NextSibling();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TGlsXmlElement* TGlsXmlNode::NextSiblingElement()
{
	TGlsXmlNode* node;

	for (	node = NextSibling();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

const TGlsXmlElement* TGlsXmlNode::NextSiblingElement( const char * _value ) const
{
	const TGlsXmlNode* node;

	for (	node = NextSibling( _value );
	node;
	node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TGlsXmlElement* TGlsXmlNode::NextSiblingElement( const char * _value )
{
	TGlsXmlNode* node;

	for (	node = NextSibling( _value );
	node;
	node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const TGlsXmlDocument* TGlsXmlNode::GetDocument() const
{
	const TGlsXmlNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}

TGlsXmlDocument* TGlsXmlNode::GetDocument()
{
	TGlsXmlNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}

TGlsXmlElement::TGlsXmlElement (const char * _value)
	: TGlsXmlNode( TGlsXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}




TGlsXmlElement::TGlsXmlElement( const TGlsXmlElement& copy)
	: TGlsXmlNode( TGlsXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	copy.CopyTo( this );	
}


void TGlsXmlElement::operator=( const TGlsXmlElement& base )
{
	ClearThis();
	base.CopyTo( this );
}


TGlsXmlElement::~TGlsXmlElement()
{
	ClearThis();
}


void TGlsXmlElement::ClearThis()
{
	Clear();
	while( attributeSet.First() )
	{
		TGlsXmlAttribute* node = attributeSet.First();
		attributeSet.Remove( node );
		delete node;
	}
}


const char* TGlsXmlElement::Attribute( const char * name ) const
{
	const TGlsXmlAttribute* node = attributeSet.Find( name );

	if ( node )
		return node->Value();

	return 0;
}


const char* TGlsXmlElement::Attribute( const char * name, int* i ) const
{
	const char * s = Attribute( name );
	if ( i )
	{
		if ( s )
			*i = atoi( s );
		else
			*i = 0;
	}
	return s;
}


const char * TGlsXmlElement::Attribute( const char * name, double* d ) const
{
	const char * s = Attribute( name );
	if ( d )
	{
		if ( s )
			*d = atof( s );
		else
			*d = 0;
	}
	return s;
}


int TGlsXmlElement::QueryIntAttribute( const char* name, int* ival ) const
{
	const TGlsXmlAttribute* node = attributeSet.Find( name );
	if ( !node )
		return TGLSXML_NO_ATTRIBUTE;

	return node->QueryIntValue( ival );
}


int TGlsXmlElement::QueryDoubleAttribute( const char* name, double* dval ) const
{
	const TGlsXmlAttribute* node = attributeSet.Find( name );
	if ( !node )
		return TGLSXML_NO_ATTRIBUTE;

	return node->QueryDoubleValue( dval );
}


void TGlsXmlElement::SetAttribute( const char * name, int val )
{	
	char buf[64];
	sprintf( buf, "%d", val );
	SetAttribute( name, buf );
}


void TGlsXmlElement::SetDoubleAttribute( const char * name, double val )
{	
	char buf[256];
	sprintf( buf, "%f", val );
	SetAttribute( name, buf );
}


void TGlsXmlElement::SetAttribute( const char * name, const char * _value )
{
	TGlsXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		node->SetValue( _value );
		return;
	}

	TGlsXmlAttribute* attrib = new TGlsXmlAttribute( name, _value );
	if ( attrib )
	{
		attributeSet.Add( attrib );
	}
	else
	{
		TGlsXmlDocument* document = GetDocument();
		if ( document ) document->SetError( TGLSXML_ERROR_OUT_OF_MEMORY, 0, 0, TGLSXML_ENCODING_UNKNOWN );
	}
}

void TGlsXmlElement::Print( FILE* cfile, int depth ) const
{
	int i;
	for ( i=0; i<depth; i++ )
	{
		fprintf( cfile, "    " );
	}

	fprintf( cfile, "<%s", value.c_str() );

	const TGlsXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		fprintf( cfile, " " );
		attrib->Print( cfile, depth );
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	TGlsXmlNode* node;
	if ( !firstChild )
	{
		fprintf( cfile, " />" );
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		fprintf( cfile, ">" );
		firstChild->Print( cfile, depth + 1 );
		fprintf( cfile, "</%s>", value.c_str() );
	}
	else
	{
		fprintf( cfile, ">" );

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				fprintf( cfile, "\n" );
			}
			node->Print( cfile, depth+1 );
		}
		fprintf( cfile, "\n" );
		for( i=0; i<depth; ++i )
		fprintf( cfile, "    " );
		fprintf( cfile, "</%s>", value.c_str() );
	}
}

void TGlsXmlElement::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value;

	const TGlsXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{	
		(*stream) << " ";
		attrib->StreamOut( stream );
	}

	// If this node has children, give it a closing tag. Else
	// make it an empty tag.
	TGlsXmlNode* node;
	if ( firstChild )
	{ 		
		(*stream) << ">";

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			node->StreamOut( stream );
		}
		(*stream) << "</" << value << ">";
	}
	else
	{
		(*stream) << " />";
	}
}


void TGlsXmlElement::CopyTo( TGlsXmlElement* target ) const
{
	// superclass:
	TGlsXmlNode::CopyTo( target );

	// Element class: 
	// Clone the attributes, then clone the children.
	const TGlsXmlAttribute* attribute = 0;
	for(	attribute = attributeSet.First();
	attribute;
	attribute = attribute->Next() )
	{
		target->SetAttribute( attribute->Name(), attribute->Value() );
	}

	TGlsXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}
}


TGlsXmlNode* TGlsXmlElement::Clone() const
{
	TGlsXmlElement* clone = new TGlsXmlElement( Value() );
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TGlsXmlDocument::TGlsXmlDocument() : TGlsXmlNode( TGlsXmlNode::DOCUMENT )
{
	tabsize = 4;
	ClearError();
}

TGlsXmlDocument::TGlsXmlDocument( const char * documentName ) : TGlsXmlNode( TGlsXmlNode::DOCUMENT )
{
	tabsize = 4;
	value = documentName;
	ClearError();
}



TGlsXmlDocument::TGlsXmlDocument( const TGlsXmlDocument& copy ) : TGlsXmlNode( TGlsXmlNode::DOCUMENT )
{
	copy.CopyTo( this );
}


void TGlsXmlDocument::operator=( const TGlsXmlDocument& copy )
{
	Clear();
	copy.CopyTo( this );
}


bool TGlsXmlDocument::LoadFile( TGlsXmlEncoding encoding )
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && LoadFile( buf.buffer, encoding ) )
		return true;

	return false;
}


bool TGlsXmlDocument::SaveFile() const
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && SaveFile( buf.buffer ) )
		return true;

	return false;
}

bool TGlsXmlDocument::LoadFile( const char* filename, TGlsXmlEncoding encoding )
{
	// Delete the existing data:
	Clear();
	location.Clear();

	// There was a really terrifying little bug here. The code:
	//		value = filename
	// in the STL case, cause the assignment method of the std::string to
	// be called. What is strange, is that the std::string had the same
	// address as it's c_str() method, and so bad things happen. Looks
	// like a bug in the Microsoft STL implementation.
	// See STL_STRING_BUG above.
	// Fixed with the StringToBuffer class.
	value = filename;

	FILE* file = fopen( value.c_str (), "r" );

	if ( file )
	{
		// Get the file size, so we can pre-allocate the string. HUGE speed impact.
		long length = 0;
		fseek( file, 0, SEEK_END );
		length = ftell( file );
		fseek( file, 0, SEEK_SET );

		// Strange case, but good to handle up front.
		if ( length == 0 )
		{
			fclose( file );
			return false;
		}

		// If we have a file, assume it is all one big XML file, and read it in.
		// The document parser may decide the document ends sooner than the entire file, however.
		TGLSXML_STRING data;
		data.reserve( length );

		const int BUF_SIZE = 2048;
		char buf[BUF_SIZE];

		while( fgets( buf, BUF_SIZE, file ) )
		{
			data += buf;
		}
		fclose( file );

		Parse( data.c_str(), 0, encoding );

		if (  Error() )
            return false;
        else
			return true;
	}
	SetError( TGLSXML_ERROR_OPENING_FILE, 0, 0, TGLSXML_ENCODING_UNKNOWN );
	return false;
}

bool TGlsXmlDocument::SaveFile( const char * filename ) const
{
	// The old c stuff lives on...
	FILE* fp = fopen( filename, "w" );
	if ( fp )
	{
		Print( fp, 0 );
		fclose( fp );
		return true;
	}
	return false;
}


void TGlsXmlDocument::CopyTo( TGlsXmlDocument* target ) const
{
	TGlsXmlNode::CopyTo( target );

	target->error = error;
	target->errorDesc = errorDesc.c_str ();

	TGlsXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}	
}


TGlsXmlNode* TGlsXmlDocument::Clone() const
{
	TGlsXmlDocument* clone = new TGlsXmlDocument();
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TGlsXmlDocument::Print( FILE* cfile, int depth ) const
{
	const TGlsXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->Print( cfile, depth );
		fprintf( cfile, "\n" );
	}
}

void TGlsXmlDocument::StreamOut( TGLSXML_OSTREAM * out ) const
{
	const TGlsXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->StreamOut( out );

		// Special rule for streams: stop after the root element.
		// The stream in code will only read one element, so don't
		// write more than one.
		if ( node->ToElement() )
			break;
	}
}


const TGlsXmlAttribute* TGlsXmlAttribute::Next() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}

TGlsXmlAttribute* TGlsXmlAttribute::Next()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}

const TGlsXmlAttribute* TGlsXmlAttribute::Previous() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}

TGlsXmlAttribute* TGlsXmlAttribute::Previous()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}

void TGlsXmlAttribute::Print( FILE* cfile, int /*depth*/ ) const
{
	TGLSXML_STRING n, v;

	PutString( name, &n );
	PutString( value, &v );

	if (value.find ('\"') == TGLSXML_STRING::npos)
		fprintf (cfile, "%s=\"%s\"", n.c_str(), v.c_str() );
	else
		fprintf (cfile, "%s='%s'", n.c_str(), v.c_str() );
}


void TGlsXmlAttribute::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	if (value.find( '\"' ) != TGLSXML_STRING::npos)
	{
		PutString( name, stream );
		(*stream) << "=" << "'";
		PutString( value, stream );
		(*stream) << "'";
	}
	else
	{
		PutString( name, stream );
		(*stream) << "=" << "\"";
		PutString( value, stream );
		(*stream) << "\"";
	}
}

int TGlsXmlAttribute::QueryIntValue( int* ival ) const
{
	if ( sscanf( value.c_str(), "%d", ival ) == 1 )
		return TGLSXML_SUCCESS;
	return TGLSXML_WRONG_TYPE;
}

int TGlsXmlAttribute::QueryDoubleValue( double* dval ) const
{
	if ( sscanf( value.c_str(), "%lf", dval ) == 1 )
		return TGLSXML_SUCCESS;
	return TGLSXML_WRONG_TYPE;
}

void TGlsXmlAttribute::SetIntValue( int _value )
{
	char buf [64];
	sprintf (buf, "%d", _value);
	SetValue (buf);
}

void TGlsXmlAttribute::SetDoubleValue( double _value )
{
	char buf [256];
	sprintf (buf, "%lf", _value);
	SetValue (buf);
}

const int TGlsXmlAttribute::IntValue() const
{
	return atoi (value.c_str ());
}

const double  TGlsXmlAttribute::DoubleValue() const
{
	return atof (value.c_str ());
}


TGlsXmlComment::TGlsXmlComment( const TGlsXmlComment& copy ) : TGlsXmlNode( TGlsXmlNode::COMMENT )
{
	copy.CopyTo( this );
}


void TGlsXmlComment::operator=( const TGlsXmlComment& base )
{
	Clear();
	base.CopyTo( this );
}


void TGlsXmlComment::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
	{
		fputs( "    ", cfile );
	}
	fprintf( cfile, "<!--%s-->", value.c_str() );
}

void TGlsXmlComment::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	(*stream) << "<!--";
	//PutString( value, stream );
	(*stream) << value;
	(*stream) << "-->";
}


void TGlsXmlComment::CopyTo( TGlsXmlComment* target ) const
{
	TGlsXmlNode::CopyTo( target );
}


TGlsXmlNode* TGlsXmlComment::Clone() const
{
	TGlsXmlComment* clone = new TGlsXmlComment();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TGlsXmlText::Print( FILE* cfile, int /*depth*/ ) const
{
	TGLSXML_STRING buffer;
	PutString( value, &buffer );
	fprintf( cfile, "%s", buffer.c_str() );
}


void TGlsXmlText::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	PutString( value, stream );
}


void TGlsXmlText::CopyTo( TGlsXmlText* target ) const
{
	TGlsXmlNode::CopyTo( target );
}


TGlsXmlNode* TGlsXmlText::Clone() const
{	
	TGlsXmlText* clone = 0;
	clone = new TGlsXmlText( "" );

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TGlsXmlDeclaration::TGlsXmlDeclaration( const char * _version,
									const char * _encoding,
									const char * _standalone )
	: TGlsXmlNode( TGlsXmlNode::DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}



TGlsXmlDeclaration::TGlsXmlDeclaration( const TGlsXmlDeclaration& copy )
	: TGlsXmlNode( TGlsXmlNode::DECLARATION )
{
	copy.CopyTo( this );	
}


void TGlsXmlDeclaration::operator=( const TGlsXmlDeclaration& copy )
{
	Clear();
	copy.CopyTo( this );
}


void TGlsXmlDeclaration::Print( FILE* cfile, int /*depth*/ ) const
{
	fprintf (cfile, "<?xml ");

	if ( !version.empty() )
		fprintf (cfile, "version=\"%s\" ", version.c_str ());
	if ( !encoding.empty() )
		fprintf (cfile, "encoding=\"%s\" ", encoding.c_str ());
	if ( !standalone.empty() )
		fprintf (cfile, "standalone=\"%s\" ", standalone.c_str ());
	fprintf (cfile, "?>");
}

void TGlsXmlDeclaration::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	(*stream) << "<?xml ";

	if ( !version.empty() )
	{
		(*stream) << "version=\"";
		PutString( version, stream );
		(*stream) << "\" ";
	}
	if ( !encoding.empty() )
	{
		(*stream) << "encoding=\"";
		PutString( encoding, stream );
		(*stream ) << "\" ";
	}
	if ( !standalone.empty() )
	{
		(*stream) << "standalone=\"";
		PutString( standalone, stream );
		(*stream) << "\" ";
	}
	(*stream) << "?>";
}


void TGlsXmlDeclaration::CopyTo( TGlsXmlDeclaration* target ) const
{
	TGlsXmlNode::CopyTo( target );

	target->version = version;
	target->encoding = encoding;
	target->standalone = standalone;
}


TGlsXmlNode* TGlsXmlDeclaration::Clone() const
{	
	TGlsXmlDeclaration* clone = new TGlsXmlDeclaration();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void TGlsXmlUnknown::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
		fprintf( cfile, "    " );
	fprintf( cfile, "<%s>", value.c_str() );
}


void TGlsXmlUnknown::StreamOut( TGLSXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value << ">";		// Don't use entities here! It is unknown.
}


void TGlsXmlUnknown::CopyTo( TGlsXmlUnknown* target ) const
{
	TGlsXmlNode::CopyTo( target );
}


TGlsXmlNode* TGlsXmlUnknown::Clone() const
{
	TGlsXmlUnknown* clone = new TGlsXmlUnknown();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


TGlsXmlAttributeSet::TGlsXmlAttributeSet()
{
	sentinel.next = &sentinel;
	sentinel.prev = &sentinel;
}


TGlsXmlAttributeSet::~TGlsXmlAttributeSet()
{
	assert( sentinel.next == &sentinel );
	assert( sentinel.prev == &sentinel );
}


void TGlsXmlAttributeSet::Add( TGlsXmlAttribute* addMe )
{
	assert( !Find( addMe->Name() ) );	// Shouldn't be multiply adding to the set.

	addMe->next = &sentinel;
	addMe->prev = sentinel.prev;

	sentinel.prev->next = addMe;
	sentinel.prev      = addMe;
}

void TGlsXmlAttributeSet::Remove( TGlsXmlAttribute* removeMe )
{
	TGlsXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node == removeMe )
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = 0;
			node->prev = 0;
			return;
		}
	}
	assert( 0 );		// we tried to remove a non-linked attribute.
}

const TGlsXmlAttribute* TGlsXmlAttributeSet::Find( const char * name ) const
{
	const TGlsXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}

TGlsXmlAttribute*  TGlsXmlAttributeSet::Find( const char * name )
{
	TGlsXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}



TGLSXML_OSTREAM & operator<< (TGLSXML_OSTREAM & out, const TGlsXmlNode & base)
{
	base.StreamOut (& out);
	return out;
}



TGlsXmlHandle TGlsXmlHandle::FirstChild() const
{
	if ( node )
	{
		TGlsXmlNode* child = node->FirstChild();
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::FirstChild( const char * value ) const
{
	if ( node )
	{
		TGlsXmlNode* child = node->FirstChild( value );
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::FirstChildElement() const
{
	if ( node )
	{
		TGlsXmlElement* child = node->FirstChildElement();
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::FirstChildElement( const char * value ) const
{
	if ( node )
	{
		TGlsXmlElement* child = node->FirstChildElement( value );
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::Child( int count ) const
{
	if ( node )
	{
		int i;
		TGlsXmlNode* child = node->FirstChild();
		for (	i=0;
				child && i<count;
				child = child->NextSibling(), ++i )
		{
			// nothing
		}
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::Child( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		TGlsXmlNode* child = node->FirstChild( value );
		for (	i=0;
				child && i<count;
				child = child->NextSibling( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::ChildElement( int count ) const
{
	if ( node )
	{
		int i;
		TGlsXmlElement* child = node->FirstChildElement();
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement(), ++i )
		{
			// nothing
		}
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}


TGlsXmlHandle TGlsXmlHandle::ChildElement( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		TGlsXmlElement* child = node->FirstChildElement( value );
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return TGlsXmlHandle( child );
	}
	return TGlsXmlHandle( 0 );
}

