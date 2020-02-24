//---------------------------------------------------------------------------

#ifndef uRhombShapeH
#define uRhombShapeH
#include "uBaseShape.h"

class TRhombShape: public TBaseShape
{
  public:
    static void GetPointRhomb(TPoint *Pt, TRect Rect);
    TRhombShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
    void  Paint(TCanvas *Canvas);
};
//---------------------------------------------------------------------------
#endif
