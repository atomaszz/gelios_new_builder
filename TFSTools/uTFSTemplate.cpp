//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFSTemplate.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TFsTableItem* GetFsTableItem(TFsList* AItems, int AIndex)
{
  return (TFsTableItem*)(AItems->MoveInit(AIndex))->Data;
}

//---------------------------------------------------------------------------

TTFSTemplate::TTFSTemplate(TChecker* AOwner)
{
  FOwner = AOwner;
  FList = new TList;
  InnerPath1 = new TTFSInnerPath;
  InnerPath2 = new TTFSInnerPath;
}

TTFSTemplate::~TTFSTemplate()
{
  delete InnerPath1;
  delete InnerPath2;
  delete FList;
}

int TTFSTemplate::Check(TFsTableItemData* Transit)
{
  FEnd = NULL;
  FBegin = NULL;
  FRpsWork = NULL;
  FList->Clear();
  return 0;
}

TFsTableItem* TTFSTemplate::BeginItem()
{
  return FBegin;
}

TFsTableItem* TTFSTemplate::EndItem()
{
  return FEnd;
}

void TTFSTemplate::Rights(TFsTableItemData* AItem, TFsList* AList)
{
  AList->Clear();
  FOwner->Rights(AItem, AList);
}

void TTFSTemplate::Lefts(TFsTableItemData* AItem, TFsList* AList)
{
  AList->Clear();
  FOwner->Lefts(AItem, AList);
}

TFsTableItem* TTFSTemplate::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItem*)(FList->Items[AIndex]);
}



