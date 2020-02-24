//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicateTFSConvertor.h"
#include "uCommonGraph.h"
//#include "ufrmPredicateView.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------    TPredicateItemBase() --------------------
TPredicateItemBase::TPredicateItemBase()
{
   f_NumAlt = -1;
   f_Envelope = false;
   f_ID = 0;
   f_EnvelopeBIG = NULL;
}

void TPredicateItemBase::ListIDFill(TDynamicArray* AList)
{
   AList->AppendInteger(f_ID, NULL);
}


//-------------------TPredicateItemTFE-----------------------------
TPredicateItemTFE::TPredicateItemTFE()
{
   f_TFE = NULL;
   f_Big = NULL;
   f_RfcTFE = NULL;
}

TPredicateItemTFE::~TPredicateItemTFE()
{
   if (f_Big)
     delete f_Big;
}


//-------------------TPredicateItemTFS-----------------------------
TPredicateItemTFS::TPredicateItemTFS()
{
   f_TFS = NULL;
   f_ListTFE = new TList;
}

TPredicateItemTFS::~TPredicateItemTFS()
{
   FreeList();
   delete f_ListTFE;
}

void TPredicateItemTFS::FreeList()
{
   TPredicateItemTFE* Item;
   for (int i = 0; i <= f_ListTFE->Count - 1; i++)
   {
      Item = static_cast<TPredicateItemTFE*>(f_ListTFE->Items[i]);
      delete Item;
   }
   f_ListTFE->Clear();
}

int __fastcall TPredicateItemTFS::GetTFECount()
{
  return f_ListTFE->Count;
}

TPredicateItemTFE* __fastcall TPredicateItemTFS::GetTFEItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListTFE->Count - 1)
     return static_cast<TPredicateItemTFE*>(f_ListTFE->Items[AIndex]);
   else
     return NULL;
}


void TPredicateItemTFS::Assign(TAlternativeParserItemTFS *ATfs)
{
   TPredicateItemTFE* mTfe;
   FreeList();
   f_TFS = ATfs->TFS;
   NumAlt = ATfs->NumAlt;
   for (int i = 0; i <= ATfs->TFECount - 1; i++)
   {
      mTfe = new TPredicateItemTFE;
      mTfe->RfcTFE = ATfs->TFEItems[i];
      mTfe->TFE = ATfs->TFEItems[i]->TFE;
      f_ListTFE->Add(mTfe);
   }

}

void TPredicateItemTFS::ListIDFill(TDynamicArray* AList)
{
   int m_who = TFS->BaseWorkShape->TypeShape;
   switch (m_who)
   {
     case 1:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        break;
     }
     case 2:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        break;
     }
     case 3:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        break;
     }

     case 4:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        break;
     }
     case 5:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        break;
     }
     case 6:
     {
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[2]->TFE->BaseShape->ID, TFEItems[2]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        break;
     }

     case 7:
     {
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        break;
     }

     case 8:
     {
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        break;
     }

     case 9:
     {
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[2]->TFE->BaseShape->ID, TFEItems[2]->TFE->BaseShape);
        break;
     }

     case 10:
     {
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[2]->TFE->BaseShape->ID, TFEItems[2]->TFE->BaseShape);
        break;
     }


     case 11:
     {
        AList->AppendInteger(TFEItems[1]->TFE->BaseShape->ID, TFEItems[1]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[2]->TFE->BaseShape->ID, TFEItems[2]->TFE->BaseShape);
        AList->AppendInteger(TFEItems[0]->TFE->BaseShape->ID, TFEItems[0]->TFE->BaseShape);
        break;
     }
  }
}

//----------------TPredicateItemPWork --------------------------------
TPredicateItemPWork::TPredicateItemPWork()
{
   f_Item1 = NULL;
   f_Item2 = NULL;
}

TPredicateItemPWork::~TPredicateItemPWork()
{
   delete f_Item1;
   delete f_Item2;
}

void TPredicateItemPWork::ListIDFill(TDynamicArray* AList)
{
   int id;
   TPredicateItemTFS* mTfs;
   //мб только укрупненная или просто рабочая операция
   id = f_Item1->Who();
   if (id == 0)
   {
      mTfs = dynamic_cast<TPredicateItemTFS*>(f_Item1);
      id = mTfs->TFEItems[0]->TFE->BaseShape->ID;
      AList->AppendInteger(id,  mTfs->TFEItems[0]->TFE->BaseShape);
   }
   else
      AList->AppendInteger(f_Item1->ID, NULL );

   id = f_Item2->Who();
   if (id == 0)
   {
      mTfs = dynamic_cast<TPredicateItemTFS*>(f_Item2);
      id = mTfs->TFEItems[0]->TFE->BaseShape->ID;
      AList->AppendInteger(id,  mTfs->TFEItems[0]->TFE->BaseShape );
   }
   else
      AList->AppendInteger(f_Item2->ID, NULL );
}



//-------------------TPredicateItemBIG-----------------------------
TPredicateItemBig::TPredicateItemBig()
{
//   f_OwnerTFE = NULL;
   f_Rfc = NULL;
   f_List = new TList;
   f_Print = false;
}

TPredicateItemBig::~TPredicateItemBig()
{
   FreeList();
   delete  f_List;
}

