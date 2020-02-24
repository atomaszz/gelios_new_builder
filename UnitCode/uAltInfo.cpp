//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAltInfo.h"
#include "uListShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TAltInfoItem::TAltInfoItem()
{
   f_Id = 0;
   f_Num = 0;
   f_ParentShapeId = 0;
   f_NodeStart =  NULL;
   f_NodeEnd = NULL;
   f_Main = false;
}

TAltInfo::TAltInfo()
{
   f_List = new TList;
}

TAltInfo::~TAltInfo()
{
   FreeList();
   delete f_List;
}

void TAltInfo::FreeList()
{
   TAltInfoItem* Item;
   for (int i = f_List->Count -  1; i >=0; i--)
   {
      Item = static_cast<TAltInfoItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

void TAltInfo::Clear()
{
   FreeList();
}

TAltInfoItem* TAltInfo::FindItem(int AId, int ANum, int AParentShapeId)
{
   TAltInfoItem* Item;
   for (int i = f_List->Count -  1; i >=0; i--)
   {
      Item = static_cast<TAltInfoItem*>(f_List->Items[i]);
      if ( (Item->f_Id == AId) && (Item->f_Num == ANum) && (Item->f_ParentShapeId == AParentShapeId) )
        return  Item;
   }
   return NULL;
}


TAltInfoItem* TAltInfo::AddAltIfo(int AId, int ANum, int AParentShapeId, TNodeMain* ANodeStart, TNodeMain* ANodeEnd)
{
   if ( FindItem(AId, ANum, AParentShapeId) ) return NULL;
   TAltInfoItem* Item = new TAltInfoItem;
   Item->f_Id = AId;
   Item->f_Num = ANum;
   Item->f_ParentShapeId = AParentShapeId;
   Item->f_NodeStart = ANodeStart;
   Item->f_NodeEnd = ANodeEnd;
   f_List->Add(Item);
   return  Item;
}

int __fastcall TAltInfo::GetItemCount()
{
   return f_List->Count;
}

TAltInfoItem* __fastcall TAltInfo::GetItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAltInfoItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}


