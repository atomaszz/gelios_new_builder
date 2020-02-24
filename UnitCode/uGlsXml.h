//---------------------------------------------------------------------------

#ifndef uGlsXmlH
#define uGlsXmlH
//---------------------------------------------------------------------------
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


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "uGlsXmlString.h"
#define TGLSXML_STRING	TGlsXmlString
#define TGLSXML_OSTREAM	TGlsXmlOutStream


class TGlsXmlDocument;
class TGlsXmlElement;
class TGlsXmlComment;
class TGlsXmlUnknown;
class TGlsXmlAttribute;
class TGlsXmlText;
class TGlsXmlDeclaration;
class TGlsXmlParsingData;

//stas const int TIXML_MAJOR_VERSION = 2;
//stas const int TIXML_MINOR_VERSION = 3;
//stas const int TIXML_PATCH_VERSION = 4;

/*	Internal structure for tracking location of items
	in the XML file.
*/
struct TGlsXmlCursor
{
	TGlsXmlCursor()		{ Clear(); }
	void Clear()		{ row = col = -1; }

	int row;	// 0 based.
	int col;	// 0 based.
};


// Only used by Attribute::Query functions
enum
{
	TGLSXML_SUCCESS,
	TGLSXML_NO_ATTRIBUTE,
	TGLSXML_WRONG_TYPE
};


// Used by the parsing routines.
enum TGlsXmlEncoding
{
	TGLSXML_ENCODING_UNKNOWN,
	TGLSXML_ENCODING_UTF8,
	TGLSXML_ENCODING_LEGACY
};

const TGlsXmlEncoding TGLSXML_DEFAULT_ENCODING = TGLSXML_ENCODING_UNKNOWN;

/** TiXmlBase is a base class for every class in TinyXml.
	It does little except to establish that TinyXml classes
	can be printed and provide some utility functions.

	In XML, the document and elements can contain
	other elements and other types of nodes.

	@verbatim
	A Document can contain:	Element	(container or leaf)
							Comment (leaf)
							Unknown (leaf)
							Declaration( leaf )

	An Element can contain:	Element (container or leaf)
							Text	(leaf)
							Attributes (not on tree)
							Comment (leaf)
							Unknown (leaf)

	A Decleration contains: Attributes (not on tree)
	@endverbatim
*/
class TGlsXmlBase
{
	friend class TGlsXmlNode;
	friend class TGlsXmlElement;
	friend class TGlsXmlDocument;

public:
	TGlsXmlBase(): userData(0) {}
	virtual ~TGlsXmlBase()					{}

	/**	All TinyXml classes can print themselves to a filestream.
		This is a formatted print, and will insert tabs and newlines.
		
		(For an unformatted stream, use the << operator.)
	*/
	virtual void Print( FILE* cfile, int depth ) const = 0;

	/**	The world does not agree on whether white space should be kept or
		not. In order to make everyone happy, these global, static functions
		are provided to set whether or not TinyXml will condense all white space
		into a single space or not. The default is to condense. Note changing this
		values is not thread safe.
	*/
	static void SetCondenseWhiteSpace( bool condense )		{ condenseWhiteSpace = condense; }

	/// Return the current white space setting.
	static bool IsWhiteSpaceCondensed()						{ return condenseWhiteSpace; }

	/** Return the position, in the original source file, of this node or attribute.
		The row and column are 1-based. (That is the first row and first column is
		1,1). If the returns values are 0 or less, then the parser does not have
		a row and column value.

		Generally, the row and column value will be set when the TiXmlDocument::Load(),
		TiXmlDocument::LoadFile(), or any TiXmlNode::Parse() is called. It will NOT be set
		when the DOM was created from operator>>.

		The values reflect the initial load. Once the DOM is modified programmatically
		(by adding or changing nodes and attributes) the new values will NOT update to
		reflect changes in the document.

		There is a minor performance cost to computing the row and column. Computation
		can be disabled if TiXmlDocument::SetTabSize() is called with 0 as the value.

		@sa TiXmlDocument::SetTabSize()
	*/
	int Row() const			{ return location.row + 1; }
	int Column() const		{ return location.col + 1; }	///< See Row()

	void  SetUserData( void* user )			{ userData = user; }
	void* GetUserData()						{ return userData; }

	// Table that returs, for a given lead byte, the total number of bytes
	// in the UTF-8 sequence.
	static const int utf8ByteTable[256];

	virtual const char* Parse(	const char* p,
								TGlsXmlParsingData* data,
								TGlsXmlEncoding encoding /*= TIXML_ENCODING_UNKNOWN */ ) = 0;

	enum
	{
		TGLSXML_NO_ERROR = 0,
		TGLSXML_ERROR,
		TGLSXML_ERROR_OPENING_FILE,
		TGLSXML_ERROR_OUT_OF_MEMORY,
		TGLSXML_ERROR_PARSING_ELEMENT,
		TGLSXML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
		TGLSXML_ERROR_READING_ELEMENT_VALUE,
		TGLSXML_ERROR_READING_ATTRIBUTES,
		TGLSXML_ERROR_PARSING_EMPTY,
		TGLSXML_ERROR_READING_END_TAG,
		TGLSXML_ERROR_PARSING_UNKNOWN,
		TGLSXML_ERROR_PARSING_COMMENT,
		TGLSXML_ERROR_PARSING_DECLARATION,
		TGLSXML_ERROR_DOCUMENT_EMPTY,
		TGLSXML_ERROR_EMBEDDED_NULL,

