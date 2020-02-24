//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSubstWorkItem.h"
#include "uSubstWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TSubstWorkItem::TSubstWorkItem()
{
   f_Type = -1;
   f_Shape = NULL;
   f_SubstWork = NULL;
   f_WorkLines = new TList;
}

void TSubstWorkItem::SetShape(TBaseShape* AShape)
{
   if ( (f_Type == 0) && (f_Shape == AShape) )
     return;
   if ( (f_Type == 0) && (f_Shape != AShape) )
   {
       delete f_Shape;
       f_Shape = AShape;
   }
   if (f_Type == 1)
   {
       delete f_SubstWork;
       f_SubstWork = NULL;
       f_Shape = AShape;
       f_Type = 0;
   }
   if (f_Type == -1)
   {
       f_Type = 0;
       f_Shape = AShape;
   }
}


void TSubstWorkItem::SetSubstWork(TSubstWork* ASW)
{
   if ( (f_Type == 1) && (f_SubstWork == ASW) )
     return;
   if ( (f_Type == 1) && (f_SubstWork != ASW) )
   {
       delete f_SubstWork;
       f_SubstWork = ASW;
   }
   if (f_Type == 0)
   {
       delete f_Shape;
       f_Shape = NULL;
       f_SubstWork = ASW;
       f_Type = 1;
   }
   if (f_Type == -1)
   {
       f_Type = 1;
       f_SubstWork = ASW;
   }
}

TSubstWorkItem::~TSubstWorkItem()
{
    if (f_SubstWork)
      delete f_SubstWork;
    if (f_Shape)
      delete f_Shape;
    delete f_WorkLines;
}

void TSubstWorkItem::Paint(TCanvas *ACanvas)
{
   if (f_Shape)
     f_Shape->Paint(ACanvas);
   if (f_SubstWork)
     f_SubstWork->Paint(ACanvas);
}

void TSubstWorkItem::SetOffsetPosition(int Ax, int Ay)
{
   TRect R;
   TBaseLine* baseLine;
   if (f_Shape)
   {
     R = f_Shape->BoundRect;
     R.Left = R.Left + Ax;
     R.Right = R.Right + Ax;
     R.Top = R.Top + Ay;
     R.Bottom = R.Bottom + Ay;
     f_Shape->BoundRect = R;
     for (int i = 0 ; i <= WorkLineCount - 1 ;i++)
     {
       baseLine = WorkLine[i];
       baseLine->ApplyOffset(Ax, Ay);
     }

   }
   if (f_SubstWork)
     f_SubstWork->SetOffsetPosition(Ax, Ay);
}

TRect TSubstWorkItem::GetAnyRect()
{
   if (f_Shape)
     return f_Shape->GetRect();
   if (f_SubstWork)
     return f_SubstWork->GetAnyRect();
   return TRect(0,0,0,0);
}


TRect TSubstWorkItem::GetRectSummary(TRect ARect)
{
   TRect R_tmp;
   TRect Res = ARect;
   if (f_Shape)
   {
     R_tmp =  f_Shape->GetRect();
     if (R_tmp.Left < Res.Left )  Res.Left = R_tmp.Left;
     if (R_tmp.Right > Res.Right) Res.Right = R_tmp.Right;
     if (R_tmp.Top < Res.Top) Res.Top = R_tmp.Top;
     if (R_tmp.Bottom > Res.Bottom) Res.Bottom = R_tmp.Bottom;
     return Res;
   }
   if (f_SubstWork)
     return f_SubstWork->GetRectSummary(ARect);
   return TRect(0, 0, 0, 0);  
}


bool TSubstWorkItem::IsContainShapeID(int AID)
{
   if (f_Type == 0)
     return (f_Shape->ID == AID);
   return false;
}

TPoint __fastcall TSubstWorkItem::GetStartPoint()
{
   TPoint Res = TPoint(0, 0);
   if (f_Shape)
     Res = f_Shape->PointTail_StartShape;
   if (f_SubstWork)
     Res = f_SubstWork->StartPoint;
   return Res;
}

TPoint __fastcall TSubstWorkItem::GetEndPoint()
{
   TPoint Res = TPoint(0, 0);
   if (f_Shape)
     Res = f_Shape->PointTail_EndShape;
   if (f_SubstWork)
     Res = f_SubstWork->EndPoint;
   return Res;
}

void TSubstWorkItem::OffsetEndCoordinate(TSubstWork* AfterWork)
{

}


TBaseLine* __fastcall  TSubstWorkItem::GetWorkLine(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_WorkLines->Count - 1)
     return static_cast<TBaseLine*>(f_WorkLines->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TSubstWorkItem::GetWorkLineCount()
{
   return f_WorkLines->Count;
}


void TSubstWorkItem::AddWorkLine(TBaseLine *ALine)
{
   f_WorkLines->Add(ALine);
}

void TSubstWorkItem::ClearWorkLine()
{
   f_WorkLines->Clear();
}

