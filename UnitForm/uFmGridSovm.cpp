//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFmGridSovm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFmGridSovm *FmGridSovm;
//---------------------------------------------------------------------------
__fastcall TFmGridSovm::TFmGridSovm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFmGridSovm::acGridSovmAddExecute(TObject *Sender)
{
  sgSovm->RowCount = sgSovm->RowCount+1;
  for(int i = 0; i <= sgSovm->ColCount - 1; i++)
    sgSovm->Cells[i][sgSovm->RowCount-1] = "";

}
//---------------------------------------------------------------------------

void __fastcall TFmGridSovm::acGridSovmDelExecute(TObject *Sender)
{
  if(sgSovm->RowCount != 2)
  {
    for(int i = sgSovm->Row; i < sgSovm->RowCount-1; i++)
      for(int j = 0; j < sgSovm->ColCount; j++)
        sgSovm->Cells[j][i] = sgSovm->Cells[j][i+1];
      sgSovm->RowCount = sgSovm->RowCount-1;
  }
  else
    for(int j=0; j< sgSovm->ColCount; j++)
      sgSovm->Cells[j][1] = "";
}
//---------------------------------------------------------------------------


void __fastcall TFmGridSovm::acSaveSovmExecute(TObject *Sender)
{
  AnsiString s;
  int i, j, f = 0;
  for (j = 0; j < sgSovm->ColCount; j++)
	for (i = 1; i < sgSovm->RowCount; i++)
	{
	  s = sgSovm->Cells[j][i];
	  if( SameText(s, "") ) continue;
	  if( atoi(s.c_str())!=0)
		  sgSovm->Cells[j][i] = atoi(s.c_str());
      else f=1;
    }

 if(f)
 {
   Application->MessageBox(_T("Значения должны быть целыми."), _T("Ошибка!"), MB_OK | MB_ICONWARNING);
   sgSovm->SetFocus();
   return;
 }
 ModalResult = mrOk;
}
//---------------------------------------------------------------------------



void __fastcall TFmGridSovm::acCancelExecute(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

