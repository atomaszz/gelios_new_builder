//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCheckSuperPos.h"
#include "uTFSTemplate.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void TLevelHeap::FreeList()
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItemData* Item = (TFsTableItemData*)FList->Items[i];
    delete Item;
  }
  FList->Clear();
}

void TLevelHeap::Add(TFsTableItemData *AData)
{
  TFsTableItemData* Item = Find(AData);
  if(!Item)
  {
    Item = new TFsTableItemData;
    *(Item) = *(AData);
    FList->Add(Item);
  }
}

TFsTableItemData* TLevelHeap::Find(TFsTableItemData *AData)
{
  return Find2(AData->Type, AData->Num);
}

TFsTableItemData* TLevelHeap::Find2(int AType, int ANum)
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItemData* Item = (TFsTableItemData*)FList->Items[i];
    if ((Item->Type == AType) && (Item->Num == ANum) )
      return Item;
  }
  return NULL;
}

TFsTableItemData* TLevelHeap::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItemData*)(FList->Items[AIndex]);
}




//-----------------------------------------------------------------
TFsTableItem* TBigWork::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItem*)(FList->Items[AIndex]);
}

TFsTableItem* TBigWork::FindItem(TFsTableItem* AItem)
{
  for(int i = 0; i < Count; i++)
  {
    TFsTableItem* Item = Items[i];
    if (IsEqualFsItem(Item->Left, AItem->Left) &&
        IsEqualFsItem(Item->Right, AItem->Right))
      return Item;
  }
  return NULL;
}

AnsiString TBigWork::ToString()
{
  AnsiString Res = "A" + IntToStr(Num) + " TYPE=" + IntToStr(Typ) + " :";
  TFsTableItem* Item;
  for(int i = 0; i < Count; i++)
  {
    Item = Items[i];
    Res = Res + Item->ToString();
    if (i != Count - 1)
      Res = Res + ",";
  }
  return Res;
}

//---------------------------------------------------------------------------
TFsTableItem* TChecker::ListFirst()
{
  TFsNode* N = FList->MoveInit(0);
  if (N)
    return (TFsTableItem*)(N->Data);
  return NULL;
}

TFsTableItem* TChecker::ListNext()
{
  TFsNode* N = FList->MoveNext();
  if (N)
    return (TFsTableItem*)(N->Data);
  return NULL;
}

void TChecker::Lefts(TFsTableItemData* ARight, TFsList* AItems)
{
  TFsTableItem* Item = ListFirst();
  while(Item)
  {
    if (IsEqualFsItem(Item->Right, ARight))
      AItems->Add(Item);
    Item = ListNext();
  }
}

void TChecker::Rights(TFsTableItemData* ALeft, TFsList* AItems)
{
  TFsTableItem* Item = ListFirst();
  while(Item)
  {
    if (IsEqualFsItem(Item->Left, ALeft))
      AItems->Add(Item);
    Item = ListNext();
  }
}



int TChecker::Check()
{
  if (Count < 2)
    return 0;
  int res = 0;
  TTFSTemplate *T = NULL;
  TFsNode* N = FList->First;
  TFsTableItem* Item = (TFsTableItem*)(N->Data);
  if (Count == 2)
  {
    T = new TTFSSimpleWork(this);
    res = T->Check(Item->Left);
  }
  else
    do
    {
      delete T;
      T = new TTFSReverse(this);
      res = T->Check(Item->Left);
      if (res > 0)
        break;

      delete T;
      T = new TTFSReverseRO(this);
      res = T->Check(Item->Left);
      if (res > 0)
        break;

      delete T;
      T = new TTFSBifurcation(this);
      res = T->Check(Item->Left);
      if (res > 0)
        break;

      delete T;
      T = new TTFSParWork(this);
      res = T->Check(Item->Left);
      if (res > 0)
        break;

      delete T;
      T = new TTFSPoslWork(this);
      res = T->Check(Item->Left);
      if (res > 0)
        break;

      N = N->Next;
      Item = (TFsTableItem*)(N->Data);
    }while (N != FList->First);

  if (res > 0 && res != TFS_WORK)
  {
    FBigWork = FOwner->CreateBigWork(res);
    FBigWork->BeginItem = T->BeginItem();
    FBigWork->EndItem = T->EndItem();
    FBigWork->RpsWork = T->RpsWork;
    FBigWork->InnerPath1->CopyFrom(T->InnerPath1);
    FBigWork->InnerPath2->CopyFrom(T->InnerPath2);
    for(int i = 0; i < T->Count; i++)
      FBigWork->AddItem(T->Items[i]);
  }
  delete T;
  return res;
}
//---------------------------------------------------------------------------
TFsTableItem* TCheckSuperPosItem::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItem*)(FList->Items[AIndex]);
}

void TCheckSuperPosItem::CopyListToChecker(TChecker* AChecker)
{
  for(int i = 0; i < FList->Count; i++)
    AChecker->AddItem((TFsTableItem*)FList->Items[i]);
}

