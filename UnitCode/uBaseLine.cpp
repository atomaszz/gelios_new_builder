//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uBaseLine.h"
#include "uFlagShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TBaseLine::TBaseLine(int x0, int y0, int x1, int y1, int step)
{
   ApplyCoord(x0, y0, x1, y1);
   Pen = new Graphics::TPen;
   OldPenParent = new Graphics::TPen;
   F_Step = step;
   F_Flag = NULL;
   F_FlagS = NULL;
   F_FlagE = NULL;
   F_DrawFlag = false;
   F_DrawFlagS = false;
   F_DrawFlagE = false;

   F_FlagColor = clWhite;
   F_DrawFlagS = false;
   F_FlagSColor = clWhite;
   F_DrawFlagE = false;
   F_FlagEColor = clWhite;

   F_FlagType = 0;
   F_FlagSType = 0;
   F_FlagEType = 0;

   F_FlagRadius = 0.7;
   F_FlagSRadius = 0.7;
   F_FlagERadius = 0.7;

   F_WndHandler = 0;
   F_UnderControl = NULL;
   F_Visible = true;
   FOnFlagCreate = NULL;
   FOnFlagDestroy = NULL;
   FOnFlagImport = NULL;
   f_LEControl = false;
   f_Tag = 0;
   f_Tag2 = 0;
}


//------------------------------------------------------------------------
TBaseLine::~TBaseLine()
{
   delete Pen;
   delete OldPenParent;
   if (F_Flag)
     delete F_Flag;
   if (F_FlagS)
     delete F_FlagS;
   if (F_FlagE)
     delete F_FlagE;
}


//--------------------------------------------------------------------
void TBaseLine::Paint(TCanvas *Canvas)
{
   TPoint p0, p1, p2, p3, Center;
   if (!F_Visible) return;
   OldPenParent->Assign(Canvas->Pen);
   Canvas->Pen->Assign(this->Pen);
   if (F_DrawFlag && F_Flag)
   {
      F_Flag->TypeFlag = F_FlagType;
      F_Flag->PenWidth = Width;
      F_Flag->PenColor = Color;
      F_Flag->Radius = F_FlagRadius; 
   }
   if (F_DrawFlagS && F_FlagS)
   {
      F_FlagS->TypeFlag = F_FlagSType;
      F_FlagS->PenWidth = Width;
      F_FlagS->PenColor = Color;
      F_FlagS->Radius = F_FlagSRadius;
   }
   if (F_DrawFlagE && F_FlagE)
   {
      F_FlagE->TypeFlag = F_FlagEType;
      F_FlagE->PenWidth = Width;
      F_FlagE->PenColor = Color;
      F_FlagE->Radius = F_FlagERadius;
   }
   DrawLinesAndFlag(Canvas);
   Canvas->Pen->Assign(OldPenParent);
}

//---------------------------------------------------------------------
void __fastcall TBaseLine::SetPenColor(TColor Value)
{
   Pen->Color = Value;
}

//------------------------------------------------------------------------
void __fastcall TBaseLine::SetPenWidth(int Value)
{
   Pen->Width = Value;
}

//--------------------------------------------------------------------
void __fastcall TBaseLine::SetPenStyle(TPenStyle  Value)
{
   Pen->Style = Value;
}


//---------------------------------------------------------------------
TColor __fastcall TBaseLine::GetPenColor()
{
   return Pen->Color;
}

//----------------------------------------------------------------------
int __fastcall    TBaseLine::GetPenWidth()
{
   return Pen->Width;
}


//--------------------------------------------------------------------
TPenStyle __fastcall TBaseLine::GetPenStyle()
{
   return Pen->Style;
}


//----------------------------------------------------------------------
int  __fastcall TBaseLine::GetTypeLine()
{
   int res = BL_OTHER;
   if (x0 == x1)
     res =  BL_VERTICAL;
   if (y0 == y1)
     res = BL_HORIZONTAL;
   if ((y0 == y1) && (x0 == x1))
     res = BL_POINT;
   return res;
}


