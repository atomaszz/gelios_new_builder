//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufmViewPredicateTrackConstructor.h"
#include "uCommonGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfmViewPredicateTrackConstructor *fmViewPredicateTrackConstructor;
//---------------------------------------------------------------------------
__fastcall TfmViewPredicateTrackConstructor::TfmViewPredicateTrackConstructor(TComponent* Owner)
		: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TfmViewPredicateTrackConstructor::StringInit(TStringGrid *Grid)
{
  Grid->RowCount    = 1;
  Grid->RowCount    = 2;
  Grid->FixedRows   = 1;
  SGCells(Grid, 0, 0, "Типовая структура");
  SGCells(Grid, 0, 1, "ТФЕ 1");
  SGCells(Grid, 0, 2, "ТФЕ 2");
  SGCells(Grid, 0, 3, "ТФЕ 3");
  Grid->ColWidths[0] = 300;
  Grid->Rows[1]->Clear();
}

void __fastcall TfmViewPredicateTrackConstructor::FormShow(TObject *Sender)
{
  StringInit(sgBase);
  StringInit(sgResult);
  ResultTrack = Zadacha->TrackCreator->Items[0];
  RefreshGrids();
}

void TfmViewPredicateTrackConstructor::RefreshList()
{
  Zadacha->TrackCreator->GetAllTrack(ResultTrack, f_Arr);
}

//---------------------------------------------------------------------------
void TfmViewPredicateTrackConstructor::InsertKnotToGrid(TStringGrid *Grid,
  TPredicateScannerItemKnot* AKnot)
{
   AnsiString RusName = "";
   int m_type = AKnot->TypeKnot;
   switch(m_type)
   {
     case 1:
       RusName = "Раб. оперция";
	   break;

     case 2:
       RusName = "Парал. рабочая И";
       break;

     case 3:
       RusName = "Парал. рабочая ИЛИ";
       break;

     case 4:
       RusName = "Контроль раб-ти";
       break;

     case 5:
       RusName = "Функ-ый контроль";
       break;

     case 6:
       RusName = "Развилка";
       break;

     case 7:
       RusName = "Проверка условия (к.р.)";
       break;

     case 8:
       RusName = "Цикл WHILE DO";
       break;

     case 9:
       RusName = "Цикл DO WHILE DO";
       break;

	 case 10:
       RusName = "Цикл DO WHILE DO (с ФК)";
       break;

     case 11:
       RusName = "Проверка условия";
       break;

     case 13:
       RusName = "Послед. рабочая";
       break;
   }

   int id1 = AKnot->TFE_ID1;
   int id2 = AKnot->TFE_ID2;
   int id3 = AKnot->TFE_ID3;
   if ( (id1 > 0) || (id2 > 0) || (id3 > 0) )
   {
      if (m_type == 13)
      {
         if ( (id1 < 0) || (id2 < 0) )
         {
           RusName = "Раб. оперция";
           if (id2 > 0)
           {
              id1 = id2;
              id2 = 0;
           }
         }
      }
      DoInsertToGrid(Grid, AKnot, RusName, id1, id2, id3);
   }

}

void TfmViewPredicateTrackConstructor::DoInsertToGrid(TStringGrid *Grid,
  TPredicateScannerItemKnot* AKnot, AnsiString ATFSName, int AID1, int AID2, int AID3 )
{
  int row;
  if (Grid->Cells[0][1].Length())
      SGInsertRow(Grid, Grid->RowCount);
  row = Grid->RowCount - 1;
  Grid->Objects[0][row] = (TObject*)AKnot;
  SGCells(Grid, row, 0, ATFSName);
  if(AID1 > 0)
    SGCells(Grid, row, 1, IntToStr(AID1));
  else
    SGCells(Grid, row, 1, "");
  if(AID2 > 0)
    SGCells(Grid, row, 2, IntToStr(AID2));
  else
    SGCells(Grid, row, 2, "");
  if(AID3 > 0)
    SGCells(Grid, row, 3, IntToStr(AID3));
  else
    SGCells(Grid, row, 3, "");
}