void TCheckSuperPosItem::Build(TCheckSuperPosItem* ASource, TChecker* AChecker)
{
  bool L, R;
  TFsList List;
  TFsNode* Node;
  TFsTableItem *ItemSource, *ItemFound, *ItemAppend;
  TFsTableItemData Left, Right;
  TBigWork* Work = AChecker->BigWork;
  for(int i = 0; i < ASource->Count; i++)
  {
    ItemSource = ASource->Items[i];
    ItemFound = Work->FindItem(ItemSource);
    if (ItemFound)
    {
      L = ItemFound == Work->BeginItem;
      R = ItemFound == Work->EndItem;
      if (L || R)
      {
        if (L)
        {
          Left = *(ItemFound->Left);
		  Right.Type = ST_RO;
          Right.Num = Work->Num;
        }
        else
        {
          Right = *(ItemFound->Right);
		  Left.Type = ST_RO;
          Left.Num = Work->Num;
        }
        ItemAppend = FOwner->CreateAppendFsTableItem(Left, Right);
        List.Add(ItemAppend);
      }
    }
    else
      List.Add(ItemSource);
  }

  Node = List.MoveInit(0);
  while(Node)
  {
    ItemAppend = NULL;
    ItemSource = (TFsTableItem*)(Node->Data);
    if (Work->RpsWork)
    {
      L = IsEqualFsItem(ItemSource->Left, Work->RpsWork);
      R = IsEqualFsItem(ItemSource->Right, Work->RpsWork);
      if (L || R)
      {
        if (L)
        {
          Right = *(ItemSource->Right);
          Left.Type = ST_RO;
          Left.Num = Work->Num;
        }
        else
        {
          Left = *(ItemSource->Left);
          Right.Type = ST_RO;
          Right.Num = Work->Num;
        }
        ItemAppend = FOwner->CreateAppendFsTableItem(Left, Right);
      }
    }
    if (ItemAppend)
      AddItem(ItemAppend);
    else
      AddItem(ItemSource);
    Node = List.MoveNext();
  }
}

AnsiString TCheckSuperPosItem::ToString()
{
  AnsiString Res = "";
  TFsTableItem* Item;
  for(int i = 0; i < Count; i++)
  {
    Item = Items[i];
    Res = Res + Item->ToString();
    if (i != Count - 1)
      Res = Res + ",";
  }
  return Res;

}


//---------------------------------------------------------------------------

TCheckSuperPos::TCheckSuperPos()
{
  FList = new TList;
  FListItem = new TList;
  FListBigWork = new TList;
  FListAppend = new TList;
  FHeap = new TLevelHeap;
}

TCheckSuperPos::~TCheckSuperPos()
{
  FreeListItem();
  FreeListBigWork();
  FreeListAppend();
  delete FListItem;
  delete FListBigWork;
  delete FListAppend;
  delete FList;
  delete FHeap;
}

void TCheckSuperPos::FreeListItem()
{
  for(int i = 0; i < FListItem->Count; i++)
  {
    TCheckSuperPosItem* Item = (TCheckSuperPosItem*)FListItem->Items[i];
    delete Item;
  }
  FListItem->Clear();
}

void TCheckSuperPos::FreeListBigWork()
{
  for(int i = 0; i < FListBigWork->Count; i++)
  {
    TBigWork* Item = (TBigWork*)FListBigWork->Items[i];
    delete Item;
  }
  FListBigWork->Clear();
}

void TCheckSuperPos::FreeListAppend()
{
  for(int i = 0; i < FListAppend->Count; i++)
  {
    TFsTableItem* Item = (TFsTableItem*)FListAppend->Items[i];
    delete Item;
  }
  FListAppend->Clear();
}

TCheckSuperPosItem* TCheckSuperPos::GetItemsSuperPos(int AIndex)
{
  if (AIndex < 0 || AIndex >= FListItem->Count)
    return NULL;
  return (TCheckSuperPosItem*)(FListItem->Items[AIndex]);
}

TBigWork* TCheckSuperPos::GetItemsBigWork(int AIndex)
{
  if (AIndex < 0 || AIndex >= FListBigWork->Count)
    return NULL;
  return (TBigWork*)(FListBigWork->Items[AIndex]);
}


void TCheckSuperPos::InitFromTable(TFsTable* ATable)
{
  FList->Clear();
  TFsTableItem *Item;
  for(int i = 0; i < ATable->Count; i++)
  {
    Item = ATable->Items[i];
      Append(Item);
  }
}

void TCheckSuperPos::Append(TFsTableItem* AItem)
{
  if (FList->IndexOf(AItem) < 0)
    FList->Add(AItem);
}

TBigWork* TCheckSuperPos::CreateBigWork(int ATyp)
{
  FBigCounter--;
  TBigWork *BigWork = new TBigWork(FBigCounter, ATyp);
  FListBigWork->Add(BigWork);
  return BigWork;
}


TCheckSuperPosItem* TCheckSuperPos::CreateCheckSuperPosItem()
{
  TCheckSuperPosItem* Item = new TCheckSuperPosItem(this);
  FListItem->Add(Item);
  return Item;
}

