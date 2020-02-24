//--------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPaintgrids.h"              



//------------------------------------------------------------------------
#pragma package(smart_init)


//------------------------------------------------------------------------
TPaintGrid::TPaintGrid(TCanvas *ACanvas, HWND AOwnerForm)
{
   f_Width = f_Height = 0;
   f_StepPixels = 5;
   f_StepPixelsGrid = 8;
   f_FonColor = clWhite;
   f_PixelColor = clBlack;
   f_PaintPixels = true;
   f_Canvas = ACanvas;
   f_OwnerForm = AOwnerForm;
   f_LEControl = false;
   f_WndHandler = 0;
   f_UnderControl = NULL;
   f_RefreshFon = true;
   f_CurrEndPoint = TPoint(40, 100);
   f_X_offs = 0; //смещение по Х
   f_Y_offs = 0; //смещение по Y
   f_WSPenWidth = 1;
   f_X_offsSum = f_Y_offsSum = 0;
   f_LineColor = clBlack;
   f_BrushTFE = false;
   f_BrushColor = clWhite;
   f_LeaveFlagColor = clRed;
   f_EnterFlagColor = clLime;
   f_CurrentCommand = 0;
   f_FlagType = 0;
   f_TypMouseOperation = 0;
   f_SelectedTFE = NULL;
   f_SelectedTFS = NULL;
   f_FrameColorTFE = clRed;
   f_FrameColorTFS = clRed;
   f_WSMoving = false;
   f_SelectedFlag = NULL;
   f_Regim = 0;
   f_SelectedAlternateFirst = NULL; //первая выбранная ТФС для альтернативы
   f_SelectedAlternateLast = NULL; //первая выбранная ТФС для альтернативы
   f_SelectedDeleteTFSFirst = NULL; //первая выбранная ТФС для альтернативы
   f_SelectedDeleteTFSLast = NULL; //первая выбранная ТФС для альтернативы
   


   f_FontTFE = new Graphics::TFont;
   ScrBitmap = new Graphics::TBitmap;
   ScrBitmapCopy = new Graphics::TBitmap;
   f_ClipPath = new TClipPath;
   g_PainterList = new TPainterList;
   f_ListForPaint = new TListForPaint;
   f_FlagController = new TFlagController();
   f_InvalidateList = new TInvalidateList;
   f_LineCutting = new TLineCutting(f_Canvas);
   g_AlternateList = new TAlternateList;
   f_AltWSList = new TAltWSList;
   f_localVisiblearrowall = false;
}

//------------------------------------------------------------------------
TPaintGrid::~TPaintGrid()
{
   FreeBitmap();
   FreeBitmapCopy();
   delete  f_FontTFE;
   delete  f_ClipPath;
   delete  g_PainterList;
   delete  f_ListForPaint;
   delete  f_FlagController;
   delete  f_InvalidateList;
   delete  f_LineCutting;
   delete  g_AlternateList;
   delete  f_AltWSList;
}


