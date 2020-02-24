//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufmTrackShow.h"
#include "uCommonGraph.h"
#include "ufmViewPredicateTrackConstructor.h"
#include "ufmViewPredicateTrackConstructorAuto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmTrackShow *fmTrackShow;

void CreateTrackShow(TZadacha* AZadacha, AnsiString AText)
{
   fmTrackShow = new TfmTrackShow(Application);
   fmTrackShow->Zadacha = AZadacha;
   fmTrackShow->REPredicate->Text = AText;
   fmTrackShow->ShowModal();
   fmTrackShow->Release();
}
//---------------------------------------------------------------------------
__fastcall TfmTrackShow::TfmTrackShow(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfmTrackShow::StringInit()
{
  sgModel->RowCount    = 1;
  sgModel->RowCount    = 2;
  sgModel->FixedRows   = 1;

  SGCells(sgModel, 0, 0, "Типовая структура");
  SGCells(sgModel, 0, 1, "ТФЕ 1");
  SGCells(sgModel, 0, 2, "ТФЕ 2");
  SGCells(sgModel, 0, 3, "ТФЕ 3");
  sgModel->ColWidths[0] = 300;
  sgModel->Rows[1]->Clear();
}

void __fastcall TfmTrackShow::FormShow(TObject *Sender)
{
  //StringInit();
  FillStringGrid();
}
//---------------------------------------------------------------------------

void TfmTrackShow::FillStringGrid()
{
  TPredicateScannerItemKnot* Item;
  StringInit();
  Zadacha->Scanner->Scan(AnsiString(REPredicate->Text).c_str());
  String Err = Zadacha->Scanner->Error;
  if(!Err.Length())
    Err = Zadacha->CheckTrack();
  if(Err.Length() > 0)
	Application->MessageBox(Err.c_str(), _T("Ошибка!"), MB_ICONWARNING);

  if(Err.Length() == 0)
  {
    for(int i = 0; i <= Zadacha->Scanner->CountKnot - 1; i++ )
    {
     Item = Zadacha->Scanner->ItemsKnot[i];
     InsertKnotToGrid(Item);
    }
  }
}


void TfmTrackShow::InsertKnotToGrid(TPredicateScannerItemKnot* AKnot)
{
   String RusName = "";
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
      DoInsertToGrid(RusName, id1, id2, id3);
   }

}

void TfmTrackShow::DoInsertToGrid(String ATFSName, int AID1, int AID2, int AID3 )
{
  if (sgModel->Cells[0][1].Length())
    SGInsertRow(sgModel, sgModel->RowCount);
  int row = sgModel->RowCount - 1;
  SGCells(sgModel, row, 0, ATFSName);

  if(AID1 > 0)
    SGCells(sgModel, row, 1, IntToStr(AID1));
  else
    SGCells(sgModel, row, 1, "");
  if(AID2 > 0)
    SGCells(sgModel, row, 2, IntToStr(AID2));
  else
    SGCells(sgModel, row, 2, "");
  if(AID3 > 0)
    SGCells(sgModel, row, 3, IntToStr(AID3));
  else
    SGCells(sgModel, row, 3, "");

}

void __fastcall TfmTrackShow::sgModelDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
/* Этот код был в пятом билдере
  String s = sgModel->Cells[ACol][ARow];

  if (ARow == 0) return; //уже добавил это строку когда експерементировал в XE10
  if ( (ARow == 0) )
  {
	 if (State.Contains(gdFixed))
	 {
		TFontStyles FS = sgModel->Canvas->Font->Style;
		FS<<fsBold;
		sgModel->Canvas->Font->Style = FS;
		sgModel->Canvas->FillRect(Rect);
		DrawText(sgModel->Canvas->Handle, s.c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
	 }
  }
  if (ACol == 0)
  {
	 sgModel->Canvas->FillRect(Rect);
	 TRect NR  = Rect;
	 NR.Left =  NR.Left + 2;
	 DrawText(sgModel->Canvas->Handle, s.c_str(), -1, &NR, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
  }


  if ( (ACol == 1) || (ACol == 2) || (ACol == 3) )
  {
	 sgModel->Canvas->FillRect(Rect);
	 DrawText(sgModel->Canvas->Handle, s.c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
  }
  конец старого кода
  */

