//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternativeParserGrp.h"
#include "uGlsAtmCommon.h"
#include "uMessengers.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TList *lc;
int APC_CompareNode(void* A, void* B)
{
   TAlternativeParserGrpItemTFS* m_A = static_cast<TAlternativeParserGrpItemTFS*>(A);
   TAlternativeParserGrpItemTFS* m_B = static_cast<TAlternativeParserGrpItemTFS*>(B);
   int res = GMess->SendMess(3, int(m_A->TFS->BaseWorkShape), int(m_B->TFS->BaseWorkShape));
   if (res == -100)
     throw Exception("Исключительная ошибка в алгоритме программы. Обратитесь к разработчику.");
   return res;
}

bool APC_Inorder(void* A)
{
   lc->Add(A);
   return true;
}



// ----------------  TAlternativeParserGrpItemTFS ----------------------
TAlternativeParserGrpItemTFS::TAlternativeParserGrpItemTFS()
{
   f_TFS = NULL;
}



// ----------------  TAlternativeParserGrpItemList ----------------------
TAlternativeParserGrpItemList::TAlternativeParserGrpItemList()
{
   f_List = new TList;
   f_CheckAgregate = false;
   f_Agregate = NULL;
   f_CheckCross = false;
   f_Alternative = NULL;
}

TAlternativeParserGrpItemList::~TAlternativeParserGrpItemList()
{
   FreeList();
   delete f_List;
}

void TAlternativeParserGrpItemList::FreeList()
{
   TAlternativeParserGrpItemTFS* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

TAlternativeParserGrpItemTFS* TAlternativeParserGrpItemList::FindItemTfs(TTreeListTFS* ATFS)
{
   TAlternativeParserGrpItemTFS* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[i]);
      if (Item->TFS == ATFS)
         return Item;
   }
   return NULL;
}

void TAlternativeParserGrpItemList::AddTfs(TTreeListTFS* ATFS)
{
   if (!FindItemTfs(ATFS))
   {
      TAlternativeParserGrpItemTFS* T = new TAlternativeParserGrpItemTFS;
      T->TFS =ATFS;
      f_List->Add(T);
   }
}


int __fastcall TAlternativeParserGrpItemList::GetCount()
{
   return f_List->Count;
}

TAlternativeParserGrpItemTFS* __fastcall TAlternativeParserGrpItemList::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void __fastcall TAlternativeParserGrpItemList::SetAgregate(TAlternativeParserGrpItemList* AValue)
{
   if (f_Agregate)
   {
      int m_new = AValue->Count;
      int m_prev = f_Agregate->Count;
      if (m_new > m_prev)
        f_Agregate = AValue;
   }
   else
     f_Agregate = AValue;
}

//--------------------------------------------------------------------


// ----------------  TAlternativeParserGrpCrossItemEnlarge ----------------------
TAlternativeParserGrpCrossItemEnlarge::TAlternativeParserGrpCrossItemEnlarge()
{
   f_List = new TList;
}

TAlternativeParserGrpCrossItemEnlarge::~TAlternativeParserGrpCrossItemEnlarge()
{
   FreeList();
   delete f_List;
}

void TAlternativeParserGrpCrossItemEnlarge::FreeList()
{
/*   TAlternativeParserGrpItemTFS* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
*/
}


void TAlternativeParserGrpCrossItemEnlarge::AddGRPTfs(TAlternativeParserGrpItemTFS* ATFS)
{
   f_List->Add(ATFS);
}


int __fastcall TAlternativeParserGrpCrossItemEnlarge::GetCount()
{
   return f_List->Count;
}

TAlternativeParserGrpItemTFS* __fastcall TAlternativeParserGrpCrossItemEnlarge::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TAlternativeParserGrpItemTFS* __fastcall TAlternativeParserGrpCrossItemEnlarge::GetPos()
{
   return Items[0];
}



//------------------------- TAlternativeParserGrpCrossItemOut ----------------
TAlternativeParserGrpCrossItemOut::TAlternativeParserGrpCrossItemOut()
{
   f_List = new TList;
}

TAlternativeParserGrpCrossItemOut::~TAlternativeParserGrpCrossItemOut()
{
   delete f_List;
}


