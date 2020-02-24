//---------------------------------------------------------------------------

#ifndef uCompositeBifurcationH
#define uCompositeBifurcationH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeBifurcation: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TRect f_Rect1, f_Rect2;
     TRectLine *f_FirstRectLine;
     TDynamicArray *f_RCT[6];
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
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
     TCompositeBifurcation();
     ~TCompositeBifurcation();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};

#endif
