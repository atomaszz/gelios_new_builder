//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTfeEllShape.h"
#include "uBaseShape.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTfeEllShape::TTfeEllShape(int X, int Y, int step, int number): TEllShape(X, Y, step, number)
{
   TRect R;
   F_TypeShape = 7;
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
TTfeEllShape::~TTfeEllShape()
{
   delete  T0;
   delete  T1;
   delete  T2;
   delete  T3;
}

//-------------------------------------------------------------------------------
void TTfeEllShape::SetRect(int X, int Y, int Width, int Height)
{
   TEllShape::SetRect(X + F_Step*2, Y, Width,  Height);
   SetTail();
}


//-----------------------------------------------------------------------------
void TTfeEllShape::SetRect(TRect Rect)
{
   TRect Temp = Rect;
   Temp.Left = Temp.Left + F_Step*2;
   Temp.Right = Temp.Right + F_Step*2;
   TEllShape::SetRect(Temp);
   SetTail();
}

//------------------------------------------------------------------------------
void TTfeEllShape::SetTail()
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
void TTfeEllShape::Paint(TCanvas *Canvas)
{
    SetTail();
    CopyPen();
    TEllShape::Paint(Canvas);
    T0->Paint(Canvas);
    T1->Paint(Canvas);
    T2->Paint(Canvas);
    T3->Paint(Canvas);

}


//-------------------------------------------------------------------------------
bool TTfeEllShape::GetTailPoint(int num, TPoint &pt)
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
void __fastcall TTfeEllShape::SetTailLeft(bool Value)
{
  F_TailLeft = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeEllShape::SetTailTop(bool Value)
{
  F_TailTop = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeEllShape::SetTailBottom(bool Value)
{
  F_TailBottom = Value;
  SetTail();
}

//-------------------------------------------------------------------
void __fastcall TTfeEllShape::SetTailRight(bool Value)
{
  F_TailRight = Value;
  SetTail();
}


//---------------------------------------------------------------------
void  TTfeEllShape::CopyPen()
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
void TTfeEllShape::SetBaseRect(TRect Rect)
{
   TBaseShape::SetBaseRect(Rect);
   SetTail();
}

bool TTfeEllShape::CopyObject(TBaseShape *ASource)
{
   TBaseShape::CopyObject(ASource);
   dynamic_cast<TTfeEllShape*>(ASource)->TailLeft = F_TailLeft;
   dynamic_cast<TTfeEllShape*>(ASource)->TailTop = F_TailTop;
   dynamic_cast<TTfeEllShape*>(ASource)->TailBottom = F_TailBottom;
   dynamic_cast<TTfeEllShape*>(ASource)->TailRight = F_TailRight;
   return true;
}

TPoint __fastcall TTfeEllShape::GetPointTailStartShape()
{
  TPoint Res(0, 0);
  GetTailPoint(0, Res);
  return Res;
}

TPoint __fastcall TTfeEllShape::GetPointTailEndShape()
{
  TPoint Res(0, 0);
  GetTailPoint(2, Res);
  return Res;
}


AnsiString TTfeEllShape::Make_One_SimpleItem(int AIndex)
{
  char ch='\"';
  AnsiString Res = "";
  if (ParamAlt)
  {
    TParamAlternativeItem* I = ParamAlt->Items[AIndex];
    if (I)
    {
      Res = "control_func(" + IntToStr(I->NUMBER) +
                   "," + IntToStr(AIndex + 1) +  //номер альтернативы
                   "," + ch + I->NAME + ch +
                   "," + ch + I->FUNCTION2 + ch +
                   "," + ch + I->ELEMENT + ch +
                   "," + float_2_string(I->K_11, 6) +
                   "," + float_2_string(I->K_00, 6) +
                   "," + float_2_string(I->T_F, 10) +
                   "," + float_2_string(I->V_F, 10) +
                   ",[[" + float_2_string(I->A1_K11_F, 4) +
                   "," + float_2_string(I->K11_F1N, 6) +
                   "," + float_2_string(I->K11_F1B, 6) +
                   "],[" + float_2_string(I->A2_K11_F, 4) +
                   "," + float_2_string(I->K11_F2N, 6) +
                   "," + float_2_string(I->K11_F2B, 6) +
                   "],[" + float_2_string(I->A3_K11_F, 4) +
                   "," + float_2_string(I->K11_F3N, 6) +
                   "," + float_2_string(I->K11_F3B, 6) +
                   "]],[[" + float_2_string(I->A1_K00_F, 4) +
                   "," + float_2_string(I->K00_F1N, 6) +
                   "," + float_2_string(I->K00_F1B, 6) +
                   "],[" + float_2_string(I->A2_K00_F, 4) +
                   "," + float_2_string(I->K00_F2N, 6) +
                   "," + float_2_string(I->K00_F2B, 6) +
                   "],[" + float_2_string(I->A3_K00_F, 4) +
                   "," + float_2_string(I->K00_F3N, 6) +
                   "," + float_2_string(I->K00_F3B, 6) +
                   "]],[[" + float_2_string(I->A1_TF_F, 4) +
                   "," + float_2_string(I->TF_F1N, 10) +
                   "," + float_2_string(I->TF_F1B, 10) +
                   "],[" + float_2_string(I->A2_TF_F, 4) +
                   "," + float_2_string(I->TF_F2N, 10) +
                   "," + float_2_string(I->TF_F2B, 10) +
                   "],[" + float_2_string(I->A3_TF_F, 4) +
                   "," + float_2_string(I->TF_F3N, 10) +
                   "," + float_2_string(I->TF_F3B, 10) +
                   "]],[[" + float_2_string(I->A1_VF_F, 4) +
                   "," + float_2_string(I->VF_F1N, 10) +
                   "," + float_2_string(I->VF_F1B, 10) +
                   "],[" + float_2_string(I->A2_VF_F, 4) +
                   "," + float_2_string(I->VF_F2N, 10) +
                   "," + float_2_string(I->VF_F2B, 10) +
                   "],[" + float_2_string(I->A3_VF_F, 4) +
                   "," + float_2_string(I->VF_F3N, 10) +
                   "," + float_2_string(I->VF_F3B, 10) +
                   "]]"+ "," + ch + I->PREDICAT + ch + ").";
    }
  }
  return Res;
}


