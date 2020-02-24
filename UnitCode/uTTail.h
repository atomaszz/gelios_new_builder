//---------------------------------------------------------------------------

#ifndef uTTailH
#define uTTailH
#include "uBaseLine.h"
#include "uTrailer.h"
//---------------------------------------------------------------------------
class TTail: public TBaseLine
{
   private:
     int F_Step;
     double F_FirstRadius;
     double F_LastRadius;
     TTrailer *End;
     TTrailer *Start;
   public:
     TTail(int x0, int y0, int x1, int y1, int Step);
     ~TTail();
     void Paint(TCanvas *Canvas);
     __property double  FirstRadius = {read = F_FirstRadius, write = F_FirstRadius};
     __property double  LastRadius = {read = F_LastRadius, write = F_LastRadius};
};


#endif
