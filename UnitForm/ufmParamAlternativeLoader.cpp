//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufmParamAlternativeLoader.h"
#include "uCommonGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfmParamAlternativeLoader *fmParamAlternativeLoader;
int ShowParamAlternativeLoader(int AType, double &AT_0, double &AT_1, double &AV_0, double &AV_1,
  double &AX00_0, double &AX00_1, double &AZ00_0, double &AZ00_1)
{
  int ret = 0;
  TfmParamAlternativeLoader *F = new TfmParamAlternativeLoader(Application);
  F->SetType(AType);
  bool res = F->ShowModal() == mrOk;
  if (res)
  {
	ret = atoi(AnsiString(F->edCount->Text).c_str());
	AT_0 = atof(AnsiString(F->edT_0->Text).c_str());
	AT_1 = atof(AnsiString(F->edT_1->Text).c_str());
	AV_0 = atof(AnsiString(F->edV_0->Text).c_str());
	AV_1 = atof(AnsiString(F->edV_1->Text).c_str());
	if (AType == 5)
	{
	  AX00_0 = atof(AnsiString(F->edB_0->Text).c_str());
	  AX00_1 = atof(AnsiString(F->edB_1->Text).c_str());
	}
	if (AType == 6)
	{
	  AX00_0 = atof(AnsiString(F->edP00_0->Text).c_str());
	  AX00_1 = atof(AnsiString(F->edP00_1->Text).c_str());
	  AZ00_0 = atof(AnsiString(F->edP11_0->Text).c_str());
	  AZ00_1 = atof(AnsiString(F->edP11_1->Text).c_str());
	}
	if (AType == 7)
	{
	  AX00_0 = atof(AnsiString(F->edK00_0->Text).c_str());
	  AX00_1 = atof(AnsiString(F->edK00_1->Text).c_str());
	  AZ00_0 = atof(AnsiString(F->edK11_0->Text).c_str());
	  AZ00_1 = atof(AnsiString(F->edK11_1->Text).c_str());
	}
  }
  F->Release();
  return ret;
}


//---------------------------------------------------------------------------
__fastcall TfmParamAlternativeLoader::TfmParamAlternativeLoader(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfmParamAlternativeLoader::SetType(int AType)
{
  gbControlRab->Visible = false;
  gbControlFunc->Visible = false;
  gbRab->Visible = false;
  if (AType == 5)
  {
    gbRab->Visible = true;
    gbRab->Align = alClient;
  }
  if (AType == 6)
  {
    gbControlRab->Visible = true;
    gbControlRab->Align = alClient;
  }
  if (AType == 7)
  {
    gbControlFunc->Visible = true;
	gbControlFunc->Align = alClient;
  }

}

int TfmParamAlternativeLoader::exit_proverka_simb(TEdit *Edit)
{
  if(read_float(AnsiString(Edit->Text).c_str()))
  {
	Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
    Edit->SetFocus();
    return 0;
  }
  return 1;
}

int TfmParamAlternativeLoader::exit_proverka_0_1(TEdit *Edit)
{
  float i;
  if(exit_proverka_simb(Edit)==0)
    return 0;

  i=atof(AnsiString(Edit->Text).c_str());

  if(i<0||i>1)
  {
    Application->MessageBox(_T("Значение должно быть в интервале [0,1]."), _T("Ошибка!"), MB_OK);
    Edit->SetFocus();
    return 0 ;
  }

  return 1;
}


void __fastcall TfmParamAlternativeLoader::edCountExit(TObject *Sender)
{
  exit_proverka_simb(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edK00_0Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edB_0Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edB_1Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edK00_1Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edK11_0Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edK11_1Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edP00_0Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edP00_1Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edP11_0Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edP11_1Exit(TObject *Sender)
{
  exit_proverka_0_1(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edT_0Exit(TObject *Sender)
{
  exit_proverka_simb(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edT_1Exit(TObject *Sender)
{
  exit_proverka_simb(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edV_0Exit(TObject *Sender)
{
  exit_proverka_simb(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::edV_1Exit(TObject *Sender)
{
  exit_proverka_simb(dynamic_cast<TEdit*>(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::acCancelExecute(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternativeLoader::acOkExecute(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

