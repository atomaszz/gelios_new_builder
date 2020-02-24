//---------------------------------------------------------------------------

#ifndef ufSetupH
#define ufSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "uGlsActionList.h"
#include <ImgList.hpp>
#include <ActnList.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TFmSetup : public TForm
{
__published:	// IDE-managed Components
        TColorDialog *CDG;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TEdit *edStepPixel;
        TLabel *Label1;
        TCheckBox *cbPaintPixels;
        TShape *shpFon;
        TLabel *Label3;
        TLabel *Label4;
        TShape *shpPixel;
        TPanel *Panel1;
        TTabSheet *TabSheet2;
        TCheckBox *cbBoldTFELine;
        TGroupBox *GroupBox1;
        TCheckBox *cbDrawFrameLine;
        TLabel *Label2;
        TShape *shpFrameLineColor;
        TShape *shpLineColor;
        TLabel *Label5;
        TCheckBox *cbBrushTFE;
        TShape *shpBrushColor;
        TLabel *Label6;
        TPaintBox *pbFont;
        TButton *btFont;
        TFontDialog *FDG;
        TComboBox *cbxFlagType;
        TLabel *Label7;
        TLabel *Label8;
        TShape *shpColorLeave;
        TLabel *Label9;
        TShape *shpColorEnter;
        TShape *shpFrameColorTFE;
        TLabel *Label10;
        TShape *shpFrameColorTFS;
        TLabel *Label11;
        TLabel *Label12;
        TShape *shpHaveChildColor;
        TTabSheet *TabSheet3;
        TShape *shpAltFlagColor;
        TLabel *Label13;
        TLabel *Label14;
        TShape *shpAltEnterFlagColor;
        TShape *shpAltArrowColor;
        TLabel *Label15;
        TLabel *Label16;
        TShape *shpAltEnterArrowColor;
        TShape *shpAltLineColor;
        TLabel *Label17;
        TCheckBox *cbCanModifyPenWidth;
        TTabSheet *TabSheet4;
        TLabel *Label18;
        TEdit *edHelp;
        TButton *btHelp;
        TOpenDialog *OPD;
        TButton *btHelpDefault;
        TShape *shpAltEnabledFlagColor;
        TLabel *Label19;
        TGroupBox *GroupBox2;
        TShape *shpAltParamLineColor;
        TLabel *Label20;
        TGroupBox *GroupBox3;
        TCheckBox *cbAltParamShapeColorEnable;
        TLabel *Label21;
        TShape *shpAltParamShapeColor;
        TTabSheet *tsActions;
        TPanel *Panel2;
        TStringGrid *sgActions;
        TComboBox *cbKey;
        TImageList *ImgList;
        TCheckBox *cbMenu;
        TCheckBox *cbxShift;
        TCheckBox *cbxCtrl;
        TCheckBox *cbxAlt;
        TLabel *Label22;
        TMemo *mmHint;
        TTabSheet *tsView;
        TLabel *Label23;
        TShape *shpVwColorAlt;
        TLabel *Label24;
        TShape *shpVwColorBadAlt;
        TActionList *ActionList1;
        TAction *acOK;
        TAction *acCancel;
        TButton *Button1;
        TButton *Button2;
	TCheckBox *cbSectionBarAlternativeColor;
        void __fastcall edStepPixelExit(TObject *Sender);
        void __fastcall cbPaintPixelsClick(TObject *Sender);
        void __fastcall shpFonMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shpPixelMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall cbDrawFrameLineClick(TObject *Sender);
        void __fastcall cbBoldTFELineClick(TObject *Sender);
        void __fastcall shpFrameLineColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall pbFontPaint(TObject *Sender);
        void __fastcall btFontClick(TObject *Sender);
        void __fastcall shpLineColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpBrushColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall cbBrushTFEClick(TObject *Sender);
        void __fastcall cbxFlagTypeChange(TObject *Sender);
        void __fastcall shpColorLeaveMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpColorEnterMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpFrameColorTFEMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpFrameColorTFSMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpHaveChildColorMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shpAltFlagColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltEnterFlagColorMouseU(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltArrowColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltEnterArrowColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltLineColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall cbCanModifyPenWidthClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall btHelpClick(TObject *Sender);
        void __fastcall btHelpDefaultClick(TObject *Sender);
        void __fastcall edHelpExit(TObject *Sender);
        void __fastcall shpAltEnabledFlagColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltParamLineColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpAltParamShapeColorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall cbAltParamShapeColorEnableClick(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall sgActionsSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall cbKeyExit(TObject *Sender);
        void __fastcall sgActionsDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall cbMenuExit(TObject *Sender);
        void __fastcall cbxShiftClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall shpVwColorAltMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shpVwColorBadAltMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall acOKExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
	void __fastcall cbSectionBarAlternativeColorClick(TObject *Sender);

private:	// User declarations
        int f_StepPixel;
        bool f_PaintPixels;
        bool f_DrawFrameLine;
        TColor f_FonColor;
        TColor f_PixelColor;
        TColor f_FrameLineColor;
        bool f_BoldTFELine;
        TColor f_LineColor;
        bool f_BrushTFE;
        TColor f_BrushColor;
        Graphics::TFont* f_FontTFE;
        int f_FlagType;
        TColor f_ColorLeave;
        TColor f_ColorEnter;
        TColor f_FrameColorTFE;
        TColor f_FrameColorTFS;
        TColor f_HaveChildColor;
        TColor f_AltFlagColor;
        TColor f_AltEnterFlagColor;
        TColor f_AltArrowColor;
        TColor f_AltEnterArrowColor;
        TColor f_AltLineColor;
        bool f_CanModifyPenWidth;
        AnsiString f_HelpUrl;
        TColor f_AltEnabledFlagColor;
        TColor f_AltParamLineColor;
        TColor f_AltParamShapeColor;
		bool   f_AltParamShapeColorEnable;
		bool   f_SectionBarAlternativeColor;

        TColor f_VwColorAlt;
        TColor f_VwColorBadAlt;


        void __fastcall SetStepPixel(int Value);
        void __fastcall SetPaintPixels(bool Value);
        void __fastcall SetDrawFrameLine(bool Value);
        void __fastcall SetFonColor(TColor Value);
        void __fastcall SetPixelColor(TColor Value);
        void __fastcall SetFrameLineColor(TColor Value);
        void __fastcall SetBoldTFELine(bool Value);
        void __fastcall SetLineColor(TColor Value);
        void __fastcall SetBrushColor(TColor Value);
        void __fastcall SetBrushTFE(bool Value);
        void __fastcall SetFontTFE(Graphics::TFont* Value);
        void __fastcall SetFlagType(int Value);
        void __fastcall SetColorLeave(TColor Value);
        void __fastcall SetColorEnter(TColor Value);
        void __fastcall SetFrameColorTFE(TColor Value);
        void __fastcall SetFrameColorTFS(TColor Value);
        void __fastcall SetHaveChildColor(TColor Value);
        void __fastcall SetAltFlagColor(TColor Value);
        void __fastcall SetAltEnterFlagColor(TColor Value);
        void __fastcall SetAltArrowColor(TColor Value);
        void __fastcall SetAltEnterArrowColor(TColor Value);
        void __fastcall SetAltLineColor(TColor Value);
        void __fastcall SetCanModifyPenWidth(bool Value);
        void __fastcall SetHelpUrl(AnsiString AHelpUrl);
        void __fastcall SetAltEnabledFlagColor(TColor Value);

        void __fastcall SetAltParamLineColor(TColor Value);
        void __fastcall SetAltParamShapeColor(TColor Value);
		void __fastcall SetAltParamShapeColorEnable(bool Value);
		void __fastcall SetSectionBarAlternativeColor(bool Value);

        void __fastcall SetVwColorAlt(TColor Value);
        void __fastcall SetVwColorBadAlt(TColor Value);


        void InitActions();
        void UpdateAddInfo(int ARow);
        void FreeHandler();
        void SetHandler();
        void SetAddInfo();
        void ApplyActions();
public:		// User declarations
        __fastcall TFmSetup(TComponent* Owner);
        TGlsActionList *ActList;
        __property int StepPixel = {read = f_StepPixel, write = SetStepPixel};
        __property bool PaintPixels = {read = f_PaintPixels, write = SetPaintPixels};
        __property bool DrawFrameLine = {read = f_DrawFrameLine, write = SetDrawFrameLine};
        __property TColor FonColor = {read = f_FonColor, write = SetFonColor};
        __property TColor PixelColor = {read = f_PixelColor, write = SetPixelColor};
        __property bool BoldTFELine = {read = f_BoldTFELine, write = SetBoldTFELine};
        __property TColor FrameLineColor = {read = f_FrameLineColor, write = SetFrameLineColor};
        __property TColor LineColor = {read  = f_LineColor, write = SetLineColor};
        __property TColor BrushColor = {read = f_BrushColor, write = SetBrushColor};
        __property bool  BrushTFE = {read = f_BrushTFE, write = SetBrushTFE};
        __property Graphics::TFont* FontTFE = {read = f_FontTFE, write  = SetFontTFE};
        __property int FlagType = {read = f_FlagType, write = SetFlagType};
        __property TColor ColorLeave = {read = f_ColorLeave, write = SetColorLeave};
        __property TColor ColorEnter = {read = f_ColorEnter, write = SetColorEnter};
        __property TColor FrameColorTFE = {read = f_FrameColorTFE, write = SetFrameColorTFE};
        __property TColor FrameColorTFS = {read = f_FrameColorTFS, write = SetFrameColorTFS};
        __property TColor HaveChildColor = {read= f_HaveChildColor, write = SetHaveChildColor};
        __property TColor AltFlagColor = {read = f_AltFlagColor, write = SetAltFlagColor};
        __property TColor AltEnterFlagColor = {read = f_AltEnterFlagColor, write = SetAltEnterFlagColor};
        __property TColor AltArrowColor = {read = f_AltArrowColor, write = SetAltArrowColor};
        __property TColor AltEnterArrowColor = {read = f_AltEnterArrowColor, write = SetAltEnterArrowColor};
        __property TColor AltLineColor = {read = f_AltLineColor, write = SetAltLineColor};
        __property bool CanModifyPenWidth = {read = f_CanModifyPenWidth, write  = SetCanModifyPenWidth};
        __property AnsiString HelpUrl  = {read = f_HelpUrl, write = SetHelpUrl};
        __property TColor AltEnabledFlagColor = {read = f_AltEnabledFlagColor, write = SetAltEnabledFlagColor};
        __property TColor AltParamLineColor = {read = f_AltParamLineColor, write = SetAltParamLineColor};
        __property TColor AltParamShapeColor = {read = f_AltParamShapeColor, write = SetAltParamShapeColor};
        __property bool AltParamShapeColorEnable = {read = f_AltParamShapeColorEnable, write  = SetAltParamShapeColorEnable};
        __property TColor VwColorAlt = {read =  f_VwColorAlt, write  = SetVwColorAlt};
		__property TColor VwColorBadAlt = {read =  f_VwColorBadAlt, write  = SetVwColorBadAlt};
		__property bool SectionBarAlternativeColor = {read = f_SectionBarAlternativeColor, write = SetSectionBarAlternativeColor};
};
//---------------------------------------------------------------------------
extern PACKAGE TFmSetup *FmSetup;
//---------------------------------------------------------------------------
#endif
