//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicateTree.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TPredicateTreeItem::TPredicateTreeItem()
{
  f_ParentID = 0;
  f_TypeWorkShape = 0;
  f_NumAlt = 0;
  f_BaseWorkShape = NULL;
  f_ParentShape = NULL;
  f_TReated = false;
  f_List = new TDynamicArray;
}

TPredicateTreeItem::~TPredicateTreeItem()
{
  delete f_List;
}

int __fastcall TPredicateTreeItem::GetCount()
{
  return f_List->Count;
}

int __fastcall TPredicateTreeItem::GetTFE_ID(int AIndex)
{
   TDynamicArrayItem* P = f_List->Position[AIndex];
   if (P)
     return P->Int_Value;
   else
     return 0;
}

TBaseShape* __fastcall TPredicateTreeItem::GetTFE(int AIndex)
{
   TDynamicArrayItem* P = f_List->Position[AIndex];
   if (P)
     return static_cast<TBaseShape*>(P->P);
   else
     return NULL;
}

void TPredicateTreeItem::AddBaseShape(TBaseShape *AShape, int AID)
{
  f_List->AppendInteger(AID, AShape);
}


//-----------------------------------------------------------------------------
TPredicateTree::TPredicateTree()
{
  f_List = new TList;
}

TPredicateTree::~TPredicateTree()
{
  FreeList();
  delete f_List;
}

void TPredicateTree::FreeList()
{
   TPredicateTreeItem* Tmp;
   for (int i = f_List->Count - 1; i>=0; i--)
   {
      Tmp = static_cast<TPredicateTreeItem*>(f_List->Items[i]);
      delete Tmp;
   }
   f_List->Clear();

}

TPredicateTreeItem* TPredicateTree::NewPredicateTreeItem()
{
   TPredicateTreeItem* N = new TPredicateTreeItem;
   f_List->Add(N);
   return N;
}

void TPredicateTree::Clear()
{
   FreeList();
}

int __fastcall TPredicateTree::GetCount()
{
   return f_List->Count;
}

TPredicateTreeItem* __fastcall TPredicateTree::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicateTreeItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TPredicateTreeItem* TPredicateTree::FindByTfeID(int AID, TDynamicArray *Arr)
{
   TPredicateTreeItem *Item, *Res = NULL;
   if (Arr)
     Arr->Clear();
   for (int i = 0; i <= Count - 1; i++)
   {
     Item = Items[i];
     for (int j = 0; j <= Item->Count - 1 ; j++)
     {
       if (Item->TFE_ID[j] == AID)
       {
         if (!Res)
           Res = Item;
         if (Arr)
           Arr->Append(Item);
       }
     }
   }
   return Res;
}

TPredicateTreeItem* TPredicateTree::FindByParentID(int AID)
{
   TPredicateTreeItem *Item;
   for (int i = 0; i <= Count - 1; i++)
   {
     Item = Items[i];
     if (Item->ParentID == AID)
       return Item;
   }
   return NULL;
}


void TPredicateTree::ArrayIDToDelete(TPredicateTreeItem* AItem, TDynamicArray *Arr)
{
   TPredicateTreeItem* Item;
   Arr->Clear();
   int del, cfind;
   for (int i = 0; i <= AItem->Count - 1; i++)
   {
     del = AItem->TFE_ID[i];
     cfind = 0;
     for ( int j = 0; j <= f_List->Count - 1; j++)
     {
       Item = static_cast<TPredicateTreeItem*>(f_List->Items[j]);
       if (!Item->TReated && (Item != AItem))
       {
         for (int k = 0; k <= Item->Count - 1; k++)
           if (del == Item->TFE_ID[k])
             cfind++;
       }
     }
     if ( !cfind && !Arr->Find((void*)del) )
       Arr->Append((void*)del);

   }
}

