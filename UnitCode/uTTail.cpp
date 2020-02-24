//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTTail.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


TTail::TTail(int x0, int y0, int x1, int y1, int Step):TBaseLine(x0, y0, x1, y1, Step)
{
   F_Step = Step;
   F_FirstRadius = 0;
   F_LastRadius = 0;
   End = new TTrailer(F_Step);
   Start = new TTrailer(F_Step);

}

//----------------------------------------------------------
TTail::~TTail()
{
   delete End;
   delete Start;
}

//---------------------------------------------------------------------------
void TTail::Paint(TCanvas *Canvas)
{
   TRect R;
   if ((F_FirstRadius == 0) && (F_LastRadius == 0))
     TBaseLine::Paint(Canvas);
   else
   {
      OldPenParent->Assign(Canvas->Pen);
      Canvas->Pen->Assign(this->Pen);
      Canvas->MoveTo(x0, y0);
      if (F_FirstRadius > 0)
      {
        Start->Center = TPoint(x0, y0);
        Start->Radius = F_FirstRadius;
        Start->Paint(Canvas);
      }
      Canvas->LineTo(x1, y1);
      if (F_LastRadius > 0)
      {
        End->Center = TPoint(x1, y1);
        End->Radius = F_LastRadius;
        End->Paint(Canvas);
      }
      Canvas->LineTo(x1, y1);

      Canvas->Pen->Assign(OldPenParent);
   }
}
