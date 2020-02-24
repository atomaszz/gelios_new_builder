//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternateViewItem.h"
#include "uTreeListItem.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TAlternateViewItem::TAlternateViewItem()
{
   f_List = new TList;
   ArrayChild = new TDynamicArray;
   f_WSStart = NULL;
   f_WSEnd = NULL;
   f_MainTreeList = NULL;
   f_Fixed = false;
   f_ParentTFE = NULL;
   f_Parent = NULL;
}

TAlternateViewItem::~TAlternateViewItem()
{
   FreeList();
   delete f_List;
   delete ArrayChild;
}

void TAlternateViewItem::FreeList()
{
   TAlternateViewItemTFS* Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TAlternateViewItemTFS*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

TAlternateViewItemTFS* TAlternateViewItem::AddItemTFS(TBaseWorkShape* ABaseWorkShape, bool ACheck)
{
   TAlternateViewItemTFS *Item = new TAlternateViewItemTFS(ABaseWorkShape);
   Item->Check = ACheck;
   f_List->Add(Item);
   return Item;
}


int __fastcall TAlternateViewItem::GetItemCount()
{
   return  f_List->Count;
}

TAlternateViewItemTFS* __fastcall TAlternateViewItem::GetItemTFS(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TAlternateViewItem::SetFixedTFE(TBaseShape *ABaseShape, bool AFixed)
{
   TAlternateViewItemTFE* TFE;
   for(int i = 0; i <= ItemCount - 1; i++)
   {
     for (int j = 0; j <= ItemTFS[i]->ItemCount - 1; j++)
     {
        TFE = ItemTFS[i]->ItemTFE[j];
        if (TFE->BaseShape == ABaseShape)
          TFE->Fixed = AFixed;
      }
   }
}


//--------------------------------------------------------------------------
TAlternateViewItemTFS::TAlternateViewItemTFS(TBaseWorkShape* ABaseWorkShape)
{
   TBaseShape *mBS;
   TAlternateViewItemTFE *Tfe;
   f_List = new TList;
   f_BaseWorkShape = ABaseWorkShape;
   for (int i = 0; i <= f_BaseWorkShape->WorkShapesCount - 1 ; i++)
   {
      mBS = f_BaseWorkShape->GetWorkShape(i);
      Tfe = new TAlternateViewItemTFE(mBS);
      f_List->Add(Tfe);
   }
   f_Check = false;
}

TAlternateViewItemTFS::~TAlternateViewItemTFS()
{
   FreeList();
   delete f_List;
}

void  TAlternateViewItemTFS::FreeList()
{
   TAlternateViewItemTFE* Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TAlternateViewItemTFE*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

int __fastcall TAlternateViewItemTFS::GetItemCount()
{
   return  f_List->Count;
}

TAlternateViewItemTFE* __fastcall TAlternateViewItemTFS::GetItemTFE(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItemTFE*>(f_List->Items[AIndex]);
   else
     return NULL;
}


//---------------------------------------------------------------------------
TAlternateViewItemTFE::TAlternateViewItemTFE(TBaseShape *ABaseShape)
{
   f_BaseShape = ABaseShape;
   f_NextItem = NULL;
   f_Fixed = false;
}

TAlternateViewItemTFE::~TAlternateViewItemTFE()
{
 //  if (f_NextItem)
 //    delete f_NextItem;
}


