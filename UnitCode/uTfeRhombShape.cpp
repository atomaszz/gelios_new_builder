//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTfeRhombShape.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTfeRhombShape::TTfeRhombShape(int X, int Y, int step, int number): TRhombShape(X, Y, step, number)
{
   TRect R;
   F_TypeShape = 6;
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
TTfeRhombShape::~TTfeRhombShape()
{
   delete  T0;
   delete  T1;
   delete  T2;
   delete  T3;
}

//-------------------------------------------------------------------------------
void TTfeRhombShape::SetRect(int X, int Y, int Width, int Height)
{
   TRhombShape::SetRect(X + F_Step*2, Y, Width,  Height);
   SetTail();
}


//-----------------------------------------------------------------------------
void TTfeRhombShape::SetRect(TRect Rect)
{
   TRect Temp = Rect;
   Temp.Left = Temp.Left + F_Step*2;
   Temp.Right = Temp.Right + F_Step*2;
   TRhombShape::SetRect(Temp);
   SetTail();
}

//------------------------------------------------------------------------------
void TTfeRhombShape::SetTail()
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
void TTfeRhombShape::Paint(TCanvas *Canvas)
{
    SetTail();
    CopyPen();
    TRhombShape::Paint(Canvas);
    T0->Paint(Canvas);
    T1->Paint(Canvas);
    T2->Paint(Canvas);
    T3->Paint(Canvas);

}


//-------------------------------------------------------------------------------
bool TTfeRhombShape::GetTailPoint(int num, TPoint &pt)
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
void __fastcall TTfeRhombShape::SetTailLeft(bool Value)
{
  F_TailLeft = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeRhombShape::SetTailTop(bool Value)
{
  F_TailTop = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeRhombShape::SetTailBottom(bool Value)
{
  F_TailBottom = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeRhombShape::SetTailRight(bool Value)
{
  F_TailRight = Value;
  SetTail();
}


//-----------------------------------------------------------------------
void  TTfeRhombShape::CopyPen()
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
void TTfeRhombShape::SetBaseRect(TRect Rect)
{
   TBaseShape::SetBaseRect(Rect);
   SetTail();
}

bool TTfeRhombShape::CopyObject(TBaseShape *ASource)
{
   TBaseShape::CopyObject(ASource);
   dynamic_cast<TTfeRhombShape*>(ASource)->TailLeft = F_TailLeft;
   dynamic_cast<TTfeRhombShape*>(ASource)->TailTop = F_TailTop;
   dynamic_cast<TTfeRhombShape*>(ASource)->TailBottom = F_TailBottom;
   dynamic_cast<TTfeRhombShape*>(ASource)->TailRight = F_TailRight;
   return true;
}

TPoint __fastcall TTfeRhombShape::GetPointTailStartShape()
{
  TPoint Res(0, 0);
  GetTailPoint(0, Res);
  return Res;
}


TPoint __fastcall TTfeRhombShape::GetPointTailEndShape()
{
  TPoint Res(0, 0);
  GetTailPoint(2, Res);
  return Res;
}


AnsiString TTfeRhombShape::Make_One_SimpleItem(int AIndex)
{
  char ch='\"';
  AnsiString Res = "";
  if (ParamAlt)
  {
    TParamAlternativeItem* I = ParamAlt->Items[AIndex];
    if (I)
    {
      Res = "control_rab(" + IntToStr(I->NUMBER) +
                   "," + IntToStr(AIndex + 1) +  //номер альтернативы
                   "," + ch + I->NAME + ch +
                   "," + ch + I->FUNCTION2 + ch +
                   "," + ch + I->ELEMENT + ch +
                   "," + ch + I->ELEM_DIAGN + ch +
                   "," + float_2_string(I->P_DIAGN_EL, 6) +
                   "," + float_2_string(I->P_11, 6) +
                   "," + float_2_string(I->P_00, 6) +
                   "," + float_2_string(I->T_D, 10) +
                   "," + float_2_string(I->V_D, 10) +
                   ",[[" + float_2_string(I->A1_P11_F, 4) +
                   "," + float_2_string(I->P11_F1N, 6) +
                   "," + float_2_string(I->P11_F1B, 6) +
                   "],[" + float_2_string(I->A2_P11_F, 4) +
                   "," + float_2_string(I->P11_F2N, 6) +
                   "," + float_2_string(I->P11_F2B, 6) +
                   "],[" + float_2_string(I->A3_P11_F, 4) +
                   "," + float_2_string(I->P11_F3N, 6) +
                   "," + float_2_string(I->P11_F3B, 6) +
                   "]],[[" + float_2_string(I->A1_P00_F, 4) +
                   "," + float_2_string(I->P00_F1N, 6) +
                   "," + float_2_string(I->P00_F1B, 6) +
                   "],[" + float_2_string(I->A2_P00_F, 4) +
                   "," + float_2_string(I->P00_F2N, 6) +
                   "," + float_2_string(I->P00_F2B, 6) +
                   "],[" + float_2_string(I->A3_P00_F, 4) +
                   "," + float_2_string(I->P00_F3N, 6) +
                   "," + float_2_string(I->P00_F3B, 6) +
                   "]],[[" + float_2_string(I->A1_TD_F, 4) +
                   "," + float_2_string(I->TD_F1N, 10) +
                   "," + float_2_string(I->TD_F1B, 10) +
                   "],[" + float_2_string(I->A2_TD_F, 4) +
                   "," + float_2_string(I->TD_F2N, 10) +
                   "," + float_2_string(I->TD_F2B, 10) +
                   "],[" + float_2_string(I->A3_TD_F, 4) +
                   "," + float_2_string(I->TD_F3N, 10) +
                   "," + float_2_string(I->TD_F3B, 10) +
                   "]],[[" + float_2_string(I->A1_VD_F, 4) +
                   "," + float_2_string(I->VD_F1N, 10) +
                   "," + float_2_string(I->VD_F1B, 10) +
                   "],[" + float_2_string(I->A2_VD_F, 4) +
                   "," + float_2_string(I->VD_F2N, 10) +
                   "," + float_2_string(I->VD_F2B, 10) +
                   "],[" + float_2_string(I->A3_VD_F, 4) +
                   "," + float_2_string(I->VD_F3N, 10) +
                   "," + float_2_string(I->VD_F3B, 10) +
                   "]],[[" + float_2_string(I->A1_P_EL_F, 4) +
                   "," + float_2_string(I->P_EL_F1N, 6) +
                   "," + float_2_string(I->P_EL_F1B, 6) +
                   "],[" + float_2_string(I->A2_P_EL_F, 4) +
                   "," + float_2_string(I->P_EL_F2N, 6) +
                   "," + float_2_string(I->P_EL_F2B, 6) +
                   "],[" + float_2_string(I->A3_P_EL_F, 4)+
                   "," + float_2_string(I->P_EL_F3N, 6) +
                   "," + float_2_string(I->P_EL_F3B, 6) +
                   "]]" + ","+ ch + I->PREDICAT + ch +   ").";

    }
  }
  return Res;
}

