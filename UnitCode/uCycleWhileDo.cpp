//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCycleWhileDo.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TCycleWhileDo::Init()
{
   TPoint P1, P2;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 6*F_Step;
   P1.y = StartPoint.y - 6*F_Step;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId);
   AddShape(Rct);

   Rct->GetTailPoint(1, P1);
   P1.x = P1.x + F_Step;
   P1.y = StartPoint.y;
   F_LastShapeId++;
   Rhomb = new TTfeRhombShape(P1.x, P1.y, F_Step, F_LastShapeId);
   Rhomb->TailLeft = true;
   Rhomb->TailTop = true;
   Rhomb->TailRight = true;
   AddShape(Rhomb);


   CreateLines();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;

//   CalcWidthWork();
}

//--------------------------------------------------------------------------
void TCycleWhileDo::CreateLines()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2, VP;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Rct = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Rhomb = static_cast<TTfeRhombShape*>(GetWorkShape(1));
   Rct->GetTailPoint(0, P1);
   Rhomb->GetTailPoint(0, P2);
   VP.x = P1.x - 4*F_Step;
   VP.y = P2.y;

   F_LastLineId++;
   //1
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = VP.x;
   Line->yEnd = VP.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Lnb = Line;


   F_LastLineId++;
   //2
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   Line->Bend = 2;
   AddLine(Line);


   Rct->GetTailPoint(1, P1);
   Rhomb->GetTailPoint(1, P2);
   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = 1;
   //Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);

   Rhomb->GetTailPoint(0, P1);
   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   //Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);


   //5
   Rhomb->GetTailPoint(2, P1);
   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 2*F_Step;
   Line->yEnd = P1.y;
   AddLine(Line);


}

//--------------------------------------------------------------------------
void TCycleWhileDo::Prepare()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2, VP;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;


   Rct = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Rhomb = static_cast<TTfeRhombShape*>(GetWorkShape(1));
   Rct->GetTailPoint(0, P1);
   Rhomb->GetTailPoint(0, P2);
   VP.x = P1.x - 4*F_Step;
   VP.y = P2.y;


   //1
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = VP.x;
   Line->yEnd = VP.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;


   //2
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
  // Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Line->Bend = 2;


   Rct->GetTailPoint(1, P1);
   Rhomb->GetTailPoint(1, P2);
   //3
   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = 1;
//   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   Rhomb->GetTailPoint(0, P1);
   //4
   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = P1.x ;
   Line->yStart = P1.y ;
   Line->xEnd = Lnb->xEnd;
   Line->yEnd = Lnb->yEnd;
 //  Line->Bend = CalcBend(Line->xStart, Line->xEnd);


   //5
   Rhomb->GetTailPoint(2, P1);
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 2*F_Step;
   Line->yEnd = P1.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TCycleWhileDo::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TCycleWhileDo::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}


//------------------------------------------------------------------------------
TPoint __fastcall TCycleWhileDo::GetEndPoint()
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
TRectLine* __fastcall TCycleWhileDo::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCycleWhileDo::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(4));
   return L;
}


int __fastcall TCycleWhileDo::GetTypeShape()
{
   return 8;
}





