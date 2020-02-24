//---------------------------------------------------------------------------

#ifndef uFsTableH
#define uFsTableH
//---------------------------------------------------------------------------

struct TFsTableItemData
{
  int Type;
  int Num;
  int Level;
  bool IsTrans();
  bool IsRo();
  bool IsFunc();
  bool IsDiag();
  bool IsFin();
  bool IsStart();
  bool IsBigWork();
  TFsTableItemData() {Level = 0;}
};

class TFsTableItem
{
  public:
    TFsTableItemData *Left;
    TFsTableItemData *Right;
    TFsTableItem();
    ~TFsTableItem();
    bool IsFirst();
    bool IsLast();
    AnsiString ToString();

};

class TFsTable
{
  private:
    TList *FList;
    void FreeList();
    int GetCount() { return FList->Count; }
    TFsTableItem* GetItems(int AIndex);
  public:
    TFsTable();
    ~TFsTable();
    void AddItem(TFsTableItemData ALeft, TFsTableItemData ARight);
    inline void Clear() { FreeList(); }
    TFsTableItem* FindFirst();
    __property int Count = {read = GetCount};
    __property TFsTableItem* Items[int AIndex] = {read = GetItems};

};

bool IsEqualFsItem(TFsTableItemData *A, TFsTableItemData *B)
{
  return (A->Type == B->Type) && (A->Num == B->Num);
}

#endif
