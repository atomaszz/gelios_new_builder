//---------------------------------------------------------------------------
#include "uTreeList.h"
#include "uDynamicArray.h"
#include "uAlternativeParser.h"
#include "uPredicateNumGenerator.h"
#include "uPredicatePath.h"

#ifndef uPredicateTFSConvertorH
#define uPredicateTFSConvertorH
//---------------------------------------------------------------------------
class TPredicateItemBig;
class TPredicateItemBase
{
  private:
    int f_ID;
    int f_NumAlt;
    bool f_Envelope;
    TPredicateItemBig* f_EnvelopeBIG;
  public:
    TPredicateItemBase();
    virtual ~TPredicateItemBase(){return;}
    virtual int Who() {return -1;}
    virtual void ListIDFill(TDynamicArray* AList);
    __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};
    __property bool Envelope = {read = f_Envelope, write = f_Envelope};
    __property int  ID = {read = f_ID, write = f_ID};
    __property TPredicateItemBig* EnvelopeBIG = {read = f_EnvelopeBIG, write = f_EnvelopeBIG};

};

class TPredicateItemTFE
{
   private:
     TTreeListItem* f_TFE;
     TPredicateItemBig* f_Big;
     TAlternativeParserItemTFE* f_RfcTFE;
   public:
     TPredicateItemTFE();
     ~TPredicateItemTFE();
     __property TTreeListItem* TFE = {read = f_TFE, write = f_TFE};
     __property TPredicateItemBig* Big = {read = f_Big, write = f_Big};
     __property TAlternativeParserItemTFE* RfcTFE = {read = f_RfcTFE, write = f_RfcTFE};

};


class TPredicateItemTFS: public TPredicateItemBase
{
    private:
      TTreeListTFS* f_TFS;
      TList* f_ListTFE;
      void FreeList();
      int __fastcall GetTFECount();
      TPredicateItemTFE* __fastcall GetTFEItems(int AIndex);
    public:
      TPredicateItemTFS();
      ~TPredicateItemTFS();
      int Who() {return 0;}
      void Assign(TAlternativeParserItemTFS *ATfs);
      void ListIDFill(TDynamicArray* AList);
      __property TTreeListTFS* TFS = {read = f_TFS};
      __property int TFECount = {read = GetTFECount};
      __property TPredicateItemTFE* TFEItems[int AIndex] = {read = GetTFEItems};

};

class TPredicateItemBig: public TPredicateItemBase
{
   private:
      bool f_Print;
      TList* f_List;
//      TPredicateItemTFE* f_OwnerTFE;
      TAlternativeParserItemBig* f_Rfc;
      int __fastcall GetCount();
      TPredicateItemBase* __fastcall GetItems(int AIndex);
      void FreeList();
   public:
     int Who() {return 1;}
     TPredicateItemBig();
     ~TPredicateItemBig();
     void AddItem(TPredicateItemBase *AItem);
     void DeleteItemToList(TPredicateItemBase* AItem);
     bool ValidDescendant();
     __property int Count = {read = GetCount};
     __property TPredicateItemBase* Items[int AIndex] = {read = GetItems};
//     __property TPredicateItemTFE* OwnerTFE = {read = f_OwnerTFE, write = f_OwnerTFE};
     __property TAlternativeParserItemBig* Rfc = {read = f_Rfc, write =  f_Rfc};
     __property bool Print = {read = f_Print, write = f_Print};
};

class TPredicateItemPWork: public TPredicateItemBase
{
    private:
      TPredicateItemBase* f_Item1;
      TPredicateItemBase* f_Item2;
    public:
      int Who() {return 2;}
      TPredicateItemPWork();
      ~TPredicateItemPWork();
      void ListIDFill(TDynamicArray* AList);
      __property TPredicateItemBase* Item1 = {read = f_Item1, write = f_Item1};
      __property TPredicateItemBase* Item2 = {read = f_Item2, write = f_Item2};
};


class TPredicateTFSConvertor
{
   private:
     TList *f_ListEnlarge;
     TPredicateNumGenerator* f_NGen;
     TPredicateItemBig* f_PredicateStart;
     TPredicatePathItem* f_BasePath;
     TPredicatePathItem* f_UsedPath;
     int f_PathStyle;
     bool f_TryPath;
     void FreeHead();
     TPredicateItemBig* NewBig(TAlternativeParserItemBig *ABig);
     void DoCopyTree(TPredicateItemBig *ABig, TDynamicArray*  AStack);
     void DoSetID();
     void DoSetIDItem(TPredicateItemBig* AHead, TDynamicArray *AStack);
     void DoSetIDItemTFS(TPredicateItemBase *ABase, TDynamicArray *AStack);
     void PushTFS(TPredicateItemTFS *ATFS, TDynamicArray *AStack);

