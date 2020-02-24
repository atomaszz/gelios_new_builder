//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternativeParserEnlarger.h"
#include "uAlternativeParserGrp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int g_TrashCounter;
void InitTrashCounter()
{
  g_TrashCounter = 0;
}

int NextTrashItemID()
{
   return (++g_TrashCounter);
}


//--------------- TAlternativeParserEnlargerItem -------------------------------
TAlternativeParserEnlargerItem::TAlternativeParserEnlargerItem()
{
   f_List = new TList;
   f_Basis = false;
   f_Parent = NULL;
   f_ParentMain = NULL;
}

TAlternativeParserEnlargerItem::~TAlternativeParserEnlargerItem()
{
   delete f_List;
}

void TAlternativeParserEnlargerItem::AddTfsItem(TAlternativeParserGrpItemTFS *AGrpTfs)
{
   if (f_List->IndexOf(AGrpTfs) < 0)
     f_List->Add(AGrpTfs);
}

void TAlternativeParserEnlargerItem::DeleteTfsItem(TAlternativeParserGrpItemTFS *AGrpTfs)
{
   int in = f_List->IndexOf(AGrpTfs);
   if (in >= 0)
     f_List->Delete(in);
}


void TAlternativeParserEnlargerItem::CascadeDelete(TDynamicArray *AMass)
{
   for(int i = 0; i <= AMass->Count - 1; i++)
     DeleteTfsItem(static_cast<TAlternativeParserGrpItemTFS*>(AMass->Items[i]));
}


int TAlternativeParserEnlargerItem::Find(TAlternativeParserGrpItemTFS *AGrpTfs)
{
   return f_List->IndexOf(AGrpTfs);
}



int __fastcall TAlternativeParserEnlargerItem::GetCount()
{
   return f_List->Count;
}

TAlternativeParserGrpItemTFS* __fastcall TAlternativeParserEnlargerItem::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}


int TAlternativeParserEnlargerItem::Pos(TAlternativeParserEnlargerStep *AStep)
{
  int plen = AStep->Count;
  int slen = Count;
  int pindx;
  int cmppos;
  int endpos;
  for( endpos = plen-1; endpos < slen ; )
  {
     for( cmppos = endpos, pindx = (plen - 1); pindx >= 0 ; cmppos--, pindx-- )
      if( Items[cmppos]->TFS !=  AStep->Items[pindx]->TFS )
       {
         endpos+= 1;
         break;
       }
     if( pindx < 0 )
       return ( endpos - (plen-1));
  }
  return -1;
}


int TAlternativeParserEnlargerItem::FillStep(TAlternativeParserEnlargerStep* AStep,
  int APos, int ACount)
{
   int res = -1;
   int d = Count;
   if ( (d - APos - ACount + 1) > 0 )
   {
     for (res = APos; res <= APos + ACount - 1; res++)
        AStep->AddItem(Items[res]);
   }
   return res;
}


//--------------------TAlternativeParserEnlargerStep -------------------------------
TAlternativeParserEnlargerStep::TAlternativeParserEnlargerStep()
{
//   f_Parent = NULL;
   f_List = new TList;
}

TAlternativeParserEnlargerStep::~TAlternativeParserEnlargerStep()
{
   delete f_List;
}

void TAlternativeParserEnlargerStep::AddItem(TAlternativeParserGrpItemTFS *AGrpTfs)
{
   if (f_List->IndexOf(AGrpTfs) < 0)
     f_List->Add(AGrpTfs);
}

int __fastcall TAlternativeParserEnlargerStep::GetCount()
{
   return f_List->Count;
}

TAlternativeParserGrpItemTFS* __fastcall TAlternativeParserEnlargerStep::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserGrpItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TAlternativeParserEnlargerStep::Clear()
{
   f_List->Clear();
}


//-----------------------TAlternativeParserEnlargerTFS-------------------------
int TAlternativeParserEnlargerTFS::Who()
{
   return 0;
}


//-----------------------TAlternativeParserEnlargerBig----------------------
TAlternativeParserEnlargerBig::TAlternativeParserEnlargerBig()
{
   f_List = new TList;
}

