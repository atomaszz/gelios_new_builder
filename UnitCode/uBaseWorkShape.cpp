//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uBaseWorkShape.h"
#include "uCompositeBaseWork.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//----------------------------------------------------------------------------
TBaseWorkShape::TBaseWorkShape(int X, int Y, int Step, int NumberShape_Id , int Block_Id, int NumberLine_Id )
{
   F_Step = Step;
   F_NumberShapeId = NumberShape_Id;
   F_NumberLineId = NumberLine_Id;
   F_BlockId = Block_Id;
   F_LastShapeId = F_NumberShapeId;
   F_LastLineId = F_NumberLineId;

   F_StartPoint.x = X;
   F_StartPoint.y = Y;
   f_BaseStartPoint = F_StartPoint;

   F_BrushColor = clWhite;
   F_BrushStyle = bsClear;
   F_PenColor = clBlack;
   F_FrameColor = clRed;
   F_PenMode =  pmCopy;
   F_Font = new Graphics::TFont;

   F_PenWidth = 1;
   F_PenStyle = psSolid;
   F_DrawFrame = false;

   F_LineColor = clBlack;
   F_LineWidth = 1;
   F_LineStyle = psSolid;
   F_LineMode =  pmCopy;

   F_IsLineCopy = true;
   F_IsBrushCopy = true;
   F_IsFontCopy = true;
   F_IsPenCopy = true;
   OnShapeCopy = NULL;
   OnLineCopy  = NULL;
   F_DrawCaption = true;

   F_DrawFirstFlag = false;
   F_DrawLastFlag = false;
   F_DrawMiddleFlag = false;

   WorkShapes = new TList;
   WorkLines = new TList;
   ListFlag = new TListFlag;

   f_LEControl = false;
   F_WndHandler = 0;
   F_UnderControl = NULL;

   F_FlagColor = clWhite;
   F_FlagType = 0;
   F_FlagSColor = clWhite;
   F_FlagSType = 0;
   F_FlagEColor = clWhite;
   F_FlagEType = 0;
   F_FrameColorTFE = clRed;

   FOnWSFlagCreate = NULL;
   FOnWSFlagDestroy = NULL;
   f_ApplyAttribute = true;
   F_DrawCaption = true;
   f_ParentShapeID = 0;
   f_Tag = 0;
   FOnAfterLinePrepare = NULL;
   f_LEActive = true;
   f_BaseOffsetX = 0;
   f_BaseOffsetY = 0;
   F_WidthWork = 0;
   F_Indent = 0;
   f_CompositeWorkShape = NULL;
}


//----------------------------------------------------------------------------
TBaseWorkShape::~TBaseWorkShape()
{
   delete F_Font;
   delete ListFlag;
   FreeWorkLines();
   FreeWorkShapes();
   delete WorkLines;
   delete WorkShapes;
   if (f_CompositeWorkShape)
     f_CompositeWorkShape->FreeRef();
}


//----------------------------------------------------------------------------
void TBaseWorkShape::FreeWorkLines()
{
   int i;
   TArrowLine *Line;
   for (i = WorkLines->Count - 1; i >= 0; i--)
   {
      Line  =  static_cast<TArrowLine*>(WorkLines->Items[i]);
      delete Line;
      WorkLines->Delete(i);
   }
}

//----------------------------------------------------------------------------
void TBaseWorkShape::FreeWorkShapes()
{
   int i;
   TBaseShape *Shp;
   for (i = WorkShapes->Count - 1; i >= 0; i--)
   {
      Shp  =  static_cast<TBaseShape*>(WorkShapes->Items[i]);
      delete Shp;
      WorkShapes->Delete(i);
   }

}



//------------------------------------------------------------------------------
void TBaseWorkShape::Init()
{

}

//------------------------------------------------------------------------------

void TBaseWorkShape::Prepare()
{
  if (f_CompositeWorkShape)
  {
      f_CompositeWorkShape->Prepare();
      return;
  }

  DoSetLEControl();
  DoSetWndHandler();
  DoSetUnderCotrol();
  DoSetLEActive();
  PrepareLines();
  PaintFirstFlag();
  PaintLastFlag();
  PaintMiddleFlag();
}


