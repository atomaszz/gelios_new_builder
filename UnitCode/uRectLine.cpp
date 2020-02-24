//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uRectLine.h"
#include "uFlagShape.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
//--------------------------------------------------
TRectLine::TRectLine(int step, int number)
{
   x0 = 0;
   y0 = 0;
   x1 = 0;
   y1 = 0;
   Lines = new TList;
   F_id = number;
   F_bend = 0;
   F_Width = 1;
   F_Color = clBlack;
   F_Style = psSolid;
   F_PenMode = pmCopy;
   F_Step = step;
   F_DrawFlag = false;
   F_FlagColor = clWhite;
   F_FlagType = 1;

   F_DrawFlagS = false;
   F_FlagSColor = clWhite;
   F_FlagSType = 1;

   F_DrawFlagE = false;
   F_FlagEColor = clWhite;
   F_FlagEType = 1;

   f_LEControl = false;
   F_WndHandler = 0;
   F_UnderControl = NULL;

   F_MiddleFlag = NULL;

   FOnRctFlagCreate = NULL;
   FOnRctFlagDestroy = NULL;
   f_CurrentBaseLine = 0;
   f_PaintLine = true;


   for (int i = 0; i <= 2; i++)
   {
     TBaseLine* line;
     line = new TBaseLine(0, 0, 0, 0, F_Step);
     line->OnFlagCreate = &FlagCreate;
     line->OnFlagDestroy = &FlagDestroy;
     line->OnFlagImport = &FlagImport;
     Lines->Add(line);
   }

}

//---------------------------------------------------------
TRectLine::~TRectLine()
{
   FreeLines();
   delete Lines;
}

//--------------------------------------------------------
void TRectLine::FreeLines()
{
   int i;
   TBaseLine *line;
   for (i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      delete line;
      Lines->Delete(i);
   }
}

//--------------------------------------------------------------
void TRectLine::CalcCoord()
{
  TBaseLine *line;
  int midl;
  int t_x0, t_x1, t_y0, t_y1;
  bool m_rev = false;
  InvisibleLines();
//  DrawFlagFalse();

  t_x0 = x0;
  t_x1 = x1;
  t_y0 = y0;
  t_y1 = y1;

  if ((t_x0 > t_x1) && (t_y0 > t_y1))
  {
    t_x0 = x1;
    t_x1 = x0;
    t_y0 = y1;
    t_y1 = y0;
    m_rev = true;
  }

  if ((t_x0 > t_x1) && (t_y0 < t_y1))
  {
    t_x0 = x1;
    t_x1 = x0;
    t_y0 = y1;
    t_y1 = y0;
    m_rev = true;
  }

  if ((t_x0 < t_x1) && (t_y0 < t_y1))
  {
     if (F_bend == 0)
     {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, t_y1);
//     line = new TBaseLine(t_x0, t_y0, t_x0, t_y1, F_Step);
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       //if (F_MiddleFlag)
       //  line->ImportFlag(F_MiddleFlag
       CreateMiddleFlagToLine(line, F_DrawFlag);
//       line->DrawFlag = F_DrawFlag;
       line->ApplyCoord(t_x0, t_y1, t_x1, t_y1);
//     line = new TBaseLine(t_x0, t_y1, t_x1, t_y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);
    }
    if (F_bend == 1)
    {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x1, t_y0);
//     line = new TBaseLine(t_x0, t_y0, t_x1, t_y0, F_Step);
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(t_x1, t_y0, t_x1, t_y1);
//     line = new TBaseLine(t_x1, t_y0, t_x1, t_y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);
    }
    if (F_bend == 2)
    {
       midl = int((t_x1 - t_x0)/2 + t_x0);

       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, midl, t_y0);
