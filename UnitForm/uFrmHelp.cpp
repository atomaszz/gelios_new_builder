//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFrmHelp.h"
#include "uDocHostUiHandler.h"
#include "uMessengers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TDocHostUiHandler *HelpHandler;
TfrmHelp *fmHelp;

void InitHelp()
{
  fmHelp = NULL;
}

void FreeHelp()
{
  if (fmHelp)
  {
    fmHelp->Quit();
    fmHelp->Release();
    fmHelp = NULL;
  }
}


void ShowHelp(AnsiString AUrl, bool ARefresh, bool AHideBar)
{
   bool mRefresh = ARefresh || (!fmHelp);
   if (!fmHelp)
   {
      fmHelp =  new TfrmHelp(Application);
      fmHelp->URL = AUrl;
      fmHelp->TBar->Visible = !AHideBar;
   }
   if (mRefresh)
      fmHelp->RefreshBrowser();
   fmHelp->Show();
   ShowWindow(fmHelp->Handle, SW_RESTORE);
}
//---------------------------------------------------------------------------
__fastcall TfrmHelp::TfrmHelp(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::FormCreate(TObject *Sender)
{
   HelpHandler = new  TDocHostUiHandler;
   f_Url = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::WebBrowserNavigateComplete2(TObject *Sender,
      LPDISPATCH pDisp, TVariant *URL)
{
   ICustomDoc *Doc;
   HRESULT hr =  WebBrowser->Document->QueryInterface(IID_ICustomDoc,(void**)&Doc);
   if( SUCCEEDED(hr))
     Doc->SetUIHandler(HelpHandler);
   Doc->Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::acFindExecute(TObject *Sender)
{
   GUID FD = {0xED016940, 0xBD5B, 0x11cf, {0xBA, 0x4E, 0x00, 0xC0, 0x4F, 0xD7, 0x08, 0x16 } };
   VARIANT vaIn, vaOut;
   IOleCommandTarget* I;
   HRESULT hr =  WebBrowser->Document->QueryInterface(IID_IOleCommandTarget,(void**)&I);
   if( SUCCEEDED(hr))
      I->Exec( &FD, 1, 0, &vaIn, &vaOut);
   I->Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::acBackExecute(TObject *Sender)
{
  VARIANT V;
  IOmHistory *IH;
  IHTMLWindow2* IWin;
  IHTMLDocument2* Doc;
  HRESULT hr =  WebBrowser->Document->QueryInterface(IID_IHTMLDocument2,(void**)&Doc);
  if (SUCCEEDED(hr))
  {
     Doc->get_parentWindow(&IWin);
     IWin->get_history(&IH);
     IH->back(&V);
  }
  Doc->Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::acForwardExecute(TObject *Sender)
{
  VARIANT V;
  IOmHistory *IH;
  IHTMLWindow2* IWin;
  IHTMLDocument2* Doc;
  HRESULT hr =  WebBrowser->Document->QueryInterface(IID_IHTMLDocument2,(void**)&Doc);
  if (SUCCEEDED(hr))
  {
     Doc->get_parentWindow(&IWin);
     IWin->get_history(&IH);
     IH->forward(&V);
  }
  Doc->Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::acPrintExecute(TObject *Sender)
{
  TVariant vaIn, vaOut;
  int mr = Application->MessageBox(_T("Вывести документ на принтер?"), _T("Справка"),
    MB_ICONQUESTION | MB_YESNO );
  if (mr == ID_YES)
	WebBrowser->ControlInterface->ExecWB(OLECMDID_PRINT,
      OLECMDEXECOPT_DONTPROMPTUSER, &vaIn, &vaOut);
}
//---------------------------------------------------------------------------

void TfrmHelp::RefreshBrowser()
{
  wchar_t *str = new wchar_t[URL.WideCharBufSize()];
  wchar_t* UnicodeString = URL.WideChar(str, URL.WideCharBufSize());
  WebBrowser->Navigate(UnicodeString);
  delete []str;
}

void TfrmHelp::Quit()
{
  delete  HelpHandler;
}


void __fastcall TfrmHelp::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = caFree;
  GMess->SendMess(2, int(!fmHelp->TBar->Visible), 0);
  Quit();
  fmHelp = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmHelp::acHideBarExecute(TObject *Sender)
{
   TBar->Visible = !TBar->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TfrmHelp::acHideBarUpdate(TObject *Sender)
{
   acHideBar->Checked = !TBar->Visible;
}
//---------------------------------------------------------------------------


void __fastcall TfrmHelp::acCloseExecute(TObject *Sender)
{
   GMess->SendMess(2, int(!fmHelp->TBar->Visible), 0);
   FreeHelp();        
}
//---------------------------------------------------------------------------