//------------------------------------------------------------------------------
void TBaseWorkShape::Paint(TCanvas *Canvas)
{
  int i;
  TBaseShape *currShape;
  TArrowLine *currLine;
  TColor OldPenColor;
  if (f_CompositeWorkShape)
  {
      f_CompositeWorkShape->Selected = F_DrawFrame;
      f_CompositeWorkShape->Paint(Canvas);
      return;
  }
  PenCopy();
  BrushCopy();
  FontCopy();
  for (i=0 ; i <= WorkShapes->Count-1 ;i++)
  {
    currShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    currShape->FrameColor = F_FrameColorTFE;

    OldPenColor = currShape->PenColor;
    if (F_DrawFrame) currShape->PenColor = F_FrameColor;

    if (OnShapeCopy) OnShapeCopy(currShape, i); //переставлено
    currShape->Paint(Canvas);
    currShape->PenColor = OldPenColor;

  }
  LineCopy();

  DoSetFlag();
  DoSetFlagS();
  DoSetFlagE();

  for (i=0; i<=WorkLines->Count-1; i++)
  {
    currLine = static_cast<TArrowLine*>(WorkLines->Items[i]);
    if (OnLineCopy) OnLineCopy(currLine, i);
    OldPenColor = currLine->Color;
    if (F_DrawFrame) currLine->Color = F_FrameColor;
    currLine->Paint(Canvas);
    currLine->Color = OldPenColor;
  }
 // DoDrawFrame(Canvas);

}



//-----------------------------------------------------------------------------
void TBaseWorkShape::AddShape(TBaseShape *N)
{
   WorkShapes->Add(N);
}


//------------------------------------------------------------------------------
void TBaseWorkShape::AddLine(TArrowLine *L)
{
  WorkLines->Add(L);
}


//---------------------------------------------------------------------------
TBaseShape* TBaseWorkShape::GetWorkShape(int num)
{
  TBaseShape* Res = NULL;
  if ( (num >=0) || (num < WorkShapes->Count) )
     Res =  static_cast<TBaseShape*>(WorkShapes->Items[num]);
  return Res;
}

//---------------------------------------------------------------------------
TBaseShape* TBaseWorkShape::GetWorkNode(int num)
{
  TBaseShape* N = NULL;
  if ( (num >=0) || (num < WorkShapes->Count) )
     N = static_cast<TBaseShape*>(WorkShapes->Items[num]);
  return N;
}

//-------------------------------------------------------------------------
TArrowLine*  TBaseWorkShape::GetWorkLine(int num)
{
  TArrowLine* Res = NULL;
  if ( (num >=0) || (num < WorkLines->Count) )
     Res = static_cast<TArrowLine*>(WorkLines->Items[num]);
  return Res;
}

//--------------------------------------------------------------------------
int __fastcall TBaseWorkShape::GetTypeShape()
{
   return 0;
}


//----------------------------------------------------------------------------
void TBaseWorkShape::PenCopy()
{
  TBaseShape* currShape;
  int i;
  if (!F_IsPenCopy) return;
  for (i = 0 ; i <= WorkShapes->Count-1 ;i++)
  {
    currShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    currShape->PenColor = PenColor;
    currShape->PenWidth = PenWidth;
    currShape->PenStyle = PenStyle;
    currShape->PenMode  = PenMode;
  }
}


//--------------------------------------------------------------------------
void TBaseWorkShape::BrushCopy()
{
  TBaseShape *currShape;
  int i;
  if (!F_IsBrushCopy) return;
  for (i = 0 ; i <= WorkShapes->Count-1 ;i++)
  {
    currShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    currShape->BrushColor = BrushColor;
    currShape->BrushStyle = BrushStyle;
  }

}

//---------------------------------------------------------------------------
void TBaseWorkShape::FontCopy()
{
  TBaseShape *currShape;
  int i;
  if (!F_IsFontCopy) return;
  for (i = 0 ; i <= WorkShapes->Count-1 ;i++)
  {
    currShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    currShape->Font = F_Font;
  }
}