//---------------------------------------------------------------------------
TPoint __fastcall TBaseLine::GetPointStart()
{
   return (TPoint(x0, y0));
}


//------------------------------------------------------------------
TPoint __fastcall TBaseLine::GetPointEnd()
{
   return (TPoint(x1, y1));
}


//------------------------------------------------------------------
void __fastcall TBaseLine::SetPointStart(TPoint Value)
{
   x0 = Value.x;
   y0 = Value.y;
}


//----------------------------------------------------------------
void __fastcall TBaseLine::SetPointEnd(TPoint Value)
{
   x1 = Value.x;
   y1 = Value.y;
}


//------------------------------------------------------------------
void __fastcall TBaseLine::SetPenMode(TPenMode  Value)
{
   Pen->Mode = Value;
}


//-----------------------------------------------------------------
TPenMode __fastcall TBaseLine::GetPenMode()
{
   return  Pen->Mode;
}

//-----------------------------------------------------------------
void  __fastcall TBaseLine::SetDrawFlag(bool Value)
{
   int pos = 1;
   F_DrawFlag = Value;
   if (F_DrawFlag && (!F_Flag))
   {
      F_Flag =  new TFlagShape(F_Step, this, 0);
      F_Flag->LEControl = true;
      F_Flag->WndHandler = F_WndHandler;
      F_Flag->BrushColor = F_FlagColor;
      if (FOnFlagCreate) OnFlagCreate(this, F_Flag, pos);
   }

   if ((!F_DrawFlag) && F_Flag)
   {
      if (FOnFlagDestroy) OnFlagDestroy(this, F_Flag, pos);
      delete F_Flag;
      F_Flag = NULL;
   }

}

//-----------------------------------------------------------------
void  __fastcall TBaseLine::SetDrawFlagS(bool Value)
{
   int pos = 0;
   F_DrawFlagS = Value;
   if (F_DrawFlagS && (!F_FlagS))
   {
      F_FlagS =  new TFlagShape(F_Step, this, 0);
      F_FlagS->LEControl = true;
      F_FlagS->WndHandler = F_WndHandler;
      if (FOnFlagCreate) OnFlagCreate(this, F_FlagS, pos);
   }

   if ((!F_DrawFlagS) && F_FlagS)
   {
      if (FOnFlagDestroy) OnFlagDestroy(this, F_FlagS, pos);
      delete F_FlagS;
      F_FlagS = NULL;
   }

}

//-----------------------------------------------------------------
void  __fastcall TBaseLine::SetDrawFlagE(bool Value)
{
   int pos = 2;
   F_DrawFlagE = Value;
   if (F_DrawFlagE && (!F_FlagE))
   {
      F_FlagE =  new TFlagShape(F_Step, this, 0);
      F_FlagE->LEControl = true;
      F_FlagE->WndHandler = F_WndHandler;
      F_FlagE->BrushColor = F_FlagEColor;
      if (FOnFlagCreate) OnFlagCreate(this, F_FlagE, pos);
   }

   if ((!F_DrawFlagE) && F_FlagE)
   {
      if (FOnFlagDestroy) OnFlagDestroy(this, F_FlagE, pos);
      delete F_FlagE;
      F_FlagE = NULL;
   }

}


