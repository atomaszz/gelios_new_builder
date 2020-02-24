//---------------------------------------------------------------------------

#ifndef uFrmHelpH
#define uFrmHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TfrmHelp : public TForm
{
__published:	// IDE-managed Components
        TActionList *ActionList1;
        TAction *acClose;
        TAction *acBack;
        TAction *acForward;
        TAction *acFind;
        TAction *acPrint;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TImageList *IL;
        TImageList *ILHot;
        TToolBar *TBar;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TStatusBar *StatusBar1;
        TCppWebBrowser *WebBrowser;
        TAction *acHideBar;
        TMenuItem *N8;
        TMenuItem *N9;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall WebBrowserNavigateComplete2(TObject *Sender,
          LPDISPATCH pDisp, TVariant *URL);
        void __fastcall acFindExecute(TObject *Sender);
        void __fastcall acBackExecute(TObject *Sender);
        void __fastcall acForwardExecute(TObject *Sender);
        void __fastcall acPrintExecute(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall acHideBarExecute(TObject *Sender);
        void __fastcall acHideBarUpdate(TObject *Sender);
        void __fastcall acCloseExecute(TObject *Sender);
private:	// User declarations
        AnsiString f_Url;


public:		// User declarations
        void RefreshBrowser();
        void Quit();
        __fastcall TfrmHelp(TComponent* Owner);
        __property AnsiString URL = {read = f_Url, write = f_Url};

};

void ShowHelp(AnsiString AUrl, bool ARefresh, bool AHideBar);
void InitHelp();
void FreeHelp();
#endif
