//---------------------------------------------------------------------------

#ifndef uCompositeControlFuncH
#define uCompositeControlFuncH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeControlFunc: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRect f_Rect1;
     int f_R1Width;
     TDynamicArray *f_RCT[6];
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
     TRectLine *f_FirstRectLine;
     void CreateLines(TBaseWorkShape *AWS);
     TBaseLine* GetIndexLine(int AIndex);
     void PrepareDrawFlags();
   protected:
     TPoint __fastcall GetEndPoint();
     TPoint __fastcall GetStartPoint();
     TBaseLine* __fastcall GetEndLine();
     TRectLine* __fastcall GetFirstLine();
   public:
     TCompositeControlFunc();
     ~TCompositeControlFunc();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};

#endif
