//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufrmDialogExit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDialogExit *frmDialogExit;
//---------------------------------------------------------------------------
__fastcall TfrmDialogExit::TfrmDialogExit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int DialogExitExecute()
{
  Application->CreateForm(__classid(TfrmDialogExit), &frmDialogExit);
  frmDialogExit->MResult = 0;
  frmDialogExit->ShowModal();
  int res = frmDialogExit->MResult;
  frmDialogExit->Release();
  return res;
}
void __fastcall TfrmDialogExit::BtSaveClick(TObject *Sender)
{
   MResult = 1;
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogExit::BtContinueClick(TObject *Sender)
{
   MResult = 0;
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogExit::BtExitClick(TObject *Sender)
{
   MResult = 2;
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogExit::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == VK_ESCAPE	)
     BtContinueClick(NULL);
}
//---------------------------------------------------------------------------
