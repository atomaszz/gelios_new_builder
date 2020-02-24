//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTreeListItem.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TMainTreeList
{
   private:
     TList *f_List;
   public:
     TMainTreeList();
     ~TMainTreeList();
};
*/

TMainTreeList::TMainTreeList()
{
   f_List = new TList;
   f_Level = -1;
}

TMainTreeList::~TMainTreeList()
{
   FreeList();
   delete f_List;
}

void TMainTreeList::AddToTree(TAlternateTreeList *Item)
{
   if (Item)
     f_List->Add(Item);
}


void TMainTreeList::Clear()
{
   FreeList();
}

void TMainTreeList::FreeList()
{
   TAlternateTreeList *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TAlternateTreeList*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}


int __fastcall TMainTreeList::GetItemCount()
{
   return  f_List->Count;
}

TAlternateTreeList* __fastcall TMainTreeList::GetAlternateItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateTreeList*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TAlternateTreeList* __fastcall TMainTreeList::GetMainAlternative()
{
    TAlternateTreeList* Res;
    for (int i = 0; i <= ItemCount - 1; i++)
    {
        Res = AlternateItem[i];
        if (Res->MainAlternative)
          return Res;
    }
    return NULL;
}


TTreeListItem* TMainTreeList::FindTFE(TBaseShape* ABaseShape)
{
   TTreeListItem* Res;
   for (int i = 0; i <= ItemCount - 1; i++)
     for (int j = 0; j <= AlternateItem[i]->ItemCount - 1; j++)
        for (int k = 0; k <= AlternateItem[i]->TreeTFSItem[j]->ItemCount - 1; k++ )
        {
           Res = AlternateItem[i]->TreeTFSItem[j]->TreeTFEItem[k];
           if (Res->BaseShape == ABaseShape)
             return Res;
        }
   return NULL;

}


void TMainTreeList::FindAlternate(TBaseWorkShape* ABaseWorkShape,
   TDynamicArray *D)
{
   TBaseWorkShape* Tfs;
   D->Clear();
   for (int i = 0; i <= ItemCount - 1; i++)
   {
      Tfs  = AlternateItem[i]->NodeStart->WorkShape;
      if (Tfs == ABaseWorkShape)
        D->Append(AlternateItem[i]);
   }
}

void TMainTreeList::FindAlternate2(TBaseWorkShape* AFirstWorkShape,
  TBaseWorkShape* AEndWorkShape,   TDynamicArray *D)
{
   TBaseWorkShape *Tfs1, *Tfs2;
   D->Clear();
   for (int i = 0; i <= ItemCount - 1; i++)
   {
      Tfs1  = NULL;
      Tfs2  = NULL;
      if (AlternateItem[i]->NodeStart)
        Tfs1  = AlternateItem[i]->NodeStart->WorkShape;
      if (AlternateItem[i]->NodeEnd)
        Tfs2  = AlternateItem[i]->NodeEnd->WorkShape;
      if ( (Tfs1 == AFirstWorkShape) && (Tfs2 == AEndWorkShape) )
        D->Append(AlternateItem[i]);
   }
}




void TMainTreeList::GetTreeListTFSFromMainAlternative(TAlternateTreeList* Alternative, TDynamicArray *D)
{
   D->Clear();
   TAlternateTreeList *Item;
   TBaseWorkShape *NS, *NE, *CR;
   TTreeListTFS* Tmp;
   bool f = false;
   bool e = false;
   TAlternateTreeList* MA = MainAlternative;
   for (int i = 0; i <= ItemCount - 1; i++)
   {
      Item  = AlternateItem[i];
      if (Item == Alternative)
      {
         NS = Item->NodeStart->WorkShape;
         NE = Item->NodeEnd->WorkShape;
         for (int j = 0; j <= MA->ItemCount - 1; j++)
         {
            Tmp = MA->TreeTFSItem[j];
            CR = Tmp->BaseWorkShape;
            if  ( !f && (CR == NS) )
              f = true;

            if ( f && !e )
              D->Append(Tmp);

            if  ( !e && (CR == NE) )
              e = true;

         }
      }
   }
}






TAlternateTreeList::TAlternateTreeList()
{
   f_List = new TList;
   f_Main = false;
   f_NodeStart = NULL;
   f_NodeEnd = NULL;
   f_ID = -1;
   f_Num = -1;
}


TAlternateTreeList::~TAlternateTreeList()
{
   FreeList();
   delete f_List;
}


void TAlternateTreeList::FreeList()
{
   TTreeListTFS *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TTreeListTFS*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}


int __fastcall TAlternateTreeList::GetItemCount()
{
   return f_List->Count;
}


TTreeListTFS* __fastcall TAlternateTreeList::GetTreeTFSItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TTreeListTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}


void TAlternateTreeList::AddToAlternate(TTreeListTFS *Item)
{
   if (Item)
     f_List->Add(Item);
}

TTreeListItem* TAlternateTreeList::FindTFE(TBaseShape* ABaseShape)
{
   TTreeListItem* Res;
   for (int i = 0; i <= ItemCount - 1; i++)
     for (int j = 0; j <= TreeTFSItem[i]->ItemCount - 1; j++)
     {
       Res = TreeTFSItem[i]->TreeTFEItem[j];
       if (Res->BaseShape == ABaseShape)
             return Res;
     }
   return NULL;
}

TTreeListTFS* TAlternateTreeList::FindTFS(TBaseWorkShape* AWS)
{
   TTreeListTFS* Res;
   for (int i = 0; i <= ItemCount - 1; i++)
   {
      Res = TreeTFSItem[i];
      if(Res->BaseWorkShape == AWS)
        return Res;
   }
   return NULL;
}



TTreeListTFS::TTreeListTFS(TBaseWorkShape * ABaseWorkShape)
{
   TBaseShape *mBS;
   TTreeListItem *TL;
   f_BaseWorkShape = ABaseWorkShape;
   f_List = new TList;
   for (int i = 0; i <= f_BaseWorkShape->WorkShapesCount - 1 ; i++)
   {
      mBS = f_BaseWorkShape->GetWorkShape(i);
      TL = new TTreeListItem(mBS);
      f_List->Add(TL);
   }
}


TTreeListTFS::~TTreeListTFS()
{
   FreeList();
   delete f_List;
}



void TTreeListTFS::FreeList()
{
   TTreeListItem *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TTreeListItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

int __fastcall TTreeListTFS::GetItemCount()
{
   return  f_List->Count;
}

TTreeListItem* __fastcall TTreeListTFS::GetTreeTFEItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TTreeListItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TTreeListItem::TTreeListItem(TBaseShape *ABaseShape)
{
   f_BaseShape = ABaseShape;
   f_MainNode = NULL;
}

TTreeListItem::~TTreeListItem()
{
   if (f_MainNode)
     delete f_MainNode;
}






