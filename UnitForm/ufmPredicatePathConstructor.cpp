//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ufmPredicatePathConstructor.h"
#include "uMessengers.h"
#include "ufmPredicatePathConstructorOgr.h"
#include "uGlsAtmCommon.h"
#include "uCommonGraph.h"
#include "uPredicatePathScanner.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfmPredicatePathConstructor *fmPredicatePathConstructor;

struct TPredicatePathConstructorItems
{
  double oz0;
  double oz1;
  TPredicatePathItem* PredicatePath;
  TPredicatePathConstructorItems() { oz0 = 0; oz1 = 0; PredicatePath = NULL; }
};

TList *PredicatePathConstructor_L;

int PredicatePathConstructor_CompareNode(void* A, void* B)
{
   TPredicatePathConstructorItems* m_A = static_cast<TPredicatePathConstructorItems*>(A);
   TPredicatePathConstructorItems* m_B = static_cast<TPredicatePathConstructorItems*>(B);
   if(m_A->oz0 > m_B->oz0)
     return 1;
   if(m_A->oz0 < m_B->oz0)
     return -1;
   return 0;
}

bool PredicatePathConstructor_Inorder(void* A)
{
   TPredicatePathConstructorItems* m_A = static_cast<TPredicatePathConstructorItems*>(A);
   PredicatePathConstructor_L->Add(m_A);
   return true;
}



AnsiString ShowPredicatePathConstructor(TPredicatePath* APath)
{
  AnsiString Res = "";
  fmPredicatePathConstructor = new TfmPredicatePathConstructor(Application);
  fmPredicatePathConstructor->PPath = APath;
  if ( fmPredicatePathConstructor->ShowModal() == mrOk )
    Res = fmPredicatePathConstructor->REText->Text;
  fmPredicatePathConstructor->Release();
  APath->ClearDescendant();
  return Res;
}


//---------------------------------------------------------------------------
__fastcall TfmPredicatePathConstructor::TfmPredicatePathConstructor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::TabControlChange(
      TObject *Sender)
{
   TPredicatePathConstructorItems* Item;
   Item = reinterpret_cast<TPredicatePathConstructorItems*>(TabControl->Tabs->Objects[TabControl->TabIndex]);
   if (Item)
     REText->Text = Item->PredicatePath->Text;
   else
     REText->Text = "";

   TPredicatePathScanner *Scaner = new TPredicatePathScanner;
   Scaner->Scan(AnsiString(REText->Text).c_str(), FPredicatePathItem);
   delete Scaner;
   RefreshDataToGrid(sgTable, FPredicatePathItem);
   RefreshDataItemsToGrid(sgTableItems, (TPredicatePathNode*)sgTable->Objects[0][1]);
   ShowValueOzenk();
}
//---------------------------------------------------------------------------
/*void TfmPredicatePathConstructor::CheckInput()
{
   f_Percent = StrToIntDef(edPercent->Text, 0);
   if (f_Percent < 0)
     f_Percent = 0;
   if (f_Percent > 100)
     f_Percent = 100;
   edPercent->Text = IntToStr(f_Percent);

   f_Count = StrToIntDef(edCount->Text, 1000);
   if (f_Count < 0)
     f_Count = 1;
   edCount->Text = IntToStr(f_Count);

} */

void TfmPredicatePathConstructor::MakeTabControl()
{
  TPredicatePathConstructorItems* Item;
  TabControl->Tabs->Clear();
  for(int i = 0; i <= f_Items->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[i]);
    TabControl->Tabs->AddObject(IntToStr(i+1), reinterpret_cast<TObject*>(Item));
  }
  TabControlChange(NULL);
}

