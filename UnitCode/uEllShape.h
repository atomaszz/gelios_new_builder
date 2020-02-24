//---------------------------------------------------------------------------

#ifndef uEllShapeH
#define uEllShapeH
#include "uBaseShape.h"


class TEllShape: public TBaseShape
{
  public:
   TEllShape(int X, int Y, int step, int number=0);
   virtual void  Paint(TCanvas *Canvas);

};

//---------------------------------------------------------------------------
#endif
