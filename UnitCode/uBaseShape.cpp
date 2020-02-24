//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uBaseShape.h"
#include "uFlagShape.h"
#include "uBaseLine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TBaseShape::TBaseShape(int X, int Y, int step, int number)
{
   F_BrushColor = clWhite;
   F_PenColor = clBlack;
   F_FrameColor = clRed;
   F_BrushStyle = bsClear;
   F_PenMode =  pmCopy;
   F_Font = new Graphics::TFont;

   F_PenWidth = 1;
   F_PenStyle = psSolid;
   F_DrawFrame = false;

   F_Old_Font = new Graphics::TFont;

   F_Id = number;
   F_Caption = IntToStr(F_Id);
   F_TypeShape = 0;

   F_Rect.Left = X;
   F_Rect.Top = Y - step*2 ;
   F_Rect.Right = X + step*4;
   F_Rect.Bottom = Y + step*2;
   F_Step = step;

   F_DrawLastFlag = F_DrawFirstFlag = false;


   F_FrameRect.Left = F_Rect.Left - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Top = F_Rect.Top - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Right = F_Rect.Right + OFFS_FRAME*F_PenWidth;
   F_FrameRect.Bottom = F_Rect.Bottom +OFFS_FRAME*F_PenWidth;
   F_DrawCaption = true;
   F_LEControl = NULL;
   F_WndHandler = 0;
   F_LEFrame = 0;
   F_UnderControl = NULL;
   f_LEControl =  false;
   f_ApplyAttribute = true;
   f_LEActive = true;
   f_WorkLines = new TList;
   f_Tag = 0;
   f_IdAlternative = 0;
   f_NumAlternative = 0;
   f_IdAlternativeParent = 0;
   f_NumAlternativeParent = 0;
   f_ParamAlt = NULL;
   f_Clon = NULL;
}


//-----------------------------------------------------------
TBaseShape::~TBaseShape()
{
   delete F_Font;
   delete F_Old_Font;
   delete f_WorkLines;
   if (F_LEControl)
   {
      delete F_LEControl;
      F_LEControl = NULL;
   }
   if (f_ParamAlt)
   {
      delete f_ParamAlt;
      f_ParamAlt = NULL;
   }
}


//-----------------------------------------------------------
void TBaseShape::SaveCanvas(TCanvas *Canvas)
{
    F_Old_BrushColor = Canvas->Brush->Color;
    F_Old_BrushStyle = Canvas->Brush->Style;
    F_Old_PenColor = Canvas->Pen->Color;
    F_Old_Font->Assign(Canvas->Font);
    F_Old_PenWidth = Canvas->Pen->Width;
    F_Old_PenStyle = Canvas->Pen->Style;
    F_Old_PenMode = Canvas->Pen->Mode;
}


//-----------------------------------------------------------
void TBaseShape::RestoreCanvas(TCanvas *Canvas)
{
    Canvas->Brush->Color = F_Old_BrushColor;
    Canvas->Pen->Color = F_Old_PenColor;
    Canvas->Font->Assign(F_Old_Font);
    Canvas->Pen->Width = F_Old_PenWidth;
    Canvas->Pen->Style = F_Old_PenStyle;
    Canvas->Pen->Mode = F_Old_PenMode;
    Canvas->Brush->Style = F_Old_BrushStyle;
}