//     line = new TBaseLine(t_x0, t_y0, midl, t_y0, F_Step);
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(midl, t_y0, midl, t_y1);
//     line = new TBaseLine(midl, t_y0, midl, t_y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(midl, t_y1, t_x1, t_y1);
//     line = new TBaseLine(midl, t_y1, t_x1, t_y1, F_Step);
//     Lines->Add(line);
    }
    if (F_bend == 3)
    {
       midl = int((t_y1 - t_y0)/2 + t_y0);
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, midl);
//     line = new TBaseLine(t_x0, t_y0, t_x0, midl, F_Step);
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(t_x0, midl, t_x1, midl);
//     line = new TBaseLine(t_x0, midl, t_x1, midl, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(t_x1, midl, t_x1, t_y1);
//     line = new TBaseLine(t_x1, midl, t_x1, t_y1, F_Step);
//     Lines->Add(line);
    }
  }
  if ((t_x1 > t_x0) && (t_y0 > t_y1))
  {

     if (F_bend == 0)
     {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, t_y1);
//     line = new TBaseLine(t_x0, t_y0, t_x0, t_y1, F_Step);
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(t_x0, t_y1, t_x1, t_y1);
//       line = new TBaseLine(t_x0, t_y1, t_x1, t_y1, F_Step);
//       line->DrawFlag = F_DrawFlag;
//       Lines->Add(line);
    }
    if (F_bend == 1)
    {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x1, t_y0);
//       line = new TBaseLine(t_x0, t_y0, t_x1, t_y0, F_Step);
//       Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(t_x1, t_y0, t_x1, t_y1);
//     line = new TBaseLine(t_x1, t_y0, t_x1, t_y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);
    }
    if (F_bend == 2)
    {
       midl = int((t_x1 - t_x0)/2 + t_x0);

       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, midl, t_y0);
//       line = new TBaseLine(t_x0, t_y0, midl, t_y0, F_Step);
//       Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(midl, t_y0, midl, t_y1);
//     line = new TBaseLine(midl, t_y0, midl, t_y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(midl, t_y1, t_x1, t_y1);
//       line = new TBaseLine(midl, t_y1, t_x1, t_y1, F_Step);
//       Lines->Add(line);
    }
    if (F_bend == 3)
    {
       midl = int((t_y0 - t_y1)/2 + t_y1);

       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, midl);
//       line = new TBaseLine(t_x0, t_y0, t_x0, midl, F_Step);
//       Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
//       line->DrawFlag = F_DrawFlag;
       CreateMiddleFlagToLine(line, F_DrawFlag);
       line->ApplyCoord(t_x0, midl, t_x1, midl);
//       line = new TBaseLine(t_x0, midl, t_x1, midl, F_Step);
//       line->DrawFlag = F_DrawFlag;
//       Lines->Add(line);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(t_x1, midl, t_x1, t_y1);
//       line = new TBaseLine(t_x1, midl, t_x1, t_y1, F_Step);
//       Lines->Add(line);
    }

  }

  if ((x0==x1) || (y0==y1))
  {
     line = static_cast<TBaseLine*>(GetBaseLine(0));
     line->Visible = true;
//     line->DrawFlag = F_DrawFlag;
     CreateMiddleFlagToLine(line, F_DrawFlag);
     line->ApplyCoord(x0, y0, x1, y1);

//     line = new TBaseLine(x0, y0, x1, y1, F_Step);
//     line->DrawFlag = F_DrawFlag;
//     Lines->Add(line);
  }
  if (m_rev)
    ReverseLines();

  SetDrawFlagS();
  SetDrawFlagE();
  DoSetLEControl();
  DoSetWndHandler();
  DoSetUnderControl();
}

//------------------------------------------------------------------
void TRectLine::SetCoord(int x0, int y0, int x1, int y1, int bend)
{
   this->x0 = x0;
   this->y0 = y0;
   this->x1 = x1;
   this->y1 = y1;
   this->F_bend = bend;
}


//--------------------------------------------------------
void TRectLine::Prepare()
{
   CalcCoord();
}

