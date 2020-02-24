//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCheckCondition.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TCheckCondition::Init()
{
   TPoint P1, P2;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeHexahedronShape *Hexa;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 2*F_Step;
   P1.y = StartPoint.y;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Hexa = new TTfeHexahedronShape(P1.x, P1.y, F_Step, F_LastShapeId+2);
   Hexa->TailLeft = true;
   Hexa->TailTop = true;
   Hexa->TailBottom = true;
   AddShape(Hexa);

   Hexa->GetTailPoint(1, P1);
   P1.x = P1.x + 4*F_Step;
   P1.y = P1.y - 2*F_Step;
   F_LastShapeId++;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId-1);
   AddShape(Rct);

   Hexa->GetTailPoint(3, P1);
   P1.x = P1.x + 4*F_Step;
   P1.y = P1.y + 2*F_Step;
   F_LastShapeId++;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId-1);
   AddShape(Rct);
   CreateLines();
   CalcWidthWork();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;
}

//--------------------------------------------------------------------------
void TCheckCondition::CreateLines()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeHexahedronShape *Hexa;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Hexa = static_cast<TTfeHexahedronShape*>(GetWorkShape(0));
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Hexa->GetTailPoint(0, P1);
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

   Hexa->GetTailPoint(1, P1);
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
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(2));
   Rct->GetTailPoint(1, P2);

   tmp_x = P1.x;
   if (tmp_x < P2.x ) tmp_x = P2.x;
   tmp_x = tmp_x + 3*F_Step;

   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   AddLine(Line);

   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   AddLine(Line);

   Hexa->GetTailPoint(3, P1);
   Rct->GetTailPoint(0, P2);
   F_LastLineId++;
   //5
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   AddLine(Line);

   F_LastLineId++;
   //6
   Lnb = static_cast<TArrowLine*>(GetWorkLine(2));
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->PointStart = Lnb->PointEnd;
   Line->xEnd = Lnb->PointEnd.x + 2*F_Step;
   Line->yEnd = Lnb->PointEnd.y;
   AddLine(Line);
}

//--------------------------------------------------------------------------
void TCheckCondition::Prepare()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeHexahedronShape *Hexa;

   Hexa = static_cast<TTfeHexahedronShape*>(GetWorkShape(0));
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Hexa->GetTailPoint(0, P1);
   //1
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;

   Hexa->GetTailPoint(1, P1);
   Rct->GetTailPoint(0, P2);

   //2
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;

   Rct->GetTailPoint(1, P1);
   Rct = static_cast<TTfeRectShape*>(GetWorkShape(2));
   Rct->GetTailPoint(1, P2);

   tmp_x = P1.x;
   if (tmp_x < P2.x ) tmp_x = P2.x;
   tmp_x = tmp_x + 3*F_Step;

   //3
   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);


   //4
   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   Rct = static_cast<TTfeRectShape*>(GetWorkShape(2));
   Hexa->GetTailPoint(3, P1);
   Rct->GetTailPoint(0, P2);
   //5
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;

   //6
   Lnb = static_cast<TArrowLine*>(GetWorkLine(2));

   Line = static_cast<TArrowLine*>(GetWorkLine(5));
   Line->PointStart =   Lnb->PointEnd;
   Line->xEnd = Lnb->PointEnd.x + 2*F_Step;
   Line->yEnd = Lnb->PointEnd.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TCheckCondition::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TCheckCondition::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}



//------------------------------------------------------------------------------
TPoint __fastcall TCheckCondition::GetEndPoint()
{
/*   TArrowLine *L;
   L = (TArrowLine *)GetWorkLine(2);
   return L->PointEnd;
   */
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCheckCondition::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCheckCondition::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(5));
   return L;
}


int __fastcall TCheckCondition::GetTypeShape()
{
   return 11;
}