void __fastcall TfmPredicatePathConstructor::acRunExecute(TObject *Sender)
{
   double m0, m1;
   TPredicatePathItem* Item;
   //CheckInput();
   if (PredicatePathConstructorOgrShow(f_Percent, f_Count, f_Ozenk, f_Exclude, f_MaxOptCnt))
   {
     FreeItems();
     PPath->GenerateDescendant(f_Percent, f_Count);
     for(int i = 0; i <= PPath->DescendantCount - 1; i++)
     {
       Item = PPath->Descendants[i];
       m0 = 0.;
       m1 = 0.;
       if ( f_Ozenk )
         OzenkPathItem(Item, m0, m1);

       TPredicatePathConstructorItems *N = new TPredicatePathConstructorItems;
       N->PredicatePath = Item;
       N->oz0 = m0;
       N->oz1 = m1;
       f_Items->Add(N);
     }
     if ( f_Ozenk )
     {
       SortItems();
       if (f_Exclude)
         ExcludeItems();
       DelItems();  
     }
     
     MakeTabControl();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::acShowPredicateUpdate(
      TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Trim(REText->Text).Length() > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::acShowPredicateExecute(
      TObject *Sender)
{
   TPredicatePathConstructorItems* S;
   S = reinterpret_cast<TPredicatePathConstructorItems*>(TabControl->Tabs->Objects[TabControl->TabIndex]);
   GMess->SendMess(5, int(S->PredicatePath), 0);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::acOkUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Trim(REText->Text).Length() > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::acOkExecute(TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::acCancelExecute(
      TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicatePathConstructor::FormCreate(TObject *Sender)
{
  f_Percent = 100;
  f_Count = 1000;
  f_MaxOptCnt = 1;
  f_Ozenk = false;
  f_Exclude = false;
  f_Items = new TList;
  FPredicatePathItem = new TPredicatePathItem;
}
//---------------------------------------------------------------------------
void TfmPredicatePathConstructor::FreeItems()
{
  TPredicatePathConstructorItems* Item;
  for(int i = 0; i <= f_Items->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[i]);
    delete Item;
  }
  f_Items->Clear();
}


void TfmPredicatePathConstructor::OzenkPathItem(TPredicatePathItem* AItem, double &AOz0, double &AOz1)
{
  TPredicatePathConstructorStruct S;
  GMess->SendMess(8, int(AItem), int((&S)));
  AOz0 = S.oz0;
  AOz1 = S.oz1;
}


void __fastcall TfmPredicatePathConstructor::FormDestroy(TObject *Sender)
{
  FreeItems();
  delete FPredicatePathItem;
  delete f_Items;
}
//---------------------------------------------------------------------------
void TfmPredicatePathConstructor::SortItems()
{
  PredicatePathConstructor_L = new TList;

  TGlsBinaryTree* B = new TGlsBinaryTree(PredicatePathConstructor_CompareNode);
  for (int i = 0; i <= f_Items->Count - 1; i++)
    B->insert(f_Items->Items[i]);

  B->inorder(PredicatePathConstructor_Inorder);
  f_Items->Clear();
  for (int i = 0; i <= PredicatePathConstructor_L->Count - 1; i++)
    f_Items->Add(PredicatePathConstructor_L->Items[i]);
  delete B;

  delete PredicatePathConstructor_L;
}

bool IsEqualPredicatePath(TPredicatePathConstructorItems *A, TPredicatePathConstructorItems *B)
{
  return (fabs(A->oz0 - B->oz0) < 0.0000001);
}

void TfmPredicatePathConstructor::ExcludeItems()
{
  TList *L = new TList;
  TPredicatePathConstructorItems *Item, *Item_J;
  for(int i = 0; i <= f_Items->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[i]);
    if (L->IndexOf(Item) < 0)
    {
      for(int j = i + 1; j <= f_Items->Count - 1; j++)
      {
        Item_J = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[j]);
        if ( (L->IndexOf(Item_J) < 0) && IsEqualPredicatePath(Item, Item_J) )
          L->Add(Item_J);
      }
    }
  }

  for(int i = 0; i <= L->Count - 1; i++)
  {
    int idx = f_Items->IndexOf(L->Items[i]);
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[idx]);
    delete Item;
    f_Items->Delete(idx);
  }

  delete L;
}

void TfmPredicatePathConstructor::DelItems()
{
  int i;
  TList *L = new TList;
  TPredicatePathConstructorItems *Item;
  for(i = 0; (i <= f_Items->Count - 1) && (i < f_MaxOptCnt); i++) ;
  for(; i <= f_Items->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[i]);
    L->Add(Item);
  }

  for(i = 0; i <= L->Count - 1; i++)
  {
    int idx = f_Items->IndexOf(L->Items[i]);
    Item = static_cast<TPredicatePathConstructorItems*>(f_Items->Items[idx]);
    delete Item;
    f_Items->Delete(idx);
  }
  delete L;

}

void TfmPredicatePathConstructor::ShowValueOzenk()
{
  pnlOzenk->Visible = f_Ozenk;
  if (f_Ozenk)
  {
    TPredicatePathConstructorItems* Item;
    Item = reinterpret_cast<TPredicatePathConstructorItems*>(TabControl->Tabs->Objects[TabControl->TabIndex]);
    edPower->Text = float_2_string(Item->oz0, 10);
    edWork->Text = float_2_string(Item->oz1, 10);
  }
}

AnsiString TfmPredicatePathConstructor::GetTfsList(AnsiString AStringPathNode)
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


void TfmPredicatePathConstructor::RefreshDataToGrid(TStringGrid *AGrid,
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


AnsiString TfmPredicatePathConstructor::GetTfsDesc(TPredicatePathNodeItem *AItem,
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


void TfmPredicatePathConstructor::RefreshDataItemsToGrid(TStringGrid *AGrid,
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


void __fastcall TfmPredicatePathConstructor::sgTableSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
  RefreshDataItemsToGrid(sgTableItems, (TPredicatePathNode*)sgTable->Objects[0][ARow]);
}
//---------------------------------------------------------------------------

