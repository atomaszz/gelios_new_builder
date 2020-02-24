//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufmPredicateFull.h"
#include "uPieModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmPredicateFull *fmPredicateFull;
//---------------------------------------------------------------------------
__fastcall TfmPredicateFull::TfmPredicateFull(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmPredicateFull::acRunExecute(TObject *Sender)
{
   AnsiString Zel = Trim(edZel->Text);
   if (Zel.Length() > 0 )
   {
     REModel->Lines->SaveToFile("temp_1.dec");
     int res = gPieModule->Run1("tell(\"temp.pra\"),reconsult(\"temp_1.dec\")," + Zel);
     if (res > 0 )
     {
       STResult->Font->Color = clGreen;
       STResult->Text = "Цель достижима";
     }
     else
     {
       STResult->Font->Color = clRed;
       STResult->Text = "Цель не достижима";
     }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfmPredicateFull::acRunUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = gPieModule->CheckModule();
}
//---------------------------------------------------------------------------

void __fastcall TfmPredicateFull::acExitExecute(TObject *Sender)
{
  ModalResult = mrCancel;         
}
//---------------------------------------------------------------------------

