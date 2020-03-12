//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufGenerStruct.h"
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

	currWorkAlter = NULL;
	currWorkOper= NULL;
	currCheckAlter= NULL;
	currCheckOper= NULL;
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
	m_ListOut = new TList;
	CheckOperation* CO;
	//Отсавляем только групповой контроль
	for (int i = 0; i < m_ListCheckOper->Count; i++)
	{
		 CO = static_cast<CheckOperation*>(m_ListCheckOper->Items[i]);
		 if (CO->m_ListCheckWork->Count==1) {
			m_ListCheckOper->Delete(i--);
		 }
	}

	WorkOperation* WO, *WOB;
	//Выносим внешние зависимости
	for (int i = 0; i < m_ListCheckOper->Count; i++)
	{
		 CO = static_cast<CheckOperation*>(m_ListCheckOper->Items[i]);   //Группа контроля
		 for (int j = 0; j < CO->m_ListCheckWork->Count; j++)
		 {
		   WO =  static_cast<WorkOperation*>(CO->m_ListCheckWork->Items[j]); //Рабочая операция
		   bool bGlobal = true;
		   for (int l = 0; l < WO->m_ListWorkBefore->Count; l++)
		   {
			  WOB =  static_cast<WorkOperation*>(WO->m_ListWorkBefore->Items[l]); //Предшевст. раюб операция
			  for (int k = 0; k < CO->m_ListCheckWork->Count; k++) {
			  WorkOperation* WWO = static_cast<WorkOperation*>(CO->m_ListCheckWork->Items[k]);
				  if (WOB->m_nID == WWO->m_nID) {
					 bGlobal = false;
					 break;
				  }
			  }
			  if (bGlobal) {
				CO->m_ListOperationBefore->Add(WOB);
				WO->m_ListWorkBefore->Delete(l--);
			  }
		   }
		 }
	}

  /*-----*/
  TBaseWorkShape* WS;
  TParamAlternativeItem* PA;
  TMakerTFS* Maker = new TMakerTFS(pMain->MainList, pMain->Grid, &pMain->ShapeCopy,
	pMain->f_CurrIDShape, pMain->f_CurrIDBlock, pMain->f_CurrIDLine);
  try
  {
	Maker->SetCurrentLevel(pMain->LevelController->ParentShapeID);

	int m_Last_id = pMain->MainList->TFEMaxID; //Это последний номер тфе

	int idx =1;
	WorkOperation* WO;
	WorkAlternativ* WA;
	TList* ll = new TList;

	for (int i = 0; i < m_ListOut->Count; i++)
	{
		BasisOperation* BS = static_cast<BasisOperation*>(ll->Items[i]);
		BS->PutOnWork(Maker);
    }

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
	sgWorkOperation->Cells[4][0] = "КОНТРОЛЬ";

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
	sgControlOperation->Cells[3][0] = "КОНТРОЛИР. ОПЕРАЦИИ";

	sgControlOperation->ColWidths[0] = 40;
	sgControlOperation->ColWidths[1] = 190;
	sgControlOperation->ColWidths[2] = 190;
	sgControlOperation->ColWidths[3] = 185;
}

void TfmToolGenerStruct::InitCheckAlterTablesHeader()
{
	sgControlAlterOperation->ColCount    = 6;
	sgControlAlterOperation->RowCount    = 2;
	sgControlAlterOperation->FixedRows   = 1;
	sgControlAlterOperation->Cells[0][0] = "№";
	sgControlAlterOperation->Cells[1][0] = "НАЗВАНИЕ";
	sgControlAlterOperation->Cells[2][0] = "ВЕРОЯТНОСТЬ K_11";
	sgControlAlterOperation->Cells[3][0] = "ВЕРОЯТНОСТЬ K_00";
	sgControlAlterOperation->Cells[4][0] = "СР. ВРЕМЯ ВЫПОЛН. T_f";
	sgControlAlterOperation->Cells[4][0] = "СР. ЗАТРАТЫ НА ВЫПОЛН. V_f";

	sgControlAlterOperation->ColWidths[0] = 40;
	sgControlAlterOperation->ColWidths[1] = 190;
	sgControlAlterOperation->ColWidths[2] = 230;
	sgControlAlterOperation->ColWidths[3] = 230;
	sgControlAlterOperation->ColWidths[4] = 250;
	sgControlAlterOperation->ColWidths[5] = 250;
}

