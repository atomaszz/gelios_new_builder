//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufSetup.h"
#include "ucommonGraph.h"
#include "uGLSSmallFontsDefence.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFmSetup *FmSetup;

bool CheckNumber(AnsiString S)
{
   if (S.Length() == 0) return false;
   for (int i = 1 ; i <= S.Length(); i++)
   {
     if( (S[i] < '0') || (S[i] > '9') )
     return false;
   }
   return true;
}

//---------------------------------------------------------------------------
__fastcall TFmSetup::TFmSetup(TComponent* Owner)
        : TForm(Owner)
{
   TGLSSmallFontsDefence* F = new TGLSSmallFontsDefence(this);
   F->Update();
   delete F;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetStepPixel(int Value)
{
   if (f_StepPixel != Value)
   {
       f_StepPixel = Value;
       edStepPixel->Text = IntToStr(f_StepPixel);
   }
}

void __fastcall TFmSetup::SetPaintPixels(bool Value)
{
   if (f_PaintPixels != Value)
   {
      f_PaintPixels = Value;
      cbPaintPixels->Checked = f_PaintPixels;
   }
}

void __fastcall TFmSetup::SetFonColor(TColor Value)
{
   if (f_FonColor != Value)
   {
       f_FonColor = Value;
       shpFon->Brush->Color = f_FonColor;
   }
}

void __fastcall TFmSetup::SetPixelColor(TColor Value)
{
   if (f_PixelColor != Value)
   {
       f_PixelColor = Value;
       shpPixel->Brush->Color = f_PixelColor;
   }
}


void __fastcall TFmSetup::SetDrawFrameLine(bool Value)
{
    if (f_DrawFrameLine != Value)
    {
        f_DrawFrameLine = Value;
        cbDrawFrameLine->Checked = f_DrawFrameLine;
    }
}

void __fastcall TFmSetup::edStepPixelExit(TObject *Sender)
{
   if ( ! CheckNumber(Trim(edStepPixel->Text)) )
   {
	  Application->MessageBox(_T("Íåîáõîäèìî ââåñòè öåëîå ÷èñëî!"), _T("ÃÝÑ Èíòåëëåêò-3"), MB_ICONWARNING);
      edStepPixel->SetFocus();
      return;
   }
   f_StepPixel =  StrToInt(Trim(edStepPixel->Text));
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::cbPaintPixelsClick(TObject *Sender)
{
   f_PaintPixels = cbPaintPixels->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpFonMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = FonColor;
       if ( CDG->Execute() )
         FonColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpPixelMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = PixelColor;
       if ( CDG->Execute() )
         PixelColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::FormShow(TObject *Sender)
{
    shpPixel->Brush->Color = f_PixelColor;
    shpFon->Brush->Color = f_FonColor;
    shpFrameLineColor->Brush->Color = f_FrameLineColor;
    cbPaintPixels->Checked = f_PaintPixels;
    cbDrawFrameLine->Checked = f_DrawFrameLine;
    edStepPixel->Text = IntToStr(f_StepPixel);
    cbBoldTFELine->Checked = f_BoldTFELine;
    shpLineColor->Brush->Color = f_LineColor;
    shpBrushColor->Brush->Color = f_BrushColor;
    cbBrushTFE->Checked = f_BrushTFE;
    cbxFlagType->ItemIndex = f_FlagType;
    shpColorEnter->Brush->Color = f_ColorEnter;
    shpColorLeave->Brush->Color = f_ColorLeave;
    shpFrameColorTFE->Brush->Color = f_FrameColorTFE;
    shpFrameColorTFS->Brush->Color = f_FrameColorTFS;
    shpHaveChildColor->Brush->Color = f_HaveChildColor;
    shpAltFlagColor->Brush->Color = f_AltFlagColor;
    shpAltEnterFlagColor->Brush->Color = f_AltEnterFlagColor;
    shpAltArrowColor->Brush->Color = f_AltArrowColor;
    shpAltEnterArrowColor->Brush->Color = f_AltEnterArrowColor;
    shpAltLineColor->Brush->Color = f_AltLineColor;
    cbCanModifyPenWidth->Checked = f_CanModifyPenWidth;
    shpAltEnabledFlagColor->Brush->Color = f_AltEnabledFlagColor;
    shpAltParamLineColor->Brush->Color = f_AltParamLineColor;
    shpAltParamShapeColor->Brush->Color = f_AltParamShapeColor;
    cbAltParamShapeColorEnable->Checked = f_AltParamShapeColorEnable;
    shpVwColorAlt->Brush->Color = f_VwColorAlt;
    shpVwColorBadAlt->Brush->Color = f_VwColorBadAlt;
	InitActions();
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::cbDrawFrameLineClick(TObject *Sender)
{
   f_DrawFrameLine = cbDrawFrameLine->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetBoldTFELine(bool Value)
{
    if (f_BoldTFELine != Value)
    {
        f_BoldTFELine = Value;
        cbBoldTFELine->Checked = f_BoldTFELine;
    }
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::cbBoldTFELineClick(TObject *Sender)
{
   f_BoldTFELine = cbBoldTFELine->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetFrameLineColor(TColor Value)
{
   if (f_FrameLineColor != Value)
   {
       f_FrameLineColor = Value;
       shpFrameLineColor->Brush->Color = f_FrameLineColor;
   }
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::shpFrameLineColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = FonColor;
       if ( CDG->Execute() )
         FrameLineColor = CDG->Color;
    }

}

//---------------------------------------------------------------------------

void __fastcall TFmSetup::FormCreate(TObject *Sender)
{
   f_FontTFE = new Graphics::TFont;
   cbKey->Visible = false;
   cbMenu->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::FormDestroy(TObject *Sender)
{
   delete  f_FontTFE;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::pbFontPaint(TObject *Sender)
{
  pbFont->Font->Assign(f_FontTFE);
  DrawEdge(pbFont->Canvas->Handle, &(pbFont->ClientRect), EDGE_SUNKEN, BF_RECT);
  DrawText(pbFont->Canvas->Handle,
	 _T("123"), -1, &(pbFont->ClientRect), DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::btFontClick(TObject *Sender)
{
   FDG->Font->Assign(f_FontTFE);
   if (FDG->Execute())
   {
      f_FontTFE->Assign(FDG->Font);
      pbFont->Invalidate();
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetLineColor(TColor Value)
{
   if (f_LineColor != Value)
   {
      f_LineColor = Value;
      shpLineColor->Brush->Color = f_LineColor;
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetBrushColor(TColor Value)
{
   if (f_BrushColor != Value)
   {
      f_BrushColor = Value;
      shpBrushColor->Brush->Color = f_BrushColor;
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetBrushTFE(bool Value)
{
   if (f_BrushTFE != Value)
   {
      f_BrushTFE = Value;
      cbBrushTFE->Checked = f_BrushTFE;
   }
}


void __fastcall TFmSetup::shpLineColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = LineColor;
       if ( CDG->Execute() )
         LineColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpBrushColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = BrushColor;
       if ( CDG->Execute() )
         BrushColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::cbBrushTFEClick(TObject *Sender)
{
  f_BrushTFE = cbBrushTFE->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetFontTFE(Graphics::TFont* Value)
{
   f_FontTFE->Assign(Value);
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetFlagType(int Value)
{
   f_FlagType = Value;
   cbxFlagType->ItemIndex = f_FlagType;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::cbxFlagTypeChange(TObject *Sender)
{
   f_FlagType = cbxFlagType->ItemIndex;
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetColorLeave(TColor Value)
{
   if (f_ColorLeave != Value)
   {
      f_ColorLeave = Value;
      shpColorLeave->Brush->Color = f_ColorLeave;
   }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetColorEnter(TColor Value)
{
   if (f_ColorEnter != Value)
   {
      f_ColorEnter = Value;
      shpColorEnter->Brush->Color = f_ColorEnter;
   }
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::shpColorLeaveMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = ColorLeave;
       if ( CDG->Execute() )
         ColorLeave = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpColorEnterMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = ColorEnter;
       if ( CDG->Execute() )
         ColorEnter = CDG->Color;
    }

}
//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetFrameColorTFE(TColor Value)
{
   if (f_FrameColorTFE != Value)
   {
      f_FrameColorTFE = Value;
      shpFrameColorTFE->Brush->Color = f_FrameColorTFE;
   }
}


//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpFrameColorTFEMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = FrameColorTFE;
       if ( CDG->Execute() )
         FrameColorTFE = CDG->Color;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetFrameColorTFS(TColor Value)
{
   if (f_FrameColorTFS != Value)
   {
      f_FrameColorTFS = Value;
      shpFrameColorTFS->Brush->Color = f_FrameColorTFS;
   }
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::shpFrameColorTFSMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = FrameColorTFS;
       if ( CDG->Execute() )
         FrameColorTFS = CDG->Color;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetHaveChildColor(TColor Value)
{
   if (f_HaveChildColor != Value)
   {
      f_HaveChildColor = Value;
      shpHaveChildColor->Brush->Color = f_HaveChildColor;
   }
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::shpHaveChildColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = HaveChildColor;
       if ( CDG->Execute() )
         HaveChildColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetAltFlagColor(TColor Value)
{
   if (f_AltFlagColor != Value)
   {
      f_AltFlagColor = Value;
      shpAltFlagColor->Brush->Color = f_AltFlagColor;
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetAltEnterFlagColor(TColor Value)
{
   if (f_AltEnterFlagColor != Value)
   {
      f_AltEnterFlagColor = Value;
      shpAltEnterFlagColor->Brush->Color = f_AltEnterFlagColor;
   }
}

//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetAltArrowColor(TColor Value)
{
   if (f_AltArrowColor != Value)
   {
      f_AltArrowColor = Value;
      shpAltArrowColor->Brush->Color = f_AltArrowColor;
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetAltEnterArrowColor(TColor Value)
{
   if (f_AltEnterArrowColor != Value)
   {
      f_AltEnterArrowColor = Value;
      shpAltEnterArrowColor->Brush->Color = f_AltEnterArrowColor;
   }
}


//---------------------------------------------------------------------------
void __fastcall TFmSetup::SetAltLineColor(TColor Value)
{
   if (f_AltLineColor != Value)
   {
      f_AltLineColor = Value;
      shpAltLineColor->Brush->Color = f_AltLineColor;
   }
}



void __fastcall TFmSetup::shpAltFlagColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltFlagColor;
       if ( CDG->Execute() )
         AltFlagColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpAltEnterFlagColorMouseU(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltEnterFlagColor;
       if ( CDG->Execute() )
         AltEnterFlagColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpAltArrowColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltArrowColor;
       if ( CDG->Execute() )
         AltArrowColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpAltEnterArrowColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltEnterArrowColor;
       if ( CDG->Execute() )
         AltEnterArrowColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpAltLineColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltLineColor;
       if ( CDG->Execute() )
         AltLineColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::SetCanModifyPenWidth(bool Value)
{
    if (f_CanModifyPenWidth != Value)
    {
        f_CanModifyPenWidth = Value;
        cbCanModifyPenWidth->Checked = f_CanModifyPenWidth;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFmSetup::cbCanModifyPenWidthClick(TObject *Sender)
{
    f_CanModifyPenWidth = cbCanModifyPenWidth->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::BitBtn1Click(TObject *Sender)
{
   edStepPixelExit(NULL);
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetHelpUrl(AnsiString AHelpUrl)
{
   f_HelpUrl = AHelpUrl;
   edHelp->Text = f_HelpUrl;
}

void __fastcall TFmSetup::btHelpClick(TObject *Sender)
{
  bool ex;
  AnsiString S = GetHelpFile(edHelp->Text, ex);
  OPD->FileName = S;
  if (OPD->Execute())
    HelpUrl = OPD->FileName;

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::btHelpDefaultClick(TObject *Sender)
{
   HelpUrl = "<programm>help\\index.html";
}
//---------------------------------------------------------------------------



void __fastcall TFmSetup::edHelpExit(TObject *Sender)
{
  bool ex;
  AnsiString S = GetHelpFile(edHelp->Text, ex);
  if (ex)
    HelpUrl = S;
  else
    HelpUrl = "<programm>help\\index.html";

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetAltEnabledFlagColor(TColor Value)
{
   if (f_AltEnabledFlagColor != Value)
   {
       f_AltEnabledFlagColor = Value;
       shpAltEnabledFlagColor->Brush->Color = f_AltEnabledFlagColor;
   }
}


void __fastcall TFmSetup::shpAltEnabledFlagColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltLineColor;
       if ( CDG->Execute() )
         AltEnabledFlagColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetAltParamLineColor(TColor Value)
{
   if (f_AltParamLineColor != Value)
   {
       f_AltParamLineColor = Value;
       shpAltParamLineColor->Brush->Color = f_AltParamLineColor;
   }
}

void __fastcall TFmSetup::SetAltParamShapeColor(TColor Value)
{
   if (f_AltParamShapeColor != Value)
   {
       f_AltParamShapeColor = Value;
       shpAltParamShapeColor->Brush->Color = f_AltParamShapeColor;
   }
}

void __fastcall TFmSetup::SetAltParamShapeColorEnable(bool Value)
{
   if (f_AltParamShapeColorEnable != Value)
   {
      f_AltParamShapeColorEnable = Value;
      cbAltParamShapeColorEnable->Checked = f_AltParamShapeColorEnable;
   }
}


void __fastcall TFmSetup::shpAltParamLineColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltParamLineColor;
       if ( CDG->Execute() )
         AltParamLineColor = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpAltParamShapeColorMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = AltParamShapeColor;
       if ( CDG->Execute() )
         AltParamShapeColor = CDG->Color;
    }

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::cbAltParamShapeColorEnableClick(TObject *Sender)
{
   f_AltParamShapeColorEnable = cbAltParamShapeColorEnable->Checked;
}
//---------------------------------------------------------------------------

void TFmSetup::InitActions()
{
  TGlsActionListItem* AI;
  AnsiString SM;

  ActList->FillCharList(cbKey->Items);
  sgActions->RowCount = ActList->Count + 1;
  SGCells(sgActions, 0, 0, "ÄÅÉÑÒÂÈÅ");
  SGCells(sgActions, 0, 1, "ÊËÀÂÈØÀ");
  SGCells(sgActions, 0, 2, "Â ÌÅÍÞ?");
  sgActions->ColWidths[0] = 230;
  sgActions->ColWidths[1] = 75;
  sgActions->ColWidths[2] = 65;


  TStringList *S = new TStringList;
  for (int i = 0; i <= ActList->Count - 1; i++)
     S->Add(ActList->Items[i]->ActCaption);
  S->Sort();

  for (int i = 0; i <= S->Count - 1; i++)
  {
     AI = ActList->FindActionItemByCaption(S->Strings[i]);
     sgActions->Objects[0][1+i] = (TObject*)AI;
     SGCellsByName(sgActions, 1 + i,  "ÄÅÉÑÒÂÈÅ", AI->ActCaption);
     SGCellsByName(sgActions, 1 + i,  "ÊËÀÂÈØÀ", AI->SCut);
     if (AI->SubMenu)
       SM = "1";
     else
       SM = "0";
     SGCellsByName(sgActions, 1 + i,  "Â ÌÅÍÞ?", SM);
  }
  delete S;
}



void __fastcall TFmSetup::PageControl1Change(TObject *Sender)
{
   if (PageControl1->ActivePage == tsActions)
     sgActions->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::sgActionsSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
  TRect R;
  if ((ACol == 1) &&  (ARow != 0))
  {
    R = sgActions->CellRect(ACol, ARow);
    R.Left = R.Left + sgActions->Left;
    R.Right = R.Right + sgActions->Left;
    R.Top = R.Top + sgActions->Top;
    R.Bottom = R.Bottom + sgActions->Top;
    cbKey->Left = R.Left + 1;
    cbKey->Top = R.Top + 1;
    cbKey->Width = (R.Right + 1) - R.Left;
    cbKey->Height = (R.Bottom + 1) - R.Top;
    cbKey->ItemIndex = cbKey->Items->IndexOf(sgActions->Cells[ACol][ARow]);
    cbKey->Visible = true;
    cbKey->SetFocus();
  }
  if ((ACol == 2) && (ARow != 0))
  {
    R = sgActions->CellRect(ACol, ARow);
    R.Left = R.Left + sgActions->Left;
    R.Right = R.Right + sgActions->Left;
    R.Top = R.Top + sgActions->Top;
    R.Bottom = R.Bottom + sgActions->Top;
    cbMenu->Left = R.Left + 4;
    cbMenu->Top = R.Top + 2;
    cbMenu->Width = (R.Right + 2) - R.Left - 4;
    cbMenu->Height = (R.Bottom + 2) - R.Top - 2;
    cbMenu->Checked =  bool(StrToIntDef(sgActions->Cells[ACol][ARow], 0));
    cbMenu->Color = clWindow;
    cbMenu->Visible = true;
    cbMenu->SetFocus();
  }
  UpdateAddInfo(ARow);
  CanSelect = true;

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::cbKeyExit(TObject *Sender)
{
  sgActions->Cells[sgActions->Col][sgActions->Row] = cbKey->Text;
  cbKey->Visible = false;
  sgActions->SetFocus();

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::sgActionsDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
/*
  stas19 â XE10 îòðèñîâêà äîëæíà áûòü äðóãîé
  sgActions->Canvas->Font->Color = clMenuText;
  if ( (ACol == 0) )
  {
     if (State.Contains(gdFixed))
     {
	   sgActions->Canvas->FillRect(Rect);
       DrawText(sgActions->Canvas->Handle, sgActions->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
     }
     else
     {
       TRect R = Rect;
       R.Left = R.Left + 2;
       sgActions->Canvas->Brush->Color = clWindow;
       sgActions->Canvas->FillRect(Rect);
       DrawText(sgActions->Canvas->Handle, sgActions->Cells[ACol][ARow].c_str(), -1, &R, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
     }
  }
  if ( (ACol == 1)  )
  {
	 if (!(State.Contains(gdFixed)))
	   sgActions->Canvas->Brush->Color = clWindow;
	 sgActions->Canvas->FillRect(Rect);
	 DrawText(sgActions->Canvas->Handle, sgActions->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE );
  }
  if ( (ACol == 2)  )
  {
	 if (!(State.Contains(gdFixed)))
	   sgActions->Canvas->Brush->Color = clWindow;
	 sgActions->Canvas->FillRect(Rect);
	 if (ARow  == 0)
	   DrawText(sgActions->Canvas->Handle, sgActions->Cells[ACol][ARow].c_str(), -1, &Rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE  );
	 if (SameText(sgActions->Cells[ACol][ARow], "1"))
	 {
	   Graphics::TBitmap *Img = new Graphics::TBitmap;
	   ImgList->GetBitmap(0, Img);
	   DrawBmpInRect(sgActions->Canvas, Rect, Img);
	   delete Img;
	 }
  }
  */

  // Äàëåå äëÿ XE10
  if ( ACol == 2 )
  {
	 sgActions->Canvas->FillRect(Rect);
	 if (!State.Contains(gdFixed) && SameText(sgActions->Cells[ACol][ARow], "1"))
	 {
	   Graphics::TBitmap *Img = new Graphics::TBitmap;
	   ImgList->GetBitmap(0, Img);
	   DrawBmpInRect(sgActions->Canvas, Rect, Img);
	   delete Img;
	 }
  }

}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::cbMenuExit(TObject *Sender)
{
  sgActions->Cells[sgActions->Col][sgActions->Row] =  IntToStr(int(cbMenu->Checked));
  cbMenu->Visible = false;
  sgActions->SetFocus();

}
//---------------------------------------------------------------------------

void TFmSetup::UpdateAddInfo(int ARow)
{
   void *p = (void*)sgActions->Objects[0][ARow];
   if (p)
   {
      TGlsActionListItem* AI = static_cast<TGlsActionListItem*>(p);
      FreeHandler();
      cbxShift->Checked = AI->Shift;
      cbxCtrl->Checked = AI->Ctrl;
      cbxAlt->Checked = AI->Alt;
      SetHandler();
      mmHint->Text = AI->ActHint;
   }

}

void TFmSetup::SetAddInfo()
{
   void *p = (void*)sgActions->Objects[0][sgActions->Row];
   if (p)
   {
      TGlsActionListItem* AI = static_cast<TGlsActionListItem*>(p);
      AI->Shift = cbxShift->Checked;
      AI->Ctrl = cbxCtrl->Checked;
      AI->Alt = cbxAlt->Checked;
   }
}


void __fastcall TFmSetup::cbxShiftClick(TObject *Sender)
{
   SetAddInfo();
}
//---------------------------------------------------------------------------
void TFmSetup::FreeHandler()
{
   cbxShift->OnClick = NULL;
   cbxCtrl->OnClick = NULL;
   cbxAlt->OnClick = NULL;
}

void TFmSetup::SetHandler()
{
   cbxShift->OnClick = &cbxShiftClick;
   cbxCtrl->OnClick = &cbxShiftClick;
   cbxAlt->OnClick = &cbxShiftClick;
}

void TFmSetup::ApplyActions()
{
  void *p;
  TGlsActionListItem* AI;

  for (int i = 0; i <= ActList->Count - 1; i++)
  {
    p = (void*)sgActions->Objects[0][1+i];
    AI = static_cast<TGlsActionListItem*>(p);
    AI->SCut = sgActions->Cells[1][1+i];
    AI->SubMenu = SameText(sgActions->Cells[2][i+1], "1");
  }

}


void __fastcall TFmSetup::FormClose(TObject *Sender, TCloseAction &Action)
{
   ApplyActions();
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetVwColorAlt(TColor Value)
{
   if (f_VwColorAlt != Value)
   {
      f_VwColorAlt = Value;
      shpVwColorAlt->Brush->Color = f_VwColorAlt;
   }
}

void __fastcall TFmSetup::SetVwColorBadAlt(TColor Value)
{
   if (f_VwColorBadAlt != Value)
   {
      f_VwColorBadAlt = Value;
      shpVwColorBadAlt->Brush->Color = f_VwColorBadAlt;
   }
}

void __fastcall TFmSetup::shpVwColorAltMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = VwColorAlt;
       if ( CDG->Execute() )
         VwColorAlt = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::shpVwColorBadAltMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
       CDG->Color = VwColorBadAlt;
       if ( CDG->Execute() )
         VwColorBadAlt = CDG->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::acOKExecute(TObject *Sender)
{
   edStepPixelExit(NULL);
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------


void __fastcall TFmSetup::acCancelExecute(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFmSetup::SetSectionBarAlternativeColor(bool Value)
{
	if (f_SectionBarAlternativeColor != Value)
	{
		f_SectionBarAlternativeColor = Value;
		cbSectionBarAlternativeColor->Checked = f_SectionBarAlternativeColor;
	}
}


void __fastcall TFmSetup::cbSectionBarAlternativeColorClick(TObject *Sender)
{
  f_SectionBarAlternativeColor = cbSectionBarAlternativeColor->Checked;
}
//---------------------------------------------------------------------------

