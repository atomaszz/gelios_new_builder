//---------------------------------------------------------------------------

#ifndef uCompositeZWorkORH
#define uCompositeZWorkORH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
class TCompositeZWorkOR: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TPoint f_E1, f_E2, VPoint;
     TRect f_Rect1, f_Rect2;
     TDynamicArray *f_RCT[6];
     TRectLine *f_FirstRectLine;
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
     TBaseLine *f_LineCent;
     TBaseLine *f_V1, *f_V2;
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
     TCompositeZWorkOR();
     ~TCompositeZWorkOR();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};

#endif
