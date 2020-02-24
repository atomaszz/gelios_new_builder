//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uLineCutting.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int MyMin(int A1, int A2)
{
    if  (A1 < A2)
        return A1;
    else
        return A2;
}

int MyMax(int A1, int A2)
{
    if  (A1 > A2)
        return A1;
    else
        return A2;
}


TLineCuttingItem::TLineCuttingItem()
{
   f_PStart = TPoint(0, 0);
   f_PEnd = TPoint(0, 0);
   f_Includet = false;
}


int __fastcall TLineCuttingItem::GetType()
{
   int res = BL_OTHER;
   if (f_PStart.x == f_PEnd.x)
     res =  BL_VERTICAL;
   if (f_PStart.y == f_PEnd.y)
     res = BL_HORIZONTAL;
   if ((f_PStart.y == f_PEnd.y) && (f_PStart.x == f_PEnd.x))
     res = BL_POINT;
   return res;
}

int __fastcall TLineCuttingItem::GetXDln()
{
   return  abs(MyMax(f_PEnd.x, f_PStart.x) -  MyMin(f_PEnd.x, f_PStart.x));
}


TLineCutting::TLineCutting(TCanvas* ACanvas)
{
   f_PointList = new TList;
   f_BaseLineList = new TList;
   f_WorkShape = NULL;
   f_NextWorkShape = NULL;
   f_BaseX = f_BaseY = 0;
   f_StartBaseX = f_StartBaseY = 0;
   f_Canvas = ACanvas;
   f_FirstLine = new TRectLine(0, 0);
   f_LastLine = new TRectLine(0, 0);
   f_IsFirstWS = f_IsLastWS = false;
   f_DLines = new TDynamicArray;
   f_DShapes = new TDynamicArray;

}

TLineCutting::~TLineCutting()
{
   FreePointList();
   FreeBaseLineList();
   delete f_PointList;
   delete f_BaseLineList;
   delete f_FirstLine;
   delete f_LastLine;
   delete f_DLines;
   delete f_DShapes;
}


void TLineCutting::FreePointList()
{
   TLineCuttingItem *Item;
   for (int i = f_PointList->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TLineCuttingItem*>(f_PointList->Items[i]);
      delete Item;
      Item = NULL;
      f_PointList->Delete(i);
   }
}


void TLineCutting::FreeBaseLineList()
{
   TBaseLine* Item;
   for (int i = f_BaseLineList->Count - 1; i>=0; i--)
   {
      Item = static_cast<TBaseLine*>(f_BaseLineList->Items[i]);
      delete Item;
      Item = NULL;
      f_BaseLineList->Delete(i);
   }
}



void __fastcall TLineCutting::SetWorkShape(TBaseWorkShape* AValue)
{
   f_WorkShape = AValue;
   FreePointList();
   FreeBaseLineList();
   if (f_WorkShape)
   {
      f_PenColorWS = f_WorkShape->PenColor;
      f_PenWidthWS = f_WorkShape->PenWidth;
      f_PenStyleWS = f_WorkShape->PenStyle;
      f_PenModeWS  = f_WorkShape->PenMode;
      f_FrameColorWS = f_WorkShape->FrameColor;
      f_BrushStyleWS = f_WorkShape->BrushStyle;
      f_DrawCaption = f_WorkShape->DrawCaption;
      f_FirstLine->PointStart = f_WorkShape->FirstLine->PointStart;
      f_FirstLine->PointEnd = f_WorkShape->FirstLine->PointEnd;
      if (f_WorkShape->CompositeWorkShape)
      {
        f_DShapes->Clear();
        f_WorkShape->CompositeWorkShape->GetAllShapes(f_DShapes);
      }
      CreateImage();
   }
}


void __fastcall TLineCutting::SetNextWorkShape(TBaseWorkShape* AValue)
{
   f_NextWorkShape = AValue;
   if (f_NextWorkShape)
   {
     f_LastLine->PointStart = f_NextWorkShape->FirstLine->PointStart;
     f_LastLine->PointEnd = f_NextWorkShape->FirstLine->PointEnd;
   }
   else
   {
     f_LastLine->PointStart = TPoint(0, 0);
     f_LastLine->PointEnd = TPoint(0, 0);
   }
   if (f_NextWorkShape)
     f_NextWorkShape->FirstLine->PaintLine = false;
}


