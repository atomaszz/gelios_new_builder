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
  TBaseWorkShape* WS;
  TParamAlternativeItem* PA;
  TMakerTFS* Maker = new TMakerTFS(pMain->MainList, pMain->Grid, &pMain->ShapeCopy,
	pMain->f_CurrIDShape, pMain->f_CurrIDBlock, pMain->f_CurrIDLine);
  try
  {
	Maker->SetCurrentLevel(pMain->LevelController->ParentShapeID);

	int m_Last_id = pMain->MainList->TFEMaxID; //›ÚÓ ÔÓÒÎÂ‰ÌËÈ ÌÓÏÂ ÚÙÂ

	WS = Maker->AddTFSToCurrentLevel(3, pMain->f_IdAlternative, pMain->f_NumAlternative); // ‰Ó·‡‚ÎÂÌËÂ Ô‡‡ÎÂ¸ÌÓÈ –Œ
	//‰Ó·‡‚ÎÂÌËÂ Ô‡‡ÏÂÚË˜ÂÒÍÓÈ ‡Î¸ÚÂÌ‡ÚË‚˚ ‰Îˇ ÔÂ‚ÓÈ “‘≈ ËÁ ‰Ó·‡‚ÎÂÌÌÓÈ Ô‡‡ÎÂ¸ÌÓÈ –Œ
	PA = Maker->CreateNewParamAlternative(m_Last_id + 1); // ˝ÚÓÚ ÌÓÏÂ Ì‡‰Ó ‡Ò˜ËÚ˚‚‡Ú¸
	PA->B = 10;
	PA->T = 100;
	PA->V = 1000;

	//‰Ó·‡‚ÎÂÌËÂ Ô‡‡ÏÂÚË˜ÂÒÍÓÈ ‡Î¸ÚÂÌ‡ÚË‚˚ ‰Îˇ ‚ÚÓÈ “‘≈ ËÁ ‰Ó·‡‚ÎÂÌÌÓÈ Ô‡‡ÎÂ¸ÌÓÈ –Œ
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 30;
	PA->T = 300;
	PA->V = 3000;

	//‰Ó·‡‚ÎÂÌËÂ Â˘Â Ó‰ÌÓÈ Ô‡‡ÏÂÚË˜ÂÒÍÓÈ ‡Î¸ÚÂÌ‡ÚË‚˚ ‰Îˇ ‚ÚÓÈ “‘≈ ËÁ ‰Ó·‡‚ÎÂÌÌÓÈ Ô‡‡ÎÂ¸ÌÓÈ –Œ
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 50;
	PA->T = 500;
	PA->V = 5000;


	//ÛÒÚ‡Ì‡‚ÎË‚‡ÂÏ ÚÂÍÛ˘ËÈ ÛÓ‚ÂÌ¸ ‰Îˇ ÔÂ‚ÓÈ “‘≈ ËÁ ‰Ó·‡‚ÎÂÌÌÓÈ “‘—
	Maker->SetCurrentLevel(m_Last_id + 1);
	Maker->AddTFSToCurrentLevel(6, pMain->f_IdAlternative, pMain->f_NumAlternative); // ‰Ó·‡‚ÎÂÌËÂ ‘ÛÌÍ-˚È ÍÓÌÚÓÎ¸


	Maker->SetCurrentLevel(2);
	Maker->AddTFSToCurrentLevel(4, pMain->f_IdAlternative, pMain->f_NumAlternative); // ‰Ó·‡‚ÎÂÌËÂ Ô‡‡ÎÂ¸ÌÓÈ –Œ

	TAltSelectorItem* Item = pMain->f_AltSelector->CreateNewAlternateID(pMain->LevelController->ParentShapeID, 1);
	 if ( !pMain->MainList->CreateAlternate(WS, WS, Item->ID, Item->Num) )
			pMain->MainList->AddAlternate(Item->ID, Item->Num);
	pMain->f_AlternateController->AddAlternateItem(WS, WS, Item->ID, Item->Num,
	   0, 0);

	Maker->SetCurrentLevel(0);
	pMain->Grid->PrepareLevel();  // ÚÓÍ‡ Ó‰ËÌ ‡Á ËÒÛÂÏ ÌÓ‚˚È ÛÓ‚ÂÌ¸ ‡ÎÚÂÌ‡ÚË‚
	Maker->AddTFSToCurrentLevel(4, Item->ID, Item->Num); // ‰Ó·‡‚ÎÂÌËÂ Ô‡‡ÎÂ¸ÌÓÈ –Œ

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
	sgWorkOperation->Cells[0][0] = "π";
	sgWorkOperation->Cells[1][0] = "Õ¿«¬¿Õ»≈ 1-Œ… ¿À‹“≈–.";
	sgWorkOperation->Cells[2][0] = " ŒÀ-¬Œ ¿À‹“≈–Õ¿“»¬";
	sgWorkOperation->Cells[3][0] = "œ–≈ƒÿ≈—“¬. Œœ≈–¿÷»»";
	sgWorkOperation->Cells[4][0] = " ŒÕ“–ŒÀ‹";

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
	sgWorkAlterOperation->Cells[0][0] = "π";
	sgWorkAlterOperation->Cells[1][0] = "Õ¿«¬¿Õ»≈";
	sgWorkAlterOperation->Cells[2][0] = "¬≈–Œﬂ“ÕŒ—“‹ B";
	sgWorkAlterOperation->Cells[3][0] = "¬–≈Ãﬂ ¬€œŒÀÕ≈Õ»ﬂ T";
	sgWorkAlterOperation->Cells[4][0] = "«¿“–¿“€ Õ¿ ¬€œŒÀÕ≈Õ»≈ V";

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
	sgControlOperation->Cells[0][0] = "π";
	sgControlOperation->Cells[1][0] = "Õ¿«¬¿Õ»≈ 1-Œ… ¿À‹“≈–.";
	sgControlOperation->Cells[2][0] = " ŒÀ-¬Œ ¿À‹“≈–Õ¿“»¬";
	sgControlOperation->Cells[3][0] = " ŒÕ“–ŒÀ»–. Œœ≈–¿÷»»";

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
	sgControlAlterOperation->Cells[0][0] = "π";
	sgControlAlterOperation->Cells[1][0] = "Õ¿«¬¿Õ»≈";
	sgControlAlterOperation->Cells[2][0] = "¬≈–Œﬂ“ÕŒ—“‹ œ_11";
	sgControlAlterOperation->Cells[3][0] = "¬≈–Œﬂ“ÕŒ—“‹ œ_00";
	sgControlAlterOperation->Cells[4][0] = "¬≈–Œﬂ“ÕŒ—“‹ –¿¡Œ“Œ—-“»";

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
		if (WO->m_sNameFirstAlt=="")
		{
			sgWorkOperation->Cells[1][i+1] = "-";
		}
		else
		{
			sgWorkOperation->Cells[1][i+1] = WO->m_sNameFirstAlt;
		}
		sgWorkOperation->Cells[2][i+1] = IntToStr(WO->m_ListWorkAlter->Count);
		AnsiString  sMAsAlt ="-";
		if (WO->m_nNumMasBefore>0)
		{
			sMAsAlt ="";
			for (int j = 0; j < WO->m_nNumMasBefore; j++)
			{
				sMAsAlt += IntToStr(WO->m_nMasBefore[j]) + " ";
			}
		}
		sgWorkOperation->Cells[3][i+1] = sMAsAlt;
		sgWorkOperation->Cells[4][i+1] = WO->m_bAloneControl ? "ƒ¿" : "Õ≈“";
	}
}