void TfmViewPredicateTrackConstructor::RefreshStringGridBase()
{
  TPredicateScannerItemKnot* Knot;
  TPredicateTrackCreatorItem* BaseTrack;
  StringInit(sgBase);
  BaseTrack = Zadacha->TrackCreator->BaseTrack;
  for(int i = 0; i <= BaseTrack->Count - 1; i++)
  {
     Knot = BaseTrack->Items[i];
	 if (!ResultTrack->FindKnot(Knot))
       InsertKnotToGrid(sgBase, Knot);
  }
}

void TfmViewPredicateTrackConstructor::RefreshStringGridResult()
{
  StringInit(sgResult);
  for(int i = 0; i <= ResultTrack->Count - 1; i++)
    InsertKnotToGrid(sgResult, ResultTrack->Items[i]);
}



/*
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
       SGCellsByName(sgAlternative, 1 + i,  "СОСТАВ", AI->SOSTAV);
       SGCellsByName(sgAlternative, 1 + i, "B", float_2_string(AI->B, 6));
       SGCellsByName(sgAlternative, 1 + i, "T", float_2_string(AI->T, 6));
       SGCellsByName(sgAlternative, 1 + i, "V", float_2_string(AI->V, 6));
    }
  }

*/
void __fastcall TfmViewPredicateTrackConstructor::FormCreate(
      TObject *Sender)
{
  f_Arr = new TDynamicArray;
  f_Stack = new TDynamicArray;
}
//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructor::FormDestroy(
      TObject *Sender)
{
  delete f_Arr;
  delete f_Stack;
}

bool TfmViewPredicateTrackConstructor::CanSelect(TPredicateScannerItemKnot* AKnot)
{
  return  f_Arr->Find(AKnot);
}
//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructor::sgBaseDrawCell(
      TObject *Sender, int ACol, int ARow, TRect &Rect,
      TGridDrawState State)
{
/* stas19  в XE10 отрисовка должна быть другой
  bool Bold_Row = CanSelect((TPredicateScannerItemKnot*)sgBase->Objects[0][ARow]);
  if ( ARow == 0 )
  {
     if (State.Contains(gdFixed))
     {
        TFontStyles FS = sgBase->Canvas->Font->Style;
        FS<<fsBold;
        sgBase->Canvas->Font->Style = FS;
        sgBase->Canvas->FillRect(Rect);
        TRect NR  = Rect;
        NR.Left =  NR.Left + 2;
		if (ACol > 0)
          DrawText(sgBase->Canvas->Handle, sgBase->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
        else
          DrawText(sgBase->Canvas->Handle, sgBase->Cells[ACol][ARow].c_str(), -1, &NR, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
     }
     return;
  }

  if (ACol == 0)
  {
     TFontStyles FS = sgBase->Canvas->Font->Style;
     if (Bold_Row)
       FS<<fsBold;
     else
       FS>>fsBold<<fsItalic;
     sgBase->Canvas->Font->Style = FS;
     sgBase->Canvas->FillRect(Rect);
     TRect NR  = Rect;
     NR.Left =  NR.Left + 2;
     DrawText(sgBase->Canvas->Handle, sgBase->Cells[ACol][ARow].c_str(), -1, &NR, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
  }

  if ( (ACol == 1) || (ACol == 2) || (ACol == 3) )
  {
     TFontStyles FS = sgBase->Canvas->Font->Style;
     if (Bold_Row)
       FS<<fsBold;
     else
       FS>>fsBold<<fsItalic;
     sgBase->Canvas->Font->Style = FS;
     sgBase->Canvas->FillRect(Rect);
     DrawText(sgBase->Canvas->Handle, sgBase->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
  }
  */

}
//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructor::acDownUpdate(
      TObject *Sender)
{
   TPredicateScannerItemKnot* K = (TPredicateScannerItemKnot*)sgBase->Objects[0][sgBase->Row];
   dynamic_cast<TAction*>(Sender)->Enabled = CanSelect(K);
}
//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructor::acDownExecute(
      TObject *Sender)
{
  TPredicateScannerItemKnot* K = (TPredicateScannerItemKnot*)sgBase->Objects[0][sgBase->Row];
  if (K)
  {
    ResultTrack->PushKnot(K);
    f_Stack->Append(K);
    FillNegativeDecidedKnot();
    RefreshGrids();
  }
}
//---------------------------------------------------------------------------

