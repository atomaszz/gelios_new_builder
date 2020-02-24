//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMenuController.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TMenuController::TMenuController()
{
   f_List = new TList;
}

TMenuController::~TMenuController()
{
   FreeList();
   delete f_List;
}


void TMenuController::FreeList()
{
   TMenuItem* Item;
   for (int i = f_List->Count - 1; i >= 0 ; i--)
   {
      Item = static_cast<TMenuItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

void TMenuController::AddMenu(TMenuItem *Item)
{
   f_List->Add(Item);
}

void TMenuController::Clear()
{
   FreeList();
}
