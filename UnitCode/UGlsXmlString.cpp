//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UGlsXmlString.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)




// TiXmlString constructor, based on a C string
TGlsXmlString::TGlsXmlString (const char* instring)
{
    size_t newlen;
    char * newstring;

    if (!instring)
    {
        allocated = 0;
        cstring = NULL;
        current_length = 0;
        return;
    }
    newlen = strlen (instring) + 1;
    newstring = new char [newlen];
    memcpy (newstring, instring, newlen);
    // strcpy (newstring, instring);
    allocated = newlen;
    cstring = newstring;
    current_length = newlen - 1;
}

// TiXmlString copy constructor
TGlsXmlString::TGlsXmlString (const TGlsXmlString& copy)
{
    size_t newlen;
    char * newstring;

	// Prevent copy to self!
	if ( &copy == this )
		return;

    if (! copy . allocated)
    {
        allocated = 0;
        cstring = NULL;
        current_length = 0;
        return;
    }
    newlen = copy . length () + 1;
    newstring = new char [newlen];
    // strcpy (newstring, copy . cstring);
    memcpy (newstring, copy . cstring, newlen);
    allocated = newlen;
    cstring = newstring;
    current_length = newlen - 1;
}

// TiXmlString = operator. Safe when assign own content
void TGlsXmlString::operator= (const char * content)
{
    size_t newlen;
    char * newstring;

    if (! content)
    {
        empty_it ();
        return;
    }
    newlen = strlen (content) + 1;
    newstring = new char [newlen];
    // strcpy (newstring, content);
    memcpy (newstring, content, newlen);
    empty_it ();
    allocated = newlen;
    cstring = newstring;
    current_length = newlen - 1;
}

// = operator. Safe when assign own content
void TGlsXmlString::operator= (const TGlsXmlString & copy)
{
    size_t newlen;
    char * newstring;

    if (! copy . length ())
    {
        empty_it ();
        return;
    }
    newlen = copy . length () + 1;
    newstring = new char [newlen];
    // strcpy (newstring, copy . c_str ());
    memcpy (newstring, copy . c_str (), newlen);
    empty_it ();
    allocated = newlen;
    cstring = newstring;
    current_length = newlen - 1;
}


// append a const char * to an existing TiXmlString
void TGlsXmlString::append(const char* str, size_t len )
{
    char * new_string;
    size_t new_alloc, new_size, size_suffix;
	
	// don't use strlen - it can overrun the len passed in!
	const char* p = str;
	size_suffix = 0;

	while ( *p && size_suffix < (unsigned)len )
	{
		++p;
		++size_suffix;
	}
    if ( !size_suffix)
        return;

    new_size = length () + size_suffix + 1;
    // check if we need to expand
    if (new_size > allocated)
    {
        // compute new size
        new_alloc = assign_new_size (new_size);

        // allocate new buffer
        new_string = new char [new_alloc];        
        new_string [0] = 0;

        // copy the previous allocated buffer into this one
        if (allocated && cstring)
            // strcpy (new_string, cstring);
            memcpy (new_string, cstring, length ());

        // append the suffix. It does exist, otherwize we wouldn't be expanding 
        // strncat (new_string, str, len);
        memcpy (new_string + length (), 
                str,
                size_suffix);

        // return previsously allocated buffer if any
        if (allocated && cstring)
            delete [] cstring;

        // update member variables
        cstring = new_string;
        allocated = new_alloc;
    }
    else
    {
         // we know we can safely append the new string
        // strncat (cstring, str, len);
        memcpy (cstring + length (), 
                str,
                size_suffix);
    }
    current_length = new_size - 1;
    cstring [current_length] = 0;
}


