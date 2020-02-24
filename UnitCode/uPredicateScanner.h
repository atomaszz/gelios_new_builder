//---------------------------------------------------------------------------

#ifndef uPredicateScannerH
#define uPredicateScannerH
//---------------------------------------------------------------------------
class TPredicateScannerItemKnot
{
   private:
     int f_ParentID;
     int f_NumAlt;
     int f_TypeKnot;
     int f_TFE_ID1;
     int f_TFE_ID2;
     int f_TFE_ID3;
   public:
     TPredicateScannerItemKnot(){f_ParentID = f_NumAlt = f_TypeKnot = f_TFE_ID1 = f_TFE_ID2 = f_TFE_ID3 = 0 ;}
     AnsiString ItemName();
     __property int ParentID = {read = f_ParentID, write = f_ParentID};
     __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};
     __property int TypeKnot = {read = f_TypeKnot, write = f_TypeKnot};
     __property int TFE_ID1 = {read = f_TFE_ID1, write = f_TFE_ID1};
     __property int TFE_ID2 = {read = f_TFE_ID2, write = f_TFE_ID2};
     __property int TFE_ID3 = {read = f_TFE_ID3, write = f_TFE_ID3};
};

class TPredicateScanner
{
   private:
     bool f_Prop;
     char f_Simv[256];
     char f_Scan[256];
     char *f_Str;
     int  f_Pos;
     int  f_Len;
     TList *f_ListKnot;
     void FreeListKnot();
     void InitScanner(bool *AProp, ...);
     int ScanItem();
     bool IsContainChar(char AChar);
     bool Eof();
     int DoScanKnot();
     int ScanComment();
     int ScanPredicate();
     void IncPos(){f_Pos++;}
     int GetTypePredicate(char *AStr);
     int DoScanListID(int AType, int &AId1, int &AId2, int &AId3);
     int __fastcall GetCountKnot();
     TPredicateScannerItemKnot* __fastcall GetItemsKnot(int AIndex);
     TPredicateScannerItemKnot* CreateKnot();
   public:
     TPredicateScanner();
     ~TPredicateScanner();
     bool Scan(char *AStr);
     AnsiString Error;
     __property int CountKnot = {read = GetCountKnot};
     __property TPredicateScannerItemKnot* ItemsKnot[int AIndex] = {read = GetItemsKnot};
};

#endif
