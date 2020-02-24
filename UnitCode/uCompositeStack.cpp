//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeStack.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/*
class TCompositeStackItem
{
    private:
      TList* f_List;
      int f_IDShape;
    public:
      TCompositeStackItem(int AIDShape);
      ~TCompositeStackItem();
      void AddTFS(TAlternateViewItemTFS* AItem);
      __property int IDShape = {read = f_IDShape};
      __property int TFSCount = {read = GetTFSCount};
      __property TAlternateViewItemTFS* TFSItems[int AIndex] = {read = GetTFSItems};

};
*/

TCompositeStackItem::TCompositeStackItem(int AIDShape)
{
   f_IDShape = AIDShape;
   f_List = new TList;
}

TCompositeStackItem::~TCompositeStackItem()
{
   delete f_List;
}

void TCompositeStackItem::AddTFS(TAlternateViewItemTFS* AItem)
{
   f_List->Add(AItem);
}

TAlternateViewItemTFS* __fastcall TCompositeStackItem::GetTFSItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TCompositeStackItem::GetTFSCount()
{
   return  f_List->Count;
}


/*
class TCompositeStack
{
   private:
     TList* f_ListBase;
     TList* f_ListN;
   public:
     TCompositeStack();
     ~TCompositeStack();
     void AddBaseWork(TCompositeBaseWork* ABW);
     TCompositeStackItem* CreateItem(int AID);
};
*/

TCompositeStack::TCompositeStack()
{
   f_ListBase = new TList;
   f_ListN = new TList;
}

TCompositeStack::~TCompositeStack()
{
   FreeListN();
   delete f_ListBase;
   delete f_ListN;
}

void TCompositeStack::FreeListN()
{
   TCompositeStackItem* Item;
   for (int i = f_ListN->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TCompositeStackItem*>(f_ListN->Items[i]);
      delete Item;
      f_ListN->Delete(i);
   }
}

void TCompositeStack::AddBaseWork(TAlternateViewItemTFS* ABW)
{
   if (ABW)
     f_ListBase->Add(ABW);
}

TCompositeStackItem* TCompositeStack::CreateItem(int AID)
{
   TCompositeStackItem *Item = NULL;
   for (int i = f_ListN->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TCompositeStackItem*>(f_ListN->Items[i]);
      if (Item->IDShape == AID)
        return Item;
   }
   Item = new TCompositeStackItem(AID);
   f_ListN->Add(Item);
   return Item;
}

bool TCompositeStack::IsEmpty()
{
   return (f_ListN->Count == 0);
}

void TCompositeStack::Pop()
{
   TCompositeStackItem* Item;
   if (!IsEmpty())
   {
      int ind = f_ListN->Count - 1;
      Item = static_cast<TCompositeStackItem*>(f_ListN->Items[ind]);
      delete Item;
      f_ListN->Delete(ind);
   }
}

TAlternateViewItemTFS* __fastcall TCompositeStack::GetBaseItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListBase->Count - 1)
     return static_cast<TAlternateViewItemTFS*>(f_ListBase->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TCompositeStack::GetBaseCount()
{
    return f_ListBase->Count;
}


TCompositeStackItem* __fastcall TCompositeStack::GetSTIItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListN->Count - 1)
     return static_cast<TCompositeStackItem*>(f_ListN->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TCompositeStack::GetSTICount()
{
    return f_ListN->Count;
}

