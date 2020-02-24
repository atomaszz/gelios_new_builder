//---------------------------------------------------------------------------

#ifndef uRectShapeH
#define uRectShapeH
#include "uBaseShape.h"
//---------------------------------------------------------------------------
class TRectShape: public TBaseShape
{
  public:
   bool PowerIn();
   TRectShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
   void  Paint(TCanvas *Canvas);
};
#endif
