//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "ufmPredicatePathConstructorOgr.h"
#include "opim_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfmPredicatePathConstructorOgr *fmPredicatePathConstructorOgr;
bool PredicatePathConstructorOgrShow(int &APercent, int &ACount, bool &AOzenk,
  bool &AExclude, int &AMaxOptCnt)
{
  TfmPredicatePathConstructorOgr *F = new TfmPredicatePathConstructorOgr(Application);
  F->edPercent->Text = IntToStr(APercent);
  F->edCount->Text = IntToStr(ACount);
  F->cbOzenk->Checked = AOzenk;
  F->cbExclude->Checked = AExclude;
  F->edMaxOpt->Text = IntToStr(AMaxOptCnt);
  if (opt_sadacha->type_ogr >= 4 )
  {
    F->cbOzenk->Checked = false;
    F->gbOzenk->Enabled = false;
  }
  F->cbOzenkClick(NULL);

  bool res = F->ShowModal() == mrOk;
  if (res)
  {
    int a_p = StrToIntDef(F->edPercent->Text, 0);
    if (a_p < 0)
      a_p = 0;
    if (a_p > 100)
      a_p = 100;
    APercent = a_p;

    int a_c = StrToIntDef(F->edCount->Text, 1000);
    if (a_c < 0)
      a_c = 1;
    ACount = a_c;

    AOzenk = F->cbOzenk->Checked;
    AExclude = F->cbExclude->Checked;
    int a_m = StrToIntDef(F->edMaxOpt->Text, 1);
    if(a_m > 0)
      AMaxOptCnt = a_m;
  }
  F->Release();
  return res;
}

//---------------------------------------------------------------------------
__fastcall TfmPredicatePathConstructorOgr::TfmPredicatePathConstructorOgr(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmPredicatePathConstructorOgr::acOkExecute(
      TObject *Sender)
{
  ModalResult = mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TfmPredicatePathConstructorOgr::acCancelExecute(
      TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TfmPredicatePathConstructorOgr::cbOzenkClick(
      TObject *Sender)
{
  lblMaxOpt->Enabled = cbOzenk->Checked;
  edMaxOpt->Enabled = cbOzenk->Checked;
  cbExclude->Enabled = cbOzenk->Checked;
}
//---------------------------------------------------------------------------