int __fastcall TAlternativeParserGrpCrossItemOut::GetCount()
{
   return f_List->Count;
}

TAlternativeParserGrpItemList* __fastcall TAlternativeParserGrpCrossItemOut::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemList*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TAlternativeParserGrpCrossItemOut::AddItem(TAlternativeParserGrpItemBase* AItem)
{
   if (f_List->IndexOf(AItem) <  0)
     f_List->Add(AItem);
}

void TAlternativeParserGrpCrossItemOut::ReplaceToEnlarge(TAlternativeParserGrpCrossItemEnlarge* AE)
{
    int index = f_List->IndexOf(AE->Pos);
    f_List->Insert(index, AE);
    for (int i = 0; i <= AE->Count - 1; i++)
    {
       index = f_List->IndexOf(AE->Items[i]);
       if (index>=0)
         f_List->Delete(index);
    }
}






//-------------------------  TAlternativeParserGrpCrossItem ------------------
TAlternativeParserGrpCrossItem::TAlternativeParserGrpCrossItem()
{
   f_List = new TList;
   f_Basis = new TList;
   f_Out = new TList;
}

TAlternativeParserGrpCrossItem::~TAlternativeParserGrpCrossItem()
{
   FreeOut();
   delete f_List;
   delete f_Basis;
   delete f_Out;
}

int __fastcall TAlternativeParserGrpCrossItem::GetCount()
{
   return f_List->Count;
}

void TAlternativeParserGrpCrossItem::FreeOut()
{
   TAlternativeParserGrpCrossItemOut* Item;
   for (int i = 0; i <= f_Out->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserGrpCrossItemOut*>(f_Out->Items[i]);
      delete Item;
   }
   f_Out->Clear();
}



TAlternativeParserGrpItemList* __fastcall TAlternativeParserGrpCrossItem::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemList*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TAlternativeParserGrpCrossItem::GetCountBasis()
{
   return f_Basis->Count;
}


TAlternativeParserGrpItemBase* __fastcall TAlternativeParserGrpCrossItem::GetItemsBasis(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_Basis->Count - 1)
     return static_cast<TAlternativeParserGrpItemBase*>(f_Basis->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TAlternativeParserGrpCrossItem::GetCountOut()
{
   return f_Out->Count;
}

TAlternativeParserGrpCrossItemOut* __fastcall TAlternativeParserGrpCrossItem::GetItemsOut(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_Out->Count - 1)
     return static_cast<TAlternativeParserGrpCrossItemOut*>(f_Out->Items[AIndex]);
   else
     return NULL;
}



void TAlternativeParserGrpCrossItem::AddItem(TAlternativeParserGrpItemList* AGList)
{
   if (f_List->IndexOf(AGList) < 0)
     f_List->Add(AGList);
}


void TAlternativeParserGrpCrossItem::DoCreateBasis()
{
   TGlsBinaryTree *mTree;
   TAlternativeParserGrpItemTFS* Tfs;
   TAlternativeParserGrpItemList* Item;
   TDynamicArray *D = new TDynamicArray;
   lc = new TList;
   f_Basis->Clear();
   for (int i = 0; i <= Count - 1; i++ )
   {
     Item = Items[i];
     for (int j = 0; j <= Item->Count - 1; j++ )
     {
        Tfs = Item->Items[j];
        if (!D->Find(Tfs->TFS))
          D->AppendInteger((int)Tfs, Tfs->TFS);
     }
   }
   mTree = new TGlsBinaryTree(APC_CompareNode);
   for (int i = 0; i <= D->Count - 1; i++)
   {
      Tfs = (TAlternativeParserGrpItemTFS*)D->Position[i]->Int_Value;
      mTree->insert(Tfs);
   }
   mTree->inorder(APC_Inorder);
   for (int i = 0; i <= lc->Count - 1; i++)
   {
      Tfs = static_cast<TAlternativeParserGrpItemTFS*>(lc->Items[i]);
      f_Basis->Add(Tfs);
   }
   delete mTree;
   delete D;
   delete lc;
}

void TAlternativeParserGrpCrossItem::CreateBasis()
{
  DoCreateBasis();
}

