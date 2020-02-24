//---------------------------------------------------------------------------

#ifndef uFreeRectLineH
#define uFreeRectLineH
#include "uRectLine.h"
//---------------------------------------------------------------------------
class TFreeRectLine: public TRectLine
{
   private:
     int f_XBend;
     int f_YBend;
   public:
     TFreeRectLine(int Step, int Number=0);
     void Prepare();
     __property int XBend = {read = f_XBend, write = f_XBend};
     __property int YBend = {read = f_YBend, write = f_YBend};
};
#endif