//------------------------------------------------------------------------------
void TBaseWorkShape::LineCopy()
{
   TArrowLine *currLine;
   int i;
   for (i = 0; i <= WorkLines->Count-1; i++)
   {
     currLine = static_cast<TArrowLine*>(WorkLines->Items[i]);
     if (F_IsLineCopy)
     {
       currLine->Color = PenColor;
       currLine->Width = PenWidth;
       currLine->Style = PenStyle;
       currLine->Mode =  PenMode;
     }
     else
     {
       currLine->Color = LineColor;
       currLine->Width = LineWidth;
       currLine->Style = LineStyle;
       currLine->Mode =  LineMode;
     }
  }
}

//-----------------------------------------------------------------------------
TPoint __fastcall TBaseWorkShape::GetEndPoint()
{
   return TPoint(0, 0);
}


//-----------------------------------------------------------------------------
int __fastcall TBaseWorkShape::GetWorkLinesCount()
{
   return WorkLines->Count;
}

//------------------------------------------------------------------------------
int __fastcall TBaseWorkShape::GetWorkShapesCount()
{
   return WorkShapes->Count;
}

//-------------------------------------------------------------------------------
void __fastcall TBaseWorkShape::SetStartPoint(TPoint Value)
{
   F_StartPoint =  Value;
}

TPoint __fastcall  TBaseWorkShape::GetStartPoint()
{
   if (f_CompositeWorkShape)
     return f_CompositeWorkShape->StartPoint;
   return F_StartPoint;
}

TPoint TBaseWorkShape::GetStartPointOneComposite()
{
   return F_StartPoint;
}




void __fastcall  TBaseWorkShape::SetBaseStartPoint(TPoint Value)
{
   f_BaseStartPoint = Value;
}



//-------------------------------------------------------------------------------
void __fastcall TBaseWorkShape::SetFont(Graphics::TFont*  Value)
{
   F_Font->Assign(Value);
}

//-----------------------------------------------------------------------------
void TBaseWorkShape::SetOffsetPosition(int X_Ofs, int Y_Ofs)
{
  TRect R;
  TBaseShape *baseShape;
  TRectLine *baseLine;
  if (CompositeWorkShape)
  {
     CompositeWorkShape->ApplyOffset(X_Ofs, Y_Ofs);
     return;
  }
  for (int i=0 ; i <= WorkShapes->Count - 1 ;i++)
  {
    baseShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    R = baseShape->BoundRect;
    R.Left = R.Left + X_Ofs;
    R.Right = R.Right + X_Ofs;
    R.Top = R.Top + Y_Ofs;
    R.Bottom = R.Bottom + Y_Ofs;
    baseShape->BoundRect = R;
  }
}

void TBaseWorkShape::SetBaseOffsetPosition(int X_Ofs, int Y_Ofs)
{
   f_BaseOffsetX = X_Ofs;
   f_BaseOffsetY = Y_Ofs;
}


//------------------------------------------------------------------------------
bool __fastcall TBaseWorkShape::GetDrawCaption()
{
   return F_DrawCaption;
}

//------------------------------------------------------------------------------
void __fastcall TBaseWorkShape::SetDrawCaption(bool Value)
{
  TBaseShape *baseShape;
  F_DrawCaption = Value;
  for (int i = 0 ; i <= WorkShapes->Count - 1 ;i++)
  {
    baseShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    baseShape->DrawCaption = F_DrawCaption;
  }
}




