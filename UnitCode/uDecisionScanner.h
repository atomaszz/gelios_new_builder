//---------------------------------------------------------------------------

#ifndef uDecisionScannerH
#define uDecisionScannerH

#include "uBaseShape.h"
#include "uBaseWorkShape.h"
#include "uParamAlternativeItem.h"

//---------------------------------------------------------------------------
class TDecisionScannerItemTFE
{
   private:
     TBaseShape *f_TFE;
     TParamAlternativeItem* f_Alternative;
   public:
     TDecisionScannerItemTFE() {f_TFE = NULL; f_Alternative = NULL;}
     __property TBaseShape* TFE = {read = f_TFE, write = f_TFE};
     __property TParamAlternativeItem* Alternative = {read = f_Alternative, write = f_Alternative};
};


class TDecisionScannerItemTFS
{
  private:
    TList *f_List;
    TBaseWorkShape *f_TFS;
    int __fastcall GetTFECount() {return f_List->Count;}
    TDecisionScannerItemTFE* __fastcall GetTFEItem(int AIndex);
  public:
    TDecisionScannerItemTFS();
    ~TDecisionScannerItemTFS();
    TDecisionScannerItemTFE* CreateTFE();
    int GetMinShapeID();
    __property TBaseWorkShape* TFS = {read = f_TFS, write = f_TFS};
     __property TDecisionScannerItemTFE*  TFEItem[int AIndex] = { read =  GetTFEItem};
     __property int TFECount = {read = GetTFECount};
};

class TDecisionScanner
{
  private:
    TList *f_List;
    void FreeList();
    void ScanTFE(char* AStr);
    void LoadTFE(int ATfeID, int AParamAltId);
    TDecisionScannerItemTFS* FindTFS(TBaseWorkShape* );
    int __fastcall GetTFSCount() {return f_List->Count;}
    TDecisionScannerItemTFS* __fastcall GetTFS(int AIndex);
  public:
    TDecisionScanner();
    ~TDecisionScanner();
    void Scan(char* AStr);
    __property TDecisionScannerItemTFS*  TFS[int AIndex] = { read =  GetTFS};
    __property int TFSCount = {read = GetTFSCount};

};

#endif
