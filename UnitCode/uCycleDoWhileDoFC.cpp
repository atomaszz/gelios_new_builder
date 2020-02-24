//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCycleDoWhileDoFC.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void TCycleDoWhileDoFC::Init()
{
   TPoint P1, P2;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeEllShape *Ell;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 6*F_Step;
   P1.y = StartPoint.y - 6*F_Step;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId+1);
   AddShape(Rct);

   F_LastShapeId++;
   P1.y = StartPoint.y;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId-1);
   AddShape(Rct);


   Rct->GetTailPoint(1, P1);
   P1.x = P1.x + F_Step;
   P1.y = StartPoint.y;
   F_LastShapeId++;
   Ell = new TTfeEllShape(P1.x, P1.y, F_Step, F_LastShapeId);
   Ell->TailLeft = true;
   Ell->TailTop = true;
   Ell->TailRight = true;
   AddShape(Ell);

   CreateLines();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;

}

//--------------------------------------------------------------------------
void TCycleDoWhileDoFC::CreateLines()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2, VP;
   int tmp_x;
   TTfeRectShape *Rct, *Rct2;
   TTfeEllShape *Ell;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Rct = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Rct2 = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Ell = static_cast<TTfeEllShape*>(GetWorkShape(2));
   Rct2->GetTailPoint(0, P1);
   VP.x = P1.x - 4*F_Step;
   VP.y = P1.y;

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


   Rct->GetTailPoint(0, P1);
   F_LastLineId++;
   //2
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   AddLine(Line);


   Rct->GetTailPoint(1, P1);
   Ell->GetTailPoint(1, P2);
   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = 1;
   AddLine(Line);


   Rct2->GetTailPoint(0, P1);
   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   AddLine(Line);

   //5
   Rct2->GetTailPoint(1, P1);
   Ell->GetTailPoint(0, P2);

   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   AddLine(Line);

   //6
   Ell->GetTailPoint(2, P1);
   F_LastLineId++;
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 2*F_Step;
   Line->yEnd = P1.y;
   AddLine(Line);
}

//--------------------------------------------------------------------------
void TCycleDoWhileDoFC::Prepare()
{
   TArrowLine *Line, *Lnb, *Lnb3;
   TPoint P1, P2, VP;
   int tmp_x;
   TTfeRectShape *Rct, *Rct2;
   TTfeEllShape *Ell;


   Rct = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Rct2 = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Ell = static_cast<TTfeEllShape*>(GetWorkShape(2));
   Rct2->GetTailPoint(0, P1);
   VP.x = P1.x - 4*F_Step;
   VP.y = P1.y;
   //1
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = VP.x;
   Line->yEnd = VP.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;


   //2
   Rct->GetTailPoint(0, P1);
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   Line->Bend = 2;


   Rct->GetTailPoint(1, P1);
   Ell->GetTailPoint(1, P2);
   //3
   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = 1;

   Rct2->GetTailPoint(0, P1);
   //4
   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;

   Rct2->GetTailPoint(1, P1);
   Ell->GetTailPoint(0, P2);
   //5
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;


   //6
   Ell->GetTailPoint(2, P1);
   Line = static_cast<TArrowLine*>(GetWorkLine(5));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P1.x + 2*F_Step;
   Line->yEnd = P1.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TCycleDoWhileDoFC::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TCycleDoWhileDoFC::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}


//------------------------------------------------------------------------------
TPoint __fastcall TCycleDoWhileDoFC::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}


//------------------------------------------------------------------------------
TRectLine* __fastcall TCycleDoWhileDoFC::GetFirstLine()
{
   TRectLine *L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TCycleDoWhileDoFC::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(5));
   return L;
}


int __fastcall TCycleDoWhileDoFC::GetTypeShape()
{
   return 10;
}

