//---------------------------------------------------------------------------

#ifndef uTFSInnerPathH
#define uTFSInnerPathH
#include "uFsTable.h"
//---------------------------------------------------------------------------
class TTFSInnerPath
{
  private:
    TList* FList;
    int GetCount() { return FList->Count; }
    TFsTableItemData* GetItems(int AIndex);
    void FreeList();
  public:
    TTFSInnerPath() {  FList = new TList; }
    ~TTFSInnerPath() { FreeList(); delete FList; }
    void AddToPath(TFsTableItemData* AItem);
    bool Exists(TFsTableItemData* AItem);
    void CopyFrom(TTFSInnerPath *APath);
    __property int Count = {read = GetCount};
    __property TFsTableItemData* Items[int Aindex] = {read = GetItems};
};

#endif