//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetStepPixels(int Value)
{
   if  (Value < 5) Value = 5;
   if  (Value > 12 ) Value = 12;
   f_StepPixels = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetStepPixelsGrid(int Value)
{
   if  (Value < 5) Value = 5;
   if  (Value > 12 ) Value = 12;
   f_StepPixelsGrid = Value;
}


//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetPaintPixels(bool Value)
{
   if (f_PaintPixels != Value)
     f_PaintPixels = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetFonColor(TColor Value)
{
   if (f_FonColor != Value )
     f_FonColor = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetPixelColor(TColor Value)
{
   if (f_PixelColor != Value)
     f_PixelColor = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetLineColor(TColor Value)
{
   if (f_LineColor != Value)
     f_LineColor = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetBrushTFE(bool Value)
{
   if (f_BrushTFE != Value)
     f_BrushTFE = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetBrushColor(TColor Value)
{
   if (f_BrushColor != Value)
     f_BrushColor = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetFontTFE(Graphics::TFont* Value)
{
   f_FontTFE->Assign(Value);
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetFlagType(int Value)
{
   if ( f_FlagType != Value )
     if ( (Value >= 0) && (Value <= 2) )
       f_FlagType = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetFrameColorTFE(TColor Value)
{
   if (f_FrameColorTFE != Value)
     f_FrameColorTFE = Value;
}

//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetFrameColorTFS(TColor Value)
{
   if (f_FrameColorTFS != Value)
     f_FrameColorTFS = Value;
}


//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltFlagColor(TColor Value)
{
   if (f_AltFlagColor != Value)
   {
      f_AltFlagColor = Value;
   }
}


//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltEnterFlagColor(TColor Value)
{
   if (f_AltEnterFlagColor != Value)
   {
      f_AltEnterFlagColor = Value;
   }
}

//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltEnabledFlagColor(TColor Value)
{
   if (f_AltEnabledFlagColor != Value)
      f_AltEnabledFlagColor = Value;
}

//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltArrowColor(TColor Value)
{
   if (f_AltArrowColor != Value)
   {
      f_AltArrowColor = Value;
   }
}


//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltEnterArrowColor(TColor Value)
{
   if (f_AltEnterArrowColor != Value)
   {
      f_AltEnterArrowColor = Value;
   }
}


//---------------------------------------------------------------------------
void __fastcall TPaintGrid::SetAltLineColor(TColor Value)
{
   if (f_AltLineColor != Value)
   {
      f_AltLineColor = Value;
   }
}



//------------------------------------------------------------------------
void __fastcall TPaintGrid::SetTypMouseOperation(int Value)
{
   if (f_TypMouseOperation != Value)
   {
     f_TypMouseOperation = Value;
     switch (f_TypMouseOperation)
     {
       case 0:
         NilTFE();
         NilTFS();
         break;
       case 1:
         NilTFS();
         break;
       case 2:
         NilTFE();
         break;

     }
   }

}


//----------------------------------------------------------------------
void TPaintGrid::FreeBitmap()
{
  if ( ScrBitmap != NULL )
  {
    ScrBitmap->FreeImage();
    delete ScrBitmap;
    ScrBitmap = NULL;
  }
}

//----------------------------------------------------------------------
void TPaintGrid::FreeBitmapCopy()
{
  if ( ScrBitmapCopy != NULL )
  {
    ScrBitmapCopy->FreeImage();
    delete ScrBitmapCopy;
    ScrBitmapCopy = NULL;
  }
}


//------------------------------------------------------------------------
void TPaintGrid::CreateGrid(int Ax, int Ay)
{
   FreeBitmap();
   FreeBitmapCopy();
   CreateSrcBitmap(Ax, Ay);
   CreateSrcBitmapCopy(Ax, Ay);
   f_InvalidateList->Width = Ax;
   f_InvalidateList->Heigth = Ay;
   f_CurrentCommand = 2 ;
}

//---------------------------------------------------------------------
void TPaintGrid::CreateSrcBitmap(int Ax, int Ay)
{
  ScrBitmap = new Graphics::TBitmap;
  ScrBitmap->Width = Ax - 1;
  ScrBitmap->Height = Ay - 1;
}

//---------------------------------------------------------------------
void TPaintGrid::CreateSrcBitmapCopy(int Ax, int Ay)
{
  ScrBitmapCopy = new Graphics::TBitmap;
  ScrBitmapCopy->Width = Ax;
  ScrBitmapCopy->Height = Ay;
}


//---------------------------------------------------------------------
void TPaintGrid::PreparePaint()
{
  TBaseWorkShape *CurrShape;
  CurrShape = g_PainterList->First();
  while (CurrShape)
  {
     CurrShape->Prepare();
     CurrShape = g_PainterList->Next();
  }
  RecalcCurrEndPoint();
}



//---------------------------------------------------------------------
void TPaintGrid::DoPaint()
{
  int i;
  TBaseWorkShape *WP;
  TBaseShape *BS;
  TListForPaintItem *ItemPaint;

  if (f_RefreshFon)
     RepaintFon(f_X_offsSum, f_Y_offsSum);
  else
     CopyFon();


  if ( (f_ListForPaint->Count == 0) && (f_RefreshFon ||
    (f_CurrentCommand != 0) ) )
  {
    f_InvalidateList->Clear();
    WP = g_PainterList->First();
    while (WP)
    {
       f_InvalidateList->AddWorkShape(WP);
       if ( (WP == f_LineCutting->WorkShape) && (f_WSMovingCount == 0) ) continue;
       ApplyAttributeForWorkShape(WP);
       WP->Paint(ScrBitmap->Canvas);
       WP = g_PainterList->Next();
    }
  }

  if ( (f_ListForPaint->Count == 0) && (!f_RefreshFon && (f_CurrentCommand == 0) ) )
  {
    for (i = 0; i <= f_InvalidateList->Count - 1; i++)
    {
      WP =  f_InvalidateList->Items[i];
      if ( (WP == f_LineCutting->WorkShape) && (f_WSMovingCount == 0) ) continue;
      ApplyAttributeForWorkShape(WP);
      WP->Paint(ScrBitmap->Canvas);
    }
  }

  if (f_ListForPaint->Count > 0)
  {
     for (i = 0; i <= f_ListForPaint->Count - 1; i++)
     {
        ItemPaint = f_ListForPaint->Items[i];
        switch (ItemPaint->Type)
        {
           case 0:
             BS = static_cast<TBaseShape*>(ItemPaint->ClassPoint);
             BS->Paint(ScrBitmap->Canvas);
             break;
           case 1:
             WP = static_cast<TBaseWorkShape*>(ItemPaint->ClassPoint);
             ApplyAttributeForWorkShape(WP);
             if ( (WP == f_LineCutting->WorkShape) && (f_WSMovingCount == 0) ) continue;
             WP->Paint(ScrBitmap->Canvas);
             break;
        }
     }
     f_ListForPaint->Clear();
  }
  PaintAlternateList();
  f_RefreshFon = false;//f_Srolling;
  f_CurrentCommand = 0;
}


//---------------------------------------------------------------------
void TPaintGrid::CopyFon()
{
   int aX, aY;
   aX = ScrBitmapCopy->Width;
   aY = ScrBitmapCopy->Height;
   ScrBitmap->Canvas->CopyRect(Bounds(0,0, aX, aY), ScrBitmapCopy->Canvas, Bounds(0,0,aX, aY));
}


//---------------------------------------------------------------------
void TPaintGrid::RepaintFon(int  Ax, int Ay)
{
  int j,i, m_X, m_Y;
  int x_offs, y_offs;
  div_t th;
  m_X = ScrBitmap->Width;
  m_Y = ScrBitmap->Height;
  if ( abs(Ax) < f_StepPixelsGrid) x_offs = Ax;
  else
    {
      th = div(Ax, f_StepPixelsGrid);
      x_offs = th.rem;
    }
  if ( abs(Ay) < f_StepPixelsGrid) y_offs = Ay;
   else
   {
      th = div(Ay, f_StepPixelsGrid);
      y_offs = th.rem;
    }

  ScrBitmap->Canvas->Brush->Color = f_FonColor;
  ScrBitmap->Canvas->FillRect(TRect(0,0, m_X, m_Y));
  if (f_PaintPixels && (f_StepPixelsGrid > 0))
  {
    for (i = x_offs; i<=m_X + abs(x_offs); i = i + f_StepPixelsGrid )
    {
       for (j = y_offs; j<=m_Y + abs(y_offs); j = j + f_StepPixelsGrid)
              ScrBitmap->Canvas->Pixels[i][j] = f_PixelColor;
    }
  }
  ScrBitmapCopy->Canvas->CopyRect(Bounds(0, 0, m_X, m_Y), ScrBitmap->Canvas, Bounds(0,0, m_X, m_Y));
}


//------------------------------------------------------------------------
void TPaintGrid::Recreate(int AWidth,  int AHeight)
{
   CreateGrid(AWidth, AHeight);
   RepaintFon(f_X_offsSum, f_Y_offsSum);
   //DoPaint(0, 0);
}

//------------------------------------------------------------------------
void TPaintGrid::Paint()
{
   DoPaint();
   f_Canvas->Draw(0, 0, ScrBitmap);
}


//---------------------------------------------------------------------------------------------
TBaseWorkShape* TPaintGrid::AddWorkShape(int AType, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine)
{
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (AType > 0)
   {
      switch (AType)
      {
       case 1:
         m_CurrWorkShape = new TWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 2:
         m_CurrWorkShape = new TWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;

         //throw(Exception("Недопустимое выполнение (new TPWork). Обратитесь с этой ошибкой к разработчикам!")); //m_CurrWorkShape = new TPWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         //break;
       case 3:
         m_CurrWorkShape = new TZWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 4:
         m_CurrWorkShape = new TZWorkOR(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 5:
         m_CurrWorkShape = new TControlWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 6:
         m_CurrWorkShape = new TControlFunc(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 7:
         m_CurrWorkShape = new TBifurcation(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 8:
         m_CurrWorkShape = new TCheckConditionCW(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 9:
         m_CurrWorkShape = new TCycleWhileDo(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 10:
         m_CurrWorkShape = new TCycleDoWhileDo(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 11:
         m_CurrWorkShape = new TCycleDoWhileDoFC(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 12:
         m_CurrWorkShape = new TCheckCondition(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
      }


      m_CurrWorkShape->LEControl = f_LEControl;
      m_CurrWorkShape->WndHandler = f_WndHandler;
      m_CurrWorkShape->UnderControl = f_UnderControl;
      m_CurrWorkShape->OnWSFlagCreate = WsFlagCreate;
      m_CurrWorkShape->OnWSFlagDestroy = WsFlagDestroy;
      m_CurrWorkShape->BaseStartPoint.x+= -f_X_offsSum;
      m_CurrWorkShape->BaseStartPoint.y+= -f_Y_offsSum;
      m_CurrWorkShape->Init();
      m_CurrWorkShape->Prepare();
      f_CurrEndPoint = m_CurrWorkShape->EndPoint;

      f_CurrentCommand = 1;
   }
   return m_CurrWorkShape;
}

TBaseWorkShape* TPaintGrid::CreateTempWorkShape(int AType, TPoint AStart, int ANumberShapeId)
{
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (AType > 0)
   {
      switch (AType)
      {
       case 1:
         m_CurrWorkShape = new TWork(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 2:
         m_CurrWorkShape = new TZWork(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 3:
         m_CurrWorkShape = new TZWorkOR(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 4:
         m_CurrWorkShape = new TControlWork(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 5:
         m_CurrWorkShape = new TControlFunc(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 6:
         m_CurrWorkShape = new TBifurcation(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 7:
         m_CurrWorkShape = new TCheckConditionCW(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 8:
         m_CurrWorkShape = new TCycleWhileDo(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 9:
         m_CurrWorkShape = new TCycleDoWhileDo(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 10:
         m_CurrWorkShape = new TCycleDoWhileDoFC(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
       case 11:
         m_CurrWorkShape = new TCheckCondition(AStart.x, AStart.y, f_StepPixels, ANumberShapeId, 0, 0);
         break;
      }
   }
   return m_CurrWorkShape;
}



TBaseWorkShape* TPaintGrid::InsertWorkShape(int AType, TBaseWorkShape* AWBefore,
       int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine)
{
   TPoint P;
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (!AWBefore) return AddWorkShape(AType, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
   P = AWBefore->StartPoint;
   if (AType > 0)
   {
      switch (AType)
      {
       case 1:
         m_CurrWorkShape = new TWork(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 2:
         m_CurrWorkShape = new TWork(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;

         //throw(Exception("Недопустимое выполнение (new TPWork). Обратитесь с этой ошибкой к разработчикам!"));//  m_CurrWorkShape = new TPWork(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         //break;
       case 3:
         m_CurrWorkShape = new TZWork(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 4:
         m_CurrWorkShape = new TZWorkOR(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 5:
         m_CurrWorkShape = new TControlWork(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 6:
         m_CurrWorkShape = new TControlFunc(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 7:
         m_CurrWorkShape = new TBifurcation(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 8:
         m_CurrWorkShape = new TCheckConditionCW(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 9:
         m_CurrWorkShape = new TCycleWhileDo(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 10:
         m_CurrWorkShape = new TCycleDoWhileDo(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 11:
         m_CurrWorkShape = new TCycleDoWhileDoFC(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 12:
         m_CurrWorkShape = new TCheckCondition(P.x, P.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
      }


      m_CurrWorkShape->LEControl = f_LEControl;
      m_CurrWorkShape->WndHandler = f_WndHandler;
      m_CurrWorkShape->UnderControl = f_UnderControl;
      m_CurrWorkShape->OnWSFlagCreate = WsFlagCreate;
      m_CurrWorkShape->OnWSFlagDestroy = WsFlagDestroy;
      m_CurrWorkShape->BaseStartPoint.x+= -f_X_offsSum;
      m_CurrWorkShape->BaseStartPoint.y+= -f_Y_offsSum;

      m_CurrWorkShape->Init();
      m_CurrWorkShape->Prepare();
      RecalcFollowWorkShape(AWBefore, m_CurrWorkShape);
      f_CurrentCommand = 1;
   }
   return m_CurrWorkShape;
}


//------------------------------------------------------------------------
HRGN TPaintGrid::GetRegion(TBaseWorkShape* WS, int AOfs)
{
    HRGN Res = 0;
    if (WS)
    {
      f_ClipPath->Clear();
      f_ClipPath->Add(WS->GetFrameRectWithLines(), AOfs);
      Res = f_ClipPath->GetCliptRgn();
    }
    return Res;
}


//------------------------------------------------------------------------
void TPaintGrid::ApplyAttributeForWorkShape(TBaseWorkShape* WS) // применяет аттрибуты для ТФС
{
   WS->PenWidth = f_WSPenWidth;
   WS->LineWidth = f_WSPenWidth;
   WS->PenColor = f_LineColor;
   WS->BaseLineColor = f_LineColor;
   if ( f_BrushTFE )
     WS->BrushStyle = bsSolid;
   else
     WS->BrushStyle = bsClear;
   WS->BrushColor = f_BrushColor;
   WS->Font =  f_FontTFE;
   WS->FlagSType = f_FlagType;
   WS->FlagEType = f_FlagType;
   WS->FrameColorTFE = f_FrameColorTFE;
   WS->FrameColor = f_FrameColorTFS;
   if (WS->CompositeWorkShape)
   {
     WS->CompositeWorkShape->SetColorAll(f_LineColor);
     WS->CompositeWorkShape->SetBrushColorAll(f_BrushColor);
     WS->CompositeWorkShape->SetBrushStyleAll(WS->BrushStyle);
   }
   if ( f_AltWSList->Find(WS) )
   {
     WS->PenColor = f_AltLineColor;
     if (WS->CompositeWorkShape)
       WS->CompositeWorkShape->SetColorAll(f_AltLineColor);
   }
   ApplyAttributeForCompositeWorkShape(WS);
}


void TPaintGrid::ApplyAttributeForCompositeWorkShape(TBaseWorkShape* WS)
{
   if (WS->CompositeWorkShape)
   {
      WS->CompositeWorkShape->FirstLine->FlagSType  = WS->FlagSType;
      WS->CompositeWorkShape->FirstLine->FlagEType  = WS->FlagEType;

   }

}

//------------------------------------------------------------------------
TPoint TPaintGrid::GetPointPolygon(int AXoffs, int AYoffs)
{
   TPoint res = TPoint(0,0);
   TRect temp = TRect(0,0,0,0);
   TBaseWorkShape *TempWork;

   TempWork = g_PainterList->First();
   while (TempWork)
   {
     temp = TempWork->GetMaxRect();
     if (temp.Right > res.x) res.x = temp.Right;
     if (temp.Bottom > res.y ) res.y  = temp.Bottom;
     TempWork = g_PainterList->Next();
   }
   res.x = res.x + AXoffs;
   res.y = res.y + AYoffs;
   return res;
}

//------------------------------------------------------------------------
TPoint TPaintGrid::GetTopPoint(int AXoffs, int AYoffs)
{
   TPoint res = TPoint(MaxInt,MaxInt);
   TRect temp = TRect(0,0,0,0);
   TBaseWorkShape *TempWork;

   TempWork = g_PainterList->First();
   while (TempWork)
   {
     temp = TempWork->GetMaxRect();
     if (temp.Left < res.x) res.x = temp.Left;
     if (temp.Top <  res.y ) res.y  = temp.Top;
     TempWork = g_PainterList->Next();
   }
   res.x = res.x + AXoffs;
   res.y = res.y + AYoffs;
   return res;
}



//------------------------------------------------------------------------
void TPaintGrid::ApplyOffset(int AX, int AY)
{
    TBaseWorkShape *TempWork;
    TAlternateItem *Item;
    TPoint P;
    if ( (AX <= 0) != (f_X_offs <= 0) )
       f_X_offs = AX;
    else
       f_X_offs += AX;

    if ( (AY <= 0) != (f_Y_offs <= 0) )
       f_Y_offs = AY;
    else
       f_Y_offs += AY;

    f_X_offsSum+= AX;
    f_Y_offsSum+= AY;

    TempWork = g_PainterList->First();
    while(TempWork)
    {
      P = TempWork->StartPoint;
      P.x += AX;
      P.y += AY;
      TempWork->StartPoint = P;
      TempWork->SetOffsetPosition(AX, AY);
      TempWork->Prepare();//01.10.2006

      TempWork = g_PainterList->Next();
    }

   Item = g_AlternateList->First();
   while (Item)
   {
      P = Item->ArrowWorkShape->StartPoint;
      P.x += AX;
      P.y += AY;
      Item->ArrowWorkShape->StartPoint = P;
      Item->ArrowWorkShape->SetOffsetPosition(AX, AY);
      Item = g_AlternateList->Next();
   }

    f_RefreshFon = true;
}


//------------------------------------------------------------------------
void TPaintGrid::RecalcCurrEndPoint()
{
   TBaseWorkShape *TempWork;
   TempWork = g_PainterList->Last();
   if (TempWork)
     f_CurrEndPoint = TempWork->EndPoint;

}

//------------------------------------------------------------------------
int TPaintGrid::ApplyVisibleFlag(int APosition, bool AVisible) //показать флажки по всем ТФС по заданной позиции
{
   int res = 0;
   if ( (APosition > 2) || (APosition < 0)) return res;
   TBaseWorkShape* TempWork, *LWork;
   f_ClipPath->Clear();
   LWork = g_PainterList->Last();
   TempWork = g_PainterList->First();
   while(TempWork)
   {
     switch (APosition)
     {
       case 0:
         TempWork->DrawFirstFlag = AVisible;
         break;
       case 1:
         TempWork->DrawMiddleFlag = AVisible;
         break;
       case 2:
         TempWork->DrawLastFlag = AVisible;
         break;
     }
     if ( (LWork == TempWork) || !AVisible) //вставка в конец
         TempWork->DrawLastFlag = AVisible;
        
     f_ClipPath->Add(TempWork->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);

     TempWork = g_PainterList->Next();
     res++;
   }
   SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
   return res;
}

//------------------------------------------------------------------------
int TPaintGrid::ApplyVisibleFlagForAlternative(bool AVisible)
{
   TBaseWorkShape *TempWork, *WE;
   int res = 0;
   f_ClipPath->Clear();
   WE = g_PainterList->Last();
   TempWork = g_PainterList->First();
   while(TempWork)
   {
     if (TempWork == WE)
     {
       TempWork->DrawFirstFlag = AVisible;
       TempWork->DrawLastFlag = AVisible;
       f_ClipPath->Add(TempWork->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);
       TempWork = g_PainterList->Next();
       res++;
     }
     else
     {
       TempWork->DrawFirstFlag = AVisible;
       f_ClipPath->Add(TempWork->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);
       TempWork = g_PainterList->Next();
       res++;
     }
   }
   if (res)
     SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
   return res;
}

//------------------------------------------------------------------------
int TPaintGrid::ApplyVisibleFlagForDeleteTFS(bool AVisible)
{
   TBaseWorkShape *TempWork, *WE;
   int res = 0;
   f_ClipPath->Clear();
   WE = g_PainterList->Last();
   TempWork = g_PainterList->First();
   while(TempWork)
   {
     if (TempWork == WE)
     {
       TempWork->DrawFirstFlag = AVisible;
       TempWork->DrawLastFlag = AVisible;
       f_ClipPath->Add(TempWork->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);
       TempWork = g_PainterList->Next();
       res++;
     }
     else
     {
       TempWork->DrawFirstFlag = AVisible;
       if (!AVisible && TempWork->DrawLastFlag)
         TempWork->DrawLastFlag = AVisible;
       f_ClipPath->Add(TempWork->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);
       TempWork = g_PainterList->Next();
       res++;
     }
   }
   if (res)
     SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
   return res;
}


//------------------------------------------------------------------------
void __fastcall TPaintGrid::WsFlagCreate(TFlag* AFlag, TBaseWorkShape *WS)
{
   if (Regim == 2)
     f_FlagController->AddFlag(AFlag, f_AltEnterFlagColor, f_AltFlagColor, WS);
   else
     f_FlagController->AddFlag(AFlag, f_EnterFlagColor, f_LeaveFlagColor, WS);
}


//------------------------------------------------------------------------
void __fastcall TPaintGrid::WsFlagDestroy(TFlag* AFlag, TBaseWorkShape *WS)
{
   f_FlagController->DeleteFlag(AFlag);
}


//------------------------------------------------------------------------
void TPaintGrid::ReapintFlag(bool AEnter, TBaseShape* AFlag)
{
   bool res = false;
   if (AEnter)
   {
      if (AFlag->TypeShape == 100)
      {
        res = f_FlagController->EnterByShape((TFlagShape*)AFlag);
        f_SelectedFlag = (TFlagShape*)AFlag;
      }
      if (AFlag->TypeShape == 80)
        res = g_AlternateList->EnterByShape(AFlag);

   }
   else
   {
      if (AFlag->TypeShape == 100)
      {
        res = f_FlagController->LeaveByShape((TFlagShape*)AFlag);
        if (f_SelectedFlag == (TFlagShape*)AFlag)
          f_SelectedFlag = NULL;
      }
      if (AFlag->TypeShape == 80)
        res = g_AlternateList->LeaveByShape(AFlag);

   }
   if (res)
   {
     f_ClipPath->Clear();
     f_ClipPath->Add(AFlag->GetFrameRect(), C_DEFAULTCLIPOFS);
     PostMessage(f_OwnerForm, WM_GD_PAINTONEPREPARE, 1, LPARAM(f_ClipPath->GetCliptRgn()));
   }
}

//------------------------------------------------------------------------
void TPaintGrid::ReactMouse(TPoint APoint)
{
   TBaseWorkShape* TempWork;
   TempWork = g_PainterList->First();
   while(TempWork)
   {
      TempWork->ReactMouse(APoint);
      TempWork = g_PainterList->Next();
   }
   TAlternateItem* Item;
   Item = g_AlternateList->First();
   while(Item)
   {
      Item->ArrowWorkShape->ReactMouse(APoint);
      Item = g_AlternateList->Next();
   }

}


void __fastcall TPaintGrid::SetEnterFlagColor(TColor Value)
{
   if (f_EnterFlagColor != Value)
   {
      f_EnterFlagColor = Value;
      f_FlagController->ApplyEnterColor(f_EnterFlagColor);
   }
}


void __fastcall TPaintGrid::SetLeaveFlagColor(TColor Value)
{
   if (f_LeaveFlagColor != Value)
   {
      f_LeaveFlagColor = Value;
      f_FlagController->ApplyLeaveColor(f_LeaveFlagColor);
   }

}

//---------------------------------------------------------------------------
TBaseShape* TPaintGrid::FindTFE(int Ax, int Ay)
{
  TBaseShape * CurrShape;
  TBaseWorkShape *TempWork;
  TempWork = g_PainterList->First();
  while(TempWork)
  {
     if (TempWork->CompositeWorkShape)
     {
        CurrShape = TempWork->CompositeWorkShape->FindTFE(Ax, Ay);
        if (CurrShape)
          return CurrShape;
     }
     else
     {
       for (int i = 0; i <= TempWork->WorkShapesCount - 1; i++ )
       {
          CurrShape =static_cast<TBaseShape*>(TempWork->GetWorkShape(i));
          if (PtInRect(&CurrShape->GetRect(), TPoint(Ax, Ay)))
            return CurrShape;
       }
     }
     TempWork = g_PainterList->Next();
  }
  return NULL;
}


//-----------------------------------------------------------------------------
TBaseWorkShape* TPaintGrid::FindTFS(int Ax, int Ay)
{
  TBaseShape * CurrShape;
  TBaseWorkShape *TempWork;
  TempWork = g_PainterList->First();
  while(TempWork)
  {
     if (TempWork->CompositeWorkShape)
     {
        if (TempWork->CompositeWorkShape->FindTFE(Ax, Ay))
          return TempWork;
     }
     else
     {

       for (int i = 0; i <= TempWork->WorkShapesCount - 1; i++ )
       {
          CurrShape =static_cast<TBaseShape*>(TempWork->GetWorkShape(i));
          if (PtInRect(&CurrShape->GetRect(), TPoint(Ax, Ay)))
            return TempWork;
       }
     }
     TempWork = g_PainterList->Next();
  }
  return NULL;
}



//-----------------------------------------------------------------------------
bool TPaintGrid::SelectTFE(int Ax, int Ay)
{
   bool res;
   TBaseShape* mTFE = FindTFE(Ax, Ay);
   res = ( mTFE && (f_SelectedTFE != mTFE) );
   if ( res )
   {
      f_ClipPath->Clear();
      if (f_SelectedTFE)
      {
        f_SelectedTFE->DrawFrame = false;
        f_ClipPath->Add(f_SelectedTFE->GetFrameRect(), 4);
      }
      f_SelectedTFE = mTFE;
      f_SelectedTFE->DrawFrame = true;
      f_ClipPath->Add(f_SelectedTFE->GetFrameRect(), 4);
      SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
     // Application->ProcessMessages();
   }
   return res;
}


//-----------------------------------------------------------------------------
bool TPaintGrid::SelectTFS(int Ax, int Ay)
{
   bool res;
   TBaseWorkShape* mTFS = FindTFS(Ax, Ay);
   res = ( mTFS && (f_SelectedTFS != mTFS) );
   if ( res )
   {
      f_ClipPath->Clear();
      if (f_SelectedTFS)
      {
        f_SelectedTFS->DrawFrame = false;
        f_ClipPath->Add(f_SelectedTFS->GetFrameRectWithLines(), 4);
      }
      f_SelectedTFS = mTFS;
      f_SelectedTFS->DrawFrame = true;
      f_ClipPath->Add(f_SelectedTFS->GetFrameRectWithLines(), 4);
      SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
      //Application->ProcessMessages();
   }
   return res;

}

void TPaintGrid::RecalcBaseOffsetPosition()
{
  TBaseWorkShape *TempWork;
  TPoint PS;
  int m_idnx, m_idny;
  TempWork = g_PainterList->First();
  while(TempWork)
  {
     PS = TempWork->StartPoint;
     m_idnx = PS.x -   f_X_offsSum;
     m_idny = PS.y -   f_Y_offsSum;
     TempWork->BaseStartPoint = TPoint(m_idnx, m_idny);
     m_idnx = TempWork->FirstLine->xEnd - TempWork->Indent - PS.x;
     m_idny =  TempWork->FirstLine->yEnd - PS.y ;
     TempWork->SetBaseOffsetPosition(m_idnx, m_idny);
     TempWork = g_PainterList->Next();
  }
}




void TPaintGrid::MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   int m_x, m_y;
   TBaseWorkShape *W;
   TPoint PO;
   if (f_WSMoving && (f_TypMouseOperation == 2) )
   {
      f_LineCutting->EndMoving(m_x, m_y);
      f_LineCutting->WorkShape = NULL;
      f_SelectedTFS->SetOffsetPosition(m_x, m_y);
//      f_SelectedTFS->SetBaseOffsetPosition(m_x, m_y);
//      f_dln_x = (f_SelectedTFS->FirstLine->xEnd - f_SelectedTFS->FirstLine->xStart);
//      f_dln_y = (f_SelectedTFS->FirstLine->yEnd - f_SelectedTFS->FirstLine->yStart);
     if(f_SelectedTFS->CompositeWorkShape && !f_LineCutting->IsFirstWS)
     {
         PO = f_SelectedTFS->GetStartPointOneComposite();
         f_SelectedTFS->CompositeWorkShape->MakeFirstLine(PO, f_SelectedTFS->Bend(PO.x, f_SelectedTFS->FirstLine->xEnd));
     }
     else
        f_SelectedTFS->Prepare();
      f_WSMoving = false;

      W = FindNextWorkShape(f_SelectedTFS);
      if (f_LineCutting->IsFirstWS)
      {
        PO = TPoint(f_SelectedTFS->StartPoint.x + m_x, f_SelectedTFS->StartPoint.y + m_y);
        f_SelectedTFS->StartPoint = PO;
//        f_SelectedTFS->BaseStartPoint.x = f_SelectedTFS->BaseStartPoint.x + m_x;
//        f_SelectedTFS->BaseStartPoint.y = f_SelectedTFS->BaseStartPoint.y + m_y;
        f_SelectedTFS->Prepare();
        if ( !f_LineCutting->IsLastWS )
        {
           if (W)
           {
              W->StartPoint = f_SelectedTFS->EndPoint;
              if(W->CompositeWorkShape )
              {
                PO = W->GetStartPointOneComposite();
                W->CompositeWorkShape->MakeFirstLine(PO, W->Bend(PO.x, W->FirstLine->xEnd));
              }

//              W->BaseStartPoint.x =  f_SelectedTFS->BaseStartPoint.x
//                +  f_SelectedTFS->WidthWork + f_dln_x;
//              W->BaseStartPoint.y =  f_SelectedTFS->BaseStartPoint.y + f_dln_y;
           }
        }
      }
      else
      {
        if (W)
        {
          PO = TPoint(f_SelectedTFS->EndPoint.x, f_SelectedTFS->EndPoint.y);
          W->StartPoint = PO;
              if(W->CompositeWorkShape )
              {
                PO = W->GetStartPointOneComposite();
                W->CompositeWorkShape->MakeFirstLine(PO, W->Bend(PO.x, W->FirstLine->xEnd));
              }

//          W->BaseStartPoint.x =  f_SelectedTFS->BaseStartPoint.x
//            + m_x + f_SelectedTFS->WidthWork + f_dln_x;
//          W->BaseStartPoint.y =  f_SelectedTFS->BaseStartPoint.y
//            + m_y + f_dln_y ;
          W->Prepare();
        }
      }
//      RecalcAfterConverted(false, TPoint(40, 100));
      RecalcBaseOffsetPosition();
      SendMessage(f_OwnerForm, WM_GD_PAINT, 0, 0);

      if (f_LineCutting->IsLastWS)
        PostMessage(f_OwnerForm, WM_GD_SETNEWPOLYGON, 1, 1);
      else
        PostMessage(f_OwnerForm, WM_GD_SETNEWPOLYGON, 1, 0);

//      PostMessage(f_OwnerForm, WM_GD_RECALC, 1, 0);
   }
   if (f_localVisiblearrowall)
   {
     SendMessage(f_OwnerForm, WM_GD_VISIBLEARROWALL, 1, 1);
     f_localVisiblearrowall = false;
   }
   //TypMouseOperation = 0;

   if (f_Regim == 1)
   {                                                //f_FlagController->FindByFlagShape(AFlag)->Signal->Position
      if (f_SelectedFlag)
      {
        int m_pos = 0;
        TFlagControllerItem* CI = f_FlagController->FindByFlagShape(f_SelectedFlag);
        if (CI)
          m_pos = CI->Signal->Position;
        PostMessage(f_OwnerForm, WM_GD_INSERTWORKSHAPE, WPARAM(m_pos),
          LPARAM(f_FlagController->FindWorkShape(f_SelectedFlag)));
      }
   }
   if (f_Regim == 2)// создание альтернатив
   {
     if ( CreateAternative(f_SelectedFlag) )
       PostMessage(f_OwnerForm, WM_GD_SETALTERNATE, WPARAM(f_SelectedAlternateFirst),
         LPARAM(f_SelectedAlternateLast));
   }
   if (f_Regim == 4)// создание списка для удаления ТФС
   {
     if ( CreateDeleteTFSList(f_SelectedFlag) )
       PostMessage(f_OwnerForm, WM_GD_DELETETFSLIST, WPARAM(f_SelectedDeleteTFSFirst),
         LPARAM(f_SelectedDeleteTFSLast));
   }
   if (f_Regim == 5)//вставка ТФС из файла
   {
      if (f_SelectedFlag)
      {
        int m_pos = 0;
        TFlagControllerItem* CI = f_FlagController->FindByFlagShape(f_SelectedFlag);
        if (CI)
          m_pos = CI->Signal->Position;
        PostMessage(f_OwnerForm, WM_GD_INSERTWORKSHAPEFROMFILE, WPARAM(m_pos),
          LPARAM(f_FlagController->FindWorkShape(f_SelectedFlag)));
      }
   }
   if (f_Regim == 6)// создание списка для копирования ТФС
   {
     if ( CreateDeleteTFSList(f_SelectedFlag) )
       PostMessage(f_OwnerForm, WM_GD_COPYTFSLIST, WPARAM(f_SelectedDeleteTFSFirst),
         LPARAM(f_SelectedDeleteTFSLast));
   }
   if (f_Regim == 7)//вставка ТФС из буфера
   {
      if (f_SelectedFlag)
      {
        int m_pos = 0;
        TFlagControllerItem* CI = f_FlagController->FindByFlagShape(f_SelectedFlag);
        if (CI)
          m_pos = CI->Signal->Position;
        PostMessage(f_OwnerForm, WM_GD_INSERTWORKSHAPEFROMCANAL, WPARAM(m_pos),
          LPARAM(f_FlagController->FindWorkShape(f_SelectedFlag)));
      }
   }


}


void TPaintGrid::MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   if (f_TypMouseOperation == 2)
   {
     if (Shift.Contains(ssShift) && Shift.Contains(ssLeft) )
     {
        f_LineCutting->Moving(X, Y);
        ++f_WSMovingCount;
     }
   }
}



//-----------------------------------------------------------------------------
void TPaintGrid::MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TShiftState St1, St2, St3, St4;
   St1 << ssCtrl << ssLeft;
   St3 << ssLeft;
   St2 << ssShift  << ssLeft;
   St4 << ssRight;

   if ( ((Shift == St3) || (Shift == St4)) && ( (Button == mbLeft) || (Button == mbRight) ) )
   {
      TypMouseOperation = 0;
      if ( SelectTFE(X, Y) )
        TypMouseOperation = 1;   //перемещение ТФЕ
      return;
   }

   if ( ( (Shift == St1) || (Shift == St2) /*|| (Shift == St3)*/ )
       && (( Button == mbLeft) /*|| ( Button == mbRight)*/) )
   {

      TypMouseOperation = 0;
      if ( SelectTFS(X, Y) )
      {
        SendMessage(f_OwnerForm, WM_GD_VISIBLEARROWALL, 0, 0);
        f_localVisiblearrowall = true;
        TypMouseOperation = 2;  //перемещение ТФС
        if ((!f_WSMoving) && (Shift == St2 ))
        {
          Application->ProcessMessages();
          f_LineCutting->WorkShape = f_SelectedTFS;
          f_LineCutting->NextWorkShape = FindNextWorkShape(f_SelectedTFS);
          f_LineCutting->IsFirstWS = f_SelectedTFS == g_PainterList->First();
          f_LineCutting->IsLastWS = f_SelectedTFS == g_PainterList->Last();
         

          f_WSMoving = true;
          f_WSMovingCount = 0;
          f_ClipPath->Clear();
          f_ClipPath->Add(f_SelectedTFS->GetFrameRectWithLines(), 4);
          if (f_LineCutting->NextWorkShape)
            f_ClipPath->Add(f_LineCutting->NextWorkShape->GetFrameRectWithLines(), 4);
          SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
          Application->ProcessMessages();
          f_LineCutting->BeginMoving(X, Y);
        }
      }
      return;
   }
}

//-----------------------------------------------------------------------------
void TPaintGrid::NilTFE()
{
  if (f_SelectedTFE)
  {
     if (f_SelectedTFE->DrawFrame)
     {
        f_SelectedTFE->DrawFrame = false;
        f_ClipPath->Clear();
        f_ClipPath->Add(f_SelectedTFE->GetFrameRect(), 4);
        SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
     }
     f_SelectedTFE = NULL;
  }
}


//-----------------------------------------------------------------------------
void TPaintGrid::NilTFS()
{
  if (f_SelectedTFS)
  {
     if (f_SelectedTFS->DrawFrame)
     {
        f_SelectedTFS->DrawFrame = false;
        f_ClipPath->Clear();
        f_ClipPath->Add(f_SelectedTFS->GetFrameRectWithLines(), 4);
        SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
     }
     f_SelectedTFS = NULL;
  }
}


TBaseWorkShape* TPaintGrid::FindNextWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETNEXTWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}

TBaseWorkShape* TPaintGrid::FindPriorWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETPRIORWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}

int TPaintGrid::GetMainTabCount()
{
   int Res;
   SendMessage(f_OwnerForm, WM_GD_GETMAINTABCOUNT, 0, LPARAM(&Res));
   return Res;
}



TBaseWorkShape* __fastcall TPaintGrid::GetFirstWorkShape()
{
   return g_PainterList->First();
}

TBaseWorkShape* __fastcall TPaintGrid::GetLastWorkShape()
{
   return g_PainterList->Last();
}




//----------------------------------------------------------------------------------------
void TPaintGrid::RecalcFollowWorkShape(TBaseWorkShape* ABeforeInsertWork,  TBaseWorkShape* AInsertWork)
{
  TBaseWorkShape *TempWork;
  TPoint P1, P2, PS;
  int X_ofs = 0;
  TempWork = g_PainterList->First();
  while( TempWork )
  {
    if(TempWork == ABeforeInsertWork)
    {
      P1 = AInsertWork->StartPoint;
      P2 = AInsertWork->EndPoint;
      X_ofs = P2.x - P1.x;
    }
    PS = TempWork->StartPoint;
    PS.x = PS.x + X_ofs;
    TempWork->StartPoint = PS;
    TempWork->SetOffsetPosition(X_ofs, 0);
    TempWork = g_PainterList->Next();
  }
}


//----------------------------------------------------------------------------------------
void TPaintGrid::RecalcFollowWorkShape(TBaseWorkShape* ABeforeInsertWork,  TPoint AEndPoint)
{
  TBaseWorkShape *TempWork;
  TPoint PS;
  int X_ofs = 0;
  int Y_ofs = 0;
  bool b_base = false;
  TempWork = g_PainterList->First();
  while( TempWork )
  {
    if(TempWork == ABeforeInsertWork)
    {
      X_ofs = AEndPoint.x - ABeforeInsertWork->StartPoint.x;
      Y_ofs = AEndPoint.y - ABeforeInsertWork->StartPoint.y;
      b_base = true;
    }
    PS = TempWork->StartPoint;
    PS = PointAdd(PS, X_ofs, Y_ofs);
    TempWork->StartPoint = PS;
    TempWork->SetOffsetPosition(X_ofs, Y_ofs);
    if (b_base)
    {
      TempWork->BaseStartPoint.x += X_ofs;
      TempWork->BaseStartPoint.y += Y_ofs;
      //TempWork->SetBaseOffsetPosition(X_ofs, Y_ofs);
    }
    TempWork = g_PainterList->Next();
  }
}

void TPaintGrid::RecalcAfterDeleted(bool AFirst, TPoint FPoint)
{
  TBaseWorkShape *WS, *WN;
  TPoint P1, P2;
  int X_ofs;
  bool m_find = false;
  WS = g_PainterList->First();
  if (!WS) return;

  P1 = WS->StartPoint;


 if (AFirst)
  {
    WN = CreateTempWorkShape(WS->TypeShape, FPoint);
    WN->Init();
    WN->Prepare();
    WS->TrimFirstLine(true, WN->FirstLine->PointStart, WN->FirstLine->PointEnd);
    if (WS->CompositeWorkShape)
      WS->CompositeWorkShape->MakeFirstLine(WS->FirstLine->PointStart,WS->Bend(WS->FirstLine->xStart, WS->FirstLine->xEnd));
    delete WN;
  }
//  if (AFirst)
//    P2 = TPoint(FPoint.x + f_X_offsSum, FPoint.y + f_Y_offsSum);
  else
  {
    P2 = TPoint(WS->BaseStartPoint.x + f_X_offsSum, WS->BaseStartPoint.y + f_Y_offsSum);
  if( (P2.x != P1.x) || (P2.y != P1.y)  )
  {
     X_ofs = P2.x - P1.x;
     WS->StartPoint = P2;
     WS->SetOffsetPosition(X_ofs, 0);
     WS->Prepare();

  }
  }
  X_ofs = 0;
  WS = g_PainterList->First();
  while( WS )
  {
    WN = FindNextWorkShape(WS);
    if (!WN) return;
    P1 = WN->StartPoint;
    P2 = WS->EndPoint;
    if( (!m_find) && ( (P2.x != P1.x) || (P2.y != P1.y) ) )
    {
        X_ofs = P2.x - WN->FirstLine->xEnd + WN->OffsetXFromStart;
        m_find = true;
        WN->StartPoint = WS->EndPoint;
        WN->SetOffsetPosition(X_ofs, 0);
        WN->Prepare();
        WS = g_PainterList->Next();
        continue;
    }
    P1 = WN->StartPoint;
    P2 = PointAdd(P1, X_ofs, 0);
    WN->StartPoint = P2;
    WN->SetOffsetPosition(X_ofs, 0);
    WS = g_PainterList->Next();
  }
}


void TPaintGrid::PrepareLevel()
{
   f_CurrEndPoint = TPoint(40, 100);
   f_X_offs = 0; //смещение по Х
   f_Y_offs = 0; //смещение по Y
   f_X_offsSum = f_Y_offsSum = 0;
   f_CurrentCommand = 0;
   TypMouseOperation = 0;
   f_SelectedTFE = NULL;
   f_SelectedTFS = NULL;
   f_WSMoving = false;
   f_SelectedFlag = NULL;
   f_Regim = 0;
   f_RefreshFon = true;
}

void TPaintGrid::PrepareLevelOnOffset()
{
   f_CurrentCommand = 0;
   TypMouseOperation = 0;
   f_SelectedTFE = NULL;
   f_SelectedTFS = NULL;
   f_WSMoving = false;
   f_SelectedFlag = NULL;
   f_Regim = 0;
   f_RefreshFon = true;
}



void TPaintGrid::PaintAlternateList()
{
   TAlternateItem* Item;
   Item = g_AlternateList->First();
   while (Item)
   {
     if (Item->Visible)
       Item->ArrowWorkShape->Paint(ScrBitmap->Canvas);
     Item = g_AlternateList->Next();
   }
}


bool TPaintGrid::CreateAternative(TFlagShape* AFlag)
{
   TBaseWorkShape *WS, *InactivateWS;
   TFlagShape* FS = NULL;
   if ( !AFlag ) return false;
   if ( (f_SelectedAlternateFirst) && (f_SelectedAlternateLast) ) return false;
   WS = f_FlagController->FindWorkShape(AFlag);
   if (WS)
   {
      if (!f_SelectedAlternateFirst)
      {
         f_SelectedAlternateFirst = WS;
         f_FlagController->ApplyFlagColor(AFlag, AltEnterFlagColor, AltEnterFlagColor);
         if (f_FlagController->FindByFlagShape(AFlag)->Signal->Position == 2)
           f_SelectedAlternateFirst->Tag = 1;
         else
           f_SelectedAlternateFirst->Tag = 0;


         InactivateWS = NULL;
         if ( GetMainTabCount() > 0)
         {
           if (WS == FirstWorkShape)
              InactivateWS = LastWorkShape;
           if ( (WS == LastWorkShape) && (f_SelectedAlternateFirst->Tag == 1))
              InactivateWS = FirstWorkShape;
           if (InactivateWS)
           {
              FS =  f_FlagController->FindFlagShape(InactivateWS);
              if (FS)
              {
                FS->LEActive = false;
                FS->BrushColor = AltEnabledFlagColor;
                f_FlagController->ApplyFlagColor(FS, AltEnabledFlagColor, AltEnabledFlagColor);
              }
           }
         }

         if (f_FlagController->EnterByShape(AFlag) || (InactivateWS))
         {
           f_ClipPath->Clear();
           f_ClipPath->Add(AFlag->GetFrameRect(), C_DEFAULTCLIPOFS);
           if (FS)
              f_ClipPath->Add(FS->GetFrameRect(), C_DEFAULTCLIPOFS);
           PostMessage(f_OwnerForm, WM_GD_PAINTONEPREPARE, 1, LPARAM(f_ClipPath->GetCliptRgn()));
         }

         return false;
      }
      if (!f_SelectedAlternateLast)
      {
         if ( (WS == f_SelectedAlternateFirst)  && (WS != g_PainterList->Last() ) )
            return false;
         f_SelectedAlternateLast = WS;
         f_FlagController->ApplyFlagColor(AFlag, AltEnterFlagColor, AltEnterFlagColor);
         if (f_FlagController->FindByFlagShape(AFlag)->Signal->Position == 2)
           f_SelectedAlternateLast->Tag = 1;
         else
           f_SelectedAlternateLast->Tag = 0;

         if (f_FlagController->EnterByShape(AFlag))
         {
           f_ClipPath->Clear();
           f_ClipPath->Add(AFlag->GetFrameRect(), C_DEFAULTCLIPOFS);
           PostMessage(f_OwnerForm, WM_GD_PAINTONEPREPARE, 1, LPARAM(f_ClipPath->GetCliptRgn()));
         }
         return true;
      }
   }
   return false;
}

//---------------------------------------------------------------------------------------
bool TPaintGrid::CreateDeleteTFSList(TFlagShape* AFlag)
{
   TBaseWorkShape* WS;
   if ( !AFlag ) return false;
   if ( (f_SelectedDeleteTFSFirst) && (f_SelectedDeleteTFSLast) ) return false;
   WS = f_FlagController->FindWorkShape(AFlag);
   if (WS)
   {
      if (!f_SelectedDeleteTFSFirst)
      {
         f_SelectedDeleteTFSFirst = WS;
         f_FlagController->ApplyFlagColor(AFlag, EnterFlagColor, EnterFlagColor);
         if (f_FlagController->FindByFlagShape(AFlag)->Signal->Position == 2)
           f_SelectedDeleteTFSFirst->Tag = 1;
         else
           f_SelectedDeleteTFSFirst->Tag = 0;

         if (f_FlagController->EnterByShape(AFlag))
         {
           f_ClipPath->Clear();
           f_ClipPath->Add(AFlag->GetFrameRect(), C_DEFAULTCLIPOFS);
           PostMessage(f_OwnerForm, WM_GD_PAINTONEPREPARE, 1, LPARAM(f_ClipPath->GetCliptRgn()));
         }

         return false;
      }
      if (!f_SelectedDeleteTFSLast)
      {
         if ( (WS == f_SelectedDeleteTFSLast)  && (WS != g_PainterList->Last() ) )
            return false;
         f_SelectedDeleteTFSLast = WS;
         f_FlagController->ApplyFlagColor(AFlag, EnterFlagColor, EnterFlagColor);
         if (f_FlagController->FindByFlagShape(AFlag)->Signal->Position == 2)
           f_SelectedDeleteTFSLast->Tag = 1;
         else
           f_SelectedDeleteTFSLast->Tag = 0;

         if (f_FlagController->EnterByShape(AFlag))
         {
           f_ClipPath->Clear();
           f_ClipPath->Add(AFlag->GetFrameRect(), C_DEFAULTCLIPOFS);
           PostMessage(f_OwnerForm, WM_GD_PAINTONEPREPARE, 1, LPARAM(f_ClipPath->GetCliptRgn()));
         }
         return true;
      }
   }
   return false;
}






void TPaintGrid::NilAternative()
{
   if (f_SelectedAlternateFirst)
     f_SelectedAlternateFirst->Tag = 0;
   if (f_SelectedAlternateLast)
     f_SelectedAlternateLast->Tag = 0;
   f_SelectedAlternateFirst = f_SelectedAlternateLast = NULL;
}


void TPaintGrid::NilDeleteTFSList()
{
   if (f_SelectedDeleteTFSFirst)
     f_SelectedDeleteTFSFirst->Tag = 0;
   if (f_SelectedDeleteTFSLast)
     f_SelectedDeleteTFSLast->Tag = 0;
   f_SelectedDeleteTFSFirst = f_SelectedDeleteTFSLast = NULL;
}


void __fastcall TPaintGrid::SetRegim(int Value)
{
  // int m_OldRegim;
   if (f_Regim != Value)
   {
  //   m_OldRegim = f_Regim;
     f_Regim = Value;
     switch (f_Regim)
     {
       case 0:
       {
          NilAternative();
          NilDeleteTFSList();
          break;
       }
       case 1:
       {
          NilAternative();
          NilDeleteTFSList();
          break;

       }
       case 2:
       {
          NilDeleteTFSList();
          break;
       }
       case 3:
       {
          NilDeleteTFSList();
          break;
       }
       case 5:
       {
          NilAternative();
          NilDeleteTFSList();
          break;
       }
       case 7:
       {
          NilAternative();
          NilDeleteTFSList();
          break;
       }

     }


   }

}


void TPaintGrid::ClearAltWSList()
{
   f_AltWSList->Clear();
}

void TPaintGrid::AddToAltWSList(TBaseWorkShape* AWS)
{
   f_AltWSList->Add(AWS);
}

HRGN TPaintGrid::GetRGNAltWSList()
{
   f_ClipPath->Clear();
   for (int i = 0 ; i <= f_AltWSList->Count - 1; i++)
      f_ClipPath->Add(f_AltWSList->Items[i]->GetFrameRectWithLines(), C_DEFAULTCLIPOFS);
   return f_ClipPath->GetCliptRgn();
}


TAlternateItem *TPaintGrid::FindAlternateItem(int Ax, int Ay)
{
   TAlternateItem *Item;
   Item = g_AlternateList->First();
   while (Item)
   {
      if (PtInRect(&Item->ArrowWorkShape->GetSmallRegionRect(), TPoint(Ax, Ay)))
          return Item;
      Item = g_AlternateList->Next();
   }
   return NULL;
}


bool TPaintGrid::IsAltWSListEmpty()
{
   return (f_AltWSList->Count == 0);
}


void TPaintGrid::ClearAll()
{
   f_SelectedTFE = NULL;
   f_SelectedTFS = NULL;
   f_ClipPath->Clear();
   g_PainterList->ClearAll();
   f_ListForPaint->Clear();
   f_FlagController->ClearAll();
   f_InvalidateList->Clear();
   f_LineCutting->ClearAll();
   g_AlternateList->ClearAll();
   f_AltWSList->Clear();
   f_localVisiblearrowall = false;
}

void TPaintGrid::SetWSFlagEvent(TBaseWorkShape *WS)
{
   if (!WS) return;
   WS->OnWSFlagCreate = WsFlagCreate;
   WS->OnWSFlagDestroy = WsFlagDestroy;
}




/*

//---------------------------------------------------------------------------
TBaseShape* TPaintGrid::FindTFE(int Ax, int Ay)
{
  TBaseShape * CurrShape;
  TBaseWorkShape *TempWork;
  TempWork = g_PainterList->First();
  while(TempWork)
  {
     for (int i = 0; i <= TempWork->WorkShapesCount - 1; i++ )
     {
        CurrShape =static_cast<TBaseShape*>(TempWork->GetWorkShape(i));
        if (PtInRect(&CurrShape->GetRect(), TPoint(Ax, Ay)))
          return CurrShape;
     }
     TempWork = g_PainterList->Next();
  }
  return NULL;
}


TBaseShape* TPaintGrid::FindTFE(int Ax, int Ay)
TAlternateItem *Item;
   Item = g_AlternateList->First();
   while (Item)
   {
      P = Item->ArrowWorkShape->StartPoint;
      P.x += AX;
      P.y += AY;
      Item->ArrowWorkShape->StartPoint = P;
      Item->ArrowWorkShape->SetOffsetPosition(AX, AY);
      Item = g_AlternateList->Next();
   }

*/


void TPaintGrid::RecalcAfterConverted(bool AFirst, TPoint FPoint)
{
  TBaseWorkShape *WS, *WN;
  TPoint P1, P2;
  int X_ofs;
  WS = g_PainterList->First();
  if (!WS) return;
  P1 = WS->StartPoint;
  P1 = WS->StartPoint;
  if (AFirst)
    P2 = TPoint(FPoint.x + f_X_offsSum, FPoint.y + f_Y_offsSum);
  else
    P2 = TPoint(WS->BaseStartPoint.x + f_X_offsSum, WS->BaseStartPoint.y + f_Y_offsSum);
  if( (P2.x != P1.x) || (P2.y != P1.y)  )
  {
     X_ofs = P2.x - P1.x;
     WS->StartPoint = P2;
     WS->SetOffsetPosition(X_ofs, 0);
     WS->Prepare();
  }

  X_ofs = 0;
  WS = g_PainterList->First();
  while( WS )
  {
    WN = FindNextWorkShape(WS);
    if (!WN) return;
    P1 = WN->StartPoint;
    P2 = WS->EndPoint;
    if(  ( (P2.x != P1.x) || (P2.y != P1.y) ) )
    {
        X_ofs = P2.x - WN->FirstLine->xEnd + WN->OffsetXFromStart;
        WN->StartPoint = WS->EndPoint;
        WN->SetOffsetPosition(X_ofs, 0);
        WN->Prepare();
        WS = g_PainterList->Next();
        continue;
    }
    WN->StartPoint.x += X_ofs;
    WN->SetOffsetPosition(X_ofs, 0);
    WS = g_PainterList->Next();
  }
}


TBaseWorkShape* TPaintGrid::FindShapeFromCompositeWork(int AShapeID)
{
  TBaseWorkShape *TempWork;
  TempWork = g_PainterList->First();
  while( TempWork )
  {
     if (TempWork->CompositeWorkShape)
     {
       if (TempWork->CompositeWorkShape->ContainedShape(AShapeID))
         return  TempWork;
     }
     else
     {
        if(TempWork->ShapeSupportID(AShapeID))
          return TempWork;
     }
     TempWork = g_PainterList->Next();
  }
  return NULL;
}

void TPaintGrid::CoordinateCorrectForCompositeWork()
{
   TPoint P, PN, PO;
   int X_ofs;
   TBaseWorkShape *TempWork;
   TempWork = g_PainterList->First();
   if (!TempWork) return;
   if (TempWork->CompositeWorkShape)
   {
     TempWork->CompositeWorkShape->OffsetEndCoordinate(TempWork->CompositeWorkShape->StartPoint);
     P = TempWork->CompositeWorkShape->EndPoint;
   }
   else
     P = TempWork->EndPoint;

   TempWork = g_PainterList->Next();
   while( TempWork )
   {
     if (TempWork->CompositeWorkShape)
     {
       PN = TempWork->CompositeWorkShape->StartPoint;
       P.y = PN.y;

       TempWork->CompositeWorkShape->StartPoint = P;
       TempWork->CompositeWorkShape->OffsetEndCoordinate(P);
       P = TempWork->CompositeWorkShape->EndPoint;

       PO = TempWork->GetStartPointOneComposite();
       TempWork->CompositeWorkShape->MakeFirstLine(PO, TempWork->Bend(PO.x, TempWork->FirstLine->xEnd));

     }
     else
     {
        PN = TempWork->StartPoint;
        if( (PN.x != P.x)  )
        {
          X_ofs = PN.x - P.x;
        //  TempWork->StartPoint = TPoint(PN.x,PN.y);   //че за..........
          TempWork->StartPoint = P;
          TempWork->SetOffsetPosition(-X_ofs, 0);
          TempWork->Prepare();
        }
        P = TempWork->EndPoint;
     }
     TempWork = g_PainterList->Next();
   }

}

TCompositeBaseWorkItem* TPaintGrid::FindComositeBaseWork2(int ATFEID, TCompositeBaseWork **AFind)
{
  TBaseWorkShape* TempWork;
  TCompositeBaseWork* WF;
  TCompositeBaseWorkItem* Item;
  TempWork = g_PainterList->First();
  while(TempWork)
  {
     if (TempWork->CompositeWorkShape)
     {
       Item = TempWork->CompositeWorkShape->FindItem(ATFEID, &WF);
       if (Item)
       {
         *AFind =  WF;
         return Item;
       }
     }
     TempWork = g_PainterList->Next();
  }
  *AFind = NULL;
  return NULL;
}






