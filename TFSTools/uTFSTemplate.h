//---------------------------------------------------------------------------

#ifndef uTFSTemplateH
#define uTFSTemplateH
//---------------------------------------------------------------------------
#include "uFsTable.h"
#include "uCheckSuperPos.h"
#include "uTFSInnerPath.h"
class TTFSTemplate
{
  private:
    TList* FList;
    int GetCount() { return FList->Count; }
    TFsTableItem* GetItems(int AIndex);
  protected:
    TChecker* FOwner;
    TFsTableItem* FBegin;
    TFsTableItem* FEnd;
    TFsTableItemData *FRpsWork;
    void Rights(TFsTableItemData* AItem, TFsList* AList);
    void Lefts(TFsTableItemData* AItem, TFsList* AList);
    void AddItem(TFsTableItem* AItem) { FList->Add(AItem); }
  public:
    TTFSInnerPath* InnerPath1;
    TTFSInnerPath* InnerPath2;

    TTFSTemplate(TChecker* AOwner);
    virtual ~TTFSTemplate();
    virtual int Check(TFsTableItemData* Transit);
    TFsTableItem* BeginItem();
    TFsTableItem* EndItem();
    __property int Count = {read = GetCount};
    __property TFsTableItem* Items[int Aindex] = {read = GetItems};
    __property TFsTableItemData* RpsWork = {read = FRpsWork};

};

class TTFSReverse: public TTFSTemplate
{
  public:
    TTFSReverse(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

class TTFSReverseRO: public TTFSTemplate
{
  public:
    TTFSReverseRO(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

class TTFSBifurcation: public TTFSTemplate
{
  public:
    TTFSBifurcation(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

class TTFSParWork: public TTFSTemplate
{
  public:
    TTFSParWork(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

class TTFSPoslWork: public TTFSTemplate
{
  public:
    TTFSPoslWork(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

class TTFSSimpleWork: public TTFSTemplate
{
  public:
    TTFSSimpleWork(TChecker* AOwner): TTFSTemplate(AOwner){};
    virtual int Check(TFsTableItemData* Transit);
};

#endif
