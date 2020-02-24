//---------------------------------------------------------------------------

#ifndef uPredicateTreeH
#define uPredicateTreeH
//---------------------------------------------------------------------------
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"
class TPredicateTreeItem
{
  private:
    int f_ParentID;
    int f_TypeWorkShape;
    int f_NumAlt;
    bool f_TReated;
    TBaseWorkShape* f_BaseWorkShape;
    TBaseShape* f_ParentShape;
    TDynamicArray *f_List;
    int __fastcall GetCount();
    int __fastcall GetTFE_ID(int AIndex);
    TBaseShape* __fastcall GetTFE(int AIndex);
  public:
    TPredicateTreeItem();
    ~TPredicateTreeItem();
    void AddBaseShape(TBaseShape *AShape, int AID);
    __property int ParentID = {read = f_ParentID, write = f_ParentID};
    __property TBaseWorkShape* BaseWorkShape = {read = f_BaseWorkShape, write = f_BaseWorkShape};
    __property TBaseShape* ParentShape = {read = f_ParentShape, write = f_ParentShape};
    __property int TypeWorkShape = {read = f_TypeWorkShape, write = f_TypeWorkShape};
    __property int Count = {read = GetCount};
    __property TBaseShape* TFE[int AIndex] = {read = GetTFE};
    __property int TFE_ID[int AIndex] = {read = GetTFE_ID};
    __property bool TReated = {read = f_TReated, write = f_TReated};
    __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};

};


class TPredicateTree
{
  private:
    TList *f_List;
    void FreeList();
    int __fastcall GetCount();
    TPredicateTreeItem* __fastcall GetItems(int AIndex);
  public:
    TPredicateTree();
    ~TPredicateTree();
    void Clear();
    TPredicateTreeItem* NewPredicateTreeItem();
    TPredicateTreeItem* FindByTfeID(int AID, TDynamicArray *Arr);
    TPredicateTreeItem* FindByParentID(int AID);
    void ArrayIDToDelete(TPredicateTreeItem* AItem, TDynamicArray *Arr);
    __property int Count = {read = GetCount};
    __property TPredicateTreeItem* Items[int AIndex] = {read = GetItems};

};


#endif