		TGLSXML_ERROR_STRING_COUNT
	};

protected:

	// See STL_STRING_BUG
	// Utility class to overcome a bug.
	class StringToBuffer
	{
	  public:
		StringToBuffer(const TGLSXML_STRING& str );
		~StringToBuffer();
		char* buffer;
	};

	static const char*	SkipWhiteSpace( const char*, TGlsXmlEncoding encoding );
	inline static bool	IsWhiteSpace( char c )		
	{ 
		return ( isspace( (unsigned char) c ) || c == '\n' || c == '\r' ); 
	}

	virtual void StreamOut (TGLSXML_OSTREAM *) const = 0;


	/*	Reads an XML name into the string provided. Returns
		a pointer just past the last character of the name,
		or 0 if the function has an error.
	*/
	static const char* ReadName( const char* p, TGLSXML_STRING* name, TGlsXmlEncoding encoding );

	/*	Reads text. Returns a pointer past the given end tag.
		Wickedly complex options, but it keeps the (sensitive) code in one place.
	*/
	static const char* ReadText(	const char* in,				// where to start
									TGLSXML_STRING* text,			// the string read
									bool ignoreWhiteSpace,		// whether to keep the white space
									const char* endTag,			// what ends this text
									bool ignoreCase,			// whether to ignore case in the end tag
									TGlsXmlEncoding encoding );	// the current encoding

	// If an entity has been found, transform it into a character.
	static const char* GetEntity( const char* in, char* value, int* length, TGlsXmlEncoding encoding );

	// Get a character, while interpreting entities.
	// The length can be from 0 to 4 bytes.
	inline static const char* GetChar( const char* p, char* _value, int* length, TGlsXmlEncoding encoding )
	{
		assert( p );
		if ( encoding == TGLSXML_ENCODING_UTF8 )
		{
			*length = utf8ByteTable[ *((unsigned char*)p) ];
			assert( *length >= 0 && *length < 5 );
		}
		else
		{
			*length = 1;
		}

		if ( *length == 1 )
		{
			if ( *p == '&' )
				return GetEntity( p, _value, length, encoding );
			*_value = *p;
			return p+1;
		}
		else if ( *length )
		{
			strncpy( _value, p, *length );
			return p + (*length);
		}
		else
		{
			// Not valid text.
			return 0;
		}
	}

	// Puts a string to a stream, expanding entities as it goes.
	// Note this should not contian the '<', '>', etc, or they will be transformed into entities!
	static void PutString( const TGLSXML_STRING& str, TGLSXML_OSTREAM* out );

	static void PutString( const TGLSXML_STRING& str, TGLSXML_STRING* out );

	// Return true if the next characters in the stream are any of the endTag sequences.
	// Ignore case only works for english, and should only be relied on when comparing
	// to Engilish words: StringEqual( p, "version", true ) is fine.
	static bool StringEqual(	const char* p,
								const char* endTag,
								bool ignoreCase,
								TGlsXmlEncoding encoding );

	static const char* errorString[ TGLSXML_ERROR_STRING_COUNT ];

	TGlsXmlCursor location;

    /// Field containing a generic user pointer
	void*			userData;
	
	// None of these methods are reliable for any language except English.
	// Good for approximation, not great for accuracy.
	static int IsAlpha( unsigned char anyByte, TGlsXmlEncoding encoding );
	static int IsAlphaNum( unsigned char anyByte, TGlsXmlEncoding encoding );
	inline static int ToLower( int v, TGlsXmlEncoding encoding )
	{
		if ( encoding == TGLSXML_ENCODING_UTF8 )
		{
			if ( v < 128 ) return tolower( v );
			return v;
		}
		else
		{
			return tolower( v );
		}
	}
	static void ConvertUTF32ToUTF8( unsigned long input, char* output, int* length );

private:
	TGlsXmlBase( const TGlsXmlBase& );				// not implemented.
	void operator=( const TGlsXmlBase& base );	// not allowed.

	struct Entity
	{
		const char*     str;
		unsigned int	strLength;
		char		    chr;
	};
	enum
	{
		NUM_ENTITY = 5,
		MAX_ENTITY_LENGTH = 6

	};
	static Entity entity[ NUM_ENTITY ];
	static bool condenseWhiteSpace;
};


/** The parent class for everything in the Document Object Model.
	(Except for attributes).
	Nodes have siblings, a parent, and children. A node can be
	in a document, or stand on its own. The type of a TiXmlNode
	can be queried, and it can be cast to its more defined type.
*/
class TGlsXmlNode : public TGlsXmlBase
{
	friend class TGlsXmlDocument;
	friend class TGlsXmlElement;

public:
        // Used internally, not part of the public API.
        friend TGLSXML_OSTREAM& operator<< (TGLSXML_OSTREAM& out, const TGlsXmlNode& base);

