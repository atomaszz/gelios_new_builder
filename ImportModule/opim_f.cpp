//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "opim_f.h"
#include "uIMRIncl_all.h"
#include <math.h>
#include "uGlsAtmCommon.h"
#include "uFmGridSovm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Topt_sadacha *opt_sadacha;
//---------------------------------------------------------------------------
__fastcall Topt_sadacha::Topt_sadacha(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//при выборе одного из пунктов - одинаковые действия
void __fastcall Topt_sadacha::CheckBox1Click(TObject *Sender)
{
  if(CheckBox1->Checked==true)
  {
    what_sadacha_check(ZAD_1);
    type_sadacha=ZAD_1;
    CheckBox2->Checked=false;
    CheckBox3->Checked=false;
    CheckBox4->Checked=false;
    CheckBox6->Checked=false;
    CheckBox5->Checked=false;

    CheckBox7->Visible=true;
    CheckBox8->Visible=true;
    CheckBox7->Checked=false;
    CheckBox8->Checked=false;
    all_visible_false();
  }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox2Click(TObject *Sender)
{
  if(CheckBox2->Checked==true)
  {
    what_sadacha_check(ZAD_2);
    type_sadacha=ZAD_2;
    CheckBox1->Checked=false;CheckBox3->Checked=false;CheckBox4->Checked=false;
    CheckBox6->Checked=false;CheckBox5->Checked=false;

    CheckBox7->Visible=true;CheckBox8->Visible=true;
    CheckBox7->Checked=false;CheckBox8->Checked=false;
    all_visible_false();
  }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox3Click(TObject *Sender)
{
  if(CheckBox3->Checked==true)
  {
   what_sadacha_check(ZAD_3);
   type_sadacha=ZAD_3;
   CheckBox2->Checked=false;CheckBox1->Checked=false;CheckBox4->Checked=false;
   CheckBox6->Checked=false;CheckBox5->Checked=false;

   CheckBox7->Visible=true;CheckBox8->Visible=true;
   CheckBox7->Checked=false;CheckBox8->Checked=false;
   all_visible_false();
   }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox4Click(TObject *Sender)
{
if(CheckBox4->Checked==true) {what_sadacha_check(ZAD_4);
   type_sadacha=ZAD_4;
   CheckBox2->Checked=false;CheckBox3->Checked=false;CheckBox1->Checked=false;
   CheckBox6->Checked=false;CheckBox5->Checked=false;

   CheckBox7->Visible=false;CheckBox8->Visible=false;
   CheckBox7->Checked=false;CheckBox8->Checked=false;
   }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox5Click(TObject *Sender)
{
if(CheckBox5->Checked==true)
  {what_sadacha_check(ZAD_5);
   type_sadacha=ZAD_5;
   CheckBox2->Checked=false;CheckBox3->Checked=false;CheckBox4->Checked=false;
   CheckBox6->Checked=false;CheckBox1->Checked=false;

   CheckBox7->Visible=false;CheckBox8->Visible=false;
   CheckBox7->Checked=false;CheckBox8->Checked=false;
   }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox6Click(TObject *Sender)
{
if(CheckBox6->Checked==true)
  {what_sadacha_check(ZAD_6);
   type_sadacha=ZAD_6;
   CheckBox2->Checked=false;CheckBox3->Checked=false;CheckBox4->Checked=false;
   CheckBox1->Checked=false;CheckBox5->Checked=false;

   CheckBox7->Visible=false;CheckBox8->Visible=false;
   CheckBox7->Checked=false;CheckBox8->Checked=false;
   }

}
//---------------------------------------------------------------------------
//получение картинки задачи в зависимости от выбора
void _fastcall Topt_sadacha::what_sadacha_check(int i)
{
 Image1->Picture = NULL;
 Image2->Picture = NULL;
can_list=true;
switch(i)
      {
      case ZAD_1:Label2->Caption="Ограничения";
             ImageList1->GetBitmap(ZAD_1,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_1,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=0;
             break;
      case ZAD_2:Label2->Caption="Ограничения";
             ImageList1->GetBitmap(ZAD_2,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_2,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=1;
             break;
      case ZAD_3:Label2->Caption="Ограничения";
             ImageList1->GetBitmap(ZAD_3,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_3,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=2;
             break;
      case ZAD_4:Label2->Caption="Примечания";
             ImageList1->GetBitmap(ZAD_4,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_4,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=3;
             break;
      case ZAD_5:Label2->Caption="Примечания";
             ImageList1->GetBitmap(ZAD_5,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_5,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=4;
             break;
      case ZAD_6:Label2->Caption="Примечания";
             ImageList1->GetBitmap(ZAD_6,Image1->Picture->Bitmap);
             ImageList2->GetBitmap(ZAD_6,Image2->Picture->Bitmap);
             TabbedNotebook1->PageIndex=5;
             break;
      }
can_list=false;
Image1->Refresh();
Image2->Refresh();
}
//---------------------------------------------------------------------------
//ПРИНЯТЬ
void __fastcall Topt_sadacha::Button1Click(TObject *Sender)
{
if(CheckBox1->Checked==false&&CheckBox2->Checked==false&&CheckBox3->Checked==false&&
   CheckBox4->Checked==false&&CheckBox5->Checked==false&&CheckBox6->Checked==false)
	 {Application->MessageBox(_T("Не выбран тип задачи оптимизации."), _T("Ошибка"), MB_OK | MB_ICONWARNING);
      return;}

//проверка наличия введенных коэффициентов
bool f;
f=true;
      if(CheckBox7->Checked&&CheckBox8->Checked==false&&CheckBox9->Checked==false) type_ogr=1;
      if(CheckBox7->Checked==false&&CheckBox8->Checked&&CheckBox9->Checked==false) type_ogr=2;
      if(CheckBox7->Checked&&CheckBox8->Checked&&CheckBox9->Checked==false) type_ogr=3;
      if(CheckBox7->Checked==false&&CheckBox8->Checked==false&&CheckBox9->Checked==false) type_ogr=0;
      if(CheckBox7->Checked&&CheckBox8->Checked==false&&CheckBox9->Checked==true) type_ogr=5;
      if(CheckBox7->Checked==false&&CheckBox8->Checked&&CheckBox9->Checked==true) type_ogr=6;
      if(CheckBox7->Checked&&CheckBox8->Checked&&CheckBox9->Checked==true) type_ogr=7;
      if(CheckBox7->Checked==false&&CheckBox8->Checked==false&&CheckBox9->Checked==true) type_ogr=4;
switch(type_sadacha)
      {
      case ZAD_1:if(CheckBox7->Checked)
                    if(Edit4->Text=="") f=false;
                 else Vd=Edit4->Text;//V
                 if(CheckBox8->Checked)
                    if(Edit5->Text=="") f=false;
                 else Td=Edit5->Text;//T
                 break;

      case ZAD_2:if(CheckBox7->Checked)
                    if(Edit6->Text=="") f=false;
                 else Vd=Edit6->Text;//V
                 if(CheckBox8->Checked)
                    if(Edit7->Text=="") f=false;
                 else Bd=Edit7->Text;//B
                 break;

      case ZAD_3:if(CheckBox7->Checked)
                    if(Edit8->Text=="") f=false;
                 else Bd=Edit8->Text;//B
                 if(CheckBox8->Checked)
                    if(Edit9->Text=="") f=false;
                 else Td=Edit9->Text; //T
                 break;

      case ZAD_4:if(Edit10->Text==""||Edit11->Text==""||Edit12->Text=="") f=false;
                 c1=Edit10->Text;c2=Edit11->Text;c3=Edit12->Text;
                 break;
      case ZAD_5:if(Edit1->Text==""||Edit2->Text==""||Edit3->Text=="") f=false;
                 c1=Edit1->Text;c2=Edit2->Text;c3=Edit3->Text;
                 break;
      case ZAD_6:if(Edit13->Text==""||Edit14->Text==""||Edit15->Text=="") f=false;
                 c1=Edit13->Text;c2=Edit14->Text;c3=Edit15->Text;
                 break;
      }
if(f==false)
  {
   Application->MessageBox(_T("Не заданы коэффициенты."), _T("Ошибка"), MB_OK);
   return;
  }
Close();
}
//---------------------------------------------------------------------------
//проверка на правильность ввода числа
int __fastcall Topt_sadacha::exit_proverka_simb(TEdit *Edit)
{
  if(read_float(AnsiString(Edit->Text).c_str()))
  {
	Application->MessageBox(_T("Использован недопустимый символ."), _T("Ошибка"), MB_OK);
	Edit->SetFocus();
	return 0;
  }

return 1;
}
//---------------------------------------------------------------------------
//проверка на интервал 0...1
int __fastcall Topt_sadacha::exit_proverka_0_1(TEdit *Edit)
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
//---------------------------------------------------------------------------
//проверка на интервал -1...+1
int __fastcall Topt_sadacha::exit_proverka_1_1(TEdit *Edit)
{
float i;
if(exit_proverka_simb(Edit)==0)
  return 0;

 i=atof(AnsiString(Edit->Text).c_str());
 if(fabs(i)>1)
	{
	 Application->MessageBox(_T("Значение должно быть в интервале [-1,+1]."), _T("Ошибка!"), MB_OK);
	 Edit->SetFocus();
	 return 0;
	}
return 1;
}
//---------------------------------------------------------------------------
//проверка на интервал > 0
int __fastcall Topt_sadacha::exit_proverka_b_0(TEdit *Edit)
{
float i;
if(exit_proverka_simb(Edit)==0)
  return 0;

 i=atof(AnsiString(Edit->Text).c_str());
 if(i<0)
    {
     Application->MessageBox(_T("Значение должно быть больше 0."), _T("Ошибка!"), MB_OK);
     Edit->SetFocus();
     return 0 ;
    }
return 1;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::FormActivate(TObject *Sender)
{
can_list=true;
switch(type_sadacha)
      {
      case ZAD_1:CheckBox1->Checked=true;TabbedNotebook1->PageIndex=0;
                 break;
      case ZAD_2:CheckBox2->Checked=true;TabbedNotebook1->PageIndex=1;
                 break;
      case ZAD_3:CheckBox3->Checked=true;TabbedNotebook1->PageIndex=2;break;
      case ZAD_4:CheckBox4->Checked=true;TabbedNotebook1->PageIndex=3;break;
      case ZAD_5:CheckBox5->Checked=true;TabbedNotebook1->PageIndex=4;break;
      case ZAD_6:CheckBox6->Checked=true;TabbedNotebook1->PageIndex=5;break;
      }
if(type_sadacha==0||type_sadacha==1||type_sadacha==2)
    switch(type_ogr)
        {
        case 0:CheckBox7->Checked=false;
               CheckBox8->Checked=false;
			   CheckBox9->Checked=false;
               break;
        case 1:CheckBox7->Checked=true;
               CheckBox8->Checked=false;
               CheckBox9->Checked=false;
               break;
        case 2:CheckBox7->Checked=false;
               CheckBox8->Checked=true;
               CheckBox9->Checked=false;
               break;
        case 3:CheckBox7->Checked=true;
               CheckBox8->Checked=true;
               CheckBox9->Checked=false;
               break;
        case 4:CheckBox7->Checked=false;
               CheckBox8->Checked=false;
               CheckBox9->Checked=true;
               break;
        case 5:CheckBox7->Checked=true;
               CheckBox8->Checked=false;
               CheckBox9->Checked=true;
               break;
        case 6:CheckBox7->Checked=false;
               CheckBox8->Checked=true;
               CheckBox9->Checked=true;
               break;
        case 7:CheckBox7->Checked=true;
               CheckBox8->Checked=true;
               CheckBox9->Checked=true;
               break;
         }
    else
        switch(type_ogr)
       {case 0:
        case 1:
        case 2:
        case 3: CheckBox9->Checked=false;
               break;
        case 4:
        case 5:
        case 6:
        case 7: CheckBox9->Checked=true;
        }
can_list=false;
  CheckBox9Click(NULL);
}
//---------------------------------------------------------------------------
//отображение выблранной задачи в предикатной модели
AnsiString  Topt_sadacha::make_sadacha()
{
  AnsiString s;
  if(CheckBox9->Checked==true)
  {

  }
    switch(type_sadacha)
      {
      case ZAD_1:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 if((type_ogr==3)||(type_ogr==7))  s=s+",[[Vd,"+Vd+"],[Td,"+Td+"]]";
                 if((type_ogr==1)||(type_ogr==5))  s=s+",[[Vd,"+Vd+"],[]]";
                 if((type_ogr==2)||(type_ogr==6))  s=s+ ",[[],[Td,"+Td+"]]";
                 if((type_ogr==0)||(type_ogr==4))  s=s+ ",[[],[]]";
                 s=s+").";
                 break;

      case ZAD_2:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 if((type_ogr==3)||(type_ogr==7))  s=s+",[[Vd,"+Vd+"],[Bd,"+Bd+"]]";
                 if((type_ogr==1)||(type_ogr==5))  s=s+",[[Vd,"+Vd+"],[]]";
                 if((type_ogr==2)||(type_ogr==6))  s=s+ ",[[],[Bd,"+Bd+"]]";
                 if((type_ogr==0)||(type_ogr==4))  s=s+ ",[[],[]]";
                 s=s+").";
                 break;

      case ZAD_3:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 if((type_ogr==3)||(type_ogr==7))  s=s+",[[Bd,"+Bd+"],[Td,"+Td+"]]";
                 if((type_ogr==1)||(type_ogr==5))  s=s+",[[Bd,"+Bd+"],[]]";
                 if((type_ogr==2)||(type_ogr==6))  s=s+ ",[[],[Td,"+Td+"]]";
                 if((type_ogr==0)||(type_ogr==4))  s=s+ ",[[],[]]";
                 s=s+").";
                 break;

      case ZAD_4:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 s=s+",[[c1,"+c1+"],[c2,"+c2+"],[c3,"+c3+"]]";
                 s=s+").";
                 break;

      case ZAD_5:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 s=s+",[[c1,"+c1+"],[c2,"+c2+"],[c3,"+c3+"]]";
                 s=s+").";
                 break;

      case ZAD_6:
                 s=(AnsiString)"zadacha_opt("+(type_sadacha+1);
                 s=s+",[[l,"+c1+"],[k,"+c2+"],[m,"+c3+"]]";
                 s=s+").";
                 break;
      }
return s;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit4Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit4)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit5Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit5)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit6Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit6)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit7Exit(TObject *Sender)
{
if(exit_proverka_0_1(Edit7)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit8Exit(TObject *Sender)
{
if(exit_proverka_0_1(Edit8)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit9Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit9)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit10Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit10)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit11Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit11)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit12Exit(TObject *Sender)
{
if(exit_proverka_b_0(Edit12)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit13Exit(TObject *Sender)
{
if(exit_proverka_1_1(Edit13)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit14Exit(TObject *Sender)
{
if(exit_proverka_1_1(Edit14)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit15Exit(TObject *Sender)
{
if(exit_proverka_1_1(Edit15)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::TabbedNotebook1Change(TObject *Sender,
      int NewTab, bool &AllowChange)
{
if(can_list)
   AllowChange=true;
else
   AllowChange=false;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::FormCreate(TObject *Sender)
{
type_sadacha=ZAD_1;
type_ogr=0;
Bd="0";Td="100000000";Vd="100000000";
c1="0";c2="0";c3="0";
Edit4->Text=Vd;//V
Edit5->Text=Td;//T
Edit6->Text=Vd;//V
Edit7->Text=Bd;//B
Edit8->Text=Bd;//B
Edit9->Text=Td;//T

   MassWork = new TDynamicArray;
   OptSovm = new TDischargedMassiv(0);
   Rate = 0.0;
   f_TypeMetod = TOHN;

}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit1Exit(TObject *Sender)
{
if(exit_proverka_0_1(Edit1)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit2Exit(TObject *Sender)
{
if(exit_proverka_0_1(Edit2)==0)
  return;
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::Edit3Exit(TObject *Sender)
{
if(exit_proverka_0_1(Edit3)==0)
  return;
}
//---------------------------------------------------------------------------
//при выборе того или иного ограничения
void __fastcall Topt_sadacha::CheckBox7Click(TObject *Sender)
{
if(CheckBox7->Checked)
   {
   switch(type_sadacha)
         {
         case ZAD_1:Label7->Visible=true;Label8->Visible=true;Edit4->Visible=true;
                    Edit4->Text=Vd;
                    break;
         case ZAD_2:Label11->Visible=true;Label12->Visible=true;Edit6->Visible=true;
                    Edit6->Text=Vd;
                    break;
         case ZAD_3:Label15->Visible=true;Label16->Visible=true;Edit8->Visible=true;
                    Edit8->Text=Bd;
                    break;
         }
   }
else
   {
   switch(type_sadacha)
         {
         case ZAD_1:Label7->Visible=false;Label8->Visible=false;Edit4->Visible=false;
                    break;
         case ZAD_2:Label11->Visible=false;Label12->Visible=false;Edit6->Visible=false;
                    break;
         case ZAD_3:Label15->Visible=false;Label16->Visible=false;Edit8->Visible=false;
                    break;
         }
   }
}
//---------------------------------------------------------------------------
void __fastcall Topt_sadacha::CheckBox8Click(TObject *Sender)
{
if(CheckBox8->Checked)
   {
   switch(type_sadacha)
         {
         case ZAD_1:Label9->Visible=true;Label10->Visible=true;Edit5->Visible=true;
                    Edit5->Text=Td;
                    break;
         case ZAD_2:Label13->Visible=true;Label14->Visible=true;Edit7->Visible=true;
                    Edit7->Text=Bd;
                    break;
         case ZAD_3:Label17->Visible=true;Label18->Visible=true;Edit9->Visible=true;
                    Edit9->Text=Td;
                    break;
         }
   }
else
   {
   switch(type_sadacha)
         {
         case ZAD_1:Label9->Visible=false;Label10->Visible=false;Edit5->Visible=false;
                    break;
         case ZAD_2:Label13->Visible=false;Label14->Visible=false;Edit7->Visible=false;
                    break;
         case ZAD_3:Label17->Visible=false;Label18->Visible=false;Edit9->Visible=false;
                    break;
         }
   }
}
//---------------------------------------------------------------------------
void Topt_sadacha::all_visible_false(void)
{
Label9->Visible=false;Label10->Visible=false;Edit5->Visible=false;
Label13->Visible=false;Label14->Visible=false;Edit7->Visible=false;
Label17->Visible=false;Label18->Visible=false;Edit9->Visible=false;
Label7->Visible=false;Label8->Visible=false;Edit4->Visible=false;
Label11->Visible=false;Label12->Visible=false;Edit6->Visible=false;
Label15->Visible=false;Label16->Visible=false;Edit8->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall Topt_sadacha::ydal(int k)
{
}
//---------------------------------------------------------------------------



void __fastcall Topt_sadacha::CheckBox9Click(TObject *Sender)
{
   btShowGridSovm->Enabled = CheckBox9->Checked;
}
//---------------------------------------------------------------------------


void __fastcall Topt_sadacha::FormDestroy(TObject *Sender)
{
  delete MassWork;
  delete OptSovm;
}
//---------------------------------------------------------------------------

int OPM_CompareNode(void* A, void* B)
{
   TBaseShape* m_A = static_cast<TBaseShape*>(A);
   TBaseShape* m_B = static_cast<TBaseShape*>(B);
   if(m_A->ID > m_B->ID)
     return 1;
   if(m_A->ID < m_B->ID)
     return -1;
   return 0;
}

bool OPM_Inorder(void* A)
{
   TBaseShape* m_A = static_cast<TBaseShape*>(A);
   opt_sadacha->MassWork->Append((void*)m_A->ID);
   return true;
}

void Topt_sadacha::InitData()
{
  TBaseWorkShape *WS;
  TBaseShape *TFE;
  TGlsBinaryTree *BTree = new TGlsBinaryTree(OPM_CompareNode);
  for(int i = 0; i <= MassWork->Count - 1; i++)
  {
   WS = static_cast<TBaseWorkShape*>(MassWork->Items[i]);
   for (int j = 0; j <= WS->WorkShapesCount - 1; j++ )
   {
      TFE = static_cast<TBaseShape*>(WS->GetWorkShape(j));
      BTree->insert(TFE);
   }
  }

  MassWork->Clear();
  BTree->inorder(OPM_Inorder);
  delete BTree;
  CheckCol();
}

void Topt_sadacha::LoadData()
{
  int v;
  int rw = OptSovm->HiRow();
  int rc = MassWork->Count;
  FmGridSovm->sgSovm->RowCount = 2;
  FmGridSovm->sgSovm->FixedRows = 1;
  FmGridSovm->sgSovm->ColCount = rc;
  if (rw > 0)
    FmGridSovm->sgSovm->RowCount = rw + 2;

  for(int i = 0; i <= rc - 1; i++)
    SGCells(FmGridSovm->sgSovm, 0, i, int(MassWork->Items[i]));

  rc = OptSovm->HiCol();
  for (int i = 0; i <= rw; i++)
  {
    for(int j = 0; j <= rc; j++)
    {
      v = OptSovm->Items[i][j];
      if(v)
      {
        for(int k = 0; k <= FmGridSovm->sgSovm->ColCount - 1; k++)
        {
          if (StrToInt(FmGridSovm->sgSovm->Cells[k][0]) == j)
            SGCells(FmGridSovm->sgSovm, i+1, k, v);
        }
      }
    }
  }
}


void Topt_sadacha::SaveData()
{

  int rw = OptSovm->HiRow();
  int rc = OptSovm->HiCol();
  for (int i = 0; i <= rw; i++)
    for(int j = 0; j <= rc; j++)
      OptSovm->Items[i][j] = 0;


  rw = FmGridSovm->sgSovm->RowCount;
  rc = FmGridSovm->sgSovm->ColCount;

  for (int i = 1; i <= rw - 1; i++)
  {
    for(int j = 0; j <= rc - 1; j++)
    {
      if ( !SameText(Trim(FmGridSovm->sgSovm->Cells[j][i]), "" ) )
      {
         int mcol = StrToIntDef(FmGridSovm->sgSovm->Cells[j][0], 0);
         if(mcol)
           OptSovm->Items[i-1][mcol] = StrToIntDef(FmGridSovm->sgSovm->Cells[j][i], 0);
      }
    }
  }
}




void __fastcall Topt_sadacha::btShowGridSovmClick(TObject *Sender)
{
    TBaseShape *TFE;
    FmGridSovm = new TFmGridSovm(Application);
    LoadData();
    if (FmGridSovm->ShowModal() == mrOk)
      SaveData();
    FmGridSovm->Release();

}
//---------------------------------------------------------------------------

void Topt_sadacha::CheckCol()
{
   int rw = OptSovm->HiRow();
   int rc = OptSovm->HiCol();
   int v;
   for (int i = 0; i <= rw; i++)
   {
     for(int j = 0; j <= rc; j++)
     {
       v = OptSovm->Items[i][j];
       if(v && !MassWork->Find((void*)j))
         OptSovm->Items[i][j] = 0;
     }
   }
}

int Topt_sadacha::get_type_metod()
{
   return f_TypeMetod;
}

void Topt_sadacha::set_type_metod(int typ)
{
   f_TypeMetod = typ;
}


int Topt_sadacha::type_t_v()
{
  switch(type_sadacha)
   {
   case ZAD_1:
               switch(type_ogr)
                    {
                     case 0:return 0;
                     case 1:return 2;
                     case 2:return 1;
                     case 3:return 3;
                     case 4:return 0;
                     case 5:return 2;
                     case 6:return 1;
                     case 7:return 3;
                    }
              break;
   case ZAD_2:
                switch(type_ogr)
                    {
                     case 0:return 0;
                     case 1:return 2;
                     case 2:return 0;
                     case 3:return 2;
                     case 4:return 0;
                     case 5:return 2;
                     case 6:return 0;
                     case 7:return 2;
                    }
              break;
   case ZAD_3:
                switch(type_ogr)
                    {
                     case 0:return 0;
                     case 1:return 1;
                     case 2:return 0;
                     case 3:return 1;
                     case 4:return 0;
                     case 5:return 1;
                     case 6:return 0;
                     case 7:return 1;
                    }
              break;
   case ZAD_4://обобщенные задачи
   case ZAD_5:
   case ZAD_6: return 0;
 //  break;
   }
   return 0;
}

AnsiString  Topt_sadacha::make_ogrsovm()
{
  int v;
  AnsiString Res, Item;
  int rc = MassWork->Count;
  int rw = OptSovm->HiRow();
  if (CheckBox9->Checked)
  {
    for (int i = 0; i <= rw; i++)
    {
      Item = "ogr_sovmest([";
      for(int j = 0; j <= rc - 1; j++)
      {
        v = OptSovm->Items[i][j + 1];
        if (!j)
         Item = Item + IntToStr(v);
        else
         Item = Item + "," + IntToStr(v);
      }
      Item = Item + "]).";
      Res = Res + Item + "\r\n";
    }
  }
  return Res;
}

bool Topt_sadacha::InOgrSovm(int ATFE_ID)
{
  int v;
  int rw = OptSovm->HiRow();
  for (int i = 0; i <= rw; i++)
  {
    v = OptSovm->Items[i][ATFE_ID];
    if(v > 0)
      return true;
  }
  return false;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

