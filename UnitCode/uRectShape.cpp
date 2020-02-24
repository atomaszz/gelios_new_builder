//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uRectShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TRectShape::Paint(TCanvas *Canvas)
{
  SaveCanvas(Canvas);
  TBaseShape::Paint(Canvas);
  Canvas->Rectangle(BoundRect.Left, BoundRect.Top, BoundRect.Right, BoundRect.Bottom);
  if (DrawCaption)
    DrawText(Canvas->Handle, Caption.c_str(), -1, &BoundRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  RestoreCanvas(Canvas);
}


//---------------------------------------------------------------------------------------
TRectShape::TRectShape(int X, int Y, int step, int number):TBaseShape(X, Y, step, number)
{
   TRect R;
   R.Left = X;
   R.Top = Y - step*2 ;
   R.Right = X + step*8;
   R.Bottom = Y + step*2;
   BoundRect = R;
   F_TypeShape = 1;
}


//-----------------------------------------------------------------------------------------
bool TRectShape::PowerIn()
{
  return true;
}
