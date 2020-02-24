//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeWork.h"
#include "uSubstWork.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


bool TCompositeWork::ConvertWorkShape(TAlternateViewItemTFS  *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape;
   TPoint POfs;
   bool res = false;
   if (AWS)
   {
      f_BWS = AWS->BaseWorkShape;
      ConvertedBWS = AWS->BaseWorkShape;
      POfs = f_BWS->OffsetStartPoint();
      if (AWS->BaseWorkShape->TypeShape == 1)
      {
        mNewShape = CloneShape(AWS->ItemTFE[0]->BaseShape);
        AddBaseShape(mNewShape, AV->IsHaveChildShape(mNewShape->ID));
        f_LastLineBend = AWS->BaseWorkShape->LastLine->Bend;
        f_FirstLineBend = AWS->BaseWorkShape->FirstLine->Bend;
      }
      CreateLines(AWS->BaseWorkShape);
      ApplyOffset(POfs.x, POfs.y);
   }
   return res;
}

void TCompositeWork::ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape;
   TPoint POfs;
   if (AWS && (AWS->TypeShape == 1) )
   {
      POfs = AWS->OffsetStartPoint();
      ConvertedBWS = AWS;
      f_BWS = AWS;

      mNewShape = CloneShape(AWS->GetWorkShape(0));
      AddBaseShape(mNewShape, AV->IsHaveChildShape(mNewShape->ID));

      CreateLines(AWS);
      ApplyOffset(POfs.x, POfs.y);
   }
}


TCompositeWork::TCompositeWork()
{
   f_Rct = NULL;
   f_BWS = NULL;
   f_LastLine = NULL;
   f_FirstLine = NULL;
   f_FirstRectLine = NULL;
   f_LastRCT = new TDynamicArray;
   f_FirstRCT = new TDynamicArray;
}

TCompositeWork::~TCompositeWork()
{
   delete f_LastRCT;
   delete f_FirstRCT;
}



void TCompositeWork::CreateLines(TBaseWorkShape *AWS)
{
   TBaseLine *Line, *Base;
   f_step = AWS->Step;
   int index = 0;
   int m_x0, m_x1, m_y0, m_y1;
   int i ;
   f_FirstRectLine = new TRectLine(f_step, 0);
   AddRectLine(f_FirstRectLine);

   f_LastRCT->Clear();
   for (int i = 0 ; i <= 4; i++)
   {
     Line = new TBaseLine(0, 0, 0, 0, f_step);
     Line->Visible = false;
     AddBaseLine(Line);
   }

   f_Rct = AWS->FirstLine;
   Base = f_Rct->FirstBaseLine();
   f_FirstLine = NULL;
   while (Base)
   {
      Line = GetBaseLine(index);
      Line->Visible = true;
      m_x0 = Base->X0;
      m_x1 = Base->X1;
      m_y0 = Base->Y0;
      m_y1 = Base->Y1;
      Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
      Line->Tag = 1;
      f_FirstRCT->Append(Line);
      if (!f_FirstLine)
        f_FirstLine = Line;
      index++;
      Base = f_Rct->NextBaseLine();
   }
   f_FirstRectLine->SetCoord(f_Rct->xStart, f_Rct->yStart, f_Rct->xEnd, f_Rct->yEnd, f_Rct->Bend);

   f_Rct = AWS->LastLine;
   Base = f_Rct->FirstBaseLine();
   i = 0;
   while (Base)
   {
      Line = GetBaseLine(index);
      Line->Visible = true;
      m_x0 = Base->MinX;
      m_x1 = Base->MaxX;
      m_y0 = Base->MinY;
      m_y1 = Base->MaxY;
      Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
      f_LastRCT->Append(Line);
      if (i == 0)
      {
        f_LP.x = Base->X0;
        f_LP.y = Base->Y0;
      }
      index++;
      Base = f_Rct->NextBaseLine();
      i++;
   }
   f_LastLine = Line;
}