void TfmToolGenerStruct::RefillWorkGrid()
{
	for(int i =0; i< sgWorkOperation->RowCount; i++)
		sgWorkOperation->Rows[i+1]->Clear();

	if (m_ListWorkOper->Count==0)
	{
		sgWorkOperation->RowCount	=   2;
		return;
	}

	sgWorkOperation->RowCount    = m_ListWorkOper->Count+1;
	WorkOperation* WO;
	for (int i = 0; i <= m_ListWorkOper->Count - 1; i++ )
	{
		WO = static_cast<WorkOperation*>(m_ListWorkOper->Items[i]);
		sgWorkOperation->Cells[0][i+1] = WO->m_nID;

		if (WO->m_ListWorkAlter && WO->m_ListWorkAlter->Count>0)
			sgWorkOperation->Cells[1][i+1] = static_cast<WorkAlternativ*>(WO->m_ListWorkAlter->Items[0])->m_sName;
		else
			sgWorkOperation->Cells[1][i+1] = "-";

		sgWorkOperation->Cells[2][i+1] = IntToStr(WO->m_ListWorkAlter->Count);
		AnsiString  sMAsAlt ="-";
		if (WO->m_ListWorkBefore->Count >0)
		{
			WorkOperation* WOT;
			sMAsAlt ="";
			for (int j = 0; j < WO->m_ListWorkBefore->Count; j++)
			{
				WOT =  static_cast<WorkOperation*>(WO->m_ListWorkBefore->Items[j]);
				if (WOT && WOT->m_nID>0) {
					sMAsAlt += IntToStr(WOT->m_nID) + " ";
				}
				else
					WO->m_ListWorkBefore->Delete(j--);
			}
		}
		sgWorkOperation->Cells[3][i+1] = sMAsAlt;
		sgWorkOperation->Cells[4][i+1] = WO->m_pGroupCheck!=NULL || WO->m_pCheckAlone!=NULL ? "ДА" : "НЕТ";
	}
}

void TfmToolGenerStruct::RefillWorkAlterGrid()
{
	for(int i =0; i< sgWorkAlterOperation->RowCount; i++)
		sgWorkAlterOperation->Rows[i+1]->Clear();

	if (!currWorkOper || !currWorkOper->m_ListWorkAlter
	|| currWorkOper->m_ListWorkAlter->Count==0)
	{
	   sgWorkAlterOperation->RowCount = 2;
	   return;
	}

	sgWorkAlterOperation->RowCount    = currWorkOper->m_ListWorkAlter->Count+1;
	WorkAlternativ* WOA;
	for (int i = 0; i <= currWorkOper->m_ListWorkAlter->Count - 1; i++ )
	{
		WOA = static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[i]);
		sgWorkAlterOperation->Cells[0][i+1] = i+1;
		sgWorkAlterOperation->Cells[1][i+1] = WOA->m_sName;
		sgWorkAlterOperation->Cells[2][i+1] = FloatToStrF(WOA->m_dB,ffFixed,3,5);
		sgWorkAlterOperation->Cells[3][i+1] = FloatToStrF(WOA->m_dT,ffFixed,3,5);
		sgWorkAlterOperation->Cells[4][i+1] = FloatToStrF(WOA->m_dV,ffFixed,3,5);
	}
}

void TfmToolGenerStruct::RefillCheckAlterGrid()
{
	for(int i =0; i< sgControlAlterOperation->RowCount; i++)
		sgControlAlterOperation->Rows[i+1]->Clear();

	if (!currCheckOper || !currCheckOper->m_ListCheckAlter
	|| currCheckOper->m_ListCheckAlter->Count==0)
	{
	   sgControlAlterOperation->RowCount = 2;
	   return;
	}

	sgControlAlterOperation->RowCount    = currCheckOper->m_ListCheckAlter->Count+1;
	CheckAlternativ* WOA;
	for (int i = 0; i <= currCheckOper->m_ListCheckAlter->Count - 1; i++ )
	{
		WOA = static_cast<CheckAlternativ*>(currCheckOper->m_ListCheckAlter->Items[i]);
		sgControlAlterOperation->Cells[0][i+1] = i+1;
		sgControlAlterOperation->Cells[1][i+1] = WOA->m_sName;
		sgControlAlterOperation->Cells[2][i+1] = FloatToStrF(WOA->m_dK00,ffFixed,3,5);
		sgControlAlterOperation->Cells[3][i+1] = FloatToStrF(WOA->m_dK11,ffFixed,3,5);
		sgControlAlterOperation->Cells[4][i+1] = FloatToStrF(WOA->m_dTf,ffFixed,3,5);
		sgControlAlterOperation->Cells[5][i+1] = FloatToStrF(WOA->m_dVf,ffFixed,3,5);
	}
}

