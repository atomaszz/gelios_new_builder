//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeCheckCondition.h"
#include "uCommonGraph.h"
#include "uTfeHexahedronShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TCompositeCheckCondition::TCompositeCheckCondition()
{
   f_BWS = NULL;
   f_step = 0;
   f_FirstLine = NULL;
   for (int i = 0; i <= 5; i++)
     f_RCT[i] = new TDynamicArray;
}


TCompositeCheckCondition::~TCompositeCheckCondition()
{
   for (int i = 0; i <= 5; i++)
     delete f_RCT[i];
}

bool TCompositeCheckCondition::ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape1, *mNewShape2, *mNewShape3;
   TPoint POfs;
   bool res = false;
   if (AWS && (AWS->BaseWorkShape->TypeShape == 11) )
   {
      f_BWS = AWS->BaseWorkShape;
      ConvertedBWS = AWS->BaseWorkShape;
      POfs = f_BWS->OffsetStartPoint();

      mNewShape1 = CloneShape(AWS->ItemTFE[0]->BaseShape);
      AddBaseShape(mNewShape1, AV->IsHaveChildShape(mNewShape1->ID));
      mNewShape2 = CloneShape(AWS->ItemTFE[1]->BaseShape);
      AddBaseShape(mNewShape2, AV->IsHaveChildShape(mNewShape2->ID));
      mNewShape3 = CloneShape(AWS->ItemTFE[2]->BaseShape);
      AddBaseShape(mNewShape3, AV->IsHaveChildShape(mNewShape3->ID));

      CreateLines(AWS->BaseWorkShape);
      ApplyOffset(POfs.x, POfs.y);
      f_Rect1 = mNewShape1->GetRect();
      f_Rect2 = mNewShape2->GetRect();
   }
   return res;
}

void TCompositeCheckCondition::ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV)
{

   TBaseShape *mNewShape1, *mNewShape2, *mNewShape3;
   TPoint POfs;
   if (AWS && (AWS->TypeShape == 11) )
   {
      f_BWS = AWS;
      ConvertedBWS = AWS;
      POfs = f_BWS->OffsetStartPoint();

      mNewShape1 = CloneShape(AWS->GetWorkShape(0));
      AddBaseShape(mNewShape1, AV->IsHaveChildShape(mNewShape1->ID));
      mNewShape2 = CloneShape(AWS->GetWorkShape(1));
      AddBaseShape(mNewShape2, AV->IsHaveChildShape(mNewShape2->ID));
      mNewShape3 = CloneShape(AWS->GetWorkShape(2));
      AddBaseShape(mNewShape3, AV->IsHaveChildShape(mNewShape3->ID));

      CreateLines(AWS);
      ApplyOffset(POfs.x, POfs.y);
      f_Rect1 = mNewShape1->GetRect();
      f_Rect2 = mNewShape2->GetRect();
   }
}



void TCompositeCheckCondition::CreateLines(TBaseWorkShape *AWS)
{
   TBaseLine *Line, *Base;
   TRectLine *f_Rct, *l_Rct;
   f_step = AWS->Step;
   int index = 0;
   int cnt = 1;
   int mark;
   int m_x0, m_x1, m_y0, m_y1;
   f_FirstRectLine = new TRectLine(f_step, 0);
   AddRectLine(f_FirstRectLine);

   for (int i = 0 ; i <= 13; i++)
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
      Line->Visible = false;
      m_x0 = Base->X0;
      m_x1 = Base->X1;
      m_y0 = Base->Y0;
      m_y1 = Base->Y1;
      Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
      Line->Tag = 1;
      f_RCT[0]->Append(Line);
      if (!f_FirstLine)
        f_FirstLine = Line;
      index++;
      Base = f_Rct->NextBaseLine();
   }
   f_FirstRectLine->SetCoord(f_Rct->xStart, f_Rct->yStart, f_Rct->xEnd, f_Rct->yEnd, f_Rct->Bend);

   l_Rct = AWS->LastLine;
   Base = l_Rct->FirstBaseLine();
   while (Base)
   {
      Line = GetBaseLine(index);
      Line->Visible = false;
      m_x0 = Base->X0;
      m_x1 = Base->X1;
      m_y0 = Base->Y0;
      m_y1 = Base->Y1;
      Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
      f_RCT[5]->Append(Line);
      index++;
      Base = l_Rct->NextBaseLine();
   }
   f_LastLine = Line;

   TRectLine* t_Rct;
   for(int i = 0; i <= AWS->WorkLinesCount - 1; i ++)
   {
      mark = 0;
      t_Rct = AWS->RectLineItems[i];
      if ( (t_Rct == f_Rct) || (t_Rct == l_Rct) )
        continue;
      Base = t_Rct->FirstBaseLine();
      while (Base)
      {
        Line = GetBaseLine(index);
        Line->Visible = false;
        m_x0 = Base->MinX;
        m_x1 = Base->MaxX;
        m_y0 = Base->MinY;
        m_y1 = Base->MaxY;
        Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
        f_RCT[cnt]->Append(Line);
        mark++;
        index++;
        Base = t_Rct->NextBaseLine();
     }
     cnt++;
   }
}

