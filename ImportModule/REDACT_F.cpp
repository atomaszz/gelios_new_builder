//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop
#include "redact_f.h"
#include "uIMRIncl_all.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tredact_char *redact_char;
void ShowParamAlternativeEditor(TBaseShape* ATFE, TParamAlternativeItem* AItem,  int AType_Char, bool ACan_list)
{
   Application->CreateForm(__classid(Tredact_char), &redact_char);
   redact_char->TFE = ATFE;
   redact_char->PAItem = AItem;
   redact_char->Type_Char = AType_Char;
   redact_char->Can_list = ACan_list;
   redact_char->ShowModal();
   redact_char->Release();
}

//---------------------------------------------------------------------------
__fastcall Tredact_char::Tredact_char(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tredact_char::Button7Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
//принять редакцию
void __fastcall Tredact_char::Button6Click(TObject *Sender)
{
	if(check_table()==0)
    {
      return;
    }

	if(strlen(AnsiString(Edit13->Text).c_str())!=0)
      PAItem->NAME = Edit13->Text;
    else
      PAItem->NAME = "(нет названия)";

	if(strlen(AnsiString(Edit90->Text).c_str())!=0)
      PAItem->PREDICAT = Edit90->Text;
    else
      PAItem->PREDICAT = "";

    PAItem->ELEMENT="(нет элемента)";

    PAItem->FUNCTION2 = "(нет функции)";

    if(Type_Char==FUZZY)
      if(compare_char_fuzzy()==0)
    {
	  Application->MessageBox(_T("Значение верхней границы не может быть меньше значения нижней границы."), _T("Ошибка!"), MB_OK);
	  return;
    }

	if(Type_Char==PROP)
      save_char_prop();
    if(Type_Char==FUZZY)
      save_char_fuzzy();

  Close();
}


//---------------------------------------------------------------------------
void Tredact_char::save_char_prop()
{
  int m_type  = TFE->TypeShape;
  if(m_type == 5)
  {
	PAItem->B = atof(AnsiString(Edit2->Text).c_str());
	PAItem->T = atof(AnsiString(Edit3->Text).c_str());
	PAItem->V = atof(AnsiString(Edit4->Text).c_str());
  }
  if(m_type == 6)
  {
	PAItem->P_11 = atof(AnsiString(Edit5->Text).c_str());
	PAItem->P_00 = atof(AnsiString(Edit6->Text).c_str());
	PAItem->T_D = atof(AnsiString(Edit7->Text).c_str());
	PAItem->V_D = atof(AnsiString(Edit8->Text).c_str());
	PAItem->P_DIAGN_EL = atof(AnsiString(Edit91->Text).c_str());
  }
  if(m_type == 7)
  {
	PAItem->K_11 = atof(AnsiString(Edit9->Text).c_str());
	PAItem->K_00 = atof(AnsiString(Edit10->Text).c_str());
	PAItem->T_F = atof(AnsiString(Edit11->Text).c_str());
	PAItem->V_F = atof(AnsiString(Edit12->Text).c_str());
  }
  if(m_type == 8)
  {
	PAItem->PREDICAT = Edit14->Text;
  }
}

//---------------------------------------------------------------------------
//проверка того, чтобы нижняя граница была меньше по значению чем верхняя
int  Tredact_char::compare_char_fuzzy()
{
  int m_type  = TFE->TypeShape;
  if(m_type == 5)
  {
	 if(atof(AnsiString(Edit15->Text).c_str()) < atof(AnsiString(Edit16->Text).c_str())) {Edit15->SetFocus();return 0;}
	 if(atof(AnsiString(Edit17->Text).c_str()) < atof(AnsiString(Edit18->Text).c_str())) {Edit17->SetFocus();return 0;}
	 if(atof(AnsiString(Edit19->Text).c_str()) < atof(AnsiString(Edit20->Text).c_str())) {Edit19->SetFocus();return 0;}


	 if(atof(AnsiString(Edit21->Text).c_str()) < atof(AnsiString(Edit22->Text).c_str())) {Edit21->SetFocus();return 0;}
	 if(atof(AnsiString(Edit23->Text).c_str()) < atof(AnsiString(Edit24->Text).c_str())) {Edit23->SetFocus();return 0;}
	 if(atof(AnsiString(Edit25->Text).c_str()) < atof(AnsiString(Edit26->Text).c_str())) {Edit25->SetFocus();return 0;}

	 if(atof(AnsiString(Edit27->Text).c_str()) < atof(AnsiString(Edit28->Text).c_str())) {Edit27->SetFocus();return 0;}
	 if(atof(AnsiString(Edit29->Text).c_str()) < atof(AnsiString(Edit30->Text).c_str())) {Edit29->SetFocus();return 0;}
	 if(atof(AnsiString(Edit31->Text).c_str()) < atof(AnsiString(Edit32->Text).c_str())) {Edit31->SetFocus();return 0;}
  }
  if(m_type == 6)
  {
	 if(atof(AnsiString(Edit36->Text).c_str()) < atof(AnsiString(Edit37->Text).c_str())) {Edit36->SetFocus();return 0;}
	 if(atof(AnsiString(Edit38->Text).c_str()) < atof(AnsiString(Edit39->Text).c_str())) {Edit38->SetFocus();return 0;}
	 if(atof(AnsiString(Edit40->Text).c_str()) < atof(AnsiString(Edit41->Text).c_str())) {Edit40->SetFocus();return 0;}

	 if(atof(AnsiString(Edit42->Text).c_str()) < atof(AnsiString(Edit43->Text).c_str())) {Edit42->SetFocus();return 0;}
	 if(atof(AnsiString(Edit44->Text).c_str()) < atof(AnsiString(Edit45->Text).c_str())) {Edit44->SetFocus();return 0;}
	 if(atof(AnsiString(Edit46->Text).c_str()) < atof(AnsiString(Edit47->Text).c_str())) {Edit46->SetFocus();return 0;}

	 if(atof(AnsiString(Edit48->Text).c_str()) < atof(AnsiString(Edit49->Text).c_str())) {Edit48->SetFocus();return 0;}
	 if(atof(AnsiString(Edit50->Text).c_str()) < atof(AnsiString(Edit51->Text).c_str())) {Edit50->SetFocus();return 0;}
	 if(atof(AnsiString(Edit52->Text).c_str()) < atof(AnsiString(Edit53->Text).c_str())) {Edit52->SetFocus();return 0;}

	 if(atof(AnsiString(Edit54->Text).c_str()) < atof(AnsiString(Edit55->Text).c_str())) {Edit54->SetFocus();return 0;}
	 if(atof(AnsiString(Edit56->Text).c_str()) < atof(AnsiString(Edit57->Text).c_str())) {Edit56->SetFocus();return 0;}
	 if(atof(AnsiString(Edit58->Text).c_str()) < atof(AnsiString(Edit59->Text).c_str())) {Edit58->SetFocus();return 0;}

	 if(atof(AnsiString(Edit61->Text).c_str()) < atof(AnsiString(Edit60->Text).c_str())) {Edit61->SetFocus();return 0;}
	 if(atof(AnsiString(Edit89->Text).c_str()) < atof(AnsiString(Edit88->Text).c_str())) {Edit89->SetFocus();return 0;}
	 if(atof(AnsiString(Edit87->Text).c_str()) < atof(AnsiString(Edit62->Text).c_str())) {Edit87->SetFocus();return 0;}
 }
 if(m_type == 7)
 {
	 if(atof(AnsiString(Edit63->Text).c_str()) < atof(AnsiString(Edit64->Text).c_str())) {Edit63->SetFocus();return 0;}
	 if(atof(AnsiString(Edit65->Text).c_str()) < atof(AnsiString(Edit66->Text).c_str())) {Edit65->SetFocus();return 0;}
	 if(atof(AnsiString(Edit67->Text).c_str()) < atof(AnsiString(Edit68->Text).c_str())) {Edit67->SetFocus();return 0;}

	 if(atof(AnsiString(Edit69->Text).c_str()) < atof(AnsiString(Edit70->Text).c_str())) {Edit69->SetFocus();return 0;}
	 if(atof(AnsiString(Edit71->Text).c_str()) < atof(AnsiString(Edit72->Text).c_str())) {Edit71->SetFocus();return 0;}
	 if(atof(AnsiString(Edit73->Text).c_str()) < atof(AnsiString(Edit74->Text).c_str())) {Edit73->SetFocus();return 0;}

	 if(atof(AnsiString(Edit75->Text).c_str()) < atof(AnsiString(Edit76->Text).c_str())) {Edit75->SetFocus();return 0;}
	 if(atof(AnsiString(Edit77->Text).c_str()) < atof(AnsiString(Edit78->Text).c_str())) {Edit77->SetFocus();return 0;}
	 if(atof(AnsiString(Edit79->Text).c_str()) < atof(AnsiString(Edit80->Text).c_str())) {Edit79->SetFocus();return 0;}

	 if(atof(AnsiString(Edit81->Text).c_str()) < atof(AnsiString(Edit82->Text).c_str())) {Edit81->SetFocus();return 0;}
	 if(atof(AnsiString(Edit83->Text).c_str()) < atof(AnsiString(Edit84->Text).c_str())) {Edit83->SetFocus();return 0;}
	 if(atof(AnsiString(Edit85->Text).c_str()) < atof(AnsiString(Edit86->Text).c_str())) {Edit85->SetFocus();return 0;}
 }
 return 1;
}
//---------------------------------------------------------------------------
void Tredact_char::save_char_fuzzy()
{
  int m_type  = TFE->TypeShape;
  if(m_type == 5)
  {
	PAItem->B_F3B = atof(AnsiString(Edit15->Text).c_str());
	PAItem->B_F3N = atof(AnsiString(Edit16->Text).c_str());
	PAItem->B_F1B = atof(AnsiString(Edit17->Text).c_str());
	PAItem->B_F1N = atof(AnsiString(Edit18->Text).c_str());
	PAItem->B_F2B = atof(AnsiString(Edit19->Text).c_str());
	PAItem->B_F2N = atof(AnsiString(Edit20->Text).c_str());
	PAItem->A2_B_F = atof(AnsiString(Edit34->Text).c_str());
	PAItem->A1_B_F = 0.0;
	PAItem->A3_B_F = 1.0;

	PAItem->T_F3B = atof(AnsiString(Edit21->Text).c_str());
	PAItem->T_F3N = atof(AnsiString(Edit22->Text).c_str());
	PAItem->T_F1B = atof(AnsiString(Edit23->Text).c_str());
	PAItem->T_F1N = atof(AnsiString(Edit24->Text).c_str());
	PAItem->T_F2B = atof(AnsiString(Edit25->Text).c_str());
	PAItem->T_F2N = atof(AnsiString(Edit26->Text).c_str());
	PAItem->A2_T_F = atof(AnsiString(Edit34->Text).c_str());
	PAItem->A1_T_F = 0.0;
	PAItem->A3_T_F = 1.0;

	PAItem->V_F3B = atof(AnsiString(Edit27->Text).c_str());
	PAItem->V_F3N = atof(AnsiString(Edit28->Text).c_str());
	PAItem->V_F1B = atof(AnsiString(Edit29->Text).c_str());
	PAItem->V_F1N = atof(AnsiString(Edit30->Text).c_str());
	PAItem->V_F2B = atof(AnsiString(Edit31->Text).c_str());
	PAItem->V_F2N = atof(AnsiString(Edit32->Text).c_str());
	PAItem->A2_V_F = atof(AnsiString(Edit34->Text).c_str());
	PAItem->A1_V_F = 0.0;
	PAItem->A3_V_F = 1.0;
  }
  if(m_type == 6)
  {
	PAItem->P11_F3B = atof(AnsiString(Edit36->Text).c_str());
	PAItem->P11_F3N = atof(AnsiString(Edit37->Text).c_str());
	PAItem->P11_F1B = atof(AnsiString(Edit38->Text).c_str());
	PAItem->P11_F1N = atof(AnsiString(Edit39->Text).c_str());
	PAItem->P11_F2B = atof(AnsiString(Edit40->Text).c_str());
	PAItem->P11_F2N = atof(AnsiString(Edit41->Text).c_str());
	PAItem->A2_P11_F = atof(AnsiString(Edit33->Text).c_str());
	PAItem->A1_P11_F = 0.0;
	PAItem->A3_P11_F = 1.0;

	PAItem->P00_F3B = atof(AnsiString(Edit42->Text).c_str());
	PAItem->P00_F3N = atof(AnsiString(Edit43->Text).c_str());
	PAItem->P00_F1B = atof(AnsiString(Edit44->Text).c_str());
	PAItem->P00_F1N = atof(AnsiString(Edit45->Text).c_str());
	PAItem->P00_F2B = atof(AnsiString(Edit46->Text).c_str());
	PAItem->P00_F2N = atof(AnsiString(Edit47->Text).c_str());
	PAItem->A2_P00_F = atof(AnsiString(Edit33->Text).c_str());
	PAItem->A1_P00_F = 0.0;
	PAItem->A3_P00_F = 1.0;

	PAItem->TD_F3B = atof(AnsiString(Edit48->Text).c_str());
	PAItem->TD_F3N = atof(AnsiString(Edit49->Text).c_str());
	PAItem->TD_F1B = atof(AnsiString(Edit50->Text).c_str());
	PAItem->TD_F1N = atof(AnsiString(Edit51->Text).c_str());
	PAItem->TD_F2B = atof(AnsiString(Edit52->Text).c_str());
	PAItem->TD_F2N = atof(AnsiString(Edit53->Text).c_str());
	PAItem->A2_TD_F = atof(AnsiString(Edit33->Text).c_str());
	PAItem->A1_TD_F = 0.0;
	PAItem->A3_TD_F = 1.0;

	PAItem->VD_F3B = atof(AnsiString(Edit54->Text).c_str());
	PAItem->VD_F3N = atof(AnsiString(Edit55->Text).c_str());
	PAItem->VD_F1B = atof(AnsiString(Edit56->Text).c_str());
	PAItem->VD_F1N = atof(AnsiString(Edit57->Text).c_str());
	PAItem->VD_F2B = atof(AnsiString(Edit58->Text).c_str());
	PAItem->VD_F2N = atof(AnsiString(Edit59->Text).c_str());
	PAItem->A2_VD_F = atof(AnsiString(Edit33->Text).c_str());
	PAItem->A1_VD_F = 0.0;
	PAItem->A3_VD_F = 1.0;

	PAItem->P_EL_F3B = atof(AnsiString(Edit61->Text).c_str());
	PAItem->P_EL_F3N = atof(AnsiString(Edit60->Text).c_str());
	PAItem->P_EL_F1B = atof(AnsiString(Edit89->Text).c_str());
	PAItem->P_EL_F1N = atof(AnsiString(Edit88->Text).c_str());
	PAItem->P_EL_F2B = atof(AnsiString(Edit87->Text).c_str());
	PAItem->P_EL_F2N = atof(AnsiString(Edit62->Text).c_str());
	PAItem->A2_P_EL_F = atof(AnsiString(Edit33->Text).c_str());
	PAItem->A1_P_EL_F = 0.0;
	PAItem->A3_P_EL_F = 1.0;
  }

  if (m_type == 7)
  {
	PAItem->K11_F3B = atof(AnsiString(Edit63->Text).c_str());
	PAItem->K11_F3N = atof(AnsiString(Edit64->Text).c_str());
	PAItem->K11_F1B = atof(AnsiString(Edit65->Text).c_str());
	PAItem->K11_F1N = atof(AnsiString(Edit66->Text).c_str());
	PAItem->K11_F2B = atof(AnsiString(Edit67->Text).c_str());
	PAItem->K11_F2N = atof(AnsiString(Edit68->Text).c_str());
	PAItem->A2_K11_F = atof(AnsiString(Edit35->Text).c_str());
	PAItem->A1_K11_F =0;
	PAItem->A3_K11_F = 1;

	PAItem->K00_F3B = atof(AnsiString(Edit69->Text).c_str());
	PAItem->K00_F3N = atof(AnsiString(Edit70->Text).c_str());
	PAItem->K00_F1B = atof(AnsiString(Edit71->Text).c_str());
	PAItem->K00_F1N = atof(AnsiString(Edit72->Text).c_str());
	PAItem->K00_F2B = atof(AnsiString(Edit73->Text).c_str());
	PAItem->K00_F2N = atof(AnsiString(Edit74->Text).c_str());
	PAItem->A2_K00_F = atof(AnsiString(Edit35->Text).c_str());
	PAItem->A1_K00_F = 0.0;
	PAItem->A3_K00_F = 1.0;

	PAItem->TF_F3B = atof(AnsiString(Edit75->Text).c_str());
	PAItem->TF_F3N = atof(AnsiString(Edit76->Text).c_str());
	PAItem->TF_F1B = atof(AnsiString(Edit77->Text).c_str());
	PAItem->TF_F1N = atof(AnsiString(Edit78->Text).c_str());
	PAItem->TF_F2B = atof(AnsiString(Edit79->Text).c_str());
	PAItem->TF_F2N = atof(AnsiString(Edit80->Text).c_str());
	PAItem->A2_TF_F = atof(AnsiString(Edit35->Text).c_str());
	PAItem->A1_TF_F = 0.0;
	PAItem->A3_TF_F = 1.0;

	PAItem->VF_F3B = atof(AnsiString(Edit81->Text).c_str());
	PAItem->VF_F3N = atof(AnsiString(Edit82->Text).c_str());
	PAItem->VF_F1B = atof(AnsiString(Edit83->Text).c_str());
	PAItem->VF_F1N = atof(AnsiString(Edit84->Text).c_str());
	PAItem->VF_F2B = atof(AnsiString(Edit85->Text).c_str());
	PAItem->VF_F2N = atof(AnsiString(Edit86->Text).c_str());
	PAItem->A2_VF_F = atof(AnsiString(Edit35->Text).c_str());
	PAItem->A1_VF_F = 0.0;
	PAItem->A3_VF_F = 1.0;
  }
  if(m_type == 8)
	PAItem->PREDICAT = Edit14->Text;

}

//---------------------------------------------------------------------------
void __fastcall Tredact_char::FormActivate(TObject *Sender)
{
  bool m_old_can = f_Can_list;
  f_Can_list = true;
  int type = PAItem->TYPE;
  Edit1->Text  = PAItem->SOSTAV;
  Edit13->Text = PAItem->NAME;
  Edit14->Text = PAItem->PREDICAT;
  Edit90->Text = PAItem->PREDICAT;


  if(Type_Char==PROP)
  {
    show_char_fuzzy();
    show_char_prop();
  }
  else
  {
    show_char_prop();
    show_char_fuzzy();
  }
  switch(type)
  {
    case 5:
      Label23->Caption="Рабочая операция";
      TabbedNotebook1->PageIndex = 0;
      break;

    case 6:
      Label23->Caption="Контроль работоспособности";
      TabbedNotebook1->PageIndex = 1;
      break;

    case 7:
      Label23->Caption="Функциональный контроль";
      TabbedNotebook1->PageIndex = 2;
      break;

    case 8:
      Label23->Caption="Проверка условия";
      TabbedNotebook1->PageIndex = 3;
      break;
  }
  f_Can_list = m_old_can;
}
//---------------------------------------------------------------------------
void Tredact_char::show_char_prop()
{
   int m_type  = TFE->TypeShape;
   Label62->Visible=true;
   Edit90->Visible=true;
   if (m_type == 5)
   {
     Edit2->Text = float_2_string(PAItem->B, 6);
     Edit3->Text = float_2_string(PAItem->T, 10);
     Edit4->Text = float_2_string(PAItem->V, 10);
   }
   if (m_type == 6)
   {
     Edit5->Text = float_2_string(PAItem->P_11, 6);
     Edit6->Text = float_2_string(PAItem->P_00, 6);
     Edit7->Text = float_2_string(PAItem->T_D, 10);
     Edit8->Text = float_2_string(PAItem->V_D, 10);
     Edit91->Text = float_2_string(PAItem->P_DIAGN_EL, 6);
   }
   if (m_type == 7)
   {
     Edit9->Text = float_2_string(PAItem->K_11, 6);
     Edit10->Text = float_2_string(PAItem->K_00, 6);
     Edit11->Text = float_2_string(PAItem->T_F, 10);
     Edit12->Text = float_2_string(PAItem->V_F, 10);
   }
   if (m_type == 8)
   {
     Label62->Visible = false;
     Edit90->Visible = false;
   }
   enable_false(m_type);//установка недоступности редактирования нечетких характеристик
}
//---------------------------------------------------------------------------
//установка недоступности редактирования нечетких характеристик
void  Tredact_char::enable_false(int type)
{
if(type==5)
   {Edit15->Enabled=false;Edit16->Enabled=false;Edit17->Enabled=false;Edit18->Enabled=false;Edit19->Enabled=false;Edit20->Enabled=false;
    Edit21->Enabled=false;Edit22->Enabled=false;Edit23->Enabled=false;Edit24->Enabled=false;Edit25->Enabled=false;Edit26->Enabled=false;
    Edit27->Enabled=false;Edit28->Enabled=false;Edit29->Enabled=false;Edit30->Enabled=false;Edit31->Enabled=false;Edit32->Enabled=false;
    Edit34->Enabled=false;
    Edit2->Enabled=true;Edit3->Enabled=true;Edit4->Enabled=true;
   }
else if(type==6)
   {Edit36->Enabled=false;Edit37->Enabled=false;Edit38->Enabled=false;Edit39->Enabled=false;Edit40->Enabled=false;Edit41->Enabled=false;
    Edit42->Enabled=false;Edit43->Enabled=false;Edit44->Enabled=false;Edit45->Enabled=false;Edit46->Enabled=false;Edit47->Enabled=false;
    Edit48->Enabled=false;Edit49->Enabled=false;Edit50->Enabled=false;Edit51->Enabled=false;Edit52->Enabled=false;Edit53->Enabled=false;
    Edit54->Enabled=false;Edit55->Enabled=false;Edit56->Enabled=false;Edit57->Enabled=false;Edit58->Enabled=false;Edit59->Enabled=false;
    Edit89->Enabled=false;Edit88->Enabled=false;Edit87->Enabled=false;Edit62->Enabled=false;Edit61->Enabled=false;Edit60->Enabled=false;
    Edit33->Enabled=false;
    Edit5->Enabled=true;Edit6->Enabled=true;Edit7->Enabled=true;Edit8->Enabled=true;Edit91->Enabled=true;
    }
else if(type==7)
   {Edit63->Enabled=false;Edit64->Enabled=false;Edit65->Enabled=false;Edit66->Enabled=false;Edit67->Enabled=false;Edit68->Enabled=false;
    Edit69->Enabled=false;Edit70->Enabled=false;Edit71->Enabled=false;Edit72->Enabled=false;Edit73->Enabled=false;Edit74->Enabled=false;
    Edit75->Enabled=false;Edit76->Enabled=false;Edit77->Enabled=false;Edit78->Enabled=false;Edit79->Enabled=false;Edit80->Enabled=false;
    Edit81->Enabled=false;Edit82->Enabled=false;Edit83->Enabled=false;Edit84->Enabled=false;Edit85->Enabled=false;Edit86->Enabled=false;
    Edit35->Enabled=false;
    Edit9->Enabled=true;Edit10->Enabled=true;Edit11->Enabled=true;Edit12->Enabled=true;
   }
}
//---------------------------------------------------------------------------
void Tredact_char::show_char_fuzzy()
{
  int m_type  = TFE->TypeShape;
  if (m_type == 5)
  {
    Edit15->Text = float_2_string(PAItem->B_F3B, 6);
    Edit16->Text = float_2_string(PAItem->B_F3N, 6);
    Edit17->Text = float_2_string(PAItem->B_F1B, 6);
    Edit18->Text = float_2_string(PAItem->B_F1N, 6);
    Edit19->Text = float_2_string(PAItem->B_F2B, 6);
    Edit20->Text = float_2_string(PAItem->B_F2N, 6);
    Edit34->Text = float_2_string(PAItem->A2_B_F, 4);

    Edit21->Text = float_2_string(PAItem->T_F3B, 10);
    Edit22->Text = float_2_string(PAItem->T_F3N, 10);
    Edit23->Text = float_2_string(PAItem->T_F1B, 10);
    Edit24->Text = float_2_string(PAItem->T_F1N, 10);
    Edit25->Text = float_2_string(PAItem->T_F2B, 10);
    Edit26->Text = float_2_string(PAItem->T_F2N, 10);

    Edit27->Text = float_2_string(PAItem->V_F3B, 10);
    Edit28->Text = float_2_string(PAItem->V_F3N, 10);
    Edit29->Text = float_2_string(PAItem->V_F1B, 10);
    Edit30->Text = float_2_string(PAItem->V_F1N, 10);
    Edit31->Text = float_2_string(PAItem->V_F2B, 10);
    Edit32->Text = float_2_string(PAItem->V_F2N, 10);
  }

  if (m_type == 6)
  {
    Edit36->Text = float_2_string(PAItem->P11_F3B, 6);
    Edit37->Text = float_2_string(PAItem->P11_F3N, 6);
    Edit38->Text = float_2_string(PAItem->P11_F1B, 6);
    Edit39->Text = float_2_string(PAItem->P11_F1N, 6);
    Edit40->Text = float_2_string(PAItem->P11_F2B, 6);
    Edit41->Text = float_2_string(PAItem->P11_F2N, 6);
    Edit33->Text = float_2_string(PAItem->A2_P11_F, 4);

    Edit42->Text = float_2_string(PAItem->P00_F3B, 6);
    Edit43->Text = float_2_string(PAItem->P00_F3N, 6);
    Edit44->Text = float_2_string(PAItem->P00_F1B, 6);
    Edit45->Text = float_2_string(PAItem->P00_F1N, 6);
    Edit46->Text = float_2_string(PAItem->P00_F2B, 6);
    Edit47->Text = float_2_string(PAItem->P00_F2N, 6);

    Edit48->Text = float_2_string(PAItem->TD_F3B, 10);
    Edit49->Text = float_2_string(PAItem->TD_F3N, 10);
    Edit50->Text = float_2_string(PAItem->TD_F1B, 10);
    Edit51->Text = float_2_string(PAItem->TD_F1N, 10);
    Edit52->Text = float_2_string(PAItem->TD_F2B, 10);
    Edit53->Text = float_2_string(PAItem->TD_F2N, 10);

    Edit54->Text = float_2_string(PAItem->VD_F3B, 10);
    Edit55->Text = float_2_string(PAItem->VD_F3N, 10);
    Edit56->Text = float_2_string(PAItem->VD_F1B, 10);
    Edit57->Text = float_2_string(PAItem->VD_F1N, 10);
    Edit58->Text = float_2_string(PAItem->VD_F2B, 10);
    Edit59->Text = float_2_string(PAItem->VD_F2N, 10);

    Edit61->Text = float_2_string(PAItem->P_EL_F3B, 6);
    Edit60->Text = float_2_string(PAItem->P_EL_F3N, 6);
    Edit89->Text = float_2_string(PAItem->P_EL_F1B, 6);
    Edit88->Text = float_2_string(PAItem->P_EL_F1N, 6);
    Edit87->Text = float_2_string(PAItem->P_EL_F2B, 6);
    Edit62->Text = float_2_string(PAItem->P_EL_F2N, 6);
  }

  if (m_type == 7)
  {
    Edit63->Text = float_2_string(PAItem->K11_F3B, 6);
    Edit64->Text = float_2_string(PAItem->K11_F3N, 6);
    Edit65->Text = float_2_string(PAItem->K11_F1B, 6);
    Edit66->Text = float_2_string(PAItem->K11_F1N, 6);
    Edit67->Text = float_2_string(PAItem->K11_F2B, 6);
    Edit68->Text = float_2_string(PAItem->K11_F2N, 6);
    Edit35->Text = float_2_string(PAItem->A2_K11_F, 4);

    Edit69->Text = float_2_string(PAItem->K00_F3B, 6);
    Edit70->Text = float_2_string(PAItem->K00_F3N, 6);
    Edit71->Text = float_2_string(PAItem->K00_F1B, 6);
    Edit72->Text = float_2_string(PAItem->K00_F1N, 6);
    Edit73->Text = float_2_string(PAItem->K00_F2B, 6);
    Edit74->Text = float_2_string(PAItem->K00_F2N, 6);

    Edit75->Text = float_2_string(PAItem->TF_F3B, 10);
    Edit76->Text = float_2_string(PAItem->TF_F3N, 10);
    Edit77->Text = float_2_string(PAItem->TF_F1B, 10);
    Edit78->Text = float_2_string(PAItem->TF_F1N, 10);
    Edit79->Text = float_2_string(PAItem->TF_F2B, 10);
    Edit80->Text = float_2_string(PAItem->TF_F2N, 10);

    Edit81->Text = float_2_string(PAItem->VF_F3B, 10);
    Edit82->Text = float_2_string(PAItem->VF_F3N, 10);
    Edit83->Text = float_2_string(PAItem->VF_F1B, 10);
    Edit84->Text = float_2_string(PAItem->VF_F1N, 10);
    Edit85->Text = float_2_string(PAItem->VF_F2B, 10);
    Edit86->Text = float_2_string(PAItem->VF_F2N, 10);
  }
  if (m_type == 8)
  {
    Edit14->Text = PAItem->PREDICAT;
  }


  enable_true(m_type);//установка доступности редактирования нечетких характеристик
}
//---------------------------------------------------------------------------
//установка доступности редактирования нечетких характеристик
void  Tredact_char::enable_true(int type)
{
if(type==5)
   {Edit15->Enabled=true;Edit16->Enabled=true;Edit17->Enabled=true;Edit18->Enabled=true;Edit19->Enabled=true;Edit20->Enabled=true;
    Edit21->Enabled=true;Edit22->Enabled=true;Edit23->Enabled=true;Edit24->Enabled=true;Edit25->Enabled=true;Edit26->Enabled=true;
    Edit27->Enabled=true;Edit28->Enabled=true;Edit29->Enabled=true;Edit30->Enabled=true;Edit31->Enabled=true;Edit32->Enabled=true;
//    Edit34->Enabled=true;
    Edit2->Enabled=false;Edit3->Enabled=false;Edit4->Enabled=false;
   }
else if(type==6)
   {Edit36->Enabled=true;Edit37->Enabled=true;Edit38->Enabled=true;Edit39->Enabled=true;Edit40->Enabled=true;Edit41->Enabled=true;
    Edit42->Enabled=true;Edit43->Enabled=true;Edit44->Enabled=true;Edit45->Enabled=true;Edit46->Enabled=true;Edit47->Enabled=true;
    Edit48->Enabled=true;Edit49->Enabled=true;Edit50->Enabled=true;Edit51->Enabled=true;Edit52->Enabled=true;Edit53->Enabled=true;
    Edit54->Enabled=true;Edit55->Enabled=true;Edit56->Enabled=true;Edit57->Enabled=true;Edit58->Enabled=true;Edit59->Enabled=true;
    Edit89->Enabled=true;Edit88->Enabled=true;Edit87->Enabled=true;Edit62->Enabled=true;Edit61->Enabled=true;Edit60->Enabled=true;
//    Edit33->Enabled=true;
    Edit5->Enabled=false;Edit6->Enabled=false;Edit7->Enabled=false;Edit8->Enabled=false;Edit91->Enabled=false;
    }
else if(type==7)
   {Edit63->Enabled=true;Edit64->Enabled=true;Edit65->Enabled=true;Edit66->Enabled=true;Edit67->Enabled=true;Edit68->Enabled=true;
    Edit69->Enabled=true;Edit70->Enabled=true;Edit71->Enabled=true;Edit72->Enabled=true;Edit73->Enabled=true;Edit74->Enabled=true;
    Edit75->Enabled=true;Edit76->Enabled=true;Edit77->Enabled=true;Edit78->Enabled=true;Edit79->Enabled=true;Edit80->Enabled=true;
    Edit81->Enabled=true;Edit82->Enabled=true;Edit83->Enabled=true;Edit84->Enabled=true;Edit85->Enabled=true;Edit86->Enabled=true;
//    Edit35->Enabled=true;
    Edit9->Enabled=false;Edit10->Enabled=false;Edit11->Enabled=false;Edit12->Enabled=false;
   }
}
//---------------------------------------------------------------------------
//функция проверки правильности ввода характеристик
int  Tredact_char::check_table()
{
  float prob1=0,prob2=0;
  int type = TFE->TypeShape;

 //перед тем, как перейти на другую запись, проверка допустимости значений
 //для вероятностей
  if(type==5) {prob1 = atof(AnsiString(Edit2->Text).c_str());}
  if(type==6) {prob1 = atof(AnsiString(Edit5->Text).c_str());prob2=atof(AnsiString(Edit6->Text).c_str());}
  if(type==7) {prob1 = atof(AnsiString(Edit9->Text).c_str());prob2=atof(AnsiString(Edit10->Text).c_str());}

  if( prob1<0.0 || prob1>1.0)
  {
	Application->MessageBox(_T("Значение вероятности должно быть в интервале 0...1"), _T("Ошибка"), MB_OK);
	if(type==1) Edit2->SetFocus();
	if(type==2) Edit5->SetFocus();
	if(type==3) Edit9->SetFocus();
	return 0;
  }
  if( prob2<0.0 || prob2>1.0)
  {
	Application->MessageBox(_T("Значение вероятности должно быть в интервале 0...1"), _T("Ошибка"), MB_OK);
	if(type==2) Edit6->SetFocus();
	if(type==3) Edit10->SetFocus();
	return 0;
  }
  return 1;
}

//---------------------------------------------------------------------------
//присмене страниц
void __fastcall Tredact_char::TabbedNotebook1Change(TObject *Sender,
      int NewTab, bool &AllowChange)
{
  AllowChange = f_Can_list;
}
/***********Обработка правильности ввода значений типа float по всем полям*****/
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit2Exit(TObject *Sender)
{if(Exit_Edit(Edit2)==0) return;if(check_table()==0) {Edit2->SetFocus();return;}}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit3Exit(TObject *Sender)
{if(Exit_Edit(Edit3)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit4Exit(TObject *Sender)
{if(Exit_Edit(Edit4)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit6Exit(TObject *Sender)
{if(Exit_Edit(Edit5)==0) return;if(check_table()==0) {Edit5->SetFocus();return;}}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit5Exit(TObject *Sender)
{if(Exit_Edit(Edit6)==0) return;if(check_table()==0) {Edit6->SetFocus();return;}}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit8Exit(TObject *Sender)
{if(Exit_Edit(Edit7)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit7Exit(TObject *Sender)
{if(Exit_Edit(Edit8)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit9Exit(TObject *Sender)
{if(Exit_Edit(Edit9)==0) return;if(check_table()==0) {Edit9->SetFocus();return;}}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit10Exit(TObject *Sender)
{if(Exit_Edit(Edit10)==0) return;if(check_table()==0)  {Edit10->SetFocus();return;}}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit12Exit(TObject *Sender)
{if(Exit_Edit(Edit11)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit11Exit(TObject *Sender)
{if(Exit_Edit(Edit12)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit15Exit(TObject *Sender)
{if(Exit_Edit(Edit15)==0) return;
if(exit_proverka_0_1(Edit15)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit16Exit(TObject *Sender)
{if(Exit_Edit(Edit16)==0) return;
if(exit_proverka_0_1(Edit16)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit17Exit(TObject *Sender)
{if(Exit_Edit(Edit17)==0) return;
if(exit_proverka_0_1(Edit17)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit18Exit(TObject *Sender)
{if(Exit_Edit(Edit18)==0) return;
if(exit_proverka_0_1(Edit18)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit19Exit(TObject *Sender)
{if(Exit_Edit(Edit19)==0) return;
if(exit_proverka_0_1(Edit19)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit20Exit(TObject *Sender)
{if(Exit_Edit(Edit20)==0) return;
if(exit_proverka_0_1(Edit20)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit21Exit(TObject *Sender)
{if(Exit_Edit(Edit21)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit22Exit(TObject *Sender)
{if(Exit_Edit(Edit22)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit23Exit(TObject *Sender)
{if(Exit_Edit(Edit23)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit24Exit(TObject *Sender)
{if(Exit_Edit(Edit24)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit25Exit(TObject *Sender)
{if(Exit_Edit(Edit25)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit26Exit(TObject *Sender)
{if(Exit_Edit(Edit26)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit27Exit(TObject *Sender)
{if(Exit_Edit(Edit27)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit28Exit(TObject *Sender)
{if(Exit_Edit(Edit28)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit29Exit(TObject *Sender)
{if(Exit_Edit(Edit29)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit30Exit(TObject *Sender)
{if(Exit_Edit(Edit30)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit31Exit(TObject *Sender)
{if(Exit_Edit(Edit31)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit32Exit(TObject *Sender)
{if(Exit_Edit(Edit32)==0) return;}
//---------------------------------------------------------------------------
//проверка правильности ввода значений типа float
int  Tredact_char::Exit_Edit(TEdit *E)
{
  if(read_float(AnsiString(E->Text).c_str()))
  {
	Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
    E->SetFocus();
    return 0;
  }
  return 1;
}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit36Exit(TObject *Sender)
{if(Exit_Edit(Edit36)==0) return;
if(exit_proverka_0_1(Edit36)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit37Exit(TObject *Sender)
{if(Exit_Edit(Edit37)==0) return;
if(exit_proverka_0_1(Edit37)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit38Exit(TObject *Sender)
{if(Exit_Edit(Edit38)==0) return;
if(exit_proverka_0_1(Edit38)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit39Exit(TObject *Sender)
{if(Exit_Edit(Edit39)==0) return;
if(exit_proverka_0_1(Edit39)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit40Exit(TObject *Sender)
{if(Exit_Edit(Edit40)==0) return;
if(exit_proverka_0_1(Edit40)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit41Exit(TObject *Sender)
{if(Exit_Edit(Edit41)==0) return;
if(exit_proverka_0_1(Edit41)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit42Exit(TObject *Sender)
{if(Exit_Edit(Edit42)==0) return;
if(exit_proverka_0_1(Edit42)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit43Exit(TObject *Sender)
{if(Exit_Edit(Edit43)==0) return;
if(exit_proverka_0_1(Edit43)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit44Exit(TObject *Sender)
{if(Exit_Edit(Edit44)==0) return;
if(exit_proverka_0_1(Edit44)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit45Exit(TObject *Sender)
{if(Exit_Edit(Edit45)==0) return;
if(exit_proverka_0_1(Edit45)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit46Exit(TObject *Sender)
{if(Exit_Edit(Edit46)==0) return;
if(exit_proverka_0_1(Edit46)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit47Exit(TObject *Sender)
{if(Exit_Edit(Edit47)==0) return;
if(exit_proverka_0_1(Edit47)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit48Exit(TObject *Sender)
{if(Exit_Edit(Edit48)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit49Exit(TObject *Sender)
{if(Exit_Edit(Edit49)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit50Exit(TObject *Sender)
{if(Exit_Edit(Edit50)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit51Exit(TObject *Sender)
{if(Exit_Edit(Edit51)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit52Exit(TObject *Sender)
{if(Exit_Edit(Edit52)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit53Exit(TObject *Sender)
{if(Exit_Edit(Edit53)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit54Exit(TObject *Sender)
{if(Exit_Edit(Edit54)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit55Exit(TObject *Sender)
{if(Exit_Edit(Edit55)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit56Exit(TObject *Sender)
{if(Exit_Edit(Edit56)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit57Exit(TObject *Sender)
{if(Exit_Edit(Edit57)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit58Exit(TObject *Sender)
{if(Exit_Edit(Edit58)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit59Exit(TObject *Sender)
{if(Exit_Edit(Edit59)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit63Exit(TObject *Sender)
{if(Exit_Edit(Edit63)==0) return;
if(exit_proverka_0_1(Edit63)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit64Exit(TObject *Sender)
{if(Exit_Edit(Edit64)==0) return;
if(exit_proverka_0_1(Edit64)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit65Exit(TObject *Sender)
{if(Exit_Edit(Edit65)==0) return;
if(exit_proverka_0_1(Edit65)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit66Exit(TObject *Sender)
{if(Exit_Edit(Edit66)==0) return;
if(exit_proverka_0_1(Edit66)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit67Exit(TObject *Sender)
{if(Exit_Edit(Edit67)==0) return;
if(exit_proverka_0_1(Edit67)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit68Exit(TObject *Sender)
{if(Exit_Edit(Edit68)==0) return;
if(exit_proverka_0_1(Edit68)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit69Exit(TObject *Sender)
{if(Exit_Edit(Edit69)==0) return;
if(exit_proverka_0_1(Edit69)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit70Exit(TObject *Sender)
{if(Exit_Edit(Edit70)==0) return;
if(exit_proverka_0_1(Edit70)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit71Exit(TObject *Sender)
{if(Exit_Edit(Edit71)==0) return;
if(exit_proverka_0_1(Edit71)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit72Exit(TObject *Sender)
{if(Exit_Edit(Edit72)==0) return;
if(exit_proverka_0_1(Edit72)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit73Exit(TObject *Sender)
{if(Exit_Edit(Edit73)==0) return;
if(exit_proverka_0_1(Edit73)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit74Exit(TObject *Sender)
{if(Exit_Edit(Edit74)==0) return;
if(exit_proverka_0_1(Edit74)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit75Exit(TObject *Sender)
{if(Exit_Edit(Edit75)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit76Exit(TObject *Sender)
{if(Exit_Edit(Edit76)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit77Exit(TObject *Sender)
{if(Exit_Edit(Edit77)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit78Exit(TObject *Sender)
{if(Exit_Edit(Edit78)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit79Exit(TObject *Sender)
{if(Exit_Edit(Edit79)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit80Exit(TObject *Sender)
{if(Exit_Edit(Edit80)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit81Exit(TObject *Sender)
{if(Exit_Edit(Edit81)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit82Exit(TObject *Sender)
{if(Exit_Edit(Edit82)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit83Exit(TObject *Sender)
{if(Exit_Edit(Edit83)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit84Exit(TObject *Sender)
{if(Exit_Edit(Edit84)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit85Exit(TObject *Sender)
{if(Exit_Edit(Edit85)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit86Exit(TObject *Sender)
{if(Exit_Edit(Edit86)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit91Exit(TObject *Sender)
{
if(Exit_Edit(Edit91)==0) return;
}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit89Exit(TObject *Sender)
{
if(Exit_Edit(Edit89)==0) return;
if(exit_proverka_0_1(Edit89)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit88Exit(TObject *Sender)
{
if(Exit_Edit(Edit88)==0) return;
if(exit_proverka_0_1(Edit88)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit87Exit(TObject *Sender)
{
if(Exit_Edit(Edit87)==0) return;
if(exit_proverka_0_1(Edit87)==0) return;
}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit62Exit(TObject *Sender)
{
if(Exit_Edit(Edit62)==0) return;
if(exit_proverka_0_1(Edit62)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit61Exit(TObject *Sender)
{
if(Exit_Edit(Edit61)==0) return;
if(exit_proverka_0_1(Edit61)==0) return;}
//---------------------------------------------------------------------------
void __fastcall Tredact_char::Edit60Exit(TObject *Sender)
{
if(Exit_Edit(Edit60)==0) return;
if(exit_proverka_0_1(Edit60)==0) return;}
//---------------------------------------------------------------------------

int Tredact_char::exit_proverka_0_1(TEdit *Edit)
{
  float i = atof(AnsiString(Edit->Text).c_str());
  if(i<0||i>1)
  {
    Application->MessageBox(_T("Значение должно быть в интервале [0,1]."), _T("Ошибка!"), MB_OK);
    Edit->SetFocus();
    return 0 ;
  }
  return 1;
}









