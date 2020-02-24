//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include "uPredicatePath.h"
#include "uPredicateTFSConvertor.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
int PredicatePathCnt = 0;

void PredicatePathInit()
{
  PredicatePathCnt = 0;
}
int PredicatePathNextNum()
{
  --PredicatePathCnt;
  return PredicatePathCnt;
}


TPredicatePathNode::TPredicatePathNode(TPredicateItemBase* AParentItemBase,
  int AID, int ANumAlt)
{
  f_Cnt = 0;
  f_ID = AID;
  f_MaxPermutation = 0;
  f_ParentItemBase = AParentItemBase;
  f_NumAlt = ANumAlt;
  f_List = new TList;
}

TPredicatePathNode::~TPredicatePathNode()
{
  FreeList();
  delete f_List;
}

void TPredicatePathNode::FreeList()
{
   for(int i = 0; i <= f_List->Count - 1; i++)
     delete static_cast<TPredicatePathNodeItem*>(f_List->Items[i]);
   f_List->Clear();
}

void TPredicatePathNode::Clear()
{
  FreeList();
}

int __fastcall TPredicatePathNode::GetCount()
{
  return f_List->Count;
}

TPredicatePathNodeItem* __fastcall TPredicatePathNode::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicatePathNodeItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TPredicatePathNode::AddItem(TPredicateItemBase* AItem)
{
   TPredicatePathNodeItem *N = new TPredicatePathNodeItem;
   if (AItem->Who() == 0)
   {
      N->TFS = dynamic_cast<TPredicateItemTFS*>(AItem)->TFS->BaseWorkShape;
      N->BlockID = N->TFS->BlockId;
   }
   else
      N->BlockID = PredicatePathNextNum();

   N->f_Index = f_Cnt;
   N->ItemBase = AItem;
   f_Cnt++;
   f_List->Add(N);
}

TPredicatePathNodeItem* TPredicatePathNode::CreateItem()
{
   TPredicatePathNodeItem *N = new TPredicatePathNodeItem;
   f_List->Add(N);
   N->f_Index = f_Cnt;
   f_Cnt++;
   return N;
}


AnsiString __fastcall TPredicatePathNode::GetText()
{
   int m_pos, i = 0;
   TPredicatePathNodeItem *T;
   AnsiString Res = "vector(" + IntToStr(f_ID) + ", " + IntToStr(f_NumAlt) + ", [";
   T = FindIndexFirst(m_pos);
   while(T)
   {
      if ( i != 0 )
        Res = Res + ", ";
      Res = Res + IntToStr(T->BlockID);
      i++;
      T = FindIndexNext(m_pos);
   }
   Res = Res + "]).";
   return Res;
}

TPredicatePathNodeItem* TPredicatePathNode::FindIndexFirst(int &APos)
{
   APos = 0;
   TPredicatePathNodeItem *T;
   for(int i = APos; i <= f_List->Count - 1; i++)
   {
      T = Items[i];
      if (T->Index == 0)
        return T;
   }
   return NULL;
}

TPredicatePathNodeItem* TPredicatePathNode::FindIndexNext(int &APos)
{
   APos++;
   TPredicatePathNodeItem *T;
   for(int i = 0; i <= f_List->Count - 1; i++)
   {
      T = Items[i];
      if (T->Index == APos)
        return T;
   }
   return NULL;
}


TPredicatePathNodeItem* TPredicatePathNode::FindByBlockID(int ABlockID)
{
  TPredicatePathNodeItem *T;
  for(int i = 0; i <= f_List->Count - 1; i++)
  {
    T = Items[i];
    if (T->BlockID == ABlockID)
      return T;
  }
  return NULL;
}

bool TPredicatePathNode::IsLike(TPredicatePathNode *ANode)
{
  int mCnt = 0;
  if(f_List->Count == ANode->Count)
  {
    if (f_ID == ANode->ID)
    {
       if (f_NumAlt == ANode->NumAlt)
       {
         for(int i = 0; i <= ANode->Count - 1; i++)
           if(FindByBlockID(ANode->Items[i]->BlockID))
             mCnt++;
         return mCnt == ANode->Count;
       }
    }
  }
  return false;
}

