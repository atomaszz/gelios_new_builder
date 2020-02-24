//---------------------------------------------------------------------------

#ifndef uArrowLineH
#define uArrowLineH
//---------------------------------------------------------------------------
#include "uRectLine.h"
class TArrowLine: public TRectLine
{
   private:
     int F_Step;
   public:
     TArrowLine(int Step, int Number=0);
     void Prepare();
     void Paint(TCanvas *Canvas);


};

#endif
