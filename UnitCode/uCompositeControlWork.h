//---------------------------------------------------------------------------

#ifndef uCompositeControlWorkH
#define uCompositeControlWorkH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------

class TCompositeControlWork: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRectLine *f_FirstRectLine;
     TRect f_Rect1;
     int f_R1Width;
     TDynamicArray *f_RCT[6];
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
     void CreateLines(TBaseWorkShape *AWS);
     TBaseLine* GetIndexLine(int AIndex);
     void PrepareDrawFlags();
   protected:
     TPoint __fastcall GetEndPoint();
     TPoint __fastcall GetStartPoint();
     TBaseLine* __fastcall GetEndLine();
     TRectLine* __fastcall GetFirstLine();
   public:
     TCompositeControlWork();
     ~TCompositeControlWork();
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
    

};

#endif