int TCompositeCheckCondition::CalcBend(int t_x1, int t_x2)
{
   int res = 0;
   if (t_x1 < t_x2) res = 2;
   if (t_x1 > t_x2) res = 3;
   return res;
}

TBaseLine* TCompositeCheckCondition::GetIndexLine(int AIndex)
{
   TBaseLine* Res = NULL;
   switch (AIndex)
   {
      case 0:
        Res =  static_cast<TBaseLine*>(f_RCT[1]->Items[0]);
        break;
      case 1:
        Res =  static_cast<TBaseLine*>(f_RCT[1]->Items[1]);
        break;
      case 2:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[0]);
        break;
      case 3:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[1]);
        break;
      case 4:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[2]);
        break;
      case 5:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[0]);
        break;
      case 6:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[1]);
        break;
      case 7:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[2]);
        break;
      case 8:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[0]);
        break;
      case 9:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[1]);
        break;

   }

   return Res;
}



void TCompositeCheckCondition::Prepare()
{
   int dy1, dy2;
   int s1, s2, dx, mx1, mx2;
   int x_offs, y_offs;
   int x_offs2, y_offs2;
   TBaseLine *Line, *Lnb;

   TCompositeBaseWorkItem *Shape1, *Shape2;
   TCompositeBaseWorkItem *MaxShape, *MinShape;
   TTfeHexahedronShape *Hexa;
   TPoint PS1, PE1, PS2, PE2, RHV, RHV1, RHV2;
   TPoint VP;
   TRect R1, R2, RMax, RMin;
   HideLines();
   Shape1 = GetItem(1);
   Shape2 = GetItem(2);
   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;
   Hexa = dynamic_cast<TTfeHexahedronShape*>(GetItem(0)->BaseShape);
   Hexa->GetTailPoint(0, RHV);
   Hexa->GetTailPoint(1, RHV1);
   Hexa->GetTailPoint(3, RHV2);

   dy1 = RHV.y - 4*f_step - R1.Bottom;
   dy2 = RHV.y + 4*f_step - R2.Top;
   if (dy1)
     Shape1->ApplyOffset(0, dy1);
   if (dy2)
     Shape2->ApplyOffset(0, dy2);

   PS1 = Shape1->StartPoint;
   PS2 = Shape2->StartPoint;
   Line = GetIndexLine(0);
   mx1 = PS1.x - Line->MaxX -  4*f_step;
   mx2 = PS2.x - Line->MaxX  - 4*f_step;
   Shape1->ApplyOffset(-mx1, 0);
   Shape2->ApplyOffset(-mx2, 0);
   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;


   s1 = DivTrunc(abs(R1.Right - R1.Left), 2) + R1.Left;
   s2 = DivTrunc(abs(R2.Right - R2.Left), 2) + R2.Left;
   dx = abs(s1 - s2);
   if (s1 > s2)
     Shape2->ApplyOffset(dx, 0);

   if (s1 < s2)
     Shape1->ApplyOffset(dx, 0);


   //смещаем линии
   PS1 = Shape1->StartPoint;
   PS2 = Shape2->StartPoint;
   PE1 = Shape1->EndPoint;
   PE2 = Shape2->EndPoint;


   Line = GetIndexLine(0);
   Line->Visible = true;
   StretchLineY(Line, PS1.y);
   Lnb = Line;

   Line = GetIndexLine(1);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(Lnb->X0, Lnb->MinY);
   StretchLineX(Line, PS1.x);

   Line = GetIndexLine(2);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(PE1);
   StretchLineX(Line, std::max(PE1.x, PE2.x) + f_step);
   Lnb = Line;

   Line = GetIndexLine(3);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(Lnb->End);
   StretchLineY(Line, RHV.y);
   Lnb = Line;

   Line = GetIndexLine(4);
   Line->Visible = true;
   Line->MoveTo(Lnb->End);
   Lnb = Line;
   VP = Line->End;

   Line = GetIndexLine(5);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(PE2);
   StretchLineX(Line, std::max(PE1.x, PE2.x) + f_step);
   Lnb = Line;

   Line = GetIndexLine(6);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(Lnb->MaxX, RHV.y);
   StretchLineY(Line, Lnb->MaxY);
   Lnb = Line;

   Line = GetIndexLine(7);
   Line->Visible = true;
   Line->MoveTo(Lnb->X0, Lnb->MinY);

   Line = GetIndexLine(9);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(RHV2);
   StretchLineY(Line, PS2.y);
   Lnb = Line;

   Line = GetIndexLine(8);
   Line->Visible = true;
   Line->ApplyCoord(0,0,0,0);
   Line->MoveTo(Lnb->X0, Lnb->MaxY);
   StretchLineX(Line, PS2.x);

   for(int i = 0; i <= f_RCT[5]->Count-1 ; i ++)
   {
      Line = static_cast<TBaseLine*>(f_RCT[5]->Items[i]);
      Line->Visible = true;
      Line->MoveTo(VP);
   }

   if (!f_FirstRectLine || f_FirstRectLine->PaintLine)
      {
        for(int i = 0; i <= f_RCT[0]->Count-1 ; i ++)
        {
          Line = static_cast<TBaseLine*>(f_RCT[0]->Items[i]);
          Line->Visible = true;
        }
      }
   PrepareDrawFlags();
}

