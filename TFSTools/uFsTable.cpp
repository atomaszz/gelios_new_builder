//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFsTable.h"
#include "uToolConsts.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool TFsTableItemData::IsTrans()
{
  return Type == ST_TRANS;
}

bool TFsTableItemData::IsRo()
{
  return Type == ST_RO;
}

bool TFsTableItemData::IsFunc()
{
  return Type == ST_FUNC;
}

bool TFsTableItemData::IsDiag()
{
  return Type == ST_DIAG;
}

bool TFsTableItemData::IsFin()
{
  return Type == ST_FIN;
}

bool TFsTableItemData::IsStart()
{
  return Type == ST_START;
}

bool TFsTableItemData::IsBigWork()
{
  return (Type == ST_RO) && (Num < 0);
}


bool TFsTableItem::IsFirst()
{
  return Left->Type == ST_BEGIN;
}

bool TFsTableItem::IsLast()
{
  return Right->Type == ST_END;
}

TFsTableItem::TFsTableItem()
{
  Left = new TFsTableItemData;
  Right = new TFsTableItemData;
}

TFsTableItem::~TFsTableItem()
{
  delete Left;
  delete Right;
}

AnsiString TFsTableItem::ToString()
{
  AnsiString Res = '(';
  if (Left->IsTrans())
    Res = Res + "T";
  if (Left->IsRo())
    Res = Res + "A";
  if (Left->IsFunc())
    Res = Res + "B";
  if (Left->IsDiag())
    Res = Res + "D";
  if (Left->IsFin())
    Res = Res + "F";
  if (Left->IsStart())
    Res = Res + "C";
  Res = Res + IntToStr(Left->Num) + ",";

  if (Right->IsTrans())
    Res = Res + "T";
  if (Right->IsRo())
    Res = Res + "A";
  if (Right->IsFunc())
    Res = Res + "B";
  if (Right->IsDiag())
    Res = Res + "D";
  if (Right->IsFin())
    Res = Res + "F";
  if (Right->IsStart())
    Res = Res + "C";

  Res = Res + IntToStr(Right->Num) + ")";
  return Res;
}

//-----------------------------------------

TFsTable::TFsTable()
{
  FList = new TList;
}


TFsTable::~TFsTable()
{
  FreeList();
  delete FList;
}

TFsTableItem* TFsTable::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItem*)(FList->Items[AIndex]);
}

void TFsTable::FreeList()
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItem* Item = (TFsTableItem*)FList->Items[i];
    delete Item;
  }
  FList->Clear();
}

void TFsTable::AddItem(TFsTableItemData ALeft, TFsTableItemData ARight)
{
   TFsTableItem* Item = new TFsTableItem;
   *(Item->Left) = ALeft;
   *(Item->Right) = ARight;
   FList->Add(Item);
}

/*
void TFsTable::Init()
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItem* Item = (TFsTableItem*)FList->Items[i];
    Item->Init();
  }
}
*/

TFsTableItem* TFsTable::FindFirst()
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItem* Item = (TFsTableItem*)FList->Items[i];
    if (Item->IsFirst())
      return Item;
  }
  return NULL;
}




