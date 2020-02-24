//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufmPredicatePathView.h"
#include "uPredicatePathScanner.h"
#include "ufmPredicatePathConstructor.h"
#include "uMessengers.h"
#include "uCommonGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmPredicatePathView *fmPredicatePathView;

bool ShowPredicatePathView(TPredicatePath* APath)
{
  fmPredicatePathView = new TfmPredicatePathView(Application);
  fmPredicatePathView->PPath = APath;
  int res = fmPredicatePathView->ShowModal();
  fmPredicatePathView->Release();
  return res == mrOk;
}

//---------------------------------------------------------------------------
__fastcall TfmPredicatePathView::TfmPredicatePathView(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfmPredicatePathView::FormShow(TObject *Sender)
{
  const String Rep = "Текущий метод неправилен или устарел!\r\nУстановить основной в качестве текущего метода?";
  AnsiString USP = PPath->UsedPath->Text;
  REBase->Text = PPath->BasePath->Text;
  if (USP.Length() == 0)
	REUsed->Text = REBase->Text;
  else
	REUsed->Text = USP;
  TPredicatePathScanner *Scaner = new TPredicatePathScanner;
  bool scan = Scaner->Scan(AnsiString(REUsed->Text).c_str(), PPath->UsedPath);
  if (scan && (!GMess->SendMess(4, 0, 0)) )
  {
	if ( Application->MessageBox(Rep.c_str(), _T("Внимание!"),
	  MB_ICONWARNING | MB_YESNO) == ID_YES )
    {
       REUsed->Text = REBase->Text;
	   Scaner->Scan(AnsiString(REUsed->Text).c_str(), PPath->UsedPath);
    }
  }
  Scaner->Scan(AnsiString(REBase->Text).c_str(), FBasePathToGrid);
  Scaner->Scan(AnsiString(REUsed->Text).c_str(), FUsedPathToGrid);
  RefreshDataToGrid(sgBase, FBasePathToGrid);
  RefreshDataToGrid(sgUsed, FUsedPathToGrid);
  RefreshDataItemsToGrid(sgBaseItems, (TPredicatePathNode*)sgBase->Objects[0][1]);
  RefreshDataItemsToGrid(sgUsedItems, (TPredicatePathNode*)sgUsed->Objects[0][1]);

  delete Scaner;
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::acOkExecute(TObject *Sender)
{
  bool m_try = true;
  const String Rep = "Текущий метод неправилен!";
  REUsed->Text = FUsedPathToGrid->Text;
  TPredicatePathScanner *Scaner = new TPredicatePathScanner;
  bool scan = Scaner->Scan(AnsiString(REUsed->Text).c_str(), PPath->UsedPath);
  if (scan && (!GMess->SendMess(4, 0, 0)) )
  {
	Application->MessageBox(Rep.c_str(), _T("Внимание!"), MB_ICONWARNING);
    m_try = false;
  }
  delete Scaner;
  if (!scan)
  {
	Application->MessageBox(_T("Ошибка интерпретации!"), _T("Внимание!"), MB_ICONWARNING);
    m_try = false;
  }
  if (m_try)
	Application->MessageBox(_T("Метод принят в качестве текущего!"), _T("Сообщение"),
	  MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::acCancelExecute(TObject *Sender)
{
  ModalResult = mrCancel;        
}
//---------------------------------------------------------------------------


void __fastcall TfmPredicatePathView::acShowPredicateExecute(
      TObject *Sender)
{
   GMess->SendMess(5, int(PPath->UsedPath), 0);
}
//---------------------------------------------------------------------------


void __fastcall TfmPredicatePathView::acCreateExecute(TObject *Sender)
{
  AnsiString Ret = ShowPredicatePathConstructor(PPath);
  if ( Ret.Length() > 0 )
  {
    REUsed->Text = Ret;
    TPredicatePathScanner *Scaner = new TPredicatePathScanner;
	Scaner->Scan(AnsiString(REUsed->Text).c_str(), FUsedPathToGrid);
    delete Scaner;
    RefreshDataToGrid(sgUsed, FUsedPathToGrid);
    RefreshDataItemsToGrid(sgUsedItems, (TPredicatePathNode*)sgUsed->Objects[0][1]);
  }

}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::FormCreate(TObject *Sender)
{
  FUsedPathToGrid = new TPredicatePathItem;
  FBasePathToGrid = new TPredicatePathItem;

}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::FormDestroy(TObject *Sender)
{
  delete FUsedPathToGrid;
  delete FBasePathToGrid;
}
//---------------------------------------------------------------------------
AnsiString TfmPredicatePathView::GetTfsList(AnsiString AStringPathNode)
{
  AnsiString  Res;
  int p = AStringPathNode.Pos(", [");
  if (p > 0)
  {
    Res = AStringPathNode.Delete(1, p + 2);
    p = Res.Pos("]).");
    if (p > 0)
      Res.Delete(p, 3);
  }
  return Res;
}

void TfmPredicatePathView::RefreshDataToGrid(TStringGrid *AGrid,
  TPredicatePathItem* APath)
{
  TPredicatePathNode* PtNode;
  int n_c = APath->NodeCount;
  TSelectCellEvent OnSC = AGrid->OnSelectCell;
  AGrid->OnSelectCell = NULL;
  AGrid->RowCount    = 2;
  AGrid->FixedRows   = 1;
  SGCells(AGrid, 0, 0, "№");
  SGCells(AGrid, 0, 1, "№ алт-вы");
  SGCells(AGrid, 0, 2, "Список ТФС");
  AGrid->ColWidths[0] = 30;
  AGrid->ColWidths[1] = 80;
  AGrid->ColWidths[2] = 692;
  AGrid->Rows[1]->Clear();
  AGrid->RowCount  = n_c + 1;
  for(int i = 0; i <= n_c - 1; i++)
  {
    PtNode = APath->NodeItems[i];
    AGrid->Objects[0][i + 1] = (TObject*)PtNode;
    SGCells(AGrid, i + 1, 0, i + 1);
    SGCells(AGrid, i + 1, 1, " " + IntToStr(PtNode->NumAlt));
    SGCells(AGrid, i + 1, 2, GetTfsList(PtNode->Text));

  }
  AGrid->OnSelectCell = OnSC;
}

AnsiString TfmPredicatePathView::GetTfsDesc(TPredicatePathNodeItem *AItem,
 int &AID1, int &AID2, int &AID3)
{
  AID1 = AItem->BlockID;
  AID2 = 0;
  AID3 = 0;
  AnsiString RusName = "Раб. оперция";
  TBaseWorkShape* mTFS;
  mTFS = (TBaseWorkShape*)GMess->SendMess(9, AItem->BlockID, 0);
  if (mTFS)
  {
    int m_type = mTFS->TypeShape;
    switch(m_type)
    {
     case 1:
       RusName = "Раб. оперция";
       AID1 = mTFS->GetWorkShape(0)->ID;
       break;

     case 2:
       RusName = "Парал. рабочая И";
       AID1 = mTFS->GetWorkShape(0)->ID;
       AID2 = mTFS->GetWorkShape(1)->ID;
       break;

     case 3:
       RusName = "Парал. рабочая ИЛИ";
       AID1 = mTFS->GetWorkShape(0)->ID;
       AID2 = mTFS->GetWorkShape(1)->ID;
       break;

     case 4:
       RusName = "Контроль раб-ти";
       AID1 = mTFS->GetWorkShape(0)->ID;
       AID2 = mTFS->GetWorkShape(1)->ID;
       break;

     case 5:
       RusName = "Функ-ый контроль";
       AID1 = mTFS->GetWorkShape(0)->ID;
       AID2 = mTFS->GetWorkShape(1)->ID;
       break;

     case 6:
       RusName = "Развилка";
       AID1 = mTFS->GetWorkShape(1)->ID;
       AID2 = mTFS->GetWorkShape(2)->ID;
       AID3 = mTFS->GetWorkShape(0)->ID;
       break;

     case 7:
       RusName = "Проверка условия (к.р.)";
       AID1 = mTFS->GetWorkShape(1)->ID;
       AID2 = mTFS->GetWorkShape(0)->ID;
       break;

     case 8:
       RusName = "Цикл WHILE DO";
       AID1 = mTFS->GetWorkShape(0)->ID;
       AID2 = mTFS->GetWorkShape(1)->ID;
       break;

     case 9:
       RusName = "Цикл DO WHILE DO";
       AID1 = mTFS->GetWorkShape(1)->ID;
       AID2 = mTFS->GetWorkShape(0)->ID;
       AID3 = mTFS->GetWorkShape(2)->ID;
       break;

     case 10:
       RusName = "Цикл DO WHILE DO (с ФК)";
       AID1 = mTFS->GetWorkShape(1)->ID;
       AID2 = mTFS->GetWorkShape(0)->ID;
       AID3 = mTFS->GetWorkShape(2)->ID;
       break;

     case 11:
       RusName = "Проверка условия";
       AID1 = mTFS->GetWorkShape(1)->ID;
       AID2 = mTFS->GetWorkShape(2)->ID;
       AID3 = mTFS->GetWorkShape(0)->ID;
       break;
   }
  }
  return RusName;
}

void TfmPredicatePathView::RefreshDataItemsToGrid(TStringGrid *AGrid,
  TPredicatePathNode* ANode)
{
  int id1, id2, id3;
  TPredicatePathNodeItem* Item;
  if (ANode)
  {
    TSelectCellEvent OnSC = AGrid->OnSelectCell;
    AGrid->OnSelectCell = NULL;
    int n_c = ANode->Count;
    AGrid->RowCount    = 2;
    AGrid->FixedRows   = 1;
    SGCells(AGrid, 0, 0, "№");
    SGCells(AGrid, 0, 1, "№ ТФС");
    SGCells(AGrid, 0, 2, "Типовая структура");
    SGCells(AGrid, 0, 3, "ТФЕ 1");
    SGCells(AGrid, 0, 4, "ТФЕ 2");
    SGCells(AGrid, 0, 5, "ТФЕ 3");
    AGrid->ColWidths[0] = 30;
    AGrid->ColWidths[1] = 80;
    AGrid->ColWidths[2] = 400;
    AGrid->ColWidths[3] = 64;
    AGrid->ColWidths[4] = 64;
    AGrid->ColWidths[5] = 64;
    AGrid->Rows[1]->Clear();
    AGrid->RowCount  = n_c + 1;
    for(int i = 0; i <= n_c - 1; i++)
    {
      Item = ANode->Items[i];
      AGrid->Objects[0][i + 1] = (TObject*)Item;
      AGrid->Objects[1][i + 1] = (TObject*)ANode;
      SGCells(AGrid, i + 1, 0, i + 1);
      SGCells(AGrid, i + 1, 1, " " + IntToStr(Item->BlockID));
      SGCells(AGrid, i + 1, 2, GetTfsDesc(Item, id1, id2, id3));
      SGCells(AGrid, i + 1, 3, " " + IntToStr(id1));
      SGCells(AGrid, i + 1, 4, " " + IntToStr(id2));
      SGCells(AGrid, i + 1, 5, " " + IntToStr(id3));
    }
    AGrid->OnSelectCell = OnSC;
  }
}

void __fastcall TfmPredicatePathView::sgBaseSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  RefreshDataItemsToGrid(sgBaseItems, (TPredicatePathNode*)sgBase->Objects[0][ARow]);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::sgUsedSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  RefreshDataItemsToGrid(sgUsedItems, (TPredicatePathNode*)sgUsed->Objects[0][ARow]);
}

//---------------------------------------------------------------------------
void TfmPredicatePathView::RefreshStringGrid(TStringGrid *AGrid, TPredicatePathNode* ANode)
{
  int r = 0;
  for(int i = 1; i <= AGrid->RowCount - 1; i++)
  {
    if ( (void*)AGrid->Objects[0][i] == (void*)ANode )
    {
      r = i;
      break;
    }
  }
  if (r)
  {
    SGCells(AGrid, r, 0, r);
    SGCells(AGrid, r, 1, " " + IntToStr(ANode->NumAlt));
    SGCells(AGrid, r, 2, GetTfsList(ANode->Text));
  }
}


//---------------------------------------------------------------------------
void TfmPredicatePathView::RefreshStringGridItems(TStringGrid *AGrid, int ARow)
{
  int id1, id2, id3;
  if (ARow > 0)
  {
    TPredicatePathNodeItem* Item = (TPredicatePathNodeItem*)(AGrid->Objects[0][ARow]);
    SGCells(AGrid, ARow, 0, ARow);
    SGCells(AGrid, ARow, 1, " " + IntToStr(Item->BlockID));
    SGCells(AGrid, ARow, 2, GetTfsDesc(Item, id1, id2, id3));
    SGCells(AGrid, ARow, 3, " " + IntToStr(id1));
    SGCells(AGrid, ARow, 4, " " + IntToStr(id2));
    SGCells(AGrid, ARow, 5, " " + IntToStr(id3));
  }
}

//----------------------------------------------------------------------------
void TfmPredicatePathView::UpStringGrid(TStringGrid *AGrid)
{
  TPredicatePathNode* Node;
  TPredicatePathNodeItem *Item0, *Item1;
  int r = AGrid->Row;
  if (r > 1)
  {
     Item0 =  (TPredicatePathNodeItem*)(AGrid->Objects[0][r]);
     Item1 =  (TPredicatePathNodeItem*)(AGrid->Objects[0][r - 1]);
     Node = (TPredicatePathNode*)(AGrid->Objects[1][r]);
     Node->SwapItem(Item0, Item1);
     AGrid->Objects[0][r - 1] = (TObject*)Item0;
     AGrid->Objects[0][r] = (TObject*)Item1;
     RefreshStringGridItems(AGrid, r);
     RefreshStringGridItems(AGrid, r - 1);
     RefreshStringGrid(sgUsed, Node);
     AGrid->Row = r - 1;
   }
}

void TfmPredicatePathView::DownStringGrid(TStringGrid *AGrid)
{
  TPredicatePathNode* Node;
  TPredicatePathNodeItem *Item0, *Item1;
  int r = AGrid->Row;
  if (r < AGrid->RowCount - 1)
  {
     Item0 =  (TPredicatePathNodeItem*)(AGrid->Objects[0][r]);
     Item1 =  (TPredicatePathNodeItem*)(AGrid->Objects[0][r + 1]);
     Node = (TPredicatePathNode*)(AGrid->Objects[1][r]);
     Node->SwapItem(Item0, Item1);
     AGrid->Objects[0][r + 1] = (TObject*)Item0;
     AGrid->Objects[0][r] = (TObject*)Item1;
     RefreshStringGridItems(AGrid, r);
     RefreshStringGridItems(AGrid, r + 1);
     RefreshStringGrid(sgUsed, Node);
     AGrid->Row = r + 1;
   }
}


void __fastcall TfmPredicatePathView::acUpExecute(TObject *Sender)
{
  UpStringGrid(sgUsedItems);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::acDownExecute(TObject *Sender)
{
  DownStringGrid(sgUsedItems);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::PageControl3Change(TObject *Sender)
{
  if (PageControl3->ActivePage == tsUsedEdit)
  {
    REUsed->Text = FUsedPathToGrid->Text;
  }
  if (PageControl3->ActivePage == tsUsedGrid)
  {
    RefreshDataToGrid(sgUsed, FUsedPathToGrid);
    RefreshDataItemsToGrid(sgUsedItems, (TPredicatePathNode*)sgUsed->Objects[0][1]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathView::PageControl3Changing(TObject *Sender,
      bool &AllowChange)
{
  if (PageControl3->ActivePage == tsUsedEdit)
  {
    TPredicatePathScanner *Scaner = new TPredicatePathScanner;
	bool m_try = Scaner->Scan(AnsiString(REUsed->Text).c_str(), FUsedPathToGrid);
    delete Scaner;
    if (!m_try)
      Application->MessageBox(_T("Ошибка интерпретации!"), _T("Внимание!"), MB_ICONWARNING);
    AllowChange = m_try;
  }
}
//---------------------------------------------------------------------------


void __fastcall TfmPredicatePathView::acCreateUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = PPath->BasePath->NodeCount > 0;
}
//---------------------------------------------------------------------------

