//---------------------------------------------------------------------------

#ifndef uSubstWorkH
#define uSubstWorkH
#include "uBaseWorkShape.h"
#include "uSubstWorkItem.h"
#include "uDynamicArray.h"

class TSubstWork
{
    private:
      TColor f_PenColor;
      TList* f_ListShapes;
      TList* f_ListLines;
      TBaseLine *f_FirstLine;
      TBaseLine *f_LastLine;
      TColor f_LineColor;

      TDynamicArray *f_FixColorArr;

      void FreeListShapes();
      void FreeListLines();
      TRect __fastcall GetMaxRect();
      TBaseShape* CloneShape(TBaseShape* ADest);
      TBaseLine*  CloneLine(TBaseLine* ADest);
      TSubstWorkItem* __fastcall GetSWItem(int AIndex);
      int __fastcall GetSWItemCount();
      void __fastcall SetStartPoint(TPoint AValue);

      int __fastcall GetStep();
      TPoint __fastcall  GetEndPoint();
      TPoint __fastcall  GetStartPoint();
      TPoint  RecalcStartPoint();
      TPoint  RecalcEndPoint();
      void __fastcall SetLineColor(TColor AValue);
      bool FindFixedColor(TBaseShape* ABaseShape);

     // TBaseShap
    public:
      TSubstWork();
      ~TSubstWork();
      void AddShape(TBaseWorkShape* ABaseWorkShape, bool IncFLine, bool IncLLine);
      TBaseShape* AddBaseShape(TBaseShape* ABaseShape, TBaseWorkShape* ABaseWorkShape);
      void AddShapeNoLines(TBaseWorkShape* ABaseWorkShape);
      void SetOffsetPosition(int Ax, int Ay);
      void Paint(TCanvas* ACanvas);
      bool FixedColor(TBaseShape* ABaseShape);
      TSubstWorkItem* FindItem(int ABaseShapeID, TSubstWork **AFind);
      TPoint CheckOffset(TBaseWorkShape* ABaseWorkShape);
      TRect GetRectSummary(TRect ARect);
      TRect GetAnyRect();
      TBaseShape* FindTFE(int Ax, int Ay);
      void OffsetEndCoordinate(TSubstWork* AfterWork);
      __property int Step = {read = GetStep};
      __property TColor  PenColor = {read = f_PenColor, write = f_PenColor};
      __property TRect MaxRect = {read = GetMaxRect};
      __property TSubstWorkItem* SWItems[int AIndex] = {read = GetSWItem};
      __property int SWItemCount = {read = GetSWItemCount};
      __property TPoint StartPoint = {read = GetStartPoint, write = SetStartPoint};
      __property TPoint EndPoint = {read = GetEndPoint};
      __property TBaseLine* FirstLine  = {read = f_FirstLine};
      __property TBaseLine* LastLine  = {read = f_LastLine};
      __property TColor LineColor = {read = f_LineColor, write = SetLineColor};

};
//---------------------------------------------------------------------------
#endif