void TPredicatePathNode::Assign(TPredicatePathNode *ASource)
{
  f_ID = ASource->ID;
  f_NumAlt = ASource->NumAlt;
  f_ParentItemBase = ASource->ParentItemBase;
  f_MaxPermutation = ASource->MaxPermutation;
  TPredicatePathNodeItem *IPS, *IPN;
  Clear();
  f_Cnt = 0;
  for(int i = 0; i <= ASource->Count - 1; i++)
  {
    IPS = ASource->Items[i];
    IPN = CreateItem();
    IPN->BlockID = IPS->BlockID;
    IPN->TFS = IPS->TFS;
    IPN->ItemBase = IPS->ItemBase;
    IPN->SetIndex(IPS->Index);
    f_Cnt++;
  }
}

void TPredicatePathNode::SwapItem(TPredicatePathNodeItem* AItem1,
  TPredicatePathNodeItem* AItem2)
{
  int mi;
  int idx1  = f_List->IndexOf(AItem1);
  int idx2  = f_List->IndexOf(AItem2);
  if ( (idx1 >= 0) && (idx2 >= 0) )
  {
    f_List->Items[idx1] = AItem2;
    f_List->Items[idx2] = AItem1;
    mi = AItem1->Index;
    AItem1->f_Index = AItem2->f_Index;
    AItem2->f_Index = mi;
  }
}





//--------------- TPredicatePathItem --------------------------------------
TPredicatePathItem::TPredicatePathItem()
{
   f_List = new TList;
}

TPredicatePathItem::~TPredicatePathItem()
{
   FreeList();
   delete f_List;
}

void TPredicatePathItem::FreeList()
{
   TPredicatePathNode* Item;
   for(int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPredicatePathNode*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

int __fastcall TPredicatePathItem::GetNodeCount()
{
   return f_List->Count;
}

TPredicatePathNode* __fastcall TPredicatePathItem::GetNodeItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicatePathNode*>(f_List->Items[AIndex]);
   else
     return NULL;
}

AnsiString __fastcall TPredicatePathItem::GetText()
{
   AnsiString Res;
   TPredicatePathNode* N;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      N = static_cast<TPredicatePathNode*>(f_List->Items[i]);
      Res = Res + N->Text + "\r\n";
   }
   return Res;
}

TPredicatePathNodeItem* TPredicatePathItem::FindPathNodeByParent(TPredicateItemBase* AParent)
{
   TPredicatePathNode* Item;
   TPredicatePathNodeItem *NItem;
   for(int i = 0; i <= NodeCount - 1; i++)
   {
     Item = NodeItems[i];
     for(int j  = 0; j <= Item->Count - 1; j++)
     {
       NItem = Item->Items[j];
       if (NItem->ItemBase == AParent)
         return NItem;
     }
   }
   return NULL;
}


TPredicatePathNode* TPredicatePathItem::CreatePathNode(
  TPredicateItemBase* AParentItemBase)
{
   int mID = 0;
   int Num = 0;
   if (AParentItemBase)
   {
     Num = dynamic_cast<TPredicateItemBig*>(AParentItemBase)->NumAlt;
     TPredicatePathNodeItem* NI = FindPathNodeByParent(AParentItemBase);
     if (NI)
       mID = NI->BlockID;
   }    
   TPredicatePathNode* N = new TPredicatePathNode(AParentItemBase, mID, Num);
   f_List->Add(N);
   return N;
}

void TPredicatePathItem::Clear()
{
  FreeList();
}


TPredicatePathNode* TPredicatePathItem::FindLikePathNode(TPredicatePathNode* ANode)
{
   TPredicatePathNode* Item;
   for(int i = 0; i <= NodeCount - 1; i++)
   {
     Item = NodeItems[i];
     if (Item->IsLike(ANode))
       return Item;
   }
   return NULL;
}

TPredicatePathNode* TPredicatePathItem::LastPathNode()
{
   if (f_List->Count > 0)
     return  static_cast<TPredicatePathNode*>(f_List->Items[f_List->Count - 1]);
   return NULL;
}

void TPredicatePathItem::Assign(TPredicatePathItem *ASource)
{
  TPredicatePathNode* PN;
  if ( ASource )
  {
    Clear();
    for(int i = 0; i <= ASource->NodeCount - 1; i++)
    {
      PN = CreatePathNode(NULL);
      PN->Assign(ASource->NodeItems[i]);
    }
  }
}