void TAlternativeParserGrpCrossItem::DoCreateListItem(TAlternativeParserGrpItemList* AItem,
  TAlternativeParserGrpCrossItemOut *ANew)
{
   int i;
   bool f_s = false;
   TAlternativeParserGrpItemBase *Base;
   TAlternativeParserGrpItemTFS *Tfs;
   TBaseWorkShape *WS, *WE;
   WS = AItem->Alternative->NodeStart->WorkShape;
   WE = AItem->Alternative->NodeEnd->WorkShape;
   for (i = 0; i <= CountBasis - 1; i++)
   {
      Base = ItemsBasis[i];
      if (!Base->Who())
      {
        Tfs = dynamic_cast<TAlternativeParserGrpItemTFS*>(Base);
        if (Tfs->TFS->BaseWorkShape == WS)
        {
          f_s = true;
          break;
        }
        ANew->AddItem(Tfs);
      }
   }
   if (f_s)
    ANew->AddItem(AItem);
   for (; i <= CountBasis - 1; i++)
   {
      Base = ItemsBasis[i];
      if (!Base->Who())
      {
        Tfs = dynamic_cast<TAlternativeParserGrpItemTFS*>(Base);
        if (Tfs->TFS->BaseWorkShape == WE)
          break;
      }
   }
   for (++i; i <= CountBasis - 1; i++)
     ANew->AddItem(ItemsBasis[i]);
}

TAlternativeParserGrpCrossItemOut* TAlternativeParserGrpCrossItem::GetNewCrossOut()
{
   TAlternativeParserGrpCrossItemOut* Item =  new TAlternativeParserGrpCrossItemOut;
   f_Out->Add(Item);
   return Item;
}


void TAlternativeParserGrpCrossItem::DoCreateList()
{
   TAlternativeParserGrpCrossItemOut* mOut;
   for (int i = 0; i <= Count - 1; i++ )
   {
     mOut = GetNewCrossOut();
     DoCreateListItem(Items[i], mOut);
   }
}

void TAlternativeParserGrpCrossItem::CreateListOut()
{
   DoCreateList();
}

void TAlternativeParserGrpCrossItem::ReplaceToEnlarge(TAlternativeParserGrpCrossItemEnlarge* AE)
{
    int index = f_Basis->IndexOf(AE->Pos);
    f_Basis->Insert(index, AE);
    for (int i = 0; i <= AE->Count - 1; i++)
    {
       index = f_Basis->IndexOf(AE->Items[i]);
       if (index>=0)
         f_Basis->Delete(index);
    }
}

TAlternativeParserGrpCrossItemEnlarge* TAlternativeParserGrpCrossItem::FindEnlarge(TAlternativeParserGrpItemTFS* ATfs)
{
   TAlternativeParserGrpItemBase *Base;
   TAlternativeParserGrpCrossItemOut *Outs;
   TAlternativeParserGrpCrossItemEnlarge* Enl;
   for(int i = 0; i <= CountBasis-1; i++)
   {
      Base = ItemsBasis[i];
      if (Base->Who() == 3)
      {
         Enl = dynamic_cast<TAlternativeParserGrpCrossItemEnlarge*>(Base);
         if (Enl->Pos == ATfs)
           return Enl;
      }
   }

   for(int i = 0; i <= CountOut - 1; i++)
   {
      Outs = ItemsOut[i];
      for (int j = 0; j <= Outs->Count - 1; j++)
      {
        Base = Outs->Items[j];
        if (Base->Who() == 3)
        {
           Enl = dynamic_cast<TAlternativeParserGrpCrossItemEnlarge*>(Base);
           if (Enl->Pos == ATfs)
             return Enl;
        }
      }
   }
   return NULL;
}