     void DoProcess();
     void DoProcessItemTFS(TPredicateItemBase *ABase, TDynamicArray *AStack);
     void DoProcessItem(TPredicateItemBig* AHead, TDynamicArray *AStack);
     void SwapNumAlt(TPredicateItemBase *ADest, TPredicateItemBase *ASource);
     TPredicateItemBase* EnvelopeToBig(TPredicateItemBase *ASource);
     bool CheckEnlargeNum(TPredicateItemBig* ABig);
     TPredicatePathNode* FillPathNode(TPredicateItemBig* AHead, TPredicateItemBase* AItem);
     TPredicatePathNode* FillPathNode(TPredicateItemBig* AHead, TDynamicArray* ADyn);
     bool CheckPath(TPredicateItemBig* AHead, TPredicateItemBase* AItem);
     bool CheckPath(TPredicateItemBig* AHead, TDynamicArray* ADyn);
     void SetPathNode(TPredicateItemBig* AHead, TDynamicArray* ADyn);
     void ApplyStyle(TPredicateItemBig* AHead, TPredicateItemBase* AItem);
     void ApplyStyle(TPredicateItemBig* AHead, TDynamicArray* ADyn);
   public:
     TPredicateTFSConvertor();
     ~TPredicateTFSConvertor();
     void CopyTree(TAlternativeParserItemBig *AHead);
     void Process(TPredicatePathItem* ABase, TPredicatePathItem* AUsed);
     __property TPredicateItemBig* Head = {read = f_PredicateStart};
     __property int PathStyle = {read = f_PathStyle, write = f_PathStyle};
     __property bool TryPath = {read = f_TryPath};
};