//--------------------------------------------------------
void TRectLine::Paint(TCanvas *Canvas)
{
   int i;
   TBaseLine *line;
   if (!f_PaintLine) return;
   SetColorFlagS();
   SetColorFlagE();
   for (i = 0 ; i<=Lines->Count - 1; i++)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->Color = Color;
      line->Width = Width;
      line->Style = Style;
      line->Mode =  Mode;

      line->PaintLine(Canvas);
   }
   for (i = 0 ; i<=Lines->Count - 1; i++)
   {
     line =  static_cast<TBaseLine*>(Lines->Items[i]);
     line->FlagColor = F_FlagColor;
     line->FlagType = F_FlagType;
     line->PaintFlag(Canvas);
   }
}


//--------------------------------------------------------------------
void __fastcall TRectLine::SetBend(int Value)
{
   if ((Value > 3) || (Value < 0))
      F_bend = 0;
   else
     F_bend = Value;
}


//--------------------------------------------------------------------
TPoint __fastcall TRectLine::GetPointStart()
{
   return (TPoint(x0, y0));
}


//------------------------------------------------------------------
TPoint __fastcall TRectLine::GetPointEnd()
{
   return (TPoint(x1, y1));
}

//------------------------------------------------------------------
void __fastcall TRectLine::SetPointStart(TPoint Value)
{
   x0 = Value.x;
   y0 = Value.y;
}


//----------------------------------------------------------------
void __fastcall TRectLine::SetPointEnd(TPoint Value)
{
   x1 = Value.x;
   y1 = Value.y;
}

//----------------------------------------------------------------
void TRectLine::SetDrawFlagS()
{
   int i, res;
   TBaseLine *line;
   line =  static_cast<TBaseLine*>(Lines->Items[0]);
   line->DrawFlagS = F_DrawFlagS;
 //  line->FlagSColor = F_FlagSColor;
   line->FlagSType = F_FlagSType;
}


void TRectLine::SetDrawFlagE()
{
   int i, res;
   TBaseLine *line;
   line =  static_cast<TBaseLine*>(Lines->Items[0]);
   line->DrawFlagE = F_DrawFlagE;
  // line->FlagEColor = F_FlagEColor;
   line->FlagEType = F_FlagEType;
}

//---------------------------------------------------------------------------
void TRectLine::SetColorFlagS()
{
   int i, res;
   TBaseLine *line;
   if (!F_DrawFlagS) return;
   line =  static_cast<TBaseLine*>(Lines->Items[0]);
  // line->FlagSColor = F_FlagSColor;
   line->FlagSType = F_FlagSType;
}

//---------------------------------------------------------------------------
void TRectLine::SetColorFlagE()
{
   int i, res;
   TBaseLine *line;
   if (!F_DrawFlagE) return;
   line =  static_cast<TBaseLine*>(Lines->Items[0]);
  // line->FlagEColor = F_FlagEColor;
   line->FlagEType = F_FlagEType;
}


//---------------------------------------------------------------------------
void __fastcall TRectLine::SetLEControl(bool Value)
{
   if (f_LEControl == Value) return;
   f_LEControl = Value;
}

//---------------------------------------------------------------------------
void __fastcall TRectLine::SetWndHandler(const HWND Value)
{
   if (F_WndHandler == Value) return;
   F_WndHandler = Value;
}


//---------------------------------------------------------------------------
void  TRectLine::DoSetLEControl()
{
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->LEControl = f_LEControl; 
   }
}

//---------------------------------------------------------------------------
void  TRectLine::DoSetWndHandler()
{
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->WndHandler = F_WndHandler;
   }
}

//---------------------------------------------------------------------------
void __fastcall TRectLine::SetUnderControl(TControl* Value)
{
    if (F_UnderControl != Value)
       F_UnderControl = Value;

}

//---------------------------------------------------------------------------
void  TRectLine::DoSetUnderControl()
{
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->UnderControl = F_UnderControl;
   }
}

