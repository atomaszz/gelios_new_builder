//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uListLevel.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TLevelController
{
   private:
     TList* f_List;
     void FreeList();
   public:
     TLevelController();
     ~TLevelController();
     TLevelItem* Push(int AIdParentShape);
     TLevelItem* Pop();
     void DeleteLastLevel();

};
*/

TLevelItem::TLevelItem()
{
   f_IdParentShape = 0;
   f_X_offsSum = f_Y_offsSum = 0;
}


TLevelController::TLevelController()
{
   f_List = new TList;
   f_CurrentLevel = NULL;
}


TLevelController::~TLevelController()
{
   FreeList();
   delete f_List;
}


void TLevelController::FreeList()
{
   TLevelItem *Item;
   for(int i = f_List->Count - 1; i>=0; i--)
   {
      Item = static_cast<TLevelItem*>(f_List->Items[i]);
      delete Item;
      Item = NULL;
      f_List->Delete(i);
   }
}


TLevelItem* TLevelController::FindLevel(int AIdParentShape)
{
   TLevelItem *Item;
   for(int i = f_List->Count - 1; i>=0; i--)
   {
      Item = static_cast<TLevelItem*>(f_List->Items[i]);
      if (Item->IdParentShape == AIdParentShape)
        return Item;
   }
   return NULL;
}


TLevelItem* TLevelController::Push(int AIdParentShape)
{
   TLevelItem *Item = FindLevel(AIdParentShape);
   if ( !Item )
   {
      Item = new TLevelItem;
      Item->IdParentShape = AIdParentShape;
      f_List->Add(Item);
   }
   f_CurrentLevel = Item;
   return Item;
}


TLevelItem* TLevelController::Pop()
{
   TLevelItem *Item = NULL;
   int idx = f_List->Count;
   if ( idx > 1)
   {
      Item =  static_cast<TLevelItem*>(f_List->Items[idx - 2]);
      f_CurrentLevel = Item;
      DeleteLastLevel();
   }
   return Item;
}


void TLevelController::DeleteLastLevel()
{
   TLevelItem *Item;
   int idx = f_List->Count;
   if ( idx )
   {
      Item =  static_cast<TLevelItem*>(f_List->Items[idx - 1]);
      if ( f_CurrentLevel == Item ) f_CurrentLevel = NULL;
      delete Item;
      Item = NULL;
      f_List->Delete(idx - 1);
   }
}


int __fastcall TLevelController::GetParentShapeID()
{
   if (f_CurrentLevel)
     return f_CurrentLevel->IdParentShape;
   return 0;
}


void TLevelController::ClearAll()
{
   FreeList();
}