//-----------------------------------------------------------------
bool TBaseLine::GetCoordLines(TPoint &p0, TPoint &p1, TPoint &p2, TPoint &p3, TPoint &Center)
{
   int cnt;
   int xd, yd;
   int x_start, x_end, y_start, y_end;
//   bool res = false;
   p0 = TPoint(0,0);
   p1 = TPoint(0,0);
   p2 = TPoint(0,0);
   p3 = TPoint(0,0);
   cnt = int(F_Flag->Radius*F_Step);
   xd = abs(int((x1-x0)/2));
   yd = abs(int((y1-y0)/2));
   if (y0 == y1)
   {
      if (x0 == x1) return false;
	  x_start = std::min(x0, x1);
      x_end = x_start + xd - cnt;
      p0 = TPoint(x_start, y0);
      p1 = TPoint(x_end, y0);

      Center = TPoint(x_end + cnt, y0);

      x_start = x_end + 2*cnt;
      x_end = x_start + xd - cnt;
      p2 = TPoint(x_start, y0);
      p3 = TPoint(x_end, y0);

   }
   if (x0 == x1)
   {
      if (y0 == y1) return false;
	  y_start = std::min(y0, y1);
      y_end = y_start + yd - cnt;
      p0 = TPoint(x1, y_start);
      p1 = TPoint(x1, y_end);

      Center = TPoint(x0, y_end + cnt);

      y_start = y_end + 2*cnt;
      y_end = y_start + yd - cnt;
      p2 = TPoint(x1, y_start);
      p3 = TPoint(x1, y_end);
   }
   return true;
}

//-------------------------------------------------------------------------
void TBaseLine::DrawLinesAndFlag(TCanvas *Canvas)
{
   TPoint m_s(x0, y0), m_e(x1, y1), m_1(0, 0), m_2(0, 0), temp1, temp2, temp3, temp4, center;
   TPoint center_S, center_C, center_E;
   bool p_c, p_s, p_e;
   p_c = p_s = p_e = false;
   if (F_FlagS)
   {
        if ( GetCoordLinesStart(temp1, center) )
        {
           m_s = temp1;
           p_s = true;
           center_S =  center;
        }
   }
   if (F_Flag)
   {
     if ( GetCoordLines(temp1, temp2, temp3, temp4,  center) )
     {
        m_1 = temp2;
        m_2 = temp3;
        p_c = true;
        center_C =  center;
     }
   }
   if (F_FlagE)
   {

      if ( GetCoordLinesEnd(temp1, center) )
      {
         m_e = temp1;
         p_e = true;
         center_E =  center;
      }
   }

   Canvas->MoveTo(m_s.x, m_s.y);
   if (F_Flag)
   {
      Canvas->LineTo(m_1.x, m_1.y);
      Canvas->MoveTo(m_2.x, m_2.y);
   }
   Canvas->LineTo(m_e.x, m_e.y);
   if (p_s)
   {
     F_FlagS->Center = center_S;
     F_FlagS->Paint(Canvas);
   } else if(F_FlagS) F_FlagS->Paint(Canvas);
   if (p_c)
   {
     F_Flag->Center = center_C;
    // F_Flag->BrushColor = F_FlagColor;
     F_Flag->Paint(Canvas);
   } else if(F_Flag) F_Flag->Paint(Canvas);
   if (p_e)
   {
     F_FlagE->Center = center_E;
    // F_FlagE->BrushColor = F_FlagEColor;
     F_FlagE->Paint(Canvas);
   } else if(F_FlagE) F_FlagE->Paint(Canvas);

}


//-------------------------------------------------------------------------
bool TBaseLine::GetCoordLinesStart(TPoint &p, TPoint &Center)
{
   int cnt;
   int x_start, y_start;
   p = TPoint(0,0);
   Center = TPoint(0,0);
   cnt = int(F_FlagS->Radius*F_Step);

   if (y0 == y1)
   {
      if (x0 == x1)
         return false;
      if (x0 <= x1)
      {
        x_start = x0 + cnt*2;
        Center = TPoint(x_start - cnt, y0);
      }
      else
      {
        x_start = x0 - cnt*2;
        Center = TPoint(x_start + cnt, y0);
      }
      p = TPoint(x_start, y0);
   }
   if (x0 == x1)
   {
      if (y0 == y1)
         return false;
      if (y0 <= y1)
      {
         y_start = y0 + cnt*2;
         Center = TPoint(x0, y_start - cnt);
      }
      else
      {
         y_start = y0 - cnt*2;
         Center = TPoint(x0, y_start + cnt);
      }
      p = TPoint(x0, y_start);
   }
   return true;
}

