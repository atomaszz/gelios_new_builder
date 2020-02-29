//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMainFrm.h"

#include "uPaintgrids.h"
#include "ufSetup.h"
#include "ufrmAlternateView.h"
#include "ufrmDialogExit.h"
#include "uCompositeWork.h"
#include "uCompositeZWork.h"
#include "uCompositeZWorkOR.h"
#include "uCompositeControlWork.h"
#include "uCompositeControlFunc.h"
#include "uCompositeBifurcation.h"
#include "uCompositeCheckConditionCW.h"
#include "uCompositeCycleWhileDo.h"
#include "uCompositeCycleDoWhileDo.h"
#include "uCompositeCycleDoWhileDoFC.h"
#include "uCompositeCheckCondition.h"
#include "ufrmAlternateViewSelect.h"
#include "uMessengers.h"
#include "uFrmHelp.h"
#include "uGraphTFEConvertor.h"
#include "ufrmPredicateView.h"
#include "uPredicateTFSConvertor.h"
#include "uAlternativeParserEnlarger.h"
#include "uParamAlternativeItem.h"
#include "uFmParamAlternative.h"
#include "uIMRIncl_all.h"
#include "uCursorStorage.h"
#include "opim_f.H"
#include "ufmStartDecision.h"
#include "uMetodOpt.h"
#include "ufmPredicatePathView.h"
#include "uMakerTFS.h"
#include "ufmPredicatePathConstructor.h"
#include "ufAbount.h"
#include "ufToolMain.h"
#include "ufGenerStruct.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//friend
int ContainsChildShape(int Param1, int Param2)
{
  if ( frmMain->GetMainList()->IsContainsChildShape(Param1) )
    return frmMain->HaveChildColor;
  return 0;
}


int SaveHideBar(int Param1, int Param2)
{
   frmMain->HelpHideBar = bool(Param1);
   return 1;
}

int CompareWS(int Param1, int Param2)
{
  TBaseWorkShape *m_s, *m_e;
  TBaseWorkShape *m_olds;
  int m_num;
  m_s = (TBaseWorkShape*)(Param1);
  m_e = (TBaseWorkShape*)(Param2);
  m_olds = m_s;
  if ( frmMain->GetMainList()->CompareWorkShape(&m_s, &m_e) )
  {
     if (m_olds == m_s)
       return -1;
     if (m_olds != m_s)
       return 1;
  }
  return -100;
}

int GLBCheckUsedPath(int Param1, int Param2)
{
   return frmMain->CheckUsedPath();
}

int GLBShowPredicateModel(int Param1, int Param2)
{
  frmMain->PredicateModel(reinterpret_cast<TPredicatePathItem*>(Param1));
  return 0;
}

int GLBFindTFS(int Param1, int Param2)
{
  TListNode* NM = frmMain->GetMainList();
  int fid = NM->FindBlockOutShape(Param1);
  if (fid)
  {
    int mpos;
    TNodeMain* Node = NM->FindNode(fid, mpos);
    if (Node)
      return int(Node->WorkShape);
  }
  return 0;
}

int GLBFindTFSByBlockID(int Param1, int Param2)
{
  TListNode* NM = frmMain->GetMainList();
  int mpos;
  TNodeMain* Node = NM->FindNode(Param1, mpos);
  if (Node)
    return int(Node->WorkShape);
  return 0;
}


int GLBApplySettingsForOutherGrid(int Param1, int Param2)
{
  TPaintGrid* G = reinterpret_cast<TPaintGrid*>(Param1);
  frmMain->ApplySettingsForOutherGrid(G);
  return 0;
}

int GLBOzenk(int Param1, int Param2)
{
  TPredicatePathItem* PI = reinterpret_cast<TPredicatePathItem*>(Param1);
  TPredicatePathConstructorStruct* S = reinterpret_cast<TPredicatePathConstructorStruct*>(Param2);
  frmMain->OzenkTFEStill(PI, S->oz0, S->oz1);
  return 0;
}



void TfrmMain::InitPieModule()
{
   String S = "Ошибка загрузки модуля ПРОЛОГ системы!\r\n";
   S = S + "Без данной функции условия предикатов ТФЕ в задачах оптимизации будут игнорироваться!";
   gPieModule = new TPieModule;
   if (!gPieModule->CheckModule())
     MessageBox(0, S.c_str(), _T("Предупреждение"), MB_ICONWARNING);
}



//----------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
   TAltSelectorItem* Item;
   f_IsDebug = HasParam("debug");
   f_StepPixel = 8;
   f_PaintPixels = true;
   f_DrawFrameLine = false;
   f_FonColor = clWhite;
   f_PixelColor = clBlack;
   Grid = new TPaintGrid(pbMain->Canvas, frmMain->Handle);
   Grid->LEControl = true;
   Grid->WndHandler = this->Handle;
   Grid->UnderControl = pbMain;
   CreateSectionBar();
   MainList = new TListNode;
   MainList->OnListChange = ListChange;
   LevelController = new TLevelController;
   LevelController->Push(0);
   f_IdAlternative = 0;
   f_CurrIDBlock = 1;
   f_CurrIDShape = 0;
   f_CurrIDLine = 0;
   f_WSPenWidth = 1;
   f_FrameLineColor = clBlack;
   sbY->Max = 0;
   sbX->Max = 0;
   X_Base = Y_Base = X_Ofs = Y_Ofs = 0;
   f_LineColor = clBlack;
   f_BrushTFE = false;
   f_BrushColor = clWhite;
   f_FontTFE = new Graphics::TFont;
   f_FlagType = 1;
   f_ColorLeave = clRed;
   f_ColorEnter = clYellow;
   __idls =0;
   f_FrameColorTFE = clRed;
   f_FrameColorTFS = clRed;
   f_HaveChildColor = clGreen;
   f_AltFlagColor = clBlue;
   f_AltEnterFlagColor = clAqua;
   f_AltArrowColor = clBlue;
   f_AltEnterArrowColor = clAqua;
   f_AltLineColor = clBlue;
   f_AltEnabledFlagColor = clSilver;
   f_Operation = 0;
   f_TypeParam = PROP;
   f_CanModifyPenWidth = false;
   f_AltParamLineColor = clFuchsia;
   f_AltParamShapeColor = clYellow;
   f_AltParamShapeColorEnable = false;
   f_CheckNud = false;
   f_OptAnp = false;


   f_AlternateController = new TAlternateController(Handle);
   f_AlternateController->OnListChange = AlternateListChange;
   f_AlternateController->LEControl = true;
   f_AlternateController->WndHandler = this->Handle;
   f_AlternateController->UnderControl = pbMain;
   f_AltSelector = new TAltSelector;
   f_AltStackController = new  TAltStackController;
   f_MenuController = new TMenuController;
   f_ContextMenuController = new TMenuController;
   Item = f_AltSelector->CreateNewAlternateID(LevelController->ParentShapeID);
   f_IdAlternative = Item->ID;
   f_NumAlternative = f_AltSelector->AddAltItem(f_IdAlternative);
   f_IdAlternativeParent = f_IdAlternative;
   f_NumAlternativeParent = f_NumAlternative;
   MainList->CreateAlternate(NULL, NULL, f_IdAlternative, f_NumAlternative);
   f_AltStackController->Push(f_IdAlternative, f_NumAlternative,
      f_IdAlternativeParent, f_NumAlternativeParent);
   f_ColorSetup = new TColorSetup;
   f_RSettings =  new TGlsRegistry;
   GMess = new TMessangers;
   f_AV = new TAlternateView;
   f_StackHistory = new TDynamicArray;
   f_OgrSovmArray = new TOgrSovmArray;
   f_ActList = new TGlsActionList;
   InitActionList();

   f_RSettings->Path = "\\Software\\TFEGraph\\GLS";
   RestoreSettings();
   GMess->RegistrMessage(1, ContainsChildShape);
   GMess->RegistrMessage(2, SaveHideBar);
   GMess->RegistrMessage(3, CompareWS);
   GMess->RegistrMessage(4, GLBCheckUsedPath);
   GMess->RegistrMessage(5, GLBShowPredicateModel);
   GMess->RegistrMessage(6, GLBFindTFS);
   GMess->RegistrMessage(7, GLBApplySettingsForOutherGrid);
   GMess->RegistrMessage(8, GLBOzenk);
   GMess->RegistrMessage(9, GLBFindTFSByBlockID);

   InitHelp();
   InitPieModule();
   f_Zadacha = new TZadacha;
   f_ClipCopyTFS = new TClipCopyTFS(Handle, 0x8000000);
   f_PredicatePath = new TPredicatePath;
   f_PredicateDopPrav = new AnsiString;
   ApplySettings();
   randomize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
   delete Grid;
   delete SectionBar;
   delete MainList;
   delete LevelController;
   delete f_FontTFE;
   delete f_AlternateController;
   delete f_AltSelector;
   delete f_AltStackController;
   delete f_MenuController;
   delete f_ColorSetup;
   delete f_RSettings;
   delete f_AV;
   delete GMess;
   delete f_StackHistory;
   FreeCursorStorage();
   delete gPieModule;
   delete f_Zadacha;
   delete f_ActList;
   delete f_ContextMenuController;
   delete f_ClipCopyTFS;
   delete f_PredicatePath;
   delete f_PredicateDopPrav;
   delete f_OgrSovmArray;
}

//---------------------------------------------------------------------------
void  TfrmMain::CreateSectionBar()
{
   SectionBar = new TGLSSectionBar(this);
   SectionBar->Width = pnlButton->Width;
   SectionBar->Parent = pnlButton;
   SectionBar->Images = ImgButtons;
   SectionBar->ApplyDown = true;
   SectionBar->ShowHint = true;
   SectionBar->Sections->Add();
   SectionBar->Sections->Items[0]->Caption = "Основные";
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();
   SectionBar->Sections->Items[0]->Buttons->Add();

   SectionBar->Sections->Items[0]->Buttons->Items[0]->Caption = "Раб. оперция";
   SectionBar->Sections->Items[0]->Buttons->Items[0]->Hint = "Рабочая операция";
   SectionBar->Sections->Items[0]->Buttons->Items[0]->ImageIndex = 0;

   SectionBar->Sections->Items[0]->Buttons->Items[1]->Caption = "Послед. рабочая";
   SectionBar->Sections->Items[0]->Buttons->Items[1]->Hint = "Последовательная рабочая операция";
   SectionBar->Sections->Items[0]->Buttons->Items[1]->ImageIndex = 11;

   SectionBar->Sections->Items[0]->Buttons->Items[2]->Caption = "Парал. рабочая И";
   SectionBar->Sections->Items[0]->Buttons->Items[2]->Hint = "Параллельная рабочая операция И";
   SectionBar->Sections->Items[0]->Buttons->Items[2]->ImageIndex = 1;

   SectionBar->Sections->Items[0]->Buttons->Items[3]->Caption = "Парал. рабочая ИЛИ";
   SectionBar->Sections->Items[0]->Buttons->Items[3]->Hint = "Параллельная рабочая операция ИЛИ";
   SectionBar->Sections->Items[0]->Buttons->Items[3]->ImageIndex = 2;


   //   SectionBar->Sections->Items[0]->Buttons->Items[2]->Enabled = false;

   SectionBar->Sections->Items[0]->Buttons->Items[4]->Caption = "Контроль раб-ти";
   SectionBar->Sections->Items[0]->Buttons->Items[4]->Hint = "Контроль работоспособности";
   SectionBar->Sections->Items[0]->Buttons->Items[4]->ImageIndex = 3;

   SectionBar->Sections->Items[0]->Buttons->Items[5]->Caption = "Функ-ый контроль";
   SectionBar->Sections->Items[0]->Buttons->Items[5]->Hint = "Функциональный контроль";
   SectionBar->Sections->Items[0]->Buttons->Items[5]->ImageIndex = 4;
 //  SectionBar->Sections->Items[0]->Buttons->Items[4]->Enabled = false;

   SectionBar->Sections->Items[0]->Buttons->Items[6]->Caption = "Развилка";
   SectionBar->Sections->Items[0]->Buttons->Items[6]->Hint = "Развилка";
   SectionBar->Sections->Items[0]->Buttons->Items[6]->ImageIndex = 5;

   SectionBar->Sections->Items[0]->Buttons->Items[7]->Caption = "Проверка условия (к.р.)";
   SectionBar->Sections->Items[0]->Buttons->Items[7]->Hint = "Проверка условия (контроль работоспособности)";
   SectionBar->Sections->Items[0]->Buttons->Items[7]->ImageIndex = 6;

   SectionBar->Sections->Items[0]->Buttons->Items[8]->Caption = "Цикл WHILE DO";
   SectionBar->Sections->Items[0]->Buttons->Items[8]->Hint = "Цикл WHILE DO";
   SectionBar->Sections->Items[0]->Buttons->Items[8]->ImageIndex = 7;

   SectionBar->Sections->Items[0]->Buttons->Items[9]->Caption = "Цикл DO WHILE DO";
   SectionBar->Sections->Items[0]->Buttons->Items[9]->Hint = "Цикл DO WHILE DO";
   SectionBar->Sections->Items[0]->Buttons->Items[9]->ImageIndex = 8;

   SectionBar->Sections->Items[0]->Buttons->Items[10]->Caption = "Цикл DO WHILE DO (с ФК)";
   SectionBar->Sections->Items[0]->Buttons->Items[10]->Hint = "Цикл DO WHILE DO с функц. контролем";
   SectionBar->Sections->Items[0]->Buttons->Items[10]->ImageIndex = 9;

   SectionBar->Sections->Items[0]->Buttons->Items[11]->Caption = "Проверка условия";
   SectionBar->Sections->Items[0]->Buttons->Items[11]->Hint = "Проверка условия";
   SectionBar->Sections->Items[0]->Buttons->Items[11]->ImageIndex = 10;
   SectionBar->RightMouseDown = GlsBarRigthDown;
   SectionBar->OnButtonApplyDown = GlsBarApplyDown;

//   SectionBar->Sections->Items[0]->Buttons->Items[5]->Enabled = false;

}



//---------------------------------------------------------------------------