TAlternativeParserEnlargerBig::~TAlternativeParserEnlargerBig()
{
   delete f_List;
}

void TAlternativeParserEnlargerBig::FreeList()
{
   //TAlternativeParserEnlargerTFS
}

void TAlternativeParserEnlargerBig::AddItem(TAlternativeParserEnlargerTFS* ATfs)
{
   if (f_List->IndexOf(ATfs) == -1 )
     f_List->Add(ATfs);
}



int TAlternativeParserEnlargerBig::Who()
{
   return 1;
}


//--------------------------TAlternativeParserEnlargerTrashItem ---------------------------
TAlternativeParserEnlargerTrashItem::TAlternativeParserEnlargerTrashItem()
{
   f_ID = 0;
   f_Length = 0;
   f_Pos = NULL;
   f_Owner = NULL;
}


//--------------------------TAlternativeParserEnlargerTrash ---------------------------
TAlternativeParserEnlargerTrash::TAlternativeParserEnlargerTrash()
{
   f_List = new TList;
}

TAlternativeParserEnlargerTrash::~TAlternativeParserEnlargerTrash()
{
   FreeList();
   delete f_List;
}


void TAlternativeParserEnlargerTrash::FreeList()
{
   TAlternativeParserEnlargerTrashItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++ )
   {
      Item = static_cast<TAlternativeParserEnlargerTrashItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();

}

int __fastcall TAlternativeParserEnlargerTrash::GetCount()
{
   return f_List->Count;
}

TAlternativeParserEnlargerTrashItem* __fastcall TAlternativeParserEnlargerTrash::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserEnlargerTrashItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}


TAlternativeParserEnlargerTrashItem* TAlternativeParserEnlargerTrash::NewTrashItem()
{
   TAlternativeParserEnlargerTrashItem* Item = new TAlternativeParserEnlargerTrashItem;
   f_List->Add(Item);
   return Item;
}

void TAlternativeParserEnlargerTrash::Clear()
{
   FreeList();
}





//-------------------TAlternativeParserEnlarger -------------------------------
TAlternativeParserEnlarger::TAlternativeParserEnlarger()
{
   f_List = new TList;
   f_Trash = new TAlternativeParserEnlargerTrash;
}

TAlternativeParserEnlarger::~TAlternativeParserEnlarger()
{
   FreeList();
   delete f_List;
   delete f_Trash;
}

