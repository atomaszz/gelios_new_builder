//---------------------------------------------------------------------------

#ifndef uCompositeCycleWhileDoH
#define uCompositeCycleWhileDoH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeCycleWhileDo: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRect f_Rect;
     TDynamicArray *f_RCT[5];
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
     TCompositeCycleWhileDo();
     ~TCompositeCycleWhileDo();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};
#endif