void TfmViewPredicateTrackConstructor::RefreshGrids()
{
  RefreshList();
  RefreshStringGridBase();
  RefreshStringGridResult();
}

void __fastcall TfmViewPredicateTrackConstructor::acUpUpdate(
      TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = f_Stack->Count > 0;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructor::acUpExecute(
      TObject *Sender)
{
   f_Stack->InitStack();
   TPredicateScannerItemKnot* K = (TPredicateScannerItemKnot*)f_Stack->Pop();
   ResultTrack->DeleteKnot(K);
   DeleteBadKnot();
   RefreshGrids();
}
//---------------------------------------------------------------------------
void TfmViewPredicateTrackConstructor::FillNegativeDecidedKnot()
{
  TPredicateScannerItemKnot* Knot;
  TDynamicArray *D = new TDynamicArray;
  while(true)
  {
    Zadacha->TrackCreator->GetNegativeDecidedKnot(ResultTrack, D);
    if(!D->Count) break;
    for(int i = 0; i <= D->Count - 1; i++)
    {
      Knot = static_cast<TPredicateScannerItemKnot*>(D->Items[i]);
      ResultTrack->PushKnot(Knot);
    }
  }
  delete D;
}

void TfmViewPredicateTrackConstructor::DeleteBadKnot()
{
  TPredicateScannerItemKnot* Knot;
  TDynamicArray *D = new TDynamicArray;
  while(true)
  {
    ResultTrack->GetBadKnot(D);
    if(!D->Count) break;
    for(int i = 0; i <= D->Count - 1; i++)
    {
      Knot = static_cast<TPredicateScannerItemKnot*>(D->Items[i]);
      ResultTrack->DeleteKnot(Knot);
    }
  }
  delete D;
}


void __fastcall TfmViewPredicateTrackConstructor::acOkExecute(
      TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructor::acCancelExecute(
      TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructor::acOkUpdate(
      TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled =
    ResultTrack->Count == Zadacha->TrackCreator->BaseTrack->Count;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructor::sgBaseDblClick(
      TObject *Sender)
{
  TPredicateScannerItemKnot* K = (TPredicateScannerItemKnot*)sgBase->Objects[0][sgBase->Row];
  if( CanSelect(K) )
    acDownExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructor::sgResultDrawCell(
      TObject *Sender, int ACol, int ARow, TRect &Rect,
      TGridDrawState State)
{
/* stas19  в XE10 отрисовка должна быть другой
  if ( (ARow == 0) )
  {
     if (State.Contains(gdFixed))
     {
        TFontStyles FS = sgResult->Canvas->Font->Style;
        FS<<fsBold;
        sgResult->Canvas->Font->Style = FS;
        sgResult->Canvas->FillRect(Rect);
        TRect NR  = Rect;
        NR.Left =  NR.Left + 2;
        if (ACol > 0)
          DrawText(sgResult->Canvas->Handle, sgResult->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
        else
          DrawText(sgResult->Canvas->Handle, sgResult->Cells[ACol][ARow].c_str(), -1, &NR, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
     }
     return;
  }
  if (ACol == 0)
  {
	 sgResult->Canvas->FillRect(Rect);
     TRect NR  = Rect;
     NR.Left =  NR.Left + 2;
     DrawText(sgResult->Canvas->Handle, sgResult->Cells[ACol][ARow].c_str(), -1, &NR, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
  }

  if ( (ACol == 1) || (ACol == 2) || (ACol == 3) )
  {
	 sgResult->Canvas->FillRect(Rect);
	 DrawText(sgResult->Canvas->Handle, sgResult->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
  }
  */
}
//---------------------------------------------------------------------------