TRect TBaseWorkShape::GetFrameRectWithLines()
{
  TRect Res, R_tmp;
  TBaseShape *baseShape;
  TArrowLine *currLine;
  int i;
  if (CompositeWorkShape)
    return CompositeWorkShape->GetMaxRect();

  baseShape = static_cast<TBaseShape*>(WorkShapes->Items[0]);
  Res = baseShape->GetRect();

  for (i = 1 ; i <= WorkShapes->Count - 1 ;i++)
  {
    baseShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    R_tmp = baseShape->GetRect();
    if (R_tmp.Left < Res.Left )  Res.Left = R_tmp.Left;
    if (R_tmp.Right > Res.Right) Res.Right = R_tmp.Right;
    if (R_tmp.Top < Res.Top) Res.Top = R_tmp.Top;
    if (R_tmp.Bottom > Res.Bottom) Res.Bottom = R_tmp.Bottom;
  }


  for (i=0; i<=WorkLines->Count-1; i++)
  {
     currLine = (TArrowLine *)WorkLines->Items[i];
     if (currLine->xStart <  Res.Left) Res.Left = currLine->xStart;
     if (currLine->xEnd <  Res.Left) Res.Left = currLine->xEnd;
     if (currLine->xStart >  Res.Right) Res.Right = currLine->xStart;
     if (currLine->xEnd >  Res.Right) Res.Right = currLine->xEnd;

     if (currLine->yStart <  Res.Top) Res.Top = currLine->yStart;
     if (currLine->yEnd <  Res.Top) Res.Top = currLine->yEnd;
     if (currLine->yStart >  Res.Bottom) Res.Bottom = currLine->yStart;
     if (currLine->yEnd >  Res.Bottom) Res.Bottom = currLine->yEnd;

  }

  Res.Left = Res.Left - OFFS_FRAME*PenWidth;
  Res.Top = Res.Top - OFFS_FRAME*PenWidth;
  Res.Right = Res.Right + OFFS_FRAME*PenWidth;
  Res.Bottom = Res.Bottom + OFFS_FRAME*PenWidth;
  F_Ofs_Point.x = Res.Left - F_StartPoint.x;
  F_Ofs_Point.y = Res.Top - F_StartPoint.y;
  return Res;

}


//-----------------------------------------------------------------------------------
TRect TBaseWorkShape::FrameRectToRect(TRect R)
{
   TRect Res;
   Res = R;
   Res.Left = Res.Left + OFFS_FRAME*F_PenWidth;
   Res.Top = Res.Top + OFFS_FRAME*F_PenWidth;
   Res.Right = Res.Right - OFFS_FRAME*F_PenWidth;
   Res.Bottom = Res.Bottom - OFFS_FRAME*F_PenWidth;
   return Res;
}


//-------------------------------------------------------------------------------------
TPoint TBaseWorkShape::GetStartPointFromFrameRect(TRect R)
{
   TPoint Res;
   Res.x = R.Left - F_Ofs_Point.x ;
   Res.y = R.Top - F_Ofs_Point.y;
   return Res;
}

//-------------------------------------------------------------------------------------
int TBaseWorkShape::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}


//-------------------------------------------------------------------------------------
TRect TBaseWorkShape::GetMaxRect()
{
  TRect Res, R_tmp;
  TBaseShape *baseShape;
  TArrowLine *currLine;
  if (CompositeWorkShape)
    return CompositeWorkShape->GetMaxRect();
  baseShape = static_cast<TBaseShape*>(WorkShapes->Items[0]);
  Res = baseShape->GetRect();
  for (int i = 1 ; i <= WorkShapes->Count - 1 ;i++)
  {
    baseShape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
    R_tmp = baseShape->GetRect();
    if (R_tmp.Left < Res.Left )  Res.Left = R_tmp.Left;
    if (R_tmp.Right > Res.Right) Res.Right = R_tmp.Right;
    if (R_tmp.Top < Res.Top) Res.Top = R_tmp.Top;
    if (R_tmp.Bottom > Res.Bottom) Res.Bottom = R_tmp.Bottom;
  }


  for (int i = 0; i<=WorkLines->Count-1; i++)
  {
     currLine =(TArrowLine *)WorkLines->Items[i];
     if (currLine->xStart <  Res.Left) Res.Left = currLine->xStart;
     if (currLine->xEnd <  Res.Left) Res.Left = currLine->xEnd;
     if (currLine->xStart >  Res.Right) Res.Right = currLine->xStart;
     if (currLine->xEnd >  Res.Right) Res.Right = currLine->xEnd;

     if (currLine->yStart <  Res.Top) Res.Top = currLine->yStart;
     if (currLine->yEnd <  Res.Top) Res.Top = currLine->yEnd;
     if (currLine->yStart >  Res.Bottom) Res.Bottom = currLine->yStart;
     if (currLine->yEnd >  Res.Bottom) Res.Bottom = currLine->yEnd;

  }


  Res.Left = Res.Left - OFFS_FRAME*PenWidth;
  Res.Top = Res.Top - OFFS_FRAME*PenWidth;
  Res.Right = Res.Right + OFFS_FRAME*PenWidth;
  Res.Bottom = Res.Bottom + OFFS_FRAME*PenWidth;
  F_Ofs_Point.x = Res.Left - F_StartPoint.x;
  F_Ofs_Point.y = Res.Top - F_StartPoint.y;
  return Res;
}

