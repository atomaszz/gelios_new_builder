//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGraphTFEConvertorTransNum.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TGraphTFEConvertorTransNumTFS::TGraphTFEConvertorTransNumTFS()
{
  f_Name = "";
  f_NumAlt = 0;
  f_ParentID = 0;
  f_ParentIDReal = 0;
  f_ListItem = new TList;
}

TGraphTFEConvertorTransNumTFS::~TGraphTFEConvertorTransNumTFS()
{
  FreeList();
  delete f_ListItem;
}

void TGraphTFEConvertorTransNumTFS::FreeList()
{
   TGraphTFEConvertorTransNumItem* Item;
   for (int i = 0; i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TGraphTFEConvertorTransNumItem*>(f_ListItem->Items[i]);
      delete Item;
   }
   f_ListItem->Clear();
}

TGraphTFEConvertorTransNumItem* TGraphTFEConvertorTransNumTFS::AddItem(int AId,
  int AOldId, int APrefix)
{
   TGraphTFEConvertorTransNumItem* Item = new TGraphTFEConvertorTransNumItem;
   Item->ID = AId;
   Item->OldID = AOldId;
   Item->Prefix = APrefix;
   f_ListItem->Add(Item);
   return Item;
}

int __fastcall TGraphTFEConvertorTransNumTFS::GetItemCount()
{
  return f_ListItem->Count;
}

TGraphTFEConvertorTransNumItem* __fastcall TGraphTFEConvertorTransNumTFS::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListItem->Count - 1)
     return static_cast<TGraphTFEConvertorTransNumItem*>(f_ListItem->Items[AIndex]);
   else
     return NULL;
}



//------------------------TGraphTFEConvertorTransNum---------------------------
TGraphTFEConvertorTransNum::TGraphTFEConvertorTransNum()
{
   TGraphTFEConvertorTransNumTFS* Head = new  TGraphTFEConvertorTransNumTFS;
   Head->AddItem(1,0,0);
   f_List = new TList;
   f_NGen = new TPredicateNumGenerator;
   f_List->Add(Head);
   f_NGen->InitNum(1);
}

TGraphTFEConvertorTransNum::~TGraphTFEConvertorTransNum()
{
   FreeList();
   delete f_List;
   delete f_NGen;
}

void TGraphTFEConvertorTransNum::FreeList()
{
   TGraphTFEConvertorTransNumTFS* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TGraphTFEConvertorTransNumTFS*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}


int TGraphTFEConvertorTransNum::GetPrefix(TGraphTFEConvertorItem* AItem)
{
   int res = 0;
   TGraphTFEConvertorTransNumTFS* m_tfs;
   TDynamicArray *D = new TDynamicArray;
   AItem->ListIDFromTFE(D);
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      m_tfs = static_cast<TGraphTFEConvertorTransNumTFS*>(f_List->Items[i]);
      int cmp = 0;
      if ( (AItem->ParentID == m_tfs->ParentIDReal ) && (D->Count == m_tfs->ItemCount) )
      {
         for (int j =0; j <= m_tfs->ItemCount - 1; j++ )
         {
            if (m_tfs->Items[j]->OldID == int(D->Items[j]) )
             cmp++;
         }
      }
      if (cmp == D->Count)
        res++;
   }
   delete D;
   return res;
}

int TGraphTFEConvertorTransNum::GetPrefixForItem(int ANum)
{
   int res = 0;
   TGraphTFEConvertorTransNumTFS* m_tfs;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      m_tfs = static_cast<TGraphTFEConvertorTransNumTFS*>(f_List->Items[i]);
      for (int j =0; j <= m_tfs->ItemCount - 1; j++ )
      {
         if (m_tfs->Items[j]->OldID == ANum )
           res++;
      }
   }
   return res;
}


int TGraphTFEConvertorTransNum::GetParentID(TGraphTFEConvertorItem* AItem, int APrefix)
{
   TGraphTFEConvertorTransNumTFS* m_tfs;
   TGraphTFEConvertorTransNumItem* m_item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      m_tfs = static_cast<TGraphTFEConvertorTransNumTFS*>(f_List->Items[i]);
      for (int j =0; j <= m_tfs->ItemCount - 1; j++ )
      {
         m_item = m_tfs->Items[j];
         if ( (m_item->OldID == AItem->ParentID) && (m_item->Prefix == APrefix) )
           return m_item->ID;
      }
   }
   return -1;
}



void TGraphTFEConvertorTransNum::AddGTItem(TGraphTFEConvertorItem* AItem)
{
   int m_prefix = GetPrefix(AItem);
   int m_parentID = GetParentID(AItem, m_prefix);

   TGraphTFEConvertorTransNumTFS* mTFS = new TGraphTFEConvertorTransNumTFS;
   mTFS->NumAlt = AItem->Item->NumAlt;
   mTFS->Name = AItem->Alias;
   mTFS->ParentID = m_parentID;
   mTFS->ParentIDReal = AItem->ParentID;

   TDynamicArray *D = new TDynamicArray;
   AItem->ListIDFromTFE(D);
   for (int i = 0; i <= D->Count -1; i++)
   {
      int i_n = int(D->Items[i]);
      int i_next = f_NGen->NextNum();
      int i_pref = GetPrefixForItem(i_n);
      mTFS->AddItem(i_next, i_n, i_pref);
   }
   delete D;
   f_List->Add(mTFS);
}

AnsiString TGraphTFEConvertorTransNum::ListIDFromItem(TGraphTFEConvertorTransNumTFS* AItem)
{
   AnsiString Res = "";
   int cnt = AItem->ItemCount;
   for (int i = 0; i <= cnt - 1; i++)
   {
      Res = Res + IntToStr(AItem->Items[i]->ID);
      if ( (i != cnt - 1) && (cnt > 1) )
        Res = Res + ", ";
   }
   return Res;
}


AnsiString TGraphTFEConvertorTransNum::DoMake(TGraphTFEConvertorTransNumTFS* AItem)
{
   AnsiString Res = "knot(" + IntToStr(AItem->ParentID) + "," +  IntToStr(AItem->NumAlt + 1) +", ";
   Res = Res + AItem->Name +", " + "[" + ListIDFromItem(AItem) + "]).";
   return Res;
}


AnsiString TGraphTFEConvertorTransNum::Make()
{
   AnsiString Res = "";
   TGraphTFEConvertorTransNumTFS* mTFS;
   for(int i = 1; i <= f_List->Count -1; i++ )
   {
      mTFS = static_cast<TGraphTFEConvertorTransNumTFS*>(f_List->Items[i]);
      Res = Res + DoMake(mTFS) + "\r\n";
   }
   return Res;
}