void TfmToolGenerStruct::RefillWorkAlterGrid()
{
	for(int i =0; i< sgWorkAlterOperation->RowCount; i++)
		sgWorkAlterOperation->Rows[i+1]->Clear();

	sgWorkAlterOperation->RowCount    = currWorkOper->m_ListWorkAlter->Count+1;
	WorkAlternativ* WOA;
	for (int i = 0; i <= currWorkOper->m_ListWorkAlter->Count - 1; i++ )
	{
		WOA = static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[i]);
		sgWorkAlterOperation->Cells[0][i+1] = i+1;

	}
}

void TfmToolGenerStruct::RefillCheckGrid()
{
	for(int i =0; i< sgControlOperation->RowCount; i++)
		sgControlOperation->Rows[i+1]->Clear();

	sgControlOperation->RowCount    = m_ListCheckOper->Count+1;
	CheckOperation* CO;
	for (int i = 0; i <= m_ListCheckOper->Count - 1; i++ )
	{
		CO = static_cast<CheckOperation*>(m_ListCheckOper->Items[i]);
		sgControlOperation->Cells[0][i+1] = i+1;
		if(CO->m_sNameFirstAlt =="")
		{
			sgControlOperation->Cells[1][i+1] = "-";
		}
		else
		{
		   sgControlOperation->Cells[1][i+1] = CO->m_sNameFirstAlt;
		}
		sgControlOperation->Cells[2][i+1] = CO->m_nNumAlt;
		AnsiString  sMasCheck ="-";
		if (CO->m_nNumMasCheck>0)
		{
			sMasCheck ="";
			for (int j = 0; j < CO->m_nNumMasCheck; j++)
			{
				sMasCheck += IntToStr(CO->m_nMasCheck[j]) + " ";
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
		Item->m_nNumAlt = 0;
		Item->m_sNameFirstAlt = "";

		Item->m_nNumMasBefore = 0;
		Item->m_ListWorkAlter = new TList;
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
		if (currWorkOper == NULL)
		{
			InitCurrWorkOper(1);
		}
	}
	else
	{
		WorkAlternativ * ItemA = new WorkAlternativ;

		ItemA->m_nID = 1;
		ItemA->m_nWorkID = 1;
		ItemA->m_sName = "test";
		ItemA->m_dB = 1;
		ItemA->m_dV = 1;
		ItemA->m_dT = 1;

		if(currWorkOper!=NULL)
		{
			currWorkOper->m_ListWorkAlter->Add(ItemA);

			WorkAlternativ * tmp =   static_cast<WorkAlternativ*>(currWorkOper->m_ListWorkAlter->Items[0]);
			currWorkOper->m_sNameFirstAlt =  tmp->m_sName;
			RefillWorkAlterGrid();
		}

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
		PageControl3->ActivePageIndex = 1;

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
		PageControl2->ActivePageIndex = 1;

	EnableWorkControls();
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

void TfmToolGenerStruct::EnableWorkControls()
{
	bool bEButt = false;
	bool bEWork = false;
	bool bEAlter = false;
	if (PageControl2->ActivePageIndex == 0)
	{
	   bEButt = (m_ListWorkOper->Count >0) && (currWorkOper!=NULL);
	   editBeforeOperation->Enabled = bEButt;
	   addWorkBtn->Enabled = true;
	}
	else if (PageControl2->ActivePageIndex == 1)
	{
		bEButt = (m_ListWorkOper->Count >0) && (currWorkOper!=NULL);
		addWorkBtn->Enabled = bEButt;
	}

	delWorkBtn->Enabled = bEButt;
	editWorkBtn->Enabled = bEButt;

/*	editBeforeOperation
	CheckBoxAloneCheck

	editNameAlter
	editB
	editT
	editV        */

}

void TfmToolGenerStruct::InitFieldsWorkOper()
{
	if (currWorkOper->m_nNumMasBefore>0)
	{
		for (int i=0; i < currWorkOper->m_nNumMasBefore; i++)
		{
			editBeforeOperation->Text = editBeforeOperation->Text +currWorkOper->m_nMasBefore[i] + " ";
		}
	}
	else
		editBeforeOperation->Text ="";
	if (currWorkOper->m_ListWorkAlter) {
		editNumAlter->Text = IntToStr(currWorkOper->m_ListWorkAlter->Count);
	}
	else
	  editNumAlter->Text = IntToStr(0);
	editFirstAlterName->Text =  currWorkOper->m_sNameFirstAlt;
}

void TfmToolGenerStruct::EnableCheckControls()
{

}

//---------------------------------------------------------------------------
void __fastcall TfmToolGenerStruct::addControlBtnClick(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		CheckOperation* Item = new CheckOperation;

		Item->m_nID = m_ListCheckOper->Count+1;
		Item->m_nNumAlt = 0;
		Item->m_sNameFirstAlt = "";
		Item->m_nNumAlt = 0;

		m_ListCheckOper->Add(Item);
		RefillCheckGrid();
	}
	else
	{
		WorkAlternativ * ItemA = new WorkAlternativ;

		ItemA->m_nID = 1;
		ItemA->m_nWorkID = 1;
		ItemA->m_sName = "test";
		ItemA->m_dB = 1;
		ItemA->m_dV = 1;
		ItemA->m_dT = 1;

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


void __fastcall TfmToolGenerStruct::sgWorkOperationSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
	InitCurrWorkOper(ARow);
}
//---------------------------------------------------------------------------