//-----------------------------------------------------------------
void TBaseWorkShape::PaintFirstFlag()
{
   FirstLine->DrawFlagS = F_DrawFirstFlag;
   FirstLine->Prepare();
}

//--------------------------------------------------------
void  TBaseWorkShape::PaintLastFlag()
{
   LastLine->DrawFlagE = F_DrawLastFlag;
   LastLine->Prepare();
}


void  TBaseWorkShape::PaintMiddleFlag()
{
     if (MiddleLine)
     {
        MiddleLine->DrawFlag = F_DrawMiddleFlag;
        MiddleLine->Prepare();
     }
}



TRectLine* __fastcall TBaseWorkShape::GetFirstLine()
{
    if (f_CompositeWorkShape)
      return f_CompositeWorkShape->FirstLine;
    return NULL;
}

void __fastcall TBaseWorkShape::SetCompositeWorkShape(TCompositeBaseWork* ACWS)
{
     f_CompositeWorkShape = ACWS;
     if (f_CompositeWorkShape)
     {
        f_CompositeWorkShape->FirstLine->UnderControl = F_UnderControl;
        f_CompositeWorkShape->FirstLine->WndHandler = F_WndHandler;
        f_CompositeWorkShape->FirstLine->OnRctFlagCreate = &FlagCreate;
        f_CompositeWorkShape->FirstLine->OnRctFlagDestroy = &FlagDestroy;

     }
}


TRectLine* __fastcall TBaseWorkShape::GetLastLine()
{
    return NULL;
}

TRectLine* __fastcall TBaseWorkShape::GetMiddleLine()
{
    return NULL;
}


void TBaseWorkShape::DoSetLEControl()
{
  int i;
  TBaseShape *bs;
  TRectLine *line;
  for (i = 0; i <= WorkShapes->Count - 1; i++)
  {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     bs->LEControl = f_LEControl;
  }
  for (i = 0; i<= WorkLines->Count-1; i++)
  {
     line = static_cast<TRectLine *>(WorkLines->Items[i]);
     line->LEControl = f_LEControl;
  }
}


void TBaseWorkShape::DoSetWndHandler()
{
  int i;
  TBaseShape *bs;
  TRectLine *line;
  for (i = 0; i <= WorkShapes->Count - 1; i++)
  {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     bs->WndHandler = F_WndHandler;
  }
  for (i = 0; i<= WorkLines->Count-1; i++)
  {
     line = static_cast<TRectLine *>(WorkLines->Items[i]);
     line->WndHandler = F_WndHandler;
  }
}

void TBaseWorkShape::DoSetLEActive()
{
  int i;
  TBaseShape *bs;
  for (i = 0; i <= WorkShapes->Count - 1; i++)
  {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     bs->LEActive = f_LEActive;
  }
}



void __fastcall TBaseWorkShape::SetLEControl(bool Value)
{
  if (f_LEControl == Value) return;
  f_LEControl = Value;
  DoSetLEControl();
}

void __fastcall TBaseWorkShape::SetWndHandler(const HWND Value)
{
  if (F_WndHandler == Value) return;
  F_WndHandler = Value;
  DoSetWndHandler();
}

void __fastcall TBaseWorkShape::SetDrawFirstFlag(bool Value)
{
   if (F_DrawFirstFlag != Value)
   {
      F_DrawFirstFlag = Value;
   }
}

