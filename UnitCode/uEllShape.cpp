//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uEllShape.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

void TEllShape::Paint(TCanvas *Canvas)
{
  SaveCanvas(Canvas);
  TBaseShape::Paint(Canvas);
  Canvas->Ellipse(BoundRect.Left, BoundRect.Top, BoundRect.Right, BoundRect.Bottom);
  if (DrawCaption)
    DrawText(Canvas->Handle, Caption.c_str(), -1, &BoundRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  RestoreCanvas(Canvas);
}

TEllShape::TEllShape(int X, int Y, int step, int number):TBaseShape(X, Y, step, number)
{
   F_TypeShape = 2;
}