void __fastcall TfrmMain::pbMainPaint(TObject *Sender)
{
  Grid->Paint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
   Grid->StepPixels = 6;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acSetupInterfaceExecute(TObject *Sender)
{
  Application->CreateForm(__classid(TFmSetup), &FmSetup);
  FmSetup->StepPixel = f_StepPixel;
  FmSetup->PaintPixels = f_PaintPixels;
  FmSetup->FonColor = f_FonColor;
  FmSetup->PixelColor = f_PixelColor;
  FmSetup->DrawFrameLine = f_DrawFrameLine;
  FmSetup->BoldTFELine = (f_WSPenWidth == 2);
  FmSetup->FrameLineColor = f_FrameLineColor;
  FmSetup->LineColor = f_LineColor;
  FmSetup->BrushTFE = f_BrushTFE;
  FmSetup->BrushColor = f_BrushColor;
  FmSetup->FontTFE = f_FontTFE;
  FmSetup->FlagType = f_FlagType;
  FmSetup->ColorEnter = f_ColorEnter;
  FmSetup->ColorLeave = f_ColorLeave;
  FmSetup->FrameColorTFE = f_FrameColorTFE;
  FmSetup->FrameColorTFS = f_FrameColorTFS;
  FmSetup->HaveChildColor = f_HaveChildColor;
  FmSetup->AltFlagColor =   f_AltFlagColor;
  FmSetup->AltEnterFlagColor = f_AltEnterFlagColor;
  FmSetup->AltArrowColor = f_AltArrowColor;
  FmSetup->AltEnterArrowColor = f_AltEnterArrowColor;
  FmSetup->AltLineColor = f_AltLineColor;
  FmSetup->CanModifyPenWidth = f_CanModifyPenWidth;
  FmSetup->HelpUrl = f_HelpFile;
  FmSetup->AltEnabledFlagColor = f_AltEnabledFlagColor;
  FmSetup->AltParamLineColor = f_AltParamLineColor;
  FmSetup->AltParamShapeColor = f_AltParamShapeColor;
  FmSetup->AltParamShapeColorEnable = f_AltParamShapeColorEnable;
  FmSetup->VwColorAlt = f_VwColorAlt;
  FmSetup->VwColorBadAlt = f_VwColorBadAlt;
  FmSetup->SectionBarAlternativeColor = f_SectionBarAlternativeColor;

  FmSetup->ActList = f_ActList;


  if ( FmSetup->ShowModal() == mrOk )
  {
	 f_StepPixel = FmSetup->StepPixel;
	 f_PaintPixels = FmSetup->PaintPixels;
	 f_FonColor = FmSetup->FonColor;
	 f_PixelColor = FmSetup->PixelColor;
	 f_DrawFrameLine = FmSetup->DrawFrameLine;
	 f_FrameLineColor = FmSetup->FrameLineColor;
	 f_LineColor = FmSetup->LineColor;
	 f_BrushTFE = FmSetup->BrushTFE;
	 f_BrushColor = FmSetup->BrushColor;
	 f_FontTFE->Assign(FmSetup->FontTFE);
	 FmSetup->BoldTFELine ? f_WSPenWidth = 2 : f_WSPenWidth = 1;
	 f_FlagType = FmSetup->FlagType;
	 f_ColorEnter = FmSetup->ColorEnter;
	 f_ColorLeave = FmSetup->ColorLeave;
	 f_FrameColorTFE = FmSetup->FrameColorTFE;
	 f_FrameColorTFS = FmSetup->FrameColorTFS;
	 f_HaveChildColor = FmSetup->HaveChildColor;
	 f_AltFlagColor = FmSetup->AltFlagColor;
	 f_AltEnterFlagColor = FmSetup->AltEnterFlagColor;
	 f_AltArrowColor = FmSetup->AltArrowColor;
	 f_AltEnterArrowColor = FmSetup->AltEnterArrowColor;
	 f_AltLineColor = FmSetup->AltLineColor;
	 f_CanModifyPenWidth = FmSetup->CanModifyPenWidth;
	 f_HelpFile = FmSetup->HelpUrl;
	 f_AltEnabledFlagColor = FmSetup->AltEnabledFlagColor;

	 f_AltParamLineColor = FmSetup->AltParamLineColor;
	 f_AltParamShapeColor = FmSetup->AltParamShapeColor;
	 f_AltParamShapeColorEnable = FmSetup->AltParamShapeColorEnable;
	 f_VwColorAlt = FmSetup->VwColorAlt;
	 f_VwColorBadAlt = FmSetup->VwColorBadAlt;
	 f_SectionBarAlternativeColor = FmSetup->SectionBarAlternativeColor;

	 ApplySettings();
  }
  FmSetup->Release();
}

//---------------------------------------------------------------------------
void TfrmMain::SetShapeAtr()
{
   shpLeft->Visible = f_DrawFrameLine;
   shpLeft->Pen->Color = f_FrameLineColor;
   shpLeft->Brush->Color = f_FrameLineColor;
   shpTop->Visible = f_DrawFrameLine;
   shpTop->Pen->Color = f_FrameLineColor;
   shpTop->Brush->Color = f_FrameLineColor;
   shpRight->Visible = f_DrawFrameLine;
   shpRight->Pen->Color = f_FrameLineColor;
   shpRight->Brush->Color = f_FrameLineColor;
   shpButtom->Visible = f_DrawFrameLine;
   shpButtom->Pen->Color = f_FrameLineColor;
   shpButtom->Brush->Color = f_FrameLineColor;

}

//---------------------------------------------------------------------------
void TfrmMain::ApplySettings()
{
   Grid->StepPixelsGrid = f_StepPixel;
   Grid->PaintPixels = f_PaintPixels;
   Grid->FonColor = f_FonColor;
   Grid->PixelColor = f_PixelColor;
   Grid->WSPenWidth = f_WSPenWidth;
   f_StepPixel = Grid->StepPixelsGrid; //грид может сам переопределить растояние мд пикселами
   Grid->LineColor = f_LineColor;
   Grid->BrushTFE = f_BrushTFE;
   Grid->BrushColor = f_BrushColor;
   Grid->FontTFE = f_FontTFE;
   Grid->FlagType = f_FlagType;
   Grid->EnterFlagColor = f_ColorEnter;
   Grid->LeaveFlagColor = f_ColorLeave;
   Grid->FrameColorTFE = f_FrameColorTFE;
   Grid->FrameColorTFS = f_FrameColorTFS;
   Grid->AltEnterFlagColor = f_AltEnterFlagColor;
   Grid->AltFlagColor = f_AltFlagColor;
   Grid->AltArrowColor = f_AltArrowColor;
   Grid->AltEnterArrowColor = f_AltEnterArrowColor;
   Grid->AltLineColor = f_AltLineColor;
   Grid->AltEnabledFlagColor = f_AltEnabledFlagColor;
   Grid->Recreate(pbMain->Width, pbMain->Height);
   pnlMain->Color = Grid->FonColor;
   SetShapeAtr();
   f_AlternateController->EnterArrowColor = f_AltEnterArrowColor;
   f_AlternateController->ArrowColor = f_AltArrowColor;
   f_AlternateController->PenColor = f_LineColor;
   if (f_CanModifyPenWidth)
     f_AlternateController->PenWidth = f_WSPenWidth;
   else
     f_AlternateController->PenWidth = 1;
   ApplyColorSetupSettings();
   pbMain->Invalidate();
   ApplyShortCutToActions();
   SectionBar->AlternativeColor = f_SectionBarAlternativeColor;
   SectionBar->Invalidate();
}

void TfrmMain::ApplySettingsForOutherGrid(TPaintGrid* AGrid)
{
  AGrid->StepPixels = 6;
  AGrid->StepPixelsGrid = f_StepPixel;
  AGrid->PaintPixels = f_PaintPixels;
  AGrid->FonColor = f_FonColor;
  AGrid->PixelColor = f_PixelColor;
  AGrid->WSPenWidth = f_WSPenWidth;
  AGrid->LineColor = f_LineColor;
  AGrid->BrushTFE = f_BrushTFE;
  AGrid->BrushColor = f_BrushColor;
  AGrid->FontTFE = f_FontTFE;
  AGrid->FlagType = f_FlagType;
  AGrid->EnterFlagColor = f_ColorEnter;
  AGrid->LeaveFlagColor = f_ColorLeave;
  AGrid->FrameColorTFE = f_FrameColorTFE;
  AGrid->FrameColorTFS = f_FrameColorTFS;
  AGrid->AltEnterFlagColor = f_AltEnterFlagColor;
  AGrid->AltFlagColor = f_AltFlagColor;
  AGrid->AltArrowColor = f_AltArrowColor;
  AGrid->AltEnterArrowColor = f_AltEnterArrowColor;
  AGrid->AltLineColor = f_AltLineColor;
  AGrid->AltEnabledFlagColor = f_AltEnabledFlagColor;
}

void TfrmMain::ApplyColorSetupSettings()
{
   f_ColorSetup->FonColor =  f_FonColor;
   f_ColorSetup->BoldTFELine =  (f_WSPenWidth == 2);
   f_ColorSetup->LineColor = f_LineColor;
   f_ColorSetup->BrushTFE = f_BrushTFE;
   f_ColorSetup->BrushColor = f_BrushColor;
   f_ColorSetup->FrameColorTFE =  f_FrameColorTFE;
   f_ColorSetup->FrameColorTFS =  f_FrameColorTFS;
   f_ColorSetup->HaveChildColor = f_HaveChildColor;
   f_ColorSetup->SetFont(f_FontTFE);
   f_ColorSetup->AltParamLineColor = f_AltParamLineColor;
   f_ColorSetup->AltParamShapeColor = f_AltParamShapeColor;
   f_ColorSetup->AltParamShapeColorEnable = f_AltParamShapeColorEnable;

}


void __fastcall TfrmMain::pnlMainResize(TObject *Sender)
{
   Grid->Recreate(pbMain->Width, pbMain->Height);
   SetNewPolygon();
}
//---------------------------------------------------------------------------

int TfrmMain::GetTypShape()
{
   int res;
   res = -1;
   if (SectionBar->Sections->Items[0]->Buttons->Items[0]->Down)
     res = 1;
   if (SectionBar->Sections->Items[0]->Buttons->Items[1]->Down)
     res = 2;
   if (SectionBar->Sections->Items[0]->Buttons->Items[2]->Down)
     res = 3;
   if (SectionBar->Sections->Items[0]->Buttons->Items[3]->Down)
     res = 4;
   if (SectionBar->Sections->Items[0]->Buttons->Items[4]->Down)
     res = 5;
   if (SectionBar->Sections->Items[0]->Buttons->Items[5]->Down)
     res = 6;
   if (SectionBar->Sections->Items[0]->Buttons->Items[6]->Down)
     res = 7;
   if (SectionBar->Sections->Items[0]->Buttons->Items[7]->Down)
     res = 8;
   if (SectionBar->Sections->Items[0]->Buttons->Items[8]->Down)
	 res = 9;
   if (SectionBar->Sections->Items[0]->Buttons->Items[9]->Down)
     res = 10;
   if (SectionBar->Sections->Items[0]->Buttons->Items[10]->Down)
     res = 11;
   if (SectionBar->Sections->Items[0]->Buttons->Items[11]->Down)
     res = 12;
   return res;
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::pbMainMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   bool m_tfs, m_tfe;
   TAlternateItem* Item;
   int typ = GetTypShape();
   if ((typ > 0) && (Grid->Regim == 0))
   {
     AddWorkShape(typ);
     SectionBar->DownFalse();
   }
   else
     Grid->MouseUp(Sender, Button, Shift, X, Y);
   Item = Grid->FindAlternateItem(X, Y);
   if ( (Button == mbRight ) && (Item) )
   {
     MenuAlternateItemCreate(Item, X, Y );
     return;
   }

   if ( Button == mbRight )
   {
//     m_tfe =  ( (Grid->SelectedTFE) &&  (Grid->FindTFE(X, Y) ==  Grid->SelectedTFE) );
//     m_tfs =  ( (Grid->SelectedTFS) &&  (Grid->FindTFS(X, Y) ==  Grid->SelectedTFS) );
//     if (m_tfe || m_tfs )
//     {
        MenuContextCreate(X, Y);
/*        TPoint P = pbMain->ClientToScreen(TPoint(X, Y));
        PopupMenu->Popup(P.x, P.y); */
		return;
//     }
   }

}


//---------------------------------------------------------------------------
void TfrmMain::AddWorkShape(int AType)
{
   TBaseWorkShape* WH;
   WH = Grid->AddWorkShape(AType, f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
   WH->OnShapeCopy = &ShapeCopy;
   WH->ParentShapeID = LevelController->ParentShapeID;
   assert(WH);
   f_CurrIDShape = WH->LastShapeId;
   f_CurrIDLine = WH->LastLineId;
   f_CurrIDBlock++;
   MainList->AddShapeToList(f_IdAlternative, f_NumAlternative, WH , LevelController->ParentShapeID);
   Grid->PreparePaint();
   SetNewPolygon();
   SetNewPosition();
   InvalidateRgn(pbMain->Parent->Handle, Grid->GetRegion(WH, 4), false);

   if (AType == 2)
   {
     Application->ProcessMessages();
     WH = Grid->AddWorkShape(AType, f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
     WH->OnShapeCopy = &ShapeCopy;
     WH->ParentShapeID = LevelController->ParentShapeID;
     assert(WH);
     f_CurrIDShape = WH->LastShapeId;
     f_CurrIDLine = WH->LastLineId;
     f_CurrIDBlock++;
     MainList->AddShapeToList(f_IdAlternative, f_NumAlternative, WH , LevelController->ParentShapeID);
     Grid->PreparePaint();
     SetNewPolygon();
     SetNewPosition();
     InvalidateRgn(pbMain->Parent->Handle, Grid->GetRegion(WH, 4), false);
   }
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ListChange()
{
  MainList->FillPainterList(Grid->g_PainterList, f_IdAlternative, f_NumAlternative, LevelController->ParentShapeID);
}


void __fastcall TfrmMain::AlternateListChange()
{
   f_AlternateController->FillAlternateList(Grid->g_AlternateList,
     LevelController->ParentShapeID, f_IdAlternative, f_NumAlternative);

}


//---------------------------------------------------------------------------
void TfrmMain::SetNewPolygon()
{
   TPoint P;
   P =  Grid->GetPointPolygon(sbX->Position, sbY->Position);
   if ((P.x - pbMain->Width - sbX->Position) > 2)
     sbX->Max = P.x  - pbMain->Width + (Grid->StepPixels * 4);
   if ((P.y - pbMain->Height - sbY->Position) > 2)
     sbY->Max = P.y  - pbMain->Height + (Grid->StepPixels * 4);
}


//--------------------------------------------------------------------------
void TfrmMain::SetNewPosition()
{
   //TPoint P;
   TRect R;
   TBaseWorkShape *W;
   //P =  Grid->GetPointPolygon(sbX->Position, sbY->Position);
   W =  Grid->LastWorkShape;
   if (W)
   {
     R =  W->GetFrameRectWithLines();
     if ((R.Right + abs(Grid->OffsetSumX) - pbMain->Width - sbX->Position) > (Grid->StepPixels * 2))
         sbX->Position = sbX->Max;
     if ((R.Bottom + abs(Grid->OffsetSumY) - pbMain->Height - sbY->Position) > (Grid->StepPixels * 2))
         sbY->Position = sbY->Max;
   }
}




//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbXChange(TObject *Sender)
{
   TRect R;
   X_Ofs = sbX->Position - X_Base;
   X_Base = sbX->Position;
   Grid->ApplyOffset(-X_Ofs, 0);
   Grid->PreparePaint();
   if (X_Ofs < 0)
     R = TRect(0,0, abs(X_Ofs) + 3, pbMain->Height);
   else
     R = TRect(pbMain->Width - X_Ofs  - 3, 0, pbMain->Width, pbMain->Height);
   ScrollDC(pbMain->Canvas->Handle, -X_Ofs, 0, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlMain->Handle, &R, false);
   UpdateWindow(pnlMain->Handle);
   //Application->ProcessMessages();//очень важная вещь, необходима для прогонки отрисовки
   //и когда необходимо завесить прогу
//   TimerMain->Enabled = false;
//   TimerMain->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sbYChange(TObject *Sender)
{
   TRect R;
   Y_Ofs = sbY->Position - Y_Base;
   Y_Base = sbY->Position;
   Grid->ApplyOffset(0, -Y_Ofs);
   Grid->PreparePaint();
   if (Y_Ofs < 0)
     R = TRect(0,0,  pbMain->Width, abs(Y_Ofs) + 3);
   else
     R = TRect(0, pbMain->Height - Y_Ofs  - 3, pbMain->Width, pbMain->Height);

   ScrollDC(pbMain->Canvas->Handle, 0, - Y_Ofs, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlMain->Handle, &R, false);
   UpdateWindow(pnlMain->Handle);
//   TimerMain->Enabled = false;
//   TimerMain->Enabled = true;

}


TBaseWorkShape* TfrmMain::FindPriorWorkShape(TBaseWorkShape *W)
{
   return MainList->FindPriorNode(W);
}

TBaseWorkShape* TfrmMain::FindNextWorkShape(TBaseWorkShape *W)
{
  return MainList->FindNextNode(W);
}


//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
//Обработка сообщений
//------------------------------------------------------------------------
void __fastcall TfrmMain::M_gd_gettypshape(TMessage& Msg)
{
    int *p;
    p = (int*)(Msg.LParam);
    *p = GetTypShape();

}

//------------------------------------------------------------------------
void __fastcall TfrmMain::M_gd_addworkshape(TMessage& Msg)
{


}


//------------------------------------------------------------------------
void __fastcall TfrmMain::M_gd_paint(TMessage& Msg)
{
  Grid->PreparePaint();
  switch (Msg.WParam)
  {
    case 0 :
       pbMain->Invalidate();
       break;
    case 1 :
       InvalidateRgn(pbMain->Parent->Handle, HRGN(Msg.LParam), false);
       break;
    case 2:
       InvalidateRgn(pbMain->Parent->Handle, HRGN(Msg.LParam), false);
       UpdateWindow(pnlMain->Handle);
       break;
  }
}


//------------------------------------------------------------------------
void __fastcall TfrmMain::M_gd_paintoneprepare(TMessage& Msg)
{
//  Grid->PreparePaint();
  if (Msg.WParam == 1)
     InvalidateRgn(pbMain->Parent->Handle, HRGN(Msg.LParam), false);
  else
     pbMain->Invalidate();
}


void __fastcall TfrmMain::M_le_mouseenter(TMessage& Msg)
{
   Grid->ReapintFlag(true, (TBaseShape*)Msg.WParam);
}

void __fastcall TfrmMain::M_le_mouseleave(TMessage& Msg)
{
   Grid->ReapintFlag(false, (TBaseShape*)Msg.WParam);
}


void __fastcall TfrmMain::M_gd_getnextworkshape(TMessage& Msg)
{
   TBaseWorkShape *W;
   TBaseWorkShape **WRES;
   W = (TBaseWorkShape*)(Msg.WParam);
   WRES = (TBaseWorkShape**)(Msg.LParam);
   (*WRES) = FindNextWorkShape(W);
}

void __fastcall TfrmMain::M_gd_getpriorworkshape(TMessage& Msg)
{
   TBaseWorkShape *W;
   TBaseWorkShape **WRES;
   W = (TBaseWorkShape*)(Msg.WParam);
   WRES = (TBaseWorkShape**)(Msg.LParam);
   (*WRES) = FindPriorWorkShape(W);
}


void __fastcall TfrmMain::M_gd_setnewpolygon(TMessage& Msg)
{
   if ( (Msg.WParam == 1) && (Msg.LParam == 0) )
     SetNewPolygon();
   if ( (Msg.WParam == 0) && (Msg.LParam == 1) )
     SetNewPosition();
   if ( (Msg.WParam == 1) && (Msg.LParam == 1) )
   {
      SetNewPolygon();
      SetNewPosition();
   }
}


void __fastcall TfrmMain::M_gd_insertworkshape(TMessage& Msg)
{
   TBaseWorkShape *WBefore;
   int typ = GetTypShape();
   if ((typ > 0) && (Grid->Regim == 1))
   {
     if (Msg.WParam == 0)
	 {
	   WBefore = (TBaseWorkShape*)(Msg.LParam);
       InsertWorkShape(typ, WBefore);
     }
     if (Msg.WParam == 2)
       AddWorkShape(typ);
     SectionBar->DownFalse();
   }
   Operation = 0;
}

void __fastcall TfrmMain::M_gd_insertworkshapefromfile(TMessage& Msg)
{
   TBaseWorkShape *WBefore;
   if (Grid->Regim == 5)
   {
     if (Msg.WParam == 0)
     {
       WBefore = (TBaseWorkShape*)(Msg.LParam);
       InsertTFSFromFile(WBefore);
     }
     if (Msg.WParam == 2)
       acLoadTFSFromFileExecute(NULL);
   }
   Operation = 0;
}



void __fastcall TfrmMain::M_gd_setalternate(TMessage& Msg)
{
  int m_IdAlt;
  TBaseWorkShape *m_s, *m_e;
  String Rep;
  int m_num;
  m_s = (TBaseWorkShape*)(Msg.WParam);
  m_e = (TBaseWorkShape*)(Msg.LParam);
  if ( MainList->CompareWorkShape(&m_s, &m_e) )
  {
    if ( (m_s != m_e) && (m_e->Tag == 0))
      m_e = FindPriorWorkShape(m_e);
    Rep = "Создать альтернативы между ТФС "+IntToStr(m_s->BlockId) + " и ТФС " + IntToStr(m_e->BlockId) + " ?";
	m_IdAlt = f_AlternateController->IsExistsAlternate(m_s, m_e);
	if ( m_IdAlt == -1 )
    {
      if (Application->MessageBox(Rep.c_str(), _T("ГЭС Интеллект-3"), MB_YESNO	) == ID_YES)
      {
         Operation = 0;
         CreateAlternative(m_s, m_e);
      }
    }
    else
    {
        Operation = 0;
        LoadAlternative(m_IdAlt);
    }
  }
  if (Operation)
    Operation = 0;
}


void __fastcall TfrmMain::M_gd_visiblearrowall(TMessage& Msg)
{
   switch (Msg.LParam)
   {
     case 0:
       f_AlternateController->VisibleArrow(Grid->SelectedTFS, Msg.WParam == 1);
       break;
     case 1:
       f_AlternateController->VisibleArrowAll(Msg.WParam == 1);
       break;
   }
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::M_gd_deletetfslist(TMessage& Msg)
{
  int m_IdAlt;
  TBaseWorkShape *m_s, *m_e;
  String Rep;
  int m_num;
  bool m_last;
  m_s = (TBaseWorkShape*)(Msg.WParam);
  m_e = (TBaseWorkShape*)(Msg.LParam);
  if ( MainList->CompareWorkShape(&m_s, &m_e) )
  {
 //   if ( (m_s != m_e) && (m_e->Tag == 0))
 //     m_e = FindPriorWorkShape(m_e);
    Rep = "Удалить блоки от ТФС "+IntToStr(m_s->BlockId) + " до ТФС " + IntToStr(m_e->BlockId) + " ?";
    if (Application->MessageBox(Rep.c_str(), _T("ГЭС Интеллект-3"), MB_YESNO	) == ID_YES)
    {
         m_last = m_e->Tag == 1;
         Operation = 0;
         DeleteTFSList(m_s ,m_e, ( m_last && (m_e == Grid->LastWorkShape) ));
    }
    else
    {
        Operation = 0;
    }
  }
  if (Operation)
    Operation = 0;
}

void __fastcall TfrmMain::M_gd_getmaintabcount(TMessage& Msg)
{
    int *p;
    p =  (int*)(Msg.LParam);
    *p =  tcMain->Tabs->Count;
}




//---------------------------------------------------------------------------








void __fastcall TfrmMain::ApplicationEventsIdle(TObject *Sender,
	  bool &Done)
{

  //__idls++;
   Grid->ReactMouse(Mouse->CursorPos);
 //  SBar->SimpleText = IntToStr(__idls);
   Done = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::pbMainMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   SBar->SimpleText = "X= "+IntToStr(X)+ "  Y="+IntToStr(Y);
   Grid->MouseMove(Sender, Shift, X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pbMainMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TShiftState St;
   St << ssLeft;
   if ( Shift != St )
     SectionBar->DownFalse();
   Grid->MouseDown(Sender, Button, Shift, X, Y);
//   if ( (Grid->MouseOperation == 2) && (Grid->SelectedTFS) )
//     f_AlternateController->VisibleArrow(Grid->SelectedTFS, false);

}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetOperation(int AValue)
{
   int OldOperation;
   if (f_Operation != AValue)
   {
      OldOperation = f_Operation;
      f_Operation = AValue;
      switch ( f_Operation )
	  {
		case 0:
        {
           if (OldOperation == 1)//была вставка ТФС
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlag(0, false);
           }
           if (OldOperation == 2)//была вставка альтернатив
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlagForAlternative(false);
           }
           if (OldOperation == 4)//была вставка альтернатив
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlagForDeleteTFS(false);
           }
           if (OldOperation == 5)//была вставка ТФС из файла
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlag(0, false);
           }
           if (OldOperation == 6)//была вставка альтернатив
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlagForDeleteTFS(false);
           }
           if (OldOperation == 7)//была вставка ТФС из буфера
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlag(0, false);
           }

           if ( !Grid->IsAltWSListEmpty() )
           {
              ClearAltWSList();
           }
           break;
        }
        case 1:
        {
		   Grid->Regim = f_Operation;
		   Grid->ApplyVisibleFlag(0, true);
           break;
        }
        case 2:
        {
           Grid->Regim = f_Operation;
           Grid->ApplyVisibleFlagForAlternative(true);
           break;
        }
        case 4:
        {
           Grid->Regim = f_Operation;
           Grid->ApplyVisibleFlagForDeleteTFS(true);
           break;
        }
        case 5:
        {
           Grid->Regim = f_Operation;
           Grid->ApplyVisibleFlag(0, true);
           break;
        }
        case 6:
        {
           Grid->Regim = f_Operation;
           Grid->ApplyVisibleFlagForDeleteTFS(true);
           break;
        }
        case 7:
        {
           if(Grid->g_PainterList->Count)
           {
             Grid->Regim = f_Operation;
             Grid->ApplyVisibleFlag(0, true);
           }
           else  LoadFromCanal();
           break;
        }

      }

   }

}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::acInsertBlockExecute(TObject *Sender)
{
   Operation = 0;
   Operation = 1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TfrmMain::InsertWorkShape(int AType, TBaseWorkShape *WBefore)
{
   TBaseWorkShape* WH;
   WH = Grid->InsertWorkShape(AType, WBefore, f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
   WH->ParentShapeID = LevelController->ParentShapeID;
   WH->OnShapeCopy = &ShapeCopy;
   f_CurrIDShape = WH->LastShapeId;
   f_CurrIDLine = WH->LastLineId;
   f_CurrIDBlock++;
   MainList->InsertShapeToList(f_IdAlternative, f_NumAlternative, WBefore, WH, LevelController->ParentShapeID);
   Grid->PreparePaint();
   SetNewPolygon();
   Grid->RecalcBaseOffsetPosition();
   f_AlternateController->RecalcPosition(LevelController->ParentShapeID, f_IdAlternative, f_NumAlternative);
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);

   if (AType == 2)
   {
     WH = Grid->InsertWorkShape(AType, WBefore, f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
     WH->ParentShapeID = LevelController->ParentShapeID;
     WH->OnShapeCopy = &ShapeCopy;
     f_CurrIDShape = WH->LastShapeId;
     f_CurrIDLine = WH->LastLineId;
     f_CurrIDBlock++;
     MainList->InsertShapeToList(f_IdAlternative, f_NumAlternative, WBefore, WH, LevelController->ParentShapeID);
     Grid->PreparePaint();
     SetNewPolygon();
     Grid->RecalcBaseOffsetPosition();
     f_AlternateController->RecalcPosition(LevelController->ParentShapeID, f_IdAlternative, f_NumAlternative);
	 InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   }
}

void __fastcall TfrmMain::acInsertBlockUpdate(TObject *Sender)
{
    dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
    dynamic_cast<TAction*>(Sender)->Checked = (Operation == 1) && (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if ( Key == VK_ESCAPE )
  {
     Operation = 0;
     Key = 0;
  }
  if ( Key == VK_F1)
  {
     acHelpExecute(NULL);
     Key = 0;
  }

}

void TfrmMain::PrepareScroll()
{
   X_Base = Y_Base =  X_Ofs = Y_Ofs = 0;
   sbY->Max = 0;
   sbX->Max = 0;
   Grid->ApplyOffset(-Grid->OffsetSumX, -Grid->OffsetSumY);
}


//---------------------------------------------------------------------------
void TfrmMain::LevelDown(int AParentShapeID)
{
/*
   X_Base = Y_Base =  X_Ofs = Y_Ofs = 0;
   sbY->Max = 0;
   sbX->Max = 0;
   Grid->ApplyOffset(-Grid->OffsetSumX, -Grid->OffsetSumY);
*/

   int mAltID, mNumAlt, mIDParent;
   f_StackHistory->AppendInteger(f_IdAlternative, (void*)(f_NumAlternative));
   MainList->GetAlternateInfo(AParentShapeID, mAltID, mNumAlt, mIDParent);
   if ( (mAltID != f_IdAlternative)  || (mNumAlt != f_NumAlternative) )
   {
      f_IdAlternative = mAltID;
      f_NumAlternative = mNumAlt;
   }
   LevelController->Push(AParentShapeID);
   f_AltStackController->CurrentItem->NumAlternative = f_NumAlternative;
   PrepareTabs(f_NumAlternative);
   PrepareScroll();
   ListChange();
   AlternateListChange();
   Grid->PrepareLevel();
   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(false, TPoint(40, 100));
   Grid->PreparePaint();
   SetNewPolygon();
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}

//---------------------------------------------------------------------------
void TfrmMain::LevelUp()
{
   TLevelItem* UpLevel;
   TDynamicArrayItem *Item = f_StackHistory->Last();
   if (Item)
   {
      f_IdAlternative = Item->Int_Value;
      f_NumAlternative = int(Item->P);
      f_StackHistory->Pop();
   }
   UpLevel = LevelController->Pop();
   if (UpLevel)
   {
      PrepareScroll();
	  PrepareTabs(f_NumAlternative);
	  ListChange();
      AlternateListChange();

	  Grid->PrepareLevel();
	  Grid->PreparePaint();

      SetNewPolygon();
      f_AlternateController->CoordinateCorrect();
      InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   }

}


//---------------------------------------------------------------------------
void TfrmMain::LevelUpReplace()
{
   TLevelItem* UpLevel;
   UpLevel = LevelController->Pop();
   if (UpLevel)
   {
      PrepareScroll();

      TTreeList* m_TreeList = new TTreeList;
      m_TreeList->FillTreeFromList(MainList);
      f_AV->Load(m_TreeList->MainTreeList);

      // g_PainterList


      delete  m_TreeList;

      PrepareTabs(f_NumAlternative);
      ListChange();
      AlternateListChange();

      Grid->PrepareLevel();
      Grid->PreparePaint();

      SetNewPolygon();
      f_AlternateController->CoordinateCorrect();
	  InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   }

}



void __fastcall TfrmMain::acRollupExecute(TObject *Sender)
{
    LevelUp();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acRollupUpdate(TObject *Sender)
{
    dynamic_cast<TAction*>(Sender)->Enabled = ( (LevelController->ParentShapeID != 0) &&
      (tcMain->Tabs->Count == 0) );
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::ShapeCopy(TBaseShape *Shape, int Num_Shape)
{
   if ( MainList->IsContainsChildShape(Shape->ID) )
     Shape->PenColor = f_HaveChildColor;
   if (Shape->ParamAlt)
   {
     if (f_AltParamShapeColorEnable)
     {
       Shape->BrushStyle = bsSolid;
       Shape->BrushColor = f_AltParamShapeColor;
     }
     else
       Shape->BrushStyle = bsClear;
     Shape->PenColor = f_AltParamLineColor;
   }

}

//---------------------------------------------------------------------------


void __fastcall TfrmMain::acExpandUpdate(TObject *Sender)
{
   bool enb = Grid->SelectedTFE;
   if (enb)
     enb = Grid->SelectedTFE->PowerIn();
   dynamic_cast<TAction*>(Sender)->Enabled = enb;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acExpandExecute(TObject *Sender)
{
   LevelDown(Grid->SelectedTFE->ID);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAlternateExecute(TObject *Sender)
{
    Operation = 0;
    Operation = 2;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::tcMainChange(TObject *Sender)
{
/*   Grid->PrepareLevel();
   Grid->PreparePaint();
   SetNewPolygon();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
 */
   if (Operation)
    Operation = 0;

   f_NumAlternative =  reinterpret_cast<int>(tcMain->Tabs->Objects[tcMain->TabIndex]);

   PrepareScroll();
   ListChange();
   AlternateListChange();
   Grid->PrepareLevel();
   Grid->PreparePaint();
   SetNewPolygon();
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);


// ShowMessage(IntToStr(reinterpret_cast<int>(tcMain->Tabs->Objects[tcMain->TabIndex])));
}
//---------------------------------------------------------------------------


void TfrmMain::CreateAlternative(TBaseWorkShape* WS, TBaseWorkShape *WE)
{
   TAltSelectorItem* Item;
   f_IdAlternativeParent = f_IdAlternative;
   f_NumAlternativeParent = f_NumAlternative;

   Item = f_AltSelector->CreateNewAlternateID(LevelController->ParentShapeID, 1);
   f_IdAlternative = Item->ID;
   f_NumAlternative = Item->Num;
   f_AlternateController->AddAlternateItem(WS, WE, f_IdAlternative,
       f_NumAlternative, f_IdAlternativeParent, f_NumAlternativeParent);
   MainList->CreateAlternate(WS, WE, f_IdAlternative, f_NumAlternative);
   f_AltStackController->Push(f_IdAlternative, f_NumAlternative,
      f_IdAlternativeParent, f_NumAlternativeParent);
//   f_AlternateController->ApplyOffsetForNoOffset(-Grid->OffsetSumX, -Grid->OffsetSumY/*,
//      LevelController->ParentShapeID, f_IdAlternativeParent, f_NumAlternativeParent  */);

   PrepareScroll();
   PrepareAlternative(f_NumAlternative);
//   f_AlternateController->CoordinateCorrect();
}


void TfrmMain::LoadAlternative(int AIdAlt)
{
   TAltSelectorItem* Item;
   f_IdAlternativeParent = f_IdAlternative;
   f_NumAlternativeParent = f_NumAlternative;

   Item = f_AltSelector->FindFirst(AIdAlt, LevelController->ParentShapeID);

   f_IdAlternative = Item->ID;
   f_NumAlternative = Item->Num;
   f_AltStackController->Push(f_IdAlternative, f_NumAlternative,
	  f_IdAlternativeParent, f_NumAlternativeParent);
  // f_AlternateController->CoordinateCorrect();///stassssssssssss
//   f_AlternateController->ApplyOffsetForNoOffset(-Grid->OffsetSumX, -Grid->OffsetSumY/*,
//      LevelController->ParentShapeID, f_IdAlternativeParent, f_NumAlternativeParent*/  );
   PrepareScroll();
   PrepareAlternative(f_NumAlternative);
   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(false, TPoint(40, 100));



}



void TfrmMain::PrepareTabs(int ANumActive)
{
   AnsiString S;
   TAltSelectorItem* Item;
   tcMain->Tabs->Clear();
   if (!f_NumAlternative && !f_IdAlternative) return;
   Item = f_AltSelector->FindFirst(f_IdAlternative, LevelController->ParentShapeID);
   while (Item)
   {
      S = "Альтернатива №("+IntToStr(f_IdAlternative)+"/"+ IntToStr(Item->Num)+")";
      tcMain->Tabs->AddObject(S, reinterpret_cast<TObject*>(Item->Num));
      Item = f_AltSelector->FindNext();
   }
   if(ANumActive - 1 < tcMain->Tabs->Count)
     tcMain->TabIndex = ANumActive - 1;
   else
     tcMain->TabIndex = tcMain->Tabs->Count - 1;
}


void TfrmMain::PrepareAlternative(int ANumAlt)
{
   PrepareTabs(f_NumAlternative);

   ListChange();
   AlternateListChange();
   Grid->PrepareLevel();
   Grid->PreparePaint();
   f_AlternateController->CoordinateCorrect();///stassssssssssss
   SetNewPolygon();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}


void TfrmMain::AddAlternativeNum()
{
   f_NumAlternative = f_AltSelector->AddAltItem(f_IdAlternative);
   MainList->AddAlternate(f_IdAlternative, f_NumAlternative);
   PrepareScroll();
   PrepareAlternative(f_NumAlternative);
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}








void TfrmMain::HighlightAlternative(int AId)
{
   TBaseWorkShape* Item;
   TBaseWorkShape *WSF, *WSL;
   WSF = NULL;
   WSL = NULL;
   Operation = 0;
   UpdateWindow(pnlMain->Handle);
   ClearAltWSList();
   if (MainList->GetWSToAlternate(AId, &WSF, &WSL))
   {
     if ( MainList->CompareWorkShape(&WSF, &WSL) )
     {
       Item = WSF;
       while (true)
       {
          Grid->AddToAltWSList(Item);
          if (( Item == WSL ) || (!Item)) break;
          Item = FindNextWorkShape(Item);
	   }
	   InvalidateRgn(pbMain->Parent->Handle, Grid->GetRGNAltWSList(), false);
     }
   }
   Operation = 3;
}


void TfrmMain::ClearAltWSList()
{
   HRGN R;
   R = Grid->GetRGNAltWSList();
   Grid->ClearAltWSList();
   if (R)
   {
      InvalidateRgn(pbMain->Parent->Handle, R, false);
      UpdateWindow(pnlMain->Handle);
   }
}



//---------------------------------------------------------------------------
void TfrmMain::DeleteSelectedTFS()
{
/*  TNodeAlt* Node;
  MainList->PrepareDeleteWorkShape(Grid->SelectedTFS);
  Node = MainList->StackDustController->FirstAlt();
  while (Node)
  {
     f_AltSelector->DeleteAltItem(Node->ID, Node->Num);
     Node = MainList->StackDustController->NextAlt();
  }
  Node = MainList->StackDustController->FirstAlt();
  while (Node)
  {
     f_AlternateController->DeleteAlternateItem2(Node->ID, false);
     MainList->DeleteAlternate(Node->ID, Node->Num);
     Node = MainList->StackDustController->NextAlt();
  }
  MainList->PrepareLinksBeforeDelete(Grid->SelectedTFS);
  MainList->DeleteWorkShape();
  Grid->SelectedTFS = NULL;
  ListChange();
  AlternateListChange();
  Grid->RecalcAfterDeleted();
  if (Grid->g_PainterList->First())
    Grid->PrepareLevelOnOffset();
  else
    Grid->PrepareLevel();
  Grid->PreparePaint();
  SetNewPolygon();
//   DeleteAlternate(int AID, int ANum)
  f_AlternateController->CoordinateCorrect();
  InvalidateRgn(pbMain->Parent->Handle, NULL, false);       */
}




void __fastcall TfrmMain::acAlternateUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAltAddExecute(TObject *Sender)
{
   AddAlternativeNum();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAltAddUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (tcMain->Tabs->Count > 0) ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAltRollupExecute(TObject *Sender)
{
   CheckEmptyAlternate(f_IdAlternative);
   f_AltStackController->Pop();
   f_IdAlternative = f_AltStackController->CurrentItem->IdAlternative;
   f_NumAlternative = f_AltStackController->CurrentItem->NumAlternative;
   f_IdAlternativeParent = f_AltStackController->CurrentItem->IdAlternativeParent;
   f_NumAlternativeParent = f_AltStackController->CurrentItem->NumAlternativeParent;
   PrepareTabs(f_NumAlternative);
   PrepareScroll();
   ListChange();
   AlternateListChange();
   Grid->PrepareLevel();
   Grid->PreparePaint();
   SetNewPolygon();
//   DeleteAlternate(int AID, int ANum)
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAltRollupUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (tcMain->Tabs->Count > 0) ;
}
//---------------------------------------------------------------------------



void TfrmMain::MenuAlternateItemCreate(TAlternateItem *AItem, int AX, int AY)
{
   int m_num;
   TPoint P;
   TMenuItem *NewItem;
   f_MenuController->Clear();
   for (int i = 0; i <= AItem->ArrowWorkShape->CountNodeHint - 1; i++)
   {
      m_num = AItem->ArrowWorkShape->NodeHind[i];
      NewItem = new TMenuItem(this);
      if (NewItem)
      {
         NewItem->Tag = m_num;
//         NewItem->Action = acAltShow;
         NewItem->OnClick =  AltShow;
         NewItem->Caption = "Альтернатива №"+IntToStr(m_num);
         PmAlternate->Items->Add(NewItem);
         f_MenuController->AddMenu(NewItem);
	  }
   }
   P = pbMain->ClientToScreen(TPoint(AX, AY));
   PmAlternate->Popup(P.x, P.y);


/*
  TMenuItem *NewItem = new TMenuItem(this);
  if (NewItem){
  NewItem->Caption = "Мяню";
  NewItem->Name = "BNM";
 // cnt++;
  NewItem->Tag = cnt;
  NewItem->OnClick = ManuClick; // ===> то что тебе надо
  PopupMenu1->Items->Add (NewItem);
  ShowMessage(IntToStr(PopupMenu1->Items->Count));
  }

  TPoint P = this->ClientToScreen(TPoint(X, Y));
  PopupMenu1->Popup(P.x, P.y);
  delete NewItem;
  ShowMessage(IntToStr(PopupMenu1->Items->Count));
*/

}

void __fastcall TfrmMain::AltShow(TObject *Sender)
{
  HighlightAlternative(dynamic_cast<TMenuItem*>(Sender)->Tag);
}

void __fastcall TfrmMain::acAltShowExecute(TObject *Sender)
{
   HighlightAlternative(dynamic_cast<TAction*>(Sender)->Tag);
}


void TfrmMain::CheckEmptyAlternate(int AId)
{
   TAltSelectorItem* Item;
   TNodeMain *ND;
   int m_cnt, m_del;
   m_cnt = m_del = 0;
   Item = f_AltSelector->FindFirst(AId, LevelController->ParentShapeID);
   while (Item)
   {
      m_cnt++;
      ND = MainList->SearchFirstNodeToAlternate(Item->ID, Item->Num, Item->ParentShapeID);
      if (!ND)
      {
        MainList->DeleteAlternate(Item->ID, Item->Num);
        f_AltSelector->DeleteAltItem(Item->ID, Item->Num);
        m_del++;
      }
      Item = f_AltSelector->FindNext();
   }
   if ( (m_cnt) && (m_cnt == m_del) )
      f_AlternateController->DeleteAlternateItem2(AId);

}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::acNewExecute(TObject *Sender)
{
   if (MainList->IsEmpty()) return;
   if (!f_IsDebug && (Application->MessageBox(_T("Вы действительно хотите удалить все ТФС?"),
	_T("ГЭС Интеллект-3"), MB_ICONWARNING | MB_YESNO) == ID_NO)) return;
   ClearWorkSpace();
}

//---------------------------------------------------------------------------
void TfrmMain::DoDeleteWorkSahpeWithAlternate(TBaseWorkShape* WS, int AParentShapeID, TList *AList)
{
   TNodeAlt *AF, *AE;
   TAltSelectorItem* Item;
   TNodeMain* N;
   TList *m_L = new TList;
   if (AList->IndexOf(WS) == -1)
     AList->Add(WS);
   AF = MainList->CheckAlternateWSFirst(WS);
   if (AF)
   {
      Item = f_AltSelector->FindFirst(AF->ID, AParentShapeID);
	  while(Item)
	  {
         N = MainList->SearchFirstNodeToAlternate(Item->ID, Item->Num, Item->ParentShapeID);
         while(N)
         {
            m_L->Add(N->WorkShape);
            N =  MainList->SearchNextNodeToAlternate(Item->ID, Item->Num, N);
         }
         Item = f_AltSelector->FindNext();
      }
   }

   AE = MainList->CheckAlternateWSEnd(WS);
   if (AE)
   {
      Item = f_AltSelector->FindFirst(AE->ID, AParentShapeID);
      while(Item)
      {
         N = MainList->SearchFirstNodeToAlternate(Item->ID, Item->Num, Item->ParentShapeID);
         while(N)
         {
            m_L->Add(N->WorkShape);
//            DoDeleteWorkSahpeWithAlternate(N->WorkShape, AParentShapeID, AList);
            N =  MainList->SearchNextNodeToAlternate(Item->ID, Item->Num, N);
         }
         Item = f_AltSelector->FindNext();
      }
   }
   for (int i = 0; i <= m_L->Count - 1; i++)
    DoDeleteWorkSahpeWithAlternate(static_cast<TBaseWorkShape*>(m_L->Items[i]), AParentShapeID, AList);
   delete m_L;

}


//---------------------------------------------------------------------------
void TfrmMain::DeleteWorkSahpeWithAlternate(TBaseWorkShape* WS)
{
   TBaseWorkShape *WD;
   TList *m_List = new TList;
   try
   {
	 DoDeleteWorkSahpeWithAlternate(WS, WS->ParentShapeID, m_List);
	 for (int i = 0; i <= m_List->Count - 1; i++)
     {
        WD = static_cast<TBaseWorkShape*>(m_List->Items[i]);
        //ShowMessage(IntToStr(WD->BlockId));
        DeleteWorkSahpe(WD);
     }
   }
   __finally
   {
      delete  m_List;
   }

}



//---------------------------------------------------------------------------
void TfrmMain::DeleteWorkSahpe(TBaseWorkShape* WS)
{
  TNodeAlt* Node;
  TBaseWorkShape *W1, *W2;

  MainList->PrepareDeleteWorkShape(WS);
  Node = MainList->StackDustController->FirstAlt();
  while (Node)
  {
     f_AltSelector->DeleteAltItem(Node->ID, Node->Num);
     Node = MainList->StackDustController->NextAlt();
  }
  Node = MainList->StackDustController->FirstAlt();
  while (Node)
  {
     f_AlternateController->DeleteAlternateItem2(Node->ID, false);
     MainList->DeleteAlternate(Node->ID, Node->Num);
     Node = MainList->StackDustController->NextAlt();
  }
  f_AlternateController->DeleteWorkShape(WS);
  MainList->PrepareLinksBeforeDelete(WS);
  MainList->DeleteWorkShape();
}




//---------------------------------------------------------------------------

void __fastcall TfrmMain::acDeleteTFSUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = ( Grid->SelectedTFS != NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acDeleteTFSExecute(TObject *Sender)
{
   TPoint P = Grid->SelectedTFS->StartPoint;
   bool fs = (Grid->FirstWorkShape == Grid->SelectedTFS);
//   if ( MainList->CheckAlternateWS(Grid->SelectedTFS)  > 0 )
//   {
//     Application->MessageBox("Удаление не допускается!","Гелиос", NULL);
//     return;
//   }
   DeleteWorkSahpeWithAlternate(Grid->SelectedTFS);
   Grid->SelectedTFS = NULL;
   ListChange();
   AlternateListChange();
  // PrepareScroll();
   //Grid->PrepareLevel();//sssssssssss
   Grid->RecalcAfterDeleted(fs, P);
   if (Grid->g_PainterList->First())
     Grid->PrepareLevelOnOffset();
   else
     Grid->PrepareLevel();

   Grid->PreparePaint();
   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(fs, P);
   Grid->PreparePaint();
   Grid->RecalcBaseOffsetPosition();
   SetNewPolygon();
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);

 //  DeleteSelectedTFS();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N2Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acDeleteTFSPointToPointExecute(TObject *Sender)
{
   Operation = 0;
   Operation = 4;
}
//---------------------------------------------------------------------------


void TfrmMain::DeleteTFSList(TBaseWorkShape* AFirst, TBaseWorkShape* ALast, bool ALastInclude)
{
   TBaseWorkShape* MNext = AFirst;
   TList *m_l = new TList();
   do
   {
      m_l->Add(MNext);
      MNext = FindNextWorkShape(MNext);
   } while ( MNext && (MNext != ALast) );
   if ( (ALastInclude) && (AFirst != ALast) )
     m_l->Add(ALast);
   for (int i = 0; i <= m_l->Count - 1; i++)
   {
    /* if ( MainList->CheckAlternateWS(static_cast<TBaseWorkShape*>(m_l->Items[i]))  > 0 )
     {
        Application->MessageBox("Удаление не допускается!", "Гелиос", NULL);
        delete m_l;
        return;
     }*/
     DeleteWorkSahpeWithAlternate(static_cast<TBaseWorkShape*>(m_l->Items[i]));
   }
   delete m_l;
   ListChange();
   AlternateListChange();
   Grid->RecalcAfterDeleted(false, TPoint(40, 100));
   if (Grid->g_PainterList->First())
     Grid->PrepareLevelOnOffset();
   else
     Grid->PrepareLevel();

   Grid->PreparePaint();
   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(false, TPoint(40, 100));
   Grid->PreparePaint();
   Grid->RecalcBaseOffsetPosition();
   SetNewPolygon();
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);


}


//---------------------------------------------------------------------------



void __fastcall TfrmMain::acDeleteTFSPointToPointUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acSaveListExecute(TObject *Sender)
{
   AnsiString Pt, Fn, Ex, Tmp;
   bool s_xml;
   if ( SaveDLG->Execute() )
   {
	  Pt = ExtractFilePath(SaveDLG->FileName);
	  Fn = ExtractFileName(SaveDLG->FileName);
	  Ex = ExtractFileExt(SaveDLG->FileName);
	  Tmp = Fn.SubString(1, Fn.Length() - Ex.Length());
	  s_xml = (SaveDLG->FilterIndex == 2);
	  if(s_xml)
		Fn = Pt + Tmp + ".xml";
	  else
		Fn = Pt + Tmp + ".gls";
	  ShowCursorStorage();
	  if(s_xml)
		MainList->SaveAllToFile(Fn, f_TypeParam, opt_sadacha->OptSovm);
	  else
		MainList->SaveAllToFileBin(Fn, f_TypeParam, opt_sadacha->OptSovm);
	  MainList->Changes = false;
	  HideCursorStorage();
	  SaveDLG->FileName = Fn;
   }
}
//---------------------------------------------------------------------------



/*
   TBaseWorkShape* WH;
   WH = Grid->AddWorkShape(AType, f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
   WH->OnShapeCopy = &ShapeCopy;
   WH->ParentShapeID = LevelController->ParentShapeID;
   assert(WH);
   f_CurrIDShape = WH->LastShapeId;
   f_CurrIDLine = WH->LastLineId;
   f_CurrIDBlock++;
   MainList->AddShapeToList(f_IdAlternative, f_NumAlternative, WH , LevelController->ParentShapeID);
   Grid->PreparePaint();
   SetNewPolygon();
   SetNewPosition();
   InvalidateRgn(pbMain->Parent->Handle, Grid->GetRegion(WH, 4), false);

                    //-----------------------------------------------------
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (AType > 0)
   {
      switch (AType)
      {
       case 1:
         m_CurrWorkShape = new TWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 2:
		 m_CurrWorkShape = new TPWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
		 break;
       case 3:
         m_CurrWorkShape = new TZWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 4:
         m_CurrWorkShape = new TControlWork(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 5:
         m_CurrWorkShape = new TControlFunc(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 6:
         m_CurrWorkShape = new TBifurcation(f_CurrEndPoint.x, f_CurrEndPoint.y, f_StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
      }


      m_CurrWorkShape->LEControl = f_LEControl;
      m_CurrWorkShape->WndHandler = f_WndHandler;
      m_CurrWorkShape->UnderControl = f_UnderControl;
      m_CurrWorkShape->OnWSFlagCreate = WsFlagCreate;
      m_CurrWorkShape->OnWSFlagDestroy = WsFlagDestroy;
      m_CurrWorkShape->BaseStartPoint.x+= -f_X_offsSum;
      m_CurrWorkShape->BaseStartPoint.y+= -f_Y_offsSum;
      m_CurrWorkShape->Init();
      m_CurrWorkShape->Prepare();
      f_CurrEndPoint = m_CurrWorkShape->EndPoint;

      f_CurrentCommand = 1;
   }
   return m_CurrWorkShape;


*/
TBaseWorkShape* TfrmMain::DoCreateWorkShape(int AType, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine)
{
   TBaseWorkShape *m_CurrWorkShape = NULL;
   if (AType > 0)
   {
      switch (AType)
	  {
       case 1:
		 m_CurrWorkShape = new TWork(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
		 break;
       case 2:
         m_CurrWorkShape = new TZWork(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 3:
         m_CurrWorkShape = new TZWorkOR(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 4:
         m_CurrWorkShape = new TControlWork(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 5:
         m_CurrWorkShape = new TControlFunc(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 6:
         m_CurrWorkShape = new TBifurcation(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 7:
         m_CurrWorkShape = new TCheckConditionCW(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 8:
         m_CurrWorkShape = new TCycleWhileDo(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 9:
         m_CurrWorkShape = new TCycleDoWhileDo(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 10:
         m_CurrWorkShape = new TCycleDoWhileDoFC(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;
       case 11:
         m_CurrWorkShape = new TCheckCondition(0, 0, Grid->StepPixels, ACurrIDShape, ACurrIDBlock, ACurrIDLine);
         break;

      }


      m_CurrWorkShape->LEControl = true;
      m_CurrWorkShape->WndHandler = this->Handle;
      m_CurrWorkShape->UnderControl = pbMain;
      Grid->SetWSFlagEvent(m_CurrWorkShape);
      m_CurrWorkShape->OnShapeCopy = &ShapeCopy;
   }
   return m_CurrWorkShape;
}

void TfrmMain::LoadFromFile(AnsiString AFileName, bool isNew)
{
	TPoint AStart(40, 100);
    TNodeMain* Node = MainList->FindLastNodeToAlternate(f_IdAlternative, f_NumAlternative, LevelController->ParentShapeID);
    if (Node)
       AStart = Node->WorkShape->EndPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    TDischargedMassiv *ogr = NULL;
	if (isNew)
	  ogr = opt_sadacha->OptSovm;
    if ( Loader->LoadFromFile(AFileName, ogr) )
    {
      DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadMainListNew(Loader, LevelController->ParentShapeID);
      DoLoadMainListPrepareLink(Loader);
      DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      if(Node)
        DoPrepareFirstAlternate(Loader, AStart);
      if (isNew)
        f_TypeParam = Loader->TypeParam;
    }
	delete Loader;
	MainList->ClearNodeTypeCreate();
	ListChange();
	AlternateListChange();
	Grid->PrepareLevelOnOffset();
	Grid->PreparePaint();
	f_AlternateController->CoordinateCorrect();
	SetNewPolygon();
    f_CurrIDShape = MainList->TFEMaxID;
    f_CurrIDBlock = MainList->NodeMaxID + 1;
	InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}


void TfrmMain::LoadFromFileBin(AnsiString AFileName, bool isNew)
{
	TPoint AStart(40, 100);
	TNodeMain* Node = MainList->FindLastNodeToAlternate(f_IdAlternative, f_NumAlternative, LevelController->ParentShapeID);
	if (Node)
       AStart = Node->WorkShape->EndPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    TDischargedMassiv *ogr = NULL;
    if (isNew)
	  ogr = opt_sadacha->OptSovm;
    if ( Loader->LoadFromFileBin(AFileName, ogr) )
    {
      DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadMainListNew(Loader, LevelController->ParentShapeID);
      DoLoadMainListPrepareLink(Loader);
      DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      if(Node)
        DoPrepareFirstAlternate(Loader, AStart);
      if (isNew)
        f_TypeParam = Loader->TypeParam;
    }
    delete Loader;
    MainList->ClearNodeTypeCreate();
    ListChange();
    AlternateListChange();
    Grid->PrepareLevelOnOffset();
    Grid->PreparePaint();
    f_AlternateController->CoordinateCorrect();
    SetNewPolygon();
    f_CurrIDShape = MainList->TFEMaxID;
    f_CurrIDBlock = MainList->NodeMaxID + 1;
	InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}


void TfrmMain::DoInsertTFSFromFile(AnsiString AFileName, TBaseWorkShape *WBefore)
{
    TNodeMain* Node;
    TLoaderTFSMain* Main;
    TPoint  AStart = WBefore->StartPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    try
    {
      Loader->LoadFromFile(AFileName, NULL);
	  DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative); //rrr
	  DoLoadMainListNew(Loader, LevelController->ParentShapeID); //rrr
      DoLoadMainListPrepareLink(Loader, WBefore);
      DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      DoPrepareFirstAlternate(Loader, AStart);
      Main = Loader->FindLastToAlternate(f_IdAlternative, f_NumAlternative);
      MainList->ClearNodeTypeCreate();
      ListChange();
      AlternateListChange();
      Node = static_cast<TNodeMain*>(Main->Tag);
      Grid->PrepareLevelOnOffset();

      Grid->RecalcAfterConverted(false, TPoint(40, 100));
      Grid->RecalcFollowWorkShape(WBefore, Node->WorkShape->EndPoint);
      Grid->PreparePaint();
      f_AlternateController->CoordinateCorrect();
      SetNewPolygon();
    //Grid->RecalcBaseOffsetPosition();

//        Grid->RecalcBaseOffsetPosition();

      f_CurrIDShape = MainList->TFEMaxID;
      f_CurrIDBlock = MainList->NodeMaxID + 1;
      InvalidateRgn(pbMain->Parent->Handle, NULL, false);
    }catch(...){}
    delete Loader;


}

void TfrmMain::DoInsertTFSFromFileBin(AnsiString AFileName, TBaseWorkShape *WBefore)
{
    TNodeMain* Node;
    TLoaderTFSMain* Main;
    TPoint  AStart = WBefore->StartPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    try
    {
      Loader->LoadFromFileBin(AFileName, NULL);
      DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative); //rrr
      DoLoadMainListNew(Loader, LevelController->ParentShapeID); //rrr
	  DoLoadMainListPrepareLink(Loader, WBefore);
	  DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      DoPrepareFirstAlternate(Loader, AStart);
      Main = Loader->FindLastToAlternate(f_IdAlternative, f_NumAlternative);
      MainList->ClearNodeTypeCreate();
      ListChange();
      AlternateListChange();
      Node = static_cast<TNodeMain*>(Main->Tag);
      Grid->PrepareLevelOnOffset();

      Grid->RecalcAfterConverted(false, TPoint(40, 100));
      Grid->RecalcFollowWorkShape(WBefore, Node->WorkShape->EndPoint);
      Grid->PreparePaint();
      f_AlternateController->CoordinateCorrect();
      SetNewPolygon();
    //Grid->RecalcBaseOffsetPosition();

//        Grid->RecalcBaseOffsetPosition();

      f_CurrIDShape = MainList->TFEMaxID;
      f_CurrIDBlock = MainList->NodeMaxID + 1;
      InvalidateRgn(pbMain->Parent->Handle, NULL, false);
    }catch(...){}
    delete Loader;


}




void TfrmMain::DoLoadPrepareInc(TLoaderTFS* ALoaderTFS, int AParentID, int AParentNum)
{
   if (ALoaderTFS)
   {
     if (MainList->NodeMaxID > 0)
     {
       ALoaderTFS->IncTfsID(MainList->NodeMaxID);
       ALoaderTFS->IncTfeID(MainList->TFEMaxID);
       ALoaderTFS->IncAltID(MainList->AlternateMaxID, AParentID, AParentNum);
     }
   }
}

void TfrmMain::DoPrepareFirstAlternate(TLoaderTFS* ALoaderTFS, TPoint AStartPoint)
{
   TLoaderTFSAlternate  *Item;
   TLoaderTFSItemAlternate *AltItem;
   TLoaderTFSMain *Main;
   TBaseWorkShape *WS;
   int m_x, m_y, m_bx, m_by;
   Item = ALoaderTFS->Alternate[0];
   AltItem = Item->AltItems[0];
   Main  = ALoaderTFS->FindNodeOutBlockID(AltItem->Id);
   WS = static_cast<TNodeMain*>(Main->Tag)->WorkShape;
   m_x = AStartPoint.x - WS->StartPoint.x;
   m_y = AStartPoint.y - WS->StartPoint.y;
   m_bx = -Grid->OffsetSumX;
   m_by = -Grid->OffsetSumY;
   for (int i = 0; i <= Item->AltCount - 1; i++  )
   {
      AltItem = Item->AltItems[i];
      Main  = ALoaderTFS->FindNodeOutBlockID(AltItem->Id);
      WS = static_cast<TNodeMain*>(Main->Tag)->WorkShape;
      WS->StartPoint.x = WS->StartPoint.x + m_x;
      WS->StartPoint.y = WS->StartPoint.y + m_y;
      WS->BaseStartPoint.x = WS->StartPoint.x + m_bx;
      WS->BaseStartPoint.y = WS->StartPoint.y + m_by;
      WS->SetOffsetPosition(m_x , m_y );
      WS->Prepare();
   }

}

void TfrmMain::DoLoadAlternate(TLoaderTFS* ALoaderTFS, int AParentID, int AParentNum)
{
   TLoaderTFSAlternate  *Item, *AParent;
   TLoaderTFSAncestor *Ancestor;
   TBaseWorkShape *WS, *WE;
   TLoaderTFSMain* Node;
   int m_ParentShapeID;
   if (!ALoaderTFS) return;
   for (int i = 0; i <= ALoaderTFS->AlternateCount - 1; i++)
   {
	  Item = ALoaderTFS->Alternate[i];
      Ancestor  = ALoaderTFS->FindAncestorOutBlockID(Item->NodeStartID); //первый узел всегда должен быть
      if(Ancestor)
        m_ParentShapeID = Ancestor->IdShapeAncestor;
      else
        m_ParentShapeID = LevelController->ParentShapeID;
	  f_AltSelector->CreateNewAlternateID2(Item->Id, m_ParentShapeID, Item->Num);
      if (Item->Id)
      {
        Node = ALoaderTFS->FindNodeOutBlockID(Item->NodeStartID);
        if (Node)
          WS = static_cast<TNodeMain*>(Node->Tag)->WorkShape;
        else
          WS = NULL;

        Node = ALoaderTFS->FindNodeOutBlockID(Item->NodeEndID);
        if (Node)
          WE = static_cast<TNodeMain*>(Node->Tag)->WorkShape;
        else
          WE = NULL;

        AParent = ALoaderTFS->FindAlternativeParentNew(Item);
        if (AParent)
		  f_AlternateController->AddAlternateItem(WS, WE, Item->Id, Item->Num,
			  AParent->Id, AParent->Num);
//        else
//          if(AParentID)
//             f_AlternateController->AddAlternateItem(WS, WE, Item->Id, Item->Num,
//                AParentID, AParentNum);

		if ( !MainList->CreateAlternate(WS, WE, Item->Id, Item->Num) )
			MainList->AddAlternate(Item->Id, Item->Num);

      }
   }
}


bool TfrmMain::DoLoadAncestor(TLoaderTFS* ALoaderTFS, int AParentShapeID)
{
   TLoaderTFSAncestor* Item;
   TLoaderTFSMain* Main;
   TNodeMain *ANode;
   for (int i = 0; i <= ALoaderTFS->AncestorCount - 1; i++)
   {
      Item = ALoaderTFS->Ancestor[i];
      MainList->CreateNodeAncestor(Item->IdBlock, Item->IdShapeAncestor);

   }
   if (AParentShapeID > 0)
   {
     for (int i = 0; i <= ALoaderTFS->MainNodeCount - 1; i++)
     {
        Main = ALoaderTFS->MainNode[i];
        Item = ALoaderTFS->FindAncestorNew(Main);
        if (!Item)
        {
          ANode = static_cast<TNodeMain*>(Main->Tag);
          MainList->FillNodeAncestor(ANode);
        }
     }
   }
   return true;
}

void TfrmMain::DoLoadParamAlt(TBaseWorkShape* AWS, TLoaderTFSMain* AMainItem, int AIdOffs)
{
   TLoaderTFSItemMain* mi;
   TBaseShape* bs;
   for (int i = 0; i <= AMainItem->TFECount -1; i++)
   {
     mi = AMainItem->TFEItems[i];
     if (mi->ListParams->Count > 0)
     {
        bs = AWS->ShapeSupportID(mi->Id);
        for(int j = 0; j <= mi->ListParams->Count -1; j++)
          bs->AddParamAlternativeItem(static_cast<TParamAlternativeItem*>(mi->ListParams->Items[j]));
     }
   }

}


AnsiString TfrmMain::DoLoadMainListNew(TLoaderTFS* ALoaderTFS, int AParentShapeID)
{
   TLoaderTFSMain *MainItem;
   TBaseWorkShape *WS;
   TNodeMain *ANode;
   TLoaderTFSAlternate *Alt;
   TLoaderTFSAncestor *Ancestor;
   int m_minTfsId, m_minTfeId, m_minLineId;
   if (!ALoaderTFS) return "NULL";
   m_minLineId = f_CurrIDLine;
   for (int i = 0; i <= ALoaderTFS->MainNodeCount - 1; i++ )
   {
      MainItem = ALoaderTFS->MainNode[i];
      m_minTfsId = MainItem->Id;
      m_minTfeId = MainItem->MinTFE;
      Alt = ALoaderTFS->FindAlternativeNew(MainItem);
      if (!Alt)
        return "Ошибка загрузки альтернатив! " + IntToStr(MainItem->Id);
	  Ancestor  = ALoaderTFS->FindAncestorNew(MainItem);
	  WS =  DoCreateWorkShape(MainItem->TypeId, m_minTfeId , m_minTfsId,  m_minLineId);
      WS->StartPoint = MainItem->StartPoint;
      WS->BaseStartPoint = MainItem->StartPoint;
	  WS->Init();
      //WS->Prepare(); //убрал 10.12.2006 поставил ниже
	  m_minLineId = WS->LastLineId;
      ANode = MainList->CreateNode(WS);
      ANode->IdAlternate = Alt->Id;
      ANode->NumAlt = Alt->Num;
      ANode->IdBlock = WS->BlockId;
      if (Ancestor)
      {
        ANode->IdParentShape = Ancestor->IdShapeAncestor;
        ANode->WorkShape->ParentShapeID = Ancestor->IdShapeAncestor;
      }
      else
      {
        ANode->IdParentShape = AParentShapeID;
        ANode->WorkShape->ParentShapeID = AParentShapeID;
      }
      MainList->PrepareAddNode(ANode);
      MainItem->Tag = ANode;
      WS->SetOffsetPosition(MainItem->OffsetX , MainItem->OffsetY );
	  WS->SetBaseOffsetPosition(MainItem->OffsetX, MainItem->OffsetY);
	  WS->Prepare(); // поставил  10.12.2006

      /*
         загрузка параметрических альтернатив
      */
      DoLoadParamAlt(WS, MainItem, m_minTfeId);

   }
   f_CurrIDLine = m_minLineId;
   return "";
}

void TfrmMain::DoLoadMainListPrepareLink(TLoaderTFS* ALoaderTFS)
{
   TNodeMain *ANode, *NPrior;
   TLoaderTFSMain *MainItem, *Tmp;
   for (int i = 0; i <= ALoaderTFS->MainNodeCount - 1; i++ )
   {
     MainItem = ALoaderTFS->MainNode[i];
     ANode = static_cast<TNodeMain*>(MainItem->Tag);
     Tmp = ALoaderTFS->FindNext(MainItem);
     if (Tmp)
       ANode->Next = MainList->FindNode(static_cast<TNodeMain*>(Tmp->Tag)->WorkShape);

     Tmp = ALoaderTFS->FindPrior(MainItem);
     if (Tmp)
       ANode->Prior = MainList->FindNode(static_cast<TNodeMain*>(Tmp->Tag)->WorkShape);
     else
     {
        NPrior = MainList->FindLastNodeToAlternate(ANode->IdAlternate, ANode->NumAlt, ANode->IdParentShape);
		if (NPrior && (!NPrior->TypeCreate)) //не первый узел
        {
           NPrior->Next = ANode;
           ANode->Prior = NPrior;
		}
     }
   }
}

void TfrmMain::DoLoadMainListPrepareLink(TLoaderTFS* ALoaderTFS, TBaseWorkShape *WBefore)
{
   TNodeMain *ANode, *NBefore;
   TLoaderTFSMain *MainItem, *Tmp;
   NBefore = MainList->FindNode(WBefore);
   for (int i = 0; i <= ALoaderTFS->MainNodeCount - 1; i++ )
   {
     MainItem = ALoaderTFS->MainNode[i];
     ANode = static_cast<TNodeMain*>(MainItem->Tag);
     Tmp = ALoaderTFS->FindNext(MainItem);
     if (Tmp)
       ANode->Next = MainList->FindNode(static_cast<TNodeMain*>(Tmp->Tag)->WorkShape);
     else
     {
             if ( (NBefore) && (NBefore->IdAlternate == ANode->IdAlternate) &&
             (NBefore->NumAlt == ANode->NumAlt) && (NBefore->IdParentShape == ANode->IdParentShape) &&
             (!NBefore->TypeCreate)  )
         {
        ANode->Next = NBefore;
        NBefore->Prior = ANode;
        }

     }
     Tmp = ALoaderTFS->FindPrior(MainItem);
     if (Tmp)
       ANode->Prior = MainList->FindNode(static_cast<TNodeMain*>(Tmp->Tag)->WorkShape);
     else
     {


        if ( (NBefore) && (NBefore->IdAlternate == ANode->IdAlternate) &&
             (NBefore->NumAlt == ANode->NumAlt) && (NBefore->IdParentShape == ANode->IdParentShape) &&
			 (!NBefore->TypeCreate)  )
        {
           ANode->Prior = NBefore->Prior;
           if (NBefore->Prior)
             NBefore->Prior->Next = ANode;
        }
     }
   }
}

void TfrmMain::InsertTFSFromFile(TBaseWorkShape *WBefore)
{
   if (OpenDLG->Execute())
   {
     ShowCursorStorage();
     AnsiString Ext = ExtractFileExt(OpenDLG->FileName);
     if (SameText(Ext, ".xml"))
       DoInsertTFSFromFile(OpenDLG->FileName, WBefore);
     if (SameText(Ext, ".gls"))
       DoInsertTFSFromFileBin(OpenDLG->FileName, WBefore);
     HideCursorStorage();
  }
}



void __fastcall TfrmMain::acInsertTFSFromFileExecute(TObject *Sender)
{
  Operation = 0;
  Operation = 5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acLoadTFSFromFileExecute(TObject *Sender)
{
   bool isNew = Sender;
   AnsiString Ext;
   if (OpenDLG->Execute())
   {
     if (isNew)
       ClearWorkSpace();
     ShowCursorStorage();
     Ext = ExtractFileExt(OpenDLG->FileName);
     if (SameText(Ext, ".xml"))
	   LoadFromFile(OpenDLG->FileName, isNew);
     if (SameText(Ext, ".gls"))
       LoadFromFileBin(OpenDLG->FileName, isNew);
	 MainList->Changes = false;
     Grid->RecalcAfterConverted(false, TPoint(40, 100));
     Grid->PreparePaint();
     f_AlternateController->CoordinateCorrect();
     SetNewPolygon();
     SetNewPosition();
     InvalidateRgn(pbMain->Parent->Handle, NULL, false);
	 HideCursorStorage();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acInsertTFSFromFileUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
   dynamic_cast<TAction*>(Sender)->Checked = (Operation == 5) && (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::acAltViewUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acAltViewExecute(TObject *Sender)
{
  TTreeList* m_TreeList = new TTreeList;
  m_TreeList->FillTreeFromList(MainList);
  Application->CreateForm(__classid(TfrmAlternateView), &frmAlternateView);
  frmAlternateView->LoadAlternative(m_TreeList);
  frmAlternateView->MColorSetup = f_ColorSetup;
  frmAlternateView->ShowModal();
  frmAlternateView->Release();
  delete  m_TreeList;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   int res;
   if (!f_IsDebug && MainList->Changes && !MainList->IsEmpty())
   {
	  res = DialogExitExecute();
	  if ( res == 0 )
		CanClose = false;
	  if ( res == 1)
		acSaveListExecute(NULL);
   }
   if (CanClose)
	 FreeHelp();
}
//---------------------------------------------------------------------------
void TfrmMain::SaveSettings()
{
   f_RSettings->LocalPath = "Setup";
   f_RSettings->SaveInteger("StepPixel", f_StepPixel);
   f_RSettings->SaveBool("PaintPixels", f_PaintPixels);
   f_RSettings->SaveInteger("FonColor", f_FonColor);
   f_RSettings->SaveInteger("PixelColor", f_PixelColor);
   f_RSettings->SaveBool("DrawFrameLine", f_DrawFrameLine);
   f_RSettings->SaveInteger("FrameLineColor", f_FrameLineColor);
   f_RSettings->SaveInteger("LineColor", f_LineColor);
   f_RSettings->SaveBool("BrushTFE", f_BrushTFE);
   f_RSettings->SaveInteger("BrushColor", f_BrushColor);
   f_RSettings->SaveBool("BoldTFELine", f_WSPenWidth == 2);
   f_RSettings->SaveInteger("FlagType", f_FlagType);
   f_RSettings->SaveInteger("ColorEnter", f_ColorEnter);
   f_RSettings->SaveInteger("ColorLeave", f_ColorLeave);
   f_RSettings->SaveInteger("FrameColorTFE", f_FrameColorTFE);
   f_RSettings->SaveInteger("FrameColorTFS", f_FrameColorTFS);
   f_RSettings->SaveInteger("HaveChildColor", f_HaveChildColor);
   f_RSettings->SaveInteger("AltFlagColor", f_AltFlagColor);
   f_RSettings->SaveInteger("AltEnterFlagColor", f_AltEnterFlagColor);
   f_RSettings->SaveInteger("AltArrowColor", f_AltArrowColor);
   f_RSettings->SaveInteger("AltEnterArrowColor", f_AltEnterArrowColor);
   f_RSettings->SaveInteger("AltLineColor", f_AltLineColor);
   f_RSettings->SaveBool("CanModifyPenWidth", f_CanModifyPenWidth);
   f_RSettings->SaveString("HelpFile", f_HelpFile);
   f_RSettings->SaveBool("HelpHideBar", f_HelpHideBar);
   f_RSettings->SaveString("FontTFE", FontToStr(f_FontTFE));
   f_RSettings->SaveInteger("AltEnabledFlagColor", f_AltEnabledFlagColor);
   f_RSettings->SaveInteger("TypeParam", f_TypeParam);

   f_RSettings->SaveInteger("AltParamLineColor", f_AltParamLineColor);
   f_RSettings->SaveInteger("AltParamShapeColor", f_AltParamShapeColor);
   f_RSettings->SaveBool("AltParamShapeColorEnable", f_AltParamShapeColorEnable);

   f_RSettings->SaveInteger("VwColorAlt", f_VwColorAlt);
   f_RSettings->SaveInteger("VwColorBadAlt", f_VwColorBadAlt);

   f_RSettings->SaveBool("SectionBarAlternativeColor", f_SectionBarAlternativeColor);

   SaveActions();
}


//---------------------------------------------------------------------------
void TfrmMain::RestoreSettings()
{
   bool BoldLine;
   f_RSettings->LocalPath = "Setup";
   f_StepPixel = f_RSettings->GetInteger("StepPixel", 8);
   f_PaintPixels = f_RSettings->GetBool("PaintPixels", true);
   f_FonColor = TColor(f_RSettings->GetInteger("FonColor", clWhite));
   f_PixelColor = TColor(f_RSettings->GetInteger("PixelColor", clBlack));
   f_DrawFrameLine = f_RSettings->GetBool("DrawFrameLine", false);
   f_FrameLineColor = TColor(f_RSettings->GetInteger("FrameLineColor", clBlack));
   f_LineColor = TColor(f_RSettings->GetInteger("LineColor", clBlack));
   f_BrushTFE = f_RSettings->GetBool("BrushTFE", false);
   f_BrushColor = TColor(f_RSettings->GetInteger("BrushColor", clWhite));
   BoldLine = f_RSettings->GetBool("BoldTFELine", false);
   if (BoldLine)
     f_WSPenWidth = 2;
   else
     f_WSPenWidth = 1;
   f_FlagType = f_RSettings->GetInteger("FlagType", 1);
   f_ColorEnter = TColor(f_RSettings->GetInteger("ColorEnter", clYellow));
   f_ColorLeave = TColor(f_RSettings->GetInteger("ColorLeave", clRed));
   f_FrameColorTFE = TColor(f_RSettings->GetInteger("FrameColorTFE", clRed));
   f_FrameColorTFS = TColor(f_RSettings->GetInteger("FrameColorTFS", clRed));
   f_HaveChildColor = TColor(f_RSettings->GetInteger("HaveChildColor", clGreen));
   f_AltFlagColor = TColor(f_RSettings->GetInteger("AltFlagColor", clBlue));
   f_AltEnterFlagColor = TColor(f_RSettings->GetInteger("AltEnterFlagColor", clAqua));
   f_AltArrowColor = TColor(f_RSettings->GetInteger("AltArrowColor", clBlue));
   f_AltEnterArrowColor = TColor(f_RSettings->GetInteger("AltEnterArrowColor", clAqua));
   f_AltLineColor = TColor(f_RSettings->GetInteger("AltLineColor", clBlue));
   f_CanModifyPenWidth = f_RSettings->GetBool("CanModifyPenWidth", false);
   f_HelpFile =  f_RSettings->GetString("HelpFile");
   f_HelpHideBar = f_RSettings->GetBool("HelpHideBar", false);
   if (f_HelpFile.Length() == 0)
     f_HelpFile = "<programm>help\\index.html";
   StrToFont(f_RSettings->GetString("FontTFE"), f_FontTFE);
   f_AltEnabledFlagColor = TColor(f_RSettings->GetInteger("AltEnabledFlagColor", clSilver));
   f_TypeParam = f_RSettings->GetInteger("TypeParam", PROP);

   f_AltParamLineColor = TColor(f_RSettings->GetInteger("AltParamLineColor", clFuchsia));
   f_AltParamShapeColor = TColor(f_RSettings->GetInteger("AltParamShapeColor", clYellow));
   f_AltParamShapeColorEnable = f_RSettings->GetBool("AltParamShapeColorEnable", false);
   f_VwColorAlt = TColor(f_RSettings->GetInteger("VwColorAlt", RGB(0, 0, 255)));
   f_VwColorBadAlt = TColor(f_RSettings->GetInteger("VwColorBadAlt", RGB(255, 0, 0)));
   f_SectionBarAlternativeColor = f_RSettings->GetBool("SectionBarAlternativeColor", false);
   RestoreActions();
}


void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  SaveSettings();
}


TCompositeBaseWork* TfrmMain::CreateCompositeWS(TBaseWorkShape* ATFS)
{
    TCompositeBaseWork* WS = NULL;
    switch (ATFS->TypeShape)
    {
       case 1:
       {
          WS = new TCompositeWork;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }
       case 2:
       {
          WS = new TCompositeZWork;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }
       case 3:
       {
          WS = new TCompositeZWorkOR;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }

       case 4:
       {
          WS = new TCompositeControlWork;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
		  break;
	   }
       case 5:
       {
          WS = new TCompositeControlFunc;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }
       case 6:
       {
          WS = new TCompositeBifurcation;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }

       case 7:
       {
          WS = new TCompositeCheckConditionCW;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }

       case 8:
       {
          WS = new TCompositeCycleWhileDo;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }

       case 9:
       {
          WS = new TCompositeCycleDoWhileDo;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }

       case 10:
	   {
		  WS = new TCompositeCycleDoWhileDoFC;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }


       case 11:
       {
          WS = new TCompositeCheckCondition;
          WS->ColorSetup = f_ColorSetup;
          WS->ConvertWorkShapeFromBase(ATFS, f_AV);
          break;
       }
    }
    return WS;

}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::acExpandReplaceExecute(TObject *Sender)
{
   TAlternateViewItem* Item;
   TAlternateViewItemTFS* TFS;
   TCompositeBaseWork *W, *Find;
   TCompositeBaseWorkItem* F;
   TCompositeWork *S;
   TBaseWorkShape *WS;
   TPoint PS;
   int  mRes;

   TTreeList* m_TreeList = new TTreeList;
   m_TreeList->FillTreeFromList(MainList);
   f_AV->Load(m_TreeList->MainTreeList);


   int m_id = Grid->SelectedTFE->ID;
   Grid->PrepareLevelOnOffset();

   WS = Grid->FindShapeFromCompositeWork(m_id);
   if(!WS->CompositeWorkShape)
   {
	 WS->CompositeWorkShape = CreateCompositeWS(WS);
	 WS->CompositeWorkShape->Prepare();
   }

   TDynamicArray *D = new TDynamicArray;
   Application->CreateForm(__classid(TfrmAlternateViewSelect), &frmAlternateViewSelect);
   frmAlternateViewSelect->AV = f_AV;
   frmAlternateViewSelect->MColorSetup = f_ColorSetup;
   for (int i = 0; i <= f_AV->ItemCount - 1; i++)
   {
	  Item = f_AV->ItemView[i];
	  if (Item->ParentTFE)
	  {
		if (Item->ParentTFE->BaseShape->ID == m_id)
		{
		   TDynamicArray *DItem = new TDynamicArray;
		   for (int j = 0 ; j <= Item->ItemCount - 1; j++)
		   {
			  TFS = Item->ItemTFS[j];
			  DItem->Append(TFS);
		   }
		   D->Append(DItem);
		 }
	  }
   }

   TDynamicArray *Del = new TDynamicArray;
   for(int i = 0 ; i <= D->Count - 1; i++)
   {
	  TDynamicArray *DItem1 = static_cast<TDynamicArray*>(D->Items[i]);
	  if(!Del->Find(DItem1))
	  {
		for(int j = i + 1 ; j <= D->Count - 1; j++)
		{
		  TDynamicArray *DItem2 = static_cast<TDynamicArray*>(D->Items[j]);
		  TAlternateViewItemTFS *TFS1, *TFS2;
		  int mcnt = 0;
		  if ( DItem1->Count == DItem2->Count )
		  {
			for(int k = 0; k <= DItem2->Count - 1; k++)
			{
			  TFS1 = static_cast<TAlternateViewItemTFS*>(DItem1->Items[k]);
			  TFS2 = static_cast<TAlternateViewItemTFS*>(DItem2->Items[k]);
			  if (TFS1->BaseWorkShape == TFS2->BaseWorkShape)
				mcnt++;
			}
			if(mcnt == DItem2->Count)
			  Del->Append(DItem2);
		  }
		}
	  }
   }

   for(int i = 0; i <= Del->Count - 1; i++)
   {
	  TDynamicArray *DItem = static_cast<TDynamicArray*>(Del->Items[i]);
	  D->Delete(DItem);
	  delete DItem;
   }
   delete Del;

   for(int i = 0; i <= D->Count - 1; i++)
   {
	  TDynamicArray *DItem = static_cast<TDynamicArray*>(D->Items[i]);
	  frmAlternateViewSelect->AddMassiv(DItem);
	  delete DItem;
   }

   mRes = frmAlternateViewSelect->ShowModal();
   if ( mRes == mrOk )
   {
		frmAlternateViewSelect->GetAlternate(D);
		F = WS->CompositeWorkShape->FindItem(m_id, &Find);
		PS = F->StartPoint;
		WS->CompositeWorkShape->History->CreateItem(F, Find);
		for(int k = 0; k <= D->Count - 1; k++)
		{
		  TFS = static_cast<TAlternateViewItemTFS*>(D->Items[k]);
		  W = frmAlternateViewSelect->CreateWS(TFS);
		  W->StartPoint =  PS;
		  W->Prepare();
		  F->AddCompositeWork(W);
		  PS = W->EndPoint;
		}
		Find->Prepare();
	 }


   frmAlternateViewSelect->Release();
   delete D;
   delete  m_TreeList;
   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(false, TPoint(40, 100));
   Grid->PreparePaint();
   f_AlternateController->CoordinateCorrect();

   TopCorrect();
   SetNewPolygon();
   SetNewPosition();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   UpdateWindow(pbMain->Parent->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acExpandBackExecute(TObject *Sender)
{
   TBaseWorkShape* WS = Grid->SelectedTFS;
   TCompositeStack2* History;
   TCompositeStackItem2 *STI;
   TAlternateViewItemTFS* TFS;
   TCompositeBaseWork *W, *Find;
   TCompositeBaseWorkItem* F;
   TPoint PS;
   if (WS)
   {
      History = WS->CompositeWorkShape->History;
      STI = History->Last();
      STI->CompositeWorkItem->Degenerate();
      STI->CompositeWork->Prepare();
      History->Pop();
   }

   Grid->CoordinateCorrectForCompositeWork();
   Grid->RecalcAfterConverted(false, TPoint(40, 100));

   Grid->PreparePaint();
   f_AlternateController->CoordinateCorrect();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   UpdateWindow(pbMain->Parent->Handle);

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acExpandBackUpdate(TObject *Sender)
{
   TBaseWorkShape* WS = Grid->SelectedTFS;
   bool enb = (WS != NULL) && (WS->CompositeWorkShape != NULL);
   if (enb)
	 enb = !WS->CompositeWorkShape->History->IsEmpty();
   dynamic_cast<TAction*>(Sender)->Enabled = enb;
}



void __fastcall TfrmMain::acExpandReplaceUpdate(TObject *Sender)
{
   TBaseShape* BS = Grid->SelectedTFE;
   bool enb = (BS != NULL);
   if (enb)
      enb = MainList->IsContainsChildShape(BS->ID);
   dynamic_cast<TAction*>(Sender)->Enabled = enb;

}
//---------------------------------------------------------------------------
void TfrmMain::TopCorrect()
{
   TPoint  P =  Grid->GetTopPoint(sbX->Position, sbY->Position);
   if (P.y < 20 + sbY->Position)
   {
     int my = 20 - P.y - sbY->Position;
     Grid->ApplyOffset(0, my);
   }
   Grid->PreparePaint();
}


void __fastcall TfrmMain::acScrollDownExecute(TObject *Sender)
{
   TPoint  P =  Grid->GetTopPoint(sbX->Position, sbY->Position);
   if (P.y < 20 )
   {
     Grid->ApplyOffset(0,  20 - P.y);
     SetNewPolygon();
     SetNewPosition();
     InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::acScrollRightExecute(TObject *Sender)
{
   TPoint  P =  Grid->GetTopPoint(sbX->Position, sbY->Position);
   if (P.x < 20 )
   {
     Grid->ApplyOffset(20 -  P.x, 0);
     SetNewPolygon();
     SetNewPosition();
     InvalidateRgn(pbMain->Parent->Handle, NULL, false);
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::acHelpExecute(TObject *Sender)
{
   bool ex;
   AnsiString S = GetHelpFile(f_HelpFile, ex);
   if (ex)
	 ShowHelp(S, false, f_HelpHideBar);
   else
	 Application->MessageBox(_T("Не найден файл справки!"), _T("ГЭС Интеллект-3"), MB_ICONWARNING);
}
//---------------------------------------------------------------------------



bool __fastcall TfrmMain::ApplicationEventsHelp(WORD Command, int Data,
      bool &CallHelp)
{
   acHelpExecute(NULL);
   CallHelp  = false;
   return true;

}
//---------------------------------------------------------------------------

void TfrmMain::ShowPredicateModel(AnsiString AStruct, AnsiString ARab, AnsiString AControlRab,
          AnsiString AControlFunc, AnsiString ACheckCondition, AnsiString AOptZadacha, AnsiString *ADopPrav)
{
   Application->CreateForm(__classid(TfrmPredicateView), &frmPredicateView);
   frmPredicateView->REStruct->Text = AStruct;
   frmPredicateView->RERab->Text = ARab;
   frmPredicateView->REControlRab->Text = AControlRab;
   frmPredicateView->REControlFunc->Text = AControlFunc;
   frmPredicateView->RECheckCondition->Text = ACheckCondition;
   frmPredicateView->REOptZadacha->Text = AOptZadacha;
   frmPredicateView->REDopPrav->Text = *ADopPrav;
   frmPredicateView->ShowModal();
   *ADopPrav = frmPredicateView->REDopPrav->Text;
   frmPredicateView->Release();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::acGraphTFEConvertExecute(TObject *Sender)
{
   PredicateModel(f_PredicatePath->UsedPath);
}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::acShowParamAlternateUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = Grid->SelectedTFE;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acShowParamAlternateExecute(TObject *Sender)
{
   TBaseWorkShape* Sel =  Grid->FindShapeFromCompositeWork(Grid->SelectedTFE->ID);
   if (Sel)
   {
	 if (Sel->CompositeWorkShape)
	 {
	   TCompositeBaseWork *F;
	   Grid->FindComositeBaseWork2(Grid->SelectedTFE->ID,  &F);
	   Sel = F->ConvertedBWS;
	 }
	 TBaseWorkShape* WN =  Grid->CreateTempWorkShape(Sel->TypeShape, TPoint(0,0), Sel->FirstShapeId - 1);

	 Graphics::TBitmap* Glp = new Graphics::TBitmap;
	 BuildGlp(WN, Glp, Grid->SelectedTFE);
	 ShowParamAlternative(Grid->SelectedTFE, LevelController->ParentShapeID, f_TypeParam, Glp, false);
	 delete  WN;
	 delete Glp;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acParamPropUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Checked =  f_TypeParam == PROP;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acParamFuzzyUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Checked =  f_TypeParam == FUZZY;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acParamFuzzyExecute(TObject *Sender)
{
   f_TypeParam = FUZZY;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acParamPropExecute(TObject *Sender)
{
   f_TypeParam = PROP;
}
//---------------------------------------------------------------------------

void TfrmMain::BuildGlp(TBaseWorkShape* AWN, Graphics::TBitmap* Glp, TBaseShape *ASel)
{
   TBaseShape* BS;
   Application->CreateForm(__classid(TfmParamAlternative), &fmParamAlternative);
   Glp->Width = fmParamAlternative->pbTfs->Width;
   Glp->Height = fmParamAlternative->pbTfs->Height;
   fmParamAlternative->Release();
   Application->ProcessMessages();
   Glp->Canvas->Brush->Color = f_FonColor;
   Glp->Canvas->FillRect(TRect(0,0, Glp->Width, Glp->Height));
   AWN->StartPoint = TPoint(0, 0);
   AWN->Init();
   AWN->Prepare();
   if ( f_BrushTFE )
     AWN->BrushStyle = bsSolid;
   else
     AWN->BrushStyle = bsClear;
   AWN->BrushColor = f_BrushColor;
   AWN->LineWidth = f_WSPenWidth;
   AWN->PenWidth = f_WSPenWidth;
   AWN->Font->Assign(f_FontTFE);
   AWN->FrameColorTFE = f_FrameColorTFE;
   AWN->PenColor = f_LineColor;

   TRect R = AWN->GetFrameRectWithLines();
   int rx = (Glp->Width - R.Width())/2 - R.Left;
   int ry = (Glp->Height - R.Height())/2 - R.Top;
   AWN->SetOffsetPosition(rx, ry);
   AWN->StartPoint = TPoint(rx, ry);

   if (ASel->Clon)
     BS = ASel->Clon;
   else
	 BS = ASel;

   BS = AWN->ShapeSupportID(BS->ID);
   if (BS)
     BS->DrawFrame = true;

   AWN->Prepare();
   AWN->Paint(Glp->Canvas);
}





void __fastcall TfrmMain::acOptZadachaExecute(TObject *Sender)
{
   MainList->GetAllWorkShape(opt_sadacha->MassWork);
   opt_sadacha->InitData();
   opt_sadacha->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::GlsBarRigthDown(TObject *Sender)
{
  acInsertBlock->Execute();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::GlsBarApplyDown(TGLSSectionBar *Sender,
  TSectionBarButton *SectionButton, TMouseButton Button,  bool &AllowChange)
{
  AllowChange = true;
  if (Button == mbRight)
     AllowChange = !SectionButton->Down;
}


void TfrmMain::InitActionList()
{
  TAction* Item;
  TGlsActionListItem* AI;
  for (int i = 0; i <= ActionList->ActionCount - 1; i++)
  {
	 Item = dynamic_cast<TAction*>(ActionList->Actions[i]);
     if (!SameText(Item->Name, "acAltShow"))
     {
       AI = f_ActList->CreateActionItem(Item->Name);
       AI->Action = Item;
       AI->ActCaption = Item->Caption;
       AI->ActHint = Item->Hint;
     }
  }
}

void TfrmMain::MenuContextCreate(int AX, int AY)
{
   TPoint P;
   TMenuItem *NewItem;
   TGlsActionListItem* AI;
   f_ContextMenuController->Clear();
   for (int i = 0; i <= f_ActList->Count - 1; i++)
   {
      AI = f_ActList->Items[i];
      if (AI->SubMenu)
      {
        NewItem = new TMenuItem(this);
        if (NewItem)
        {
           NewItem->Action = AI->Action;
           NewItem->Caption = AI->ActCaption;
           PopupMenu->Items->Add(NewItem);
           f_ContextMenuController->AddMenu(NewItem);
        }
      }
   }
   P = pbMain->ClientToScreen(TPoint(AX, AY));
   PopupMenu->Popup(P.x, P.y);

}
void __fastcall TfrmMain::acGraphTFEConvertUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void TfrmMain::ApplyShortCutToActions()
{
  TGlsActionListItem* AI;
  for (int i = 0; i <= f_ActList->Count - 1; i++)
  {
     AI = f_ActList->Items[i];
     if ( !SameText(AI->SCut, "[нет]") )
       AI->Action->ShortCut = MakeShortCut(AI->SCut, AI->Shift, AI->Ctrl, AI->Alt );
     else
       AI->Action->ShortCut = 0;
  }
}

void TfrmMain::SaveActions()
{
   TGlsActionListItem* AI;
   AnsiString Path;
   for (int i = 0; i <= f_ActList->Count - 1; i++)
   {
     AI = f_ActList->Items[i];
     Path = AI->ActName;
     f_RSettings->LocalPath = "Setup\\Actios\\" + Path;
     f_RSettings->SaveString("NAME",AI->SCut);
     f_RSettings->SaveBool("SHIFT", AI->Shift);
     f_RSettings->SaveBool("CTRL", AI->Ctrl);
     f_RSettings->SaveBool("ALT", AI->Alt);
     f_RSettings->SaveBool("SUBMENU", AI->SubMenu);
   }

}

void TfrmMain::RestoreActions()
{
   bool firstload;
   TGlsActionListItem* AI;
   AnsiString Path, S;
   f_RSettings->LocalPath = "Setup\\";
   firstload = (f_RSettings->GetString("HelpFile").Length() == 0);
   for (int i = 0; i <= f_ActList->Count - 1; i++)
   {
     AI = f_ActList->Items[i];
	 Path = AI->ActName;
	 f_RSettings->LocalPath = "Setup\\Actios\\" + Path;


     S = f_RSettings->GetString("NAME");
     if (S.Length() == 0)
       S = "[нет]";
     AI->SCut = S;

     AI->Shift = f_RSettings->GetBool("SHIFT", false);
     AI->Ctrl = f_RSettings->GetBool("CTRL", false);
     AI->Alt = f_RSettings->GetBool("ALT", false);

     AI->SubMenu = f_RSettings->GetBool("SUBMENU", false);
     if(firstload)
     {
        if ( SameText(AI->ActName, "acShowParamAlternate") ||
             SameText(AI->ActName, "acExpandReplace") ||
             SameText(AI->ActName, "acExpandBack")
            )
        AI->SubMenu = true;
     }

   }

}



void __fastcall TfrmMain::acFindDecisionExecute(TObject *Sender)
{
   unsigned int StartTime, EndTime;
   bool OptAnp = IsOptAnp();
   if ( OptAnp )
	 CreateZadachaOptAnp();

   AnsiString OptZ = opt_sadacha->make_sadacha() + "\r\n" + opt_sadacha->make_ogrsovm();
   f_PredicatePath->Init();
   f_Zadacha->Clear();
   InitTrashCounter();
   InitTFEConvertor();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   TGraphTFEConvertor* GC = new TGraphTFEConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 2;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   GC->Init(TC->Head, f_Zadacha->Tree);
//   f_Zadacha->Init(f_TypeParam, f_CheckNud, FullPredicateModel(GC->PrStruct,
//     GC->PrRab, GC->PrControlRab, GC->PrControlFunc, GC->PrCheckCondition, OptZ, *f_PredicateDopPrav));
   f_Zadacha->Init(f_TypeParam, f_CheckNud, OptAnp, f_OgrSovmArray, FullPredicateModel("","", "", "", "", "", *f_PredicateDopPrav));

   String S;
   S = f_Zadacha->Check();
   if ( S.Length() > 0 )
	 Application->MessageBox(S.c_str(), _T("Ошибка"), MB_ICONWARNING);
   else
   {
	 if ( CreateStartDecision(f_Zadacha, f_TypeParam, opt_sadacha->get_type_metod()) )
     {
       StartTime = GetTickCount();
       f_Zadacha->Process();
       EndTime = GetTickCount();
	   f_Zadacha->ShowDecision(f_VwColorAlt, f_VwColorBadAlt, EndTime - StartTime, f_PredicatePath->BasePath);
     }
     FreeStartDecision();
   }
   delete GC;
   delete TC;
   delete AP;
   delete m_TreeList;
   FreeTFEConvertor();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acFindDecisionUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acMetodOptExecute(TObject *Sender)
{
   int m_type = opt_sadacha->get_type_metod();
   double m_rate = opt_sadacha->Rate;
   if (ShowMetodOpt(m_type, m_rate, m_type, m_rate))
   {
	  opt_sadacha->set_type_metod(m_type);
	  opt_sadacha->Rate = m_rate;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::M_gd_copytfslist(TMessage& Msg)
{
  TBaseWorkShape *m_s, *m_e;
  m_s = (TBaseWorkShape*)(Msg.WParam);
  m_e = (TBaseWorkShape*)(Msg.LParam);
  if ( MainList->CompareWorkShape(&m_s, &m_e) )
  {
    if ( (m_s != m_e) && (m_e->Tag == 0))
      m_e = FindPriorWorkShape(m_e);
	String Rep = "Копировать блоки от ТФС "+IntToStr(m_s->BlockId) + " до ТФС " + IntToStr(m_e->BlockId) + " ?";
	Application->MessageBox(Rep.c_str(), _T("ГЭС Интеллект-3"), MB_YESNO);
  }
  f_ClipCopyTFS->CopyTfsList(MainList, LevelController->ParentShapeID, m_s, m_e);
/*      TTreeList* m_TreeList = new TTreeList;
      m_TreeList->FillTreeFromList(MainList, LevelController->ParentShapeID, m_s, m_e);
     delete  m_TreeList;
*/
  Operation = 0;
}


void __fastcall TfrmMain::acClipCopyTFSExecute(TObject *Sender)
{
   Operation = 0;
   Operation = 6;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::acClipPasteUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = (f_ClipCopyTFS->CanalLength() > 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acClipPasteExecute(TObject *Sender)
{
  Operation = 0;
  Operation = 7;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acClipCopyTFSUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------


void TfrmMain::InsertTFSFromCanal(TBaseWorkShape *WBefore)
{
    TNodeMain* Node;
    TLoaderTFSMain* Main;
    TPoint  AStart = WBefore->StartPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    try
    {
      Loader->LoadFromCanal(f_ClipCopyTFS);
      DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative); //rrr
      DoLoadMainListNew(Loader, LevelController->ParentShapeID); //rrr
      DoLoadMainListPrepareLink(Loader, WBefore);
      DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      DoPrepareFirstAlternate(Loader, AStart);
	  Main = Loader->FindLastToAlternate(f_IdAlternative, f_NumAlternative);
	  MainList->ClearNodeTypeCreate();
	  ListChange();
      AlternateListChange();
      Node = static_cast<TNodeMain*>(Main->Tag);
      Grid->PrepareLevelOnOffset();

	  Grid->RecalcAfterConverted(false, TPoint(40, 100));
	  Grid->RecalcFollowWorkShape(WBefore, Node->WorkShape->EndPoint);
      Grid->PreparePaint();
      f_AlternateController->CoordinateCorrect();
      SetNewPolygon();
	  f_CurrIDShape = MainList->TFEMaxID;
      f_CurrIDBlock = MainList->NodeMaxID + 1;
      InvalidateRgn(pbMain->Parent->Handle, NULL, false);
    }catch(...){}
    delete Loader;
}

void TfrmMain::LoadFromCanal()
{
    TPoint AStart(40, 100);
    TNodeMain* Node = MainList->FindLastNodeToAlternate(f_IdAlternative, f_NumAlternative, LevelController->ParentShapeID);
    if (Node)
       AStart = Node->WorkShape->EndPoint;
    TLoaderTFS* Loader = new TLoaderTFS;
    Loader->LoadFromCanal(f_ClipCopyTFS);
      DoLoadPrepareInc(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadMainListNew(Loader, LevelController->ParentShapeID);
      DoLoadMainListPrepareLink(Loader);
      DoLoadAlternate(Loader, f_IdAlternative, f_NumAlternative);
      DoLoadAncestor(Loader, LevelController->ParentShapeID);
      if(Node)
        DoPrepareFirstAlternate(Loader, AStart);
    delete Loader;
	MainList->ClearNodeTypeCreate();
    ListChange();
    AlternateListChange();
    Grid->PrepareLevelOnOffset();
    Grid->PreparePaint();
	f_AlternateController->CoordinateCorrect();
	SetNewPolygon();
    f_CurrIDShape = MainList->TFEMaxID;
    f_CurrIDBlock = MainList->NodeMaxID + 1;
//    InvalidateRgn(pbMain->Parent->Handle, NULL, false);

    MainList->Changes = true;;
    Grid->RecalcAfterConverted(false, TPoint(40, 100));
    Grid->PreparePaint();
    f_AlternateController->CoordinateCorrect();
    SetNewPolygon();
    SetNewPosition();
    InvalidateRgn(pbMain->Parent->Handle, NULL, false);

}



void __fastcall TfrmMain::M_gd_insertworkshapefromcanal(TMessage& Msg)
{
   TBaseWorkShape *WBefore;
   if (Grid->Regim == 7)
   {
     if (Msg.WParam == 0)
     {
       WBefore = (TBaseWorkShape*)(Msg.LParam);
       InsertTFSFromCanal(WBefore);
     }
     if (Msg.WParam == 2)
       LoadFromCanal();
   }
   Operation = 0;
}

void TfrmMain::ClearWorkSpace()
{
   Operation = 0;
   TAltSelectorItem* Item;
   f_AlternateController->ClearAll();
   f_AltSelector->ClearAll();
   f_AltStackController->ClearAll();
   MainList->ClearAll();
   LevelController->ClearAll();
   LevelController->Push(0);
   Grid->ClearAll();
   f_StackHistory->Clear();
   f_StackHistory->InitStack();

   f_IdAlternative = 0;
   f_CurrIDBlock = 1;
   f_CurrIDShape = 0;
   f_CurrIDLine = 0;
   sbY->Max = 0;
   sbX->Max = 0;
   X_Base = Y_Base = X_Ofs = Y_Ofs = 0;
   Operation = 0;

   Item = f_AltSelector->CreateNewAlternateID(LevelController->ParentShapeID);
   f_IdAlternative = Item->ID;
   f_NumAlternative = f_AltSelector->AddAltItem(f_IdAlternative);
   f_IdAlternativeParent = f_IdAlternative;
   f_NumAlternativeParent = f_NumAlternative;
   MainList->CreateAlternate(NULL, NULL, f_IdAlternative, f_NumAlternative);
   f_AltStackController->Push(f_IdAlternative, f_NumAlternative,
      f_IdAlternativeParent, f_NumAlternativeParent);

   PrepareTabs(f_NumAlternative);
   PrepareScroll();
   ListChange();
   AlternateListChange();
   Grid->PrepareLevel();
   Grid->PreparePaint();
   SetNewPolygon();
   InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}

void __fastcall TfrmMain::acCheckNudExecute(TObject *Sender)
{
    f_CheckNud = !f_CheckNud;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acCheckNudUpdate(TObject *Sender)
{
   MNCheckNudYes->Checked = f_CheckNud;
   MNCheckNudNo->Checked = !f_CheckNud;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acMetodSuperPosExecute(TObject *Sender)
{
   if ( IsOptAnp() )
   {
	 String S = "Используется режим оптимизации возможного АНП.\r\n";
	 S = S + "Изменение метода построения суперпозиции не повлияет на алгоритм поиска решения!";
	 MessageBox(0, S.c_str(), _T("Внимание!"), MB_ICONWARNING);
   }
   f_PredicatePath->Init();
   InitTrashCounter();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 0;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   ShowPredicatePathView(f_PredicatePath);
   delete TC;
   delete AP;
   delete m_TreeList;
}
//---------------------------------------------------------------------------

bool TfrmMain::CheckUsedPath()
{
   bool res;
   f_PredicatePath->Init();
   InitTrashCounter();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 1;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   res = TC->TryPath;
   delete TC;
   delete AP;
   delete m_TreeList;
   return res;
}

void TfrmMain::PredicateModel(TPredicatePathItem* AUsedPath)
{
   AnsiString OptZ = opt_sadacha->make_sadacha() + "\r\n" + opt_sadacha->make_ogrsovm();
   f_PredicatePath->Init();
   InitTrashCounter();
   InitTFEConvertor();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   TGraphTFEConvertor* GC = new TGraphTFEConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 2;
   TC->Process(f_PredicatePath->BasePath, AUsedPath);
   GC->Init(TC->Head, f_Zadacha->Tree);
   ShowPredicateModel(GC->PrStruct, GC->PrRab, GC->PrControlRab,
	 GC->PrControlFunc, GC->PrCheckCondition, OptZ, f_PredicateDopPrav);
   delete GC;
   delete TC;
   delete AP;
   delete m_TreeList;
   FreeTFEConvertor();
}

void __fastcall TfrmMain::acMetodSuperPosUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = (Grid->g_PainterList->Count > 0);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
/*
  //Внимание Для добавления последовательной РО нужно дважды вызывать Maker->AddTFSToCurrentLevel(1) те это две обычных РО;
  TParamAlternativeItem* PA;
  TMakerTFS* Maker = new TMakerTFS(MainList, Grid, &ShapeCopy,
	f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
  try
  {
    Maker->SetCurrentLevel(0);

    Maker->AddTFSToCurrentLevel(1);
    Maker->AddTFSToCurrentLevel(3);
    Maker->AddTFSToCurrentLevel(4);
    Maker->AddTFSToCurrentLevel(5);
    Maker->SetCurrentLevel(3);
    Maker->AddTFSToCurrentLevel(6);
    Maker->AddTFSToCurrentLevel(7);
    Maker->SetCurrentLevel(6);
    Maker->AddTFSToCurrentLevel(1);
    Maker->AddTFSToCurrentLevel(1);
    Maker->SetCurrentLevel(2);
    Maker->AddTFSToCurrentLevel(9);
    Maker->AddTFSToCurrentLevel(10);
    Maker->SetCurrentLevel(18);
    Maker->AddTFSToCurrentLevel(11);
    Maker->AddTFSToCurrentLevel(12);

    //добавление двух параметрических альтернатив для ТФЕ 5
    PA = Maker->CreateNewParamAlternative(5);
    PA->B = 12.67;
    PA->T = 100;
    PA->V = 9000;

    PA = Maker->CreateNewParamAlternative(5);
    PA->B = 22.67;
    PA->T = 120;
    PA->V = 9999;

    f_CurrIDBlock = Maker->CurrIDBlock;
    f_CurrIDShape = Maker->CurrIDShape;
    f_CurrIDLine = Maker->CurrIDLine;
  }
  catch(...){}
  delete Maker;
  SetNewPolygon();
  SetNewPosition();
  InvalidateRgn(pbMain->Parent->Handle, NULL, false);
*/

   f_PredicatePath->Init();
   InitTrashCounter();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 0;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   f_PredicatePath->GenerateOptSovmPath(f_OgrSovmArray);
   f_PredicatePath->UsedPath->Assign(f_PredicatePath->OptSovmPath);
   ShowMessage(f_PredicatePath->UsedPath->Text);
   delete TC;
   delete AP;
   delete m_TreeList;


}
//---------------------------------------------------------------------------
/* stas19 Это возможно был пример для гениатулиной*/

void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
  TBaseWorkShape* WS;
  TParamAlternativeItem* PA;
  TMakerTFS* Maker = new TMakerTFS(MainList, Grid, &ShapeCopy,
	f_CurrIDShape, f_CurrIDBlock, f_CurrIDLine);
  try
  {
	Maker->SetCurrentLevel(LevelController->ParentShapeID);

	int m_Last_id = MainList->TFEMaxID; //Это последний номер тфе

	WS = Maker->AddTFSToCurrentLevel(3, f_IdAlternative, f_NumAlternative); // добавление паралеьной РО
	//добавление параметрической альтернативы для первой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 1); // этот номер надо расчитывать
	PA->B = 10;
	PA->T = 100;
	PA->V = 1000;

	//добавление параметрической альтернативы для втрой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 30;
	PA->T = 300;
	PA->V = 3000;

	//добавление еще одной параметрической альтернативы для втрой ТФЕ из добавленной паралеьной РО
	PA = Maker->CreateNewParamAlternative(m_Last_id + 2);
	PA->B = 50;
	PA->T = 500;
	PA->V = 5000;


	//устанавливаем текущий уровень для первой ТФЕ из добавленной ТФС
	Maker->SetCurrentLevel(m_Last_id + 1);
	Maker->AddTFSToCurrentLevel(6, f_IdAlternative, f_NumAlternative); // добавление Функ-ый контроль


	Maker->SetCurrentLevel(2);
	Maker->AddTFSToCurrentLevel(4, f_IdAlternative, f_NumAlternative); // добавление паралеьной РО

	TAltSelectorItem* Item = f_AltSelector->CreateNewAlternateID(LevelController->ParentShapeID, 1);
	 if ( !MainList->CreateAlternate(WS, WS, Item->ID, Item->Num) )
			MainList->AddAlternate(Item->ID, Item->Num);
	f_AlternateController->AddAlternateItem(WS, WS, Item->ID, Item->Num,
	   0, 0);

	Maker->SetCurrentLevel(0);
	Grid->PrepareLevel();  // тока один раз рисуем новый уровень алтернатив
	Maker->AddTFSToCurrentLevel(4, Item->ID, Item->Num); // добавление паралеьной РО

	f_CurrIDBlock = Maker->CurrIDBlock;
	f_CurrIDShape = Maker->CurrIDShape;
	f_CurrIDLine = Maker->CurrIDLine;
  }
  catch(...){}
  delete Maker;

	MainList->ClearNodeTypeCreate();
	ListChange();
	AlternateListChange();
	Grid->PrepareLevelOnOffset();
	Grid->PreparePaint();
	f_AlternateController->CoordinateCorrect();
	SetNewPolygon();

//	 SetNewPosition();
	 InvalidateRgn(pbMain->Parent->Handle, NULL, false);



}
//*/

//---------------------------------------------------------------------------
void TfrmMain::PrepareOzenkTFEStill(TPredicatePathItem* APathItem)
{
   f_PredicatePath->Init();
   InitTrashCounter();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 0;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   delete TC;
   delete AP;
   delete m_TreeList;
}

void TfrmMain::OzenkTFEStill(TPredicatePathItem* APathItem, double &AOzenk0, double &AOzenk1)
{

   double m0, m1;
   AnsiString OptZ = opt_sadacha->make_sadacha() + "\r\n" + opt_sadacha->make_ogrsovm();

   f_PredicatePath->Init();
   f_Zadacha->Clear();
   InitTrashCounter();
   InitTFEConvertor();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   TGraphTFEConvertor* GC = new TGraphTFEConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 2;
   TC->Process(f_PredicatePath->BasePath, APathItem);

   GC->Init(TC->Head, f_Zadacha->Tree);
   f_Zadacha->Init(f_TypeParam, f_CheckNud, false, NULL, FullPredicateModel(GC->PrStruct,
	 GC->PrRab, GC->PrControlRab, GC->PrControlFunc, GC->PrCheckCondition, OptZ, *f_PredicateDopPrav));
   f_Zadacha->Ozenk_TFEStill(m0, m1);

   AOzenk0 = m0;
   AOzenk1 = m1;

   delete GC;
   delete TC;
   delete AP;
   delete m_TreeList;
   FreeTFEConvertor();
   PrepareOzenkTFEStill(APathItem);

}

void __fastcall TfrmMain::acAboutExecute(TObject *Sender)
{
  ShowAbout();
}

/* stas19 очередной пример для гениатулиной
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button3Click(TObject *Sender)
{

   f_PredicatePath->Init();
   f_Zadacha->Clear();
   InitTrashCounter();
   InitTFEConvertor();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   TGraphTFEConvertor* GC = new TGraphTFEConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 2;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   GC->Init(TC->Head, f_Zadacha->Tree);
   delete GC;
   delete TC;
   delete AP;
   delete m_TreeList;
   FreeTFEConvertor();
}
//---------------------------------------------------------------------------
*/

void __fastcall TfrmMain::acOptAnpExecute(TObject *Sender)
{
  f_OptAnp = !f_OptAnp;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acOptAnpUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Checked = f_OptAnp;
}

//---------------------------------------------------------------------------
bool TfrmMain::IsOptAnp()
{
  return f_OptAnp && (opt_sadacha->type_ogr > 3);
}

void TfrmMain::CreateZadachaOptAnp()
{
   f_PredicatePath->Init();
   InitTrashCounter();
   TTreeList* m_TreeList = new TTreeList;
   TAlternativeParser *AP = new TAlternativeParser;
   TPredicateTFSConvertor* TC =  new TPredicateTFSConvertor;
   m_TreeList->FillTreeFromList(MainList);
   AP->Parse(m_TreeList->MainTreeList);
   TC->CopyTree(AP->Head);
   TC->PathStyle = 0;
   TC->Process(f_PredicatePath->BasePath, f_PredicatePath->UsedPath);
   f_PredicatePath->GenerateOptSovmPath(f_OgrSovmArray);
   f_PredicatePath->UsedPath->Assign(f_PredicatePath->OptSovmPath);
   delete TC;
   delete AP;
   delete m_TreeList;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acToolBinRelExecute(TObject *Sender)
{
  ShowToolTFS("ЕЕЕЕ");
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::acToolGenerStruct(TObject *Sender)
{
  ShowToolGenerStruct(this);
  InvalidateRgn(pbMain->Parent->Handle, NULL, false);
}
//---------------------------------------------------------------------------

