//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uControlFunc.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TControlFunc::ShapeCopy(TBaseShape *Shape, int Num_Shape)
{
   if (Num_Shape == 1)
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

void TControlFunc::CreateLines()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeEllShape *Ell;
   FreeWorkLines();
   F_LastLineId = F_NumberLineId;

   Rct =  static_cast<TTfeRectShape*>(GetWorkShape(0));
   Ell =  static_cast<TTfeEllShape*>(GetWorkShape(1));
   Rct->GetTailPoint(0, P1);
   F_LastLineId++;
   //1
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P1.x - 2*F_Step;
   Line->yEnd = P1.y;
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
   AddLine(Line);

   Rct->GetTailPoint(1, P1);
   Ell->GetTailPoint(0, P2);

   F_LastLineId++;
   //3
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   AddLine(Line);

   Rct->GetTailPoint(0, P1);
   Ell->GetTailPoint(1, P2);

   F_LastLineId++;
   //4
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;
   AddLine(Line);

   Ell->GetTailPoint(2, P2);
   F_LastLineId++;
   //5
   Line = new TArrowLine(F_Step, F_LastLineId);
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P2.x + 2*F_Step;
   Line->yEnd = P2.y;
   AddLine(Line);
}


void TControlFunc::Init()
{
   TPoint P1,P2;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeEllShape *Ell;

   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 4*F_Step;
   P1.y = StartPoint.y;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, F_LastShapeId);
   AddShape(Rct);

   Rct->GetTailPoint(1, P2);
   P2.x = P2.x + 2*F_Step;
   F_LastShapeId++;
   Ell = new TTfeEllShape(P2.x, P2.y, F_Step, F_LastShapeId);
   Ell->TailLeft = true;
   Ell->TailTop = true;
   Ell->TailRight = true;
   AddShape(Ell);
   CreateLines();
   CalcWidthWork();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;

}

//--------------------------------------------------------------------------
void TControlFunc::Prepare()
{
   TArrowLine *Line, *Lnb;
   TPoint P1, P2;
   int tmp_x;
   TTfeRectShape *Rct;
   TTfeEllShape *Ell;

   Rct =  static_cast<TTfeRectShape*>(GetWorkShape(0));
   Ell =  static_cast<TTfeEllShape*>(GetWorkShape(1));
   Rct->GetTailPoint(0, P1);
   Line = static_cast<TArrowLine*>(GetWorkLine(0));
   Line->xStart = StartPoint.x;
   Line->yStart = StartPoint.y;
   Line->xEnd = P1.x - 2*F_Step;
   Line->yEnd = P1.y;
   Line->Bend = CalcBend(Line->xStart, Line->xEnd);
   Lnb = Line;

   Line = static_cast<TArrowLine*>(GetWorkLine(1));
   Line->xStart = Lnb->xEnd;
   Line->yStart = Lnb->yEnd;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;

   Rct->GetTailPoint(1, P1);
   Ell->GetTailPoint(0, P2);

   Line = static_cast<TArrowLine*>(GetWorkLine(2));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;

   Rct->GetTailPoint(0, P1);
   Ell->GetTailPoint(1, P2);

   Line = static_cast<TArrowLine*>(GetWorkLine(3));
   Line->xStart = P1.x;
   Line->yStart = P1.y;
   Line->xEnd = P2.x;
   Line->yEnd = P2.y;

   Ell->GetTailPoint(2, P2);
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P2.x + 2*F_Step;
   Line->yEnd = P2.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TControlFunc::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TControlFunc::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}

//----------------------------------------------------------------------
TPoint __fastcall TControlFunc::GetEndPoint()
{
   if (CompositeWorkShape)
      return CompositeWorkShape->EndPoint;
   return LastLine->PointEnd;
}

//----------------------------------------------------------------------
bool TControlFunc::CanAlternate(int ID_Shape1, int ID_Shape2)
{
   TBaseShape *Shp1, *Shp2;
   bool res = false;
   Shp1 = GetWorkShape(0);
   Shp2 = GetWorkShape(1);
   if ((Shp1->ID == ID_Shape1) && (Shp2->ID == ID_Shape2)) res = true;
   if ((Shp1->ID == ID_Shape2) && (Shp2->ID == ID_Shape1)) res = true;
   return res;
}

//----------------------------------------------------------------------
TRectLine* __fastcall TControlFunc::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;

}

//----------------------------------------------------------------------
TRectLine* __fastcall TControlFunc::GetLastLine()
{
   TRectLine *L;
   L = static_cast<TRectLine*>(GetWorkLine(4));
   return L;
}

int __fastcall TControlFunc::GetTypeShape()
{
   return 5;
}


