//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uRhombShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TRhombShape::TRhombShape(int X, int Y, int step, int number):  TBaseShape(X, Y, step, number)
{
    F_TypeShape = 3;
}

//--------------------------------------------------------------------------
void TRhombShape::Paint(TCanvas *Canvas)
{
   TPoint P[4];
   GetPointRhomb(P, BoundRect);
   SaveCanvas(Canvas);
   TBaseShape::Paint(Canvas);
   Canvas->Polygon(P, 3);
   if (DrawCaption)
      DrawText(Canvas->Handle, Caption.c_str(), -1, &BoundRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
   RestoreCanvas(Canvas);
}

//--------------------------------------------------------------------------------
void TRhombShape::GetPointRhomb(TPoint *Pt, TRect Rect)
{
   int x1, y1, x2, y2, x3, y3, x4, y4;
   div_t d_t;
   x1 = Rect.Left;

   d_t = div(int(Rect.Bottom - Rect.Top), 2);
   y1 = Rect.Top + d_t.quot;

   d_t = div(int(Rect.Right - Rect.Left), 2);
   x2 = Rect.Right - d_t.quot;

   y2 = Rect.Top;
   x3 = Rect.Right;
   y3 = y1;
   x4 = x2;
   y4 = Rect.Bottom;
   Pt[0] = TPoint(x1, y1);
   Pt[1] = TPoint(x2, y2);
   Pt[2] = TPoint(x3, y3);
   Pt[3] = TPoint(x4, y4);
}
