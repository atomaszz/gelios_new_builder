//---------------------------------------------------------------------------

#ifndef uHexahedronShapeH
#define uHexahedronShapeH
#include "uBaseShape.h"

class THexahedronShape: public TBaseShape
{
  public:
   THexahedronShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
   void  Paint(TCanvas *Canvas);
};

//---------------------------------------------------------------------------
#endif
