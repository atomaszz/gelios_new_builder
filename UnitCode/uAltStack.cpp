//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAltStack.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TAltStackItem
{
   private:
     int f_IdAlternative;
     int f_NumAlternative;
     int f_IdAlternativeParent;
     int f_NumAlternativeParent;
   public:
     TAltStackItem(int AIdAlternative, int ANumAlternative,  int AIdAlternativeParent,
        int ANumAlternativeParent);
     __property int IdAlternative = { read = f_IdAlternative};
     __property int NumAlternative =  {read =  f_NumAlternative};
     __property int IdAlternativeParent = { read = f_IdAlternativeParent};
     __property int NumAlternativeParent = { read = f_NumAlternativeParent};
};


class TAltStackController
{
   private:
     TList* f_List;
     void FreeList();
   public:
     TAltStackController();
     ~TAltStackController();
};
*/

TAltStackItem::TAltStackItem(int AIdAlternative, int ANumAlternative,  int AIdAlternativeParent,
        int ANumAlternativeParent)
{
   f_IdAlternative = AIdAlternative;
   f_NumAlternative = ANumAlternative;
   f_IdAlternativeParent = AIdAlternativeParent;
   f_NumAlternativeParent = ANumAlternativeParent;
}


TAltStackController::TAltStackController()
{
   f_List = new TList;
}

TAltStackController::~TAltStackController()
{
   FreeList();
   delete f_List;
}

void TAltStackController::FreeList()
{
   TAltStackItem* Item;
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAltStackItem*>(f_List->Items[i]);
      delete Item;
      Item = NULL;
      f_List->Delete(i);
   }
}

TAltStackItem* TAltStackController::Push(int AIdAlternative, int ANumAlternative,
  int AIdAlternativeParent,  int ANumAlternativeParent)
{
   TAltStackItem* Item = new TAltStackItem(AIdAlternative, ANumAlternative,
     AIdAlternativeParent,  ANumAlternativeParent);
   f_List->Add(Item);
   f_CurrentItem = Item;
/*   f_CurrentItem->IdAlternative = Item->IdAlternative;
   f_CurrentItem->NumAlternative = Item->NumAlternative;
   f_CurrentItem->IdAlternativeParent = Item->IdAlternativeParent;
   f_CurrentItem->NumAlternativeParent = Item->NumAlternativeParent;
*/
   return Item;
}


TAltStackItem*  TAltStackController::Pop()
{
   TAltStackItem* Item = NULL;
   int idx = f_List->Count;
   if ( idx > 1)
   {
      Item = static_cast<TAltStackItem*>(f_List->Items[idx - 2]);
      f_CurrentItem = Item;
/*      f_CurrentItem->IdAlternative = Item->IdAlternative;
      f_CurrentItem->NumAlternative = Item->NumAlternative;
      f_CurrentItem->IdAlternativeParent = Item->IdAlternativeParent;
      f_CurrentItem->NumAlternativeParent = Item->NumAlternativeParent;
*/
      DeleteLastLevel();
   }
   return Item;
}


void TAltStackController::DeleteLastLevel()
{
   TAltStackItem* Item;
   int idx = f_List->Count;
   if ( idx )
   {
      Item =  static_cast<TAltStackItem*>(f_List->Items[idx - 1]);
      delete Item;
      Item = NULL;
      f_List->Delete(idx - 1);
   }
}


void TAltStackController::ClearAll()
{
   FreeList();
}




