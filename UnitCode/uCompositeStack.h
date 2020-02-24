//---------------------------------------------------------------------------

#ifndef uCompositeStackH
#define uCompositeStackH
#include "uAlternateViewItem.h"
//---------------------------------------------------------------------------
class TCompositeStackItem
{
    private:
      TList* f_List;
      int f_IDShape;
      TAlternateViewItemTFS* __fastcall GetTFSItems(int AIndex);
      int __fastcall GetTFSCount();

    public:
      TCompositeStackItem(int AIDShape);
      ~TCompositeStackItem();
      void AddTFS(TAlternateViewItemTFS* AItem);
      __property int IDShape = {read = f_IDShape};
      __property int TFSCount = {read = GetTFSCount};
      __property TAlternateViewItemTFS* TFSItems[int AIndex] = {read = GetTFSItems};

};

class TCompositeStack
{
   private:
     TList* f_ListBase;
     TList* f_ListN;
     void FreeListN();
     TAlternateViewItemTFS* __fastcall GetBaseItems(int AIndex);
     int __fastcall GetBaseCount();
     TCompositeStackItem* __fastcall GetSTIItems(int AIndex);
     int __fastcall GetSTICount();
   public:
     TCompositeStack();
     ~TCompositeStack();
     void AddBaseWork(TAlternateViewItemTFS* ABW);
     TCompositeStackItem* CreateItem(int AID);
     void Pop();
     bool IsEmpty();
      __property int BaseCount = {read = GetBaseCount};
      __property TAlternateViewItemTFS* BaseItems[int AIndex] = {read = GetBaseItems};
      __property int STICount = {read = GetSTICount};
      __property TCompositeStackItem* STIItems[int AIndex] = {read = GetSTIItems};

};

#endif