TLineCuttingItem* TLineCutting::FindLine(TPoint APointStart, TPoint APointEnd)
{
   TLineCuttingItem* Res;
   for (int i = 0; i <= f_PointList->Count - 1; i++)
   {
      Res = static_cast<TLineCuttingItem*>(f_PointList->Items[i]);
      if ( (Res->PointStart.x == APointStart.x) && (Res->PointStart.y == APointStart.y) &&
        (Res->PointEnd.x == APointEnd.x) && (Res->PointEnd.y == APointEnd.y) )
        return Res;
   }
   return NULL;
}


bool TLineCutting::AddToPointList(TPoint APointStart, TPoint APointEnd)
{
   TLineCuttingItem* Item =  FindLine(APointStart, APointEnd);
   if (!Item)
   {
      Item = new TLineCuttingItem;
      Item->PointStart = APointStart;
      Item->PointEnd = APointEnd;
      f_PointList->Add(Item);
      return true;
   }
   return false;
}


void TLineCutting::CreateImage()
{
   int i;
   TRectLine* Line;
   TBaseLine *BL;
   FreePointList();
   FreeBaseLineList();
   if (f_WorkShape->CompositeWorkShape)
   {
      f_DLines->Clear();
      f_WorkShape->CompositeWorkShape->GetAllLines(f_DLines, true);
      for (i = 0; i <= f_DLines->Count-1; i++)
      {
         BL = static_cast<TBaseLine*>(f_DLines->Items[i]);
         if (!BL->Tag || !BL->Tag2)
           AddToPointList(BL->PointStart, BL->PointEnd);
      }
   }
   else
   {
     for (i = 0; i <= f_WorkShape->RectLineCount - 1; i++)
     {
        Line = f_WorkShape->RectLineItems[i];
        if (Line != f_WorkShape->FirstLine)
        {
          BL = Line->FirstBaseLine();
          while (BL)
          {
             AddToPointList(BL->PointStart, BL->PointEnd);
             BL = Line->NextBaseLine();
          }
       }
     }
   }
   CreateBaseLine();
}


bool TLineCutting::ComparePoint(TLineCuttingItem *A, TLineCuttingItem* B,
    TPoint &AStart, TPoint &AEnd)
{
   int ax0, ay0, ax1, ay1;
   int bx0, by0, bx1, by1;
   TLineCuttingItem* Temp = B;
   if (A->XDln > B->XDln)
   {
      B = A;
      A = Temp;
   }
   AStart = TPoint(0, 0);
   AEnd = TPoint(0, 0);
   if ( (A->Type == BL_HORIZONTAL) || (A->Type == BL_VERTICAL) )
   {
      if (A->Type != B->Type) return false;
      if (A->Type == BL_HORIZONTAL)
      {
         ax0 = MyMin(A->PointStart.x, A->PointEnd.x);
         ay0 = A->PointStart.y;
         ax1 = MyMax(A->PointStart.x, A->PointEnd.x);
         ay1 = ay0;

         bx0 = MyMin(B->PointStart.x, B->PointEnd.x);
         by0 = B->PointStart.y;
         bx1 = MyMax(B->PointStart.x, B->PointEnd.x);
         by1 = by0;
         if (ay0 != by0) return false;
         if (ax0 <= bx0)
         {
            if (ax1 <= bx0) return false;
            AStart.x = ax0;
            AStart.y = ay0;
            AEnd.x = bx1;
            AEnd.y = by1;
            return true;
         }
         else
         {
            if (bx1 <= ax0) return false;
            AStart.x = bx0;
            AStart.y = by0;
            AEnd.x = ax1;
            AEnd.y = ay1;
            return true;
         }
      }
      else
      {

         ax0 = A->PointStart.x;
         ay0 = MyMin(A->PointStart.y, A->PointEnd.y);
         ax1 = A->PointEnd.x;
         ay1 = MyMax(A->PointStart.y, A->PointEnd.y);

         bx0 = B->PointStart.x;
         by0 = MyMin(B->PointStart.y, B->PointEnd.y);
         bx1 = B->PointEnd.x;
         by1 = MyMax(B->PointStart.y, B->PointEnd.y);
         if (ax0 != bx0) return false;
         if (ay0 <= by0)
         {
            if (ay1 <= by0) return false;
            AStart.x = ax0;
            AStart.y = ay0;
            AEnd.x = bx1;
            AEnd.y = by1;
            return true;
         }
         else
         {
            if (by1 <= ay0) return false;
            AStart.x = bx0;
            AStart.y = by0;
            AEnd.x = ax1;
            AEnd.y = ay1;
            return true;
         }
      }
   }
   return false;
}