//--------------------------------------------------------------------------
int TTFSReverse::Check(TFsTableItemData* Transit)
{
  //проверить всюду где можно на вхождение слева в ТФЕ

  TFsList CallItems;
  TFsTableItem* Item;
  TFsTableItemData *T1, *A1, *T2, *E, *T3;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  FBegin = Item;
  InnerPath1->AddToPath(A1);

  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  FRpsWork = A1;

  Item = GetFsTableItem(&CallItems, 0);
  T2 = Item->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(T2);

  Rights(T2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  E = Item->Right;
  if (E->IsFunc() || E->IsDiag())
    AddItem(Item);
  else
    return 0;
  Rights(E, &CallItems);
  if (CallItems.Count != 2)
    return 0;
  TFsTableItem* ItemRO = GetFsTableItem(&CallItems, 0);
  TFsTableItem* ItemTR = GetFsTableItem(&CallItems, 1);
  if (!IsEqualFsItem(ItemRO->Right, A1))
  {
    Item = ItemRO;
    ItemRO = ItemTR;
    ItemTR = Item;
  }

  Lefts(E, &CallItems);
  if (CallItems.Count != 1)
    return 0;


  if (IsEqualFsItem(ItemRO->Right, A1))
    AddItem(ItemRO);
  else
    return 0;

  T3 = ItemTR->Right;
  if (T3->IsTrans())
    AddItem(ItemTR);
  else
    return 0;
  FEnd = ItemTR;

  if (E->IsFunc())
    return TFS_CONTROLFUNC;
  return TFS_CONTROLWORK;
}


//--------------------------------------------------------------------------
int TTFSReverseRO::Check(TFsTableItemData* Transit)
{
  TFsList CallItems;
  TFsTableItem* Item;
  TFsTableItemData* Temp;
  TFsTableItemData *T1, *T2, *T3, *T4, *T5, *A1, *A2, *E;
  TFsTableItem *Prev, *Next;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  FBegin = Item;
  InnerPath1->AddToPath(A1);

  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  FRpsWork = A1;
  Item = GetFsTableItem(&CallItems, 0);
  T2 = Item->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(T2);

  Rights(T2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  E = Item->Right;
  if (E->IsFunc() || E->IsDiag())
    AddItem(Item);
  else
    return 0;

  Lefts(E, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(E, &CallItems);
  if (CallItems.Count != 2)
    return 0;

  TFsTableItem* Path1 = GetFsTableItem(&CallItems, 0);
  TFsTableItem* Path2 = GetFsTableItem(&CallItems, 1);

  //----------------   Тест
  bool swap = false;
  Temp = Path1->Right;
  if (!Temp->IsTrans())
    return 0;
  Rights(Temp, &CallItems);
  if (CallItems.Count == 1)
  {
    Item = GetFsTableItem(&CallItems, 0);
    Temp = Item->Right;
    if (Temp->IsRo())
    {
      Rights(Temp, &CallItems);
      if (CallItems.Count == 1)
      {
        Item = GetFsTableItem(&CallItems, 0);
        Temp = Item->Right;
        if (Temp->IsTrans())
        {
          Rights(Temp, &CallItems);
          if (CallItems.Count == 1)
          {
            Item = GetFsTableItem(&CallItems, 0);
            Temp = Item->Right;
            if(Temp->IsRo())
            {
              if (!IsEqualFsItem(Temp, A1))
                swap = true;
            }
            else
              swap = true;
          }
          else
            swap = true;
        }
        else
          swap = true;

      }
      else
        swap = true;
    }
    else
      swap = true;
  }
  else
    swap = true;

  //--------------------------- конец теста

  if (swap)
  {
    Prev = Path2;
    Next = Path1;
  }
  else
  {
    Prev = Path1;
    Next = Path2;
  }
  //------------------Prev
  T3 = Prev->Right;
  if (!T3->IsTrans())
    return 0;
  AddItem(Prev);
  InnerPath2->AddToPath(T3);

  Rights(T3, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A2 = Item->Right;
  if (!A2->IsRo())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(A2);

  Lefts(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T4 = Item->Right;
  if (!T4->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(T4);

  Rights(T4, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  Temp = Item->Right;
  if (!Temp->IsRo())
    return 0;
  if (!IsEqualFsItem(Temp, A1))
    return 0;
  AddItem(Item);

  //------------------Next
  T5 = Next->Right;
  if (!T5->IsTrans())
    return 0;
  AddItem(Next);
  FEnd = Next;

  if (E->IsFunc())
    return TFS_CycleDoWhileDo_FC;
  return TFS_CycleDoWhileDo;
}


//--------------------------------------------------------------------------
int TTFSBifurcation::Check(TFsTableItemData* Transit)
{
  TFsList CallItems;
  TFsTableItem *Item, *Item1, *Item2;
  TFsTableItemData *T1, *T2, *T3, *T4, *T5, *T6, *B1, *A1, *A2, *F1, *F2;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  B1 = Item->Right;
  if (!B1->IsDiag())
    return 0;
  AddItem(Item);
  FBegin = Item;


  Rights(B1, &CallItems);
  if (CallItems.Count != 2)
    return 0;
  Item1 = GetFsTableItem(&CallItems, 0);
  Item2 = GetFsTableItem(&CallItems, 1);


  //------------------------- Item1
  T2 = Item1->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item1);
  InnerPath1->AddToPath(T2);

  Rights(T2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(A1);

  Lefts(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T3 = Item->Right;
  if (!T3->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(T3);

  Rights(T3, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  F1 = Item->Right;
  if (!F1->IsFin())
    return 0;
  AddItem(Item);

  Rights(F1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T6 = Item->Right;
  if (!T6->IsTrans())
    return 0;
  AddItem(Item);
  FEnd = Item;


  //------------------------- Item2
  T4 = Item2->Right;
  if (!T4->IsTrans())
    return 0;
  AddItem(Item2);
  InnerPath2->AddToPath(T4);

  Rights(T4, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A2 = Item->Right;
  if (!A2->IsRo())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(A2);

  Lefts(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T5 = Item->Right;
  if (!T5->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(T5);

  Rights(T5, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  F2 = Item->Right;
  if (!F2->IsFin())
    return 0;
  AddItem(Item);
  if (!IsEqualFsItem(F1, F2))
    return 0;
  return TFS_BIFURCATION;
}


//--------------------------------------------------------------------------
int TTFSParWork::Check(TFsTableItemData* Transit)
{
  TFsList CallItems;
  TFsTableItem *Item, *Item1, *Item2;
  TFsTableItemData *T1, *T2, *T3, *T4, *T5, *T6, *C1, *A1, *A2, *F1, *F2;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  C1 = Item->Right;
  if (!C1->IsStart())
    return 0;
  AddItem(Item);
  FBegin = Item;


  Rights(C1, &CallItems);
  if (CallItems.Count != 2)
    return 0;
  Item1 = GetFsTableItem(&CallItems, 0);
  Item2 = GetFsTableItem(&CallItems, 1);


  //------------------------- Item1
  T2 = Item1->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item1);
  InnerPath1->AddToPath(T2);

  Rights(T2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(A1);

  Lefts(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T3 = Item->Right;
  if (!T3->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath1->AddToPath(T3);

  Rights(T3, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  F1 = Item->Right;
  if (!F1->IsFin())
    return 0;
  AddItem(Item);

  Rights(F1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T6 = Item->Right;
  if (!T6->IsTrans())
    return 0;
  AddItem(Item);
  FEnd = Item;


  //------------------------- Item2
  T4 = Item2->Right;
  if (!T4->IsTrans())
    return 0;
  AddItem(Item2);
  InnerPath2->AddToPath(T4);

  Rights(T4, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A2 = Item->Right;
  if (!A2->IsRo())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(A2);

  Lefts(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T5 = Item->Right;
  if (!T5->IsTrans())
    return 0;
  AddItem(Item);
  InnerPath2->AddToPath(T5);

  Rights(T5, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  F2 = Item->Right;
  if (!F2->IsFin())
    return 0;
  AddItem(Item);
  if (!IsEqualFsItem(F1, F2))
    return 0;
  return TFS_ZWORK_OR;
}

//--------------------------------------------------------------------------
int TTFSPoslWork::Check(TFsTableItemData* Transit)
{
  TFsList CallItems;
  TFsTableItem *Item;
  TFsTableItemData *T1, *T2, *T3, *A1, *A2;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  FBegin = Item;

  FRpsWork = A1;
  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T2 = Item->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item);

  Rights(T2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A2 = Item->Right;
  if (!A2->IsRo())
    return 0;
  AddItem(Item);


  Lefts(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A2, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T3 = Item->Right;
  if (!T3->IsTrans())
    return 0;
  AddItem(Item);

  FEnd = Item;
  return TFS_ZWORK;

  
}

//--------------------------------------------------------------------------
int TTFSSimpleWork::Check(TFsTableItemData* Transit)
{
  TFsList CallItems;
  TFsTableItem *Item;
  TFsTableItemData *T1, *T2, *A1;

  TTFSTemplate::Check(Transit);

  T1 = Transit;
  Rights(T1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  A1 = Item->Right;
  if (!A1->IsRo())
    return 0;
  AddItem(Item);
  FBegin = Item;


  Lefts(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;

  Rights(A1, &CallItems);
  if (CallItems.Count != 1)
    return 0;
  Item = GetFsTableItem(&CallItems, 0);
  T2 = Item->Right;
  if (!T2->IsTrans())
    return 0;
  AddItem(Item);
  FEnd = Item;
  return TFS_WORK;

  
}

