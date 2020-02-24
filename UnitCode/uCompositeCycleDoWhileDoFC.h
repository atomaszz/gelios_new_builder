//---------------------------------------------------------------------------

#ifndef uCompositeCycleDoWhileDoFCH
#define uCompositeCycleDoWhileDoFCH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeCycleDoWhileDoFC: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRect f_Rect1, f_Rect2;
     TDynamicArray *f_RCT[6];
     TRectLine *f_FirstRectLine;
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
     TCompositeCycleDoWhileDoFC();
     ~TCompositeCycleDoWhileDoFC();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};
#endif
