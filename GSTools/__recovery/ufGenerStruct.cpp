//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufGenerStruct.h"
#include "uMakerTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmToolGenerStruct *fmToolGenerStruct;
TfrmMain *pMain;
//---------------------------------------------------------------------------
__fastcall TfmToolGenerStruct::TfmToolGenerStruct(TComponent* Owner)
	: TForm(Owner)
{
	m_ListWorkOper = new TList;
	InitWorkTablesHeader();

	InitWorkAlterTablesHeader();

	m_ListCheckOper = new TList;
	InitCheckTablesHeader();

	InitCheckAlterTablesHeader();
}
//---------------------------------------------------------------------------

bool ShowToolGenerStruct(TfrmMain *frmMain)
{
  pMain = frmMain;
  TfmToolGenerStruct *fmToolGenerStruct;
  Application->CreateForm(__classid(TfmToolGenerStruct), &fmToolGenerStruct);
  bool res = fmToolGenerStruct->ShowModal() == mrOk;
  fmToolGenerStruct->Release();
  return res;
}
void __fastcall TfmToolGenerStruct::acptBtnClick(TObject *Sender)
{
  TBaseWorkShape* WS;
  TParamAlternativeItem* PA;
  TMakerTFS* Maker = new TMakerTFS(pMain->MainList, pMain->Grid, &pMain->ShapeCopy,
	pMain->f_CurrIDShape, pMain->f_CurrIDBlock, pMain->f_CurrIDLine);
  try
  {
	Maker->SetCurrentLevel(pMain->LevelController->ParentShapeID);

	int m_Last_id = pMain->MainList->TFEMaxID; //Это последний номер тфе

	WS = Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative); // добавление паралеьной РО
	//добавление параметрической альтернативы для первой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 1); // этот номер надо расчитывать
	PA->B = 10;
	PA->T = 100;
	PA->V = 1000;

	//добавление параметрической альтернативы для втрой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 30;
	PA->T = 300;
	PA->V = 3000;

	//добавление еще одной параметрической альтернативы для втрой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 50;
	PA->T = 500;
	PA->V = 5000;


	//устанавливаем текущий уровень для первой ТФЕ из добавленной ТФС
	Maker->SetCurrentLevel(m_Last_id + 1);
	Maker->AddTFSToCurrentLevel(6, pMain->f_IdAlternative, pMain->f_NumAlternative); // добавление Функ-ый контроль


	Maker->SetCurrentLevel(2);
	Maker->AddTFSToCurrentLevel(4, pMain->f_IdAlternative, pMain->f_NumAlternative); // добавление паралеьной РО

	TAltSelectorItem* Item = pMain->f_AltSelector->CreateNewAlternateID(pMain->LevelController->ParentShapeID, 1);
	 if ( !pMain->MainList->CreateAlternate(WS, WS, Item->ID, Item->Num) )
			pMain->MainList->AddAlternate(Item->ID, Item->Num);
	pMain->f_AlternateController->AddAlternateItem(WS, WS, Item->ID, Item->Num,
	   0, 0);

	Maker->SetCurrentLevel(0);
	pMain->Grid->PrepareLevel();  // тока один раз рисуем новый уровень алтернатив
	Maker->AddTFSToCurrentLevel(4, Item->ID, Item->Num); // добавление паралеьной РО

   pMain->f_CurrIDBlock = Maker->CurrIDBlock;
   pMain->f_CurrIDShape = Maker->CurrIDShape;
   pMain->f_CurrIDLine = Maker->CurrIDLine;
  }
  catch(...){}
  delete Maker;

	pMain->MainList->ClearNodeTypeCreate();
	pMain->ListChange();
	pMain->AlternateListChange();
	pMain->Grid->PrepareLevelOnOffset();
	pMain->Grid->PreparePaint();
	pMain->f_AlternateController->CoordinateCorrect();
	pMain->SetNewPolygon();

//	 SetNewPosition();
}
//---------------------------------------------------------------------------

void TfmToolGenerStruct::InitWorkTablesHeader()
{
	sgWorkOperation->ColCount    = 5;
	sgWorkOperation->RowCount    = 2;
	sgWorkOperation->FixedRows   = 1;
	sgWorkOperation->Cells[0][0] = "№";
	sgWorkOperation->Cells[1][0] = "НАЗВАНИЕ 1-ОЙ АЛЬТЕР.";
	sgWorkOperation->Cells[2][0] = "КОЛ-ВО АЛЬТЕРНАТИВ";
	sgWorkOperation->Cells[3][0] = "ПРЕДШЕСТВ. ОПЕРАЦИИ";
	sgWorkOperation->Cells[4][0] = "ИНДИВИД. КОНТРОЛЬ";

	sgWorkOperation->ColWidths[0] = 40;
	sgWorkOperation->ColWidths[1] = 190;
	sgWorkOperation->ColWidths[2] = 190;
	sgWorkOperation->ColWidths[3] = 185;
	sgWorkOperation->ColWidths[4] = 175;
}

