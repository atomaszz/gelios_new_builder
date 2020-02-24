//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufrmPredicateView.h"
#include "ufmPredicateFull.h"
#include "opim_f.H"
#include "UMainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPredicateView *frmPredicateView;

AnsiString FullPredicateModel(AnsiString AStruct, AnsiString ARab,
  AnsiString AControlRab, AnsiString AControlFunc, AnsiString ACheckCondition,
  AnsiString AOptZadacha, AnsiString ADopPrav )
{
   frmMain->GetMainList()->GetAllWorkShape(opt_sadacha->MassWork);
   opt_sadacha->InitData();
   AnsiString S = "%Предикатная модель Альтернативного Графа (структур на основе ТФЕ)\r\n";
   S = S + "%Дата создания: "+DateToStr(Date()) + "\r\n";
   S = S + "%----------------------------------------------------\r\n";
   S = S + "%Задача оптимизации:\r\n";
   if (AOptZadacha.Length() > 0 )
      S = S + AOptZadacha + "\r\n";
//   S = S + opt_sadacha->make_sadacha() + "\r\n";
//   S = S + opt_sadacha->make_ogrsovm();
   S = S + "%Структура ТФЕ:\r\n";
   if (AStruct.Length() > 0)
   {
     S = S + AStruct;
     S = S + "\r\n";
   }
   S = S + "%Параметры подблоков ТФЕ:\r\n";
   if (ARab.Length() > 0)
   {
     S = S + ARab;
     S = S + "\r\n";
   }
   if (AControlRab.Length() > 0)
   {
     S = S + AControlRab;
     S = S + "\r\n";
   }
   if (AControlFunc.Length() > 0)
   {
     S = S + AControlFunc;
     S = S + "\r\n";
   }
   if (ACheckCondition.Length() > 0)
   {
     S = S + ACheckCondition;
     S = S + "\r\n";
   }
   S = S + "%Дополнительные (вспомогательные) правила:\r\n";
   if (ADopPrav.Length() > 0)
   {
     S = S + ADopPrav;
     S = S + "\r\n";
   }
   return S;
}

//---------------------------------------------------------------------------
__fastcall TfrmPredicateView::TfrmPredicateView(TComponent* Owner)
        : TForm(Owner)
{
  f_Close = false;
}

AnsiString TfrmPredicateView::FullModel()
{
   return FullPredicateModel(REStruct->Lines->Text,
     RERab->Lines->Text,
     REControlRab->Lines->Text,
     REControlFunc->Lines->Text,
     RECheckCondition->Lines->Text,
     REOptZadacha->Lines->Text,
     REDopPrav->Lines->Text);

/*
   AnsiString S = "%Предикатная модель Альтернативного Графа (структур на основе ТФЕ)\r\n";
   S = S + "%Дата создания: "+DateToStr(Date()) + "\r\n";
   S = S + "%----------------------------------------------------\r\n";
   S = S + "%Задача оптимизации:\r\n";
   S = S + opt_sadacha->make_sadacha() + "\r\n";
   S = S + "%Структура ТФЕ:\r\n";
   if (REStruct->Lines->Text.Length() > 0)
   {
     S = S + REStruct->Lines->Text;
     S = S + "\r\n";
   }
   S = S + "%Параметры подблоков ТФЕ:\r\n";
   if (RERab->Lines->Text.Length() > 0)
   {
     S = S + RERab->Lines->Text;
     S = S + "\r\n";
   }
   if (REControlRab->Lines->Text.Length() > 0)
   {
     S = S + REControlRab->Lines->Text;
     S = S + "\r\n";
   }
   if (REControlFunc->Lines->Text.Length() > 0)
   {
     S = S + REControlFunc->Lines->Text;
     S = S + "\r\n";
   }
   if (RECheckCondition->Lines->Text.Length() > 0)
   {
     S = S + RECheckCondition->Lines->Text;
     S = S + "\r\n";
   }
   S = S + "%Дополнительные (вспомогательные) правила:\r\n";
   if (REDopPrav->Lines->Text.Length() > 0)
   {
     S = S + REDopPrav->Lines->Text;
     S = S + "\r\n";
   }
   return S;
*/   
}

//---------------------------------------------------------------------------
void __fastcall TfrmPredicateView::acSaveExecute(TObject *Sender)
{
   TFileStream *Fs;
   AnsiString Model = FullModel();
   if (SDG->Execute())
   {
     Fs = new TFileStream(SDG->FileName, fmCreate);
     Fs->WriteBuffer(Model.c_str(), Model.Length());
     delete Fs;
   }
   else
     f_Close = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPredicateView::acExitExecute(TObject *Sender)
{
  ModalResult = mrOk;

}
//---------------------------------------------------------------------------
void __fastcall TfrmPredicateView::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == VK_ESCAPE)
   {
      if ( f_Close )
        f_Close = false;
      else
        acExitExecute(NULL);
      Key = 0;
   }

}
//---------------------------------------------------------------------------

void __fastcall TfrmPredicateView::acLoadDopPravUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = PC->ActivePage == tsDopPrav;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPredicateView::acLoadDopPravExecute(TObject *Sender)
{
  if (OD->Execute())
    REDopPrav->Lines->LoadFromFile(OD->FileName);
  else
    f_Close = true;
}
//---------------------------------------------------------------------------



void __fastcall TfrmPredicateView::acAllExecute(TObject *Sender)
{
  Application->CreateForm(__classid(TfmPredicateFull), &fmPredicateFull);
  fmPredicateFull->REModel->Text = FullModel();
  fmPredicateFull->ShowModal();
  fmPredicateFull->Release();
  f_Close = true;

}
//---------------------------------------------------------------------------