TAlternativeParserGrpCrossItemEnlarge* TAlternativeParserGrpCrossItem::RestructEnlarge(TAlternativeParserEnlargerTrashItem* ATrash)
{
   TAlternativeParserGrpItemTFS *Tfs;
   TAlternativeParserGrpItemBase *Base;
   TAlternativeParserGrpCrossItemOut *Outs;
   TAlternativeParserGrpCrossItemEnlarge* Enl = NULL;
   for(int i = 0; i <= CountBasis-1; i++)
   {
      Base = ItemsBasis[i];
      if ((Base->Who() == 0) && (Base == ATrash->Pos))
      {
         Enl = new TAlternativeParserGrpCrossItemEnlarge;
         Enl->ID = ATrash->ID;
         for (int j = i; j <= i + ATrash->Length - 1; j++ )
           Enl->AddGRPTfs(dynamic_cast<TAlternativeParserGrpItemTFS*>(ItemsBasis[j]));
         ReplaceToEnlarge(Enl);
      }

   }

   for(int i = 0; i <= CountOut - 1; i++)
   {
      Outs = ItemsOut[i];
      for (int j = 0; j <= Outs->Count - 1; j++)
      {
        Base = Outs->Items[j];
        if ( (Base->Who() == 0) && (Base == ATrash->Pos) )
        {
           if (!Enl)
           {
             Enl = new TAlternativeParserGrpCrossItemEnlarge;
             Enl->ID = ATrash->ID;
             for (int k = j; k <= j + ATrash->Length - 1; k++ )
               Enl->AddGRPTfs(dynamic_cast<TAlternativeParserGrpItemTFS*>(Outs->Items[k]));
           }
           Outs->ReplaceToEnlarge(Enl);
        }
      }
   }
   return Enl;
}



//------------------------------ TAlternativeParserGrpCross -------------------------
TAlternativeParserGrpCross::TAlternativeParserGrpCross()
{
   f_List = new TList;
}

TAlternativeParserGrpCross::~TAlternativeParserGrpCross()
{
   FreeList();
   delete f_List;
}

void  TAlternativeParserGrpCross::FreeList()
{
   TAlternativeParserGrpCrossItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpCrossItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}


TAlternativeParserGrpCrossItem* __fastcall TAlternativeParserGrpCross::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpCrossItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TAlternativeParserGrpCross::GetCount()
{
   return f_List->Count;
}

void TAlternativeParserGrpCross::AddItem(TAlternativeParserGrpItemList* A,
  TAlternativeParserGrpItemList* B)
{
  TAlternativeParserGrpItemList* T;
  TAlternativeParserGrpCrossItem* Item;
  for (int i = 0; i <= Count - 1; i++ )
  {
     Item = Items[i];
     for (int j = 0; j <= Item->Count - 1; j++ )
     {
       T = Item->Items[j];
       if ( (A == T) || (B == T))
       {
         Item->AddItem(A);
         Item->AddItem(B);
         return;
       }
     }
  }
  Item = new TAlternativeParserGrpCrossItem;
  Item->AddItem(A);
  Item->AddItem(B);
  f_List->Add(Item);
}


TAlternativeParserGrpCrossItem* TAlternativeParserGrpCross::FindToCross(TAlternativeParserGrpItemList* AItem)
{
  TAlternativeParserGrpItemList* T;
  TAlternativeParserGrpCrossItem* Item;
  for (int i = 0; i <= Count - 1; i++ )
  {
     Item = Items[i];
     for (int j = 0; j <= Item->Count - 1; j++ )
     {
       T = Item->Items[j];
       if (T == AItem)
         return Item;
     }
  }
  return NULL;
}


//--------------------------TAlternativeParserGrp ----------------------
TAlternativeParserGrp::TAlternativeParserGrp()
{
   f_List = new TList;
   f_ListOut = new TList;
   f_ListEnlarge = new TList;
   f_Cross = new TAlternativeParserGrpCross;
   f_FindListPos = 0;
   f_FindListPosNoCross = 0;
   f_Enlarger = new TAlternativeParserEnlarger;
}

TAlternativeParserGrp::~TAlternativeParserGrp()
{
   FreeList();
   FreeListOut();
   FreeListEnlarge();
   delete f_List;
   delete f_ListOut;
   delete f_Cross;
   delete f_Enlarger;
   delete f_ListEnlarge;
}

int __fastcall TAlternativeParserGrp::GetCountOUT()
{
   return f_ListOut->Count;
}

TAlternativeParserGrpItemBase* __fastcall TAlternativeParserGrp::GetItemsOUT(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_ListOut->Count - 1)
     return static_cast<TAlternativeParserGrpItemBase*>(f_ListOut->Items[AIndex]);
    else
     return NULL;
}


