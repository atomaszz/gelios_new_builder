//---------------------------------------------------------------------------

#ifndef uLineCuttingH
#define uLineCuttingH
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"



//---------------------------------------------------------------------------
class TLineCuttingItem
{
   private:
     TPoint f_PStart;
     TPoint f_PEnd;
     bool f_Includet;
     int __fastcall GetType();
     int __fastcall GetXDln();
   public:
     TLineCuttingItem();
     __property int Type = {read = GetType};
     __property TPoint PointStart = {read = f_PStart, write  = f_PStart};
     __property TPoint PointEnd = {read = f_PEnd, write  = f_PEnd};
     __property bool Includet = {read = f_Includet, write = f_Includet};
     __property int XDln = {read = GetXDln};
};


class TLineCutting
{
   private:
     TColor f_PenColorWS;
     int    f_PenWidthWS;
     TPenStyle f_PenStyleWS;
     TPenMode f_PenModeWS;
     TColor f_FrameColorWS;
     TBrushStyle f_BrushStyleWS;
     bool f_DrawCaption;
     int f_BaseX, f_BaseY;
     int f_StartBaseX, f_StartBaseY;
     TList* f_PointList;
     TList* f_BaseLineList;
     TBaseWorkShape* f_WorkShape;
     TBaseWorkShape* f_NextWorkShape;
     TCanvas* f_Canvas;
     TRectLine* f_FirstLine;
     TRectLine* f_LastLine;
     bool f_IsFirstWS;
     bool f_IsLastWS;
     TDynamicArray *f_DLines;
     TDynamicArray *f_DShapes;

     void FreePointList();
     void FreeBaseLineList();
     void __fastcall SetWorkShape(TBaseWorkShape* AValue);
     void __fastcall SetNextWorkShape(TBaseWorkShape* AValue);
     void CreateImage();
     void CreateBaseLine();
     TLineCuttingItem* FindLine(TPoint APointStart, TPoint APointEnd);
     bool AddToPointList(TPoint APointStart, TPoint APointEnd);
     bool ComparePoint(TLineCuttingItem *A, TLineCuttingItem* B, TPoint &AStart, TPoint &AEnd);
     void ApplyOffset(int Ax, int Ay);
     void Paint(TCanvas *ACanvas);
   public:
     TLineCutting(TCanvas* ACanvas);
     ~TLineCutting();

     void BeginMoving(int Ax, int Ay);
     void Moving(int Ax, int Ay);
     void EndMoving(int &AxOfs, int &AyOfs);
     void ClearAll();

     __property TBaseWorkShape* WorkShape = {read = f_WorkShape, write  = SetWorkShape};
     __property TBaseWorkShape* NextWorkShape = {read = f_NextWorkShape, write  = SetNextWorkShape};
     __property bool IsFirstWS = {read = f_IsFirstWS, write = f_IsFirstWS};
     __property bool IsLastWS = {read = f_IsLastWS, write = f_IsLastWS};


};
#endif