/*

bool TLineCutting::ComparePoint(TLineCuttingItem *A, TLineCuttingItem* B,
    TPoint &AStart, TPoint &AEnd)
{
   int ax0, ay0, ax1, ay1;
   int bx0, by0, bx1, by1;
   AStart = TPoint(0, 0);
   AEnd = TPoint(0, 0);
   if ( (A->Type == BL_HORIZONTAL) || (A->Type == BL_VERTICAL) )
   {
      if (A->Type != B->Type) return false;
      if (A->Type == BL_HORIZONTAL)
      {
         ax0 = MyMin(A->PointStart.x, A->PointEnd.x);
         ay0 = A->PointStart.y;
         ax1 = MyMax(A->PointStart.x, A->PointEnd.x);
         ay1 = ay0;

         bx0 = MyMin(B->PointStart.x, B->PointEnd.x);
         by0 = B->PointStart.y;
         bx1 = MyMax(B->PointStart.x, B->PointEnd.x);
         by1 = by0;
         if (ay0 != by0) return false;
         if (ax0 <= bx0)
         {
            if (ax1 <= bx0) return false;
            AStart.x = ax0;
            AStart.y = ay0;
            AEnd.x = bx1;
            AEnd.y = by1;
            return true;
         }
         else
         {
            if (bx1 <= ax0) return false;
            AStart.x = bx0;
            AStart.y = by0;
            AEnd.x = ax1;
            AEnd.y = ay1;
            return true;
         }
      }
      else
      {

         ax0 = A->PointStart.x;
         ay0 = MyMin(A->PointStart.y, A->PointEnd.y);
         ax1 = A->PointEnd.x;
         ay1 = MyMax(A->PointStart.y, A->PointEnd.y);

         bx0 = B->PointStart.x;
         by0 = MyMin(B->PointStart.y, B->PointEnd.y);
         bx1 = B->PointEnd.x;
         by1 = MyMax(B->PointStart.y, B->PointEnd.y);
         if (ax0 != bx0) return false;
         if (ay0 <= by0)
         {
            if (ay1 <= by0) return false;
            AStart.x = ax0;
            AStart.y = ay0;
            AEnd.x = bx1;
            AEnd.y = by1;
            return true;
         }
         else
         {
            if (by1 <= ay0) return false;
            AStart.x = bx0;
            AStart.y = by0;
            AEnd.x = ax1;
            AEnd.y = ay1;
            return true;
         }
      }
   }
   return false;
}

*/