	/** The types of XML nodes supported by TinyXml. (All the
			unsupported types are picked up by UNKNOWN.)
	*/
	enum NodeType
	{
		DOCUMENT,
		ELEMENT,
		COMMENT,
		UNKNOWN,
		TEXT,
		DECLARATION,
		TYPECOUNT
	};

	virtual ~TGlsXmlNode();

	/** The meaning of 'value' changes for the specific type of
		TiXmlNode.
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		Unknown:	the tag contents
		Text:		the text string
		@endverbatim

		The subclasses will wrap this function.
	*/
	const char* Value() const { return value.c_str (); }

	/** Changes the value of the node. Defined as:
		@verbatim
		Document:	filename of the xml file
		Element:	name of the element
		Comment:	the comment text
		Unknown:	the tag contents
		Text:		the text string
		@endverbatim
	*/
	void SetValue(const char * _value) { value = _value;}


	/// Delete all the children of this node. Does not affect 'this'.
	void Clear();

	/// One step up the DOM.
	TGlsXmlNode* Parent()							{ return parent; }
	const TGlsXmlNode* Parent() const				{ return parent; }

	const TGlsXmlNode* FirstChild()	const	{ return firstChild; }		///< The first child of this node. Will be null if there are no children.
	TGlsXmlNode* FirstChild()					{ return firstChild; }
	const TGlsXmlNode* FirstChild( const char * value ) const;			///< The first child of this node with the matching 'value'. Will be null if none found.
	TGlsXmlNode* FirstChild( const char * value );						///< The first child of this node with the matching 'value'. Will be null if none found.

	const TGlsXmlNode* LastChild() const	{ return lastChild; }		/// The last child of this node. Will be null if there are no children.
	TGlsXmlNode* LastChild()	{ return lastChild; }
	const TGlsXmlNode* LastChild( const char * value ) const;			/// The last child of this node matching 'value'. Will be null if there are no children.
	TGlsXmlNode* LastChild( const char * value );	


	/** An alternate way to walk the children of a node.
		One way to iterate over nodes is:
		@verbatim
			for( child = parent->FirstChild(); child; child = child->NextSibling() )
		@endverbatim

		IterateChildren does the same thing with the syntax:
		@verbatim
			child = 0;
			while( child = parent->IterateChildren( child ) )
		@endverbatim

		IterateChildren takes the previous child as input and finds
		the next one. If the previous child is null, it returns the
		first. IterateChildren will return null when done.
	*/
	const TGlsXmlNode* IterateChildren( const TGlsXmlNode* previous ) const;
	TGlsXmlNode* IterateChildren( TGlsXmlNode* previous );

	/// This flavor of IterateChildren searches for children with a particular 'value'
	const TGlsXmlNode* IterateChildren( const char* value, const TGlsXmlNode* previous ) const;
	TGlsXmlNode* IterateChildren( const char * value, TGlsXmlNode* previous );


	/** Add a new node related to this. Adds a child past the LastChild.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	TGlsXmlNode* InsertEndChild( const TGlsXmlNode& addThis );


	/** Add a new node related to this. Adds a child past the LastChild.

		NOTE: the node to be added is passed by pointer, and will be
		henceforth owned (and deleted) by tinyXml. This method is efficient
		and avoids an extra copy, but should be used with care as it
		uses a different memory model than the other insert functions.

		@sa InsertEndChild
	*/
	TGlsXmlNode* LinkEndChild( TGlsXmlNode* addThis );

	/** Add a new node related to this. Adds a child before the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	TGlsXmlNode* InsertBeforeChild( TGlsXmlNode* beforeThis, const TGlsXmlNode& addThis );

	/** Add a new node related to this. Adds a child after the specified child.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	TGlsXmlNode* InsertAfterChild(  TGlsXmlNode* afterThis, const TGlsXmlNode& addThis );

	/** Replace a child of this node.
		Returns a pointer to the new object or NULL if an error occured.
	*/
	TGlsXmlNode* ReplaceChild( TGlsXmlNode* replaceThis, const TGlsXmlNode& withThis );

	/// Delete a child of this node.
	bool RemoveChild( TGlsXmlNode* removeThis );

	/// Navigate to a sibling node.
	const TGlsXmlNode* PreviousSibling() const			{ return prev; }
	TGlsXmlNode* PreviousSibling()						{ return prev; }

	/// Navigate to a sibling node.
	const TGlsXmlNode* PreviousSibling( const char * ) const;
	TGlsXmlNode* PreviousSibling( const char * );


	/// Navigate to a sibling node.
	const TGlsXmlNode* NextSibling() const				{ return next; }
	TGlsXmlNode* NextSibling()							{ return next; }

	/// Navigate to a sibling node with the given 'value'.
	const TGlsXmlNode* NextSibling( const char * ) const;
	TGlsXmlNode* NextSibling( const char * );

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	const TGlsXmlElement* NextSiblingElement() const;
	TGlsXmlElement* NextSiblingElement();