void __fastcall TBaseWorkShape::SetDrawLastFlag(bool Value)
{
  if (F_DrawLastFlag != Value)
  {
     F_DrawLastFlag = Value;
  }
}


void __fastcall TBaseWorkShape::SetDrawMiddleFlag(bool Value)
{
  if (F_DrawMiddleFlag != Value)
  {
     F_DrawMiddleFlag = Value;
  }
}


void __fastcall TBaseWorkShape::SetUnderControl(TControl* Value)
{
   if (F_UnderControl != Value)
   {
      F_UnderControl = Value;
      DoSetUnderCotrol();
   }
}


void TBaseWorkShape::DoSetUnderCotrol()
{
  int i;
  TBaseShape *bs;
  TRectLine *line;
  for (i = 0; i <= WorkShapes->Count - 1; i++)
  {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     bs->UnderControl = F_UnderControl;
  }
  for (i = 0; i<= WorkLines->Count-1; i++)
  {
     line = static_cast<TRectLine *>(WorkLines->Items[i]);
     line->UnderControl = F_UnderControl;
  }
}


void TBaseWorkShape::DoSetFlag()
{
  TRectLine *line = MiddleLine;
  if (line)
  {
     //line->FlagColor = F_FlagColor;
     line->FlagType = F_FlagType;
  }
}

void TBaseWorkShape::DoSetFlagS()
{
  TRectLine *line = FirstLine;
  if (line)
  {
     //line->FlagSColor = F_FlagSColor;
     line->FlagSType = F_FlagSType;
  }
}

void TBaseWorkShape::DoSetFlagE()
{
  TRectLine *line = LastLine;
  if (line)
  {
     //line->FlagEColor = F_FlagEColor;
     line->FlagEType = F_FlagEType;
  }
}


void TBaseWorkShape::PrepareLines()
{
  TRectLine *line;
  for (int i = 0; i<= WorkLines->Count-1; i++)
  {
     line = static_cast<TRectLine *>(WorkLines->Items[i]);
     line->OnRctFlagCreate = &FlagCreate;
     line->OnRctFlagDestroy = &FlagDestroy;
     line->Prepare();
  }
  if (WorkLines->Count > 0)
    if (FOnAfterLinePrepare) OnAfterLinePrepare(this);
}

bool TBaseWorkShape::KeepFlag(TBaseShape *Flag, int &type)
{
  TRectLine *line;
  for (int i = 0; i<= WorkLines->Count-1; i++)
  {
     line = static_cast<TRectLine *>(WorkLines->Items[i]);
     if (line->KeepFlag(Flag, type)) return true;
  }
  return false;
}

void __fastcall TBaseWorkShape::FlagCreate(TRectLine *ASender, TFlagShape *AFlag, int APosFlag)
{
   bool res;
   TBaseShape* Shape = GetShapeByLine(ASender, APosFlag);
   TFlag* Flag = ListFlag->AddFlag(AFlag, Shape, ASender, APosFlag, res);
   if ( !res && FOnWSFlagCreate) OnWSFlagCreate(Flag, this);

}


void __fastcall TBaseWorkShape::FlagDestroy(TRectLine *ASender, TFlagShape *AFlag, int APosFlag)
{
   TFlag* Flag = ListFlag->DeleteFlagByShape(AFlag);
   if ( Flag && FOnWSFlagDestroy) OnWSFlagDestroy(Flag, this);
}


TBaseShape* TBaseWorkShape::GetShapeByLine(TRectLine* ALine, int APos)
{
   return NULL;
}

bool TBaseWorkShape::MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor)
{
   return false;
}

void TBaseWorkShape::ShowAllFlagForSahpe(int AType, TColor AColor)
{
   TBaseShape* bs;
   for (int i = 0; i <= WorkShapes->Count - 1; i++)
   {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     MakeFlagForShape(bs, true, 0, AType, AColor);
     MakeFlagForShape(bs, true, 1, AType, AColor);
   }
}

void TBaseWorkShape::HideAllFlagForSahpe()
{
   TBaseShape* bs;
   for (int i = 0; i <= WorkShapes->Count - 1; i++)
   {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     MakeFlagForShape(bs, false, 0, 0, clBlack);
     MakeFlagForShape(bs, false, 1, 0, clBlack);
   }
}