//---------------------TPredicatePath ------------------------
TPredicatePath::TPredicatePath()
{
  f_Max = 10000;
  f_Rate = 100.0;
  f_BasePath = new TPredicatePathItem;
  f_UsedPath = new TPredicatePathItem;
  f_OptSovmPath = new TPredicatePathItem;
  f_OgrSovm = NULL;
  f_ListDescendant = new TList;
}

TPredicatePath::~TPredicatePath()
{
   FreeListDescendant();
   delete f_BasePath;
   delete f_UsedPath;
   delete f_OptSovmPath;
   delete f_ListDescendant;
}


void TPredicatePath::FreeListDescendant()
{
  TPredicatePathItem* Item;
  for(int i = 0; i <= f_ListDescendant->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathItem*>(f_ListDescendant->Items[i]);
    delete Item;
  }
  f_ListDescendant->Clear();
}

void TPredicatePath::Init()
{
  PredicatePathInit();
}

TPredicatePathItem* TPredicatePath::CloneToDescendant(TPredicatePathItem* ASource)
{
  TPredicatePathNode *S, *N;
  TPredicatePathNodeItem *IPS, *IPN;
  TPredicatePathItem* NItem = new TPredicatePathItem;
  for(int i = 0; i <= ASource->NodeCount - 1; i++)
  {
    S = ASource->NodeItems[i];
    N = NItem->CreatePathNode(NULL);
    N->Assign(S);
  }
  f_ListDescendant->Add(NItem);
  return NItem;
}

int __fastcall TPredicatePath::GetDescendantCount()
{
  return f_ListDescendant->Count;
}

TPredicatePathItem* __fastcall TPredicatePath::GetDescendantItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListDescendant->Count - 1)
     return static_cast<TPredicatePathItem*>(f_ListDescendant->Items[AIndex]);
   else
     return NULL;
}

void TPredicatePath::DoGenerateDescendant(TPredicatePathItem* AItem,
  TDynamicArray *AStack)
{
  TPredicatePathNode* CR;
  TPredicatePathNode* Source = AItem->LastPathNode();
  int nc = 0;
  int m_cnt = Source->Count;
  int m_maxper = Source->MaxPermutation;
  if (DescendantCount < f_Max)
  {
    if ( ( m_cnt > 2 )  )
    {
      int *mass =  new int[m_cnt];
      for(int i = 0; i <= m_cnt - 1; i++)
        mass[i] = Source->Items[i]->Index;
      int fact = Factorial(m_cnt);
      while (fact > 1)
      {
        NextArray(mass, m_cnt);
        if ( ((!nc) || (CheckRnd()) ) && (DescendantCount < f_Max) && (nc < m_maxper) )
        {
          TPredicatePathItem* N = CloneToDescendant(AItem);
          CR = N->LastPathNode();
          for(int j = 0; j <= m_cnt - 1; j++)
            CR->Items[j]->SetIndex(mass[j]);
          if (AddPredicatePathNodeFromBase(N))
            AStack->InsertToFirst(N);
          nc++;
        }
        fact--;

      }
      delete []mass;
    }
//    if (AddPredicatePathNodeFromBase(AItem))
//      AStack->InsertToFirst(AItem);
  }
    if (AddPredicatePathNodeFromBase(AItem)) //stas0813 перенес из верха
      AStack->InsertToFirst(AItem);

}


void TPredicatePath::GenerateDescendant(double ARate, int AMax)
{
  f_Max = AMax;
  f_Rate = ARate;
  CalcPermutationInPathNodes();
  TPredicatePathItem* P = InitDescendant();
  TDynamicArray *m_Stack = new TDynamicArray;
  while(P)
  {
    DoGenerateDescendant(P, m_Stack);
    P = static_cast<TPredicatePathItem*>(m_Stack->Pop());
  }
  delete m_Stack;
}

