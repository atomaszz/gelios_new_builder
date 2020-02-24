//---------------------------------------------------------------------------

#ifndef uCompositeStack2H
#define uCompositeStack2H
//---------------------------------------------------------------------------
#include "uAlternateViewItem.h"


class TCompositeBaseWork;
class TCompositeBaseWorkItem;
class TCompositeStackItem2
{
    private:
      TList* f_List;
      TCompositeBaseWork *f_CompositeWork;
      TCompositeBaseWorkItem *f_CompositeWorkItem;
      TAlternateViewItemTFS* __fastcall GetTFSItems(int AIndex);
      int __fastcall GetTFSCount();

    public:
      TCompositeStackItem2(TCompositeBaseWorkItem* ACompositeWorkItem, TCompositeBaseWork* ACompositeWork);
      ~TCompositeStackItem2();
      void AddTFS(TAlternateViewItemTFS* AItem);
      __property TCompositeBaseWork *CompositeWork = {read = f_CompositeWork};
      __property TCompositeBaseWorkItem *CompositeWorkItem = {read = f_CompositeWorkItem};
      __property TAlternateViewItemTFS* TFSItems[int AIndex] = {read = GetTFSItems};
      __property int TFSCount = {read = GetTFSCount};
};


class TCompositeStack2
{
   private:
     TList* f_ListN;
     void FreeListN();
     TCompositeStackItem2* __fastcall GetSTIItems(int AIndex);
     int __fastcall GetSTICount();
   public:
     TCompositeStack2();
     ~TCompositeStack2();
     TCompositeStackItem2* CreateItem(TCompositeBaseWorkItem* ACompositeWorkItem, TCompositeBaseWork* ACompositeWork);
     void Pop();
     bool IsEmpty();
     TCompositeStackItem2* Last();
      __property int STICount = {read = GetSTICount};
      __property TCompositeStackItem2* STIItems[int AIndex] = {read = GetSTIItems};

};


#endif
