//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeCycleDoWhileDo.h"
#include "uTfeRhombShape.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TCompositeCycleDoWhileDo::TCompositeCycleDoWhileDo()
{
   f_BWS = NULL;
   f_step = 0;
   f_FirstLine = NULL;
   for (int i = 0; i <= 5; i++)
     f_RCT[i] = new TDynamicArray;
}


TCompositeCycleDoWhileDo::~TCompositeCycleDoWhileDo()
{
   for (int i = 0; i <= 5; i++)
     delete f_RCT[i];
}

bool TCompositeCycleDoWhileDo::ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape1, *mNewShape2, *mNewShape3;
   TPoint POfs;
   bool res = false;
   if (AWS && (AWS->BaseWorkShape->TypeShape == 9) )
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

void TCompositeCycleDoWhileDo::ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape1, *mNewShape2, *mNewShape3;
   TPoint POfs;
   if (AWS && (AWS->TypeShape == 9) )
   {
      POfs = AWS->OffsetStartPoint();
      f_BWS = AWS;
      ConvertedBWS = AWS;

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



void TCompositeCycleDoWhileDo::CreateLines(TBaseWorkShape *AWS)
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
   Line = new TBaseLine(0, 0, 0, 0, f_step);
   Line->Visible = false;
   AddBaseLine(Line);
   f_RCT[4]->Append(Line);

}

TBaseLine* TCompositeCycleDoWhileDo::GetIndexLine(int AIndex)
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
        Res =  static_cast<TBaseLine*>(f_RCT[1]->Items[2]);
        break;
      case 3:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[0]);
        break;
      case 4:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[1]);
        break;
      case 5:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[0]);
        break;
      case 6:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[0]);
        break;
      case 7:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[1]);
        break;

   }

   return Res;
}



