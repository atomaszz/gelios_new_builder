//---------------------------------------------------------------------------

#ifndef uPredicateTrackCreatorH
#define uPredicateTrackCreatorH
#include "uPredicateScanner.h"
#include "uDynamicArray.h"
#include "uOgrSovmArray.h"
//---------------------------------------------------------------------------
class TPredicateTrackCreatorItem
{
   private:
     TList *f_List;
     int __fastcall GetCount();
     TPredicateScannerItemKnot* __fastcall GetItems(int AIndex);
     AnsiString __fastcall GetText();
   public:
     TPredicateTrackCreatorItem();
     ~TPredicateTrackCreatorItem();
     bool FindKnot(TPredicateScannerItemKnot* AKnot);
     void AddKnot(TPredicateScannerItemKnot* AKnot);
     void PushKnot(TPredicateScannerItemKnot* AKnot);
     void DeleteKnot(TPredicateScannerItemKnot* AKnot);
     void Clear(){f_List->Clear();}
     int CountKnotByParentID(int AID);
      void GetBadKnot(TDynamicArray *OutKnot);
     __property int Count = {read = GetCount};
     __property TPredicateScannerItemKnot* Items[int AIndex] = {read = GetItems};
     __property AnsiString Text = {read = GetText};

};

class TPredicateTrackCreator
{
   private:
     TList *f_List;
     TList *f_ListBase;
     TPredicateTrackCreatorItem* f_BaseTrack;
     int __fastcall GetCount();
     void FreeList();
     TPredicateTrackCreatorItem* __fastcall GetItems(int AIndex);
   public:
     TPredicateTrackCreator();
     ~TPredicateTrackCreator();
     void ClearTrack();
     void ClearBase();
     TPredicateScannerItemKnot* CreateKnotToBase();
     TPredicateTrackCreatorItem* CreateItem();
     TPredicateTrackCreatorItem* CloneItem(TPredicateTrackCreatorItem* ASource);
     void GetAllTrack(TPredicateTrackCreatorItem* AItem, TDynamicArray *OutTrack);
     void GetNegativeDecidedKnot(TPredicateTrackCreatorItem* AItem, TDynamicArray *OutKnot);
     void GenerateOptSovmTrack(TOgrSovmArray* AOgrSovm);

     __property int Count = {read = GetCount};
     __property TPredicateTrackCreatorItem* Items[int AIndex] = {read = GetItems};
     __property TPredicateTrackCreatorItem* BaseTrack = {read = f_BaseTrack};

};


#endif
