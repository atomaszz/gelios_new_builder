//---------------------------------------------------------------------------

#ifndef UGlsXmlStringH
#define UGlsXmlStringH
//---------------------------------------------------------------------------
#include <assert.h>


class TGlsXmlString
{
  public :
    explicit TGlsXmlString (const char * instring);
    TGlsXmlString ()
    {
        allocated = 0;
        cstring = NULL;
        current_length = 0;
    }

    explicit TGlsXmlString (const TGlsXmlString& copy);

    ~TGlsXmlString ()
    {
        empty_it();
    }

    const char *c_str () const
    {
        if (allocated)
            return cstring;
        return "";
    }

    size_t length() const
    {
       return ( allocated ) ? current_length : 0;
    }

    void operator = (const char * content);

    void operator = (const TGlsXmlString & copy);

    TGlsXmlString& operator += (const char * suffix)
    {
        append (suffix);
		return *this;
    }

    TGlsXmlString& operator += (char single)
    {
        append (single);
		return *this;
    }

    TGlsXmlString& operator += (TGlsXmlString & suffix)
    {
        append (suffix);
		return *this;
    }
    bool operator == (const TGlsXmlString & compare) const;
    bool operator == (const char* compare) const;
    bool operator < (const TGlsXmlString & compare) const;
    bool operator > (const TGlsXmlString & compare) const;
    bool operator != (const TGlsXmlString & compare) const;
    bool operator != (const char* compare) const;

    bool equal (const TGlsXmlString & compare) const;
    bool equal (const char* compare) const;

    bool empty() const
    {
        return length() ? false : true;
    }

    const char& at(unsigned index) const
    {
        assert( index < length ());
        return cstring [index];
    }

    unsigned find(char lookup) const
    {
        return find(lookup, 0);
    }

    unsigned find(char tofind, unsigned offset) const;

    void reserve(unsigned size)
    {
        empty_it();
        if (size)
        {
            allocated = size;
            cstring = new char [size];
            cstring [0] = 0;
            current_length = 0;
        }
    }

    char& operator[] (unsigned index) const
    {
        assert( index < length ());
        return cstring [index];
    }

    enum {  notfound = 0xffffffff,
            npos = notfound };

    void append(const char *str, size_t len );

  protected :

    char* cstring;
    size_t allocated;
    size_t current_length;

    size_t assign_new_size(size_t  minimum_to_allocate)
    {
        return minimum_to_allocate * 2;
    }

    void empty_it()
    {
        if (cstring)
            delete []cstring;
        cstring = NULL;
        allocated = 0;
        current_length = 0;
    }

    void append(const char *suffix );

    void append(const TGlsXmlString & suffix)
    {
        append(suffix.c_str());
    }

    void append(char single)
    {
        if ( cstring && current_length < (allocated-1) )
		{
			cstring[ current_length ] = single;
			++current_length;
			cstring[ current_length ] = 0;
		}
		else
		{
			char smallstr [2];
			smallstr [0] = single;
			smallstr [1] = 0;
			append (smallstr);
		}
    }

} ;

class TGlsXmlOutStream : public TGlsXmlString
{
public :
    TGlsXmlOutStream() : TGlsXmlString () {}

    TGlsXmlOutStream& operator << (const char * in)
    {
        append (in);
        return (*this);
    }

    TGlsXmlOutStream& operator << (const TGlsXmlString & in)
    {
        append (in.c_str ());
        return (*this);
    }
} ;
#endif
