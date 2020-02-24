//---------------------------------------------------------------------------

#ifndef uCompositeCheckConditionH
#define uCompositeCheckConditionH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeCheckCondition: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRect f_Rect1, f_Rect2;
     TDynamicArray *f_RCT[6];
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
     TRectLine *f_FirstRectLine;
     void CreateLines(TBaseWorkShape *AWS);
     int CalcBend(int t_x1, int t_x2);
     TBaseLine* GetIndexLine(int AIndex);
     void PrepareDrawFlags();
   protected:
     TPoint __fastcall GetEndPoint();
     TPoint __fastcall GetStartPoint();
     TBaseLine* __fastcall GetEndLine();
     TRectLine* __fastcall GetFirstLine();
   public:
     TCompositeCheckCondition();
     ~TCompositeCheckCondition();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};

#endif