void TLineCutting::CreateBaseLine()
{
   int i, j;
//   TRectLine* Line; //debug
//   TBaseLine *BL; //debug
   TBaseLine *BLine;
   TLineCuttingItem  *LI, *LJ;
   TPoint PS, PE;

/* debug
   for (i = 0; i <= f_WorkShape->RectLineCount - 1; i++)
   {
      Line = f_WorkShape->RectLineItems[i];
      BL = Line->FirstBaseLine();
      while (BL)
      {
        BLine = new TBaseLine(BL->PointStart.x, BL->PointStart.y, BL->PointEnd.x, BL->PointEnd.y, 0);
        BLine->Color = clRed;
        BLine->Mode = pmNotXor;
        f_BaseLineList->Add(BLine);
        BL = Line->NextBaseLine();
      }
   }
*/



   if (f_PointList->Count == 0) return;
   for (i = 0; i <= f_PointList->Count - 1; i++)
   {
     LI = static_cast<TLineCuttingItem*>(f_PointList->Items[i]);
     if (LI->Includet) continue;
     if ( (LI->Type == BL_HORIZONTAL) || (LI->Type == BL_VERTICAL) )
     {
       for (j = i + 1; j <= f_PointList->Count - 1; j++)
       {
          LJ = static_cast<TLineCuttingItem*>(f_PointList->Items[j]);
          if (LI == LJ) continue;
          if ( !LJ->Includet )
          {
             if ( ComparePoint(LI, LJ, PS, PE) )
             {
                LJ->Includet = true;
                LI->PointStart = PS;
                LI->PointEnd = PE;
             }
          }
       }
     }
   }

   for (i = 0; i <= f_PointList->Count - 1; i++)
   {
     LI = static_cast<TLineCuttingItem*>(f_PointList->Items[i]);
     if ( !LI->Includet )
     {
        BLine = new TBaseLine(LI->PointStart.x, LI->PointStart.y,
        LI->PointEnd.x, LI->PointEnd.y, 0);
        BLine->Color = f_FrameColorWS;
        BLine->Width = f_PenWidthWS;
        BLine->Style = f_PenStyleWS;
        BLine->Mode  = pmNotXor;
        f_BaseLineList->Add(BLine);
     }
   }
}


void TLineCutting::BeginMoving(int Ax, int Ay)
{
   TBaseShape* Sh;
   TBaseLine *BL;
   f_StartBaseX = Ax;
   f_StartBaseY = Ay;
   f_BaseX = Ax;
   f_BaseY = Ay;
   if (f_WorkShape->CompositeWorkShape)
   {

      for (int j = 0; j <= f_DShapes->Count - 1; j++)
      {
         Sh = static_cast<TBaseShape*>(f_DShapes->Items[j]);
         Sh->PenColor = f_FrameColorWS;
         Sh->PenMode = pmNotXor;
         Sh->BrushStyle = bsClear;
         Sh->DrawCaption = false;
      }
   }
   else
   {
     f_WorkShape->PenColor   = f_FrameColorWS;
     f_WorkShape->PenMode    = pmNotXor;
     f_WorkShape->BrushStyle = bsClear;
     f_WorkShape->DrawCaption = false;
     for (int i = 0; i <= f_WorkShape->WorkShapesCount - 1; i++ )
     {
        Sh =  f_WorkShape->GetWorkShape(i);
        Sh->PenColor = f_FrameColorWS;
        Sh->PenMode = pmNotXor;
        Sh->BrushStyle = bsClear;
     }
   }

   f_FirstLine->Color = f_FrameColorWS;
   f_FirstLine->Mode = pmNotXor;
   f_FirstLine->Width = f_WorkShape->PenWidth;
   f_LastLine->Color = f_FrameColorWS;
   f_LastLine->Mode = pmNotXor;
   f_LastLine->Width = f_WorkShape->PenWidth;


   f_FirstLine->Bend =  f_WorkShape->Bend(f_FirstLine->xStart, f_FirstLine->xEnd);
   f_LastLine->Bend =  f_WorkShape->Bend(f_LastLine->xStart, f_LastLine->xEnd);

   Paint(f_Canvas);
}


void TLineCutting::Moving(int Ax, int Ay)
{
   if (!f_WorkShape) return;
   Paint(f_Canvas);
   ApplyOffset(Ax - f_BaseX, Ay - f_BaseY);
   f_BaseX = Ax;
   f_BaseY = Ay;
   Paint(f_Canvas);
}


