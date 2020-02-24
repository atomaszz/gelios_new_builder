//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uZWorkOR.h"
#include "uCommonGraph.h"
#include "uCompositeBaseWork.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

TZWorkOR::TZWorkOR(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id)
{
   F_OldPenParent = new Graphics::TPen;
}

TZWorkOR::~TZWorkOR()
{
   delete  F_OldPenParent;
}



void TZWorkOR::Init()
{
   TPoint P1;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Shape;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 6*F_Step;
   P1.y = StartPoint.y - 4*F_Step;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Shape = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId);
   AddShape(Shape);

   P1.y = StartPoint.y + 4*F_Step;
   F_LastShapeId++;
   Shape = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId);
   AddShape(Shape);
   CreateLines();
   CalcWidthWork();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;
   VPoint = TPoint(0,0);

}

//--------------------------------------------------------------------------
void TZWorkOR::CreateLines()
{
   TArrowLine *Line, *Lnb;
   TPoint P, P2;
   int tmp_x;
   TTfeRectShape *Shape1, *Shape2;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Shape1 = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape2 = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Shape1->GetTailPoint(0, P);


   F_LastLineId++;
   //1
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P.x - 3*F_Step ;
   Line->yEnd = P.y + 4*F_Step;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Lnb = Line;
   Shape1->AddWorkLine(Line);



   F_LastLineId++;
   //2
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
//stas   Line->Prepare();
   AddLine(Line);
   Shape1->AddWorkLine(Line);



   Shape1->GetTailPoint(1, P);
   Shape2->GetTailPoint(1, P2);

   tmp_x = P.x;
   if (tmp_x < P2.x ) tmp_x = P2.x;
   tmp_x = tmp_x + 3*F_Step;


   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P.x;
   Line->yStart = P.y;

   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Shape1->AddWorkLine(Line);


   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P2.x;
   Line->yStart = P2.y;

   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Shape2->AddWorkLine(Line);


   Shape2->GetTailPoint(0, P2);
   F_LastLineId++;
   //5
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;

   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   AddLine(Line);
   Shape2->AddWorkLine(Line);


   F_LastLineId++;
   //6
   Lnb = static_cast<TArrowLine*>(GetWorkLine(2));

   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->PointStart =   Lnb->PointEnd;
   Line->xEnd = Lnb->PointEnd.x + 2*F_Step;
   Line->yEnd = Lnb->PointEnd.y;
   AddLine(Line);
   Shape2->AddWorkLine(Line);

}



//--------------------------------------------------------------------------
void TZWorkOR::Prepare()
{
   TArrowLine *Line, *Lnb;
   TPoint P, P2;
   int tmp_x;
   TTfeRectShape *Shape1, *Shape2;

   Shape1 = static_cast<TTfeRectShape*>(GetWorkShape(0));
   Shape2 = static_cast<TTfeRectShape*>(GetWorkShape(1));
   Shape1->GetTailPoint(0, P);


   //1
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P.x - 3*F_Step ;
   Line->yEnd = P.y + 4*F_Step;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;

   //2
   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P.x;
   Line->yEnd = P.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);


   Shape1->GetTailPoint(1, P);
   Shape2->GetTailPoint(1, P2);

   tmp_x = P.x;
   if (tmp_x < P2.x ) tmp_x = P2.x;
   tmp_x = tmp_x + 3*F_Step;

   //3
   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P.x;
   Line->yStart = P.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   VPoint = TPoint(Line->xStart, Line->yEnd);


   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = tmp_x;
   Line->yEnd = Lnb->yEnd;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);


   Shape2->GetTailPoint(0, P2);
   //5
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;

   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   //6
   Lnb = static_cast<TArrowLine*>(GetWorkLine(2));
   Line = static_cast<TArrowLine*>(GetWorkLine(5));
   Line->PointStart =   Lnb->PointEnd;
   Line->xEnd = Lnb->PointEnd.x + 2*F_Step;
   Line->yEnd = Lnb->PointEnd.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TZWorkOR::Paint(TCanvas *Canvas)
{
//    Prepare();
    TBaseWorkShape::Paint(Canvas);
    if (!CompositeWorkShape)
    {
      F_OldPenParent->Assign(Canvas->Pen);
      Canvas->Pen->Width = LineWidth;
      Canvas->Pen->Style = LineStyle;
      Canvas->Pen->Color = PenColor;
      PaintVShape(Canvas, VPoint, F_Step, F_Step, true);
      Canvas->Pen->Assign(F_OldPenParent);
    }  
}


//---------------------------------------------------------------------
int TZWorkOR::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}

//------------------------------------------------------------------------
TPoint __fastcall TZWorkOR::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//------------------------------------------------------------------------
TRectLine* __fastcall TZWorkOR::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------
TRectLine* __fastcall TZWorkOR::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(5));
   return L;
}

//------------------------------------------------------------------------
int __fastcall TZWorkOR::GetTypeShape()
{
   return 3;
}