//---------------------------------------------------------------------------
bool TRectLine::KeepFlag(TBaseShape *Flag, int &type)
{
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      if (line->KeepFlag(Flag, type)) return true;
   }
   return false;
}



//---------------------------------------------------------------------------
TBaseLine* TRectLine::GetBaseLine(int num)
{
   TBaseLine* Res = NULL;
   if ( (num >=0) && (num < Lines->Count) )
      Res =  static_cast<TBaseLine*>(Lines->Items[num]);
   return Res;
}

//---------------------------------------------------------------------------
void TRectLine::InvisibleLines()
{
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->Visible = false;
   }
}

//---------------------------------------------------------------------------
void TRectLine::ReverseLines()
{
   int i, cnt, dln = 0;
   TBaseLine *line, *tmp;
   TPoint S, E;
   for (i = 0; i <= Lines->Count - 1 ; i++)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      if (line->Visible) dln++;
   }
   cnt = int(dln/2);
   for (i = 0; i <= cnt - 1 ; i++)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      tmp = static_cast<TBaseLine*>(Lines->Items[dln - i - 1]);
      S = line->PointStart;
      E = line->PointEnd;
      line->PointStart = tmp->PointEnd;
      line->PointEnd = tmp->PointStart;
      tmp->PointStart = E;
      tmp->PointEnd = S;
   }
}


void __fastcall TRectLine::FlagCreate(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag)
{
    if (APosFlag == 1) F_MiddleFlag = AFlag;
    if (FOnRctFlagCreate) FOnRctFlagCreate(this, AFlag, APosFlag);
}


void __fastcall TRectLine::FlagDestroy(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag)
{
    if (APosFlag == 1) F_MiddleFlag = NULL;
    if (FOnRctFlagDestroy) FOnRctFlagDestroy(this, AFlag, APosFlag);
}

void __fastcall TRectLine::FlagImport(TBaseLine *ASource, TBaseLine *ADest, TFlagShape *AFlag, int APosFlag)
{
   ASource->NilFlag(AFlag);
}


void TRectLine::CreateMiddleFlagToLine(TBaseLine* ALine, bool ADrawFlag)
{
   if (F_MiddleFlag)
   {
     if (ADrawFlag)
        ALine->ImportFlag(F_MiddleFlag, 1, F_MiddleFlag->TypeFlag,
                         F_MiddleFlag->Radius, F_MiddleFlag->BrushColor);
     else
        ALine->DrawFlag = false;
     return;
   }
   else
      ALine->DrawFlag = ADrawFlag;
}


TBaseLine* TRectLine::FirstBaseLine()
{
   TBaseLine* Res;
   f_CurrentBaseLine = 0;
   for (int i = 0; i <= Lines->Count - 1; i++)
   {
      Res =  static_cast<TBaseLine*>(Lines->Items[i]);
      if (Res->Visible)
      {
         f_CurrentBaseLine++;
         return Res;
      }
   }
   return NULL;
}


TBaseLine* TRectLine::NextBaseLine()
{
   TBaseLine* Res;
   for (int i = f_CurrentBaseLine; i <= Lines->Count - 1; i++)
   {
      Res =  static_cast<TBaseLine*>(Lines->Items[i]);
      if (Res->Visible)
      {
            f_CurrentBaseLine++;
            return Res;
      }
   }
   return NULL;
}


void TRectLine::ApplyOffset(int Ax, int Ay)
{
   x0 = x0 + Ax;
   x1 = x1 + Ax;
   y0 = y0 + Ay;
   y1 = y1 + Ay;
}

void __fastcall TRectLine::SetBaseLineColor(TColor AValue)
{
   f_BaseLineColor = AValue;
   TBaseLine *line;
   for (int i = Lines->Count - 1; i>=0; i--)
   {
      line =  static_cast<TBaseLine*>(Lines->Items[i]);
      line->BasePenColor = f_BaseLineColor;
   }

}

