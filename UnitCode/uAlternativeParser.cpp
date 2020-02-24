//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternativeParser.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
// ----------------  TAlternativeParserItemBase ----------------------
TAlternativeParserItemBase::TAlternativeParserItemBase()
{
   f_MainTree = NULL;
   f_OwnerBig = NULL;
   f_NumAlt = 0;
}

TAlternativeParserItemBase::~TAlternativeParserItemBase()
{

}

// ----------------  TAlternativeParserItemList ----------------------
TAlternativeParserItemList::TAlternativeParserItemList()
{
   f_List = new TList;
}

TAlternativeParserItemList::~TAlternativeParserItemList()
{
   FreeList();
   delete f_List;
}

void TAlternativeParserItemList::FreeList()
{
   TAlternativeParserItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserItemBase*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

int __fastcall TAlternativeParserItemList::GetCount()
{
   return f_List->Count;
}

TAlternativeParserItemBase* __fastcall TAlternativeParserItemList::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserItemBase*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TAlternativeParserItemList::Append(TAlternativeParserItemBase* AItem)
{
   TAlternativeParserItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserItemBase*>(f_List->Items[i]);
      if (Item == AItem)
        return;
   }
   f_List->Add(AItem);
}

//------------------  TAlternativeParserItemTFE ---------------------------------
/*class TAlternativeParserItemTFE
{
    private:
      TTreeListItem* f_TFE;
      TAlternativeParserItemBig* f_Big;
      void __fastcall SetTFE(TTreeListItem* ATFE);
    public:
      TAlternativeParserItemTFE();
      __property TTreeListItem*  TFE = {read = f_TFE, write = SetTFE};
      __property TTreeListItem*  Big = {read = f_Big};
};
*/
TAlternativeParserItemTFE::TAlternativeParserItemTFE()
{
   f_TFE = NULL;
   f_Big = NULL;
}

TAlternativeParserItemTFE::~TAlternativeParserItemTFE()
{
   if (f_Big)
     delete f_Big;
}

void __fastcall TAlternativeParserItemTFE::SetTFE(TTreeListItem* ATFE)
{
   if (f_TFE)
     throw(Exception("ѕовторное присвоение в TAlternativeParserItemTFE не допустимо!"));
   f_TFE = ATFE;
   if (ATFE->MainNode)
   {
      f_Big = new TAlternativeParserItemBig;
      f_Big->MainTreeList = ATFE->MainNode;
      f_Big->FillBasisAlternateTreeList(f_Big->MainTreeList->MainAlternative);
      f_Big->ParentTFE = this;
   }
}

//--------------------- TAlternativeParserItemTFS ------------------------------
TAlternativeParserItemTFS::TAlternativeParserItemTFS()
{
   f_TFS = NULL;
   f_List = new TList;
}

TAlternativeParserItemTFS::~TAlternativeParserItemTFS()
{
   FreeList();
   delete f_List;
}

void TAlternativeParserItemTFS::FreeList()
{
   TAlternativeParserItemTFE* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserItemTFE*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

void __fastcall TAlternativeParserItemTFS::SetTFS(TTreeListTFS* ATFS)
{
    f_TFS = ATFS;
    TAlternativeParserItemTFE* Item;
    FreeList();
    for(int i = 0; i <= ATFS->ItemCount - 1; i++ )
    {
      Item = new TAlternativeParserItemTFE;
      Item->TFE = ATFS->TreeTFEItem[i];
      f_List->Add(Item);
    }
}

int __fastcall TAlternativeParserItemTFS::GetTFECount()
{
   return f_List->Count;
}

TAlternativeParserItemTFE* __fastcall TAlternativeParserItemTFS::GetTFEItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserItemTFE*>(f_List->Items[AIndex]);
   else
     return NULL;
}



//--------------------------TAlternativeParserItemBig ----------------------
TAlternativeParserItemBig::TAlternativeParserItemBig()
{
   f_Check = false;
   f_Cross = false;
   f_Enlarge = 0;
   f_EnlargeSetNum = false;
   f_ParentTFE = NULL;
   f_BadBasis = false;
   f_MainList = new TAlternativeParserItemList;
   f_List = new TList;
   f_Basis = new TDynamicArray;
}

TAlternativeParserItemBig::~TAlternativeParserItemBig()
{
   FreeList();
   delete f_List;
   delete f_MainList;
   delete f_Basis;
}