void TAlternativeParserGrp::FreeList()
{
   TAlternativeParserGrpItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}


void TAlternativeParserGrp::FreeListOut()
{
   f_ListOut->Clear();
}

TAlternativeParserGrpItemTFS* TAlternativeParserGrp::FindItemTfs(TTreeListTFS* ATFS)
{
   TAlternativeParserGrpItemTFS* Temp;
   TAlternativeParserGrpItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      int m_who = Item->Who();
      if (!m_who)
      {
         Temp = dynamic_cast<TAlternativeParserGrpItemTFS*>(Item);
         if (Temp->TFS == ATFS)
           return Temp;
      }
      if ( m_who == 1)
      {
        Temp =  dynamic_cast<TAlternativeParserGrpItemList*>(Item)->FindItemTfs(ATFS);
        if (Temp)
          return Temp;
      }
   }
   return NULL;
}

void TAlternativeParserGrp::AddTfs(TTreeListTFS* ATFS)
{
   if (!FindItemTfs(ATFS))
   {
      TAlternativeParserGrpItemTFS* T = new TAlternativeParserGrpItemTFS;
      T->TFS =ATFS;
      f_List->Add(T);
   }
}

void TAlternativeParserGrp::FreeItem(TAlternativeParserGrpItemBase* AItem)
{
   TAlternativeParserGrpItemBase* Del;
   int index = f_List->IndexOf(AItem);
   if (index >= 0)
   {
      Del = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[index]);
      delete Del;
      f_List->Delete(index);
   }

}


void TAlternativeParserGrp::CheckTFS()
{
   TAlternativeParserGrpItemTFS* Temp;
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList* List;
   TDynamicArray *mTfs = new TDynamicArray;
   TDynamicArray *mGrp = new TDynamicArray;
   TDynamicArray *mDbl = new TDynamicArray;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      int m_who = Item->Who();
      if (!m_who)
        mTfs->Append(Item);
      if (m_who == 1)
        mGrp->Append(Item);

   }
   for (int i = 0; i <= mTfs->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(mTfs->Items[i]);
      Temp = dynamic_cast<TAlternativeParserGrpItemTFS*>(Item);
      for (int j = 0; j <= mGrp->Count - 1 ; j++ )
      {
         Item = static_cast<TAlternativeParserGrpItemBase*>(mGrp->Items[j]);
         List = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
         if (List->FindItemTfs(Temp->TFS))
           mDbl->Append(Temp);
      }
   }
   for (int i = 0; i <= mDbl->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(mDbl->Items[i]);
      FreeItem(Item);
   }
   delete mDbl;
   delete mGrp;
   delete mTfs;
}

void  TAlternativeParserGrp::CheckList()
{
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList *List1, *List2;
   TDynamicArray *mList = new TDynamicArray;
   TDynamicArray *mDbl = new TDynamicArray;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      if (Item->Who() == 1)
        mList->Append(Item);

   }

   for (int i = 0; i <= mList->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(mList->Items[i]);
      List1 = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
      for (int j = i + 1; j <= mList->Count - 1 ; j++ )
      {
         Item = static_cast<TAlternativeParserGrpItemBase*>(mList->Items[j]);
         List2 = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
         if (IdentityAlternate(List1, List2))
           mDbl->Append(Item);
      }
   }
   for (int i = 0; i <= mDbl->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(mDbl->Items[i]);
      FreeItem(Item);
   }
   delete mDbl;
   delete mList;
}


TAlternativeParserGrpItemList* TAlternativeParserGrp::GetNewList(TAlternateTreeList* Alternative)
{
   TAlternativeParserGrpItemList* Item =  new TAlternativeParserGrpItemList;
   Item->Alternative = Alternative;
   f_List->Add(Item);
   return Item;
}                   

void TAlternativeParserGrp::Clear()
{
   FreeList();
   FreeListOut();
}

TAlternativeParserGrpItemList*  TAlternativeParserGrp::FindFirstList()
{
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList* Res;
   for (int i = 0; i <=  f_List->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      if ( Item->Who() == 1)
      {
        Res = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
        if (!Res->CheckAgregate)
        {
          f_FindListPos = i;
          return Res;
        }
      }
   }
   f_FindListPos = 0;
   return NULL;
}