int TBaseWorkShape::ShapeSupport(TBaseShape *AShape)
{
   TBaseShape* bs;
   for (int i = 0; i <= WorkShapes->Count - 1; i++)
   {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     if (bs == AShape) return bs->ID;
   }
   return -1;
}

TBaseShape*  TBaseWorkShape::ShapeSupportID(int AShapeID)
{
   TBaseShape* bs;
   for (int i = 0; i <= WorkShapes->Count - 1; i++)
   {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     if (bs->ID == AShapeID) return bs;
   }
   return NULL;
}

void TBaseWorkShape::CreateLines()
{
   //решить проблему
   return;

}


int TBaseWorkShape::ReactMouse(TPoint APoint)
{
   int res = 0;
   TBaseShape* bs;
   TFlag* fl;
   for (int i = 0; i <= WorkShapes->Count - 1; i++)
   {
     bs = static_cast<TBaseShape*>(WorkShapes->Items[i]);
     if ( bs->ReactMouse(APoint) ) res++;
   }
   for (int i = 0; i <= ListFlag->Count - 1; i++)
   {
     fl = ListFlag->Items[i];
     if ( fl->Flag->ReactMouse(APoint) ) res++;
   }
   return res;
}


TRectLine* __fastcall TBaseWorkShape::GetRectLineItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= WorkLines->Count - 1)
     return static_cast<TRectLine*>(WorkLines->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TBaseWorkShape::GetRectLineCount()
{
   return WorkLines->Count;
}


void __fastcall TBaseWorkShape::SetApplyAttribute(bool Value)
{
  TBaseShape* Shape;
  if ( f_ApplyAttribute != Value )
  {
    f_ApplyAttribute = Value;
    for (int i = 0 ; i <= WorkShapes->Count-1 ;i++)
    {
      Shape = static_cast<TBaseShape*>(WorkShapes->Items[i]);
      Shape->ApplyAttribute = f_ApplyAttribute;
    }
  }
}


int TBaseWorkShape::Bend(int t_x1, int t_x2)
{
    return CalcBend(t_x1, t_x2);
}


void __fastcall TBaseWorkShape::SetLEActive(bool AValue)
{
   if (f_LEActive != AValue)
   {
      f_LEActive = AValue;
      DoSetLEActive();
   }
}

int __fastcall TBaseWorkShape::GetOffsetXFromStart()
{
    return 2*F_Step;
}

int __fastcall TBaseWorkShape::CalcWidthWork()
{
   F_WidthWork = LastLine->xEnd - FirstLine->xEnd;
   return  F_WidthWork;
}

void __fastcall TBaseWorkShape::SetBaseLineColor(TColor AValue)
{
   TArrowLine *Line;
   f_BaseLineColor = AValue;
   for (int i = WorkLines->Count - 1; i >= 0; i--)
   {
      Line  =  static_cast<TArrowLine*>(WorkLines->Items[i]);
      Line->BaseLineColor = f_BaseLineColor;
   }
}


TPoint TBaseWorkShape::OffsetStartPoint()
{
   int m_x, m_y;
   m_x = BaseStartPoint.x - StartPoint.x;
   m_y = BaseStartPoint.y - StartPoint.y;
   return TPoint(m_x, m_y);
}

void TBaseWorkShape::TrimFirstLine(bool ATrimComposite, TPoint APStart, TPoint APEnd)
{
   int mX, mY;

   if (ATrimComposite && CompositeWorkShape)
   {
     CompositeWorkShape->TrimFirstLine(APStart, APEnd);
     return;
   }  


   TRectLine *RL = GetWorkLine(0);
   if (RL)
   {
     StartPoint = APStart;
     mX = RL->xEnd - APEnd.x ;
     mY = RL->yEnd - APEnd.y;
     this->SetOffsetPosition(-mX, -mY);
//     RL->SetCoord(PC.x - F_Step, PC.y, PC.x + F_Step, PC.y, 0);
//     RL->Prepare();

//     Prepare();

   }


}








