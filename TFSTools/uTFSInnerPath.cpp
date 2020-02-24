//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFSInnerPath.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TFsTableItemData* TTFSInnerPath::GetItems(int AIndex)
{
  if (AIndex < 0 || AIndex >= FList->Count)
    return NULL;
  return (TFsTableItemData*)(FList->Items[AIndex]);
}



void TTFSInnerPath::AddToPath(TFsTableItemData* AItem)
{
  if (!Exists(AItem))
  {
    TFsTableItemData* N = new TFsTableItemData;
    *(N) = *(AItem);
    FList->Add(N);
  }  
}

void TTFSInnerPath::FreeList()
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItemData* Item = (TFsTableItemData*)FList->Items[i];
    delete Item;
  }
  FList->Clear();
}


bool TTFSInnerPath::Exists(TFsTableItemData* AItem)
{
  for(int i = 0; i < FList->Count; i++)
  {
    TFsTableItemData* Item = (TFsTableItemData*)FList->Items[i];
    if ( (Item->Type == AItem->Type) && (Item->Num == AItem->Num))
      return true;
  }
  return false;
}


void TTFSInnerPath::CopyFrom(TTFSInnerPath *APath)
{
  FreeList();
  for(int i = 0; i < APath->Count; i++)
    AddToPath(APath->Items[i]);
}
