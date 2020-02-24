//---------------------------------------------------------------------------

#include <vcl.h>
#include "uTfeRectShape.h"
#include "uCommonGraph.h"


#pragma hdrstop

#pragma package(smart_init)


TTfeRectShape::TTfeRectShape(int X, int Y, int step, int number): TRectShape(X, Y, step, number)
{
   TRect R;
   F_TypeShape = 5;
   Start = new TTail(0,0,0,0, step);
   End = new TTail(0,0,0,0, step);

   R = BoundRect;
   R.Left = R.Left + F_Step*2;
   R.Right = R.Right + F_Step*2;
   BoundRect = R;

   SetTail();
}

//--------------------------------------------------------------------------------------
TTfeRectShape::~TTfeRectShape()
{
   delete Start;
   delete End;
}

//------------------------------------------------------------------------------
void TTfeRectShape::SetTail()
{
   TPoint Point;
   Point = Point_StartShape;
   Start->PointEnd = Point;
   Point.x = Point.x - F_Step*2;
   Start->PointStart = Point;

   Point = Point_EndShape;
   End->PointStart = Point;
   Point.x = Point.x + F_Step*2;
   End->PointEnd = Point;

}

//-------------------------------------------------------------------------------
void TTfeRectShape::SetRect(int X, int Y, int Width, int Height)
{
   TRectShape::SetRect(X + F_Step*2, Y, Width,  Height);
   SetTail();
}


//-----------------------------------------------------------------------------
void TTfeRectShape::SetRect(TRect Rect)
{
   TRect Temp = Rect;
   Temp.Left = Temp.Left + F_Step*2;
   Temp.Right = Temp.Right + F_Step*2;
   TRectShape::SetRect(Temp);
   SetTail();
}

//-----------------------------------------------------------------------------
void TTfeRectShape::Paint(TCanvas *Canvas)
{
    SetTail();
    CopyPen();
    TRectShape::Paint(Canvas);
    Start->Paint(Canvas);
    End->Paint(Canvas);

}


//-------------------------------------------------------------------------------
bool TTfeRectShape::GetTailPoint(int num, TPoint &pt)
{
   bool res = ((num == 0) || (num == 1));
   if (num == 0)
     pt = Start->PointStart;
   if (num == 1)
     pt = End->PointEnd;
   return  res;
}

//---------------------------------------------------------------------
void  TTfeRectShape::CopyPen()
{
   Start->Color = PenColor;
   Start->Width = PenWidth;
   Start->Style = PenStyle;
   Start->Mode  = PenMode;

   End->Color = PenColor;
   End->Width = PenWidth;
   End->Style = PenStyle;
   End->Mode  = PenMode;
}


//--------------------------------------------------------------------------
void TTfeRectShape::SetBaseRect(TRect Rect)
{
   TBaseShape::SetBaseRect(Rect);
   SetTail();
}


//--------------------------------------------------------------------------
TBaseLine* __fastcall  TTfeRectShape::GetBaseLine(int AIndex)
{
   if (AIndex == 0)
      return dynamic_cast<TBaseLine*>(Start);
   if (AIndex == 1)
      return dynamic_cast<TBaseLine*>(End);
   return NULL;
}

//--------------------------------------------------------------------------
int __fastcall  TTfeRectShape::GetBaseLineCount()
{
   return 2;
}

TPoint __fastcall TTfeRectShape::GetPointTailStartShape()
{
  TPoint Res(0, 0);
  GetTailPoint(0, Res);
  return Res;
}

TPoint __fastcall TTfeRectShape::GetPointTailEndShape()
{
  TPoint Res(0, 0);
  GetTailPoint(1, Res);
  return Res;
}

bool TTfeRectShape::CopyObject(TBaseShape *ASource)
{
   bool res = TBaseShape::CopyObject(ASource);
   dynamic_cast<TTfeRectShape*>(ASource)->SetTail();
   return res;
}

AnsiString TTfeRectShape::Make_One_SimpleItem(int AIndex)
{
  char ch='\"';
  AnsiString Res = "";
  if (ParamAlt)
  {
    TParamAlternativeItem* I = ParamAlt->Items[AIndex];
    if (I)
    {
      Res = "rab(" + IntToStr(I->NUMBER) +
                   "," + IntToStr(AIndex + 1) +  //номер альтернативы
                   "," + ch + I->NAME+ch +
                   "," + ch + I->FUNCTION2 + ch +
                   "," + ch + I->ELEMENT + ch +
                   "," + float_2_string( I->B , 6) +
                   "," + float_2_string( I->T, 10) +
                   "," + float_2_string( I->V, 10) +
                   ",[[" + float_2_string( I->A1_B_F, 4) +
                   "," + float_2_string(I->B_F1N, 6) +
                   "," + float_2_string(I->B_F1B, 6) +
                   "],[" + float_2_string(I->A2_B_F, 4) +
                   "," + float_2_string(I->B_F2N, 6) +
                   "," + float_2_string(I->B_F2B, 6) +
                   "],[" + float_2_string(I->A3_B_F, 4) +
                   "," + float_2_string(I->B_F3N, 6) +
                   "," + float_2_string(I->B_F3B, 6) +
                   "]],[[" + float_2_string(I->A1_T_F, 4) +
                   "," + float_2_string(I->T_F1N, 10) +
                   "," + float_2_string(I->T_F1B, 10) +
                   "],[" + float_2_string(I->A2_T_F, 4) +
                   "," + float_2_string(I->T_F2N, 10) +
                   "," + float_2_string(I->T_F2B, 10) +
                   "],[" + float_2_string(I->A3_T_F, 4) +
                   "," + float_2_string(I->T_F3N, 10) +
                   "," + float_2_string(I->T_F3B, 10) +
                   "]],[[" + float_2_string(I->A1_V_F, 4) +
                   "," + float_2_string(I->V_F1N, 10) +
                   "," + float_2_string(I->V_F1B, 10) +
                   "],[" + float_2_string(I->A2_V_F, 4) +
                   "," + float_2_string(I->V_F2N, 10) +
                   "," + float_2_string(I->V_F2B, 10) +
                   "],[" + float_2_string(I->A3_V_F, 4) +
                   "," + float_2_string(I->V_F3N, 10)+
                   "," + float_2_string(I->V_F3B, 10)+
                   "]]" +
                   "," + ch + I->PREDICAT + ch + ").";

    }
  }
  return Res;

}