//-------------------------------------------------------------------------
bool TBaseLine::GetCoordLinesEnd(TPoint &p, TPoint &Center)
{
   int cnt;
   int x_end, y_end;
   p = TPoint(0,0);
   Center = TPoint(0,0);
   cnt = int(F_FlagE->Radius*F_Step);
   if (y0 == y1)
   {
      if (x0 == x1) return false;
      if (x0 <= x1)
      {
        x_end = x1 - cnt*2;
        Center = TPoint(x_end + cnt, y1);
      }
      else
      {
        x_end = x1 + cnt*2;
        Center = TPoint(x_end - cnt, y1);
      }
      p = TPoint(x_end, y1);
   }
   if (x0 == x1)
   {
      if (y0 == y1) return false;
      if (y0 <= y1)
      {
        y_end = y1 - cnt*2;
        Center = TPoint(x1, y_end + cnt);
      }
      else
      {
        y_end = y1 + cnt*2;
        Center = TPoint(x1, y_end - cnt);
      }

      p =TPoint(x1, y_end);
   }
   return true;
}


//-------------------------------------------------------------------------
TPoint __fastcall TBaseLine::GetStart()
{
   return TPoint(x0,y0);
}

//-------------------------------------------------------------------------
TPoint __fastcall TBaseLine::GetEnd()
{
   return TPoint(x1, y1);
}

//-------------------------------------------------------------------------
int TBaseLine::CompareToPoint(TPoint P)
{
   if ( (x0 != P.x) && (x1 != P.x)) return 0;
   if ( (y0 != P.y) && (y1 != P.y)) return 0;
   if (x0 == x1)
   {
      if  (y0 == P.y) return 1;
        else return -1;
   }
   if (y0 == y1)
   {
      if  (x0 == P.x) return 1;
        else return -1;
   }
   return -2; //такого не дб
}


//-------------------------------------------------------------------------
void TBaseLine::PaintLine(TCanvas *Canvas)
{
   TPoint p0, p1, p2, p3, Center;
   if (!F_Visible) return;
   OldPenParent->Assign(Canvas->Pen);
   Canvas->Pen->Assign(this->Pen);
   Canvas->MoveTo(x0, y0);
   Canvas->LineTo(x1, y1);
   Canvas->Pen->Assign(OldPenParent);
}


void TBaseLine::PaintFlag(TCanvas *Canvas)
{
   TPoint temp1, temp2, temp3, temp4, center;
   TPoint center_S, center_C, center_E;
   bool p_c, p_s, p_e;
   p_c = p_s = p_e = false;

   if (F_DrawFlag && F_Flag)
   {
      F_Flag->TypeFlag = F_FlagType;
      F_Flag->PenWidth = Width;
      F_Flag->PenColor = Color;
      F_Flag->Radius = F_FlagRadius;
   }
   if (F_DrawFlagS && F_FlagS)
   {
      F_FlagS->TypeFlag = F_FlagSType;
      F_FlagS->PenWidth = Width;
      F_FlagS->PenColor = Color;
      F_FlagS->Radius = F_FlagSRadius;
   }
   if (F_DrawFlagE && F_FlagE)
   {
      F_FlagE->TypeFlag = F_FlagEType;
      F_FlagE->PenWidth = Width;
      F_FlagE->PenColor = Color;
      F_FlagE->Radius = F_FlagERadius;
   }


   if (F_FlagS)
   {
      if ( GetCoordLinesStart(temp1, center) )
      {
         p_s = true;
         center_S =  center;
      }
   }
   if (F_Flag)
   {
     if ( GetCoordLines(temp1, temp2, temp3, temp4,  center) )
     {
        p_c = true;
        center_C =  center;
     }
   }
   if (F_FlagE)
   {
      if ( GetCoordLinesEnd(temp1, center) )
      {
         p_e = true;
         center_E =  center;
      }
   }

   if (p_s)
   {
     F_FlagS->Center = center_S;
     F_FlagS->Paint(Canvas);
   }
   if (p_c)
   {
     F_Flag->Center = center_C;
     F_Flag->Paint(Canvas);
   }
   if (p_e)
   {
     F_FlagE->Center = center_E;
     F_FlagE->Paint(Canvas);
   }

}