//---------------------------------------------------------------
void TBaseShape::Paint(TCanvas *Canvas)
{
    TRect R;
    TPoint Pt;
    if (F_DrawFrame)
    {
       Canvas->Pen->Width = F_PenWidth;
       Canvas->Pen->Color = F_FrameColor;
       Canvas->Brush->Style = bsClear;
       Canvas->Pen->Mode  = F_PenMode;
       F_FrameRect.Left = F_Rect.Left - OFFS_FRAME*F_PenWidth;
       F_FrameRect.Top = F_Rect.Top - OFFS_FRAME*F_PenWidth;
       F_FrameRect.Right = F_Rect.Right + OFFS_FRAME*F_PenWidth;
       F_FrameRect.Bottom = F_Rect.Bottom + OFFS_FRAME*F_PenWidth;
       Canvas->Rectangle(F_FrameRect);
       R.Left = F_FrameRect.Left - D_FRAME*F_PenWidth;
       R.Right = F_FrameRect.Left + D_FRAME*F_PenWidth;
       R.Top = F_FrameRect.Top - D_FRAME*F_PenWidth;
       R.Bottom = F_FrameRect.Top + D_FRAME*F_PenWidth;
       Canvas->Ellipse(R);

       R.Left = F_FrameRect.Right - D_FRAME*F_PenWidth;
       R.Right = F_FrameRect.Right + D_FRAME*F_PenWidth;
       R.Top = F_FrameRect.Top - D_FRAME*F_PenWidth;
       R.Bottom = F_FrameRect.Top + D_FRAME*F_PenWidth;
       Canvas->Ellipse(R);

       R.Left = F_FrameRect.Right - D_FRAME*F_PenWidth;
       R.Right = F_FrameRect.Right + D_FRAME*F_PenWidth;
       R.Top = F_FrameRect.Bottom - D_FRAME*F_PenWidth;
       R.Bottom = F_FrameRect.Bottom + D_FRAME*F_PenWidth;
       Canvas->Ellipse(R);

       R.Left = F_FrameRect.Left - D_FRAME*F_PenWidth;
       R.Right = F_FrameRect.Left + D_FRAME*F_PenWidth;
       R.Top = F_FrameRect.Bottom - D_FRAME*F_PenWidth;
       R.Bottom = F_FrameRect.Bottom + D_FRAME*F_PenWidth;
       Canvas->Ellipse(R);
    }
    if (f_ApplyAttribute)
    {
      Canvas->Brush->Color = F_BrushColor;
      Canvas->Brush->Style = F_BrushStyle;
      Canvas->Pen->Color = F_PenColor;
      Canvas->Pen->Width = F_PenWidth;
      Canvas->Pen->Style = F_PenStyle;
      Canvas->Pen->Mode  = F_PenMode;
    }  
    Canvas->Font = F_Font;
//    Canvas->Font->Assign(F_Font);

}

//---------------------------------------------------------------
void TBaseShape::SetRealRect(int X, int Y, int Width, int Height)
{
   F_RealRect.Left = X;
   F_RealRect.Top = Y;
   F_RealRect.Right = X + Width;
   F_RealRect.Bottom = Y + Height;
}

//----------------------------------------------------------------
void TBaseShape::SetRealRect(TRect Rect)
{
  F_RealRect = Rect;
}

//----------------------------------------------------------------
void TBaseShape::SetRect(int X, int Y, int Width, int Height)
{
   F_Rect.Left = X;
   F_Rect.Top = Y;
   F_Rect.Right = X + Width;
   F_Rect.Bottom = Y + Height;
}


//----------------------------------------------------------------
void TBaseShape::SetRect(TRect Rect)
{
   F_Rect = Rect;
}

//--------------------------------------------------------------------
TRect TBaseShape::GetRealRect()
{
   return F_RealRect;
}


//----------------------------------------------------------------
TRect TBaseShape::GetRect()
{
   return F_Rect;
}