TAlternativeParserGrpItemList*  TAlternativeParserGrp::FindNextList(TAlternativeParserGrpItemList* AByPass)
{
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList* Res;
   ++f_FindListPos;
   for (int i = f_FindListPos; i <=  f_List->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      if ( Item->Who() == 1)
      {
        Res = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
        if (Res != AByPass)
        {
          f_FindListPos = i;
          return Res;
        }
      }
   }
   return NULL;
}

TAlternativeParserGrpItemList*  TAlternativeParserGrp::FindFirstListNoCross()
{
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList* Res;
   for (int i = 0; i <=  f_List->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      if ( Item->Who() == 1)
      {
        Res = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
        if (!Res->CheckCross)
        {
          f_FindListPosNoCross = i;
          return Res;
        }
      }
   }
   f_FindListPosNoCross = 0;
   return NULL;
}

TAlternativeParserGrpItemList*  TAlternativeParserGrp::FindNextListNoCross(TAlternativeParserGrpItemList* AByPass)
{
   TAlternativeParserGrpItemBase* Item;
   TAlternativeParserGrpItemList* Res;
   ++f_FindListPosNoCross;
   for (int i = f_FindListPosNoCross; i <=  f_List->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      if ( Item->Who() == 1)
      {
        Res = dynamic_cast<TAlternativeParserGrpItemList*>(Item);
        if (Res != AByPass)
        {
          f_FindListPosNoCross = i;
          return Res;
        }
      }
   }
   return NULL;
}

bool TAlternativeParserGrp::IdentityAlternate(TAlternativeParserGrpItemList* AL1,
  TAlternativeParserGrpItemList* AL2)
{
   TTreeListTFS *Tfs1, *Tfs2;
   int m_d1 = AL1->Count;
   int m_d2 = AL2->Count;
   if (m_d2 != m_d1)
     return false;
   for (int i = 0; i <= m_d1 - 1; i++)
   {
     if (AL1->Items[i]->TFS !=  AL2->Items[i]->TFS )
       return false;
   }
   return true;
}




int TAlternativeParserGrp::CompareAlternate(TAlternativeParserGrpItemList* AL1,
       TAlternativeParserGrpItemList* AL2, TAlternativeParserGrpItemList** AMax,
       TAlternativeParserGrpItemList** AMin)
{
   int m_d1, m_d2, m_dMin;
   int m_find = 0;
   TTreeListTFS* m_TFS;
   TAlternativeParserGrpItemList *m_aMin, *m_aMax;
   m_d1 = AL1->Count;
   m_d2 = AL2->Count;
   if (m_d1 > m_d2)
   {
      m_dMin = m_d2;
      m_aMax = AL1;
      m_aMin = AL2;
   }
   else
   {
      m_dMin = m_d1;
      m_aMax = AL2;
      m_aMin = AL1;
   }
   (*AMax) = m_aMax;
   (*AMin) = m_aMin;

   for (int i = 0; i <= m_dMin-1; i++ )
   {
      m_TFS = m_aMin->Items[i]->TFS;
      if ( m_aMax->FindItemTfs(m_TFS) )
        m_find++;
   }
   if (!m_find)
     return -1; // не пересекаются
   if (m_find < m_dMin)
     return 1; // пересекаются
   if (m_find == m_dMin)
     return 0; // вложенные
   return -2;  

}


void TAlternativeParserGrp::MakeCross()
{
    TAlternativeParserGrpItemList *m_Cur, *m_Next;
    TAlternativeParserGrpItemList *m_Max, *m_Min;
    int m_res;
    while (true)
    {
      m_Cur = FindFirstListNoCross();
      if (!m_Cur)
        return;
      m_Next = FindNextListNoCross(m_Cur);
      while (m_Next)
      {
         m_res = CompareAlternate(m_Cur, m_Next, &m_Max, &m_Min);
         if (m_res == 1)
           f_Cross->AddItem(m_Cur, m_Next);
         m_Next = FindNextListNoCross(m_Cur);
      }
      m_Cur->CheckCross = true;
    }
}



