//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufmViewResult.h"
#include "uListShape.h"
#include "uCursorStorage.h"
#include "uFmParamAlternative.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmViewResult *fmViewResult;

TBaseWorkShape* CreateWorkShape(TPoint APoint, int AType, int AStepPixels, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine)
{
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (AType > 0)
   {
      switch (AType)
      {
       case 1:
         m_CurrWorkShape = new TWork(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 2:
         m_CurrWorkShape = new TZWork(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 3:
         m_CurrWorkShape = new TZWorkOR(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 4:
         m_CurrWorkShape = new TControlWork(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 5:
         m_CurrWorkShape = new TControlFunc(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 6:
         m_CurrWorkShape = new TBifurcation(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 7:
         m_CurrWorkShape = new TCheckConditionCW(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 8:
         m_CurrWorkShape = new TCycleWhileDo(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 9:
         m_CurrWorkShape = new TCycleDoWhileDo(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 10:
         m_CurrWorkShape = new TCycleDoWhileDoFC(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 11:
         m_CurrWorkShape = new TCheckCondition(APoint.x, APoint.y, AStepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
      }

      m_CurrWorkShape->Init();
      m_CurrWorkShape->Prepare();
   }
   return m_CurrWorkShape;
}

void CloneParamAlternative(TDecisionScannerItemTFS *ASource, TBaseWorkShape *ADest)
{
  TBaseShape *D;
  TDecisionScannerItemTFE *S;
  for(int i = 0; i <= ASource->TFECount - 1; i++)
  {
    S = ASource->TFEItem[i];
    if (S->Alternative)
    {
      for(int j = 0; j <= ADest->WorkShapesCount - 1; j++)
      {
        D = ADest->GetWorkShape(j);
        if (D->ID == S->TFE->ID)
          break;
      }
      TParamAlternativeItem* AI = S->Alternative->Clone();
      AI->SOSTAV = IntToStr(S->TFE->ID) + ":1";
      D->AddParamAlternativeItem(AI);
    }
  }
}

//---------------------------------------------------------------------------
__fastcall TfmViewResult::TfmViewResult(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmViewResult::pbViewPaint(TObject *Sender)
{
  Grid->Paint();        
}
//---------------------------------------------------------------------------
void __fastcall TfmViewResult::pnlViewResize(TObject *Sender)
{
  Grid->Recreate(pbView->Width, pbView->Height);
  SetNewPolygon();
}
//---------------------------------------------------------------------------
void __fastcall TfmViewResult::FormCreate(TObject *Sender)
{
  DecScaner = new TDecisionScanner;
  LN = new TListNode;
  X_Base = Y_Base = X_Ofs = Y_Ofs = 0;
  FSortPath = new TDynamicArray;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::FormDestroy(TObject *Sender)
{
  delete DecScaner;
  delete LN;
  delete FSortPath;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::acCloseExecute(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------
void TfmViewResult::Init(int AType_Char)
{
  int MinShapeID;
  int mCurrIdLine = 0;
  TPoint P = TPoint(40, 100);
  TDecisionScannerItemTFS* mTfs;

  Type_Char = AType_Char;
  DecScaner->Scan(FStr);
  SortPath();
  LN->CreateAlternate(NULL, NULL, 0, 0);
/*
  for(int i = 0; i <= DecScaner->TFSCount - 1; i++)
  {
    mTfs = DecScaner->TFS[i];
    MinShapeID = mTfs->GetMinShapeID();
    TBaseWorkShape* WS = CreateWorkShape(P, mTfs->TFS->TypeShape, Grid->StepPixels, MinShapeID - 1, i + 1, mCurrIdLine);
    P = WS->EndPoint;
    CloneParamAlternative(mTfs, WS);
    LN->AddShapeToList(0, 0, WS, 0);
  }
*/
  for(int i = 0; i <= FSortPath->Count - 1; i++)
  {
    mTfs = static_cast<TDecisionScannerItemTFS*>(FSortPath->Items[i]);
    MinShapeID = mTfs->GetMinShapeID();
    TBaseWorkShape* WS = CreateWorkShape(P, mTfs->TFS->TypeShape, Grid->StepPixels, MinShapeID - 1, i + 1, mCurrIdLine);
    P = WS->EndPoint;
    CloneParamAlternative(mTfs, WS);
    LN->AddShapeToList(0, 0, WS, 0);
  }



  LN->FillPainterList(Grid->g_PainterList, 0, 0, 0);
  SetNewPolygon();
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::acSaveResultExecute(TObject *Sender)
{
  bool s_xml;
  AnsiString Pt, Fn, Ex, Tmp;

  if ( SaveDLG->Execute() )
  {
    TDischargedMassiv DM(0);
    Pt = ExtractFilePath(SaveDLG->FileName);
    Fn = ExtractFileName(SaveDLG->FileName);
    Ex = ExtractFileExt(SaveDLG->FileName);
    Tmp = Fn.SubString(1, Fn.Length() - Ex.Length());
    s_xml = (SaveDLG->FilterIndex == 2);
    if(s_xml)
      Fn = Pt + Tmp + ".xml";
    else
      Fn = Pt + Tmp + ".gls";
    ShowCursorStorage();


    if(s_xml)
      LN->SaveAllToFile(Fn, Type_Char, &DM);
    else
      LN->SaveAllToFileBin(Fn, Type_Char, &DM);
    HideCursorStorage();
  }  
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::pbViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Grid->MouseDown(Sender, Button, Shift, X, Y);        
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::pbViewMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Grid->MouseUp(Sender, Button, Shift, X, Y);
  if ( Button == mbRight )
  {
    TPoint P = pbView->ClientToScreen(TPoint(X, Y));
    pmMenu->Popup(P.x, P.y); 
  }
}
//---------------------------------------------------------------------------
void __fastcall TfmViewResult::M_gd_paint(TMessage& Msg)
{
  Grid->PreparePaint();
  switch (Msg.WParam)
  {
    case 0 :
       pbView->Invalidate();
       break;
    case 1 :
       InvalidateRgn(pbView->Parent->Handle, HRGN(Msg.LParam), false);
       break;
    case 2:
       InvalidateRgn(pbView->Parent->Handle, HRGN(Msg.LParam), false);
       UpdateWindow(pnlView->Handle);
       break;
  }
}

void __fastcall TfmViewResult::acShowParamUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = Grid->SelectedTFE;        
}
//---------------------------------------------------------------------------

void TfmViewResult::BuildGlp(TBaseWorkShape* AWN, Graphics::TBitmap* Glp, TBaseShape *ASel)
{
   TBaseShape* BS;
   Application->CreateForm(__classid(TfmParamAlternative), &fmParamAlternative);
   Glp->Width = fmParamAlternative->pbTfs->Width;
   Glp->Height = fmParamAlternative->pbTfs->Height;
   fmParamAlternative->Release();
   Application->ProcessMessages();
   Glp->Canvas->Brush->Color = Grid->FonColor;
   Glp->Canvas->FillRect(TRect(0,0, Glp->Width, Glp->Height));
   AWN->StartPoint = TPoint(0, 0);
   AWN->Init();
   AWN->Prepare();
   if ( Grid->BrushTFE )
     AWN->BrushStyle = bsSolid;
   else
     AWN->BrushStyle = bsClear;
   AWN->BrushColor =  Grid->BrushColor;
   AWN->LineWidth =  Grid->WSPenWidth;
   AWN->PenWidth =  Grid->WSPenWidth;
   AWN->Font->Assign( Grid->FontTFE);
   AWN->FrameColorTFE = Grid->FrameColorTFE;
   AWN->PenColor =  Grid->LineColor;

   TRect R = AWN->GetFrameRectWithLines();
   int rx = (Glp->Width - R.Width())/2 - R.Left;
   int ry = (Glp->Height - R.Height())/2 - R.Top;
   AWN->SetOffsetPosition(rx, ry);
   AWN->StartPoint = TPoint(rx, ry);

   if (ASel->Clon)
     BS = ASel->Clon;
   else
     BS = ASel;

   BS = AWN->ShapeSupportID(BS->ID);
   if (BS)
     BS->DrawFrame = true;

   AWN->Prepare();
   AWN->Paint(Glp->Canvas);
}


void __fastcall TfmViewResult::acShowParamExecute(TObject *Sender)
{
   TBaseWorkShape* Sel =  Grid->FindShapeFromCompositeWork(Grid->SelectedTFE->ID);
   if (Sel)
   {
     if (Sel->CompositeWorkShape)
     {
       TCompositeBaseWork *F;
       Grid->FindComositeBaseWork2(Grid->SelectedTFE->ID,  &F);
       Sel = F->ConvertedBWS;
     }
     TBaseWorkShape* WN =  Grid->CreateTempWorkShape(Sel->TypeShape, TPoint(0,0), Sel->FirstShapeId - 1);

     Graphics::TBitmap* Glp = new Graphics::TBitmap;
     BuildGlp(WN, Glp, Grid->SelectedTFE);
     ShowParamAlternative(Grid->SelectedTFE, 0, Type_Char, Glp, true);
     delete  WN;
     delete Glp;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::sbXChange(TObject *Sender)
{
   TRect R;
   X_Ofs = sbX->Position - X_Base;
   X_Base = sbX->Position;
   Grid->ApplyOffset(-X_Ofs, 0);
   Grid->PreparePaint();
   if (X_Ofs < 0)
     R = TRect(0,0, abs(X_Ofs) + 3, pbView->Height);
   else
     R = TRect(pbView->Width - X_Ofs  - 3, 0, pbView->Width, pbView->Height);
   ScrollDC(pbView->Canvas->Handle, -X_Ofs, 0, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlView->Handle, &R, false);
   UpdateWindow(pnlView->Handle);
 }
//---------------------------------------------------------------------------

void __fastcall TfmViewResult::sbYChange(TObject *Sender)
{
   TRect R;
   Y_Ofs = sbY->Position - Y_Base;
   Y_Base = sbY->Position;
   Grid->ApplyOffset(0, -Y_Ofs);
   Grid->PreparePaint();
   if (Y_Ofs < 0)
     R = TRect(0,0,  pbView->Width, abs(Y_Ofs) + 3);
   else
     R = TRect(0, pbView->Height - Y_Ofs  - 3, pbView->Width, pbView->Height);

   ScrollDC(pbView->Canvas->Handle, 0, - Y_Ofs, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlView->Handle, &R, false);
   UpdateWindow(pnlView->Handle);

}
//---------------------------------------------------------------------------
void TfmViewResult::SetNewPolygon()
{
   TPoint P;
   P =  Grid->GetPointPolygon(sbX->Position, sbY->Position);
   if ((P.x - pbView->Width - sbX->Position) > 2)
     sbX->Max = P.x  - pbView->Width + (Grid->StepPixels * 4);
   if ((P.y - pbView->Height - sbY->Position) > 2)
     sbY->Max = P.y  - pbView->Height + (Grid->StepPixels * 4);
}

void TfmViewResult::DoSortPathItem(TPredicatePathNodeItem* AItem)
{
  int tfe_id;
  if (AItem->TFS)
  {
    TDecisionScannerItemTFS* mTfs;
    for(int i = 0; i <= DecScaner->TFSCount - 1; i++)
    {
      mTfs = DecScaner->TFS[i];
      tfe_id = mTfs->GetMinShapeID();
      if ( AItem->TFS->ShapeSupportID(tfe_id) )
      {
        if ( !FSortPath->Find(mTfs) )
          FSortPath->Append(mTfs);
        return;
      }
    }
  }
}

void TfmViewResult::SortPath()
{
  int m_pos;
  TPredicatePathNode* Node;
  TPredicatePathNodeItem* Item;
  TDecisionScannerItemTFS* mTfs;
  FSortPath->Clear();
  for(int i = 0; i <= FPredicatePathItem->NodeCount - 1; i++)
  {
    Node = FPredicatePathItem->NodeItems[i];
    Item = Node->FindIndexFirst(m_pos);
    while(Item)
    {
      DoSortPathItem(Item);
      Item = Node->FindIndexNext(m_pos);
    }
  }

  //это на всякий случай
  for(int i = 0; i <= DecScaner->TFSCount - 1; i++)
  {
    mTfs = DecScaner->TFS[i];
    if ( !FSortPath->Find(mTfs) )
      FSortPath->Append(mTfs);
  }
}


