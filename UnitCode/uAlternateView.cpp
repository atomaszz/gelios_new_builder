//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternateView.h"
#include "uDynamicArray.h"
#include "uTreeList.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
TAlternateView::TAlternateView()
{
   f_List = new TList;
}

TAlternateView::~TAlternateView()
{
   FreeList();
   delete f_List;
}

void TAlternateView::ClearAll()
{
   FreeList();
}


void TAlternateView::FreeList()
{
   TAlternateViewItem* Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TAlternateViewItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

int __fastcall TAlternateView::GetItemCount()
{
   return  f_List->Count;
}

TAlternateViewItem* __fastcall TAlternateView::GetItemView(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TAlternateViewItem* TAlternateView::CreateAlternateViewItem()
{
   TAlternateViewItem* Item =  new TAlternateViewItem;
   f_List->Add(Item);
   return Item;
}

TAlternateViewItem* TAlternateView::CreateAlternateClone(TAlternateViewItem* ASource,
  TAlternateViewItem* AParent)
{
   if (!ASource) return NULL;
   TAlternateViewItemTFS* TFS;
   TAlternateViewItem* Item =  new TAlternateViewItem;
   Item->WSStart = ASource->ItemTFS[0]->BaseWorkShape;
   for (int i = 0; i <= ASource->ItemCount - 2; i++)
     Item->AddItemTFS(ASource->ItemTFS[i]->BaseWorkShape, true);
   Item->MainTreeList = ASource->MainTreeList;
   Item->ParentTFE = ASource->ParentTFE;
   Item->Parent = AParent;
   f_List->Add(Item);
   return Item;
}

TAlternateViewItem* TAlternateView::CreateAlternateClone(TAlternateViewItem* ASource,
       TAlternateViewItem* AParent, TAlternateTreeList* AReplace)
{
   TBaseWorkShape *WS, *WE;
   TAlternateViewItemTFS* TFS;
   if (!ASource) return NULL;
   TAlternateViewItem* Item =  new TAlternateViewItem;
   Item->WSStart = ASource->ItemTFS[0]->BaseWorkShape;
   WS = AReplace->NodeStart->WorkShape;
   WE = AReplace->NodeEnd->WorkShape;
   int i = 0;
   for (; i <= ASource->ItemCount - 1; i++)
   {
     TFS = ASource->ItemTFS[i];
     if (TFS->BaseWorkShape == WS)
       break;
     else
       Item->AddItemTFS(ASource->ItemTFS[i]->BaseWorkShape, true);
   }
   for (int j = 0; j <= AReplace->ItemCount - 1; j++)
    Item->AddItemTFS(AReplace->TreeTFSItem[j]->BaseWorkShape, false);

   bool f_end = false;
   for (; i <= ASource->ItemCount - 1; i++)
   {
     TFS = ASource->ItemTFS[i];
     if (f_end)
       Item->AddItemTFS(ASource->ItemTFS[i]->BaseWorkShape, false);
     else
       f_end = (TFS->BaseWorkShape == WE);
   }

   Item->MainTreeList = ASource->MainTreeList;
   Item->ParentTFE = ASource->ParentTFE;
   Item->Parent = AParent;
   Item->Fixed = true;
   f_List->Add(Item);
   return Item;
}


void TAlternateView::DoCreate(TAlternateViewItem *AVItem)
{
   TAlternateViewItem* P;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(AVItem);
   P = static_cast<TAlternateViewItem*>(m_Stack->Pop());
   while(P)
   {
     DoCreateItem(P, m_Stack);
     P = static_cast<TAlternateViewItem*>(m_Stack->Pop());
   }
   delete m_Stack;
}


void TAlternateView::DoCreateItem(TAlternateViewItem *AVItem, TDynamicArray *AStack)
{
   TAlternateViewItem *AVNew;
   TAlternateTreeList *ATMain, *AL;
   TAlternateViewItemTFS* TFSView;
   TAlternateViewItemTFE* TFEView;
   TMainTreeList* MList;
   TTreeListItem* LI;
   TTreeListTFS* TFS;
   TDynamicArray *Dyn = new TDynamicArray;

   MList = AVItem->MainTreeList;
   if (!AVItem->Parent)
   {
     ATMain = MList->MainAlternative;
     for (int i = 0; i <= ATMain->ItemCount - 1; i++)
     {
        TFS = ATMain->TreeTFSItem[i];
        TFSView = AVItem->AddItemTFS(TFS->BaseWorkShape, true);
        MList->FindAlternate(TFS->BaseWorkShape, Dyn);
        for (int j = 0 ; j <= Dyn->Count - 1; j++)
        {
           AL = static_cast<TAlternateTreeList*>(Dyn->Items[j]);
           if (AL != ATMain)
           {
             AVNew = this->CreateAlternateClone(AVItem, AVItem);
             AVNew->WSEnd = AL->NodeEnd->WorkShape;
             DoFillAlternative(AVNew, AL);
             AStack->InsertToFirst(AVNew);
             AVItem->ArrayChild->Append(AVNew);
           }
        }
     }

   }
   else
   {
     for (int i = 0; i <= AVItem->ItemCount - 1; i++)
     {
        TFSView = AVItem->ItemTFS[i];
        if (!TFSView->Check)
        {
          MList->FindAlternate(TFSView->BaseWorkShape, Dyn);
          for (int j = 0 ; j <= Dyn->Count - 1; j++)
          {
             AL = static_cast<TAlternateTreeList*>(Dyn->Items[j]);
             if (AL != ATMain)
             {
               AVNew = this->CreateAlternateClone(AVItem, AVItem, AL);
               AVNew->WSEnd = AL->NodeEnd->WorkShape;
              // DoFillAlternative(AVNew, AL);
               AStack->InsertToFirst(AVNew);
               AVItem->ArrayChild->Append(AVNew);
             }
          }
          TFSView->Check = true;
        }

     }
   }
   DoFillChild(AVItem);
   DoFillTFE(AVItem, AStack);
   delete Dyn;
}

void TAlternateView::DoFillAlternative(TAlternateViewItem *AView, TAlternateTreeList *Alt)
{
   TTreeListTFS* TFS;
   for (int i = 0; i <= Alt->ItemCount - 1; i++)
   {
      TFS = Alt->TreeTFSItem[i];
      AView->AddItemTFS(TFS->BaseWorkShape, false);
   }
}

void TAlternateView::DoFillChild(TAlternateViewItem *AVItem)
{
   int j;
   TBaseWorkShape *WS;
   TAlternateViewItem* Child;
   TAlternateViewItemTFS* Tfs;
   for (int i = 0; i <= AVItem->ArrayChild->Count - 1; i++ )
   {
     Child = static_cast<TAlternateViewItem*>(AVItem->ArrayChild->Items[i]);
     if (!Child->Fixed)
     {
       WS = Child->WSEnd;
       for (j = 0; j <= AVItem->ItemCount-1; j++)
       {
          Tfs = AVItem->ItemTFS[j];
          if (Tfs->BaseWorkShape == WS)
            break;
       }
       for (++j; j <= AVItem->ItemCount-1; j++)
       {
          Tfs = AVItem->ItemTFS[j];
          Child->AddItemTFS(Tfs->BaseWorkShape, false);
       }
       Child->Fixed = true;
     }
   }
}

void TAlternateView::DoFillTFE(TAlternateViewItem *AVItem, TDynamicArray *AStack)
{
   TTreeListItem* LI;
   TAlternateTreeList *AL;
   TAlternateViewItemTFS* TFSView;
   TAlternateViewItemTFE* TFEView;
   for (int i = 0; i <= AVItem->ItemCount - 1; i++)
   {
      TFSView = AVItem->ItemTFS[i];
      for(int j = 0; j <= TFSView->ItemCount - 1; j++)
      {
        TFEView = TFSView->ItemTFE[j];
        LI = AVItem->MainTreeList->FindTFE(TFEView->BaseShape);
        if (LI->MainNode)
        {
           for(int k = 0; k <= LI->MainNode->ItemCount - 1; k++)
           {
             AL = LI->MainNode->AlternateItem[k];
             if ( AL->MainAlternative ) break;
             else AL = NULL;
           }
           if( AL )
           {
             TAlternateViewItem* AVNew =  this->CreateAlternateViewItem();
             AVNew->MainTreeList = LI->MainNode;
             AVNew->ParentTFE = TFEView;
             AStack->InsertToFirst(AVNew);
           }
        }
      }

   }



}



/*
void TAlternateView::FillAlternate(TAlternateViewItem* AVI, TAlternateTreeList* ASource)
{
   TTreeListTFS *TFS;
   TAlternateViewItemTFS *TFSView;
   TAlternateViewItemTFE *TFEView;
   TAlternateViewItem *AVNew;
   TTreeListItem *LI;
   TDynamicArray *Dyn = new TDynamicArray;
   for (int i = 0; i <= ASource->ItemCount - 1; i++)
   {
      TFS = ASource->TreeTFSItem[i];
      TFSView = AVI->AddItemTFS(TFS->BaseWorkShape);
      for(int j = 0; j <= TFSView->ItemCount - 1; j++)
      {
         TFEView = TFSView->ItemTFE[j];
         if (!TFEView->Fixed)
         {
            LI = ASource->FindTFE(TFEView->BaseShape);
            if (LI->MainNode)
            {
              for(int k = 1; k <= LI->MainNode->ItemCount - 1; k++)
              {
                 AVNew = CreateAlternateClone(AVI);
                 AVNew->SetFixedTFE(TFEView->BaseShape, true);
                 FillAlternate(AVNew, LI->MainNode->AlternateItem[k]);
                 Dyn->Array[k] = AVNew;
              }
            }
         }
         TFEView->Fixed = true;
      }
      for (int k = 0; k <= Dyn->Count - 1; k++)
      {
         AVNew = static_cast<TAlternateViewItem*>(Dyn->Items[k]);
      }
   }

}

void TAlternateView::DoCreate(TAlternateViewItem *AVItem)
{
   TAlternateViewItem *AVNew;
   TAlternateTreeList *ATMain, *AL;
   TAlternateViewItemTFS* TFSView;
   TAlternateViewItemTFE* TFEView;
   TTreeListItem* LI;
   TTreeListTFS* TFS;
   TDynamicArray *Dyn = new TDynamicArray;

   ATMain = AVItem->MainTreeList->MainAlternative;
   for (int i = 0; i <= ATMain->ItemCount - 1; i++)
   {
      TFS = ATMain->TreeTFSItem[i];
      TFSView = AVItem->AddItemTFS(TFS->BaseWorkShape);
      AVItem->MainTreeList->FindAlternate(TFS->BaseWorkShape, Dyn);
      for (int j = 0 ; j <= Dyn->Count - 1; j++)
      {
         AL = static_cast<TAlternateTreeList*>(Dyn->Items[j]);
         if (AL == ATMain) continue;
         AVNew = this->CreateAlternateClone(AVItem);
         AVNew->WSEnd = AL->NodeEnd->WorkShape;
         DoFillAlternative(AVNew, AL);
         AVItem->ArrayChild->Append(AVNew);
      }
      for(int j = 0; j <= TFSView->ItemCount - 1; j++)
      {
        TFEView = TFSView->ItemTFE[j];
        {
               LI = AVItem->MainTreeList->FindTFE(TFEView->BaseShape);
               if (LI->MainNode)
               {
                  for(int k = 0; k <= LI->MainNode->ItemCount - 1; k++)
                  {
                    AL = LI->MainNode->AlternateItem[k];
                    if ( AL->MainAlternative ) break;
                    else AL = NULL;
                  }
                  if( AL )
                  {
                      AVNew =  this->CreateAlternateViewItem();
                      AVNew->MainTreeList = LI->MainNode;
                      TFEView->NextItem = AVNew;
                      AVNew->ParentTFE = TFEView;
                      DoCreate(AVNew);
                  }

               }
            }
         }

   }
   AVItem->Fixed = true;
   delete Dyn;
}



void TAlternateView::DoFillAlternative(TAlternateViewItem *AView, TAlternateTreeList *Alt)
{
   TTreeListTFS* TFS;
   TAlternateViewItemTFS* TFSView;
   TAlternateTreeList *AL;
   TAlternateViewItem *AVNew;
   TAlternateViewItemTFE* TFEView;
   TTreeListItem* LI;

   TDynamicArray *Dyn = new TDynamicArray;
   for (int i = 0; i <= Alt->ItemCount - 1; i++)
   {
      TFS = Alt->TreeTFSItem[i];
      TFSView = AView->AddItemTFS(TFS->BaseWorkShape);
      //поискать альтернативый начинающиеся с  TFS в тукущем  ANode
      AView->MainTreeList->FindAlternate(TFS->BaseWorkShape, Dyn);
      for (int j = 0 ; j <= Dyn->Count - 1; j++)
      {
         AL = static_cast<TAlternateTreeList*>(Dyn->Items[j]);
         AVNew = this->CreateAlternateClone(AView);
         DoFillAlternative( AVNew, AL);
         AView->ArrayChild->Append(AVNew);
      }
      for(int j = 0; j <= TFSView->ItemCount - 1; j++)
      {
        TFEView = TFSView->ItemTFE[j];
//        if (!TFEView->Fixed)
            {
               LI = AView->MainTreeList->FindTFE(TFEView->BaseShape);
               if (LI->MainNode)
               {
                  for(int k = 0; k <= LI->MainNode->ItemCount - 1; k++)
                  {
                    AL = LI->MainNode->AlternateItem[k];
                    if ( AL->MainAlternative ) break;
                    else AL = NULL;
                  }
                  if( AL )
                  {
                      AVNew =  this->CreateAlternateViewItem();
                      AVNew->MainTreeList = LI->MainNode;
                      TFEView->NextItem = AVNew;
                      AVNew->ParentTFE = TFEView;
                      DoCreate(AVNew);
                  }

               }
            }
       //    TFEView->Fixed = true;
         }

    }

    delete Dyn;
}


void TAlternateView::Fill()
{
   bool go = true;
   TAlternateViewItem *AVItem;
   TAlternateViewItem *AVChild;
   while(go)
   {
     go = false;
     for (int i = 0 ; i <= this->ItemCount - 1; i++)
     {
        AVItem = this->ItemView[i];
          for (int j = 0; j <= AVItem->ArrayChild->Count - 1; j++)
          {
             AVChild = static_cast<TAlternateViewItem*>(AVItem->ArrayChild->Items[j]);
             if (!AVChild->Fixed)
             {
               Fill2(AVItem, AVChild);
               go = true;
             }
          }
     }
  }
}


void TAlternateView::Fill2(TAlternateViewItem *AVMain, TAlternateViewItem *AVChild)
{
   TAlternateViewItemTFS* Tfs;
   TAlternateTreeList *AL;
   TAlternateViewItem *AVNew;
   TBaseWorkShape *WS = AVChild->WSEnd;
   TDynamicArray *Dyn = new TDynamicArray;
   int i;
   for (i = 0; i <= AVMain->ItemCount-1; i++)
   {
      Tfs = AVMain->ItemTFS[i];
      if (Tfs->BaseWorkShape == WS)
        break;
   }
   i++;
   for ( ; i <= AVMain->ItemCount-1; i++)
   {
      Tfs = AVMain->ItemTFS[i];
      AVChild->AddItemTFS(Tfs->BaseWorkShape);
      AVMain->MainTreeList->FindAlternate(Tfs->BaseWorkShape, Dyn);
      for (int j = 0 ; j <= Dyn->Count - 1; j++)
      {
         AL = static_cast<TAlternateTreeList*>(Dyn->Items[j]);
         AVNew = this->CreateAlternateClone(AVChild);
         AVNew->WSEnd = AL->NodeEnd->WorkShape;
         DoFillAlternative(AVNew, AL);
         AVMain->ArrayChild->Append(AVNew);
      }

   }
   AVChild->Fixed = true;
   delete Dyn;
}

*/
void TAlternateView::Load(TMainTreeList* ATreeList)
{
   TAlternateViewItem *AVItem;
   FreeList();
   AVItem = this->CreateAlternateViewItem();
   AVItem->MainTreeList = ATreeList;
   DoCreate(AVItem);
  // Fill();
}


bool TAlternateView::IsHaveChildShape(int AID)
{
   TAlternateViewItem* Item;
   for (int i = 0; i <= ItemCount - 1; i++)
   {
      Item = ItemView[i];
      if (Item->ParentTFE)
        if (Item->ParentTFE->BaseShape->ID == AID)
           return true;
   }
   return false;
}