//------------------------------------------------------------------
int TBaseShape::PointInFrame(int X, int Y)
{
   int left1, left2, top1, top2, right1, right2, bottom1, bottom2;
   TRect R;
   if (!F_DrawFrame) return 0;
   F_FrameRect.Left = F_Rect.Left - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Top = F_Rect.Top - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Right = F_Rect.Right + OFFS_FRAME*F_PenWidth;
   F_FrameRect.Bottom = F_Rect.Bottom +OFFS_FRAME*F_PenWidth;

   left1 = F_FrameRect.Left + D_FRAME*F_PenWidth;
   left2 = F_FrameRect.Left - D_FRAME*F_PenWidth;
   top1  = F_FrameRect.Top +  D_FRAME*F_PenWidth;
   top2  = F_FrameRect.Top -  D_FRAME*F_PenWidth;
   right1 = F_FrameRect.Right +  D_FRAME*F_PenWidth;
   right2 = F_FrameRect.Right -  D_FRAME*F_PenWidth;
   bottom1 = F_FrameRect.Bottom +  D_FRAME*F_PenWidth;
   bottom2 = F_FrameRect.Bottom -  D_FRAME*F_PenWidth;

   R.Left = left2;
   R.Top = top2;
   R.Right = left1;
   R.Bottom =top1;

   if (PtInRect(&R, TPoint(X, Y))) return 1;

   R.Left = right2;
   R.Top = top2;
   R.Right = right1;
   R.Bottom =top1;

   if (PtInRect(&R, TPoint(X, Y))) return 2;

   R.Left = right2;
   R.Top = bottom2;
   R.Right = right1;
   R.Bottom =bottom1;

   if (PtInRect(&R, TPoint(X, Y))) return 3;


   R.Left = left2;
   R.Top = bottom2;
   R.Right = left1;
   R.Bottom = bottom1;

   if (PtInRect(&R, TPoint(X, Y))) return 4;

   /*
   if ( (X < left1 && X > left2) && (Y < top1 && Y > top2 )  ) return 1;
   if ( (Y < top1 && Y > top2 )  && ( X > left1 && X < right2) ) return 2;
   if ( (X < right1 && X > right2) && (Y < top1 && Y > top2 )  ) return 3;
   if ( (X < right1 && X > right2 )  && ( Y > top1 && Y < bottom2) ) return 4;
   if ( (X < right1 && X > right2 )  && ( Y < bottom1 && Y > bottom2) ) return 5;
   if ( (Y < bottom1 && Y > bottom2 )  && ( X > left1 && X < right2) ) return 6;
   if ( (X < left1 && X > left2 )  && ( Y < bottom1 && Y > bottom2) ) return 7;
   if ( (Y < bottom2 && Y > top1 )  && ( X > left2 && X < left1) ) return 8;
   */
   return 0;
}

//------------------------------------------------------------------------
TRect TBaseShape::GetFrameRect()
{
   F_FrameRect.Left = F_Rect.Left - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Top = F_Rect.Top - OFFS_FRAME*F_PenWidth;
   F_FrameRect.Right = F_Rect.Right + OFFS_FRAME*F_PenWidth;
   F_FrameRect.Bottom = F_Rect.Bottom + OFFS_FRAME*F_PenWidth;

   return F_FrameRect;
}


//-----------------------------------------------------------------------------
int __fastcall TBaseShape::GetTypeShape()
{
   return F_TypeShape;
}

//---------------------------------------------------------------------------
TPoint __fastcall TBaseShape::GetPointStartShape()
{
    return  (TPoint(F_Rect.Left, F_Rect.Top + int((F_Rect.Bottom - F_Rect.Top)/2)));
}

//------------------------------------------------------------------------
TPoint __fastcall TBaseShape::GetPointEndShape()
{
    return  (TPoint(F_Rect.Right, F_Rect.Top + int((F_Rect.Bottom - F_Rect.Top)/2)));
}

//------------------------------------------------------------------------
TPoint __fastcall TBaseShape::GetPointTailStartShape()
{
    return GetPointStartShape();
}

//------------------------------------------------------------------------
TPoint __fastcall TBaseShape::GetPointTailEndShape()
{
    return GetPointEndShape();
}


