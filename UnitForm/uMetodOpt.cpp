//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uMetodOpt.h"
#include "uIMRIncl_all.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFmMetodOpt *FmMetodOpt;
//---------------------------------------------------------------------------
__fastcall TFmMetodOpt::TFmMetodOpt(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int TFmMetodOpt::get_type_metod()
{
   int res = TOHN;
   if (cbxMetod->ItemIndex == 1)
   {
      res = PRIBLJ1;
      if (rgMetod->ItemIndex == 1)
        res = PRIBLJ2;
   }
   return res;
}

void TFmMetodOpt::set_type_metod(int typ)
{
   if (typ == TOHN)
     cbxMetod->ItemIndex = 0;
   else
     cbxMetod->ItemIndex = 1;
   if (typ == PRIBLJ1)
     rgMetod->ItemIndex = 0;
   if (typ == PRIBLJ2)
     rgMetod->ItemIndex = 1;
   cbxMetodClick(NULL);
}


void __fastcall TFmMetodOpt::cbxMetodClick(TObject *Sender)
{
   rgMetod->Enabled = cbxMetod->ItemIndex;
   lblPribl->Enabled = cbxMetod->ItemIndex;
   edPercent->Enabled = cbxMetod->ItemIndex;
}
//---------------------------------------------------------------------------

bool ShowMetodOpt(int AType, double ARate, int &OutType, double &OutRate)
{
  FmMetodOpt = new TFmMetodOpt(Application);
  FmMetodOpt->set_type_metod(AType);
  FmMetodOpt->edPercent->Text = float_2_string(ARate, 6, 1);
  bool res = (FmMetodOpt->ShowModal() == mrOk);
  OutType = FmMetodOpt->get_type_metod();
  OutRate = StrToFloat(FmMetodOpt->edPercent->Text);
  FmMetodOpt->Release();
  return res;
}


void __fastcall TFmMetodOpt::btOkClick(TObject *Sender)
{
  if(read_float(AnsiString(edPercent->Text).c_str()))
  {
    Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
    edPercent->SetFocus();
    return;
  }
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFmMetodOpt::btCancelClick(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