void __fastcall TBaseLine::SetLEControl(bool Value)
{
   f_LEControl = Value;
   if (F_Flag)
      if (F_Flag->LEControl != f_LEControl) F_Flag->LEControl = f_LEControl;
   if (F_FlagS)
      if (F_FlagS->LEControl != f_LEControl) F_FlagS->LEControl = f_LEControl;
   if (F_FlagE)
      if (F_FlagE->LEControl != f_LEControl) F_FlagE->LEControl = f_LEControl;
}


void __fastcall TBaseLine::SetWndHandler(const HWND Value)
{
   F_WndHandler = Value;
   if (F_Flag)
     if (F_Flag->WndHandler != F_WndHandler)  F_Flag->WndHandler = F_WndHandler;
   if (F_FlagS)
     if (F_FlagS->WndHandler != F_WndHandler)  F_FlagS->WndHandler = F_WndHandler;
   if (F_FlagE)
     if (F_FlagE->WndHandler != F_WndHandler)  F_FlagE->WndHandler = F_WndHandler;

}

void __fastcall TBaseLine::SetUnderControl(TControl* Value)
{
   F_UnderControl = Value;
   if (F_Flag)
     if(F_Flag->UnderControl != F_UnderControl) F_Flag->UnderControl = F_UnderControl;
   if (F_FlagS)
     if(F_FlagS->UnderControl != F_UnderControl) F_FlagS->UnderControl = F_UnderControl;
   if (F_FlagE)
     if(F_FlagE->UnderControl != F_UnderControl) F_FlagE->UnderControl = F_UnderControl;
}


/*
void TBaseLine::DoSetParentWindow()
{
    if (F_Flag)
       F_Flag->ParentWindow = F_ParentWindow;
    if (F_FlagS)
       F_FlagS->ParentWindow = F_ParentWindow;
    if (F_FlagE)
       F_FlagE->ParentWindow = F_ParentWindow;

}
*/

/*
void TBaseLine::DoSetWndHandler()
{
    if (F_Flag)
       F_Flag->WndHandler = F_WndHandler;
    if (F_FlagS)
       F_FlagS->WndHandler = F_WndHandler;
    if (F_FlagE)
       F_FlagE->WndHandler = F_WndHandler;
}
*/

/*
void TBaseLine::DoSetUnderControl()
{
    if (F_Flag)
       F_Flag->UnderControl = F_UnderControl;
    if (F_FlagS)
       F_FlagS->UnderControl = F_UnderControl;
    if (F_FlagE)
       F_FlagE->UnderControl = F_UnderControl;
} */



bool TBaseLine::KeepFlag(TBaseShape *Flag, int &type)
{
   type = -1;
   if (Flag == (TBaseShape*)F_FlagS) type = 0;
   if (Flag == (TBaseShape*)F_Flag) type = 1;
   if (Flag == (TBaseShape*)F_FlagE) type = 2;
   return (type != -1);

}

void TBaseLine::ApplyCoord(int x0, int y0, int x1, int y1)
{
   this->x0 = x0;
   this->y0 = y0;
   this->x1 = x1;
   this->y1 = y1;
}

void TBaseLine::ApplyOffset(int Ax, int Ay)
{
   x0 = x0 + Ax;
   x1 = x1 + Ax;
   y0 = y0 + Ay;
   y1 = y1 + Ay;
}

void TBaseLine::MoveTo(int Ax, int Ay)
{
   int m_x = Ax - x0;
   int m_y = Ay - y0;
   ApplyOffset(m_x, m_y);
}

void TBaseLine::MoveTo(TPoint APoint)
{
   MoveTo(APoint.x, APoint.y);
}



