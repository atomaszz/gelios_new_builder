//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufmStartDecision.h"
#include "opim_f.h"
#include "uIMRIncl_all.h"
#include "ufmTrackShow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmStartDecision *fmStartDecision;
bool CreateStartDecision(TZadacha *AZadacha, int AType_char, int AType_metod)
{
   bool res;
   fmStartDecision = new TfmStartDecision(Application);
   fmStartDecision->type_char = AType_char;
   fmStartDecision->type_metod = AType_metod;
   fmStartDecision->set_sadacha_edit();
   fmStartDecision->edPercent->Text = float_2_string(opt_sadacha->Rate, 6, 1);
   fmStartDecision->Zadacha = AZadacha;
   res = fmStartDecision->ShowModal() == mrOk;
   return res;
}

void FreeStartDecision()
{
   fmStartDecision->Release();
}


//---------------------------------------------------------------------------
__fastcall TfmStartDecision::TfmStartDecision(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TfmStartDecision::set_sadacha_edit()
{
	AnsiString s;

	if (type_char == PROP)
	{	Edit6->Text = "вероятностные";	}
	if (type_char == FUZZY)
	{	Edit6->Text = "нечеткие";	}
        pnPribl->Visible = !(type_metod == TOHN);

	switch (opt_sadacha->type_sadacha)
	{
	case ZAD_1:
		Edit1->Text = "B(F) -> max";
		Edit5->Text = "    F <= Do";

		switch (opt_sadacha->type_ogr)
		{
		case 0:
			Edit2->Text = "";
			Edit3->Text = "";
			Edit4->Text = "";
			break;
		case 1:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd;
			Edit3->Text = "";
			break;
		case 2:
			s = "T(F) <= Td";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Td="+opt_sadacha->Td;
			break;
		case 3:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			s = "T(F) <= Td";
			Edit3->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd+"   Td="+opt_sadacha->Td;
			break;
		case 4:
			Edit2->Text = "";
			Edit3->Text = "";
			Edit4->Text = "";
			break;
		case 5:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd;
			Edit3->Text = "";
			break;
		case 6:
			s = "T(F) <= Td";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Td="+opt_sadacha->Td;
			break;
		case 7:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			s = "T(F) <= Td";
			Edit3->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd+"   Td="+opt_sadacha->Td;
			break;
		}
		break;
	case ZAD_2:
		Edit1->Text = "T(F) -> min";
		Edit5->Text = "    F <= Do";

		switch (opt_sadacha->type_ogr)
		{
		case 0:
			Edit2->Text = "";
			Edit3->Text = "";
			Edit4->Text = "";
			break;
		case 1:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd;
			Edit3->Text = "";
			break;
		case 2:
			s = "B(F) >= Bd";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd;
			break;
		case 3:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			s = "B(F) => Bd";
			Edit3->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd+"   Bd="+opt_sadacha->Bd;
			break;
		case 4:
			Edit2->Text = "";
			Edit3->Text = "";
			Edit4->Text = "";
			break;
		case 5:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd;
			Edit3->Text = "";
			break;
		case 6:
			s = "B(F) >= Bd";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd;
			break;
		case 7:
			s = "V(F) <= Vd";
			Edit2->Text = s;
			s = "B(F) => Bd";
			Edit3->Text = s;
			Edit4->Text = "Vd="+opt_sadacha->Vd+"   Bd="+opt_sadacha->Bd;
			break;
		}
		break;
	case ZAD_3:
		Edit1->Text = "V(F) -> min";
		Edit5->Text = "    F <= Do";

		switch (opt_sadacha->type_ogr)
		{
		case 0:
			Edit2->Text = "";
			Edit3->Text = "";
			break;
		case 1:
			s = "B(F) => Bd";
			Edit2->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd;
			Edit3->Text = "";
			break;
		case 2:
			s = "T(F) <= Td";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Td="+opt_sadacha->Td;
			break;
		case 3:
			s = "B(F) => Bd";
			Edit2->Text = s;
			s = "T(F) <= Td";
			Edit3->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd+"   Td="+opt_sadacha->Td;
			break;
		case 4:
			Edit2->Text = "";
			Edit3->Text = "";
			break;
		case 5:
			s = "B(F) => Bd";
			Edit2->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd;
			Edit3->Text = "";
			break;
		case 6:
			s = "T(F) <= Td";
			Edit2->Text = "";
			Edit3->Text = s;
			Edit4->Text = "Td="+opt_sadacha->Td;
			break;
		case 7:
			s = "B(F) => Bd";
			Edit2->Text = s;
			s = "T(F) <= Td";
			Edit3->Text = s;
			Edit4->Text = "Bd="+opt_sadacha->Bd+"   Td="+opt_sadacha->Td;
			break;
		}
		break;
	case ZAD_4:
		Edit1->Text = "c1*B(F) - c2*T(F) - c3*V(F) -> max";
		Edit5->Text = "                           F <= Do";
		Edit2->Text = "";
		Edit3->Text = "";
		Edit4->Text = "c1="+opt_sadacha->c1+"   c2="+opt_sadacha->c2+"   c3="+opt_sadacha->c3;
		break;
	case ZAD_5:
		Edit1->Text = "c1*(B(F)-B')/(B'-B,)+c2*(T(F)-T')/(T'-T,)+c3*(V(F)-V')/(V'-V,)->max";
		Edit5->Text = "                                                            F <= Do";
		Edit2->Text = "";
		Edit3->Text = "";
		Edit4->Text = "c1="+opt_sadacha->c1+"   c2="+opt_sadacha->c2+"   c3="+opt_sadacha->c3;
		break;
	case ZAD_6:
		Edit1->Text = "B^l (F) - T^k (F) - V^m (F) -> max";
		Edit5->Text = "                           F <= Do";
		Edit2->Text = "";
		Edit3->Text = "";
		Edit4->Text = "l="+opt_sadacha->c1+"   k="+opt_sadacha->c2+"   m="+opt_sadacha->c3;
		break;
	}
	if (opt_sadacha->type_ogr>3)
	{	Edit7->Text="S(F)";	}
	else
	{	Edit7->Text="";	}
}

void __fastcall TfmStartDecision::acStartExecute(TObject *Sender)
{
  if(read_float(AnsiString(edPercent->Text).c_str()))
  {
	Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
    edPercent->SetFocus();
    return;
  }
  opt_sadacha->Rate = StrToFloat(edPercent->Text);
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfmStartDecision::acCancelExecute(TObject *Sender)
{
  ModalResult = mrCancel;        
}
//---------------------------------------------------------------------------

void __fastcall TfmStartDecision::edPercentExit(TObject *Sender)
{
  if(read_float(AnsiString(edPercent->Text).c_str()))
  {
    Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
    edPercent->SetFocus();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmStartDecision::acTrackExecute(TObject *Sender)
{
   CreateTrackShow(Zadacha, Zadacha->Track());
}
//---------------------------------------------------------------------------


void __fastcall TfmStartDecision::acOzenkaExecute(TObject *Sender)
{
   Zadacha->Ozenk_TFE();     
}
//---------------------------------------------------------------------------

void __fastcall TfmStartDecision::acOzenkaUpdate(TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = opt_sadacha->type_ogr < 4;
}
//---------------------------------------------------------------------------

