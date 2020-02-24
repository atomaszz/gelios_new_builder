//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uToolCommon.h"
#include "uToolConsts.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool IsTfsAlpha(int ASimType)
{
  return ( (ASimType == ST_TRANS) ||
    (ASimType == ST_RO) ||
    (ASimType == ST_FUNC) ||
    (ASimType == ST_DIAG) ||
    (ASimType == ST_START) ||
    (ASimType == ST_FIN) ||
    (ASimType == ST_BEGIN) ||
    (ASimType == ST_END));

}

bool IsTfsSep(int ASimType)
{
  return ((ASimType == ST_SEP_0) ||
    (ASimType == ST_SEP_1));
}


