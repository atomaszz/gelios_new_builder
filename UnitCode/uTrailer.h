//---------------------------------------------------------------------------

#ifndef uTrailerH
#define uTrailerH
#include "uEllShape.h"
//---------------------------------------------------------------------------
class TTrailer: public TEllShape
{
  private:
    TPoint F_Center;
    double F_Radius;
  public:
   TTrailer(int Step, int number=0);
   void  Paint(TCanvas *Canvas);
   __property TPoint Center  = {read = F_Center, write = F_Center};
   __property double Radius = {read = F_Radius, write = F_Radius};

};
#endif
