//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufAbount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVersion::TVersion()
{
  FValid = false;
  FData = NULL;
  DWORD D;
  int iDataSize = GetFileVersionInfoSize(Application->ExeName.c_str(), &D);
  if (iDataSize > 0 )
  {
    FData = malloc(iDataSize);
    FValid = GetFileVersionInfo(Application->ExeName.c_str(), 0, iDataSize, FData);
  }
}

int TVersion::GetVersion(int AType)
{
  PVSFixedFileInfo FixedFileInfo;
  unsigned int Dummy;
  int res = -1;
  if ( FValid )
  {
    VerQueryValue( FData, _T("\\"), (LPVOID*)&FixedFileInfo, &Dummy );
    switch(AType)
    {
      case AB_MAJOR_VERSION:
        res = HIWORD( FixedFileInfo->dwFileVersionMS );
        break;
      case AB_MINOR_VERSION:
        res = LOWORD( FixedFileInfo->dwFileVersionMS );
        break;

      case AB_RELEASE:
        res = HIWORD( FixedFileInfo->dwFileVersionLS );
        break;

      case AB_BUILD:
        res = LOWORD( FixedFileInfo->dwFileVersionLS );
        break;
    }
  }
  return res;
}

TVersion::~TVersion()
{
  if (FData)
    free(FData);
}

void ShowAbout()
{
  TfAbount *fAbount = new TfAbount(Application);
  fAbount->ShowModal();
  fAbount->Release();
}

//---------------------------------------------------------------------------
__fastcall TfAbount::TfAbount(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TfAbount::FormCreate(TObject *Sender)
{
  Vers = new TVersion;
}
//---------------------------------------------------------------------------
void __fastcall TfAbount::FormDestroy(TObject *Sender)
{
  delete Vers;
}
//---------------------------------------------------------------------------
void __fastcall TfAbount::FormShow(TObject *Sender)
{
  AnsiString S = IntToStr(Vers->GetVersion(AB_BUILD));
  int len = S.Length();
  if (len == 1)
    S = "  " + S;
  if (len == 2)
    S = " " + S;
  lblBuild->Caption = S;
}
//---------------------------------------------------------------------------

void __fastcall TfAbount::acOkExecute(TObject *Sender)
{
  ModalResult = mrOk;      
}
//---------------------------------------------------------------------------