void  TCompositeWork::Prepare()
{
   TBaseLine *Line;
   TCompositeBaseWorkItem* Item = GetItem(0);
   Item->StartPoint = f_FirstRectLine->PointEnd;
   TPoint RHV =  Item->EndPoint;
   //Line->ApplyOffset(x_offs, y_offs);
   for(int i = 0; i <= f_LastRCT->Count-1 ; i ++)
   {
      Line = static_cast<TBaseLine*>(f_LastRCT->Items[i]);
      Line->Visible = true;
      Line->MoveTo(RHV);
   }


   if (!f_FirstRectLine || f_FirstRectLine->PaintLine)
      {
        for(int i = 0; i <= f_FirstRCT->Count-1 ; i ++)
        {
          Line = static_cast<TBaseLine*>(f_FirstRCT->Items[i]);
          Line->Visible = true;
        }
      }

   PrepareDrawFlags();

}

void TCompositeWork::PrepareDrawFlags()
{
   if (f_FirstRectLine)
   {

      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->FlagSType  = f_FirstRectLine->FlagSType;
      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->OnFlagCreate =  &(f_FirstRectLine->FlagCreate);
      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->OnFlagDestroy =  &(f_FirstRectLine->FlagDestroy);
      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->DrawFlagS = f_BWS->DrawFirstFlag;
      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->UnderControl =  f_FirstRectLine->UnderControl;
      static_cast<TBaseLine*>(f_FirstRCT->Items[0])->WndHandler =  f_FirstRectLine->WndHandler;
    //  static_cast<TBaseLine*>(f_RCT[0]->Items[0])->Prepare();

      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->FlagEType  = f_FirstRectLine->FlagEType;
      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->OnFlagCreate =  &(f_FirstRectLine->FlagCreate);
      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->OnFlagDestroy = &(f_FirstRectLine->FlagDestroy);
      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->DrawFlagE = f_BWS->DrawLastFlag;
      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->UnderControl =  f_FirstRectLine->UnderControl;
      static_cast<TBaseLine*>(f_LastRCT->Items[f_LastRCT->Count-1])->WndHandler =  f_FirstRectLine->WndHandler;
    //  static_cast<TBaseLine*>(f_RCT[0]->Items[f_RCT[0]->Count-1])->Prepare();
   }
}


TPoint __fastcall TCompositeWork::GetEndPoint()
{
   return f_LastLine->End;
}


TPoint __fastcall TCompositeWork::GetStartPoint()
{
   return f_FirstLine->Start;
}

TBaseLine* __fastcall TCompositeWork::GetEndLine()
{
   return f_LastLine;
}

TRectLine* __fastcall TCompositeWork::GetFirstLine()
{
   return f_FirstRectLine;
}


void TCompositeWork::MakeFirstLine(TPoint AStart, int ABend)
{
    int i;
    int m_x0;
    int m_x1;
    int m_y0;
    int m_y1;
    TBaseLine *L, *Line;
    TRectLine *FL;

    FL = FirstLine;
    FL->Bend = ABend;
    FL->xStart = AStart.x;
    FL->yStart = AStart.y;
    FL->Prepare();

    i = 0;
    L = FL->FirstBaseLine();
    while (L)
    {
      if (i <= f_FirstRCT->Count - 1)
        Line = static_cast<TBaseLine*>(f_FirstRCT->Items[i]);
      else
      {
        Line = GetNewLine();
        Line->Tag = 1;
        f_FirstRCT->Append(Line);
      }
      Line->Visible = true;
      m_x0 = L->X0;
      m_x1 = L->X1;
      m_y0 = L->Y0;
      m_y1 = L->Y1;
      Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
      i++;
      L = FL->NextBaseLine();
   }
   while (i <= f_FirstRCT->Count - 1 )
   {
      Line = static_cast<TBaseLine*>(f_FirstRCT->Items[i]);
      f_FirstRCT->Delete(Line);
      DeleteLine(Line);
   }

}