void TAlternativeParserItemBig::FreeList()
{
   TAlternativeParserItemBig* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserItemBig*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

void TAlternativeParserItemBig::BasisClear()
{
    f_Basis->Clear();
}

void TAlternativeParserItemBig::BasisAdd(TTreeListTFS* ATFS)
{
   for (int i = 0; i <= f_Basis->Count - 1; i++)
   {
     if ( f_Basis->Items[i] == ATFS )
       return;
   }
   f_Basis->Append(ATFS);
}

void TAlternativeParserItemBig::FillBasisFromGrpItemList(TAlternativeParserGrpItemList* AList)
{
   for (int i = 0; i <= AList->Count - 1; i++ )
      BasisAdd(AList->Items[i]->TFS);
}

void TAlternativeParserItemBig::FillBasisFromEnlarge(TAlternativeParserGrpCrossItemEnlarge* AEnl)
{
   for (int i = 0; i <= AEnl->Count - 1; i++ )
      BasisAdd(AEnl->Items[i]->TFS);
}

void TAlternativeParserItemBig::FillBasisAlternateTreeList(TAlternateTreeList* ALT)
{
   for (int i = 0; i <= ALT->ItemCount - 1; i++ )
      BasisAdd(ALT->TreeTFSItem[i]);
}

int __fastcall TAlternativeParserItemBig::GetBasisCount()
{
  return f_Basis->Count;
}


TTreeListTFS* __fastcall TAlternativeParserItemBig::GetBasisItems(int AIndex)
{
  return static_cast<TTreeListTFS*>(f_Basis->Items[AIndex]);
}

TTreeListTFS* TAlternativeParserItemBig::FirstFromBasis()
{
   return BasisItems[0];
}

TTreeListTFS* TAlternativeParserItemBig::LastFromBasis()
{
   return BasisItems[BasisCount - 1];
}


bool TAlternativeParserItemBig::CompareBasisAndAlternateTreeList(TAlternateTreeList *AList)
{
   TTreeListTFS* mTfs;
   int LenB = BasisCount;
   int LenA = AList->ItemCount;
   if (LenA != LenB)
     return false;
   for (int i = 0 ; i <= LenA - 1; i++)
   {
      if ( BasisItems[i] != AList->TreeTFSItem[i] )
          return false;
   }
   return true;
}

bool TAlternativeParserItemBig::CompareBasisAndMassiv(TDynamicArray *AMass)
{
   TTreeListTFS* mTfs;
   int LenB = BasisCount;
   int LenA = AMass->Count;
   if (LenA != LenB)
     return false;
   for (int i = 0 ; i <= LenA - 1; i++)
   {
      if ( BasisItems[i] != AMass->Items[i] )
          return false;
   }
   return true;
}

bool TAlternativeParserItemBig::IsTailAlternateTreeList(TAlternateTreeList *AList)
{
   TTreeListTFS *FT, *ET;
   TBaseWorkShape *FW, *EW;
   if (!AList->NodeEnd) return true;
   FW = AList->NodeStart->WorkShape;
   EW = AList->NodeEnd->WorkShape;
   FT = FirstFromBasis();
   ET = LastFromBasis();
   bool res = ( (FT->BaseWorkShape == FW ) && (ET->BaseWorkShape == EW) );
   return res;
}


int __fastcall TAlternativeParserItemBig::GetCountBig()
{
   return f_List->Count;
}

TAlternativeParserItemBig* __fastcall TAlternativeParserItemBig::GetItemsBig(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserItemBig*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TAlternativeParserItemBig::AddBig(TAlternativeParserItemBig* ABig)
{
   f_List->Add(ABig);
}


void TAlternativeParserItemBig::GetTreeListTFSFromBasis(TAlternateTreeList* Alternative,
  TDynamicArray *D, bool &AValid)
{
   TBaseWorkShape *NS, *NE, *CR;
   TTreeListTFS* Tmp;
   bool f = false;
   bool e = false;
   NS = Alternative->NodeStart->WorkShape;
   NE = Alternative->NodeEnd->WorkShape;
   for (int i = 0; i <= BasisCount - 1; i++)
   {
      Tmp = BasisItems[i];
      CR = Tmp->BaseWorkShape;
      if  ( !f && (CR == NS) )
        f = true;

      if ( f && !e )
        D->Append(Tmp);

      if ( !e && (CR == NE) )
        e = true;
   }
   AValid = f && e;
}

void TAlternativeParserItemBig::GetAllFirstBigsNoCheck(TDynamicArray *AMass)
{
   TAlternativeParserItemBig  *mTemp;
   TAlternativeParserItemBase *mBase;
   TAlternativeParserItemTFS *mTfs;
   TAlternativeParserItemTFE *mTfe;
   int i, m_who;
   for (i = 0 ; i <= MainList->Count - 1; i++ )
   {
     mBase = MainList->Items[i];
     m_who = mBase->Who();
     if (m_who == 1)
     {
        mTemp = dynamic_cast<TAlternativeParserItemBig*>(mBase);
        mTemp->MainTreeList = MainTreeList;
        if (!mTemp->Check)
          AMass->InsertToFirst(mTemp);
        //if (mTemp->Enlarge > 0)
     }
     if (m_who == 0)
     {
        mTfs = dynamic_cast<TAlternativeParserItemTFS*>(mBase);
        for (int j = 0; j <= mTfs->TFECount - 1; j++ )
        {
          mTfe = mTfs->TFEItems[j];
          if (mTfe->Big && !mTfe->Big->Check)
            AMass->InsertToFirst(mTfe->Big);
        }
     }
   }
   for (i = 0 ; i <= CountBig - 1; i++ )
   {
       mTemp = ItemsBig[i];
       mTemp->MainTreeList = MainTreeList;
       if (!mTemp->Check)
         AMass->InsertToFirst(mTemp);
       if (mTemp->Cross)
         mTemp->GetAllFirstBigsNoCheck(AMass);

   }
}

void TAlternativeParserItemBig::HookBasisBig()
{
  TAlternativeParserItemBig* m_F;
  BasisClear();
  m_F = ItemsBig[0];
  for (int i = 0; i <= m_F->BasisCount - 1; i++)
     BasisAdd(m_F->BasisItems[i]);
  f_List->Delete(f_List->IndexOf(m_F));
  delete m_F;

  for (int i = 0; i <= CountBig - 1; i++)
    ItemsBig[i]->NumAlt = i+1;

}



//--------------------------------------------------------------------------


//---------------TAlternativeParser-----------------------------------------
TAlternativeParser::TAlternativeParser()
{
   f_Head = NULL;
   f_Grp = new TAlternativeParserGrp;
   f_ListEnlarge  = new TList;

}

TAlternativeParser::~TAlternativeParser()
{
   FreeHead();
   delete f_Grp;
   delete f_ListEnlarge;
}

void TAlternativeParser::FreeHead()
{
   if (f_Head)
     delete f_Head;
}


void TAlternativeParser::CreateHead()
{
   FreeHead();
   f_Head = new TAlternativeParserItemBig;
}



void TAlternativeParser::Parse(TMainTreeList* AMainTree)
{
   if (AMainTree)
     DoParse(AMainTree);
}

void TAlternativeParser::DoMakeAlternative()
{
}

bool TAlternativeParser::CheckEnlarge(TAlternativeParserItemBig* ABig)
{
   TAlternativeParserItemBig* Item;
   if (ABig->Enlarge > 0 )
   {
      for(int i = 0; i <= f_ListEnlarge->Count -1; i++)
      {
         Item = static_cast<TAlternativeParserItemBig*>(f_ListEnlarge->Items[i]);
         if (Item->Enlarge == ABig->Enlarge)
           return false;
      }
      f_ListEnlarge->Add(ABig);
   }
   return true;
}


void TAlternativeParser::FillItemGrp(TAlternativeParserGrpItemBase* AItem,
  TAlternativeParserItemBig *ABig )
{
   TAlternativeParserGrpItemTFS* GTfs;
   TAlternativeParserGrpItemList* GList;
   TAlternativeParserItemTFS* mTfs;
   TAlternativeParserItemBig* mBig;
   TAlternativeParserGrpCrossItemEnlarge* Enl;

   int m_who = AItem->Who();
   if (m_who == 0)
   {
      GTfs = dynamic_cast<TAlternativeParserGrpItemTFS*>(AItem);
      mTfs = new TAlternativeParserItemTFS;
      mTfs->TFS = GTfs->TFS;
      mTfs->OwnerBig = ABig;
      ABig->MainList->Append(mTfs);
   }
   if(m_who == 1)
   {
      GList = dynamic_cast<TAlternativeParserGrpItemList*>(AItem);
      mBig = new TAlternativeParserItemBig;
      mBig->FillBasisFromGrpItemList(GList);
      mBig->OwnerBig = ABig;
      ABig->MainList->Append(mBig);
      mBig->BadBasis = ABig->Cross;
   }
   if(m_who == 2)
      CrossToBigs(dynamic_cast<TAlternativeParserGrpCrossItem*>(AItem), ABig);
   if(m_who == 3)
   {
      Enl = dynamic_cast<TAlternativeParserGrpCrossItemEnlarge*>(AItem);
      mBig = new TAlternativeParserItemBig;
      mBig->Enlarge = Enl->ID;
      mBig->FillBasisFromEnlarge(Enl);
      mBig->OwnerBig = ABig;
      ABig->MainList->Append(mBig);
   }

}

void TAlternativeParser::FillBigFromGrp(TAlternativeParserItemBig *ABig)
{
  for (int i = 0; i <= f_Grp->CountOUT - 1; i++ )
     FillItemGrp(f_Grp->ItemsOUT[i], ABig);
}

void TAlternativeParser::CrossToBigs(TAlternativeParserGrpCrossItem* ACrossItem,
 TAlternativeParserItemBig *ABig)
{
   TAlternativeParserGrpItemBase* Base;
   TAlternativeParserGrpCrossItemOut* Cross;
   TAlternativeParserItemBig* mHeadBig = new TAlternativeParserItemBig;
   mHeadBig->OwnerBig = ABig;
   ABig->MainList->Append(mHeadBig);

   TAlternativeParserItemBig* mBig = new TAlternativeParserItemBig;
   for (int i = 0; i <= ACrossItem->CountBasis - 1; i++ )
     FillItemGrp(ACrossItem->ItemsBasis[i], mBig);
   mBig->Check = true;
   mBig->OwnerBig = mHeadBig;
   mBig->NumAlt = 0;
   mBig->Cross = true;
   mHeadBig->AddBig(mBig);
   for (int i = 0; i <= ACrossItem->CountOut - 1; i++ )
   {
      mBig = new TAlternativeParserItemBig;
      Cross = ACrossItem->ItemsOut[i];
      mBig->Check = true;
      mBig->Cross = true;
      for (int j = 0; j <= Cross->Count - 1; j++ )
        FillItemGrp(Cross->Items[j], mBig);
      mBig->NumAlt = i + 1;
      mBig->OwnerBig = mHeadBig;
      mHeadBig->AddBig(mBig);
   }
}


void TAlternativeParser::CreateParserGrpItemList(TDynamicArray *AMass, TAlternateTreeList* Alternative)
{
   TAlternativeParserGrpItemList* Item;
   if (AMass->Count > 0)
   {
      Item = f_Grp->GetNewList(Alternative);
      for (int i = 0; i <= AMass->Count - 1; i++)
        Item->AddTfs(static_cast<TTreeListTFS*>(AMass->Items[i]));
   }
}


void TAlternativeParser::MakeBig(TAlternativeParserItemBig *ABig, bool AByPass)
{
   int m_n = 0;
   bool b_basis, b_main, b_tail, b_go, b_parent, b_cbm, b_valid;
   TTreeListTFS* TFS;
   TAlternateTreeList* AItem;
   TAlternativeParserItemBig *NewBig;
  // TAlternativeParserGrpItemList* AltParserItem;
   TMainTreeList* m_Tree = ABig->MainTreeList;

   TDynamicArray *D = new TDynamicArray;
   TDynamicArray *Mass = new TDynamicArray;
   bool m_whl = true;
   bool m_hook = false;
   while (m_whl)
   {
     m_whl = false;
     f_Grp->Clear();
     for( int i = 0; i <= ABig->BasisCount - 1; i++ )
     {
        TFS = ABig->BasisItems[i];
        m_Tree->FindAlternate(TFS->BaseWorkShape, D);
        b_go = false;
        if (D->Count > 0)
        for (int j = 0; j <= D->Count - 1; j++ )
        {
          AItem = static_cast<TAlternateTreeList*>(D->Items[j]);
          b_basis = ABig->CompareBasisAndAlternateTreeList(AItem);
          b_main = AItem->MainAlternative;
          b_tail = ABig->IsTailAlternateTreeList(AItem);
          b_parent = ABig->ParentTFE;
          if (!b_basis && !b_main)
          {
             Mass->Clear();
             ABig->GetTreeListTFSFromBasis(AItem, Mass, b_valid);
             if (!b_valid)
               continue;
             b_cbm = ABig->CompareBasisAndMassiv(Mass);
             b_go = (AByPass || !b_cbm || b_parent);
             if (b_go)
               CreateParserGrpItemList(Mass, AItem);
          }
          if (b_tail && !b_main && !b_go)
          {
             m_n++;
             NewBig = new TAlternativeParserItemBig;
             NewBig->NumAlt = m_n;
             NewBig->FillBasisAlternateTreeList(AItem);
             NewBig->OwnerBig = ABig;
             ABig->AddBig(NewBig);
          }

        }
        f_Grp->AddTfs(TFS);
     }

     if (ABig->BadBasis && !m_hook)
     {
        ABig->HookBasisBig();
        m_hook = true;
        m_whl = true;
     }

   }
   f_Grp->Make();
   FillBigFromGrp(ABig);
   delete D;
   delete Mass;

}

void TAlternativeParser::DoParse(TMainTreeList* AMainTree)
{
   TAlternativeParserItemBig *mBig, *mTemp;
   TAlternativeParserItemBase *mBase;
   CreateHead();
   f_Head->MainTreeList = AMainTree;
   f_Head->FillBasisAlternateTreeList(f_Head->MainTreeList->MainAlternative);
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_Head);
   mBig = static_cast<TAlternativeParserItemBig*>(m_Stack->Pop());
   while(mBig)
   {
     if (CheckEnlarge(mBig))
       MakeBig(mBig, f_Head == mBig);
     mBig->Check = true;
     mBig->GetAllFirstBigsNoCheck(m_Stack);
     mBig = static_cast<TAlternativeParserItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}