bool TBaseLine::ImportFlag(TFlagShape *AFlag, int APos, int ATypeFlag,
   double ARadius, TColor ABrushColor)
{
   if ((APos > 2) || (APos < 0) )  return false;
   if (!AFlag) return false;

   if ( APos == 0 )
   {
       if (F_FlagS == AFlag) return true;
       if (F_FlagS)
         delete F_FlagS;
       F_FlagS = AFlag;
       F_FlagSType = ATypeFlag;
       F_FlagSRadius = ARadius;
      // F_FlagSColor = ABrushColor;
       if (FOnFlagImport)  OnFlagImport(AFlag->Owner, this, AFlag, 0);
       AFlag->Owner = this;
   }

   if ( APos == 1 )
   {
       if (F_Flag == AFlag) return true;
       if (F_Flag)
          delete F_Flag;
       F_Flag = AFlag;
       F_FlagType = ATypeFlag;
       F_FlagRadius = ARadius;
       F_FlagColor = ABrushColor;
       if (FOnFlagImport)  OnFlagImport(AFlag->Owner, this, AFlag, 1);
       AFlag->Owner = this;
   }

   if ( APos == 2 )
   {
       if (F_FlagE == AFlag) return true;
       if (F_FlagE)
         delete F_FlagE;
       F_FlagE = AFlag;
       F_FlagEType = ATypeFlag;
       F_FlagERadius = ARadius;
       F_FlagEColor = ABrushColor;
       if (FOnFlagImport)  OnFlagImport(AFlag->Owner, this, AFlag, 2);
       AFlag->Owner = this;
   }
   return true;
}


int TBaseLine::NilFlag(TFlagShape* AFlag)
{
   if (!AFlag) return -1;
   if ( AFlag == F_FlagS )
   {
      F_FlagS = NULL;
      F_DrawFlagS = false;
      return 0;
   }
   if ( AFlag == F_Flag )
   {
      F_Flag = NULL;
      F_DrawFlag = false;
      return 1;
   }
   if ( AFlag == F_FlagE )
   {
      F_FlagE = NULL;
      F_DrawFlagE = false;
      return 2;
   }
    return -1;
}


void __fastcall TBaseLine::SetFlagColor(TColor Value)
{
    F_FlagColor = Value;
//    if (F_Flag)
//      F_Flag->BrushColor = F_FlagColor;
}


void __fastcall TBaseLine::SetFlagSColor(TColor Value)
{
    F_FlagSColor = Value;
}


void __fastcall TBaseLine::SetFlagEColor(TColor Value)
{
    F_FlagEColor = Value;
//    if (F_FlagE)
//      F_FlagE->BrushColor = F_FlagEColor;
}

bool TBaseLine::CopyObject(TBaseLine *ASource)
{
   ASource->F_Step = F_Step;
   ASource->ApplyCoord(x0, y0, x1, y1);
   ASource->Pen->Assign(Pen);
   ASource->BasePenColor = f_BasePenColor;
   ASource->Pen->Color = f_BasePenColor;
   ASource->OldPenParent->Assign(OldPenParent);
   return true;
}


int  __fastcall TBaseLine::GetMinX()
{
   return std::min(x0, x1);
}


int  __fastcall TBaseLine::GetMinY()
{
   return std::min(y0, y1);
}

int  __fastcall TBaseLine::GetMaxX()
{
   return std::max(x0, x1);
}


int  __fastcall TBaseLine::GetMaxY()
{
   return std::max(y0, y1);
}


/*

bool TBaseLine::NilFlag(int APos, TFlagShape *AFlag)
{
    if ((APos > 2) || (APos < 0 ) ) return false;
    if (APos == 0)
    {
       if ((AFlag) && (F_FlagS != AFlag)) return false;
       F_FlagS = NULL;
    }
    if (APos == 1)
    {
       if ((AFlag) && (F_Flag != AFlag)) return false;
       F_Flag = NULL;
    }
    if (APos == 2)
    {
       if ((AFlag) && (F_FlagE != AFlag)) return false;
       F_FlagE = NULL;
    }
    return true;
}
*/
