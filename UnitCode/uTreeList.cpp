//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTreeList.h"
#include "uListShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TNodeAlt* FindAlterantive(int AId, TListNode* AListNode)
{
   TNodeAlt* Res;
   for (int i = 0; i <= AListNode->AlternateCount - 1; i++)
   {
      Res = AListNode->AlternateItem[i];
      if ( Res->ID == AId)
        return Res;
   }
   return Res;
}

TTreeStack::TTreeStack()
{
   f_List = new TList;
}

TTreeStack::~TTreeStack()
{
   FreeList();
   delete f_List;
}

void TTreeStack::FreeList()
{
   TTreeStackItem *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TTreeStackItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

void TTreeStack::AddToStack(int ALevel)
{
   TTreeStackItem *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TTreeStackItem*>(f_List->Items[i]);
      if (Item->Level == ALevel) return;
   }
   Item = new  TTreeStackItem;
   Item->Level = ALevel;
   f_List->Add(Item);
}

void TTreeStack::Clear()
{
   FreeList();
}

TTreeStackItem* TTreeStack::GetLevel()
{
   TTreeStackItem *Item;
   for (int i = 0; i <= f_List->Count - 1; i++ )
   {
      Item = static_cast<TTreeStackItem*>(f_List->Items[i]);
      if (!Item->Fixed)
        return Item;
   }
   return NULL;
}


TTreeList::TTreeList()
{
   f_TreeList = new TMainTreeList;
   f_TreeList->Level = 0;
   f_Stack = new TTreeStack;
   f_AltInfo = new TAltInfo;
}

TTreeList::~TTreeList()
{
   delete f_TreeList;
   delete f_Stack;
   delete f_AltInfo;
}



void TTreeList::Init(int ALevel)
{
   f_TreeList->Clear();
   f_TreeList->Level = ALevel;//08.11.2007
   f_Stack->Clear();
   f_Stack->AddToStack(ALevel);
   f_AltInfo->Clear();
}

TMainTreeList* TTreeList::FindByLevel(TMainTreeList* ABegin, int ALevel)
{
    TMainTreeList* Res = NULL;
    TDynamicArray *Dyn = new TDynamicArray;
    Dyn->Append(ABegin);
    int q = 0;
    while (Dyn->Items[q])
    {
       Res = static_cast<TMainTreeList*>(Dyn->Items[q]);
       for (int i = 0; i <= Res->ItemCount - 1; i++)
        for (int j = 0; j <= Res->AlternateItem[i]->ItemCount - 1; j++)
          for (int k = 0; k <= Res->AlternateItem[i]->TreeTFSItem[j]->ItemCount - 1; k++ )
           if (Res->AlternateItem[i]->TreeTFSItem[j]->TreeTFEItem[k]->MainNode)
           {
              Dyn->Append(Res->AlternateItem[i]->TreeTFSItem[j]->TreeTFEItem[k]->MainNode);
           }
      q++;
    }


    for (int i = 0; i <= Dyn->Count - 1; i++)
    {
      Res = static_cast<TMainTreeList*>(Dyn->Items[i]);
      if (Res->Level == ALevel)
      {
        delete Dyn;
        return Res;
      }
    }
    delete Dyn;
    return NULL;

/*
    bool mFind;
    TMainTreeList* Res = NULL;
    if (ABegin->Level == ALevel)
    {
      AFind = true;
      return ABegin;
    }
    else  AFind = false;
    for (int i = 0; i <= ABegin->ItemCount - 1; i++)
      for (int j = 0; j <= ABegin->AlternateItem[i]->ItemCount - 1; j++)
         for (int k = 0; k <= ABegin->AlternateItem[i]->TreeTFSItem[j]->ItemCount - 1; k++ )
           if (ABegin->AlternateItem[i]->TreeTFSItem[j]->TreeTFEItem[k]->MainNode)
           {
             Res = FindByLevel((ABegin->AlternateItem[i]->TreeTFSItem[j]->TreeTFEItem[k]->MainNode), ALevel, mFind);
             if(mFind)
             return Res;
            }
*/

}


void TTreeList::FillTreeFromList(TListNode* AListNode)
{
   TTreeStackItem *Item;
   TAltInfoItem *AltInfoItem;
   TAlternateTreeList *AT;
   TNodeMain *Node;
   TTreeListTFS *Tfs;
   TMainTreeList* AMT;
   TMainTreeList* MNew;
   TTreeListItem *LI;
   Init(0);
   Item = f_Stack->GetLevel();
   while (Item)
   {
      AMT = FindByLevel(f_TreeList, Item->Level);
      if (AMT)
      {
        AListNode->LoadInfoForAlternate(f_AltInfo, Item->Level);
        for (int i = 0; i <= f_AltInfo->ItemCount - 1; i++)
        {
           AltInfoItem = f_AltInfo->Item[i];
           AT = new TAlternateTreeList;
           AT->MainAlternative = AltInfoItem->Main;
           AT->NodeStart = AltInfoItem->NodeStart;
           AT->NodeEnd = AltInfoItem->NodeEnd;
           AT->ID = AltInfoItem->ID;
           AT->Num = AltInfoItem->Num;
           Node =  AListNode->SearchFirstNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Item->Level );
           while (Node)
           {
              Tfs = new TTreeListTFS(Node->WorkShape);
              AT->AddToAlternate(Tfs);
              for (int j = 0; j <= Tfs->ItemCount - 1; j++)
              {
                 LI = Tfs->TreeTFEItem[j];
                 f_Stack->AddToStack(LI->BaseShape->ID);
                 if (AListNode->IsContainsChildShape(LI->BaseShape->ID))
                 {
                    if (!LI->MainNode)
                    {
                       MNew = new TMainTreeList;
                       MNew->Level = LI->BaseShape->ID;
                       LI->MainNode = MNew;
                    }
                 }
              }
              Node =  AListNode->SearchNextNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Node);
           }
           AMT->AddToTree(AT);
        }
      }
      Item->Fixed = true;
      Item = f_Stack->GetLevel();
   }
}