//-----------------------------------------------------------------------------------
TRect TBaseShape::FrameRectToRect(TRect R)
{
   TRect Res;
   Res = R;
   Res.Left = Res.Left + OFFS_FRAME*F_PenWidth;
   Res.Top = Res.Top + OFFS_FRAME*F_PenWidth;
   Res.Right = Res.Right - OFFS_FRAME*F_PenWidth;
   Res.Bottom = Res.Bottom - OFFS_FRAME*F_PenWidth;
   return Res;
}


//------------------------------------------------------------------------------
void TBaseShape::SetBaseRect(TRect Rect)
{
   F_Rect = Rect;
}


//------------------------------------------------------------------------------
bool TBaseShape::PowerIn()
{
  return false;
}

//------------------------------------------------------------------------------
void __fastcall TBaseShape::SetBoundRect(const TRect Value)
{
   //F_Rect = Value;
   SetBaseRect(Value);
   SetLEControl();
}


//------------------------------------------------------------------------------
void __fastcall TBaseShape::SetFont(Graphics::TFont*  Value)
{
   F_Font->Assign(Value);
}


void __fastcall TBaseShape::SetWndHandler(const HWND Value)
{
    F_WndHandler = Value;
    if (F_LEControl)
      F_LEControl->WndHandler = F_WndHandler;
}


void TBaseShape::DoSetLEFrame()
{
   if (F_LEControl)
   {
      F_LEControl->Left-= F_LEFrame;
      F_LEControl->Top-= F_LEFrame;
      F_LEControl->Width+= F_LEFrame;
      F_LEControl->Height+= F_LEFrame;
  }
}


void __fastcall TBaseShape::SetLEFrame(int Value)
{
   if (F_LEFrame != Value)
   {
      F_LEFrame = Value;
      DoSetLEFrame();
   }
}

void TBaseShape::SetLEControl()
{
   if (F_LEControl)
   {
      F_LEControl->Left = F_Rect.Left;
      F_LEControl->Top = F_Rect.Top;
      F_LEControl->Width = F_Rect.Width();
      F_LEControl->Height = F_Rect.Height();
      DoSetLEFrame();
  }
}

void __fastcall TBaseShape::SetUnderControl(TControl* Value)
{
    F_UnderControl = Value;
    if (F_LEControl)
      F_LEControl->UnderControl = F_UnderControl;
}


void __fastcall TBaseShape::SetCreateLEControl(bool Value)
{
  if ( (TypeShape == 100) || (TypeShape == 80) )
  {
    f_LEControl = Value;
    if (f_LEControl)
    {
      if (!F_LEControl)
      {
        F_LEControl = new TLEControl();
        F_LEControl->Source = this;
        F_LEControl->Id = F_Id;
        F_LEControl->UnderControl = F_UnderControl;
        F_LEControl->Active = f_LEActive;
      }
      SetLEControl();
    }
    else
    {
       delete  F_LEControl;
       F_LEControl = NULL;
    }
  }  

}


bool TBaseShape::ReactMouse(TPoint APoint)
{
   if (!F_LEControl) return false;
   return F_LEControl->React(APoint);
}


void TBaseShape::ApplyOffset(int Ax, int Ay)
{
   F_Rect.Left = F_Rect.Left + Ax;
   F_Rect.Right = F_Rect.Right + Ax;
   F_Rect.Top = F_Rect.Top + Ay;
   F_Rect.Bottom = F_Rect.Bottom + Ay;
}

void __fastcall TBaseShape::SetLEActive(bool AValue)
{
   if (f_LEActive != AValue)
   {
     f_LEActive = AValue;
     if (F_LEControl)
        F_LEControl->Active = f_LEActive;
   }
}


