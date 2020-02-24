//---------------------------------------------------------------------------

#ifndef uCheckSuperPosH
#define uCheckSuperPosH
#include "uFsList.h"
#include "uFsTable.h"
#include "uToolConsts.h"
#include "uTFSInnerPath.h"
//---------------------------------------------------------------------------
class TCheckSuperPos;
class TLevelHeap
{
  private:
    TList *FList;
    void FreeList();
    int GetCount() { return FList->Count; }
    TFsTableItemData* GetItems(int AIndex);
  public:
    TLevelHeap() {FList = new TList;}
    ~TLevelHeap() {FreeList(); delete FList;}
    void Clear() {FreeList();}
    void Add(TFsTableItemData *AData);
    TFsTableItemData* Find(TFsTableItemData *AData);
    TFsTableItemData* Find2(int AType, int ANum);
    __property int Count = {read = GetCount};
    __property TFsTableItemData* Items[int Aindex] = {read = GetItems};
};

class TBigWork
{
  private:
    int FNum;
    int FTyp;
    int FLevel;
    TFsTableItem* FBegin;
    TFsTableItem* FEnd;
    TFsTableItemData *FRpsWork;
    TList *FList;
    int GetCount() { return FList->Count; }
    TFsTableItem* GetItems(int AIndex);
  public:
    TTFSInnerPath* InnerPath1;
    TTFSInnerPath* InnerPath2;

    TBigWork(int ANum, int ATyp)
    {
      FLevel = 0;
      FBegin = NULL;
      FEnd = NULL;
      FRpsWork = NULL;
      FNum = ANum;
      FTyp = ATyp;
      FList = new TList;
      InnerPath1 = new TTFSInnerPath;
      InnerPath2 = new TTFSInnerPath;
    }
    ~TBigWork(){delete FList; delete InnerPath1; delete InnerPath2;}
    void AddItem(TFsTableItem* AItem) {FList->Add(AItem);}
    TFsTableItem* FindItem(TFsTableItem* AItem);
    AnsiString ToString();
  //  bool NeedUpdateLevel() { return (InnerPath1->Count > 0) || (InnerPath2->Count > 0); }
    __property int Num = {read = FNum};
    __property int Typ = {read = FTyp};
    __property int Count = {read = GetCount};
    __property int Level = {read = FLevel, write = FLevel}; 
    __property TFsTableItem* Items[int Aindex] = {read = GetItems};
    __property TFsTableItem* BeginItem = {read = FBegin, write = FBegin};
    __property TFsTableItem* EndItem = {read = FEnd, write = FEnd};
    __property TFsTableItemData* RpsWork = {read = FRpsWork, write = FRpsWork};


};


class TChecker
{
   private:
     TCheckSuperPos* FOwner;
     TBigWork* FBigWork;
     TFsList* FList;
     TFsTableItem* ListFirst();
     TFsTableItem* ListNext();
     int GetCount() { return FList->Count; }
   public:
     TChecker(TCheckSuperPos* AOwner)
     {
       FOwner = AOwner;
       FBigWork = NULL;
       FList = new TFsList;
     }
     ~TChecker() {delete FList;}
     void Lefts(TFsTableItemData* ARight, TFsList* AItems);
     void Rights(TFsTableItemData* ALeft, TFsList* AItems);
     void AddItem(TFsTableItem* AItem) {FList->Add(AItem);}
     int Check();
     __property int Count = {read = GetCount};
     __property TBigWork* BigWork = {read = FBigWork};
};

class TCheckSuperPosItem
{
  private:
    TCheckSuperPos* FOwner;
    TList* FList;
    int GetCount() { return FList->Count; }
    TFsTableItem* GetItems(int AIndex);
  public:
    TCheckSuperPosItem(TCheckSuperPos* AOwner) { FOwner = AOwner; FList = new TList; }
    ~TCheckSuperPosItem() { delete FList; }
    void AddItem(TFsTableItem* AItem) {FList->Add(AItem);}
    void CopyListToChecker(TChecker* AChecker);
    void Build(TCheckSuperPosItem* ASource, TChecker* AChecker);
    AnsiString ToString();
    __property int Count = {read = GetCount};
    __property TFsTableItem* Items[int Aindex] = {read = GetItems};
};

class TCheckSuperPos
{
   private:
     int FBigCounter;
     int FLevelCounter;
     TList* FList;
     TList* FListAppend;
     TList* FListItem;
     TList* FListBigWork;
     TLevelHeap* FHeap;
     void FreeListItem();
     void FreeListAppend();
     void FreeListBigWork();
     void SetupLevel();

     int GetCountSuperPos() { return FListItem->Count; }
     TCheckSuperPosItem* GetItemsSuperPos(int AIndex);

     int GetCountBigWork() { return FListBigWork->Count; }
     TBigWork* GetItemsBigWork(int AIndex);
   public:
     TCheckSuperPos();
     ~TCheckSuperPos();
     TCheckSuperPosItem* CreateCheckSuperPosItem();
     TBigWork* CreateBigWork(int ATyp);
     void InitFromTable(TFsTable* ATable);
     void Append(TFsTableItem* AItem);
     bool Check();
     TFsTableItem* CreateAppendFsTableItem(TFsTableItemData ALeft,
       TFsTableItemData ARight);
     TBigWork* FindBigWork(int ANum);
     int NextLevel();

     __property TLevelHeap* LevelHeap = {read = FHeap};
     __property int CountSuperPos = {read = GetCountSuperPos};
	 __property TCheckSuperPosItem* ItemsSuperPos[int Aindex] = {read = GetItemsSuperPos};

     __property int CountBigWork = {read = GetCountBigWork};
	 __property TBigWork* ItemsBigWork[int Aindex] = {read = GetItemsBigWork};


};

#endif
