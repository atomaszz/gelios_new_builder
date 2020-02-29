//---------------------------------------------------------------------------

#ifndef uMainFrmH
#define uMainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "uPaintgrids.h"
#include "uAltSelector.h"
#include "uGLSSectionBar.h"
#include "uLEControl.h"
#include "uListShape.h"
#include "uListLevel.h"
#include "uAlternate.h"
#include "uAltSelector.h"
#include "uAltStack.h"
#include "uMenuController.h"
#include "uGlsXml.h"
#include "UGlsXmlString.h"
#include "uLoaderTFS.h"
#include "uCommonGraph.h"
#include "uGlsRegistry.h"
#include "uAlternateView.h"
#include "uPieModule.h"
#include "uZadacha.h"
#include "uGlsActionList.h"
#include "uClipCopyTFS.h"
#include "uPredicatePath.h"
#include "uOgrSovmArray.h"



//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList;
	TAction *acInsertBlock;
	TAction *acExpand;
	TAction *acRollup;
	TAction *acAlternate;
	TAction *acSetupInterface;
	TAction *acAltAdd;
	TAction *acAltDelete;
	TAction *acAltRollup;
	TAction *acAltShow;
	TAction *acNew;
	TAction *acDeleteTFS;
	TAction *acDeleteTFSPointToPoint;
	TAction *acSaveList;
	TAction *acInsertTFSFromFile;
	TAction *acParamProp;
	TAction *acLoadTFSFromFile;
	TAction *acAltView;
	TAction *acExpandReplace;
	TAction *acExpandBack;
	TAction *acScrollDown;
	TAction *acScrollRight;
	TAction *acHelp;
	TAction *acGraphTFEConvert;
	TAction *acShowParamAlternate;
	TAction *acParamFuzzy;
	TAction *acOptZadacha;
	TAction *acFindDecision;
	TAction *acMetodOpt;
	TAction *acClipCopyTFS;
	TAction *acClipPaste;
	TAction *acCheckNud;
	TAction *acMetodSuperPos;
	TAction *acAbout;
	TAction *acOptAnp;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N10;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N33;
	TMenuItem *N5;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N6;
	TMenuItem *N27;
	TMenuItem *N11;
	TMenuItem *N13;
	TMenuItem *N18;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N21;
	TMenuItem *N17;
	TMenuItem *N37;
	TMenuItem *N30;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *N15;
	TMenuItem *N22;
	TMenuItem *N23;
	TMenuItem *N4;
	TMenuItem *N24;
	TMenuItem *N36;
	TMenuItem *N7;
	TMenuItem *N39;
	TMenuItem *N14;
	TMenuItem *N42;
	TMenuItem *N12;
	TMenuItem *N19;
	TMenuItem *N16;
	TMenuItem *N34;
	TMenuItem *N35;
	TMenuItem *N38;
	TMenuItem *MNCheckNudYes;
	TMenuItem *MNCheckNudNo;
	TMenuItem *N41;
	TMenuItem *N20;
	TMenuItem *N31;
	TMenuItem *N32;
	TMenuItem *N40;
	TImageList *ImgButtons;
	TPopupMenu *PopupMenu;
	TOpenDialog *OpenDLG;
	TSaveDialog *SaveDLG;
	TPopupMenu *PmAlternate;
	TApplicationEvents *ApplicationEvents;
	TImageList *ImageList1;
	TPanel *Panel1;
	TPanel *pnlButton;
	TStatusBar *SBar;
	TPanel *Panel3;
	TTabControl *tcMain;
	TShape *shpLeft;
	TShape *shpTop;
	TShape *shpButtom;
	TShape *shpRight;
	TPanel *pnlMain;
	TPaintBox *pbMain;
	TScrollBar *sbY;
	TScrollBar *sbX;
	TButton *Button2;
	TAction *acToolBinRel;
	TMenuItem *N43;
	TMenuItem *N44;
	TMenuItem *N45;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall pbMainPaint(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall acSetupInterfaceExecute(TObject *Sender);
	void __fastcall pnlMainResize(TObject *Sender);
	void __fastcall pbMainMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sbXChange(TObject *Sender);
	void __fastcall sbYChange(TObject *Sender);
	void __fastcall acInsertBlockExecute(TObject *Sender);
	void __fastcall acExpandExecute(TObject *Sender);
	void __fastcall acRollupExecute(TObject *Sender);
	void __fastcall acAlternateExecute(TObject *Sender);
	void __fastcall acNewExecute(TObject *Sender);
	void __fastcall acDeleteTFSExecute(TObject *Sender);
	void __fastcall acDeleteTFSPointToPointExecute(TObject *Sender);
	void __fastcall acSaveListExecute(TObject *Sender);
	void __fastcall acParamPropExecute(TObject *Sender);
	void __fastcall acExpandReplaceExecute(TObject *Sender);
	void __fastcall acExpandBackExecute(TObject *Sender);
	void __fastcall acHelpExecute(TObject *Sender);
	void __fastcall acShowParamAlternateExecute(TObject *Sender);
	void __fastcall acParamFuzzyExecute(TObject *Sender);
	void __fastcall acOptZadachaExecute(TObject *Sender);
	void __fastcall acFindDecisionExecute(TObject *Sender);
	void __fastcall acMetodOptExecute(TObject *Sender);
	void __fastcall acClipCopyTFSExecute(TObject *Sender);
	void __fastcall acClipPasteExecute(TObject *Sender);
	void __fastcall acCheckNudExecute(TObject *Sender);
	void __fastcall acMetodSuperPosExecute(TObject *Sender);
	void __fastcall acAboutExecute(TObject *Sender);
	void __fastcall acOptAnpExecute(TObject *Sender);
	void __fastcall acAltAddExecute(TObject *Sender);
	void __fastcall acAltAddUpdate(TObject *Sender);
	void __fastcall acAltRollupExecute(TObject *Sender);
	void __fastcall acAltRollupUpdate(TObject *Sender);
	void __fastcall acAltShowExecute(TObject *Sender);
	void __fastcall acAltViewExecute(TObject *Sender);
	void __fastcall acAltViewUpdate(TObject *Sender);
	void __fastcall acInsertBlockUpdate(TObject *Sender);
	void __fastcall acExpandUpdate(TObject *Sender);
	void __fastcall acRollupUpdate(TObject *Sender);
	void __fastcall acAlternateUpdate(TObject *Sender);
	void __fastcall acDeleteTFSUpdate(TObject *Sender);
	void __fastcall acDeleteTFSPointToPointUpdate(TObject *Sender);
	void __fastcall acInsertTFSFromFileExecute(TObject *Sender);
	void __fastcall acInsertTFSFromFileUpdate(TObject *Sender);
	void __fastcall acParamPropUpdate(TObject *Sender);
	void __fastcall acLoadTFSFromFileExecute(TObject *Sender);
	void __fastcall acExpandReplaceUpdate(TObject *Sender);
	void __fastcall acExpandBackUpdate(TObject *Sender);
	void __fastcall acScrollDownExecute(TObject *Sender);
	void __fastcall acScrollRightExecute(TObject *Sender);
	void __fastcall acGraphTFEConvertExecute(TObject *Sender);
	void __fastcall acGraphTFEConvertUpdate(TObject *Sender);
	void __fastcall acShowParamAlternateUpdate(TObject *Sender);
	void __fastcall acParamFuzzyUpdate(TObject *Sender);
	void __fastcall acFindDecisionUpdate(TObject *Sender);
	void __fastcall acClipCopyTFSUpdate(TObject *Sender);
	void __fastcall acClipPasteUpdate(TObject *Sender);
	void __fastcall acCheckNudUpdate(TObject *Sender);
	void __fastcall acMetodSuperPosUpdate(TObject *Sender);
	void __fastcall acOptAnpUpdate(TObject *Sender);
	void __fastcall ApplicationEventsIdle(TObject *Sender, bool &Done);
	bool __fastcall ApplicationEventsHelp(WORD Command, NativeInt Data, bool &CallHelp);
	void __fastcall pbMainMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pbMainMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall tcMainChange(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall acToolBinRelExecute(TObject *Sender);
	void __fastcall acToolGenerStruct(TObject *Sender);


public:	// User declarations
        int f_IdAlternative; //текущая альтернатива
        int f_NumAlternative; //текущая альтернатива номер
        int f_IdAlternativeParent; //предок текущей альтернативы
        int f_NumAlternativeParent; //нмер предка текущей альтернативы

        int f_CurrIDBlock; //текущий блок
        int f_CurrIDShape; //текущая фигура
        int f_CurrIDLine;//текущая линия
        int f_Operation;//текущая операция

        TPaintGrid* Grid;
        int f_StepPixel;
        bool f_PaintPixels;
		bool f_DrawFrameLine;
        TColor f_FonColor;
        TColor f_PixelColor;
        TColor f_FrameLineColor;
		int f_WSPenWidth;
		TGLSSectionBar *SectionBar;
		TListNode* MainList;
        TLevelController* LevelController;
        TAltSelector* f_AltSelector;
        TMenuController* f_MenuController;
        TMenuController* f_ContextMenuController;

        int X_Base, Y_Base;
        int X_Ofs, Y_Ofs;
		int __idls;

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
        TColor f_AltEnabledFlagColor;

		TColor f_VwColorAlt;
        TColor f_VwColorBadAlt;

        bool f_CanModifyPenWidth;

        TColor f_AltParamLineColor;
        TColor f_AltParamShapeColor;
        bool   f_AltParamShapeColorEnable;


        TAlternateController *f_AlternateController;
        TAltStackController *f_AltStackController;


        TGlsXmlDocument *xml_dom;
        TGlsXmlString *xml_str, *xml_att;
        TGlsXmlElement* xml_elm;
        TGlsXmlNode* xml_node;

		bool f_IsDebug;
        TColorSetup* f_ColorSetup;
		TGlsRegistry *f_RSettings;

        TAlternateView* f_AV;
        TDynamicArray *f_StackHistory;
        AnsiString f_HelpFile;
        bool f_HelpHideBar;

		int f_TypeParam;
		TZadacha *f_Zadacha;
		TGlsActionList *f_ActList;
		TClipCopyTFS *f_ClipCopyTFS;
		TPredicatePath *f_PredicatePath;
		bool f_CheckNud;
		AnsiString *f_PredicateDopPrav;
		TOgrSovmArray *f_OgrSovmArray;
		bool f_OptAnp;
		bool f_SectionBarAlternativeColor;

        void ApplySettings();
        void ApplyColorSetupSettings();
        void CreateSectionBar();
        int  GetTypShape();
        void AddWorkShape(int AType);
        void InsertWorkShape(int AType, TBaseWorkShape *WBefore);
        void __fastcall ListChange();
        void SetNewPolygon();
        void SetNewPosition();
        void SetShapeAtr();
        TBaseWorkShape* FindPriorWorkShape(TBaseWorkShape *W);
        TBaseWorkShape* FindNextWorkShape(TBaseWorkShape *W);
        void __fastcall SetOperation(int AValue);
        void LevelDown(int AParentShapeID);
        void LevelUp();
        void LevelUpReplace();
        void __fastcall ShapeCopy(TBaseShape *Shape, int Num_Shape);
        void __fastcall AlternateListChange();
        void CreateAlternative(TBaseWorkShape *WS, TBaseWorkShape *WE);
        void PrepareAlternative(int ANumAlt);
        void PrepareTabs(int ANumActive);
        void PrepareScroll();
        void LoadAlternative(int AIdAlt);
        void AddAlternativeNum();
        void HighlightAlternative(int AId);
        void MenuAlternateItemCreate(TAlternateItem *AItem, int AX, int AY);
        void __fastcall AltShow(TObject *Sender);
        void ClearAltWSList();
        void CheckEmptyAlternate(int AId);
        void DoDeleteWorkSahpeWithAlternate(TBaseWorkShape*WS, int AParentShapeID, TList *AList);
        void DeleteWorkSahpeWithAlternate(TBaseWorkShape* WS);
        void DeleteWorkSahpe(TBaseWorkShape* WS);
        void DeleteSelectedTFS();
        void DeleteTFSList(TBaseWorkShape* AFirst, TBaseWorkShape* ALast, bool ALastInclude);
        TBaseWorkShape* DoCreateWorkShape(int AType, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine);
        void DoLoadPrepareInc(TLoaderTFS* ALoaderTFS, int AParentID, int AParentNum);
        void DoLoadAlternate(TLoaderTFS* ALoaderTFS, int AParentID, int AParentNum);
        bool DoLoadAncestor(TLoaderTFS* ALoaderTFS, int AParentShapeID);
        void LoadFromFile(AnsiString AFileName, bool isNew);
        void LoadFromFileBin(AnsiString AFileName, bool isNew);
        void DoPrepareFirstAlternate(TLoaderTFS* ALoaderTFS, TPoint AStartPoint);

        AnsiString DoLoadMainListNew(TLoaderTFS* ALoaderTFS, int AParentShapeID);
        void DoLoadMainListPrepareLink(TLoaderTFS* ALoaderTFS);
        void DoLoadMainListPrepareLink(TLoaderTFS* ALoaderTFS, TBaseWorkShape *WBefore);
        void DoInsertTFSFromFile(AnsiString AFileName, TBaseWorkShape *WBefore);
        void DoInsertTFSFromFileBin(AnsiString AFileName, TBaseWorkShape *WBefore);

        void InsertTFSFromFile(TBaseWorkShape *WBefore);
        void SaveSettings();
        void RestoreSettings();
        TCompositeBaseWork* CreateCompositeWS(TBaseWorkShape* ATFS);
        void TopCorrect();
        void ShowPredicateModel(AnsiString AStruct, AnsiString ARab, AnsiString AControlRab,
          AnsiString AControlFunc, AnsiString ACheckCondition, AnsiString AOptZadacha, AnsiString *ADopPrav);
		void DoLoadParamAlt(TBaseWorkShape* AWS, TLoaderTFSMain* AMainItem, int AIdOffs);
        void BuildGlp(TBaseWorkShape* AWN, Graphics::TBitmap* Glp, TBaseShape *ASel);
		void InitPieModule();
        void InitActionList();
        void MenuContextCreate(int AX, int AY);
        void ApplyShortCutToActions();
        void SaveActions();
        void RestoreActions();
        void InsertTFSFromCanal(TBaseWorkShape *WBefore);
        void LoadFromCanal();


//        void __fastcall GlsBarLeftDown(TObject *Sender);
        void __fastcall GlsBarRigthDown(TObject *Sender);
        void __fastcall GlsBarApplyDown(TGLSSectionBar *Sender,
            TSectionBarButton *SectionButton, TMouseButton Button,  bool &AllowChange);
        void ClearWorkSpace();
        void PrepareOzenkTFEStill(TPredicatePathItem* APathItem);
        bool IsOptAnp();
        void CreateZadachaOptAnp();
        __property int Operation = { read = f_Operation, write = SetOperation};
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);

        inline TListNode* GetMainList(){return MainList;}
        bool CheckUsedPath();
        void PredicateModel(TPredicatePathItem* AUsedPath);
        void ApplySettingsForOutherGrid(TPaintGrid* AGrid);
        void OzenkTFEStill(TPredicatePathItem* APathItem, double &AOzenk0, double &AOzenk1);

        __property TColor HaveChildColor = {read = f_HaveChildColor};
        __property TColor LineColor = {read = f_LineColor};
        __property bool HelpHideBar = {read = f_HelpHideBar, write = f_HelpHideBar};

        MESSAGE void __fastcall M_gd_paint(TMessage& Msg);
        MESSAGE void __fastcall M_gd_paintoneprepare(TMessage& Msg);
        MESSAGE void __fastcall M_gd_gettypshape(TMessage& Msg);
        MESSAGE void __fastcall M_gd_addworkshape(TMessage& Msg);
        MESSAGE void __fastcall M_gd_setalternate(TMessage& Msg);
    //    MESSAGE void __fastcall M_gd_resetbutton(TMessage& Msg);

    //    MESSAGE void __fastcall M_gd_setadvancedalternate(TMessage& Msg);
    //    MESSAGE void __fastcall M_gd_setalternateparam(TMessage& Msg);
    //    MESSAGE void __fastcall M_gd_setnewpos(TMessage& Msg);
        MESSAGE void __fastcall M_gd_setnewpolygon(TMessage& Msg);
        MESSAGE void __fastcall M_le_mouseenter(TMessage& Msg);
        MESSAGE void __fastcall M_le_mouseleave(TMessage& Msg);
        MESSAGE void __fastcall M_gd_getnextworkshape(TMessage& Msg);
        MESSAGE void __fastcall M_gd_getpriorworkshape(TMessage& Msg);
        MESSAGE void __fastcall M_gd_insertworkshape(TMessage& Msg);
        MESSAGE void __fastcall M_gd_visiblearrowall(TMessage& Msg);
        MESSAGE void __fastcall M_gd_deletetfslist(TMessage& Msg);
        MESSAGE void __fastcall M_gd_insertworkshapefromfile(TMessage& Msg);
        MESSAGE void __fastcall M_gd_getmaintabcount(TMessage& Msg);
        MESSAGE void __fastcall M_gd_copytfslist(TMessage& Msg);
        MESSAGE void __fastcall M_gd_insertworkshapefromcanal(TMessage& Msg);


        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(WM_GD_PAINT, TMessage, M_gd_paint)
          MESSAGE_HANDLER(WM_GD_PAINTONEPREPARE, TMessage, M_gd_paintoneprepare)
          MESSAGE_HANDLER(WM_GD_GETTYPSHAPE, TMessage, M_gd_gettypshape)
          MESSAGE_HANDLER(WM_GD_ADDWORKSHAPE, TMessage, M_gd_addworkshape)
          MESSAGE_HANDLER(WM_GD_SETALTERNATE, TMessage, M_gd_setalternate)
          MESSAGE_HANDLER(WM_GD_VISIBLEARROWALL, TMessage, M_gd_visiblearrowall)
      //    MESSAGE_HANDLER(WM_GD_RESETBUTTON, TMessage, M_gd_resetbutton)
      //    MESSAGE_HANDLER(WM_GD_SETADVANCEDALTERNATE, TMessage, M_gd_setadvancedalternate)
      //    MESSAGE_HANDLER(WM_GD_SETALTERNATEPARAM, TMessage, M_gd_setalternateparam)
      //    MESSAGE_HANDLER(WM_GD_SETNEWPOS, TMessage, M_gd_setnewpos)
          MESSAGE_HANDLER(WM_GD_SETNEWPOLYGON, TMessage, M_gd_setnewpolygon)
          MESSAGE_HANDLER(WM_LE_MOUSEENTER, TMessage, M_le_mouseenter)
          MESSAGE_HANDLER(WM_LE_MOUSELEAVE, TMessage, M_le_mouseleave)
          MESSAGE_HANDLER(WM_GD_GETNEXTWORKSHAPE, TMessage, M_gd_getnextworkshape)
          MESSAGE_HANDLER(WM_GD_GETPRIORWORKSHAPE, TMessage, M_gd_getpriorworkshape)
          MESSAGE_HANDLER(WM_GD_INSERTWORKSHAPE, TMessage, M_gd_insertworkshape)
          MESSAGE_HANDLER(WM_GD_DELETETFSLIST, TMessage, M_gd_deletetfslist)
          MESSAGE_HANDLER(WM_GD_INSERTWORKSHAPEFROMFILE, TMessage, M_gd_insertworkshapefromfile)
          MESSAGE_HANDLER(WM_GD_GETMAINTABCOUNT, TMessage, M_gd_getmaintabcount)
          MESSAGE_HANDLER(WM_GD_COPYTFSLIST, TMessage, M_gd_copytfslist)
          MESSAGE_HANDLER(WM_GD_INSERTWORKSHAPEFROMCANAL, TMessage, M_gd_insertworkshapefromcanal)
		END_MESSAGE_MAP(TForm);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