/* код для XE10
// Если это заголовок
      if (State.Contains(gdFixed))
      {
		  sgModel->Canvas->Brush->Color = clBtnFace;
		  sgModel->Canvas->Font->Color = clWindowText;
		  sgModel->Canvas->FillRect(Rect);
		  Frame3D(sgModel->Canvas, Rect,
				  clBtnHighlight, clBtnShadow, 1);
	  }

	  // если ячейка выделена
	  else if (State.Contains(gdSelected))
	  {
		  sgModel->Canvas->Brush->Color = clHighlight;
		  sgModel->Canvas->Font->Color = clHighlightText;
		  sgModel->Canvas->FillRect(Rect);
	  }

	  // закрашиваем ячейку (2, 2)
	  else if (ACol == 2 && ARow == 2)
	  {
		  sgModel->Canvas->Brush->Color = clBlue;
		  sgModel->Canvas->Font->Color = clRed;
		  sgModel->Canvas->FillRect(Rect);
	  }

	  // Для всех остальных ячеек
	  else
	  {
		  sgModel->Canvas->Brush->Color = sgModel->Color;
		  sgModel->Canvas->Font->Color = sgModel->Font->Color;
		  sgModel->Canvas->FillRect(Rect);
	  }

	  String text = sgModel->Cells[ACol][ARow];
	  sgModel->Canvas->TextRect(Rect, Rect.Left, Rect.Top, text);
      */
}
//---------------------------------------------------------------------------

void __fastcall TfmTrackShow::acTrackAcceptExecute(TObject *Sender)
{
  Zadacha->Scanner->Scan(AnsiString(REPredicate->Text).c_str());
  String Err = Zadacha->Scanner->Error;
  if(!Err.Length())
	Err = Zadacha->AcceptTrackFromScanner();
  if(Err.Length() > 0)
	Application->MessageBox(Err.c_str(), _T("Ошибка!"), MB_ICONWARNING);
  else
    Close();

}
//---------------------------------------------------------------------------

void __fastcall TfmTrackShow::acTrackCheckExecute(TObject *Sender)
{
  Zadacha->Scanner->Scan(AnsiString(REPredicate->Text).c_str());
  String Err = Zadacha->Scanner->Error;
  if(!Err.Length())
	Err = Zadacha->CheckTrack();
  if(Err.Length() > 0)
	Application->MessageBox(Err.c_str(), _T("Ошибка!"), MB_ICONWARNING);

}
//---------------------------------------------------------------------------

void __fastcall TfmTrackShow::acCancelExecute(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TfmTrackShow::acCreateManualExecute(TObject *Sender)
{
  Zadacha->TrackCreator->ClearTrack();
  Zadacha->TrackCreator->CreateItem();
  fmViewPredicateTrackConstructor = new TfmViewPredicateTrackConstructor(Application);
  fmViewPredicateTrackConstructor->Zadacha = Zadacha;
  if (fmViewPredicateTrackConstructor->ShowModal() == mrOk )
  {
    REPredicate->Text = fmViewPredicateTrackConstructor->ResultTrack->Text;
    FillStringGrid();
  }
  fmViewPredicateTrackConstructor->Release();
}
//---------------------------------------------------------------------------



void __fastcall TfmTrackShow::PageControlChange(TObject *Sender)
{
  if(PageControl->ActivePage == tsTable)
    FillStringGrid();
}
//---------------------------------------------------------------------------


void __fastcall TfmTrackShow::acCreateAutoExecute(TObject *Sender)
{
  fmViewPredicateTrackConstructorAuto = new TfmViewPredicateTrackConstructorAuto(Application);
  fmViewPredicateTrackConstructorAuto->Zadacha = Zadacha;
  if (fmViewPredicateTrackConstructorAuto->ShowModal() == mrOk )
  {
    REPredicate->Text = fmViewPredicateTrackConstructorAuto->REPredicate->Text;
    FillStringGrid();
  }
  fmViewPredicateTrackConstructorAuto->Release();

}
//---------------------------------------------------------------------------