void TAlternativeParserGrp::MakeAgregate()
{
    TAlternativeParserGrpItemList *m_Cur, *m_Next;
    TAlternativeParserGrpItemList *m_Max, *m_Min;
    int m_res;
    while (true)
    {
      m_Cur = FindFirstList();
      if (!m_Cur)
        return;
      m_Next = FindNextList(m_Cur);
      while (m_Next)
      {
         m_res = CompareAlternate(m_Cur, m_Next, &m_Max, &m_Min);
         switch (m_res)
         {
            case 0:
              m_Min->Agregate = m_Max;
              break;
         }
         m_Next = FindNextList(m_Cur);
      }
      m_Cur->CheckAgregate = true;
    }
}


TAlternativeParserGrpItemBase* TAlternativeParserGrp::CheckOut(TAlternativeParserGrpItemList* AItem)
{
   TAlternativeParserGrpItemBase* Res;
   if (AItem->Agregate)
   {
     Res  = f_Cross->FindToCross(AItem->Agregate);
     return Res;
   }  
   Res  = f_Cross->FindToCross(AItem);
   if (Res)
     return Res;
   return AItem;
}




void TAlternativeParserGrp::MakeOUT()
{
   TAlternativeParserGrpItemList* Temp;
   TAlternativeParserGrpItemBase* Item;
   TDynamicArray *D = new TDynamicArray;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpItemBase*>(f_List->Items[i]);
      int m_who = Item->Who();
      if (!m_who)
        f_ListOut->Add(Item);
      if ( m_who == 1)
      {
        Temp =  dynamic_cast<TAlternativeParserGrpItemList*>(Item);
        Item =  CheckOut(Temp);
        if (Item)
        {
          if (!D->Find(Item))
          {
            D->Append(Item);
            f_ListOut->Add(Item);
            if (Item->Who() == 2)
            {
              TAlternativeParserGrpCrossItem *iTmp = dynamic_cast<TAlternativeParserGrpCrossItem*>(Item);
              iTmp->CreateBasis();
              iTmp->CreateListOut();
            }
          }
        }
      }
   }
   delete D;
}

void TAlternativeParserGrp::MakeCrossDubles()
{
   TAlternativeParserGrpItemBase* Base;
   TAlternativeParserGrpCrossItem* Cross;
   f_Enlarger->Init();
   for (int i = 0; i <= f_ListOut->Count - 1; i++)
   {
      Base =  static_cast<TAlternativeParserGrpItemBase*>(f_ListOut->Items[i]);
      if (Base->Who() == 2)
      {
        Cross = dynamic_cast<TAlternativeParserGrpCrossItem*>(Base);
        f_Enlarger->Enlarge(Cross);
        RestructEnlarge(Cross);
      }
   }
}


void TAlternativeParserGrp::RestructEnlarge(TAlternativeParserGrpCrossItem* AItem)
{
   TAlternativeParserGrpItemTFS* mPos;
   TAlternativeParserGrpCrossItemEnlarge* Enl;
   TAlternativeParserEnlargerTrashItem* TrItem;
   TDynamicArray *Mass = new TDynamicArray;
   f_Enlarger->FindTrashItem(AItem, Mass);
   for (int i = 0; i <= Mass->Count - 1; i++)
   {
     TrItem = static_cast<TAlternativeParserEnlargerTrashItem*>(Mass->Items[i]);
     Enl = AItem->FindEnlarge(TrItem->Pos);
     if (!Enl)
       AddToListEnlarge(AItem->RestructEnlarge(TrItem));
   }
   delete Mass; 
}



void TAlternativeParserGrp::Make()
{
   FreeListOut();
   CheckList();
   CheckTFS();
   MakeCross();
   MakeAgregate();
   MakeOUT();
   MakeCrossDubles();
}


void TAlternativeParserGrp::AddToListEnlarge(TAlternativeParserGrpCrossItemEnlarge *AItem)
{
   if (f_ListEnlarge->IndexOf(AItem) == -1)
     f_ListEnlarge->Add(AItem);
}

void TAlternativeParserGrp::FreeListEnlarge()
{
   TAlternativeParserGrpCrossItemEnlarge *Item;
   for (int i = 0; i <= f_ListEnlarge->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserGrpCrossItemEnlarge*>(f_ListEnlarge->Items[i]);
      delete Item;
   }
   f_ListEnlarge->Clear();

}

