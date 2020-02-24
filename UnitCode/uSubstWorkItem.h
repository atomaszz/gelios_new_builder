//---------------------------------------------------------------------------

#ifndef uSubstWorkItemH
#define uSubstWorkItemH
#include "uBaseWorkShape.h"
//---------------------------------------------------------------------------
class TSubstWork;
class TSubstWorkItem
{
   private:
     int f_Type;
     TBaseShape* f_Shape;
     TSubstWork* f_SubstWork;
     TList *f_WorkLines;
     TPoint __fastcall GetStartPoint();
     TPoint __fastcall GetEndPoint();
     TBaseLine* __fastcall  GetWorkLine(int AIndex);
     int __fastcall GetWorkLineCount();

   public:
     TSubstWorkItem();
     ~TSubstWorkItem();
     void SetShape(TBaseShape* AShape);
     void SetSubstWork(TSubstWork* ASW);
     void Paint(TCanvas *ACanvas);
     void SetOffsetPosition(int Ax, int Ay);
     TRect GetRectSummary(TRect ARect);
     TRect GetAnyRect();
     bool IsContainShapeID(int AID);
     TSubstWork* FindSubstWork(TSubstWork* AfterWork);
     void OffsetEndCoordinate(TSubstWork* AfterWork);
     void AddWorkLine(TBaseLine *ALine);
     void ClearWorkLine();

     __property int  Type = {read = f_Type};
     __property TBaseShape* Shape = {read = f_Shape, write = f_Shape};
     __property TSubstWork* SubstWork = {read = f_SubstWork, write = f_SubstWork};
     __property TPoint StartPoint = {read = GetStartPoint};
     __property TPoint EndPoint = {read = GetEndPoint};
     __property TBaseLine*  WorkLine[int AIndex] = { read =  GetWorkLine};
     __property int  WorkLineCount = { read =  GetWorkLineCount};

};

#endif
