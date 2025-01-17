//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsXmlError.h"
#include "uGlsXml.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



const char* TGlsXmlBase::errorString[ TGLSXML_ERROR_STRING_COUNT ] =
{
	"No error",
	"Error",
	"Failed to open file",
	"Memory allocation failed.",
	"Error parsing Element.",
	"Failed to read Element name",
	"Error reading Element value.",
	"Error reading Attributes.",
	"Error: empty tag.",
	"Error reading end tag.",
	"Error parsing Unknown.",
	"Error parsing Comment.",
	"Error parsing Declaration.",
	"Error document empty.",
	"Error null (0) or unexpected EOF found in input stream.",
};

