//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uHexahedronShape.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

THexahedronShape::THexahedronShape(int X, int Y, int step, int number):TBaseShape(X, Y, step,number)
{
    F_TypeShape = 4;
}

//-----------------------------------------------------------------------

void THexahedronShape::Paint(TCanvas *Canvas)
{
   TPoint P[6];
   int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
   div_t d_t;
   x1 = BoundRect.Left;

   d_t = div(int(BoundRect.Bottom - BoundRect.Top), 2);
   y1 = BoundRect.Top + d_t.quot;

   d_t = div(int(BoundRect.Right - BoundRect.Left), 3);
   x2 = BoundRect.Left + d_t.quot;

   y2 = BoundRect.Top;

   d_t = div(int(BoundRect.Right - BoundRect.Left), 3);
   x3 = BoundRect.Right - d_t.quot;

   y3 = BoundRect.Top;
   x4 = BoundRect.Right;
   y4 = y1;
   x5 = x3;
   y5 = BoundRect.Bottom;
   x6 = x2;
   y6 = BoundRect.Bottom;
   P[0] = TPoint(x1, y1);
   P[1] = TPoint(x2, y2);
   P[2] = TPoint(x3, y3);
   P[3] = TPoint(x4, y4);
   P[4] = TPoint(x5, y5);
   P[5] = TPoint(x6, y6);

   SaveCanvas(Canvas);
   TBaseShape::Paint(Canvas);
   Canvas->Polygon(P, 5);
   if (DrawCaption)
      DrawText(Canvas->Handle, Caption.c_str(), -1, &BoundRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
   RestoreCanvas(Canvas);
}


