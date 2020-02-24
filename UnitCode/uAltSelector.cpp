//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAltSelector.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TAltSelectorItem::TAltSelectorItem(int AID, int ANum, int AParentShapeID)
{
   f_Num = ANum;
   f_ID = AID;
   f_ParentShapeID = AParentShapeID;
}

/*
class TAltSelector
{
   private:
     TList* f_List;
     void FreeList();
   public:
     TAltSelector();
     ~TAltSelector();

};*/

TAltSelector::TAltSelector()
{
   f_List = new TList;
   f_FinderList = new TList;
   f_pos = 0;
   f_Id = 0;
}


TAltSelector::~TAltSelector()
{
   FreeList();
   delete f_List;
   delete f_FinderList;
}

void TAltSelector::FreeList()
{
   TAltSelectorItem* Item;
   for (int  i = f_List->Count -  1; i>=0; i--)
   {
     Item = static_cast<TAltSelectorItem*>(f_List->Items[i]);
     delete Item;
     Item = NULL;
     f_List->Delete(i);
   }
}



int TAltSelector::AddAltItem(int AID)
{
   TAltSelectorItem* Item;
   int m_parentId = 0;
   int m_max = 0;
   bool m_ex = false;
   if (!AID) return 0;// первая альтернатива особенная
   for (int  i = f_List->Count -  1; i>=0; i--)
   {
     Item = static_cast<TAltSelectorItem*>(f_List->Items[i]);
     if (Item->ID == AID)
     {
       m_ex = true;
       m_parentId = Item->ParentShapeID;
       if(m_max < Item->Num)
         m_max = Item->Num;
     }
   }
   if (m_ex)
   {
     m_max++;
     Item = new TAltSelectorItem(AID, m_max, m_parentId);
     f_List->Add(Item);
     return m_max;
   }
   return -1;
}


bool TAltSelector::DeleteAltItem(int AID, int ANum)
{
   TAltSelectorItem* Item;
   for (int  i = f_List->Count -  1; i>=0; i--)
   {
     Item = static_cast<TAltSelectorItem*>(f_List->Items[i]);
     if ( (Item->ID == AID) && (Item->Num == ANum) )
     {
       delete Item;
       Item = NULL;
       f_List->Delete(i);
       return true;
     }
   }
   return false;
}


TAltSelectorItem* TAltSelector::FindFirst(int AID, int AParentShapeID)
{
   TAltSelectorItem* Item;
   f_FinderList->Clear();
   f_pos = 0;
   for (int  i = 0; i <= f_List->Count -  1; i++)
   {
      Item = static_cast<TAltSelectorItem*>(f_List->Items[i]);
      if ( (Item->ID == AID) && (Item->ParentShapeID == AParentShapeID))
         f_FinderList->Add(Item);
   }
   if (f_FinderList->Count > 0)
     return  static_cast<TAltSelectorItem*>(f_FinderList->Items[f_pos]);
   return NULL;
}

TAltSelectorItem* TAltSelector::FindNext()
{
   f_pos++;
   if (f_pos > f_FinderList->Count - 1) return NULL;
   return  static_cast<TAltSelectorItem*>(f_FinderList->Items[f_pos]);
}

TAltSelectorItem* TAltSelector::CreateNewAlternateID(int AParentShapeID, int AStartNum)
{
   TAltSelectorItem* Item;
   Item = new TAltSelectorItem(f_Id, AStartNum, AParentShapeID);
   f_List->Add(Item);
   f_Id++; // первая альтернатива это особенная
   return Item;
}

TAltSelectorItem* TAltSelector::CreateNewAlternateID2(int AID,  int AParentShapeID, int ANum)
{
   TAltSelectorItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item  = static_cast<TAltSelectorItem*>(f_List->Items[i]);
      if ( (Item->ID == AID) && (Item->Num == ANum))
        return NULL;
   }
   Item = new TAltSelectorItem(AID, ANum, AParentShapeID);
   f_List->Add(Item);
   f_Id = AID;
   f_Id++;
   return Item;
}



void TAltSelector::ClearAll()
{
   FreeList();
   f_FinderList->Clear();
   f_pos = 0;
   f_Id = 0;
}