void TLineCutting::ApplyOffset(int Ax, int Ay)
{
   int i;
   TBaseShape* Sh;
   TBaseLine* Bl;
   if (f_WorkShape->CompositeWorkShape)
   {
      for (i = 0; i <= f_DShapes->Count-1; i++)
      {
         Sh = static_cast<TBaseShape*>(f_DShapes->Items[i]);
         Sh->ApplyOffset(Ax, Ay);
      }
   }
   else
   {
     for (i = 0; i <= f_WorkShape->WorkShapesCount - 1; i++ )
     {
        Sh =  f_WorkShape->GetWorkShape(i);
        Sh->ApplyOffset(Ax, Ay);
     }
   }
     for (i = 0; i <= f_BaseLineList->Count - 1; i++ )
     {
        Bl =  static_cast<TBaseLine*>(f_BaseLineList->Items[i]);
        Bl->ApplyOffset(Ax, Ay);
     }

   if (f_IsFirstWS)
     f_FirstLine->ApplyOffset(Ax, Ay);
   else
   {
     f_FirstLine->xEnd = f_FirstLine->xEnd + Ax;
     f_FirstLine->yEnd = f_FirstLine->yEnd + Ay;
   }
   if (f_IsFirstWS && f_IsLastWS)
   {
      f_LastLine->ApplyOffset(Ax, Ay);
      return;
   }
   if (f_IsLastWS)
     f_LastLine->ApplyOffset(Ax, Ay);
   else
   {
     f_LastLine->xStart = f_LastLine->xStart + Ax;
     f_LastLine->yStart = f_LastLine->yStart + Ay;
   }

   f_FirstLine->Bend =  f_WorkShape->Bend(f_FirstLine->xStart, f_FirstLine->xEnd);
   f_LastLine->Bend =  f_WorkShape->Bend(f_LastLine->xStart, f_LastLine->xEnd);
}


void TLineCutting::Paint(TCanvas *ACanvas)
{
   int i;
   TBaseShape* Sh;
   TBaseLine* Bl;
   if (!f_WorkShape) return;
   if (f_WorkShape->CompositeWorkShape)
   {
      for (i = 0; i <= f_DShapes->Count-1; i++)
      {
         Sh = static_cast<TBaseShape*>(f_DShapes->Items[i]);
         Sh->Paint(ACanvas);
      }
   }
   else
   {
     for (i = 0; i <= f_WorkShape->WorkShapesCount - 1; i++ )
     {
        Sh =  f_WorkShape->GetWorkShape(i);
        Sh->Paint(ACanvas);
     }

  }
     for (i = 0; i <= f_BaseLineList->Count - 1; i++ )
     {
        Bl =  static_cast<TBaseLine*>(f_BaseLineList->Items[i]);
        Bl->Paint(ACanvas);
     }
     f_FirstLine->Prepare();
     f_FirstLine->Paint(ACanvas);

   f_LastLine->Prepare();
   f_LastLine->Paint(ACanvas);

}


void TLineCutting::EndMoving(int &AxOfs, int &AyOfs)
{
   TBaseShape* Sh;
   if (!f_WorkShape) return;
   if (f_NextWorkShape)
     f_NextWorkShape->FirstLine->PaintLine = true;

   if (f_WorkShape->CompositeWorkShape)
   {

      for (int j = 0; j <= f_DShapes->Count - 1; j++)
      {
         Sh = static_cast<TBaseShape*>(f_DShapes->Items[j]);
      //   Sh->PenColor = f_PenColorWS;
         Sh->PenMode = f_PenModeWS;
         Sh->BrushStyle = f_BrushStyleWS;
         Sh->DrawCaption = f_DrawCaption;
         Sh->ApplyOffset(f_StartBaseX - f_BaseX, f_StartBaseY - f_BaseY);

      }
   }

   else
   {
     f_WorkShape->PenColor   = f_PenColorWS;
     f_WorkShape->PenMode    = f_PenModeWS;
     f_WorkShape->BrushStyle = f_BrushStyleWS;
     f_WorkShape->DrawCaption = f_DrawCaption;

     for (int i = 0; i <= f_WorkShape->WorkShapesCount - 1; i++ )
     {
        Sh =  f_WorkShape->GetWorkShape(i);
        Sh->PenColor = f_PenColorWS;
        Sh->PenMode = f_PenModeWS;
        Sh->BrushStyle = f_BrushStyleWS;
        Sh->ApplyOffset(f_StartBaseX - f_BaseX, f_StartBaseY - f_BaseY);
     }
   }
   AxOfs = f_BaseX - f_StartBaseX;
   AyOfs = f_BaseY - f_StartBaseY;
}


void TLineCutting::ClearAll()
{
   FreePointList();
   FreeBaseLineList();
}


