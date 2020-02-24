//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTfeHexahedronShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTfeHexahedronShape::TTfeHexahedronShape(int X, int Y, int step, int number): THexahedronShape(X, Y, step, number)
{
   TRect R;
   F_TypeShape = 8;
   F_TailLeft = F_TailTop = F_TailBottom = F_TailRight = false;
   T0 = new TTail(0,0,0,0, step);
   T1 = new TTail(0,0,0,0, step);
   T2 = new TTail(0,0,0,0, step);
   T3 = new TTail(0,0,0,0, step);

   R = BoundRect;
   R.Left = R.Left + F_Step*2;
   R.Right = R.Right + F_Step*2;
   BoundRect = R;
}


//---------------------------------------------------------------------------
TTfeHexahedronShape::~TTfeHexahedronShape()
{
   delete  T0;
   delete  T1;
   delete  T2;
   delete  T3;
}

//-------------------------------------------------------------------------------
void TTfeHexahedronShape::SetRect(int X, int Y, int Width, int Height)
{
   THexahedronShape::SetRect(X + F_Step*2, Y, Width,  Height);
   SetTail();
}


//-----------------------------------------------------------------------------
void TTfeHexahedronShape::SetRect(TRect Rect)
{
   TRect Temp = Rect;
   Temp.Left = Temp.Left + F_Step*2;
   Temp.Right = Temp.Right + F_Step*2;
   THexahedronShape::SetRect(Temp);
   SetTail();
}

//------------------------------------------------------------------------------
void TTfeHexahedronShape::SetTail()
{
   TPoint Point;
   int X, Y;
   if (F_TailLeft)
   {
     Point = Point_StartShape;
     T0->PointEnd = Point;
     Point.x = Point.x - F_Step*2;
     T0->PointStart = Point;
   }
   if (F_TailTop)
   {
     X = BoundRect.Left + int((BoundRect.Right - BoundRect.Left)/2);
     Y = BoundRect.Top;
     Point = TPoint(X,Y);
     T1->PointStart = Point;
     Point.y = Point.y - F_Step*2;
     T1->PointEnd = Point;
   }
   if (F_TailRight)
   {
     Point = Point_EndShape;
     T2->PointStart = Point;
     Point.x = Point.x + F_Step*2;
     T2->PointEnd = Point;
   }

   if (F_TailBottom)
   {
     X = BoundRect.Left + int((BoundRect.Right - BoundRect.Left)/2);
     Y = BoundRect.Bottom;
     Point = TPoint(X,Y);
     T3->PointStart = Point;
     Point.y = Point.y + F_Step*2;
     T3->PointEnd = Point;

   }

}

//-----------------------------------------------------------------------------
void TTfeHexahedronShape::Paint(TCanvas *Canvas)
{
    SetTail();
    CopyPen();
    THexahedronShape::Paint(Canvas);
    T0->Paint(Canvas);
    T1->Paint(Canvas);
    T2->Paint(Canvas);
    T3->Paint(Canvas);

}


//-------------------------------------------------------------------------------
bool TTfeHexahedronShape::GetTailPoint(int num, TPoint &pt)
{
   bool res = (((num == 0) && (F_TailLeft))
            || ((num == 1) && (F_TailTop))
            || ((num == 2) && (F_TailRight))
            || ((num == 3) && (F_TailBottom)));
   if (num == 0)
     pt = T0->PointStart;
   if (num == 1)
     pt = T1->PointEnd;
   if (num == 2)
     pt = T2->PointEnd;
   if (num == 3)
     pt = T3->PointEnd;

   return  res;
}


//-------------------------------------------------------------------
void __fastcall TTfeHexahedronShape::SetTailLeft(bool Value)
{
  F_TailLeft = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeHexahedronShape::SetTailTop(bool Value)
{
  F_TailTop = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeHexahedronShape::SetTailBottom(bool Value)
{
  F_TailBottom = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeHexahedronShape::SetTailRight(bool Value)
{
  F_TailRight = Value;
  SetTail();
}


//---------------------------------------------------------------------
void  TTfeHexahedronShape::CopyPen()
{
   T0->Color = PenColor;
   T0->Width = PenWidth;
   T0->Style = PenStyle;
   T0->Mode  = PenMode;

   T1->Color = PenColor;
   T1->Width = PenWidth;
   T1->Style = PenStyle;
   T1->Mode  = PenMode;

   T2->Color = PenColor;
   T2->Width = PenWidth;
   T2->Style = PenStyle;
   T2->Mode  = PenMode;

   T3->Color = PenColor;
   T3->Width = PenWidth;
   T3->Style = PenStyle;
   T3->Mode  = PenMode;

}


//---------------------------------------------------------------------
void TTfeHexahedronShape::SetBaseRect(TRect Rect)
{
   TBaseShape::SetBaseRect(Rect);
   SetTail();
}

TPoint __fastcall TTfeHexahedronShape::GetPointTailStartShape()
{
  TPoint Res(0, 0);
  GetTailPoint(0, Res);
  return Res;
}

TPoint __fastcall TTfeHexahedronShape::GetPointTailEndShape()
{
  TPoint Res(0, 0);
  GetTailPoint(2, Res);
  return Res;
}

bool TTfeHexahedronShape::CopyObject(TBaseShape *ASource)
{
   TBaseShape::CopyObject(ASource);
   dynamic_cast<TTfeHexahedronShape*>(ASource)->TailLeft = F_TailLeft;
   dynamic_cast<TTfeHexahedronShape*>(ASource)->TailTop = F_TailTop;
   dynamic_cast<TTfeHexahedronShape*>(ASource)->TailBottom = F_TailBottom;
   dynamic_cast<TTfeHexahedronShape*>(ASource)->TailRight = F_TailRight;
   return true;
}




AnsiString TTfeHexahedronShape::Make_One_SimpleItem(int AIndex)
{
  char ch='\"';
  AnsiString Res = "";
  if (ParamAlt)
  {
    TParamAlternativeItem* I = ParamAlt->Items[AIndex];
    if (I)
    {
      Res = "uslovie(" + IntToStr(I->NUMBER) +
                   "," + IntToStr(AIndex + 1) +
                   "," + ch + I->NAME + ch +
                   "," + ch + I->FUNCTION2 + ch +
                   "," + ch + I->ELEMENT + ch +
                   "," + ch + I->PREDICAT + ch + ").";
    }
  }
  return Res;
}