void TTreeList::FillTreeFromList(TListNode* AListNode, int AParentShapeID,
  TBaseWorkShape *AStart, TBaseWorkShape *AEnd)
{
   TTreeStackItem *Item;
   TAltInfoItem *AltInfoItem;
   TAlternateTreeList *AT, *ATMain = NULL;
   TNodeMain *Node;
   TTreeListTFS *Tfs;
   TMainTreeList* AMT;
   TMainTreeList* MNew;
   TTreeListItem *LI;
   Init(AParentShapeID);
   Item = f_Stack->GetLevel();
   while (Item)
   {
      AMT = FindByLevel(f_TreeList, Item->Level);
      if (AMT)
      {
        AListNode->LoadInfoForAlternate(f_AltInfo, Item->Level);
        for (int i = 0; i <= f_AltInfo->ItemCount - 1; i++)
        {
           AltInfoItem = f_AltInfo->Item[i];
           if (AltInfoItem->Main)
           {
             bool f_start = false;
             bool f_end = false;
             AT = new TAlternateTreeList;
             AT->ID = 0;//AltInfoItem->ID;
             AT->Num = 0;//AltInfoItem->Num;

             AT->MainAlternative = AltInfoItem->Main;
             AT->NodeEnd = NULL;

             if(AParentShapeID != Item->Level)
             {
               AT->NodeStart = AltInfoItem->NodeStart;
               AT->NodeEnd = AltInfoItem->NodeEnd;
             }

             ATMain = AT;
             Node =  AListNode->SearchFirstNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Item->Level );
             while (Node)
             {
                if ( (Node->WorkShape == AStart) && (AParentShapeID == Item->Level))
                {
                  f_start = true;
                  AT->NodeStart = Node;
                }

                if (( f_start && !f_end ) || (AParentShapeID != Item->Level) )
                {
                  Tfs = new TTreeListTFS(Node->WorkShape);
                  AT->AddToAlternate(Tfs);
                  for (int j = 0; j <= Tfs->ItemCount - 1; j++)
                  {
                     LI = Tfs->TreeTFEItem[j];
                     f_Stack->AddToStack(LI->BaseShape->ID);
                     if (AListNode->IsContainsChildShape(LI->BaseShape->ID))
                     {
                        if (!LI->MainNode)
                        {
                           MNew = new TMainTreeList;
                           MNew->Level = LI->BaseShape->ID;
                           LI->MainNode = MNew;
                        }
                     }
                  }
                }

                if ((Node->WorkShape == AEnd) && (AParentShapeID == Item->Level))
                  f_end = true;

                Node =  AListNode->SearchNextNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Node);
             }
             AMT->AddToTree(AT);
           }

        }


        for (int i = 0; i <= f_AltInfo->ItemCount - 1; i++)
        {
           AltInfoItem = f_AltInfo->Item[i];
           if (!AltInfoItem->Main)
           {
              TBaseWorkShape* WS = AltInfoItem->NodeStart->WorkShape;
              TBaseWorkShape* WE = AltInfoItem->NodeEnd->WorkShape;
              if (ATMain->FindTFS(WS) && ATMain->FindTFS(WE))
              {
                 AT = new TAlternateTreeList;
                 AT->ID = AltInfoItem->ID;
                 AT->Num = AltInfoItem->Num;

                 AT->MainAlternative = AltInfoItem->Main;
                 AT->NodeStart = AltInfoItem->NodeStart;
                 AT->NodeEnd = AltInfoItem->NodeEnd;
                 Node =  AListNode->SearchFirstNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Item->Level );
                 while (Node)
                 {
                    Tfs = new TTreeListTFS(Node->WorkShape);
                    AT->AddToAlternate(Tfs);
                    for (int j = 0; j <= Tfs->ItemCount - 1; j++)
                    {
                       LI = Tfs->TreeTFEItem[j];
                       f_Stack->AddToStack(LI->BaseShape->ID);
                       if (AListNode->IsContainsChildShape(LI->BaseShape->ID))
                       {
                          if (!LI->MainNode)
                          {
                             MNew = new TMainTreeList;
                             MNew->Level = LI->BaseShape->ID;
                             LI->MainNode = MNew;
                          }
                       }
                    }
                    Node =  AListNode->SearchNextNodeToAlternate(AltInfoItem->ID, AltInfoItem->Num, Node);
                 }
                 AMT->AddToTree(AT);
              }

           }

        }

      }
      Item->Fixed = true;
      Item = f_Stack->GetLevel();
   }
}