TFsTableItem* TCheckSuperPos::CreateAppendFsTableItem(TFsTableItemData ALeft,
  TFsTableItemData ARight)
{
   TFsTableItem* Item = new TFsTableItem;
   *(Item->Left) = ALeft;
   *(Item->Right) = ARight;
   FListAppend->Add(Item);
   return Item;
}

TBigWork* TCheckSuperPos::FindBigWork(int ANum)
{
  for(int i = 0; i < FListBigWork->Count; i++)
  {
    TBigWork* Item = (TBigWork*)FListBigWork->Items[i];
    if (Item->Num == ANum)
      return Item;
  }
  return NULL;

}

bool TCheckSuperPos::Check()
{
  int res;
  TTFSTemplate *T;
  TCheckSuperPosItem *ItemNew, *ItemPrev;

  FBigCounter = 0;
  FreeListItem();
  FreeListBigWork();
  FreeListAppend();

  ItemNew = CreateCheckSuperPosItem();

  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItem* TableItem = (TFsTableItem*)FList->Items[i];
    if (!TableItem->IsFirst() && !TableItem->IsLast())
      ItemNew->AddItem(TableItem);
  }
  while (true)
  {
    TChecker* C = new TChecker(this);
    ItemNew->CopyListToChecker(C);
	res = C->Check();
    if (res > 0 && res != TFS_WORK)
    {
      ItemPrev = ItemNew;
      ItemNew = CreateCheckSuperPosItem();
      ItemNew->Build(ItemPrev, C);
    }
    delete C;
    if (res == 0 || res == TFS_WORK)
      break;
  }
  SetupLevel();
  return res > 0;
}

int TCheckSuperPos::NextLevel()
{
  FLevelCounter++;
  return FLevelCounter;
}

void TCheckSuperPos::SetupLevel()
{
  int lvlBase = 0;
  int lvl1, lvl2;
  TBigWork* BW = NULL;
  TTFSInnerPath *Path1, *Path2;
  TFsTableItemData *L, *R;
  TFsTableItemData* HF;
  TFsList Stack;
  FLevelCounter = 0;
  FHeap->Clear();
  if(CountSuperPos > 0)
  {
    lvlBase = NextLevel();
    TCheckSuperPosItem* S = ItemsSuperPos[CountSuperPos-1];
    for(int i = 0; i < S->Count; i++)
    {
      TFsTableItem* Item = S->Items[i];
      Item->Left->Level = lvlBase;
      Item->Right->Level = lvlBase;
      FHeap->Add(Item->Left);
      FHeap->Add(Item->Right);
      if (Item->Left->IsBigWork())
        BW = FindBigWork(Item->Left->Num);
      if (Item->Right->IsBigWork())
        BW = FindBigWork(Item->Right->Num);
    }
  }
  if (BW)
  {
    BW->Level = lvlBase;
    Stack.Add(BW);
  }
  while(!Stack.IsEmpty())
  {
    BW = (TBigWork*)Stack.Delete(0);
    lvlBase = BW->Level;
    Path1 = BW->InnerPath1;
    Path2 = BW->InnerPath2;
    if (Path1->Count > 0)
      lvl1 = NextLevel();
    if (Path2->Count > 0)
      lvl2 = NextLevel();
    for(int i = 0; i < BW->Count; i++)
    {
      L = BW->Items[i]->Left;
      R = BW->Items[i]->Right;
      HF = FHeap->Find(L);
      if (HF)
        L->Level = HF->Level;
      else
      {
        L->Level = lvlBase;
        FHeap->Add(L);
      }

      HF = FHeap->Find(R);
      if (HF)
        R->Level = HF->Level;
      else
      {
        R->Level = lvlBase;
        FHeap->Add(R);
      }


      if (Path1->Exists(L))
      {
        L->Level = lvl1;
        HF = FHeap->Find(L);
        if (HF)
          HF->Level = L->Level;
        else
          FHeap->Add(L);
      }
      if (Path2->Exists(L))
      {
        L->Level = lvl2;
        HF = FHeap->Find(L);
        if (HF)
          HF->Level = L->Level;
        else
          FHeap->Add(L);
      }


      if (Path1->Exists(R))
      {
        R->Level = lvl1;
        HF = FHeap->Find(R);
        if (HF)
          HF->Level = R->Level;
        else
          FHeap->Add(R);

      }
      if (Path2->Exists(R))
      {
        R->Level = lvl2;
        HF = FHeap->Find(R);
        if (HF)
          HF->Level = R->Level;
        else
          FHeap->Add(R);
      }

      if (L->IsBigWork())
      {
        TBigWork* BigWork = FindBigWork(L->Num);
        if (!Stack.IsExists(BigWork))
        {
          BigWork->Level = L->Level;
          Stack.Add(BigWork);
        }
      }

      if (R->IsBigWork())
      {
        TBigWork* BigWork = FindBigWork(R->Num);
        if (!Stack.IsExists(BigWork))
        {
          BigWork->Level = R->Level;
          Stack.Add(BigWork);
        }  
      }

    }

  }
}
