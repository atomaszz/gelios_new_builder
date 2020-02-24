//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeStack2.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TCompositeStackItem2::TCompositeStackItem2(TCompositeBaseWorkItem* ACompositeWorkItem, TCompositeBaseWork* ACompositeWork)
{
   f_CompositeWorkItem = ACompositeWorkItem;
   f_CompositeWork = ACompositeWork;
   f_List = new TList;
}

TCompositeStackItem2::~TCompositeStackItem2()
{
   delete f_List;
}

void TCompositeStackItem2::AddTFS(TAlternateViewItemTFS* AItem)
{
   f_List->Add(AItem);
}

TAlternateViewItemTFS* __fastcall TCompositeStackItem2::GetTFSItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TCompositeStackItem2::GetTFSCount()
{
   return  f_List->Count;
}


//---------------------------------------------------------------------------------------
TCompositeStack2::TCompositeStack2()
{
   f_ListN = new TList;
}

TCompositeStack2::~TCompositeStack2()
{
   FreeListN();
   delete f_ListN;
}

void TCompositeStack2::FreeListN()
{
   TCompositeStackItem2* Item;
   for (int i = f_ListN->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TCompositeStackItem2*>(f_ListN->Items[i]);
      delete Item;
      f_ListN->Delete(i);
   }
}


TCompositeStackItem2* TCompositeStack2::CreateItem(TCompositeBaseWorkItem* ACompositeWorkItem, TCompositeBaseWork* ACompositeWork)
{
   TCompositeStackItem2 *Item = NULL;
   for (int i = f_ListN->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TCompositeStackItem2*>(f_ListN->Items[i]);
      if ( (Item->CompositeWorkItem == ACompositeWorkItem) &&
         (Item->CompositeWork == ACompositeWork) )
        return Item;
   }
   Item = new TCompositeStackItem2(ACompositeWorkItem, ACompositeWork);
   f_ListN->Add(Item);
   return Item;
}

bool TCompositeStack2::IsEmpty()
{
   return (f_ListN->Count == 0);
}

TCompositeStackItem2* TCompositeStack2::Last()
{
   TCompositeStackItem2* Item = NULL;
   if (!IsEmpty())
   {
      int ind = f_ListN->Count - 1;
      Item = static_cast<TCompositeStackItem2*>(f_ListN->Items[ind]);
   }
   return Item;
}


void TCompositeStack2::Pop()
{
   TCompositeStackItem2* Item;
   if (!IsEmpty())
   {
      int ind = f_ListN->Count - 1;
      Item = static_cast<TCompositeStackItem2*>(f_ListN->Items[ind]);
      delete Item;
      f_ListN->Delete(ind);
   }
}



TCompositeStackItem2* __fastcall TCompositeStack2::GetSTIItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListN->Count - 1)
     return static_cast<TCompositeStackItem2*>(f_ListN->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TCompositeStack2::GetSTICount()
{
    return f_ListN->Count;
}