bool TBaseShape::CopyObject(TBaseShape *ASource)
{
   if(!ASource) return false;
   ASource->BrushColor = F_BrushColor;
   ASource->PenColor = F_PenColor;
   ASource->F_FrameColor = F_FrameColor; //цвет обрамл€ющего пр€моугольника
   ASource->F_Font->Assign(F_Font);
   ASource->F_PenWidth = F_PenWidth;  // ширина пена
   ASource->F_PenStyle = F_PenStyle;  //стиль пена
   ASource->F_BrushStyle = F_BrushStyle; //стиль браша
   ASource->Caption = F_Caption; //подпись фигуры
   ASource->F_PenMode = F_PenMode;
   ASource->F_Old_BrushColor = F_Old_BrushColor;
   ASource->F_Old_PenColor = F_Old_PenColor;
   ASource->F_Old_BrushStyle = F_Old_BrushStyle;
   ASource->F_Old_Font->Assign(F_Old_Font);
   ASource->F_Old_PenWidth = F_Old_PenWidth;
   ASource->F_Old_PenStyle = F_Old_PenStyle;
   ASource->F_Old_PenMode = F_Old_PenMode;

   ASource->F_Id = F_Id; //номер фигуры
   ASource->F_DrawCaption = F_DrawCaption;
   ASource->F_FrameRect = F_FrameRect;
   ASource->F_Rect = F_Rect;
   ASource->F_Step = F_Step;
   ASource->F_TypeShape = F_TypeShape;
   ASource->F_RealRect = F_RealRect;   //реальный пр€моугольник рисовани€
   return true;
}


TBaseLine* __fastcall TBaseShape::GetBaseLine(int AIndex)
{
   return NULL;
}

int __fastcall TBaseShape::GetBaseLineCount()
{
   return 0;
}

void TBaseShape::AddWorkLine(TRectLine *ALine)
{
   f_WorkLines->Add(ALine);
}

void TBaseShape::ClearWorkLine()
{
   f_WorkLines->Clear();
}


TRectLine* __fastcall  TBaseShape::GetWorkLine(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_WorkLines->Count - 1)
     return static_cast<TRectLine*>(f_WorkLines->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TBaseShape::GetWorkLineCount()
{
   return f_WorkLines->Count;
}


void TBaseShape::AddParamAlternativeItem(TParamAlternativeItem* AItem)
{
  if (AItem)
  {
     if (!f_ParamAlt)
       f_ParamAlt = new TParamAlternative;
     f_ParamAlt->AddItem(AItem);
  }
}

void TBaseShape::CheckNullParamAlt()
{
   if (f_ParamAlt->Count == 0)
   {
      delete f_ParamAlt;
      f_ParamAlt = NULL;
   }
}


void TBaseShape::DeleteParamAlternativeItem(int AIndex)
{
   f_ParamAlt->Delete(AIndex);
   CheckNullParamAlt();
}


void TBaseShape::DeleteParamAlternativeItem2(void* APointer)
{
   f_ParamAlt->Delete2(APointer);
   CheckNullParamAlt();
}

AnsiString TBaseShape::Make_One_Simple()
{
   AnsiString Res = "";
   if (f_ParamAlt)
   {
     for (int i = 0; i <= f_ParamAlt->Count - 1; i++)
     {
       if (i)
         Res = Res +"\r\n";
       Res = Res + Make_One_SimpleItem(i);
     }
   }
   return Res;
}

AnsiString TBaseShape::Make_One_SimpleItem(int AIndex)
{
   return "empty(nl).";
}


//------------------------------------------------------------------------------
/*
void  __fastcall TBaseShape::SetDrawFirstFlag(bool Value)
{
   F_DrawFirstFlag = Value;
   if (F_DrawFirstFlag && (!F_FirstFlag))
      F_FirstFlag =  new TFlagShape(F_Step, 0);
}


//------------------------------------------------------------------------------
void  __fastcall TBaseShape::SetDrawLastFlag(bool Value)
{
   F_DrawLastFlag = Value;
   if (F_DrawLastFlag && (!F_LastFlag))
      F_LastFlag = new TFlagShape(F_Step, 0);
}


//-------------------------------------------------------------------------------
bool TBaseShape::GetTailPoint(int num, TPoint &pt)
{
   return false;
}
*/