void TAlternativeParserEnlarger::FreeList()
{
   TAlternativeParserEnlargerItem* Item;
   for(int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternativeParserEnlargerItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

int __fastcall TAlternativeParserEnlarger::GetCount()
{
   return f_List->Count;
}

TAlternativeParserEnlargerItem* __fastcall TAlternativeParserEnlarger::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternativeParserEnlargerItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}



void TAlternativeParserEnlarger::Enlarge(TAlternativeParserGrpCrossItem* AItem)
{
   DoFill(AItem);
   DoEnlarge();
}

TAlternativeParserEnlargerItem* TAlternativeParserEnlarger::GetNew(TAlternativeParserGrpCrossItem* AParentMain)
{
   TAlternativeParserEnlargerItem* Item = new TAlternativeParserEnlargerItem;
   Item->ParentMain = AParentMain;
   f_List->Add(Item);
   return Item;
}


void TAlternativeParserEnlarger::DoFill(TAlternativeParserGrpCrossItem* AItem)
{
   int m_who;
   TAlternativeParserGrpItemTFS* mTfs;
   TAlternativeParserGrpItemBase* mBase;
   TAlternativeParserGrpCrossItemOut* mOut;
   TAlternativeParserEnlargerItem* Item = GetNew(AItem);
   Item->Basis = true;
   for (int i = 0; i <= AItem->CountBasis - 1; i++ )
     Item->AddTfsItem(dynamic_cast<TAlternativeParserGrpItemTFS*>(AItem->ItemsBasis[i]));

   for (int i = 0; i <= AItem->CountOut - 1; i++)
   {
      mOut = AItem->ItemsOut[i];
      Item = GetNew(AItem);
      Item->Parent = mOut;
      for (int j = 0; j <= mOut->Count - 1; j++)
      {
         mBase = mOut->Items[j];
         m_who = mBase->Who();
         if (m_who == 0)
         {
           mTfs = dynamic_cast<TAlternativeParserGrpItemTFS*>(mBase);
           Item->AddTfsItem(mTfs);
         }
      }
   }
}

TAlternativeParserEnlargerItem* TAlternativeParserEnlarger::FindMax()
{
   TAlternativeParserEnlargerItem* Res = NULL;
   int a, b = 0;
   for (int i = 0; i <= Count - 1; i++)
   {
      a = Items[i]->Count;
      if (a > b)
      {
         b = a;
         Res = Items[i];
      }
   }
   return Res;
}

void TAlternativeParserEnlarger::ClearTrash()
{
   f_Trash->Clear();
}

bool TAlternativeParserEnlarger::IsEmptyTrash()
{
   return (f_Trash->Count == 0);
}


void TAlternativeParserEnlarger::CreateTrashItem(TAlternativeParserGrpItemTFS* APos, int ALength,
  TAlternativeParserEnlargerItem* AOwner, int AID)
{
   TAlternativeParserEnlargerTrashItem *Item = f_Trash->NewTrashItem();
   Item->Pos = APos;
   Item->Length = ALength;
   Item->Owner = AOwner;
   Item->ID = AID;
}

void TAlternativeParserEnlarger::Restruct()
{
   int mpos;
   TAlternativeParserEnlargerTrashItem *TI;
   TDynamicArray *mDel = new TDynamicArray;
   for(int i = 0; i <= f_Trash->Count - 1; i++ )
   {
      TI = f_Trash->Items[i];
      mpos = TI->Owner->Find(TI->Pos);
      if (mpos >= 0)
      {
        mDel->Clear();
        for (int j = mpos; j <= mpos + TI->Length - 1; j++)
          mDel->Append(TI->Owner->Items[j]);
        TI->Owner->CascadeDelete(mDel);
      }
   }
   delete mDel;
}



void TAlternativeParserEnlarger::DoEnlarge()
{
   int m, cnt, index, r_f, r_pos, m_id;
   TAlternativeParserEnlargerStep* MStep;
   TAlternativeParserEnlargerItem *A, *B;
   TDynamicArray *DM = new TDynamicArray;
   MStep = new TAlternativeParserEnlargerStep;
   int c_trash;
   bool go = true;
   while (go)
   {
      go = false;
      m = FindMax()->Count;
      cnt = Count;
      c_trash = 0;
   //   ClearTrash();
      for (int i = m; i >= 1 ; i--)
      {
         DM->Clear();
         for(int j = 0; j <= cnt - 1 ; j++)
         {
            A = Items[j];
            MStep->Clear();
            index = 0;
            r_f = A->FillStep(MStep, index, i);
            DM->Append(A);
            while (r_f > 0)
            {
               m_id = NextTrashItemID();
               for (int k = 0; k <= cnt - 1 ; k++)
               {
                  B = Items[k];
                  if (!DM->Find(B))
                  {
                     r_pos = B->Pos(MStep);
                     if (r_pos >= 0)
                     {
                        CreateTrashItem(A->Items[index], i, A, m_id);
                        CreateTrashItem(B->Items[r_pos], i, B, m_id);
                        c_trash++;
                     }
                  }
               }
               MStep->Clear();
               r_f = A->FillStep(MStep, ++index, i);
            }
         }
         if (c_trash)
         {
           Restruct();
           go = true;
           break;
         }
      }
   }
   delete MStep;
   delete DM;
}

void TAlternativeParserEnlarger::Init()
{
   ClearTrash();
   FreeList();//26.08.2007
}

void TAlternativeParserEnlarger::FindTrashItem(TAlternativeParserGrpCrossItem* AOwner,
  TDynamicArray *AOut)
{
   TAlternativeParserEnlargerTrashItem* Item;
   AOut->Clear();
   for (int i = 0; i <= f_Trash->Count - 1; i++)
   {
      Item = f_Trash->Items[i];
      if( Item->Owner->ParentMain == AOwner )
        AOut->Append(Item);
   }
}



