//---------------------------------------------------------------------------

#ifndef uPredicatePathScannerH
#define uPredicatePathScannerH
#include "uPredicatePath.h"
//---------------------------------------------------------------------------
class TPredicatePathScanner
{
   private:
     bool f_Prop;
     char f_Simv[256];
     char f_Scan[256];
     char *f_Str;
     int  f_Pos;
     int  f_Len;
     TPredicatePathItem *f_Dest;
     void InitScanner(bool *AProp, ...);
     int ScanItem();
     bool IsContainChar(char AChar);
     bool Eof();
     int DoScanKnot();
     int ScanComment();
     int DoScanBranch();
     int ScanBranch();
     void IncPos(){f_Pos++;}
     char LastScanChar();
   public:
     bool Scan(char *AStr, TPredicatePathItem *ADest);
     AnsiString Error;

};

#endif