void TfmToolGenerStruct::RefillCheckGrid()
{
	for(int i =0; i< sgControlOperation->RowCount; i++)
		sgControlOperation->Rows[i+1]->Clear();

	if (m_ListCheckOper->Count==0)
	{
		sgControlOperation->RowCount = 2;
	   	return;
	}

	sgControlOperation->RowCount    = m_ListCheckOper->Count+1;
	CheckOperation* CO;
	for (int i = 0; i <= m_ListCheckOper->Count - 1; i++ )
	{
		CO = static_cast<CheckOperation*>(m_ListCheckOper->Items[i]);
		sgControlOperation->Cells[0][i+1] = CO->m_nID;

		if (CO->m_ListCheckAlter && CO->m_ListCheckAlter->Count>0)
			sgControlOperation->Cells[1][i+1] = static_cast<CheckAlternativ*>(CO->m_ListCheckAlter->Items[0])->m_sName;
		else
			sgControlOperation->Cells[1][i+1] = "-";

		sgControlOperation->Cells[2][i+1] = CO->m_ListCheckAlter->Count;

		AnsiString  sMasCheck ="-";
		if (CO->m_ListCheckWork->Count>0)
		{
			sMasCheck ="";
			CheckOperation* COT;
			for (int j = 0; j < CO->m_ListCheckWork->Count; j++)
			{
				COT = static_cast<CheckOperation*>(CO->m_ListCheckWork->Items[j]);
				if (COT && COT->m_nID>0) {
				  sMasCheck += IntToStr(COT->m_nID) + " ";
				}
				else
				  CO->m_ListCheckWork->Delete(j--);
			}
		}
		sgControlOperation->Cells[3][i+1] = sMasCheck;
	}
}