void TCompositeCycleDoWhileDo::Prepare()
{
   int h, h1, h2, s1, s2;
   TBaseLine *Line, *Lnb, *Lnb0;
   TCompositeBaseWorkItem *Shape1, *Shape2, *Shape3;
   TPoint PS1, PE1, PS2, PE2, PTail;
   TTfeRhombShape* Rhomb;
   TRect R1, R2;
   HideLines();
   Shape1 = GetItem(0);
   Shape2 = GetItem(1);
   Shape3 = GetItem(2);
   Rhomb = dynamic_cast<TTfeRhombShape*>(Shape3->BaseShape);
   Rhomb->GetTailPoint(0, PTail);




   PS1 = f_FirstRectLine->PointEnd;
   PS2 = Shape2->StartPoint;
   PS2 = PointAdd(PS2, -4*f_step,0);
   PE1 = PointSub(PS1, PS2);
   if ( !PointIsNull(PE1) )
   {
      Shape2->ApplyOffset(PE1.x, PE1.y);
   }

   PS1 = f_FirstRectLine->PointEnd;
   PS2 = Shape1->StartPoint;
   PS2 = PointAdd(PS2, -4*f_step,0);
   PE1 = PointSub(PS1, PS2);
   if ( !PointIsNull(PE1) )
   {
      Shape1->ApplyOffset(PE1.x, PE1.y);
   }


   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;
   h1 = (R1.Bottom - R2.Top) + 2*f_step;
   Shape1->ApplyOffset(0, -h1);

   R1 = Shape1->MaxRect;



   s1 = DivTrunc(abs(R1.Right - R1.Left), 2) + R1.Left;
   s2 = DivTrunc(abs(R2.Right - R2.Left), 2) + R2.Left;
   h = abs(s1 - s2);
   if (h && (s1 > s2))
     Shape2->ApplyOffset(h, 0);

   if (h && (s1 < s2))
     Shape1->ApplyOffset(h, 0);

   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;

   h1 = R1.Width();
   h2 = R2.Width();

   if (h1 > h2)
      PE2 =  Shape1->EndPoint;
   else
      PE2 =  Shape2->EndPoint;

   h = PE2.x + f_step - PTail.x;
   if (h != 0)
      Shape3->ApplyOffset(h, 0);


/*
   h1 = ((R1.Bottom - R1.Top) -  (f_Rect1.Bottom - f_Rect1.Top)) - 2*f_step;
   if (h1 > 0)
      Shape1->ApplyOffset(0, -h1);

   h2 = ((R2.Bottom - R2.Top) -  (f_Rect2.Bottom - f_Rect2.Top))/2;
   if (h2 > 0)
      Shape1->ApplyOffset(0, -h2);

   PS1 = Shape1->StartPoint;
   PS2 = Shape2->StartPoint;
   Line = GetIndexLine(1);
   int mx1 = PS1.x - Line->MaxX - 2*f_step;
   int mx2 = PS2.x - Line->MaxX - 2*f_step;
   if (mx1)
     Shape1->ApplyOffset(-mx1, 0);
   if (mx2)
     Shape2->ApplyOffset(-mx2, 0);
   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;
*/

/*
   s1 = DivTrunc(abs(R1.Right - R1.Left), 2) + R1.Left;
   s2 = DivTrunc(abs(R2.Right - R2.Left), 2) + R2.Left;
   h = abs(s1 - s2);
   if (h && (s1 > s2))
     Shape2->ApplyOffset(h, 0);

   if (h && (s1 < s2))
     Shape1->ApplyOffset(h, 0);


   R1 = Shape1->MaxRect;
   R2 = Shape2->MaxRect;

   h1 = R1.Width();
   h2 = R2.Width();

   if ( (f_Rect1.Width() != h1 ) || (f_Rect2.Width() != h2 ) )
   {
      if ( f_Rect1.Width() != h1  )
      {
         h = R1.Right + 2*f_step - PTail.x;
         if (h > 0)
           Shape3->ApplyOffset(h, 0);
      }
      if ( f_Rect2.Width() != h2  )
      {
         h = R2.Right + 2*f_step - PTail.x;
         if (h > 0)
           Shape3->ApplyOffset(h, 0);
      }
   }
   f_Rect1 = R1;
   f_Rect2 = R2;

*/
   //смещаем линии
   PS1 = Shape1->StartPoint;
   PS2 = Shape2->StartPoint;
   PE1 = Shape1->EndPoint;
   PE2 = Shape2->EndPoint;
   Rhomb->GetTailPoint(1, PTail);


   Line = GetIndexLine(0);
   Line->Visible = true;
   Lnb = Line;
   Lnb0 = Lnb;


   Line = GetIndexLine(1);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->End);
   StretchLineY(Line, PS1.y);
   Lnb = Line;


   Line = GetIndexLine(2);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->X0, Lnb->MinY);
   StretchLineX(Line, PS1.x);



   Line = GetIndexLine(3);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(PE1);
   StretchLineX(Line, PTail.x);
   Lnb = Line;


   Line = GetIndexLine(4);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->MaxX, Lnb->Y0);
   StretchLineY(Line, PTail.y);

   Line = GetIndexLine(5);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb0->MinX, Lnb0->Y0);
   StretchLineX(Line, PS2.x);

   Rhomb->GetTailPoint(0, PTail);
   Line = GetIndexLine(6);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(PE2);
   StretchLineX(Line, PTail.x);
   Lnb = Line;

   Line = GetIndexLine(7);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->MaxX, Lnb->Y0);
   StretchLineY(Line, PTail.y);


   Rhomb->GetTailPoint(2, PTail);

   for(int i = 0; i <= f_RCT[5]->Count-1 ; i ++)
   {
      Line = static_cast<TBaseLine*>(f_RCT[5]->Items[i]);
      Line->Visible = true;
      Line->MoveTo(PTail);
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


void TCompositeCycleDoWhileDo::PrepareDrawFlags()
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


TPoint __fastcall TCompositeCycleDoWhileDo::GetEndPoint()
{
   return f_LastLine->End;
}


TPoint __fastcall TCompositeCycleDoWhileDo::GetStartPoint()
{
   return f_FirstLine->Start;
}

TBaseLine* __fastcall TCompositeCycleDoWhileDo::GetEndLine()
{
   return f_LastLine;
}

TRectLine* __fastcall TCompositeCycleDoWhileDo::GetFirstLine()
{
   return f_FirstRectLine;
}


void TCompositeCycleDoWhileDo::MakeFirstLine(TPoint AStart, int ABend)
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