/*
class TPredicateItemTFE;
class TPredicateItemPWork;
class TPredicateItemBase
{
    private:
      int f_ID;
      int f_Num;
      int f_NumParent;
      int f_Tail;
      bool f_OldRecalc;
      bool f_Envelope;
      TMainTreeList* f_MainTreeList;
      TAlternateTreeList* f_CurrAlternate;
    protected:
      virtual void __fastcall SetID(int AValue) { f_ID = AValue; }
      virtual int __fastcall GetMaxID() {return f_ID;}
    public:
      TPredicateItemBase(){ f_MainTreeList = NULL; f_ID = 0; f_Tail = 0; f_Envelope = false;
        f_CurrAlternate = NULL; f_Num = 0; f_NumParent = 0; f_OldRecalc = false;}
      virtual int Who(){return -1;}
      virtual ~TPredicateItemBase(){return;}
      virtual void ListIDFill(TDynamicArray* AList){return;}
      virtual void GetFullAddresItem(TDynamicArray* AList) {return;}
      __property int ID = {read = f_ID, write = SetID };
      __property TMainTreeList* MainTreeList = {read = f_MainTreeList, write= f_MainTreeList};
      __property int MaxID = {read = GetMaxID };
      __property TAlternateTreeList* CurrAlternate = {read = f_CurrAlternate, write = f_CurrAlternate};
      __property int Num = {read = f_Num, write = f_Num};
      __property int NumParent = {read = f_NumParent, write = f_NumParent};
      __property bool OldRecalc = {read = f_OldRecalc, write = f_OldRecalc};
      __property int Tail = {read = f_Tail, write = f_Tail};
      __property bool Envelope = {read = f_Envelope, write = f_Envelope};

};

class TPredicateItemTFS: public TPredicateItemBase
{
    private:
      int f_StartTFEID;
      TTreeListTFS* f_TFS;
      TList* f_ListTFE;
      void FreeList();
      int __fastcall GetCountTFE();
      TPredicateItemTFE* __fastcall GetTFE(int AIndex);
      void __fastcall SetTFS(TTreeListTFS* ATFS);
    protected:
      void __fastcall SetID(int AValue);
      int __fastcall GetMaxID();
    public:
      TPredicateItemTFS();
      ~TPredicateItemTFS();
      int Who() {return 0;}
      void ListIDFill(TDynamicArray* AList);
      void GetFullAddresItem(TDynamicArray* AList);

      __property TTreeListTFS* TFS = {read = f_TFS, write = SetTFS};
      __property int CountTFE = {read = GetCountTFE};
      __property TPredicateItemTFE* TFE[int AIndex] = {read = GetTFE};


};

class TPredicateItemBig: public TPredicateItemBase
{
   private:
      TList* f_List;
      TPredicateItemTFE* f_OwnerTFE;
      TPredicateItemPWork* f_OwnerPWork;
      int __fastcall GetCount();
      TPredicateItemBase* __fastcall GetItems(int AIndex);
      void FreeList();
   public:
     int Who() {return 1;}
     TPredicateItemBig();
     ~TPredicateItemBig();
     bool Find(TPredicateItemBase *AItem);
     void AddItem(TPredicateItemBase *AItem);
     void ClearList();
     void ClearListTFS();
     void DeleteItemToList(TPredicateItemBase* AItem);
     void ListIDFill(TDynamicArray* AList);
     void FullBigItem(TDynamicArray* AList);
     void GetFullAddresItem(TDynamicArray* AList);


     __property int Count = {read = GetCount};
     __property TPredicateItemBase* Items[int AIndex] = {read = GetItems};
     __property TPredicateItemTFE* OwnerTFE = {read = f_OwnerTFE, write = f_OwnerTFE};
     __property TPredicateItemPWork* OwnerPWork = {read =  f_OwnerPWork, write = f_OwnerPWork}; 

};

class TPredicateItemTFE
{
   private:
     int f_ID;
     TTreeListItem* f_TFE;
     TPredicateItemBig* f_Big;
   public:
     TPredicateItemTFE();
     ~TPredicateItemTFE();
     void GetFullAddresItem(TDynamicArray* AList);
     __property TTreeListItem* TFE = {read = f_TFE, write = f_TFE};
     __property TPredicateItemBig* Big = {read = f_Big, write = f_Big};
     __property int ID = {read = f_ID, write = f_ID };
};

class TPredicateItemPWork: public TPredicateItemBase
{
    private:
      TPredicateItemBase* f_Item1;
      TPredicateItemBase* f_Item2;
    protected:
      void __fastcall SetID(int AValue);
      int __fastcall GetMaxID();
    public:
      int Who() {return 2;}
      TPredicateItemPWork();
      ~TPredicateItemPWork();
      void GetFullAddresItem(TDynamicArray* AList);
      void ListIDFill(TDynamicArray* AList);
      __property TPredicateItemBase* Item1 = {read = f_Item1, write = f_Item1};
      __property TPredicateItemBase* Item2 = {read = f_Item2, write = f_Item2};
};


class TPredicatePreparedItem
{
   private:
     TAlternativeParserItemBase* f_ParserItem;
   public:
     TPredicatePreparedItem(){ f_ParserItem = NULL;}
     __property TAlternativeParserItemBase* ParserItem = { read =  f_ParserItem, write = f_ParserItem};


};


class TPredicateTFSConvertor
{
   private:
     TList *f_PeparedList;
     TAlternativeParser *f_Parser;
     TPredicateItemBig* f_PredicateStart;
     TPredicateNumGenerator* f_NumGenerator;
     TPredicateNumGenerator* f_NumGeneratorReverse;
     TDynamicArray *f_TFSList;
     void DoProcess();
     void DoProcessItem(TPredicateItemBig* AHead, TDynamicArray *AStack);
     void DoSetNumber();
     void DoSetNumberItem(TPredicateItemBig* AHead, TDynamicArray *AStack);
     void ClearPreparedList();
     void FillPreparedList();
     void DoAssignPWork(TPredicateItemPWork* APW, TPredicateItemBase* Item1, TPredicateItemBase* Item2);
     int __fastcall GetPreparedCount();
     TPredicatePreparedItem* __fastcall GetPreparedItems(int AIndex);
     void FreePredicateStart();
     void MakeTree(TMainTreeList* ATreeMain);
     void DoMake(TPredicateItemBig* ABig, TDynamicArray *AStack);
     void DoMakeItem(TPredicateItemBig* ABig, TDynamicArray *AStack);
     void CheckOldRecalc(TPredicateItemBase *AItem);
     TPredicateItemBase* DoFindPredicateFromTreeListTFS(TTreeListTFS* AIndex,
       TPredicateItemBig* ABig,  TDynamicArray *AStack);
     void DoProcessItemTFS(TPredicateItemBase *Base, TDynamicArray *AStack);
     AnsiString DoDebugInfoMake(TPredicateItemBig* ABig, TDynamicArray *AStack);
     void DebugInfoMake(AnsiString *AStr);
   public:
     TPredicateTFSConvertor();
     ~TPredicateTFSConvertor();
     void Parse(TMainTreeList* ATreeMain);
     TPredicateItemBase* FindPredicateFromTreeListTFS(TTreeListTFS* AIndex);
     __property int PreparedCount = {read = GetPreparedCount};
     __property TPredicatePreparedItem* PreparedItems[int AIndex] = {read = GetPreparedItems};
     __property TPredicateItemBig* PredicateStart = {read =  f_PredicateStart};

};
*/
#endif