void __fastcall TfmToolGenerStruct::addWorkBtnClick(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
	{
		WorkOperation* Item = new WorkOperation;

		Item->m_nID = m_ListWorkOper->Count+1;
		Item->m_ListWorkBefore = new TList;
		Item->m_pGroupCheck = NULL;
		Item->m_ListWorkAlter = new TList;
		Item->m_pCheckAlone = NULL;
		m_ListWorkOper->Add(Item);
		RefillWorkGrid();
		if (currWorkOper == NULL)
		{
			InitCurrWorkOper(1);
		}
	}
	else
	{
		WorkAlternativ * ItemA = new WorkAlternativ;

		ItemA->m_nID  = currWorkOper->m_ListWorkAlter->Count+1;
		ItemA->m_sName = "-";
		ItemA->m_dB = 1;
		ItemA->m_dV = 1;
		ItemA->m_dT = 1;

		if(currWorkOper!=NULL)
		{
			currWorkOper->m_ListWorkAlter->Add(ItemA);
			RefillWorkAlterGrid();
			if (currWorkAlter == NULL)
			{
				InitCurrWorkAlter(1);
			}
		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::editWorkBtnClick(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
	{
		TStringList * list = new TStringList();
		list->DelimitedText = Trim(editBeforeOperation->Text);
		list->Delimiter = ' ';
		currWorkOper->m_ListWorkBefore->Clear();
		WorkOperation* WOT;
		for (int i=0; i < list->Count; i++)
		{
			int idx = StrToInt(list->Strings[i]);
			if (idx<=0 || idx>m_ListWorkOper->Count)
				continue;
			WOT = static_cast<WorkOperation*>(m_ListWorkOper->Items[idx-1]);
			currWorkOper->m_ListWorkBefore->Add(WOT);
		}
		RefillWorkGrid();
	}
	else
	{
	   currWorkAlter->m_sName = editNameAlter->Text;
	   currWorkAlter->m_dB = exit_proverka_0_1(editB);
	   currWorkAlter->m_dV = exit_proverka_0_1(editV);
	   currWorkAlter->m_dT = exit_proverka_0_1(editT);
	   RefillWorkAlterGrid();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl2Change(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
	{
		PageControl3->ActivePageIndex = 0;
		InitFieldsWorkOper();
		RefillWorkGrid();
	}
	else if (PageControl2->ActivePageIndex == 1)
	{
		PageControl3->ActivePageIndex = 1;
		InitFieldsWorkAlter();
		RefillWorkAlterGrid();
	}

	EnableWorkControls();
}
//---------------------------------------------------------------------------


void __fastcall TfmToolGenerStruct::PageControl3Change(TObject *Sender)
{
	if (PageControl3->ActivePageIndex == 0)
	{
		PageControl2->ActivePageIndex = 0;
		InitFieldsWorkOper();
		RefillWorkGrid();
	}
	else if (PageControl3->ActivePageIndex == 1)
	{
		PageControl2->ActivePageIndex = 1;
		InitCurrWorkAlter(1);
		InitFieldsWorkAlter();
		RefillWorkAlterGrid();
	}

	EnableWorkControls();
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl1Change(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		PageControl4->ActivePageIndex = 0;
		InitFieldsCheckOper();
		RefillCheckGrid();
	}
	else if (PageControl1->ActivePageIndex == 1)
	{
		PageControl4->ActivePageIndex = 1;
		InitCurrCheckAlter(1);
		InitFieldsCheckAlter();
		RefillCheckAlterGrid();
	}

	EnableCheckControls();
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::PageControl4Change(TObject *Sender)
{
	if (PageControl4->ActivePageIndex == 0)
	{
		PageControl1->ActivePageIndex = 0;
		InitFieldsCheckOper();
		RefillCheckGrid();
	}
	else if (PageControl4->ActivePageIndex == 1)
	{
		PageControl1->ActivePageIndex = 1;
		InitFieldsCheckAlter();
		RefillCheckAlterGrid();
	}

    EnableCheckControls();
}
//---------------------------------------------------------------------------

void TfmToolGenerStruct::EnableWorkControls()
{
	bool bEButt = false;
	bool bEAlter = false;

	if (PageControl2->ActivePageIndex == 0)
	{
		bEButt = (m_ListWorkOper->Count >0) && (currWorkOper!=NULL);
		editBeforeOperation->Enabled = bEButt;
	    addWorkBtn->Enabled = true;
		delWorkBtn->Enabled = bEButt;
		editWorkBtn->Enabled = bEButt;
	}
	else if (PageControl2->ActivePageIndex == 1)
	{
		bEButt = (m_ListWorkOper->Count >0) && (currWorkOper!=NULL);
		addWorkBtn->Enabled = bEButt;

		bEAlter = (currWorkOper!=NULL && currWorkAlter!=NULL);
		editNameAlter->Enabled = bEAlter;
		editV->Enabled = bEAlter;
		editT->Enabled = bEAlter;
		editB->Enabled = bEAlter;
		delWorkBtn->Enabled = bEAlter;
		editWorkBtn->Enabled = bEAlter;
	}
}

void TfmToolGenerStruct::EnableCheckControls()
{
	bool bEButt = false;
	bool bEAlter = false;

	if (PageControl1->ActivePageIndex == 0)
	{
		bEButt = (m_ListCheckOper->Count >0) && (currCheckOper!=NULL);
		editCheckOperation->Enabled = bEButt;
		addControlBtn->Enabled = true;
		delControlBtn->Enabled = bEButt;
		editControlBtn->Enabled = bEButt;
	}
	else if (PageControl1->ActivePageIndex == 1)
	{
		bEButt = (m_ListCheckOper->Count >0) && (currCheckOper!=NULL);
		addControlBtn->Enabled = bEButt;

		bEAlter = (currCheckOper!=NULL && currCheckAlter!=NULL);
		editNameCheckAlter->Enabled = bEAlter;
		editK11->Enabled = bEAlter;
		editK00->Enabled = bEAlter;
		editTf->Enabled = bEAlter;
		editVf->Enabled = bEAlter;
		delControlBtn->Enabled = bEAlter;
		editControlBtn->Enabled = bEAlter;
	}
}

void TfmToolGenerStruct::InitFieldsWorkOper()
{
	if(!currWorkOper)
	{
		editBeforeOperation->Text = "";
		editNumAlter->Text = "";
		editFirstAlterName->Text = "";
		return;
	}

	editBeforeOperation->Text = "";
	if (currWorkOper->m_ListWorkBefore->Count>0)
	{
		WorkOperation* WOT;
		for (int i=0; i < currWorkOper->m_ListWorkBefore->Count; i++)
		{
			WOT = static_cast<WorkOperation*>(currWorkOper->m_ListWorkBefore->Items[i]);
			if (WOT) {
			  editBeforeOperation->Text = editBeforeOperation->Text + IntToStr(WOT->m_nID) + " ";
			}
		}
	}
	else
		editBeforeOperation->Text ="";
	if (currWorkOper->m_ListWorkAlter) {
		editNumAlter->Text = IntToStr(currWorkOper->m_ListWorkAlter->Count);
	}
	else
	  editNumAlter->Text = IntToStr(0);
	if (currWorkOper->m_ListWorkAlter && currWorkOper->m_ListWorkAlter->Count>0)
		editFirstAlterName->Text =  static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[0])->m_sName;
	else
		editFirstAlterName->Text = "-";
}

void TfmToolGenerStruct::InitFieldsCheckOper()
{
	if(!currCheckOper)
	{
		editCheckOperation->Text ="";
		editNumCheckAlter->Text = "";
		editFirstNameAlter->Text = "";
		return;
	}

	editCheckOperation->Text ="";
	if (currCheckOper->m_ListCheckWork->Count)
	{
		WorkOperation* WOT;
		for (int i=0; i < currCheckOper->m_ListCheckWork->Count; i++)
		{
			WOT = static_cast<WorkOperation*>(currCheckOper->m_ListCheckWork->Items[i]);
			if (WOT) {
			  editCheckOperation->Text = editCheckOperation->Text + IntToStr(WOT->m_nID) + " ";
			}
		}
	}
	else
		editCheckOperation->Text ="";
	if (currCheckOper->m_ListCheckAlter) {
		editNumCheckAlter->Text = IntToStr(currCheckOper->m_ListCheckAlter->Count);
	}
	else
	  editNumCheckAlter->Text = IntToStr(0);
	if (currCheckOper->m_ListCheckAlter && currCheckOper->m_ListCheckAlter->Count>0)
		editFirstNameAlter->Text =  static_cast<CheckAlternativ*>(currCheckOper->m_ListCheckAlter->Items[0])->m_sName;
	else
		editFirstNameAlter->Text = "-";
}

void TfmToolGenerStruct::InitFieldsWorkAlter()
{
	if(!currWorkAlter)
	{
		editNameAlter->Text = "";
		editB->Text = "";
		editT->Text = "";
		editV->Text = "";
		return;
	}

   editNameAlter->Text = currWorkAlter->m_sName;
   editB->Text =  FloatToStrF(currWorkAlter->m_dB,ffGeneral,3,5);
   editT->Text =  FloatToStrF(currWorkAlter->m_dT,ffGeneral,3,5);
   editV->Text =  FloatToStrF(currWorkAlter->m_dV,ffGeneral,3,5);
}

void TfmToolGenerStruct::InitFieldsCheckAlter()
{
	if(!currCheckAlter)
	{
		editNameCheckAlter->Text = "";
		editK11->Text = "";
		editK00->Text = "";
		editTf->Text = "";
		editVf->Text = "";
		return;
	}

   editNameCheckAlter->Text = currCheckAlter->m_sName;
   editK11->Text =  FloatToStrF(currCheckAlter->m_dK11,ffGeneral,3,5);
   editK00->Text =  FloatToStrF(currCheckAlter->m_dK00,ffGeneral,3,5);
   editTf->Text =  FloatToStrF(currCheckAlter->m_dTf,ffGeneral,3,5);
   editVf->Text =  FloatToStrF(currCheckAlter->m_dVf,ffGeneral,3,5);
}

//---------------------------------------------------------------------------
void __fastcall TfmToolGenerStruct::addControlBtnClick(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		CheckOperation* Item = new CheckOperation;

		Item->m_nID = m_ListCheckOper->Count+1;
		Item->m_ListCheckAlter = new TList;
		Item->m_ListCheckWork = new TList;
		Item->m_ListOperationBefore = new TList;
		m_ListCheckOper->Add(Item);
		RefillCheckGrid();
		if (currCheckOper == NULL)
		{
			InitCurrCheckOper(1);
		}
	}
	else
	{
		CheckAlternativ * ItemA = new CheckAlternativ;

		ItemA->m_nID = currCheckOper->m_ListCheckAlter->Count+1;
		ItemA->m_sName = "-";
		ItemA->m_dK00 = 1;
		ItemA->m_dK11 = 1;
		ItemA->m_dTf = 1;
		ItemA->m_dVf = 1;

		if(currCheckOper!=NULL)
		{
			currCheckOper->m_ListCheckAlter->Add(ItemA);
			RefillCheckAlterGrid();
			if (currCheckAlter == NULL)
			{
				InitCurrCheckAlter(1);
			}
		}

	}
}
//---------------------------------------------------------------------------
void TfmToolGenerStruct::InitCurrWorkOper(int idx)
{
	if (idx>0 && m_ListWorkOper->Count>0) {
	   currWorkOper = static_cast<WorkOperation*>(m_ListWorkOper->Items[idx-1]);
	   InitFieldsWorkOper();
	}
	else
	{
		currWorkOper = NULL;
	}
	EnableWorkControls();
}

void TfmToolGenerStruct::InitCurrWorkAlter(int idx)
{
	if(currWorkOper)
	{
	   if (idx>0 && currWorkOper->m_ListWorkAlter->Count>0)
	   {
			currWorkAlter = static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[idx-1]);
			InitFieldsWorkAlter();
	   }
	   else
	   {
		   currWorkAlter = NULL;
	   }
	}
	else
	{
		currWorkAlter = NULL;
	}
	EnableWorkControls();
}

void TfmToolGenerStruct::InitCurrCheckOper(int idx)
{
	if (idx>0 && m_ListCheckOper->Count>0) {
	   currCheckOper = static_cast<CheckOperation*>(m_ListCheckOper->Items[idx-1]);
	   InitFieldsCheckOper();
	}
	else
	{
		currCheckOper = NULL;
	}
	EnableCheckControls();
}

void TfmToolGenerStruct::InitCurrCheckAlter(int idx)
{
	if(currCheckOper)
	{
	   if (idx>0 && currCheckOper->m_ListCheckAlter->Count>0)
	   {
			currCheckAlter = static_cast<CheckAlternativ*>(currCheckOper->m_ListCheckAlter->Items[idx-1]);
			InitFieldsCheckAlter();
	   }
	   else
	   {
		   currCheckAlter = NULL;
	   }
	}
	else
	{
		currCheckAlter = NULL;
	}
	EnableCheckControls();
}

void __fastcall TfmToolGenerStruct::sgWorkOperationSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
	InitCurrWorkOper(ARow);
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::sgWorkAlterOperationSelectCell(TObject *Sender,
		  int ACol, int ARow, bool &CanSelect)
{
	InitCurrWorkAlter(ARow);
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::sgControlOperationSelectCell(TObject *Sender,
          int ACol, int ARow, bool &CanSelect)
{
		InitCurrCheckOper(ARow);
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::sgControlAlterOperationSelectCell(TObject *Sender,
          int ACol, int ARow, bool &CanSelect)
{
		InitCurrCheckAlter(ARow);
}
//---------------------------------------------------------------------------

int TfmToolGenerStruct::exit_proverka_simb(TEdit *Edit)
{
  if(read_float(AnsiString(Edit->Text).c_str()))
  {
//	Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
 //	Edit->SetFocus();
	return 0;
  }
  return 1;
}

float TfmToolGenerStruct::exit_proverka_0_1(TEdit *Edit)
{
  float i;
 /* if(exit_proverka_simb(Edit)==0)
	return 0;        */


  AnsiString sTmp = StringReplace(Edit->Text, ",", ".",
	   TReplaceFlags() << rfReplaceAll);

  i=atof(sTmp.c_str());

  if(i<0||i>1)
  {
//    Application->MessageBox(_T("Значение должно быть в интервале [0,1]."), _T("Ошибка!"), MB_OK);
  //  Edit->SetFocus();
    return 0 ;
  }

  return i;
}


void __fastcall TfmToolGenerStruct::editControlBtnClick(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		TStringList * list = new TStringList();
		list->DelimitedText = Trim(editCheckOperation->Text);
		list->Delimiter = ' ';

		WorkOperation* WOT;
		if (currCheckOper->m_ListCheckWork->Count == 1) {
		  WOT = static_cast<WorkOperation*>(currCheckOper->m_ListCheckWork->Items[0]);
		  WOT->m_pCheckAlone = NULL;
		}
		currCheckOper->m_ListCheckWork->Clear();

		if (list->Count == 1) {
			int idx = StrToInt(list->Strings[0]);
			if (idx>0 && idx<=m_ListWorkOper->Count)
			{
			  WOT = static_cast<WorkOperation*>(m_ListWorkOper->Items[idx-1]);
			  if (WOT->m_pCheckAlone == NULL) {
				WOT->m_pCheckAlone = currCheckOper;
				currCheckOper->m_ListCheckWork->Add(WOT);
			  }
			  else
			  {
				Application->MessageBox(_T("Индивидуальный контроль данной операции уже осуществляется."), _T("Ошибка!"), MB_OK);
				return;
              }
			}

		}
		else
		{
			for (int i = 0; i < currCheckOper->m_ListCheckWork->Count; i++) {
				WOT = static_cast<WorkOperation*>(m_ListWorkOper->Items[i]);
				WOT->m_pGroupCheck =NULL;
			}
			currCheckOper->m_ListCheckWork->Clear();
			for (int i=0; i < list->Count; i++)
			{
				int idx = StrToInt(list->Strings[i]);
				if (idx<=0 || idx>m_ListWorkOper->Count)
					continue;

				WOT = static_cast<WorkOperation*>(m_ListWorkOper->Items[idx-1]);
				if (WOT->m_pGroupCheck == NULL) {
				   WOT->m_pGroupCheck = currCheckOper;
				   currCheckOper->m_ListCheckWork->Add(WOT);
				}
				else
				{
					Application->MessageBox(_T("Одна из операций уже пренадлежит другой группе контроля."), _T("Ошибка!"), MB_OK);
					return;
                }
			}
		}
		RefillCheckGrid();
		RefillWorkGrid();
	}
	else
	{
	   currCheckAlter->m_sName = editNameCheckAlter->Text;
	   currCheckAlter->m_dK00 = exit_proverka_0_1(editK00);
	   currCheckAlter->m_dK11 = exit_proverka_0_1(editK11);
	   currCheckAlter->m_dTf = exit_proverka_0_1(editTf);
       currCheckAlter->m_dVf = exit_proverka_0_1(editVf);
	   RefillCheckAlterGrid();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::delWorkBtnClick(TObject *Sender)
{
	if (PageControl2->ActivePageIndex == 0)
	{
		WorkOperation* WO;
		for (int i = currWorkOper->m_nID; i < m_ListWorkOper->Count; i++)
		{
		   WO = static_cast<WorkOperation*>(m_ListWorkOper->Items[i]);
		   WO->m_nID --;
		}
		int idx = 1;
		if (m_ListWorkOper->Count>0)
		{
			idx =  currWorkOper->m_nID-1;
			currWorkOper->m_nID = -1;
			m_ListWorkOper->Delete(idx);
		}
		InitCurrWorkOper(idx);
		InitFieldsWorkOper();
		RefillWorkGrid();
        RefillCheckGrid();
	}
	else
	{
		WorkAlternativ* WA;
		if (currWorkOper->m_ListWorkAlter->Count>0)
		{
			for (int i = currWorkAlter->m_nID; i < currWorkOper->m_ListWorkAlter->Count; i++)
			{
			   WA = static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[i]);
			   WA->m_nID --;
			}
			currWorkOper->m_ListWorkAlter->Delete(currWorkAlter->m_nID-1);
			InitCurrWorkAlter(currWorkAlter->m_nID-1);
		}
	   InitFieldsWorkAlter();
	   RefillWorkAlterGrid();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::delControlBtnClick(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		CheckOperation* CO;
		for (int i = currCheckOper->m_nID; i < m_ListCheckOper->Count; i++)
		{
		   CO = static_cast<CheckOperation*>(m_ListCheckOper->Items[i]);
		   CO->m_nID --;
		}
		int idx =1;
		if (m_ListCheckOper->Count>0)
		{
			idx =  currCheckOper->m_nID-1;
			m_ListCheckOper->Delete(idx);
			currCheckOper->m_nID = -1;
		}
		InitCurrCheckOper(idx);
		InitFieldsCheckOper();
		RefillCheckGrid();
		RefillWorkGrid();
	}
	else
	{
		CheckAlternativ* CA;
		if (currCheckOper->m_ListCheckAlter->Count>0)
		{
			for (int i = currCheckAlter->m_nID; i < currCheckOper->m_ListCheckAlter->Count; i++)
			{
			   CA = static_cast<CheckAlternativ*>(currCheckOper->m_ListCheckAlter->Items[i]);
			   CA->m_nID --;
			}
			currCheckOper->m_ListCheckAlter->Delete(currCheckAlter->m_nID-1);
			InitCurrCheckAlter(currCheckAlter->m_nID-1);
		}
	   InitFieldsCheckAlter();
	   RefillCheckAlterGrid();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmToolGenerStruct::extBtnClick(TObject *Sender)
{
  TList *list = new TList;

   WorkOperation* wwo = new WorkOperation;
   CheckOperation* cwo = new CheckOperation;
   ParallWorkOperation* pwo = new ParallWorkOperation;

	list->Add(wwo);
	list->Add(cwo);
	list->Add(pwo);

	for (int i = 0; i < list->Count; i++) {
	   BasisOperation *bb = static_cast<BasisOperation*>(list->Items[i]);
	  // bb->PutOn();
	}


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

}
//---------------------------------------------------------------------------

void WorkOperation::PutOnWork(TMakerTFS* Maker)
{
	if (m_pCheckAlone!=NULL)
		Maker->AddTFSToCurrentLevel(6, pMain->f_IdAlternative, pMain->f_NumAlternative);
	else
		Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
	int nID = pMain->MainList->TFEMaxID;
	PutOnAlter(Maker, nID);
}

void WorkOperation::PutOnAlter(TMakerTFS* Maker, int nId)
{
	TParamAlternativeItem* PA;
	WorkAlternativ* WA;
	CheckAlternativ* CA;
	if (m_pCheckAlone!=NULL)
	{
		for (int i = 0; i < m_ListWorkAlter->Count; i++)
		{
			WA = static_cast<WorkAlternativ*>(m_ListWorkAlter->Items[i]);
			PA = Maker->CreateNewParamAlternative(nId-1); // этот номер надо расчитывать
			if (WA->m_sName!="" && WA->m_sName!="-")
				PA->NAME = WA->m_sName;
			PA->B = WA->m_dB;
			PA->T = WA->m_dT;
			PA->V = WA->m_dV;
		}
		for (int i = 0; i < m_pCheckAlone->m_ListCheckAlter->Count; i++) {
			CA = static_cast<CheckAlternativ*>(m_pCheckAlone->m_ListCheckAlter->Items[i]);
			PA = Maker->CreateNewParamAlternative(nId);
			PA->NAME = CA->m_sName;
			PA->K_11 = CA->m_dK11;
			PA->K_00 = CA->m_dK00;
			PA->T_F = CA->m_dTf;
			PA->V_F = CA->m_dVf;
		}
	}
	else
	{
		for (int i = 0; i < m_ListWorkAlter->Count; i++)
		{
			WA = static_cast<WorkAlternativ*>(m_ListWorkAlter->Items[i]);
			PA = Maker->CreateNewParamAlternative(nId); // этот номер надо расчитывать
			if (WA->m_sName!="" && WA->m_sName!="-")
				PA->NAME = WA->m_sName;
			PA->B = WA->m_dB;
			PA->T = WA->m_dT;
			PA->V = WA->m_dV;
		}
	}
}


void ParallWorkOperation::PutOnWork(TMakerTFS* Maker)
{
	Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative);
	WorkAlternativ* WA;
	if (m_op2!=NULL && m_op22!=NULL)
	{
		int currId1 = pMain->MainList->TFEMaxID-1;
		int currId2 = pMain->MainList->TFEMaxID;
		if (m_bParal1)
		{
			Maker->SetCurrentLevel(currId1);
			Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int currInId1 = pMain->MainList->TFEMaxID-1;
			int currInId2 = pMain->MainList->TFEMaxID;
			if (m_op1->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId1);
			  m_op1->PutOnWork(Maker);
			}
			else
				m_op1->PutOnAlter(Maker, currInId1);
			Maker->SetCurrentLevel(0);
			if (m_op11->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId2);
			  m_op11->PutOnWork(Maker);
			}
			else
				m_op11->PutOnAlter(Maker, currInId2);
	   }
	   else
	   {
			Maker->SetCurrentLevel(currId2);
			Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
			Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int nID = pMain->MainList->TFEMaxID;
			m_op1->PutOnAlter(Maker, nID-1);
			m_op11->PutOnAlter(Maker, nID);
	   }
	   if (m_bParal2)
		{
			Maker->SetCurrentLevel(currId2);
			Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int currInId1 = pMain->MainList->TFEMaxID-1;
			int currInId2 = pMain->MainList->TFEMaxID;
			if (m_op2->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId1);
			  m_op2->PutOnWork(Maker);
			}
			else
				m_op2->PutOnAlter(Maker, currInId1);
			Maker->SetCurrentLevel(0);
			if (m_op22->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId2);
			  m_op22->PutOnWork(Maker);
			}
			else
				m_op22->PutOnAlter(Maker, currInId2);
	   }
	   else
	   {
			Maker->SetCurrentLevel(currId2);
			Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
			Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int nID = pMain->MainList->TFEMaxID;
			m_op2->PutOnAlter(Maker, nID-1);
			m_op22->PutOnAlter(Maker, nID);
	   }
	}
	else if (m_op2!=NULL)
	{
		int currId1 = pMain->MainList->TFEMaxID-1;
		int currId2 = pMain->MainList->TFEMaxID;
		if (m_bParal1)
		{
			Maker->SetCurrentLevel(currId1);
			Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int currInId1 = pMain->MainList->TFEMaxID-1;
			int currInId2 = pMain->MainList->TFEMaxID;
			if (m_op1->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId1);
			  m_op1->PutOnWork(Maker);
			}
			else
				m_op1->PutOnAlter(Maker, currInId1);
			Maker->SetCurrentLevel(0);
			if (m_op11->m_pCheckAlone) {
			  Maker->SetCurrentLevel(currInId2);
			  m_op11->PutOnWork(Maker);
			}
			else
				m_op11->PutOnAlter(Maker, currInId2);
	   }
	   else
	   {
			Maker->SetCurrentLevel(currId2);
			Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
            Maker->AddTFSToCurrentLevel(1, pMain->f_IdAlternative, pMain->f_NumAlternative);
			int nID = pMain->MainList->TFEMaxID;
			m_op1->PutOnAlter(Maker, nID-1);
			m_op11->PutOnAlter(Maker, nID);
	   }

	   if (m_op2->m_pCheckAlone) {
			Maker->SetCurrentLevel(currId2);
			m_op2->PutOnWork(Maker);
	   }
	   else
			m_op2->PutOnAlter(Maker, currId2);
	}
	else
	{
		int currId1 = pMain->MainList->TFEMaxID-1;
		int currId2 = pMain->MainList->TFEMaxID;

		if (m_op1->m_pCheckAlone) {
			Maker->SetCurrentLevel(currId1);
			m_op1->PutOnWork(Maker);
	   }
	   else
			m_op1->PutOnAlter(Maker, currId2);

	   if (m_op11->m_pCheckAlone) {
			Maker->SetCurrentLevel(currId2);
			m_op11->PutOnWork(Maker);
	   }
	   else
			m_op11->PutOnAlter(Maker, currId2);

	}
	Maker->SetCurrentLevel(0);
}

void ParallWorkOperation::PutOnAlter(TMakerTFS* Maker, int nId)
{}

void CheckOperation::PutOnWork(TMakerTFS* Maker)
{
	TParamAlternativeItem* PA;
	WorkAlternativ* WA;
	CheckAlternativ* CA;

	int nId = pMain->MainList->TFEMaxID;

	Maker->AddTFSToCurrentLevel(6, pMain->f_IdAlternative, pMain->f_NumAlternative);

	for (int i = 0; i < m_ListCheckAlter->Count; i++) {
		CA = static_cast<CheckAlternativ*>(m_ListCheckAlter->Items[i]);
		PA = Maker->CreateNewParamAlternative(nId+2);
		PA->NAME = CA->m_sName;
		PA->K_11 = CA->m_dK11;
		PA->K_00 = CA->m_dK00;
		PA->T_F = CA->m_dTf;
		PA->V_F = CA->m_dVf;
	}
	Maker->SetCurrentLevel(nId+1);
	for (int i = 0; i < m_ListCheckWork->Count; i++) {
		BasisOperation* BO = static_cast<BasisOperation*>(m_ListCheckWork->Items[i]);
		BO->PutOnWork(Maker);
	}
	Maker->SetCurrentLevel(0);
}

void CheckOperation::PutOnAlter(TMakerTFS* Maker, int nId)
{

}

