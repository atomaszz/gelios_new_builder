#include "uBaseWorkShape.h"
#include "uDynamicArray.h"
#include "uOgrSovmArray.h"

//---------------------------------------------------------------------------
#ifndef uPredicatePathH
#define uPredicatePathH
//---------------------------------------------------------------------------
class TPredicateItemBase;
class TPredicatePathNode;
class TPredicatePathNodeItem
{
   friend TPredicatePathNode;
   private:
     int f_Index;
     int f_BlockID;
     TBaseWorkShape* f_TFS;
     TPredicateItemBase* f_ItemBase;
   public:
     TPredicatePathNodeItem(){f_Index = 0; f_BlockID = 0; f_ItemBase = NULL, f_TFS = NULL;}
     void SetIndex(int AIndex){f_Index = AIndex;}
     __property int Index = {read = f_Index};
     __property int BlockID = {read = f_BlockID, write = f_BlockID};
     __property TBaseWorkShape* TFS = {read = f_TFS , write = f_TFS};
     __property TPredicateItemBase* ItemBase = {read = f_ItemBase, write = f_ItemBase};
};

class TPredicatePathNode
{
   private:
     int f_MaxPermutation;
     int f_ID;
     int f_Cnt;
     int f_NumAlt;
     TList *f_List;
     TPredicateItemBase* f_ParentItemBase;
     void FreeList();
     int __fastcall GetCount();
     TPredicatePathNodeItem* __fastcall GetItems(int AIndex);
     AnsiString __fastcall GetText();
   public:
     TPredicatePathNode(TPredicateItemBase* AParentItemBase, int AID, int ANumAlt);
     ~TPredicatePathNode();
     TPredicatePathNodeItem* CreateItem();
     void AddItem(TPredicateItemBase* AItem);
     bool IsLike(TPredicatePathNode *ANode);
     TPredicatePathNodeItem* FindIndexFirst(int &APos);
     TPredicatePathNodeItem* FindIndexNext(int &APos);
     TPredicatePathNodeItem* FindByBlockID(int ABlockID);
     void Clear();
     void Assign(TPredicatePathNode *ASource);
     void SwapItem(TPredicatePathNodeItem* AItem1, TPredicatePathNodeItem* AItem2);
     __property int Count = {read = GetCount};
     __property TPredicatePathNodeItem* Items[int AIndex] = {read = GetItems};
     __property int ID = {read = f_ID, write = f_ID};
     __property AnsiString Text = {read = GetText};
     __property TPredicateItemBase* ParentItemBase = {read = f_ParentItemBase};
     __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};
     __property int MaxPermutation = {read = f_MaxPermutation, write = f_MaxPermutation};

};

class TPredicatePathItem
{
   private:
     TList *f_List;
     void FreeList();
     int __fastcall GetNodeCount();
     TPredicatePathNode* __fastcall GetNodeItems(int AIndex);
     AnsiString __fastcall GetText();
     TPredicatePathNodeItem* FindPathNodeByParent(TPredicateItemBase* AParent);
   public:
     TPredicatePathItem();
     ~TPredicatePathItem();
     void Clear();
     TPredicatePathNode* CreatePathNode(TPredicateItemBase* AParentItemBase);
     TPredicatePathNode* FindLikePathNode(TPredicatePathNode* ANode);
     TPredicatePathNode* LastPathNode();
     void Assign(TPredicatePathItem *ASource);
     __property int NodeCount = {read = GetNodeCount};
     __property TPredicatePathNode* NodeItems[int AIndex] = {read = GetNodeItems};
     __property AnsiString Text = {read = GetText};
};


class TPredicatePath
{
   private:
     double f_Rate;
     int f_Max;
     TList *f_ListDescendant;
     TPredicatePathItem* f_BasePath;
     TPredicatePathItem* f_CurrentPath;
     TPredicatePathItem* f_UsedPath;
     TPredicatePathItem* f_OptSovmPath;
     TOgrSovmArray* f_OgrSovm;
     void FreeListDescendant();
     TPredicatePathItem* InitDescendant();
     int __fastcall GetDescendantCount();
     TPredicatePathItem* __fastcall GetDescendantItems(int AIndex);
     void Swap(int *m, int i, int j);
     void Swap_Array(int *m, int i, int j);
     int Find_Min(int *m, int i, int N);
     void NextArray(int *m, int N);
     int Factorial(int N);
     void DoGenerateDescendant(TPredicatePathItem* AItem, TDynamicArray *AStack);
     bool CheckRnd();
     bool AddPredicatePathNodeFromBase(TPredicatePathItem* AItem);
     void CalcPermutationInPathNodes();
     void DoGenerateOptSovmPath(TPredicatePathNode* ANode);
   public:
     TPredicatePath();
     ~TPredicatePath();
     void Init();
     void GenerateDescendant(double ARate, int AMax);
     void ClearDescendant();
     void GenerateOptSovmPath(TOgrSovmArray* AOgrSovm);
     TPredicatePathItem* CloneToDescendant(TPredicatePathItem* ASource);
     __property TPredicatePathItem* BasePath = {read = f_BasePath};
     __property TPredicatePathItem* UsedPath = {read = f_UsedPath};
     __property TPredicatePathItem* OptSovmPath = {read = f_OptSovmPath};

     __property int DescendantCount = {read = GetDescendantCount};
     __property TPredicatePathItem* Descendants[int AIndex] = {read = GetDescendantItems};
};
#endif
