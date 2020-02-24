//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uWork.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void TWork::Init()
{
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Shape;
   F_LastShapeId = F_NumberShapeId;
   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Shape = new TTfeRectShape(StartPoint.x + 2*F_Step, StartPoint.y, F_Step, F_LastShapeId);
   AddShape(Shape);
   CreateLines();
   CalcWidthWork();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;
}

//--------------------------------------------------------------------------
void TWork::CreateLines()
{
   TArrowLine *Line;
   TPoint P;
   TTfeRectShape *Shape;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;
   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape->GetTailPoint(0, P);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Shape->AddWorkLine(Line);

   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape->GetTailPoint(1, P);
   Line->xStart = P.x;
   Line->yStart = P.y;
   Line->xEnd = P.x + 2*F_Step;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Shape->AddWorkLine(Line);
}

//--------------------------------------------------------------------------
void TWork::Prepare()
{
   TArrowLine *Line;
   TPoint P;
   TTfeRectShape *Shape;
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape->GetTailPoint(0, P);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape->GetTailPoint(1, P);
   Line->xStart = P.x;
   Line->yStart = P.y;
   Line->xEnd = P.x + 2*F_Step;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TWork::Paint(TCanvas *Canvas)
{
    TBaseWorkShape::Paint(Canvas);
}

//-------------------------------------------------------------------------
TPoint __fastcall TWork::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//-------------------------------------------------------------------------
TRectLine* __fastcall TWork::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//-------------------------------------------------------------------------
TRectLine* __fastcall TWork::GetLastLine()
{
   TRectLine *Line;
   Line = static_cast<TRectLine*>(GetWorkLine(1));
   return Line;
}

//-------------------------------------------------------------------------
TBaseShape* TWork::GetShapeByLine(TRectLine* ALine, int APos)
{
   TRectLine *Line;
   Line = static_cast<TRectLine*>(GetWorkLine(0));
   if (Line == ALine)
   {
     if (APos < 2) return NULL;
     if (APos == 2)
        return GetWorkShape(0);
   }
   Line = static_cast<TRectLine*>(GetWorkLine(1));
   if (Line == ALine)
   {
     if (APos > 0) return NULL;
     if (APos == 0)
       return GetWorkShape(1);
   }
   return NULL;
}

bool TWork::MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor)
{
   TRectLine* Line;
   TBaseShape* Shape;
   Shape = static_cast<TBaseShape*>(GetWorkShape(0));
   if (Shape != AShape) return false;
   if (APos == 0)
   {
      Line = static_cast<TRectLine*>(GetWorkLine(0));
      Line->DrawFlagE = ACreate;
      Line->FlagEType = AType;
      Line->FlagEColor = AColor;
      Line->Prepare();
      return true;
   }
   if (APos == 1)
   {
      Line = static_cast<TRectLine*>(GetWorkLine(1));
      Line->DrawFlagS = ACreate;
      Line->FlagSType = AType;
      Line->FlagSColor = AColor;
      Line->Prepare();
      return true;
   }
   return false;

}

int __fastcall TWork::GetTypeShape()
{
   return 1;
}