void TfmToolGenerStruct::InitWorkAlterTablesHeader()
{
	sgWorkAlterOperation->ColCount    = 5;
	sgWorkAlterOperation->RowCount    = 2;
	sgWorkAlterOperation->FixedRows   = 1;
	sgWorkAlterOperation->Cells[0][0] = "№";
	sgWorkAlterOperation->Cells[1][0] = "НАЗВАНИЕ";
	sgWorkAlterOperation->Cells[2][0] = "ВЕРОЯТНОСТЬ B";
	sgWorkAlterOperation->Cells[3][0] = "ВРЕМЯ ВЫПОЛНЕНИЯ T";
	sgWorkAlterOperation->Cells[4][0] = "ЗАТРАТЫ НА ВЫПОЛНЕНИЕ V";

	sgWorkAlterOperation->ColWidths[0] = 40;
	sgWorkAlterOperation->ColWidths[1] = 190;
	sgWorkAlterOperation->ColWidths[2] = 190;
	sgWorkAlterOperation->ColWidths[3] = 185;
	sgWorkAlterOperation->ColWidths[4] = 175;
}


void TfmToolGenerStruct::InitCheckTablesHeader()
{
	sgControlOperation->ColCount    = 4;
	sgControlOperation->RowCount    = 2;
	sgControlOperation->FixedRows   = 1;
	sgControlOperation->Cells[0][0] = "№";
	sgControlOperation->Cells[1][0] = "НАЗВАНИЕ 1-ОЙ АЛЬТЕР.";
	sgControlOperation->Cells[2][0] = "КОЛ-ВО АЛЬТЕРНАТИВ";
	sgControlOperation->Cells[3][0] = "КОНТРОЛЬ. ОПЕРАЦИИ";

	sgControlOperation->ColWidths[0] = 40;
	sgControlOperation->ColWidths[1] = 190;
	sgControlOperation->ColWidths[2] = 190;
	sgControlOperation->ColWidths[3] = 185;
}

void TfmToolGenerStruct::InitCheckAlterTablesHeader()
{
	sgControlAlterOperation->ColCount    = 5;
	sgControlAlterOperation->RowCount    = 2;
	sgControlAlterOperation->FixedRows   = 1;
	sgControlAlterOperation->Cells[0][0] = "№";
	sgControlAlterOperation->Cells[1][0] = "НАЗВАНИЕ";
	sgControlAlterOperation->Cells[2][0] = "ВЕРОЯТНОСТЬ П_11";
	sgControlAlterOperation->Cells[3][0] = "ВЕРОЯТНОСТЬ П_00";
	sgControlAlterOperation->Cells[4][0] = "ВЕРОЯТНОСТЬ РАБОТОС-ТИ";

	sgControlAlterOperation->ColWidths[0] = 40;
	sgControlAlterOperation->ColWidths[1] = 190;
	sgControlAlterOperation->ColWidths[2] = 230;
	sgControlAlterOperation->ColWidths[3] = 230;
	sgControlAlterOperation->ColWidths[4] = 245;
}

void TfmToolGenerStruct::RefillWorkGrid()
{
	for(int i =0; i< sgWorkOperation->RowCount; i++)
		sgWorkOperation->Rows[i+1]->Clear();

	sgWorkOperation->RowCount    = m_ListWorkOper->Count+1;
	WorkOperation* WO;
	for (int i = 0; i <= m_ListWorkOper->Count - 1; i++ )
	{
		WO = static_cast<WorkOperation*>(m_ListWorkOper->Items[i]);
		sgWorkOperation->Cells[0][i+1] = i+1;
		sgWorkOperation->Cells[1][i+1] = WO->m_sNameFirstAlt;
		sgWorkOperation->Cells[2][i+1] = WO->m_nNumAlt;

		AnsiString  sMAsAlt ="";
		for (int j = 0; j < WO->m_nNumMasBefore; j++)
		{
			sMAsAlt += IntToStr(WO->m_nMasBefore[j]) + " ";
		}
		sgWorkOperation->Cells[3][i+1] = sMAsAlt;
		sgWorkOperation->Cells[4][i+1] = WO->m_bAloneControl ? "ДА" : "НЕТ";
	}
}

void __fastcall TfmToolGenerStruct::addWorkBtnClick(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
	{
		WorkOperation* Item = new WorkOperation;

		Item->m_nID = m_ListWorkOper->Count+1;
		Item->m_nNumAlt = 0;
		Item->m_sNameFirstAlt = "";

		Item->m_nNumMasBefore = 0;
	/*	TStringList * list = new TStringList();
		list->DelimitedText = Trim(editBeforeOperation->Text);
		list->Delimiter = ' ';
		for (int i=0; i < list->Count; i++)
		{
			Item->m_nNumMasBefore++;
			Item->m_nMasBefore[i] = StrToInt(list->Strings[i]);
		}
		Item->m_bAloneControl = CheckBoxAloneCheck->Checked;      */

		m_ListWorkOper->Add(Item);
		RefillWorkGrid();
	}
	else
	{
  /*		WorkAlternativ * Item = WorkAlternativ;
		Item->m_nID = m_listWorkAlternativ->Count+1;
		Item->

	   m_listWorkAlternativ */
	}

}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl2Change(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
		PageControl3->ActivePageIndex = 0;
	else if (PageControl2->ActivePageIndex == 1)
		PageControl3->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------


void __fastcall TfmToolGenerStruct::PageControl3Change(TObject *Sender)
{
	if (PageControl3->ActivePageIndex == 0)
		PageControl2->ActivePageIndex = 0;
	else if (PageControl3->ActivePageIndex == 1)
		PageControl2->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl1Change(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
		PageControl4->ActivePageIndex = 0;
	else if (PageControl1->ActivePageIndex == 1)
		PageControl4->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl4Change(TObject *Sender)
{
	if (PageControl4->ActivePageIndex == 0)
		PageControl1->ActivePageIndex = 0;
	else if (PageControl4->ActivePageIndex == 1)
		PageControl1->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------

