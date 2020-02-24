//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uBifurcation.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/*
bool TBifurcation::CanFlagToLine(int NumLine)
{
   bool res = false;
   bool r1, r2;
   int i;
   TBaseShape  *S1, *S2, *S3;
   TAlternateShapeID *Alt;
   if (AlternateShapeIDList->Count == 0) return res;
   S1 = GetWorkShape(0);
   S2 = GetWorkShape(1);
   S3 = GetWorkShape(2);
   if (NumLine == 0)
   {
      for (i=0; i <= AlternateShapeIDList->Count - 1; i++)
      {
         Alt = (TAlternateShapeID*)AlternateShapeIDList->Items[i];

         res = ( ((S1->ID == Alt->ID1) && (S2->ID == Alt->ID2)) ||
            ((S1->ID == Alt->ID2) && (S2->ID == Alt->ID1)) );
         if (res) return res;
      }

   }

   if (NumLine == 1)
   {
      for (i=0; i <= AlternateShapeIDList->Count - 1; i++)
      {
         Alt = (TAlternateShapeID*)AlternateShapeIDList->Items[i];

         res = ( ((S1->ID == Alt->ID1) && (S3->ID == Alt->ID2)) ||
            ((S1->ID == Alt->ID2) && (S3->ID == Alt->ID1)) );
         if (res) return res;
      }
   }
   return res;
}
*/

void __fastcall TBifurcation::ShapeCopy(TBaseShape *Shape, int Num_Shape)
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

void TBifurcation::Init()
{
   TPoint P1, P2;
   int n1, n2, n3;
   FreeWorkLines();
   FreeWorkShapes();
   TTfeRectShape *Rct;
   TTfeRhombShape *Rhomb;
   F_LastShapeId = F_NumberShapeId;
   P1.x = StartPoint.x + 2*F_Step;
   P1.y = StartPoint.y;

   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   F_LastShapeId++;
   F_LastShapeId++;
   n3 = F_LastShapeId;
   n2 = n3 - 1;
   n1 = n2 - 1;

   Rhomb = new TTfeRhombShape(P1.x, P1.y, F_Step, n3);
   Rhomb->TailLeft = true;
   Rhomb->TailTop = true;
   Rhomb->TailBottom = true;
   AddShape(Rhomb);

   Rhomb->GetTailPoint(1, P1);
   P1.x = P1.x + 4*F_Step;
   P1.y = P1.y - 2*F_Step;

   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, n1);
   AddShape(Rct);

   Rhomb->GetTailPoint(3, P1);
   P1.x = P1.x + 4*F_Step;
   P1.y = P1.y + 2*F_Step;
   Rct = new TTfeRectShape(P1.x, P1.y, F_Step, n2);
   AddShape(Rct);
   CreateLines();
   CalcWidthWork();
   F_Indent = FirstLine->xEnd - FirstLine->xStart;
}

//--------------------------------------------------------------------------
void TBifurcation::CreateLines()
{
   TArrowLine *Line, *Lnb;
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

   Rhomb->GetTailPoint(3, P1);
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
void TBifurcation::Prepare()
{
   TArrowLine *Line, *Lnb;
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
   //Line->Bend = CalcBend(Line->xStart, Line->xEnd);

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
   Rhomb->GetTailPoint(3, P1);
   Rct->GetTailPoint(0, P2);
   //5
   Line = static_cast<TArrowLine*>(GetWorkLine(4));
   Line->xStart = P2.x;
   Line->yStart = P2.y;
   Line->xEnd = P1.x;
   Line->yEnd = P1.y;
   //Line->Bend = CalcBend(Line->xStart, Line->xEnd);

   //6
   Lnb = static_cast<TArrowLine*>(GetWorkLine(2));

   Line = static_cast<TArrowLine*>(GetWorkLine(5));
   Line->PointStart =   Lnb->PointEnd;
   Line->xEnd = Lnb->PointEnd.x + 2*F_Step;
   Line->yEnd = Lnb->PointEnd.y;

   TBaseWorkShape::Prepare();

}

//-----------------------------------------------------------------------
void TBifurcation::Paint(TCanvas *Canvas)
{
   // Prepare();
    TBaseWorkShape::Paint(Canvas);
}


//---------------------------------------------------------------------
int TBifurcation::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}


//------------------------------------------------------------------------------
TPoint __fastcall TBifurcation::GetEndPoint()
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
bool TBifurcation::CanAlternate(int ID_Shape1, int ID_Shape2)
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
TRectLine* __fastcall TBifurcation::GetFirstLine()
{
   TRectLine *L;
   L = TBaseWorkShape::GetFirstLine();
   if (!L)
     L = static_cast<TRectLine*>(GetWorkLine(0));
   return L;
}

//------------------------------------------------------------------------------
TRectLine* __fastcall TBifurcation::GetLastLine()
{
   TRectLine *L;
   L = (TRectLine *)GetWorkLine(5);
   return L;
}


int __fastcall TBifurcation::GetTypeShape()
{
   return 6;
}




