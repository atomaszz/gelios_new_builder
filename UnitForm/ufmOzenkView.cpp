//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufmOzenkView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfmOzenkView *fmOzenkView;
//---------------------------------------------------------------------------
void ShowOzenk(AnsiString APower, AnsiString AWork)
{
  TfmOzenkView *F = new TfmOzenkView(Application);
  F->edPower->Text = APower;
  F->edWork->Text = AWork;
  F->ShowModal();
  F->Release();
}

__fastcall TfmOzenkView::TfmOzenkView(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