	/** Convenience function to get through elements.
		Calls NextSibling and ToElement. Will skip all non-Element
		nodes. Returns 0 if there is not another element.
	*/
	const TGlsXmlElement* NextSiblingElement( const char * ) const;
	TGlsXmlElement* NextSiblingElement( const char * );


	/// Convenience function to get through elements.
	const TGlsXmlElement* FirstChildElement()	const;
	TGlsXmlElement* FirstChildElement();

	/// Convenience function to get through elements.
	const TGlsXmlElement* FirstChildElement( const char * value ) const;
	TGlsXmlElement* FirstChildElement( const char * value );


	/** Query the type (as an enumerated value, above) of this node.
		The possible types are: DOCUMENT, ELEMENT, COMMENT,
								UNKNOWN, TEXT, and DECLARATION.
	*/
	virtual int Type() const	{ return type; }

	/** Return a pointer to the Document this node lives in.
		Returns null if not in a document.
	*/
	const TGlsXmlDocument* GetDocument() const;
	TGlsXmlDocument* GetDocument();

	/// Returns true if this node has no children.
	bool NoChildren() const						{ return !firstChild; }

	const TGlsXmlDocument* ToDocument()	const		{ return ( this && type == DOCUMENT ) ? (const TGlsXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	const TGlsXmlElement*  ToElement() const			{ return ( this && type == ELEMENT  ) ? (const TGlsXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	const TGlsXmlComment*  ToComment() const			{ return ( this && type == COMMENT  ) ? (const TGlsXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	const TGlsXmlUnknown*  ToUnknown() const			{ return ( this && type == UNKNOWN  ) ? (const TGlsXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	const TGlsXmlText*	   ToText()    const		{ return ( this && type == TEXT     ) ? (const TGlsXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	const TGlsXmlDeclaration* ToDeclaration() const	{ return ( this && type == DECLARATION ) ? (const TGlsXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	TGlsXmlDocument* ToDocument()			{ return ( this && type == DOCUMENT ) ? (TGlsXmlDocument*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	TGlsXmlElement*  ToElement()			{ return ( this && type == ELEMENT  ) ? (TGlsXmlElement*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	TGlsXmlComment*  ToComment()			{ return ( this && type == COMMENT  ) ? (TGlsXmlComment*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	TGlsXmlUnknown*  ToUnknown()			{ return ( this && type == UNKNOWN  ) ? (TGlsXmlUnknown*)  this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	TGlsXmlText*	   ToText()   			{ return ( this && type == TEXT     ) ? (TGlsXmlText*)     this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.
	TGlsXmlDeclaration* ToDeclaration()	{ return ( this && type == DECLARATION ) ? (TGlsXmlDeclaration*) this : 0; } ///< Cast to a more defined type. Will return null not of the requested type.

	/** Create an exact duplicate of this node and return it. The memory must be deleted
		by the caller. 
	*/
	virtual TGlsXmlNode* Clone() const = 0;

protected:
	TGlsXmlNode( NodeType _type );

	// Copy to the allocated object. Shared functionality between Clone, Copy constructor,
	// and the assignment operator.
	void CopyTo( TGlsXmlNode* target ) const;


	// Figure out what is at *p, and parse it. Returns null if it is not an xml node.
	TGlsXmlNode* Identify( const char* start, TGlsXmlEncoding encoding );

	// Internal Value function returning a TIXML_STRING
	const TGLSXML_STRING& SValue() const	{ return value ; }

	TGlsXmlNode*		parent;
	NodeType		type;

	TGlsXmlNode*		firstChild;
	TGlsXmlNode*		lastChild;

	TGLSXML_STRING	value;

	TGlsXmlNode*		prev;
	TGlsXmlNode*		next;

private:
	TGlsXmlNode( const TGlsXmlNode& );				// not implemented.
	void operator=( const TGlsXmlNode& base );	// not allowed.
};


/** An attribute is a name-value pair. Elements have an arbitrary
	number of attributes, each with a unique name.

	@note The attributes are not TiXmlNodes, since they are not
		  part of the tinyXML document object model. There are other
		  suggested ways to look at this problem.
*/
class TGlsXmlAttribute : public TGlsXmlBase
{
	friend class TGlsXmlAttributeSet;

public:
	/// Construct an empty attribute.
	TGlsXmlAttribute() : TGlsXmlBase()
	{
		document = 0;
		prev = next = 0;
	}


	/// Construct an attribute with a name and value.
	TGlsXmlAttribute( const char * _name, const char * _value )
	{
		name = _name;
		value = _value;
		document = 0;
		prev = next = 0;
	}

	const char*		Name()  const		{ return name.c_str (); }		///< Return the name of this attribute.
	const char*		Value() const		{ return value.c_str (); }		///< Return the value of this attribute.
	const int       IntValue() const;									///< Return the value of this attribute, converted to an integer.
	const double	DoubleValue() const;								///< Return the value of this attribute, converted to a double.

	/** QueryIntValue examines the value string. It is an alternative to the
		IntValue() method with richer error checking.
		If the value is an integer, it is stored in 'value' and 
		the call returns TGlsXML_SUCCESS. If it is not
		an integer, it returns TGlsXML_WRONG_TYPE.

		A specialized but useful call. Note that for success it returns 0,
		which is the opposite of almost all other TGlsnyXml calls.
	*/
	int QueryIntValue( int* value ) const;
	/// QueryDoubleValue examines the value string. See QueryIntValue().
	int QueryDoubleValue( double* value ) const;

	void SetName( const char* _name )	{ name = _name; }				///< Set the name of this attribute.
	void SetValue( const char* _value )	{ value = _value; }				///< Set the value.

	void SetIntValue( int value );										///< Set the value from an integer.
	void SetDoubleValue( double value );								///< Set the value from a double.


	/// Get the next sibling attribute in the DOM. Returns null at end.
	const TGlsXmlAttribute* Next() const;
	TGlsXmlAttribute* Next();
	/// Get the previous sibling attribute in the DOM. Returns null at beginning.
	const TGlsXmlAttribute* Previous() const;
	TGlsXmlAttribute* Previous();

	bool operator==( const TGlsXmlAttribute& rhs ) const { return rhs.name == name; }
	bool operator<( const TGlsXmlAttribute& rhs )	 const { return name < rhs.name; }
	bool operator>( const TGlsXmlAttribute& rhs )  const { return name > rhs.name; }

	/*	Attribute parsing starts: first letter of the name
						 returns: the next char after the value end quote
	*/
	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

	// Prints this Attribute to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual void StreamOut( TGLSXML_OSTREAM * out ) const;
	// [internal use]
	// Set the document pointer so the attribute can report errors.
	void SetDocument( TGlsXmlDocument* doc )	{ document = doc; }

private:
	TGlsXmlAttribute( const TGlsXmlAttribute& );				// not implemented.
	void operator=( const TGlsXmlAttribute& base );	// not allowed.

	TGlsXmlDocument*	document;	// A pointer back to a document, for error reporting.
	TGLSXML_STRING name;
	TGLSXML_STRING value;
	TGlsXmlAttribute*	prev;
	TGlsXmlAttribute*	next;
};


/*	A class used to manage a group of attributes.
	It is only used internally, both by the ELEMENT and the DECLARATION.
	
	The set can be changed transparent to the Element and Declaration
	classes that use it, but NOT transparent to the Attribute
	which has to implement a next() and previous() method. Which makes
	it a bit problematic and prevents the use of STL.

	This version is implemented with circular lists because:
		- I like circular lists
		- it demonstrates some independence from the (typical) doubly linked list.
*/
class TGlsXmlAttributeSet
{
public:
	TGlsXmlAttributeSet();
	~TGlsXmlAttributeSet();

	void Add( TGlsXmlAttribute* attribute );
	void Remove( TGlsXmlAttribute* attribute );

	const TGlsXmlAttribute* First()	const	{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	TGlsXmlAttribute* First()					{ return ( sentinel.next == &sentinel ) ? 0 : sentinel.next; }
	const TGlsXmlAttribute* Last() const		{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }
	TGlsXmlAttribute* Last()					{ return ( sentinel.prev == &sentinel ) ? 0 : sentinel.prev; }

	const TGlsXmlAttribute*	Find( const char * name ) const;
	TGlsXmlAttribute*	Find( const char * name );

private:
	//*ME:	Because of hidden/disabled copy-construktor in TiXmlAttribute (sentinel-element),
	//*ME:	this class must be also use a hidden/disabled copy-constructor !!!
	TGlsXmlAttributeSet( const TGlsXmlAttributeSet& );	// not allowed
	void operator=( const TGlsXmlAttributeSet& );	// not allowed (as TGlsXmlAttribute)

	TGlsXmlAttribute sentinel;
};


/** The element is a container class. It has a value, the element name,
	and can contain other elements, text, comments, and unknowns.
	Elements also contain an arbitrary number of attributes.
*/
class TGlsXmlElement : public TGlsXmlNode
{
public:
	/// Construct an element.
	TGlsXmlElement (const char * in_value);

	TGlsXmlElement( const TGlsXmlElement& );

	void operator=( const TGlsXmlElement& base );

	virtual ~TGlsXmlElement();

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
	*/
	const char* Attribute( const char* name ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an integer,
		the integer value will be put in the return 'i', if 'i'
		is non-null.
	*/
	const char* Attribute( const char* name, int* i ) const;

	/** Given an attribute name, Attribute() returns the value
		for the attribute of that name, or null if none exists.
		If the attribute exists and can be converted to an double,
		the double value will be put in the return 'd', if 'd'
		is non-null.
	*/
	const char* Attribute( const char* name, double* d ) const;

	/** QueryIntAttribute examines the attribute - it is an alternative to the
		Attribute() method with richer error checking.
		If the attribute is an integer, it is stored in 'value' and 
		the call returns TIXML_SUCCESS. If it is not
		an integer, it returns TIXML_WRONG_TYPE. If the attribute
		does not exist, then TIXML_NO_ATTRIBUTE is returned.
	*/	
	int QueryIntAttribute( const char* name, int* value ) const;
	/// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
	int QueryDoubleAttribute( const char* name, double* value ) const;
	/// QueryFloatAttribute examines the attribute - see QueryIntAttribute().
	int QueryDoubleAttribute( const char* name, float* value ) const {
		double d;
		int result = QueryDoubleAttribute( name, &d );
		*value = (float)d;
		return result;
	}

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetAttribute( const char* name, const char * value );


	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetAttribute( const char * name, int value );

	/** Sets an attribute of name to a given value. The attribute
		will be created if it does not exist, or changed if it does.
	*/
	void SetDoubleAttribute( const char * name, double value );

	/** Deletes an attribute with the given name.
	*/
	void RemoveAttribute( const char * name );

	const TGlsXmlAttribute* FirstAttribute() const	{ return attributeSet.First(); }		///< Access the first attribute in this element.
	TGlsXmlAttribute* FirstAttribute() 				{ return attributeSet.First(); }
	const TGlsXmlAttribute* LastAttribute()	const 	{ return attributeSet.Last(); }		///< Access the last attribute in this element.
	TGlsXmlAttribute* LastAttribute()					{ return attributeSet.Last(); }

	/// Creates a new Element and returns it - the returned element is a copy.
	virtual TGlsXmlNode* Clone() const;
	// Print the Element to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: next char past '<'
						 returns: next char past '>'
	*/
	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

protected:

	void CopyTo( TGlsXmlElement* target ) const;
	void ClearThis();	// like clear, but initializes 'this' object as well

	// Used to be public [internal use]
	virtual void StreamOut( TGLSXML_OSTREAM * out ) const;

	/*	[internal use]
		Reads the "value" of the element -- another element, or text.
		This should terminate with the current end tag.
	*/
	const char* ReadValue( const char* in, TGlsXmlParsingData* prevData, TGlsXmlEncoding encoding );

private:

	TGlsXmlAttributeSet attributeSet;
};


/**	An XML comment.
*/
class TGlsXmlComment : public TGlsXmlNode
{
public:
	/// Constructs an empty comment.
	TGlsXmlComment() : TGlsXmlNode( TGlsXmlNode::COMMENT ) {}
	TGlsXmlComment( const TGlsXmlComment& );
	void operator=( const TGlsXmlComment& base );

	virtual ~TGlsXmlComment()	{}

	/// Returns a copy of this Comment.
	virtual TGlsXmlNode* Clone() const;
	/// Write this Comment to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	/*	Attribtue parsing starts: at the ! of the !--
						 returns: next char past '>'
	*/
	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

protected:
	void CopyTo( TGlsXmlComment* target ) const;

	// used to be public
	virtual void StreamOut( TGLSXML_OSTREAM * out ) const;

private:

};


/** XML text. Contained in an element.
*/
class TGlsXmlText : public TGlsXmlNode
{
	friend class TGlsXmlElement;
public:
	/// Constructor.
	TGlsXmlText (const char * initValue) : TGlsXmlNode (TGlsXmlNode::TEXT)
	{
		SetValue( initValue );
	}
	virtual ~TGlsXmlText() {}

	TGlsXmlText( const TGlsXmlText& copy ) : TGlsXmlNode( TGlsXmlNode::TEXT ) { copy.CopyTo( this ); }
	void operator=( const TGlsXmlText& base )  { base.CopyTo( this ); }

	/// Write this text object to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

protected :
	///  [internal use] Creates a new Element and returns it.
	virtual TGlsXmlNode* Clone() const;
	void CopyTo( TGlsXmlText* target ) const;

	virtual void StreamOut ( TGLSXML_OSTREAM * out ) const;
	bool Blank() const;	// returns true if all white space and new lines
	// [internal use]
private:
};


/** In correct XML the declaraTGlson is the first entry in the file.
	@verbatim
		<?xml version="1.0" standalone="yes"?>
	@endverbatim

	TinyXml will happily read or write files without a declaration,
	however. There are 3 possible attributes to the declaration:
	version, encoding, and standalone.

	Note: In this version of the code, the attributes are
	handled as special cases, not generic attributes, simply
	because there can only be at most 3 and they are always the same.
*/
class TGlsXmlDeclaration : public TGlsXmlNode
{
public:
	/// Construct an empty declaration.
	TGlsXmlDeclaration()   : TGlsXmlNode( TGlsXmlNode::DECLARATION ) {}


	/// Construct.
	TGlsXmlDeclaration(	const char* _version,
						const char* _encoding,
						const char* _standalone );

	TGlsXmlDeclaration( const TGlsXmlDeclaration& copy );
	void operator=( const TGlsXmlDeclaration& copy );

	virtual ~TGlsXmlDeclaration()	{}

	/// Version. Will return an empty string if none was found.
	const char *Version() const			{ return version.c_str (); }
	/// Encoding. Will return an empty string if none was found.
	const char *Encoding() const		{ return encoding.c_str (); }
	/// Is this a standalone document?
	const char *Standalone() const		{ return standalone.c_str (); }

	/// Creates a copy of this Declaration and returns it.
	virtual TGlsXmlNode* Clone() const;
	/// Print this declaration to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

protected:
	void CopyTo( TGlsXmlDeclaration* target ) const;
	// used to be public
	virtual void StreamOut ( TGLSXML_OSTREAM * out) const;

private:

	TGLSXML_STRING version;
	TGLSXML_STRING encoding;
	TGLSXML_STRING standalone;
};


/** Any tag that tinyXml doesn't recognize is saved as an
	unknown. It is a tag of text, but should not be modified.
	It will be written back to the XML, unchanged, when the file
	is saved.

	DTD tags get thrown into TiXmlUnknowns.
*/
class TGlsXmlUnknown : public TGlsXmlNode
{
public:
	TGlsXmlUnknown() : TGlsXmlNode( TGlsXmlNode::UNKNOWN )	{}
	virtual ~TGlsXmlUnknown() {}

	TGlsXmlUnknown( const TGlsXmlUnknown& copy ) : TGlsXmlNode( TGlsXmlNode::UNKNOWN )		{ copy.CopyTo( this ); }
	void operator=( const TGlsXmlUnknown& copy )										{ copy.CopyTo( this ); }

	/// Creates a copy of this Unknown and returns it.
	virtual TGlsXmlNode* Clone() const;
	/// Print this Unknown to a FILE stream.
	virtual void Print( FILE* cfile, int depth ) const;

	virtual const char* Parse( const char* p, TGlsXmlParsingData* data, TGlsXmlEncoding encoding );

protected:
	void CopyTo( TGlsXmlUnknown* target ) const;

	virtual void StreamOut ( TGLSXML_OSTREAM * out ) const;

private:

};


/** Always the top level node. A document binds together all the
	XML pieces. It can be saved, loaded, and printed to the screen.
	The 'value' of a document node is the xml file name.
*/
class TGlsXmlDocument : public TGlsXmlNode
{
public:
	/// Create an empty document, that has no name.
	TGlsXmlDocument();
	/// Create a document with a name. The name of the document is also the filename of the xml.
	TGlsXmlDocument( const char * documentName );


	TGlsXmlDocument( const TGlsXmlDocument& copy );
	void operator=( const TGlsXmlDocument& copy );

	virtual ~TGlsXmlDocument() {}

	/** Load a file using the current document value.
		Returns true if successful. Will delete any existing
		document data before loading.
	*/
	bool LoadFile( TGlsXmlEncoding encoding = TGLSXML_DEFAULT_ENCODING );
	/// Save a file using the current document value. Returns true if successful.
	bool SaveFile() const;
	/// Load a file using the given filename. Returns true if successful.
	bool LoadFile( const char * filename, TGlsXmlEncoding encoding = TGLSXML_DEFAULT_ENCODING );
	/// Save a file using the given filename. Returns true if successful.
	bool SaveFile( const char * filename ) const;

	/** Parse the given null terminated block of xml data. Passing in an encoding to this
		method (either TIXML_ENCODING_LEGACY or TIXML_ENCODING_UTF8 will force TinyXml
		to use that encoding, regardless of what TinyXml might otherwise try to detect.
	*/
	virtual const char* Parse( const char* p, TGlsXmlParsingData* data = 0, TGlsXmlEncoding encoding = TGLSXML_DEFAULT_ENCODING );

	/** Get the root element -- the only top level element -- of the document.
		In well formed XML, there should only be one. TinyXml is tolerant of
		multiple elements at the document level.
	*/
	const TGlsXmlElement* RootElement() const		{ return FirstChildElement(); }
	TGlsXmlElement* RootElement()					{ return FirstChildElement(); }

	/** If an error occurs, Error will be set to true. Also,
		- The ErrorId() will contain the integer identifier of the error (not generally useful)
		- The ErrorDesc() method will return the name of the error. (very useful)
		- The ErrorRow() and ErrorCol() will return the location of the error (if known)
	*/	
	bool Error() const						{ return error; }

	/// Contains a textual (english) description of the error if one occurs.
	const char* ErrorDesc() const	{ return errorDesc.c_str(); }

	/** Generally, you probably want the error string ( ErrorDesc() ). But if you
		prefer the ErrorId, this function will fetch it.
	*/
	const int ErrorId()	const				{ return errorId; }

	/** Returns the location (if known) of the error. The first column is column 1, 
		and the first row is row 1. A value of 0 means the row and column wasn't applicable
		(memory errors, for example, have no row/column) or the parser lost the error. (An
		error in the error reporting, in that case.)

		@sa SetTabSize, Row, Column
	*/
	int ErrorRow()	{ return errorLocation.row+1; }
	int ErrorCol()	{ return errorLocation.col+1; }	///< The column where the error occured. See ErrorRow()

	/** By calling this method, with a tab size
		greater than 0, the row and column of each node and attribute is stored
		when the file is loaded. Very useful for tracking the DOM back in to
		the source file.

		The tab size is required for calculating the location of nodes. If not
		set, the default of 4 is used. The tabsize is set per document. Setting
		the tabsize to 0 disables row/column tracking.

		Note that row and column tracking is not supported when using operator>>.

		The tab size needs to be enabled before the parse or load. Correct usage:
		@verbatim
		TiXmlDocument doc;
		doc.SetTabSize( 8 );
		doc.Load( "myfile.xml" );
		@endverbatim

		@sa Row, Column
	*/
	void SetTabSize( int _tabsize )		{ tabsize = _tabsize; }

	int TabSize() const	{ return tabsize; }

	/** If you have handled the error, it can be reset with this call. The error
		state is automatically cleared if you Parse a new XML block.
	*/
	void ClearError()						{	error = false; 
												errorId = 0; 
												errorDesc = ""; 
												errorLocation.row = errorLocation.col = 0; 
												//errorLocation.last = 0; 
											}

	/** Dump the document to standard out. */
	void Print() const						{ Print( stdout, 0 ); }

	/// Print this Document to a FILE stream.
	virtual void Print( FILE* cfile, int depth = 0 ) const;
	// [internal use]
	void SetError( int err, const char* errorLocation, TGlsXmlParsingData* prevData, TGlsXmlEncoding encoding );

protected :
	virtual void StreamOut ( TGLSXML_OSTREAM * out) const;
	// [internal use]
	virtual TGlsXmlNode* Clone() const;

private:
	void CopyTo( TGlsXmlDocument* target ) const;

	bool error;
	int  errorId;
	TGLSXML_STRING errorDesc;
	int tabsize;
	TGlsXmlCursor errorLocation;
};


/**
	A TiXmlHandle is a class that wraps a node pointer with null checks; this is
	an incredibly useful thing. Note that TiXmlHandle is not part of the TinyXml
	DOM structure. It is a separate utility class.

	Take an example:
	@verbatim
	<Document>
		<Element attributeA = "valueA">
			<Child attributeB = "value1" />
			<Child attributeB = "value2" />
		</Element>
	<Document>
	@endverbatim

	Assuming you want the value of "attributeB" in the 2nd "Child" element, it's very
	easy to write a *lot* of code that looks like:

	@verbatim
	TiXmlElement* root = document.FirstChildElement( "Document" );
	if ( root )
	{
		TiXmlElement* element = root->FirstChildElement( "Element" );
		if ( element )
		{
			TiXmlElement* child = element->FirstChildElement( "Child" );
			if ( child )
			{
				TiXmlElement* child2 = child->NextSiblingElement( "Child" );
				if ( child2 )
				{
					// Finally do something useful.
	@endverbatim

	And that doesn't even cover "else" cases. TiXmlHandle addresses the verbosity
	of such code. A TiXmlHandle checks for null	pointers so it is perfectly safe
	and correct to use:

	@verbatim
	TiXmlHandle docHandle( &document );
	TiXmlElement* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).Element();
	if ( child2 )
	{
		// do something useful
	@endverbatim

	Which is MUCH more concise and useful.

	It is also safe to copy handles - internally they are nothing more than node pointers.
	@verbatim
	TiXmlHandle handleCopy = handle;
	@endverbatim

	What they should not be used for is iteration:

	@verbatim
	int i=0;
	while ( true )
	{
		TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", i ).Element();
		if ( !child )
			break;
		// do something
		++i;
	}
	@endverbatim

	It seems reasonable, but it is in fact two embedded while loops. The Child method is
	a linear walk to find the element, so this code would iterate much more than it needs
	to. Instead, prefer:

	@verbatim
	TiXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).FirstChild( "Child" ).Element();

	for( child; child; child=child->NextSiblingElement() )
	{
		// do something
	}
	@endverbatim
*/
class TGlsXmlHandle
{
public:
	/// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
	TGlsXmlHandle( TGlsXmlNode* node )					{ this->node = node; }
	/// Copy constructor
	TGlsXmlHandle( const TGlsXmlHandle& ref )			{ this->node = ref.node; }
	TGlsXmlHandle operator=( const TGlsXmlHandle& ref ) { this->node = ref.node; return *this; }

	/// Return a handle to the first child node.
	TGlsXmlHandle FirstChild() const;
	/// Return a handle to the first child node with the given name.
	TGlsXmlHandle FirstChild( const char * value ) const;
	/// Return a handle to the first child element.
	TGlsXmlHandle FirstChildElement() const;
	/// Return a handle to the first child element with the given name.
	TGlsXmlHandle FirstChildElement( const char * value ) const;

	/** Return a handle to the "index" child with the given name. 
		The first child is 0, the second 1, etc.
	*/
	TGlsXmlHandle Child( const char* value, int index ) const;
	/** Return a handle to the "index" child. 
		The first child is 0, the second 1, etc.
	*/
	TGlsXmlHandle Child( int index ) const;
	/** Return a handle to the "index" child element with the given name. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	TGlsXmlHandle ChildElement( const char* value, int index ) const;
	/** Return a handle to the "index" child element. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	TGlsXmlHandle ChildElement( int index ) const;

	/// Return the handle as a TiXmlNode. This may return null.
	TGlsXmlNode* Node() const			{ return node; } 
	/// Return the handle as a TiXmlElement. This may return null.
	TGlsXmlElement* Element() const	{ return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
	/// Return the handle as a TiXmlText. This may return null.
	TGlsXmlText* Text() const			{ return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
	/// Return the handle as a TiXmlUnknown. This may return null;
	TGlsXmlUnknown* Unknown() const			{ return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }

private:
	TGlsXmlNode* node;
};



#endif
