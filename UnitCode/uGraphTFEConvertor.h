//---------------------------------------------------------------------------
#include "uTreeList.h"
#include "uDynamicArray.h"
#include "uPredicateTFSConvertor.h"
#include "uGlsAtmCommon.h"
#include "uPredicateTree.h"


#ifndef uGraphTFEConvertorH
#define uGraphTFEConvertorH
//---------------------------------------------------------------------------
class TGraphTFEConvertorTransNum;
class TGraphTFEConvertorItem
{
   private:
     AnsiString f_Out;
     TPredicateItemBase* f_Item;
     TPredicateItemBig* f_Parent;
     int __fastcall GetParentID();
     AnsiString __fastcall GetAlias();
     AnsiString ListIDFromTFE();
     void DoMake();
     TBaseShape* __fastcall GetParentBaseShape();
   public:
     TGraphTFEConvertorItem();
     void Make(TPredicateItemBase* AItem, TPredicateItemBig* AParent);
     void ListIDFromTFE(TDynamicArray* AL);
     __property AnsiString OutString = {read = f_Out};
     __property TPredicateItemBase* Item  = {read = f_Item};
     __property TPredicateItemBig* Parent = {read = f_Parent};
     __property int ParentID = {read = GetParentID};
     __property AnsiString Alias = {read = GetAlias };
     __property TBaseShape* ParentBaseShape = {read = GetParentBaseShape };
};



class TGraphTFEConvertor
{
   private:
     AnsiString f_PrStruct;
     AnsiString f_PrRab;
     AnsiString f_PrControlRab;
     AnsiString f_PrControlFunc;
     AnsiString f_PrCheckCondition;


     AnsiString f_TextRecalc;
     TGraphTFEConvertorItem* f_Item;
     TGlsBinaryTree* f_BTree;
     TGraphTFEConvertorTransNum* f_Tran;
     void PushTFS(TPredicateItemTFS *ATFS, TDynamicArray *AStack);
     void CheckParseItem(TPredicateItemBase *ABase, TDynamicArray *AStack);
     void PushBig(TPredicateItemBig *ABig, TDynamicArray *AStack);
     void PushPWork(TPredicateItemPWork *APWork, TDynamicArray *AStack);
     AnsiString PrintPWork(TPredicateItemPWork* APWork, TDynamicArray *AStack);
     AnsiString PrintBig(TPredicateItemBig* ABig, TDynamicArray *AStack);
     AnsiString ParseItem(TPredicateItemBase* ABase, TDynamicArray *AStack);

     TPredicateItemBase* DoParseItem(TPredicateItemBase* ABase, TDynamicArray *AStack);
     TPredicateItemPWork* DoPrintPWork(TPredicateItemPWork* APWork, TDynamicArray *AStack);
     TPredicateItemBig* DoPrintBig(TPredicateItemBig* ABig, TDynamicArray *AStack);
     void MakeElement(TPredicateItemBase* AElement);
     void MakeElementTFS(TPredicateItemTFS *ATFS);
     void AddElementToTree(TPredicateTree*  APredicateTree);
   public:
     TGraphTFEConvertor();
     ~TGraphTFEConvertor();
     void Init(TPredicateItemBig* AHead, TPredicateTree* APredicateTree);
     __property AnsiString PrStruct = {read = f_PrStruct};
     __property AnsiString TextRecalc = {read = f_TextRecalc};
     __property AnsiString PrRab = {read = f_PrRab};
     __property AnsiString PrControlRab = {read = f_PrControlRab};
     __property AnsiString PrControlFunc = {read = f_PrControlFunc};
     __property AnsiString PrCheckCondition = {read = f_PrCheckCondition};

};

void InitTFEConvertor();
void FreeTFEConvertor();


#endif