// append a const char * to an existing TiXmlString
void TGlsXmlString::append( const char * suffix )
{
    char * new_string;
    size_t new_alloc, new_size;

    new_size = length () + strlen (suffix) + 1;
    // check if we need to expand
    if (new_size > allocated)
    {
        // compute new size
        new_alloc = assign_new_size (new_size);

        // allocate new buffer
        new_string = new char [new_alloc];        
        new_string [0] = 0;

        // copy the previous allocated buffer into this one
        if (allocated && cstring)
            memcpy (new_string, cstring, 1 + length ());
            // strcpy (new_string, cstring);

        // append the suffix. It does exist, otherwize we wouldn't be expanding 
        // strcat (new_string, suffix);
        memcpy (new_string + length (), 
                suffix,
                strlen (suffix) + 1);

        // return previsously allocated buffer if any
        if (allocated && cstring)
            delete [] cstring;

        // update member variables
        cstring = new_string;
        allocated = new_alloc;
    }
    else
    {
        // we know we can safely append the new string
        // strcat (cstring, suffix);
        memcpy (cstring + length (), 
                suffix, 
                strlen (suffix) + 1);
    }
    current_length = new_size - 1;
}

// Check for TiXmlString equuivalence
//bool TiXmlString::operator == (const TiXmlString & compare) const
//{
//    return (! strcmp (c_str (), compare . c_str ()));
//}

//unsigned TiXmlString::length () const
//{
//    if (allocated)
//        // return strlen (cstring);
//        return current_length;
//    return 0;
//}


unsigned TGlsXmlString::find (char tofind, unsigned offset) const
{
    char * lookup;

    if (offset >= length ())
        return (unsigned) notfound;
    for (lookup = cstring + offset; * lookup; lookup++)
        if (* lookup == tofind)
            return (unsigned)(lookup - cstring);
    return (unsigned) notfound;
}

bool TGlsXmlString::equal(const TGlsXmlString & compare) const
{
	if ( allocated && compare.allocated )
	{
		assert( cstring );
		assert( compare.cstring );
		return ( strcmp( cstring, compare.cstring ) == 0 );
 	}
	else if ( length() == 0 && compare.length() == 0 )
	{
		return true;
	}
	return false;
}

bool TGlsXmlString::equal(const char* compare) const
{
	if ( allocated && compare && *compare )
	{
		assert( cstring );
		return ( strcmp( cstring, compare ) == 0 );
 	}
	else if ( length() == 0 && (!compare || !*compare ) )	// this is a little dubious, but try to duplicate behavior in other operator==
	{
		return true;
	}
	return false;

}


bool TGlsXmlString::operator== (const TGlsXmlString & compare) const
{
        return equal(compare);
/*	if ( allocated && compare.allocated )
	{
		assert( cstring );
		assert( compare.cstring );
		return ( strcmp( cstring, compare.cstring ) == 0 );
 	}
	else if ( length() == 0 && compare.length() == 0 )
	{
		return true;
	}
	return false;
*/
}


bool TGlsXmlString::operator== (const char* compare) const
{
        return equal(compare);
/*	if ( allocated && compare && *compare )
	{
		assert( cstring );
		return ( strcmp( cstring, compare ) == 0 );
 	}
	else if ( length() == 0 && (!compare || !*compare ) )	// this is a little dubious, but try to duplicate behavior in other operator==
	{
		return true;
	}
	return false;
*/
}

bool TGlsXmlString::operator!= (const TGlsXmlString & compare) const
{
   return !equal(compare);
}

bool TGlsXmlString::operator!= (const char* compare) const
{
   return !equal(compare);

}



bool TGlsXmlString::operator< (const TGlsXmlString & compare) const
{
	if ( allocated && compare.allocated )
	{
		assert( cstring );
		assert( compare.cstring );
		return ( strcmp( cstring, compare.cstring ) > 0 );
 	}
	return false;
}


bool TGlsXmlString::operator> (const TGlsXmlString & compare) const
{
	if ( allocated && compare.allocated )
	{
		assert( cstring );
		assert( compare.cstring );
		return ( strcmp( cstring, compare.cstring ) < 0 );
 	}
	return false;
}


