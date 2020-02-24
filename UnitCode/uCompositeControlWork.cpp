//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCompositeControlWork.h"
#include "uTfeRhombShape.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)


TCompositeControlWork::TCompositeControlWork()
{
   f_BWS = NULL;
   f_step = 0;
   f_FirstLine = NULL;
   for (int i = 0; i <= 5; i++)
     f_RCT[i] = new TDynamicArray;
}


TCompositeControlWork::~TCompositeControlWork()
{
   for (int i = 0; i <= 5; i++)
     delete f_RCT[i];
}

bool TCompositeControlWork::ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape1, *mNewShape2;
   TPoint POfs;
   bool res = false;
   if (AWS && (AWS->BaseWorkShape->TypeShape == 4) )
   {
      f_BWS = AWS->BaseWorkShape;
      ConvertedBWS = AWS->BaseWorkShape;
      POfs = f_BWS->OffsetStartPoint();

      mNewShape1 = CloneShape(AWS->ItemTFE[0]->BaseShape);
      AddBaseShape(mNewShape1, AV->IsHaveChildShape(mNewShape1->ID));
      mNewShape2 = CloneShape(AWS->ItemTFE[1]->BaseShape);
      AddBaseShape(mNewShape2, AV->IsHaveChildShape(mNewShape2->ID));

      CreateLines(AWS->BaseWorkShape);
      ApplyOffset(POfs.x, POfs.y);
      f_Rect1 = mNewShape1->GetRect();
      f_R1Width = f_Rect1.Width();
   }
   return res;
}

void TCompositeControlWork::ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV)
{
   TBaseShape *mNewShape1, *mNewShape2, *mNewShape3;
   TPoint POfs;
   if (AWS && (AWS->TypeShape == 4) )
   {
      POfs = AWS->OffsetStartPoint();
      f_BWS = AWS;
      ConvertedBWS = AWS;

      mNewShape1 = CloneShape(AWS->GetWorkShape(0));
      AddBaseShape(mNewShape1, AV->IsHaveChildShape(mNewShape1->ID));
      mNewShape2 = CloneShape(AWS->GetWorkShape(1));
      AddBaseShape(mNewShape2, AV->IsHaveChildShape(mNewShape2->ID));

      CreateLines(AWS);
      ApplyOffset(POfs.x, POfs.y);
   }
}



void TCompositeControlWork::CreateLines(TBaseWorkShape *AWS)
{
   TBaseLine *Line, *Base;
   TRectLine *f_Rct, *l_Rct;
   f_step = AWS->Step;
   int index = 0;
   int cnt = 1;
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
      f_RCT[0]->Append(Line);
      Line->Tag = 1;
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
        index++;
        Base = t_Rct->NextBaseLine();
     }
     cnt++;
   }

   Line = GetBaseLine(index);
   Line->Visible = false;
   m_x0 = 0;
   m_x1 = 0;
   m_y0 = 0;
   m_y1 = 0;
   Line->ApplyCoord(m_x0, m_y0, m_x1, m_y1);
   f_RCT[cnt]->Append(Line);

   Line = GetNewLine();
   f_RCT[4]->Append(Line);


}

TBaseLine* TCompositeControlWork::GetIndexLine(int AIndex)
{
   TBaseLine* Res = NULL;
   switch (AIndex)
   {
      case 0:
        Res =  static_cast<TBaseLine*>(f_RCT[1]->Items[0]);
        break;
      case 1:
        Res =  static_cast<TBaseLine*>(f_RCT[2]->Items[0]);
        break;
      case 2:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[0]);
        break;
      case 3:
        Res =  static_cast<TBaseLine*>(f_RCT[3]->Items[1]);
        break;
      case 4:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[0]);
        break;
      case 5:
        Res =  static_cast<TBaseLine*>(f_RCT[4]->Items[1]);
        break;

   }

   return Res;
}


void TCompositeControlWork::Prepare()
{

   int h, d;
   int s1, s2;
   int x_offs, y_offs;
   int x_offs2, y_offs2;
   TBaseLine *Line, *Lnb, *Lnb2;

   TCompositeBaseWorkItem *Shape1, *Shape2;
   TPoint PS1, PE1, PS2, PE2, PTail;
   HideLines();

   Shape1 = GetItem(0);
   Shape2 = GetItem(1);

   PS1 = f_FirstRectLine->PointEnd;
   PS2 = Shape1->StartPoint;
   PS2 = PointAdd(PS2, -2*f_step,0);
   PE1 = PointSub(PS1, PS2);
   if ( !PointIsNull(PE1) )
   {
      Shape1->ApplyOffset(PE1.x, PE1.y);
   }


   PE1 = Shape1->EndPoint;
   PS2 = Shape2->StartPoint;


  // h = (R1.Right - R1.Left) -  (f_Rect1.Right - f_Rect1.Left) - f_Midl;
  // d = R1.Width() - f_R1Width;
   d = PS2.x - PE1.x - 2*f_step;
   h = 0;//PE1.y - PS2.y;
   Shape2->ApplyOffset(-d, h);

   f_Rect1 = Shape1->MaxRect;
 //  f_Midl = PE1;

   //смещаем линии
   PS1 = Shape1->StartPoint;
   PS2 = Shape2->StartPoint;
   PE1 = Shape1->EndPoint;
   PE2 = Shape2->EndPoint;

   Line = GetIndexLine(0);
   Line->Visible = true;
   Lnb = Line;

   Line = GetIndexLine(1);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(PE1.x , PE1.y );
   StretchLineX(Line, PS2.x);
   Lnb2 = Line;


   Line = GetIndexLine(2);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->MaxX, Lnb->Y0);
   StretchLineY(Line, f_Rect1.Top - 2*f_step);
   Lnb = Line;


   dynamic_cast<TTfeRhombShape*>(Shape2->BaseShape)->GetTailPoint(1, PTail);
   Line = GetIndexLine(3);
   Line->Visible = true;
   Line->ApplyCoord(0, 0, 0, 0);
   Line->MoveTo(Lnb->X0, Lnb->MinY);
   StretchLineX(Line, PTail.x);
   Lnb = Line;


   Line = GetIndexLine(4);
   Line->Visible = true;
   Line->ApplyCoord(Lnb->MaxX, Lnb->MinY, PTail.x, PTail.y);

  dynamic_cast<TTfeRhombShape*>(Shape2->BaseShape)->GetTailPoint(0, PTail);
  Line = GetIndexLine(5);
  Line->Visible = true;
  Line->ApplyCoord(Lnb2->X1, Lnb2->Y0, PTail.x, PTail.y);


   dynamic_cast<TTfeRhombShape*>(Shape2->BaseShape)->GetTailPoint(2, PTail);
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

void TCompositeControlWork::PrepareDrawFlags()
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


TPoint __fastcall TCompositeControlWork::GetEndPoint()
{
   return f_LastLine->End;
}


TPoint __fastcall TCompositeControlWork::GetStartPoint()
{
   return f_FirstLine->Start;
}

TBaseLine* __fastcall TCompositeControlWork::GetEndLine()
{
   return f_LastLine;
}

TRectLine* __fastcall TCompositeControlWork::GetFirstLine()
{
   return f_FirstRectLine;
}


void TCompositeControlWork::MakeFirstLine(TPoint AStart, int ABend)
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



