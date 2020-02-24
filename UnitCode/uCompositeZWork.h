//---------------------------------------------------------------------------

#ifndef uCompositeZWorkH
#define uCompositeZWorkH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uFreeRectLine.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
/*
class TCompositeZWork: public TCompositeBaseWork
{
   private:
     TFreeRectLine *f_Rct1;
     TFreeRectLine *f_Rct2;
     TFreeRectLine *f_Rct3;
     TFreeRectLine *f_Rct4;
     TFreeRectLine *f_Rct5;
     TFreeRectLine *f_Rct6;

     TDynamicArray *f_Arr;
     void RecalcWidthPos();
     void RecalcStartPosX();
     void RecalcStartPosY();
     void CreateLines();
     int ConvertRctToBL( int AIndex, TRectLine *ARct, int AStep, TColor AColor);
     int CalcBend(int t_x1, int t_x2);

   protected:
     void __fastcall SetTopBorder(int AValue);
     TPoint __fastcall GetEndPoint();
   public:
     TCompositeZWork();
     ~TCompositeZWork();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS);
     void Prepare();
     void Appearance();
};
 */

class TCompositeZWork: public TCompositeBaseWork
{
   private:
     TBaseWorkShape *f_BWS;
     TPoint f_E1, f_E2, VPoint;
     TRect f_Rect1, f_Rect2;
     TDynamicArray *f_RCT[6];
     TRectLine *f_FirstRectLine;
     TBaseLine *f_LineCent;
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
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
     TCompositeZWork();
     ~TCompositeZWork();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);
};

#endif