void TPredicateItemBig::FreeList()
{
   TPredicateItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

int __fastcall TPredicateItemBig::GetCount()
{
   return f_List->Count;
}

TPredicateItemBase* __fastcall TPredicateItemBig::GetItems(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicateItemBase*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TPredicateItemBig::AddItem(TPredicateItemBase *AItem)
{
   f_List->Add(AItem);
}

void TPredicateItemBig::DeleteItemToList(TPredicateItemBase* AItem)
{
   int index = f_List->IndexOf(AItem);
   if (index >= 0)
     f_List->Delete(index);
}

bool  TPredicateItemBig::ValidDescendant()
{
/*
   int m_who;
   TPredicateItemBase* IPB;
   for(int i = 0; i <= Count - 1; i++)
   {
      IPB = Items[i];
      m_who = IPB->Who();
      if (m_who == 0)
        return true;
    //  if (m_who == 1)
     //   if (dynamic_cast<TPredicateItemBig*>(IPB)->ValidDescendant() )
     //     return true;
   }
   return false;
*/
  return true;
}



//----------------TPredicateTFSConvertor----------------------------------------
TPredicateTFSConvertor::TPredicateTFSConvertor()
{
   f_PathStyle = 0;
   f_TryPath = true;
   f_PredicateStart = NULL;
   f_NGen = new TPredicateNumGenerator;
   f_ListEnlarge = new TList;
}

TPredicateTFSConvertor::~TPredicateTFSConvertor()
{
   FreeHead();
   delete f_NGen;
   delete f_ListEnlarge;
}

void TPredicateTFSConvertor::FreeHead()
{
   if (f_PredicateStart)
   {
     delete f_PredicateStart;
     f_PredicateStart = NULL;
   }
}

TPredicateItemBig* TPredicateTFSConvertor::NewBig(TAlternativeParserItemBig *ABig)
{
   TPredicateItemBig* N = new TPredicateItemBig;
   N->Rfc = ABig;
   N->NumAlt = ABig->NumAlt;
   return N;
}

TPredicatePathNode* TPredicateTFSConvertor::FillPathNode(TPredicateItemBig* AHead,
  TPredicateItemBase* AItem)
{
  TPredicatePathNode* N = NULL;
  int m_who = AItem->Who();
  bool valid = m_who == 0;
  if (m_who == 1)
    valid = dynamic_cast<TPredicateItemBig*>(AItem)->ValidDescendant();
  if (valid)
  {
    N = f_BasePath->CreatePathNode(AHead);
    N->AddItem(AItem);
  }
  return N;
}


TPredicatePathNode* TPredicateTFSConvertor::FillPathNode(TPredicateItemBig* AHead,
  TDynamicArray* ADyn)
{
  int m_who;
  bool valid =  false;
  TPredicateItemBase* Item;
  TPredicatePathNode* N = NULL;
  TDynamicArray *D =  new TDynamicArray;
  for(int i = 0 ; i <= ADyn->Count - 1; i++)
  {
    Item = static_cast<TPredicateItemBase*>(ADyn->Items[i]);
    m_who = Item->Who();
    valid = m_who == 0;
    if (m_who == 1)
      valid = dynamic_cast<TPredicateItemBig*>(Item)->ValidDescendant();
    if (valid)
      D->Append(Item);
  }

  if (D->Count > 0)
  {
    N = f_BasePath->CreatePathNode(AHead);
    for(int i = 0 ; i <= D->Count - 1; i++)
      N->AddItem(static_cast<TPredicateItemBase*>(D->Items[i]));
  }
  delete D;
  return N;
}

bool TPredicateTFSConvertor::CheckPath(TPredicateItemBig* AHead,
  TPredicateItemBase* AItem)
{
   TPredicatePathNode* N = FillPathNode(AHead, AItem);
   if (N && !f_UsedPath->FindLikePathNode(N))
     return false;
   return true;
}

bool TPredicateTFSConvertor::CheckPath(TPredicateItemBig* AHead, TDynamicArray* ADyn)
{
   TPredicatePathNode* N = FillPathNode(AHead, ADyn);
   if (N && !f_UsedPath->FindLikePathNode(N))
     return false;
   return true;
}

void TPredicateTFSConvertor::SetPathNode(TPredicateItemBig* AHead,
  TDynamicArray* ADyn)
{
   int mpos;
   TPredicatePathNode* L;
   TPredicatePathNodeItem* NI;
   TPredicatePathNodeItem* FI;
   TDynamicArray *D =  new TDynamicArray;
   TPredicatePathNode* N = FillPathNode(AHead, ADyn);
   if (N)
   {
     L = f_UsedPath->FindLikePathNode(N);
     if(L)
     {
       NI = L->FindIndexFirst(mpos);
       while(NI)
       {
         FI = N->FindByBlockID(NI->BlockID);
         if(FI)
           D->Append(FI->ItemBase);
         NI = L->FindIndexNext(mpos);
       }
     }
   }
   if(D->Count == ADyn->Count)
   {
     ADyn->Clear();
     CopyDynamicArray(D, ADyn, false);
   }
   delete D;
}


void TPredicateTFSConvertor::ApplyStyle(TPredicateItemBig* AHead,
  TPredicateItemBase* AItem)
{
  if (f_PathStyle == 0)
    FillPathNode(AHead, AItem);
  if (f_PathStyle == 1)
    f_TryPath = CheckPath(AHead, AItem);
}

void TPredicateTFSConvertor::ApplyStyle(TPredicateItemBig* AHead,
  TDynamicArray* ADyn)
{
  if (f_PathStyle == 0)
    FillPathNode(AHead, ADyn);
  if (f_PathStyle == 1)
    f_TryPath = CheckPath(AHead, ADyn);
  if (f_PathStyle == 2)
    SetPathNode(AHead, ADyn);
}



void TPredicateTFSConvertor::DoCopyTree(TPredicateItemBig *ABig, TDynamicArray* AStack)
{
   int m_who;
   TAlternativeParserItemList* ML;
   TAlternativeParserItemBase* mBase;
   TAlternativeParserItemTFS* mTFS;
   TAlternativeParserItemBig* mBig;
   TPredicateItemTFE* mTFE;
   TAlternativeParserItemBig* mRfc = ABig->Rfc;

   ML = mRfc->MainList;
   for (int i = 0; i <= ML->Count - 1; i++ )
   {
      mBase = ML->Items[i];
      m_who = mBase->Who();
      if (m_who == 0)
      {
         mTFS = dynamic_cast<TAlternativeParserItemTFS*>(mBase);
         TPredicateItemTFS *iTfs = new TPredicateItemTFS;
         iTfs->Assign(mTFS);
         ABig->AddItem(iTfs);
         for (int j = 0; j <= iTfs->TFECount - 1; j++ )
         {
            mTFE = iTfs->TFEItems[j];
            if(mTFE->RfcTFE->Big)
            {
              TPredicateItemBig *iBig = NewBig(mTFE->RfcTFE->Big);
              mTFE->Big = iBig;
              AStack->InsertToFirst(iBig);
            }
         }
      }
      if (m_who == 1)
      {
         mBig = dynamic_cast<TAlternativeParserItemBig*>(mBase);
         TPredicateItemBig *iBig = NewBig(mBig);
         ABig->AddItem(iBig);
         AStack->InsertToFirst(iBig);
      }
   }

   for (int i = 0; i <= mRfc->CountBig - 1; i++ )
   {
      mBig = mRfc->ItemsBig[i];
      TPredicateItemBig *iBig = NewBig(mBig);
      ABig->AddItem(iBig);
      AStack->InsertToFirst(iBig);
   }
}



void TPredicateTFSConvertor::CopyTree(TAlternativeParserItemBig *AHead)
{
   TPredicateItemBig* Big;
   FreeHead();
   f_PredicateStart = NewBig(AHead);
   TDynamicArray *m_Stack = new TDynamicArray;
 //0202  m_Stack->InsertToFirst(f_PredicateStart);
 //0202   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   Big = f_PredicateStart;
   while(Big)
   {
     DoCopyTree(Big, m_Stack);
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}


void TPredicateTFSConvertor::SwapNumAlt(TPredicateItemBase *ADest,
  TPredicateItemBase *ASource)
{
   ADest->NumAlt = ASource->NumAlt;
   ASource->NumAlt = 0;
}

TPredicateItemBase* TPredicateTFSConvertor::EnvelopeToBig(TPredicateItemBase *ASource)
{
   TPredicateItemTFS* mTfs;
   TPredicateItemBig* nBig;
   int m_who = ASource->Who();
   if (m_who == 1)
     return ASource;
   if (m_who == 0)
   {
      mTfs =  dynamic_cast<TPredicateItemTFS*>(ASource);
      if (mTfs->TFS->BaseWorkShape->TypeShape == 1 )
        return ASource;
   }
   nBig = new TPredicateItemBig;
   nBig->Envelope = true;
   nBig->AddItem(ASource);
   SwapNumAlt(nBig, ASource);
   return nBig;
}


void TPredicateTFSConvertor::DoProcess()
{
   TPredicateItemBig* Big;
   f_TryPath = true;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   while(Big)
   {
     DoProcessItem(Big, m_Stack);
     if (!f_TryPath)  break;
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}


void TPredicateTFSConvertor::DoProcessItemTFS(TPredicateItemBase *ABase, TDynamicArray *AStack)
{
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;
   if (ABase)
   {
     int m_type = ABase->Who();
     if ( m_type == 0 )
     {
        m_Tfs = dynamic_cast<TPredicateItemTFS*>(ABase);
        for (int j = 0; j <= m_Tfs->TFECount - 1; j++)
        {
          m_Tfe = m_Tfs->TFEItems[j];
          if (m_Tfe->Big)
            AStack->InsertToFirst(m_Tfe->Big);
        }
     }
     if ( m_type == 1 )
       AStack->InsertToFirst(ABase);
   }
}

void TPredicateTFSConvertor::DoProcessItem(TPredicateItemBig* AHead, TDynamicArray *AStack)
{
   int m_type, m_cnt, m_idx;
   TPredicateItemBase *m_Base;
   TPredicateItemBase *m_BaseItem1, *m_BaseItem2;
   TPredicateItemPWork *m_PWork, *m_PW;
   TPredicateItemBig *m_Big;
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;
   TDynamicArray *m_D = new TDynamicArray;
   TDynamicArray *m_DTail = new TDynamicArray;
   TDynamicArray *m_DLN = new TDynamicArray;

   m_cnt  = AHead->Count;
   if (m_cnt == 1)
   {
      m_Base = AHead->Items[0];
      DoProcessItemTFS(m_Base, AStack);
      if (m_Base->Who() == 1)
         dynamic_cast<TPredicateItemBig*>(m_Base)->Print = true;

      ApplyStyle(AHead, m_Base);
   }
   if (m_cnt > 1)
   {
      for (int i = 0; i <= m_cnt - 1; i++)
      {
         m_Base = AHead->Items[i];
         m_type = m_Base->Who();
         if  (m_type == 1)
         {
            m_Big = dynamic_cast<TPredicateItemBig*>(m_Base);
            if (m_Big->NumAlt > 0  || m_Big->Rfc->Cross)
            {
              m_DTail->Append(m_Big);
              m_Big->Print = true;
            }
            else
            {
              m_DLN->Append(m_Base);
             // m_Big->Print = m_Big->Rfc->CrossMain;
            }

         }
         else
           m_DLN->Append(m_Base);
      }
      if (m_DLN->Count == 1)
      {
         m_Base = static_cast<TPredicateItemBase*>(m_DLN->Items[0]);
         DoProcessItemTFS(m_Base, AStack);
         ApplyStyle(AHead, m_Base);
      }
      else
      if (m_DLN->Count > 1)
      {
        ApplyStyle(AHead, m_DLN);
        m_BaseItem1 = static_cast<TPredicateItemBase*>(m_DLN->Items[0]);
        m_BaseItem2 = static_cast<TPredicateItemBase*>(m_DLN->Items[1]);
        DoProcessItemTFS(m_BaseItem1, AStack);
        DoProcessItemTFS(m_BaseItem2, AStack);
        for (int i = 2; i <= m_DLN->Count - 1; i++)
          m_D->Append(m_DLN->Items[i]);

         AHead->DeleteItemToList(m_BaseItem1);
         AHead->DeleteItemToList(m_BaseItem2);


         m_BaseItem1 = EnvelopeToBig(m_BaseItem1);
         m_BaseItem2 = EnvelopeToBig(m_BaseItem2);

         m_PWork = new TPredicateItemPWork;
         m_PWork->Item1 = m_BaseItem1;
         m_PWork->Item2 = m_BaseItem2;
         //m_PWork->Envelope = true;
         SwapNumAlt(m_PWork, m_BaseItem1);



         while (m_D->Count >= 1)
         {

           m_Big = dynamic_cast<TPredicateItemBig*>(EnvelopeToBig(m_PWork));

           m_BaseItem1 = m_Big;
           m_BaseItem2 = static_cast<TPredicateItemBase*>(m_D->Items[0]);
           DoProcessItemTFS(m_BaseItem2, AStack);
           AHead->DeleteItemToList(m_BaseItem2);

           m_PW = new TPredicateItemPWork;
           //m_PW->Envelope = true;
           m_PW->Item1 = m_BaseItem1;
           m_PW->Item2 = EnvelopeToBig(m_BaseItem2);
           SwapNumAlt(m_PW, m_Big);
           m_D->Delete(m_BaseItem2);
           m_PWork = m_PW;

         }

         AHead->AddItem(m_PWork);
      }

      for (int i = 0; i <= m_DTail->Count - 1; i++)
      {
         m_Base = static_cast<TPredicateItemBase*>(m_DTail->Items[i]);
         AStack->InsertToFirst(m_Base);
      }

  }
  delete m_DTail;
  delete m_DLN;
  delete m_D;

}

void TPredicateTFSConvertor::PushTFS(TPredicateItemTFS *ATFS, TDynamicArray *AStack)
{
   for (int i = 0; i <= ATFS->TFECount - 1; i++)
     if (ATFS->TFEItems[i]->Big)
       AStack->InsertToFirst(ATFS->TFEItems[i]->Big);
}


void TPredicateTFSConvertor::DoSetIDItemTFS(TPredicateItemBase *ABase, TDynamicArray *AStack)
{
   int m_type;
   TPredicateItemPWork *m_PW;
   if (ABase)
   {
     m_type = ABase->Who();
     if ( m_type == 0 )
        PushTFS(dynamic_cast<TPredicateItemTFS*>(ABase), AStack);

     if ( m_type == 1 )
       AStack->InsertToFirst(ABase);
     if ( m_type == 2 )
     {
        m_PW = dynamic_cast<TPredicateItemPWork*>(ABase);
        //1
        m_type = m_PW->Item1->Who();
        if ( m_type == 0 )
           PushTFS(dynamic_cast<TPredicateItemTFS*>(m_PW->Item1), AStack);

        if ( m_type == 1 )
          AStack->InsertToFirst(m_PW->Item1);

        //2
        m_type = m_PW->Item2->Who();
        if ( m_type == 0 )
           PushTFS(dynamic_cast<TPredicateItemTFS*>(m_PW->Item2), AStack);
        if ( m_type == 1 )
          AStack->InsertToFirst(m_PW->Item2);

     }
   }
}


void TPredicateTFSConvertor::DoSetID()
{
   TPredicateItemBig* Big;
   f_NGen->InitNum();
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   while(Big)
   {
     DoSetIDItem(Big, m_Stack);
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}



void TPredicateTFSConvertor::DoSetIDItem(TPredicateItemBig* AHead, TDynamicArray *AStack)
{
   int m_who;
   TPredicateItemBase *m_Base;
   TPredicateItemPWork *m_PW;
   int m_cnt  = AHead->Count;
   for (int i = 0 ; i <= m_cnt -1; i++)
   {
     m_Base = AHead->Items[i];
     m_who = m_Base->Who();
     if ( m_who == 1 )
     {
       TPredicateItemBig* mBig = dynamic_cast<TPredicateItemBig*>(m_Base);
       if(CheckEnlargeNum(mBig))
           return;
       m_Base->ID = f_NGen->NextLowNum();
     }
     if ( m_who == 2)
     {
        m_PW = dynamic_cast<TPredicateItemPWork*>(m_Base);

        m_who = m_PW->Item1->Who();
        if ( m_who == 1 )
        {
          TPredicateItemBig* mBig = dynamic_cast<TPredicateItemBig*>(m_PW->Item1);
          if( mBig->Rfc && mBig->Rfc->Enlarge > 0)
          {
            if(!CheckEnlargeNum(mBig))
            m_PW->Item1->ID = f_NGen->NextLowNum();
          }
          else
            m_PW->Item1->ID = f_NGen->NextLowNum();

        }

        m_who = m_PW->Item2->Who();
        if ( m_who == 1 )
        {
          TPredicateItemBig* mBig = dynamic_cast<TPredicateItemBig*>(m_PW->Item2);
          if( mBig->Rfc && mBig->Rfc->Enlarge > 0)
          {
            if(!CheckEnlargeNum(mBig))
            m_PW->Item2->ID = f_NGen->NextLowNum();
          }
          else
            m_PW->Item2->ID = f_NGen->NextLowNum();
        }


//        m_PW->Item2->ID = f_NGen->NextLowNum();
     }
     DoSetIDItemTFS(m_Base, AStack);
   }

}

void TPredicateTFSConvertor::Process(TPredicatePathItem* ABase, TPredicatePathItem* AUsed)
{
   f_BasePath = ABase;
   f_UsedPath = AUsed;
   f_BasePath->Clear();

   DoProcess();
   DoSetID();
}

bool TPredicateTFSConvertor::CheckEnlargeNum(TPredicateItemBig* ABig)
{
   TPredicateItemBig* Item;
   if (ABig->Rfc->Enlarge > 0 )
   {
      for(int i = 0; i <= f_ListEnlarge->Count -1; i++)
      {
         Item = static_cast<TPredicateItemBig*>(f_ListEnlarge->Items[i]);
         if ((Item->Rfc->Enlarge == ABig->Rfc->Enlarge)  && (Item->Rfc->EnlargeSetNum) )
         {
            ABig->ID = Item->ID;
            return true;
         }
      }
      ABig->Rfc->EnlargeSetNum = true;
      f_ListEnlarge->Add(ABig);
   }
   return false;
}


/*

TPredicateItemPWork::TPredicateItemPWork()
{
   f_Item1 = NULL;
   f_Item2 = NULL;
}

TPredicateItemPWork::~TPredicateItemPWork()
{
   delete f_Item1;
   delete f_Item2;
}

void TPredicateItemPWork::ListIDFill(TDynamicArray* AList)
{
   AList->Append( (void*)f_Item1->ID );
   AList->Append( (void*)f_Item2->ID );
}

void __fastcall TPredicateItemPWork::SetID(int AValue)
{
   f_Item1->ID  =   AValue;
   f_Item2->ID  =   AValue + 1;
}


int __fastcall TPredicateItemPWork::GetMaxID()
{
   return  f_Item2->ID;
}

void TPredicateItemPWork::GetFullAddresItem(TDynamicArray* AList)
{
   AList->Append(this);
   f_Item1->GetFullAddresItem(AList);
   f_Item2->GetFullAddresItem(AList);
}


//------------------------------------------------------------------------------
TPredicateItemTFS::TPredicateItemTFS()
{
   f_TFS = NULL;
   f_ListTFE = new TList;
   f_StartTFEID = 0;
}

TPredicateItemTFS::~TPredicateItemTFS()
{
   FreeList();
   delete  f_ListTFE;
}

void TPredicateItemTFS::FreeList()
{
   TPredicateItemTFE* Item;
   for (int i = 0; i <= f_ListTFE->Count - 1; i++)
   {
      Item = static_cast<TPredicateItemTFE*>(f_ListTFE->Items[i]);
      delete Item;
   }
   f_ListTFE->Clear();
}

void TPredicateItemTFS::GetFullAddresItem(TDynamicArray* AList)
{
   TPredicateItemTFE* Item;
   for (int i = 0; i <= f_ListTFE->Count - 1; i++)
   {
      Item = static_cast<TPredicateItemTFE*>(f_ListTFE->Items[i]);
      Item->GetFullAddresItem(AList);
   }
   AList->Append(this);
}

void __fastcall TPredicateItemTFS::SetTFS(TTreeListTFS* ATFS)
{
    TTreeListItem* Item;
    TPredicateItemTFE* Ptfe;
    FreeList();
    f_TFS = ATFS;
    for(int i = 0; i <= ATFS->ItemCount - 1; i++ )
    {
       Item = ATFS->TreeTFEItem[i];
       Ptfe = new  TPredicateItemTFE;
       Ptfe->TFE = Item;
       if (Item->MainNode)
       {
         TPredicateItemBig *BG = new TPredicateItemBig;
         BG->Envelope = true;
         BG->MainTreeList = Item->MainNode;
         BG->OwnerTFE = Ptfe;
         BG->CurrAlternate = CurrAlternate;
         Ptfe->Big = BG;
       }
       f_ListTFE->Add(Ptfe);
    }
}



int __fastcall TPredicateItemTFS::GetCountTFE()
{
   return f_ListTFE->Count;
}

TPredicateItemTFE* __fastcall TPredicateItemTFS::GetTFE(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListTFE->Count - 1)
     return static_cast<TPredicateItemTFE*>(f_ListTFE->Items[AIndex]);
   else
     return NULL;
}


void __fastcall TPredicateItemTFS::SetID(int AValue)
{
    void* m_p;
    TPredicateItemBase::SetID(AValue);
    TPredicateItemTFE* Item;
    TDynamicArrayItem* AI;
    TBaseWorkShape *WS  = TFS->BaseWorkShape;
    TDynamicArray *D = new TDynamicArray;
    ListIDFromWorkShape(WS, D);
    for (int i = 0; i <= D->Count - 1; i++)
    {
       m_p = D->Items[i];
       Item = NULL;
       for (int j = 0; j <= CountTFE - 1; j++ )
       {
          Item = TFE[j];
          if ( Item->TFE->BaseShape == m_p )
             break;
       }
       Item->ID = Item->TFE->BaseShape->ID;
       if (i == 0)
         f_StartTFEID = Item->ID;
    }
    delete D;
}

int __fastcall TPredicateItemTFS::GetMaxID()
{
   int res = TFE[0]->ID;
   for (int j = 1; j <= CountTFE - 1; j++ )
   {
     if ( TFE[j]->ID > res )
       res = TFE[j]->ID;
   }
   return res;
}

void TPredicateItemTFS::ListIDFill(TDynamicArray* AList)
{
    int i_max = MaxID;
    for (int i = f_StartTFEID; i <= i_max; i++)
       AList->Append((void*)i);
}



//-----------------------------------------------------------------------
TPredicateItemTFE::TPredicateItemTFE()
{
   f_TFE = NULL;
   f_Big = NULL;
   f_ID = 0;
}


TPredicateItemTFE::~TPredicateItemTFE()
{
    if (f_Big)
      delete f_Big;
}

void TPredicateItemTFE::GetFullAddresItem(TDynamicArray* AList)
{
    if (f_Big)
     AList->Append(f_Big);
    AList->Append(this);
}

//-----------------------------------------------------------------------
TPredicateItemBig::TPredicateItemBig()
{
   f_List = new TList;
   f_OwnerTFE = NULL;
   f_OwnerPWork = NULL;
}

TPredicateItemBig::~TPredicateItemBig()
{
   FreeList();
   delete f_List;
}

void TPredicateItemBig::FreeList()
{
    TPredicateItemBase* Item;
    for (int i = 0; i <= f_List->Count - 1; i++)
    {
       Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
       delete Item;
    }
    f_List->Clear();

}

void TPredicateItemBig::GetFullAddresItem(TDynamicArray* AList)
{
    TPredicateItemBase* Item;
    for (int i = 0; i <= f_List->Count - 1; i++)
    {
       Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
       Item->GetFullAddresItem(AList);
    }
    AList->Append(this);

}

void TPredicateItemBig::ClearList()
{
   FreeList();
}


void TPredicateItemBig::ListIDFill(TDynamicArray* AList)
{
   AList->Append((void*)ID);
}


void TPredicateItemBig::ClearListTFS()
{
    TPredicateItemBase* Item;
    int m_who;
    for (int i = f_List->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
       m_who = Item->Who();
       if (!m_who )
       {
          delete Item;
          f_List->Delete(i);
       }
    }
}


int __fastcall TPredicateItemBig::GetCount()
{
   return f_List->Count;
}

TPredicateItemBase* __fastcall TPredicateItemBig::GetItems(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicateItemBase*>(f_List->Items[AIndex]);
   else
     return NULL;
}

bool TPredicateItemBig::Find(TPredicateItemBase *AItem)
{
   TPredicateItemBase* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
      if (Item == AItem)
        return true;
   }
   return false;
}

void TPredicateItemBig::DeleteItemToList(TPredicateItemBase* AItem)
{
   TPredicateItemBase* Item;
   for (int i = f_List->Count -1 ; i >= 0  ; i--)
   {
      Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
      if (Item == AItem)
        f_List->Delete(i);
   }
}


void TPredicateItemBig::AddItem(TPredicateItemBase *AItem)
{
   if (!Find(AItem))
     f_List->Add(AItem);
}

void TPredicateItemBig::FullBigItem(TDynamicArray* AList)
{
    TPredicateItemBase* Item;
    TPredicateItemTFS* Tfs;
    TPredicateItemTFE* Tfe;
    int m_who;
    for (int i =  f_List->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TPredicateItemBase*>(f_List->Items[i]);
       m_who = Item->Who();
       if (!m_who )
       {
          Tfs = dynamic_cast<TPredicateItemTFS*>(Item);
          for (int j = 0; j <= Tfs->CountTFE - 1; j++)
          {
             Tfe = Tfs->TFE[j];
             if (Tfe->Big)
             {
                AList->Append(Tfe->Big);
                Tfe->Big->GetFullAddresItem(AList);
             }
          }
       }
    }

}



//--------------------------------------------------------------------------

TPredicateTFSConvertor::TPredicateTFSConvertor()
{
    f_PeparedList = new TList;
    f_Parser = new  TAlternativeParser;
    f_NumGenerator = new TPredicateNumGenerator;
    f_NumGeneratorReverse = new TPredicateNumGenerator;

    f_TFSList =  new TDynamicArray;
    f_PredicateStart = NULL;
    f_NumGenerator->Index = 1;
    f_NumGeneratorReverse->Reverse = true;
    f_NumGeneratorReverse->Step = -1;

}
TPredicateTFSConvertor::~TPredicateTFSConvertor()
{
    ClearPreparedList();
    FreePredicateStart();
    delete f_PeparedList;
    delete f_Parser;
    delete f_NumGenerator;
    delete f_TFSList;
    delete f_NumGeneratorReverse;
}



void TPredicateTFSConvertor::FreePredicateStart()
{
    if (f_PredicateStart)
      delete f_PredicateStart;
}



void TPredicateTFSConvertor::Parse(TMainTreeList* ATreeMain)
{
   MakeTree(ATreeMain);
}


//------------------------------------------------------------------------------
//     void DoProcess();
//     void DoProcessItem();

void TPredicateTFSConvertor::DoProcess()
{
   TPredicateItemBig* Big;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   while(Big)
   {
     DoProcessItem(Big, m_Stack);
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}

void TPredicateTFSConvertor::DoProcessItemTFS(TPredicateItemBase *ABase, TDynamicArray *AStack)
{
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;
   if (ABase)
   {
     int m_type = ABase->Who();
     if ( m_type == 0 )
     {
        m_Tfs = dynamic_cast<TPredicateItemTFS*>(ABase);
        for (int j = 0; j <= m_Tfs->CountTFE - 1; j++)
        {
          m_Tfe = m_Tfs->TFE[j];
          if (m_Tfe->Big)
            AStack->InsertToFirst(m_Tfe->Big);
        }
     }
     if ( m_type == 1 )
       AStack->InsertToFirst(ABase);
   }
}

void TPredicateTFSConvertor::DoProcessItem(TPredicateItemBig* AHead, TDynamicArray *AStack)
{
   int m_type, m_cnt, m_idx;
   TPredicateItemBase *m_Base;
   TPredicateItemBase *m_BaseItem1, *m_BaseItem2;
   TPredicateItemPWork *m_PWork, *m_PW;
   TPredicateItemBig *m_Big;
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;
   TDynamicArray *m_D = new TDynamicArray;
   TDynamicArray *m_DTail = new TDynamicArray;
   TDynamicArray *m_DLN = new TDynamicArray;

   m_cnt  = AHead->Count;
   if (m_cnt == 1)
   {
      m_Base = AHead->Items[0];
      DoProcessItemTFS(m_Base, AStack);
   }
   if (m_cnt > 1)
   {
      for (int i = 0; i <= m_cnt - 1; i++)
      {
         m_Base = AHead->Items[i];
         if (m_Base->Tail > 0)
           m_DTail->Append(m_Base);
         else
           m_DLN->Append(m_Base);
      }
      if (m_DLN->Count == 1)
      {
         m_Base = static_cast<TPredicateItemBase*>(m_DLN->Items[0]);
         DoProcessItemTFS(m_Base, AStack);
      }
      else
      {
        m_BaseItem1 = static_cast<TPredicateItemBase*>(m_DLN->Items[0]);
        m_BaseItem2 = static_cast<TPredicateItemBase*>(m_DLN->Items[1]);
        DoProcessItemTFS(m_BaseItem1, AStack);
        DoProcessItemTFS(m_BaseItem2, AStack);
        for (int i = 2; i <= m_DLN->Count - 1; i++)
          m_D->Append(m_DLN->Items[i]);

         AHead->DeleteItemToList(m_BaseItem1);
         AHead->DeleteItemToList(m_BaseItem2);



         m_PWork = new TPredicateItemPWork;
         m_PWork->MainTreeList = AHead->MainTreeList;
         m_PWork->CurrAlternate = AHead->CurrAlternate;
         DoAssignPWork(m_PWork, m_BaseItem1, m_BaseItem2);

         while (m_D->Count >= 1)
         {

           m_Big = new TPredicateItemBig;
           m_Big->MainTreeList = AHead->MainTreeList;
           m_Big->CurrAlternate = AHead->CurrAlternate;
           m_Big->Envelope = true;
           m_Big->AddItem(m_PWork);


           m_BaseItem1 = m_Big;
           m_BaseItem2 = static_cast<TPredicateItemBase*>(m_D->Items[0]);
           DoProcessItemTFS(m_BaseItem2, AStack);
           AHead->DeleteItemToList(m_BaseItem2);
           m_PW = new TPredicateItemPWork;
           m_PW->MainTreeList = AHead->MainTreeList;
           m_PW->CurrAlternate = AHead->CurrAlternate;
           DoAssignPWork(m_PW, m_BaseItem1, m_BaseItem2);
           m_D->Delete(m_BaseItem2);
           m_PWork = m_PW;

         }

         AHead->AddItem(m_PWork);
      }

      for (int i = 0; i <= m_DTail->Count - 1; i++)
      {
         m_Base = static_cast<TPredicateItemBase*>(m_DTail->Items[i]);
         AHead->AddItem(m_Base);
         AStack->InsertToFirst(m_Base);
      }

  }
  delete m_DTail;
  delete m_DLN;
  delete m_D;

}


//------------------------------------------------------------------------------
void TPredicateTFSConvertor::ClearPreparedList()
{
   TPredicatePreparedItem* Item;
   for (int i = 0; i <= f_PeparedList->Count -1; i++)
   {
      Item = static_cast<TPredicatePreparedItem*>(f_PeparedList->Items[i]);
      delete Item;
   }
   f_PeparedList->Clear();
}

void TPredicateTFSConvertor::FillPreparedList()
{
   void *m_p;
   int m_type;
   TAlternativeParserItemBase* Obj;
   ClearPreparedList();
   for (int i = 0; i <= f_Parser->OutsCount - 1; i++)
   {
      TPredicatePreparedItem* Item = new TPredicatePreparedItem;
      Item->ParserItem = f_Parser->Outs[i];
      f_PeparedList->Add(Item);
   }
}

int __fastcall TPredicateTFSConvertor::GetPreparedCount()
{
   return  f_PeparedList->Count;
}

TPredicatePreparedItem* __fastcall TPredicateTFSConvertor::GetPreparedItems(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_PeparedList->Count - 1)
     return static_cast<TPredicatePreparedItem*>(f_PeparedList->Items[AIndex]);
   else
     return NULL;
}

void TPredicateTFSConvertor::DoAssignPWork(TPredicateItemPWork* APW,
  TPredicateItemBase* Item1, TPredicateItemBase* Item2)
{
    int m_type, m_who;
    TPredicateItemTFS* p_tfs;
    TPredicateItemBase* m_Base;

    APW->Item1 = Item1;
    APW->Item2 = Item2;

    m_type = Item1->Who();
    if ( m_type == 0 )
    {
      p_tfs = dynamic_cast<TPredicateItemTFS*>(Item1);
      if (p_tfs->TFS->BaseWorkShape->TypeShape == 1)
        if (p_tfs->TFE[0]->Big)
          p_tfs->TFE[0]->Big->OwnerPWork = APW;
    }
    if (m_type == 1)
       dynamic_cast<TPredicateItemBig*>(Item1)->OwnerPWork = APW;

    m_type = Item2->Who();
    if ( m_type == 0 )
    {
      p_tfs = dynamic_cast<TPredicateItemTFS*>(Item2);
      if (p_tfs->TFS->BaseWorkShape->TypeShape == 1)
        if (p_tfs->TFE[0]->Big)
          p_tfs->TFE[0]->Big->OwnerPWork = APW;
    }
    if (m_type == 1)
       dynamic_cast<TPredicateItemBig*>(Item2)->OwnerPWork = APW;


}





//------------------------------------------------------------------------------
void TPredicateTFSConvertor::MakeTree(TMainTreeList* ATreeMain)
{
   AnsiString SDebug;
   TPredicateItemBig* Big;
   FreePredicateStart();
   TDynamicArray *m_Stack = new TDynamicArray;
   f_PredicateStart = new TPredicateItemBig;
   f_PredicateStart->MainTreeList = ATreeMain;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   while(Big)
   {
     DoMake(Big, m_Stack);
     m_Stack->InitStack();
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
 //  DoProcess();
   DoSetNumber();

}


void TPredicateTFSConvertor::DoMake(TPredicateItemBig* ABig, TDynamicArray *AStack)
{
   int m_who;
   TPredicateItemBase* m_Base;
   TPredicateItemTFS *m_Tfs;
   TPredicatePreparedItem *Item;
   TAlternativeParserItem* ap_Item;
   TAlternativeParserTFSItem *ap_Tfs;
   TDynamicArray *D = new TDynamicArray;

   if (!ABig->Count)
   {
      f_Parser->Parse(ABig->MainTreeList);
      FillPreparedList();
      DoMakeItem(ABig, AStack);
   }
   else
   {
       TDynamicArray *m_List = new TDynamicArray;
       for (int i = 0; i <= ABig->Count - 1; i++)
       {
          m_Base = ABig->Items[i];
          m_who = m_Base->Who();
          if (!m_who)
          {
             m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_Base);
             m_List->Append(m_Tfs->TFS);
          }
       }
       f_Parser->Parse2(ABig->MainTreeList, m_List, ABig->CurrAlternate);
       FillPreparedList();
       ABig->FullBigItem(D);
       ABig->ClearListTFS();
       DoMakeItem(ABig, AStack);
       AStack->DeleteArray(D);
       delete m_List;
   }     
   delete D;
}


void TPredicateTFSConvertor::DoMakeItem(TPredicateItemBig* ABig, TDynamicArray *AStack)
{
   int m_who;
   TPredicateItemBase* m_Base;
   TPredicateItemTFS *m_Tfs;
   TTreeListTFS* TreeTFS;
   TPredicatePreparedItem *Item;
   TAlternativeParserItem* ap_Item;
   TAlternativeParserTFSItem *ap_Tfs;

   for (int i = 0; i <= PreparedCount - 1; i++)
   {
      Item =  PreparedItems[i];
      m_who = Item->ParserItem->Who();
      if ( m_who == 0 )
      {
        ap_Tfs = dynamic_cast<TAlternativeParserTFSItem*>(Item->ParserItem);
        if (ap_Tfs->TFS->BaseWorkShape->TypeShape == 1)
        {
           TPredicateItemTFS* p_Tfs = new TPredicateItemTFS;
           p_Tfs->CurrAlternate = ap_Tfs->CurrAlternate;
           p_Tfs->TFS = ap_Tfs->TFS;
           p_Tfs->MainTreeList = ap_Tfs->MainTreeList;
           for (int j = 0; j <= p_Tfs->CountTFE - 1; j++ )
           {
              if (p_Tfs->TFE[j]->Big)
                AStack->InsertToFirst(p_Tfs->TFE[j]->Big);
           }
           ABig->AddItem(p_Tfs);
        }
        else
        {
          TPredicateItemBig* p_Big = new TPredicateItemBig;
          p_Big->Envelope = true;

          TPredicateItemTFS* p_Tfs = new TPredicateItemTFS;
          p_Tfs->CurrAlternate = ap_Tfs->CurrAlternate;
          p_Tfs->TFS = ap_Tfs->TFS;
          p_Tfs->MainTreeList = ap_Tfs->MainTreeList;
          for (int j = 0; j <= p_Tfs->CountTFE - 1; j++ )
          {
             if (p_Tfs->TFE[j]->Big)
              AStack->InsertToFirst(p_Tfs->TFE[j]->Big);
          }
          //ABig->AddItem(p_Tfs);
          p_Big->AddItem(p_Tfs);
          p_Big->MainTreeList = ABig->MainTreeList;
          ABig->AddItem(p_Big);
       }

      }
      if ( m_who == 1 )
      {
          ap_Item = dynamic_cast<TAlternativeParserItem*>(Item->ParserItem);
          TPredicateItemBig* p_Big = new TPredicateItemBig;
          p_Big->Envelope = true;//////////убрать это
          for (int j = 0; j <= ap_Item->Count - 1; j++)
          {
             TPredicateItemTFS* p_Tfs =  new TPredicateItemTFS;
             p_Tfs->CurrAlternate = ap_Item->CurrAlternate;
             p_Tfs->TFS = ap_Item->Items[j];
             p_Tfs->MainTreeList = ap_Item->MainTreeList;
             p_Big->AddItem(p_Tfs);
             for (int k = 0; k <= p_Tfs->CountTFE - 1; k++ )
             {
               if (p_Tfs->TFE[k]->Big)
                AStack->InsertToFirst(p_Tfs->TFE[k]->Big);
             }

          }
          p_Big->CurrAlternate = ap_Item->CurrAlternate;
          p_Big->MainTreeList = ABig->MainTreeList;
          p_Big->Tail = ap_Item->Tail;
          ABig->AddItem(p_Big);
          AStack->InsertToFirst(p_Big);

        //}
     }
   }
}


void TPredicateTFSConvertor::DoSetNumber()
{
   TPredicateItemBig* Big;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   Big->Num = f_NumGenerator->NextNum();
   Big->ID = 0;
   while(Big)
   {

     DoSetNumberItem(Big, m_Stack);
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
}

void TPredicateTFSConvertor::DoSetNumberItem(TPredicateItemBig* AHead, TDynamicArray *AStack)
{
   int m_type;
   TPredicateItemBase *m_Base;
   TPredicateItemBase *m_BaseItem1, *m_BaseItem2;
   TPredicateItemPWork *m_PWork;
   TPredicateItemBig *m_Big;
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;

   f_NumGenerator->InitNum();

   for (int i = 0; i <= AHead->Count - 1; i++)
   {
      m_Base = AHead->Items[i];
      m_Base->Num = f_NumGenerator->NextNum();
      m_Base->NumParent = AHead->ID;
      m_type = m_Base->Who();
      if ( m_type == 1 )
      {
         if (!m_Base->Envelope)
           m_Base->ID = f_NumGeneratorReverse->NextLowNum();
         else
           m_Base->ID = AHead->ID;
         AStack->InsertToFirst(m_Base);
      }

      if ( m_type == 0 )
      {
         m_Tfs =  dynamic_cast<TPredicateItemTFS*>(m_Base);
         m_Tfs->ID = 0;
         for (int j = 0; j <= m_Tfs->CountTFE - 1; j++ )
         {
             if (m_Tfs->TFE[j]->Big)
             {
               m_Tfs->TFE[j]->Big->ID = m_Tfs->TFE[j]->ID;
               AStack->InsertToFirst(m_Tfs->TFE[j]->Big);
             }
         }
      }
      if ( m_type == 2 )
      {
         m_PWork = dynamic_cast<TPredicateItemPWork*>(m_Base);
         m_BaseItem1 = m_PWork->Item1;
         m_BaseItem2 = m_PWork->Item2;

         m_type = m_BaseItem1->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem1);
            m_Tfe = m_Tfs->TFE[0];
            m_Tfs->ID = 0;
            m_BaseItem1->ID = m_Tfs->MaxID;
            if (m_Tfe->Big)
            {
              m_Tfe->Big->ID =   m_BaseItem1->ID;
              AStack->InsertToFirst(m_Tfe->Big);
            }
         }
         if (m_type == 1)
         {
            m_BaseItem1->ID = f_NumGeneratorReverse->NextLowNum();
            AStack->InsertToFirst(m_BaseItem1);
         }


         m_type = m_BaseItem2->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem2);
            m_Tfe = m_Tfs->TFE[0];
            m_Tfs->ID = 0;
            m_BaseItem2->ID = m_Tfs->MaxID;
            if (m_Tfe->Big)
            {
              m_Tfe->Big->ID =   m_BaseItem2->ID;
              AStack->InsertToFirst(m_Tfe->Big);
            }
         }
         if (m_type == 1)
         {
             m_BaseItem2->ID = f_NumGeneratorReverse->NextLowNum();
             AStack->InsertToFirst(m_BaseItem2);
         }

      }
   }
}


void TPredicateTFSConvertor::CheckOldRecalc(TPredicateItemBase *AItem)
{
   int m_who = AItem->Who();
   if ( m_who == 0 )
   {
     TPredicateItemTFS* m_tfs =  dynamic_cast<TPredicateItemTFS*>(AItem);
     AItem->OldRecalc = f_TFSList->Find(m_tfs->TFS);
     if (!AItem->OldRecalc)
       f_TFSList->Append(m_tfs->TFS);
   }
}

TPredicateItemBase* TPredicateTFSConvertor::FindPredicateFromTreeListTFS(TTreeListTFS* AIndex)
{
   TPredicateItemBig* Big;
   TPredicateItemBase* Res = NULL;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   while(Big)
   {

     Res = DoFindPredicateFromTreeListTFS(AIndex, Big, m_Stack);
     if (Res)
       break;
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;
   return Res;
}


TPredicateItemBase* TPredicateTFSConvertor::DoFindPredicateFromTreeListTFS(TTreeListTFS* AIndex,
  TPredicateItemBig* ABig,  TDynamicArray *AStack)
{
   int m_type;
   TPredicateItemBase *m_Base;
   TPredicateItemBase *m_BaseItem1, *m_BaseItem2;
   TPredicateItemPWork *m_PWork;
   TPredicateItemBig *m_Big;
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;

   for (int i = 0; i <= ABig->Count - 1; i++)
   {
      m_Base = ABig->Items[i];
      m_type = m_Base->Who();
      if ( m_type == 1 )
      {
         AStack->InsertToFirst(m_Base);
      }

      if ( m_type == 0 )
      {
         m_Tfs =  dynamic_cast<TPredicateItemTFS*>(m_Base);
         if (m_Tfs->TFS == AIndex)
            return m_Tfs;
         for (int j = 0; j <= m_Tfs->CountTFE - 1; j++ )
         {
             if (m_Tfs->TFE[j]->Big)
               AStack->InsertToFirst(m_Tfs->TFE[j]->Big);
         }
      }
      if ( m_type == 2 )
      {
         m_PWork = dynamic_cast<TPredicateItemPWork*>(m_Base);
         m_BaseItem1 = m_PWork->Item1;
         m_BaseItem2 = m_PWork->Item2;

         m_type = m_BaseItem1->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem1);
            if (m_Tfs->TFS == AIndex)
              return m_Tfs;
            m_Tfe = m_Tfs->TFE[0];
            if (m_Tfe->Big)
              AStack->InsertToFirst(m_Tfe->Big);
         }
         if (m_type == 1)
             AStack->InsertToFirst(m_BaseItem1);


         m_type = m_BaseItem2->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem2);
            if (m_Tfs->TFS == AIndex)
              return m_Tfs;
            m_Tfe = m_Tfs->TFE[0];
            if (m_Tfe->Big)
              AStack->InsertToFirst(m_Tfe->Big);
         }
         if (m_type == 1)
             AStack->InsertToFirst(m_BaseItem2);

      }
   }
   return NULL;
}


AnsiString TPredicateTFSConvertor::DoDebugInfoMake(TPredicateItemBig* ABig, TDynamicArray *AStack)
{
   AnsiString Res = "";
   int m_type;
   TPredicateItemBase *m_Base;
   TPredicateItemBase *m_BaseItem1, *m_BaseItem2;
   TPredicateItemPWork *m_PWork;
   TPredicateItemBig *m_Big;
   TPredicateItemTFS *m_Tfs;
   TPredicateItemTFE *m_Tfe;


   for (int i = 0; i <= ABig->Count - 1; i++)
   {
      m_Base = ABig->Items[i];
      m_type = m_Base->Who();
      if ( m_type == 1 )
      {
         Res = Res + "Тип = 1 ";
         if (!m_Base->Envelope)
           Res = Res + " Обертка ";
         AStack->InsertToFirst(m_Base);
      }

      if ( m_type == 0 )
      {
         m_Tfs =  dynamic_cast<TPredicateItemTFS*>(m_Base);
         Res = Res + "Тип = 0 (ТФС) ";
         for (int j = 0; j <= m_Tfs->CountTFE - 1; j++ )
         {
             if (m_Tfs->TFE[j]->Big)
             {
               Res = Res + " ТФЕ " + IntToStr(j) + " содержит продолжение ";
               AStack->InsertToFirst(m_Tfs->TFE[j]->Big);
             }
         }
      }
      if ( m_type == 2 )
      {
         Res = Res + "Тип = 2 (последовательная) ";

         m_PWork = dynamic_cast<TPredicateItemPWork*>(m_Base);
         m_BaseItem1 = m_PWork->Item1;
         m_BaseItem2 = m_PWork->Item2;

         m_type = m_BaseItem1->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem1);
            Res = Res + "< 1 ая простая ТФС >";
            if (m_Tfe->Big)
            {
              Res = Res + "< 1 ая содержит продолжение >";
              AStack->InsertToFirst(m_Tfe->Big);
            }
         }
         if (m_type == 1)
         {
            Res = Res + "< 1 ая укрупненная >";
            AStack->InsertToFirst(m_BaseItem1);
         }


         m_type = m_BaseItem2->Who();
         if (!m_type)
         {
            m_Tfs = dynamic_cast<TPredicateItemTFS*>(m_BaseItem2);
            m_Tfe = m_Tfs->TFE[0];
            Res = Res + "< 2 ая простая ТФС >";
            if (m_Tfe->Big)
            {
              Res = Res + "< 2 ая содержит продолжение >";
              AStack->InsertToFirst(m_Tfe->Big);
            }
         }
         if (m_type == 1)
         {
            Res = Res + "< 2 ая укрупненная >";
            AStack->InsertToFirst(m_BaseItem2);
         }

      }
   }
   return Res;
}


void TPredicateTFSConvertor::DebugInfoMake(AnsiString *AStr)
{
   TPredicateItemBig* Big;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(f_PredicateStart);
   Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   Big->Num = f_NumGenerator->NextNum();
   Big->ID = 0;
   while(Big)
   {

     (*AStr) = (*AStr) +  DoDebugInfoMake(Big, m_Stack) + "\r\n";
     Big = static_cast<TPredicateItemBig*>(m_Stack->Pop());
   }
   delete m_Stack;

}
*/