bool TPredicatePath::AddPredicatePathNodeFromBase(TPredicatePathItem* AItem)
{
  if(AItem)
  {
     int c = AItem->NodeCount;
     int b = BasePath->NodeCount;
     if ( b > c )
     {
       TPredicatePathNode* N = AItem->CreatePathNode(NULL);
       N->Assign(BasePath->NodeItems[c]);
       return true;
     }
  }
  return false;
}


void TPredicatePath::Swap(int *m, int i, int j)
{
  int t = m[i];
  m[i] = m[j];
  m[j] = t;
}

void TPredicatePath::Swap_Array(int *m, int i, int j)
{
  while (i < j)
    Swap(m, i++, j--);
}

int TPredicatePath::Find_Min(int *m, int i, int N)
{
   int j_min = i;
   for (int j = i + 1; j < N; j++)
   {
      if ((m[j] > m[i - 1]) && (m[j] < m[j_min]))
         j_min = j;
   }
   return j_min;
}

void TPredicatePath::NextArray(int *m, int N)
{
   int i = N - 1;
   while (i > 0)
   {
      if (m[i - 1] < m[i])
      {
         int j_min = Find_Min(m, i, N);
         Swap(m, j_min, i - 1);
         Swap_Array(m, i, N - 1);
         return;
      }
      i--;
   }
   Swap_Array(m, 0, N - 1);
}

int TPredicatePath::Factorial(int N)
{
   int res = 1;
   for (int i = 1; i <= N; i++)
      res*= i;
   return res;
}

void TPredicatePath::ClearDescendant()
{
  FreeListDescendant();
}


TPredicatePathItem* TPredicatePath::InitDescendant()
{
  FreeListDescendant();
  TPredicatePathItem *I = new TPredicatePathItem;
  TPredicatePathNode* N = I->CreatePathNode(NULL);
  N->Assign(BasePath->NodeItems[0]);
  f_ListDescendant->Add(I);
  return I;
}


bool TPredicatePath::CheckRnd()
{
   int r = random(100);
   return (r <= f_Rate);
}

void TPredicatePath::CalcPermutationInPathNodes()
{
  int c;
  int m_all = 1;
  int m_cnt = 0;
  TPredicatePathNode* N;
  if (f_Max > 0)
  {
    int cnt = BasePath->NodeCount;
    for(int i = 0; i <= cnt - 1; i++)
    {
      TPredicatePathNode* N = BasePath->NodeItems[i];
      c = N->Count;
      if ( c > 1 )
        m_cnt++;
      m_all *= Factorial(c);
    }

    double k = 1;
    if ( m_cnt > 0 )
      k = exp(1. / m_cnt * log(f_Max*1./m_all)) ;

    if (m_all > 0)
      for(int i = 0; i <= cnt - 1; i++)
      {
        N = BasePath->NodeItems[i];
        N->MaxPermutation = int( Factorial(N->Count) * k);
      }
  }
}

void TPredicatePath::DoGenerateOptSovmPath(TPredicatePathNode* ANode)
{
  TDynamicArray *A = new TDynamicArray;
  TDynamicArray *B = new TDynamicArray;
  TPredicatePathNodeItem* Item;
  for(int i = 0; i <= ANode->Count - 1; i++)
  {
    Item = ANode->Items[i];
    if ( f_OgrSovm->AddOgrSovm(Item->TFS) )
      A->Append(Item);
    else
      B->Append(Item);
  }
  int idx = 0;
  for(int i = 0; i <= A->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathNodeItem*>(A->Items[i]);
    Item->SetIndex(idx);
    idx++;
  }
  for(int i = 0; i <= B->Count - 1; i++)
  {
    Item = static_cast<TPredicatePathNodeItem*>(B->Items[i]);
    Item->SetIndex(idx);
    idx++;
  }
  delete A;
  delete B;
}

void TPredicatePath::GenerateOptSovmPath(TOgrSovmArray* AOgrSovm)
{
  TPredicatePathNode* N;
  f_OgrSovm = AOgrSovm;
  if (f_OgrSovm)
  {
    f_OgrSovm->Clear();
    f_OptSovmPath->Clear();
    for (int i = 0; i <= BasePath->NodeCount - 1; i++)
    {
      N = f_OptSovmPath->CreatePathNode(NULL);
      N->Assign(BasePath->NodeItems[i]);
      DoGenerateOptSovmPath(N);
    }
  }  
}











