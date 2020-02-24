//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTrailer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTrailer::TTrailer(int Step, int number):TEllShape(0, 0, Step, number)
{
   BrushStyle = bsClear;
}

//------------------------------------------------------------------
void  TTrailer::Paint(TCanvas *Canvas)
{
   TRect R;
   SaveCanvas(Canvas);

   R.Left  = Center.x - int(F_Radius*F_Step);
   R.Top = Center.y - int(F_Radius*F_Step);
   R.Right = Center.x + int(F_Radius*F_Step);
   R.Bottom = Center.y + int(F_Radius*F_Step);
   BoundRect = R;
   Canvas->Brush->Style = BrushStyle;
   Canvas->Brush->Color = BrushColor;

   Canvas->Ellipse(BoundRect.Left, BoundRect.Top, BoundRect.Right, BoundRect.Bottom);
   RestoreCanvas(Canvas);
}
