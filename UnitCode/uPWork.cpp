//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPWork.h"
#include "uCompositeBaseWork.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

TPWork::TPWork(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id)
{
   F_Work1 = NULL;
   F_Work2 = NULL;
}


void __fastcall TPWork::ShapeCopy(TBaseShape *Shape, int Num_Shape)
{
   if (Num_Shape == 1 || Num_Shape == 0)
   {
     Shape->PenColor = clGreen;
     Shape->BrushColor = clYellow;
     Shape->PenWidth = 2;
     Shape->BrushStyle = bsSolid;

   }

}
/*
//---------------------------------------------------------------------------
void __fastcall TWork::LineCopy(TArrowLine *Line, int Num_Line)
{
   if (Num_Line == 0)
     Line->Width= 0;

}
*/

void TPWork::Init()
{
   TPoint P;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Shape;
   F_LastShapeId = F_NumberShapeId;
   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Shape = new TTfeRectShape(StartPoint.x + 2*F_Step, StartPoint.y, F_Step, F_LastShapeId);
   AddShape(Shape);
   F_LastShapeId++;
   Shape->GetTailPoint(1, P);

   Shape = NULL;
   Shape = new TTfeRectShape(P.x + 2*F_Step, StartPoint.y, F_Step, F_LastShapeId);
   AddShape(Shape);

   F_Work1 = NULL;
   F_Work2 = NULL;
   CreateLines();

}
//--------------------------------------------------------------------------
void TPWork::CreateLines()
{
   TArrowLine *Line;
   TPoint P, P2;
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

   Shape->GetTailPoint(1, P2);
   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Shape->GetTailPoint(0, P);
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);

   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Shape->GetTailPoint(1, P);
   Line->xStart = P.x;
   Line->yStart = P.y;
   Line->xEnd = P.x+ 2*F_Step;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
}

//--------------------------------------------------------------------------
void TPWork::Prepare()
{
   TArrowLine *Line;
   TPoint P, P2;
   TTfeRectShape *Shape;

   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape->GetTailPoint(0, P);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   Shape->GetTailPoint(1, P2);
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Shape->GetTailPoint(0, P);
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Shape = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Shape->GetTailPoint(1, P);
   Line->xStart = P.x;
   Line->yStart = P.y;
   Line->xEnd = P.x+ 2*F_Step;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TPWork::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}

//-----------------------------------------------------------------------
TPoint __fastcall TPWork::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//-----------------------------------------------------------------------------
bool TPWork::CanAlternate(int ID_Shape1, int ID_Shape2)
{
   TBaseShape *Shp1, *Shp2;
   bool res = false;
   Shp1 = GetWorkShape(0);
   Shp2 = GetWorkShape(1);
   if ((Shp1->ID == ID_Shape1) && (Shp2->ID == ID_Shape2)) res = true;
   if ((Shp1->ID == ID_Shape2) && (Shp2->ID == ID_Shape1)) res = true;
   return res;
}

//-----------------------------------------------------------------------------
TRectLine* __fastcall TPWork::GetFirstLine()
{
   TRectLine *Line;
   Line = static_cast<TRectLine*>(GetWorkLine(0));
   return Line;
}


//-----------------------------------------------------------------------------
TRectLine* __fastcall TPWork::GetLastLine()
{
   TRectLine *Line;
   Line = static_cast<TRectLine*>(GetWorkLine(2));
   return Line;
}


//-----------------------------------------------------------------------------
TRectLine* __fastcall TPWork::GetMiddleLine()
{
   TRectLine *Line;
   Line = static_cast<TRectLine*>(GetWorkLine(1));
   return Line;
}


//-----------------------------------------------------------------------------
TBaseShape* TPWork::GetShapeByLine(TRectLine* ALine, int APos)
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
     if (APos == 0) return GetWorkShape(0);
     if (APos == 1) return NULL;
     if (APos == 2) return GetWorkShape(1);
   }
   Line = static_cast<TRectLine*>(GetWorkLine(2));
   if (Line == ALine)
   {
     if (APos == 0) return GetWorkShape(1);
     if (APos > 0) return NULL;
   }
   return NULL;

}

//-----------------------------------------------------------------------------
bool TPWork::MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor)
{
   TRectLine* Line;
   TBaseShape* Shape;
   int n_shape = 0;
   Shape = static_cast<TBaseShape*>(GetWorkShape(0));
   if (Shape != AShape)
   {
      Shape = static_cast<TBaseShape*>(GetWorkShape(1));
      if (Shape != AShape) return false;
      n_shape = 1;
   }
   if (n_shape == 0)
   {
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
   }

   if (n_shape == 1)
   {
      if (APos == 0)
      {
        Line = static_cast<TRectLine*>(GetWorkLine(1));
        Line->DrawFlagE = ACreate;
        Line->FlagEType = AType;
        Line->FlagEColor = AColor;
        Line->Prepare();
        return true;
      }
      if (APos == 1)
      {
        Line = static_cast<TRectLine*>(GetWorkLine(2));
        Line->DrawFlagS = ACreate;
        Line->FlagSType = AType;
        Line->FlagSColor = AColor;
        Line->Prepare();
        return true;
      }
   }
   return false;
}



//-----------------------------------------------------------------------------
void TPWork::Decay(TWork **W1, TWork **W2, int a_lastLineId, int a_lastBlockId, int &a_retLastLineId)
{
   TPoint PS, PE;
   TBaseShape *N1;
   if (!F_Work1)
   {
      PS = StartPoint;
      F_Work1 = new TWork(PS.x, PS.y, F_Step, F_NumberShapeId, BlockId, F_NumberLineId);
      N1 = GetWorkNode(0);
      F_Work1->AddShape(N1);
      F_Work1->OnShapeCopy = OnShapeCopy;
      F_Work1->CreateLines();  //проблема
      F_Work1->Prepare(); // без Init()
      F_Work1->LEControl = LEControl;
      F_Work1->WndHandler = WndHandler;
      F_Work1->UnderControl = UnderControl;
   }
   if (!F_Work2)
   {
      PE = F_Work1->EndPoint;
      F_Work2 = new TWork(PE.x, PE.y, F_Step, F_LastShapeId, a_lastBlockId, a_lastLineId);
      N1 = GetWorkNode(1);
      F_Work2->AddShape(N1);
      F_Work2->OnShapeCopy = OnShapeCopy;
      F_Work2->CreateLines(); //проблема
      F_Work2->Prepare(); // без Init()
      F_Work2->LEControl = LEControl;
      F_Work2->WndHandler = WndHandler;
      F_Work2->UnderControl = UnderControl;
      a_retLastLineId = F_Work2->LastLineId;
   }

   FreeWorkLines();
   *W1 = F_Work1;
   *W2 = F_Work2;

}