void TCompositeCheckCondition::PrepareDrawFlags()
{
   if (f_FirstRectLine)
   {

      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->FlagSType  = f_FirstRectLine->FlagSType;
      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->OnFlagCreate =  &(f_FirstRectLine->FlagCreate);
      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->OnFlagDestroy =  &(f_FirstRectLine->FlagDestroy);
      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->DrawFlagS = f_BWS->DrawFirstFlag;
      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->UnderControl =  f_FirstRectLine->UnderControl;
      static_cast<TBaseLine*>(f_RCT[0]->Items[0])->WndHandler =  f_FirstRectLine->WndHandler;
    //  static_cast<TBaseLine*>(f_RCT[0]->Items[0])->Prepare();

      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->FlagEType  = f_FirstRectLine->FlagEType;
      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->OnFlagCreate =  &(f_FirstRectLine->FlagCreate);
      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->OnFlagDestroy = &(f_FirstRectLine->FlagDestroy);
      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->DrawFlagE = f_BWS->DrawLastFlag;
      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->UnderControl =  f_FirstRectLine->UnderControl;
      static_cast<TBaseLine*>(f_RCT[5]->Items[f_RCT[5]->Count-1])->WndHandler =  f_FirstRectLine->WndHandler;
    //  static_cast<TBaseLine*>(f_RCT[0]->Items[f_RCT[0]->Count-1])->Prepare();
   }
}


TPoint __fastcall TCompositeCheckCondition::GetEndPoint()
{
   return f_LastLine->End;
}


TPoint __fastcall TCompositeCheckCondition::GetStartPoint()
{
   return f_FirstLine->Start;
}

TBaseLine* __fastcall TCompositeCheckCondition::GetEndLine()
{
   return f_LastLine;
}

TRectLine* __fastcall TCompositeCheckCondition::GetFirstLine()
{
   return f_FirstRectLine;
}


void TCompositeCheckCondition::MakeFirstLine(TPoint AStart, int ABend)
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
      if (i <= f_RCT[0]->Count - 1)
        Line = static_cast<TBaseLine*>(f_RCT[0]->Items[i]);
      else
      {
        Line = GetNewLine();
        Line->Tag = 1;
        f_RCT[0]->Append(Line);
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
   while (i <= f_RCT[0]->Count - 1 )
   {
      Line = static_cast<TBaseLine*>(f_RCT[0]->Items[i]);
      f_RCT[0]->Delete(Line);
      DeleteLine(Line);
   }

}





