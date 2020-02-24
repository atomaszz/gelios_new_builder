//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCheckConditionCW.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TCheckConditionCW::Init()
{
   TPoint P1, P2;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 2*F_Step;
   P1.y = StartPoint.y;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Rhomb = new TTfeRhombShape(P1.x, P1.y, F_Step, F_LastShapeId+1);
   Rhomb->TailLeft = true;
   Rhomb->TailTop = true;
   Rhomb->TailRight = true;
   AddShape(Rhomb);

   Rhomb->GetTailPoint(1, P1);
   P1.x = P1.x + 4*F_Step;
   P1.y = P1.y - 2*F_Step;
   F_LastShapeId++;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId-1);
   AddShape(Rct);

   CreateLines();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;


//   CalcWidthWork();
}

//--------------------------------------------------------------------------
void TCheckConditionCW::CreateLines()
{
   TArrowLine *Line, *Lnb, *Lnb3;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Rhomb = static_cast<TTfeRhombShape*>(GetWorkShape(0));
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Rhomb->GetTailPoint(0, P1);
   F_LastLineId++;
   //1
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Lnb = Line;

   Rhomb->GetTailPoint(1, P1);
   Rct->GetTailPoint(0, P2);

   F_LastLineId++;
   //2
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   AddLine(Line);


   Rct->GetTailPoint(1, P1);
   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 4*F_Step;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Lnb3 = Line;

   Rhomb->GetTailPoint(2, P1);
   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = Lnb3->xEnd;
   Line->yEnd = Lnb3->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);


   //5
   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb3->xEnd;
   Line->yStart = Lnb3->yEnd;
   Line->xEnd = Lnb3->xEnd + 2*F_Step;
   Line->yEnd = Lnb3->yEnd;
   AddLine(Line);
}

//--------------------------------------------------------------------------
void TCheckConditionCW::Prepare()
{
   TArrowLine *Line, *Lnb, *Lnb3;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;

   Rhomb = static_cast<TTfeRhombShape*>(GetWorkShape(0));
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Rhomb->GetTailPoint(0, P1);
   //1
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;

   Rhomb->GetTailPoint(1, P1);
   Rct->GetTailPoint(0, P2);

   //2
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;

   Rct->GetTailPoint(1, P1);
   //3
   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 4*F_Step;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb3 = Line;

   Rhomb->GetTailPoint(2, P1);
   //4
   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = Lnb3->xEnd;
   Line->yEnd = Lnb3->yEnd;

   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = Lnb3->xEnd;
   Line->yStart = Lnb3->yEnd;
   Line->xEnd = Lnb3->xEnd + 2*F_Step;
   Line->yEnd = Lnb3->yEnd;



   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TCheckConditionCW::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TCheckConditionCW::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}


//------------------------------------------------------------------------------
TPoint __fastcall TCheckConditionCW::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//------------------------------------------------------------------------------
bool TCheckConditionCW::CanAlternate(int ID_Shape1, int ID_Shape2)
{
   TBaseShape *Shp1, *Shp2, *Shp3;
   bool res = false;
   Shp1 = GetWorkShape(0);
   Shp2 = GetWorkShape(1);
   Shp3 = GetWorkShape(2);
   if ((Shp1->ID == ID_Shape1) && (Shp2->ID == ID_Shape2)) res = true;
   if ((Shp1->ID == ID_Shape2) && (Shp2->ID == ID_Shape1)) res = true;

   if ((Shp1->ID == ID_Shape1) && (Shp3->ID == ID_Shape2)) res = true;
   if ((Shp1->ID == ID_Shape2) && (Shp3->ID == ID_Shape1)) res = true;
   return res;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCheckConditionCW::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCheckConditionCW::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(4));
   return L;
}


int __fastcall TCheckConditionCW::GetTypeShape()
{
   return 7;
}




