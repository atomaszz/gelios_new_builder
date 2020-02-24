//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufmViewDecision.h"
#include "uIMRIncl_all.h"
#include "uCommonGraph.h"

#include "uZWork.h"
#include "uZWorkOR.h"
#include "uCheckCondition.h"
#include "uCheckConditionCW.h"
#include "uControlWork.h"
#include "uControlFunc.h"
#include "uBifurcation.h"
#include "uCycleWhileDO.h"
#include "uCycleDoWhileDO.h"
#include "uCycleDoWhileDOFC.h"
#include "uDischargedMassiv.h"
#include "uPaintgrids.h"
#include "ufmViewResult.h"
#include "uMessengers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmViewDecision *fmViewDecision;




//---------------------------------------------------------------------------
__fastcall TfmViewDecision::TfmViewDecision(TComponent* Owner)
        : TForm(Owner)
{
}
void TfmViewDecision::DrawBevel()
{
  Bevel1->Left = edVid1->Left - 2;
  Bevel1->Width = edVid1->Width + 4;
  Bevel1->Height = edVid1->Height + 4;
  Bevel1->Top = edVid1->Top - 2;

  Bevel2->Left = edVid2->Left - 2;
  Bevel2->Width = edVid2->Width + 4;
  Bevel2->Height = edVid2->Height + 4;
  Bevel2->Top = edVid2->Top - 2;


  Bevel3->Left = edOgr1->Left - 2;
  Bevel3->Width = edOgr1->Width + 4;
  Bevel3->Height = edOgr1->Height + 4;
  Bevel3->Top = edOgr1->Top - 2;


  Bevel4->Left = edOgr2->Left - 2;
  Bevel4->Width = edOgr2->Width + 4;
  Bevel4->Height = edOgr2->Height + 4;
  Bevel4->Top = edOgr2->Top - 2;

  Bevel5->Left = edKoef->Left - 2;
  Bevel5->Width = edKoef->Width + 4;
  Bevel5->Height = edKoef->Height + 4;
  Bevel5->Top = edKoef->Top - 2;

  Bevel6->Left = edTime->Left - 2;
  Bevel6->Width = edTime->Width + 4;
  Bevel6->Height = edTime->Height + 4;
  Bevel6->Top = edTime->Top - 2;


}
//---------------------------------------------------------------------------
void __fastcall TfmViewDecision::acCloseExecute(TObject *Sender)
{
  ModalResult = mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TfmViewDecision::FormCreate(TObject *Sender)
{
  DrawBevel();
//  DecScaner = new TDecisionScanner;
}
//---------------------------------------------------------------------------


void __fastcall TfmViewDecision::FormShow(TObject *Sender)
{
   StringInit();
   RefreshData();
   sgAlternative->SetFocus();
}
//---------------------------------------------------------------------------

void TfmViewDecision::StringInit()
{
  sgAlternative->RowCount    = 1;
  sgAlternative->RowCount    = 2;
  sgAlternative->FixedRows   = 1;

  SGCells(sgAlternative, 0, 0, "ÑÎÑÒÀÂ");
  sgAlternative->ColWidths[0] = 200;

  if(Type_Char == PROP)
  {
     sgAlternative->ColCount = 4;
     SGCells(sgAlternative, 0, 1, "B");
     SGCells(sgAlternative, 0, 2, "T");
     SGCells(sgAlternative, 0, 3, "V");
  }
  else if(Type_Char == FUZZY)
  {
     sgAlternative->ColCount = 28;
     SGCells(sgAlternative, 0, 1, "A1_B_F");
     SGCells(sgAlternative, 0, 2, "Â_F1N");
     SGCells(sgAlternative, 0, 3, "Â_F1B");
     SGCells(sgAlternative, 0, 4, "A2_Â_F");
     SGCells(sgAlternative, 0, 5, "Â_F2N");
     SGCells(sgAlternative, 0, 6, "Â_F2B");
     SGCells(sgAlternative, 0, 7, "A3_B_F");
     SGCells(sgAlternative, 0, 8, "Â_F3N");
     SGCells(sgAlternative, 0, 9, "Â_F3B");
     SGCells(sgAlternative, 0, 10, "A1_T_F");
     SGCells(sgAlternative, 0, 11, "T_F1N");
     SGCells(sgAlternative, 0, 12, "T_F1B");
     SGCells(sgAlternative, 0, 13, "A2_T_F");
     SGCells(sgAlternative, 0, 14, "T_F2N");
     SGCells(sgAlternative, 0, 15, "T_F2B");
     SGCells(sgAlternative, 0, 16, "A3_T_F");
     SGCells(sgAlternative, 0, 17, "T_F3N");
     SGCells(sgAlternative, 0, 18, "T_F3B");
     SGCells(sgAlternative, 0, 19, "A1_V_F");
     SGCells(sgAlternative, 0, 20, "V_F1N");
     SGCells(sgAlternative, 0, 21, "V_F1B");
     SGCells(sgAlternative, 0, 22, "A2_V_F");
     SGCells(sgAlternative, 0, 23, "V_F2N");
     SGCells(sgAlternative, 0, 24, "V_F2B");
     SGCells(sgAlternative, 0, 25, "A3_V_F");
     SGCells(sgAlternative, 0, 26, "V_F3N");
     SGCells(sgAlternative, 0, 27, "V_F3B");
  }
}

void TfmViewDecision::RefreshData()
{
   if(Type_Char == PROP)
     RefreshDataPROP();
   if(Type_Char == FUZZY)
     RefreshDataFUZZY();
}


void TfmViewDecision::RefreshDataPROP()
{
  TParamAlternativeItem* AI;
  sgAlternative->RowCount    = 2;
  if (ParamAlt)
  {
    int m_cnt = ParamAlt->Count;
    for (int i = 0; i <= m_cnt - 1; i++)
    {
       if (i+1 > sgAlternative->RowCount - 1)
         sgAlternative->RowCount    = sgAlternative->RowCount + 1;
       AI = ParamAlt->Items[i];
       sgAlternative->Objects[0][1+i] = (TObject*)AI;
       SGCellsByName(sgAlternative, 1 + i,  "ÑÎÑÒÀÂ", AI->SOSTAV);
       SGCellsByName(sgAlternative, 1 + i, "B", float_2_string(AI->B, 6));
       SGCellsByName(sgAlternative, 1 + i, "T", float_2_string(AI->T, 6));
       SGCellsByName(sgAlternative, 1 + i, "V", float_2_string(AI->V, 6));
    }
  }
}

void TfmViewDecision::RefreshDataFUZZY()
{
  TParamAlternativeItem* AI;
  sgAlternative->RowCount    = 2;
  if (ParamAlt)
  {
    int m_cnt = ParamAlt->Count;
    for (int i = 0; i <= m_cnt - 1; i++)
    {
       if (i+1 > sgAlternative->RowCount - 1)
         sgAlternative->RowCount    = sgAlternative->RowCount + 1;
       AI = ParamAlt->Items[i];
       sgAlternative->Objects[0][1+i] = (TObject*)AI;
       SGCellsByName(sgAlternative, 1 + i,  "ÑÎÑÒÀÂ", AI->SOSTAV);
       SGCellsByName(sgAlternative, 1 + i, "A1_B_F", float_2_string(AI->A1_B_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F1N", float_2_string(AI->B_F1N, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F1B", float_2_string(AI->B_F1B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A2_Â_F", float_2_string(AI->A2_B_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F2N", float_2_string(AI->B_F2N, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F2B", float_2_string(AI->B_F2B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A3_B_F", float_2_string(AI->A3_B_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F3N", float_2_string(AI->B_F3N, 6));
       SGCellsByName(sgAlternative, 1 + i, "Â_F3B", float_2_string(AI->B_F3B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A1_T_F", float_2_string(AI->A1_T_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F1N", float_2_string(AI->T_F1N, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F1B", float_2_string(AI->T_F1B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A2_T_F", float_2_string(AI->A2_T_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F2N", float_2_string(AI->T_F2N, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F2B", float_2_string(AI->T_F2B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A3_T_F", float_2_string(AI->A3_T_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F3N", float_2_string(AI->T_F3N, 6));
       SGCellsByName(sgAlternative, 1 + i, "T_F3B", float_2_string(AI->T_F3B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A1_V_F", float_2_string(AI->A1_V_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F1N", float_2_string(AI->V_F1N, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F1B", float_2_string(AI->V_F1B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A2_V_F", float_2_string(AI->A2_V_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F2N", float_2_string(AI->V_F2N, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F2B", float_2_string(AI->V_F2B, 6));
       SGCellsByName(sgAlternative, 1 + i, "A3_V_F", float_2_string(AI->A3_V_F, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F3N", float_2_string(AI->V_F3N, 6));
       SGCellsByName(sgAlternative, 1 + i, "V_F3B", float_2_string(AI->V_F3B, 6));
    }
  }
}

void __fastcall TfmViewDecision::sgAlternativeDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
/* Stas19
  TParamAlternativeItem *AI;
  if (ARow == 0) return;
  AI = (TParamAlternativeItem*)(sgAlternative->Objects[0][ARow]);
  if ( AI && AI->Tag == 1)
	sgAlternative->Canvas->Brush->Color = VwColorAlt;
  else
	sgAlternative->Canvas->Brush->Color = VwColorBadAlt;
  if (State.Contains(gdSelected))
	sgAlternative->Canvas->Brush->Color = clHighlight;

	sgAlternative->Canvas->FillRect(Rect);
	sgAlternative->Canvas->Font->Color = VwColorFont;
	sgAlternative->Canvas->TextOut(Rect.Left + 2, Rect.Top + 1, sgAlternative->Cells[ACol][ARow]);
*/

// Äàëåå äëÿ XE10
  TParamAlternativeItem *AI;
  if (ARow == 0) return;
  AI = (TParamAlternativeItem*)(sgAlternative->Objects[0][ARow]);
  if ( AI && AI->Tag == 1)
	sgAlternative->Canvas->Font->Color = VwColorAlt;// clBlue;
  else
	sgAlternative->Canvas->Font->Color = VwColorBadAlt; //clRed;
/*
  if (State.Contains(gdSelected))
  {
	sgAlternative->Canvas->Brush->Color = clHighlight;
	sgAlternative->Canvas->Font->Color = clHighlightText;
  }
*/

  //	sgAlternative->Canvas->FillRect(Rect);
//	sgAlternative->Canvas->Font->Color = VwColorFont;
	sgAlternative->Canvas->TextOut(Rect.Left + 2, Rect.Top + 1, sgAlternative->Cells[ACol][ARow]);

}
//---------------------------------------------------------------------------
  //ìèëëèñåêóíä
void __fastcall TfmViewDecision::FormDestroy(TObject *Sender)
{
//  delete DecScaner;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewDecision::acShowResultExecute(TObject *Sender)
{
  if (sgAlternative->Selection.Top == 0) return;
  TParamAlternativeItem *AI = (TParamAlternativeItem*)(sgAlternative->Objects[0][sgAlternative->Selection.Top]);

  fmViewResult = new TfmViewResult(Application);
  TPaintGrid* Grid = new TPaintGrid(fmViewResult->pbView->Canvas, fmViewResult->Handle);
  GMess->SendMess(7, int(Grid), 0);

  fmViewResult->FStr = AI->SOSTAV.c_str();
  fmViewResult->Grid = Grid;
  fmViewResult->pnlView->Color = Grid->FonColor;
  fmViewResult->FPredicatePathItem = FPredicatePathItem;
  fmViewResult->Init(Type_Char);
  fmViewResult->ShowModal();
  fmViewResult->Release();
  delete Grid;


/*
  bool s_xml;
  int MinShapeID;
  AnsiString Pt, Fn, Ex, Tmp;
  int mCurrIdLine = 0;
  TPoint P = TPoint(40, 100);
  TDischargedMassiv DM(0);
  TDecisionScannerItemTFS* mTfs;
  if (sgAlternative->Selection.Top == 0) return;
  TParamAlternativeItem *AI = (TParamAlternativeItem*)(sgAlternative->Objects[0][sgAlternative->Selection.Top]);

  if ( SaveDLG->Execute() )
  {
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

    DecScaner->Scan(AI->SOSTAV.c_str());
    TListNode* LN = new TListNode;
    LN->CreateAlternate(NULL, NULL, 0, 0);
    for(int i = 0; i <= DecScaner->TFSCount - 1; i++)
    {
      mTfs = DecScaner->TFS[i];
      MinShapeID = mTfs->GetMinShapeID();
      TBaseWorkShape* WS = CreateWorkShape(P, mTfs->TFS->TypeShape, MinShapeID - 1, i + 1, mCurrIdLine);
      P = WS->EndPoint;
      CloneParamAlternative(mTfs, WS);
      LN->AddShapeToList(0, 0, WS, 0);

    }

    fmViewResult = new TfmViewResult(Application);
    TPaintGrid* Grid = new TPaintGrid(fmViewResult->pbView->Canvas, fmViewResult->Handle);
    GMess->SendMess(7, int(Grid), 0);
    fmViewResult->Grid = Grid;
    fmViewResult->pnlView->Color = Grid->FonColor;


    LN->FillPainterList(Grid->g_PainterList, 0, 0, 0);

    fmViewResult->ShowModal();

    if(s_xml)
      LN->SaveAllToFile(Fn, Type_Char, &DM);
    else
      LN->SaveAllToFileBin(Fn, Type_Char, &DM);
    HideCursorStorage();

    fmViewResult->Release();
    delete Grid;
    delete LN;
  }
*/

}
//---------------------------------------------------------------------------






