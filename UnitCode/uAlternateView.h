//---------------------------------------------------------------------------

#ifndef uAlternateViewH
#define uAlternateViewH
#include "uAlternateViewItem.h"


//---------------------------------------------------------------------------
class TAlternateTreeList;
class TAlternateView
{
   private:
     TList *f_List;
     void FreeList();
     int __fastcall GetItemCount();
     TAlternateViewItem* __fastcall GetItemView(int AIndex);
     void DoCreateItem(TAlternateViewItem *AVItem, TDynamicArray *AStack);
     void DoCreate(TAlternateViewItem *AVItem);
     void DoFillAlternative(TAlternateViewItem *AView, TAlternateTreeList *Alt);
     void DoFillChild(TAlternateViewItem *AVItem);
     void DoFillTFE(TAlternateViewItem *AVItem, TDynamicArray *AStack);
     TAlternateViewItem* CreateAlternateClone(TAlternateViewItem* ASource,
       TAlternateViewItem* AParent, TAlternateTreeList* AReplace);

     void Fill();
     void Fill2(TAlternateViewItem *AVMain, TAlternateViewItem *AVChild);

   public:
     TAlternateView();
     ~TAlternateView();
     TAlternateViewItem* CreateAlternateViewItem();
     TAlternateViewItem* CreateAlternateClone(TAlternateViewItem* ASource, TAlternateViewItem* AParent);
     void FillAlternate(TAlternateViewItem* AVI, TAlternateTreeList* ASource);
     void Load(TMainTreeList* ATreeList);
     bool IsHaveChildShape(int AID);
     void ClearAll();
     __property int ItemCount = {read = GetItemCount};
     __property TAlternateViewItem* ItemView[int AIndex] = {read = GetItemView};

};



#endif
