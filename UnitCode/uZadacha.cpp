//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "uZadacha.h"
#include "uIMRIncl_all.h"
#include "opim_f.h"
#include "uCommonGraph.h"
#include "ufmViewDecision.h"
#include "ufmStartDecision.h"
#include "uCommonCalc.h"
#include "uIMRIncl_all.h"
#include "uPieModule.h"
#include "uOzenkTFE.h"
#include "ufmOzenkView.h"
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

TZadacha::TZadacha()
{
  f_Cnt_alt = 0;
  f_CntComm = 0;
  f_CheckNud = false;
  OptOgrSovm = false;
  f_TMax = 100000000.0;
  f_VMax = 100000000.0;
  FOgrSovmArray = NULL;
  f_Tree = new TPredicateTree;
  f_Equal = new TDynamicArray;
  f_PartialDecision = new TPartialDecision(this);
  f_ListPTI = new TList;
  Scanner = new TPredicateScanner;
  TrackCreator = new TPredicateTrackCreator;
  ozenk_t = new TDischargedMassiv(100000000.0);
  ozenk_v = new TDischargedMassiv(100000000.0);

}

TZadacha::~TZadacha()
{
  delete f_Tree;
  delete f_Equal;
  delete f_PartialDecision;
  delete f_ListPTI;
  delete Scanner;
  delete TrackCreator;
  delete ozenk_t;
  delete ozenk_v;

}

TPredicateTreeItem* __fastcall TZadacha::GetPTI(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListPTI->Count - 1)
     return static_cast<TPredicateTreeItem*>(f_ListPTI->Items[AIndex]);
   else
     return NULL;
}

void TZadacha::AddPTI(TPredicateTreeItem* AItem)
{
   if (f_ListPTI->IndexOf(AItem) < 0 )
     f_ListPTI->Add(AItem);
}

void TZadacha::ClearPTI()
{
   f_ListPTI->Clear();
}



void TZadacha::Clear()
{
  f_Tree->Clear();
  f_Equal->Clear();
  ClearPTI();
  TrackCreator->ClearTrack();
  TrackCreator->ClearBase();
}

void TZadacha::DoEqual()
{
   int m_id;
   int d = f_Tree->Count;
   TPredicateTreeItem *TI;
   TDynamicArray *A = new TDynamicArray;
   for (int i = 0 ; i <= d - 1; i++)
   {
     TI = f_Tree->Items[i];
     for (int j = 0; j <= TI->Count - 1; j++)
     {
        m_id = TI->TFE_ID[j];
        f_Tree->FindByTfeID(m_id, A);
        if (A->Count > 1)
          if (!f_Equal->Find((void*)m_id))
            f_Equal->Append((void*)m_id);
     }
   }
   delete A;
}

void TZadacha::SavePredicateModelToTempFile()
{
   TFileStream *FS = new TFileStream("temp_1.dec", fmCreate);
   FS->WriteBuffer(f_FullPredcateModel.c_str(), f_FullPredcateModel.Length());
   delete FS;
}

bool TZadacha::CheckPLGParamAlternative(TParamAlternative* AL)
{
  int plg;
  int trucnt = 0;
  AnsiString Pr;
  TParamAlternativeItem* Item;
  for(int i = 0; i <= AL->Count - 1; i++)
  {
    Item = AL->Items[i];
    Pr = Trim(Item->PREDICAT);
    if ( (Pr.Length() == 0) || SameText(Pr, "1") || SameText(Pr, "(нет условия)") )
      Item->CheckPLG = true;
    else if ( SameText(Pr, "0") )
        Item->CheckPLG = false;
    else
    {
      //gPieModule->RefreshModule();
      plg = gPieModule->Run1("tell(\"temp.pra\"),reconsult(\"temp_1.dec\")," + Pr);
      Item->CheckPLG = plg > 0 ;
    }
  }

  for(int i = 0; i <= AL->Count - 1; i++)
  {
    Item = AL->Items[i];
    if (Item->CheckPLG)
    {
      trucnt++;
      break;
    }

  }
  return trucnt >  0;
}


bool TZadacha::CheckCanDecision(int &AID)
{
  int  m_id;
  TBaseShape *B;
  TPredicateTreeItem *TI, *TJ;
  for (int i = 0; i <=  f_Tree->Count - 1; i++)
  {
     TI = f_Tree->Items[i];
     for (int j = 0; j <= TI->Count - 1; j++)
     {
        int  m_id = TI->TFE_ID[j];
        TJ = f_Tree->FindByParentID(m_id);
        if (!TJ)
        {
           B = TI->TFE[j];
           if (B)
           {
              if (!B->ParamAlt)
              {
                AID = m_id;
                return false;
              }
           }
           else
              {
                AID = m_id;
                return false;
              }
        }
     }
  }
  return true;
}

bool TZadacha::CheckCanPLGDecision(int &AID)
{
  int  m_id;
  TBaseShape *B;
  TPredicateTreeItem *TI, *TJ;
  for (int i = 0; i <=  f_Tree->Count - 1; i++)
  {
     TI = f_Tree->Items[i];
     for (int j = 0; j <= TI->Count - 1; j++)
     {
        int  m_id = TI->TFE_ID[j];
        B = TI->TFE[j];
        if (B && B->ParamAlt)
        {
          if (!CheckPLGParamAlternative(B->ParamAlt) && (B->TypeShape != 8) && !f_Tree->FindByParentID(m_id))
          {
            AID = m_id;
            return false;
          }
        }
     }
  }
  return true;
}




AnsiString TZadacha::Check()
{
   int m_id;
   AnsiString Res;
   if(!CheckCanDecision(m_id))
     Res = "Для подблока номер " + IntToStr(m_id) + " не заданы ни параметрические, ни структурные альтернативы.\r\nНахождение решения невозможно!";
   if(!Res.Length() && !CheckCanPLGDecision(m_id))
     Res = "Для подблока номер " + IntToStr(m_id) + " нет структурных альтернатив и все параметрические не проходят по заданным в них условиях.\r\nНахождение решения невозможно!";
   return Res;
}

void TZadacha::Init(int AType_Char,  bool ACheckNud, bool AOptOgrSovm, TOgrSovmArray *AOgrSovmArray, AnsiString AFullPredcateModel)
{
   TPredicateTreeItem* TI;
   TPredicateScannerItemKnot* Knot;
   f_CheckNud = ACheckNud;
   OptOgrSovm = AOptOgrSovm;
   FOgrSovmArray = AOgrSovmArray;
   DoEqual();
   ozenk_t->Clear();
   ozenk_v->Clear();
   f_FullPredcateModel = AFullPredcateModel;
   gPieModule->RefreshModule();
   SavePredicateModelToTempFile();
   f_PartialDecision->Clear();
   f_PartialDecision->Type_Char = AType_Char;
   f_PartialDecision->CheckNud = f_CheckNud;
   f_TMax = atof(opt_sadacha->Td.c_str());
   f_VMax = atof(opt_sadacha->Vd.c_str());
   for(int i = 0; i <= f_Tree->Count - 1; i++)
     AddPTI(f_Tree->Items[i]);

   TrackCreator->ClearBase();
   for(int i = 0; i <= f_Tree->Count - 1; i++)
   {
      TI = f_Tree->Items[i];
      Knot = TrackCreator->CreateKnotToBase();
      Knot->ParentID = TI->ParentID;
      Knot->NumAlt = TI->NumAlt;
      int m_type = TI->TypeWorkShape;
      if (m_type == 12)
       m_type = 1;
      Knot->TypeKnot = m_type;
      Knot->TFE_ID1 = TI->TFE_ID[0];
      Knot->TFE_ID2 = TI->TFE_ID[1];
      Knot->TFE_ID3 = TI->TFE_ID[2];
   }
   if ( OptOgrSovm )
   {
     TrackCreator->GenerateOptSovmTrack(FOgrSovmArray);
     LoadPredicateTrackCreatorItem(TrackCreator->Items[0]);
     FOgrSovmArray->SetCheckObj( FindUpperNodeForOgrSovm() );
   }
}

void TZadacha::ChekDeleted(TPredicateTreeItem* AI)
{
   TPartialDecisionItem* DI;
   TDynamicArray *D = new TDynamicArray;
   f_Tree->ArrayIDToDelete(AI, D);
   for(int i = 0; i <= D->Count - 1; i++)
   {
     int del =  int(D->Items[i]);
     DI = f_PartialDecision->FindPartialDecisionItemByParentID(del);
     while(DI)
     {
       f_PartialDecision->FreeItem(DI);
       DI = f_PartialDecision->FindPartialDecisionItemByParentID(del);
     }
   }
   delete D;
}



void TZadacha::Process()
{
  AnsiString S;
  TPredicateTreeItem *TI;
  TPartialDecisionItem* P;
  Nud_podgot();
  for (int i = CountPTI - 1; i >= 0 ; i--)
  {
     TI = PTI[i];
     P = f_PartialDecision->GetNew(TI);
     f_PartialDecision->FreeItem(f_PartialDecision->PullAlternate(P));
     P->Make();
     TI->TReated = true;
     ChekDeleted(TI);
  }
	if(f_PartialDecision->Type_Char==PROP)   get_opt_alt();
    if(f_PartialDecision->Type_Char==FUZZY)   get_opt_alt_fuz();

}


//---------------------------------------------------------------------------
//отсечение ПА, не подходящих по ограничениям и поиск экстремума
void TZadacha::get_opt_alt()
{
//Алгоритм:
//1. Просматриваем все ПА
//2, Учитываем все ограничения и отсекаем все ПА, которые не подходят по ограничениям
//3, Снова просматриваем все ПА
//4, Находим экстремум для выбранной функции оптимизации

  char str[1024];
  double b,t,v;
  float Bd,Td,Vd;
  float Bmax,Tmax,Vmax,Bmin,Tmin,Vmin;
  float C1,C2,C3;
  int type_sad,type_ogr;
  TPartialDecisionItem* PDI;
  TParamAlternative *PA;
  TParamAlternativeItem *AI;
  type_sad = opt_sadacha->type_sadacha;
  type_ogr = opt_sadacha->type_ogr;
  Bd = atof(opt_sadacha->Bd.c_str());
  Td = atof(opt_sadacha->Td.c_str());
  Vd = atof(opt_sadacha->Vd.c_str());
  C1 = atof(opt_sadacha->c1.c_str());
  C2 = atof(opt_sadacha->c2.c_str());
  C3 = atof(opt_sadacha->c3.c_str());

  //bool del = false;

  //ищем экстремум , не учитывая те ПА, которые не подходят по ограничениям
  double Max, Min, Func, Func_1;
  int num_extr;

  PDI = f_PartialDecision->Items[0];
  PA = PDI->ParamAlt;
  AI = PA->Items[0];
  switch(type_sad)
  {
           case ZAD_1:Max = -1;break;
           case ZAD_2:Min = AI->T;break;
           case ZAD_3:Min = AI->V;break;
           case ZAD_4:Func=-100000000;break;
           case ZAD_5://нужно найти максимальные и минимальные значения для нормировки
                      Bmax=-1;Tmax=-1;Vmax=-1;
                      Bmin=2;Tmin=100000000;Vmin=100000000;
                      for(int i = 0; i <= PA->Count - 1; i++)
                      {
                        AI = PA->Items[i];
                        b = AI->B;
                             t = AI->T;
                             v = AI->V;
                             if(b>Bmax) Bmax=b; if(t>Tmax) Tmax=t; if(v>Vmax) Vmax=v;
                             if(b<Bmin) Bmin=b; if(t<Tmin) Tmin=t; if(v<Vmin) Vmin=v;
                      }
                      if(Bmax==Bmin || Tmax==Tmin || Vmax==Vmin)
                        {
						Application->MessageBox(_T("Деление на ноль при расчете значения критерия оптимальности!\nРешение неверное!"),
						  _T("Ошибка!"), MB_OK | MB_ICONWARNING);
                        return;
                        }
                      Func=-10000;
                      break;

           case ZAD_6:Func=-1;break;
           }
num_extr=0;
bool n=false,exist_des=false;
int cnt_alt=0;
for(int i = 0; i <= PA->Count - 1; i++)
//while(!char_form->Table1->Eof)
     {
      AI = PA->Items[i];
      b=AI->B;
      t=AI->T;
      v=AI->V;
      strcpy(str, AI->SOSTAV.c_str());
     switch(type_sad)//не ищем экстрему среди записей, не подходящих по ограничениям
          {
           case ZAD_1:switch(type_ogr)//задача по В
                    {
                     case 1:if( v > Vd) n=true;//критерий V
                            else n=false;
                            break;
                     case 2:if( t > Td) n=true;//критерий T
                            else n=false;
                            break;
                     case 3:if( v > Vd || t > Td) n=true;//критерий V и T
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( v > Vd||unpack_sostav(str)==0) n=true;//критерий V
                            else n=false;
                            break;
                     case 6:if( t > Td||unpack_sostav(str)==0) n=true;//критерий T
                            else n=false;
                            break;
                     case 7:if( v > Vd || t > Td||unpack_sostav(str)==0) n=true;//критерий V и T
                            else n=false;
                            break;

                    }
              break;
           case ZAD_2:switch(opt_sadacha->type_ogr)//задача по Т
                    {
                     case 1:if( v > Vd) n=true;//критерий V
                            else n=false;
                            break;
                     case 2:if( b < Bd) n=true;//критерий B
                            else n=false;
                            break;
                     case 3:if( b < Bd || v > Vd) n=true;//критерий V и B
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( v > Vd||unpack_sostav(str)==0) n=true;//критерий V
                            else n=false;
                            break;
                     case 6:if( b < Bd||unpack_sostav(str)==0) n=true;//критерий B
                            else n=false;
                            break;
                     case 7:if( b < Bd || v > Vd||unpack_sostav(str)==0) n=true;//критерий V и B
                            else n=false;
                            break;
                    }
              break;
           case ZAD_3:switch(opt_sadacha->type_ogr)//задача по V
                    {
                     case 1:if( b < Bd) n=true;//критерий B
                            else n=false;
                            break;
                     case 2:if( t > Td) n=true;//критерий T
                            else n=false;
                            break;
                     case 3:if( t > Td || b < Bd) n=true;//критерий T и B
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( b < Bd||unpack_sostav(str)==0) n=true;//критерий B
                            else n=false;
                            break;
                     case 6:if( t > Td||unpack_sostav(str)==0) n=true;//критерий T
                            else n=false;
                            break;
                     case 7:if( t > Td || b < Bd||unpack_sostav(str)==0) n=true;//критерий T и B
                            else n=false;
                            break;

                    }
              break;
           }
   if(!n)//если опдходит по ограничениям
     {
     AI->Tag = 1;
     exist_des=true;
     switch(type_sad)
           {
           case ZAD_1: if(Max<=b) {Max=b;num_extr=i;}
              break;
           case ZAD_2:if(Min>=t) {Min=t;num_extr=i;}
              break;
           case ZAD_3:if(Min>=v) {Min=v;num_extr=i;}
              break;
           case ZAD_4:C1=atof(opt_sadacha->c1.c_str());
                      C2=atof(opt_sadacha->c2.c_str());
                      C3=atof(opt_sadacha->c3.c_str());
                      Func_1=C1*b-C2*t-C3*v;
                      if(Func_1>Func) {Func=Func_1;num_extr=i;}
              break;
           case ZAD_5:C1=atof(opt_sadacha->c1.c_str());
                      C2=atof(opt_sadacha->c2.c_str());
                      C3=atof(opt_sadacha->c3.c_str());
                      Func_1=C1*(b-Bmax)/(Bmax-Bmin)+C2*(t-Tmax)/(Tmax-Tmin)+C3*(v-Vmax)/(Vmax-Vmin);
                      if(Func_1>Func) {Func=Func_1;num_extr=i;}
              break;
           case ZAD_6:double l,k,m;
                      l=atof(opt_sadacha->c1.c_str());
                      k=atof(opt_sadacha->c2.c_str());
                      m=atof(opt_sadacha->c3.c_str());
                      if(t==0 || v==0)
                        {
						Application->MessageBox(_T("Деление на ноль при расчете значения критерия оптимальности!\nРешение неверное!"),
						  _T("Ошибка!"), MB_OK);
                        return;
                        }
					  Func_1= pow(b,l)/pow(t,k)/pow(v,m);
                      if(Func_1>Func) {Func=Func_1;num_extr=i;}

              break;
           }
      cnt_alt++;
      }
//      char_form->Table1->Next();
     }

//char_form->Table1->First();

if(exist_des==false)
  {
    f_OptB = "(нет)";
    f_OptT = "(нет)";
    f_OptV = "(нет)";
    f_Sostav = "(нет альтернатив,подходящих по ограничениям)";
    f_Cnt_alt = 0;
  }
else
  {
    AI = PA->Items[num_extr];
// оптимальное решение
    f_OptB = float_2_string(AI->B, 6);
    f_OptT = float_2_string(AI->T, 6);
    f_OptV = float_2_string(AI->V, 6);
    f_Sostav = AI->SOSTAV;
    f_Cnt_alt = cnt_alt;
 }
   f_CntComm = PA->Count;

}

void  TZadacha::ShowDecision(TColor AColorAlt, TColor AColorBadAlt, unsigned int ATime, TPredicatePathItem* APredicatePathItem)
{
//   unsigned int q = ATime;
//   TVarRec v =  ATime;

   char s[50];
   fmViewDecision = new TfmViewDecision(Application);
   fmViewDecision->VwColorAlt = AColorAlt;
   fmViewDecision->VwColorBadAlt = AColorBadAlt;

   fmViewDecision->ParamAlt = f_PartialDecision->Items[0]->ParamAlt;
   fmViewDecision->edB->Text = f_OptB;
   fmViewDecision->edT->Text = f_OptT;
   fmViewDecision->edV->Text = f_OptV;
   fmViewDecision->edOptSostav->Text = f_Sostav;
   fmViewDecision->StaticText1->Caption = IntToStr(f_Cnt_alt);
   fmViewDecision->StaticText2->Caption = IntToStr(f_CntComm);

   fmViewDecision->edVid1->Text = fmStartDecision->Edit1->Text;
   fmViewDecision->edVid2->Text = fmStartDecision->Edit5->Text;
   fmViewDecision->edOgr1->Text = fmStartDecision->Edit2->Text;
   fmViewDecision->edOgr2->Text = fmStartDecision->Edit3->Text;
   fmViewDecision->edKoef->Text = fmStartDecision->Edit4->Text;
   fmViewDecision->Type_Char = fmStartDecision->type_char;
   sprintf(s, "%u  мсек", ATime);
   fmViewDecision->edTime->Text = s;
   fmViewDecision->FPredicatePathItem = APredicatePathItem;
   fmViewDecision->ShowModal();
   fmViewDecision->Release();
}


void  TZadacha::get_opt_alt_fuz()
{
//Алгоритм:
//1. Просматриваем все ПА
//2, Учитываем все ограничения и отсекаем все ПА, которые не подходят по ограничениям
//3, Снова просматриваем все ПА
//4, Находим экстремум для выбранной функции оптимизации

  char str[1024];
  double b,t,v;
  float Bd,Td,Vd;
  float Bmax,Tmax,Vmax,Bmin,Tmin,Vmin;
  float C1,C2,C3;
  int type_sad,type_ogr;
  TPartialDecisionItem* PDI;
  TParamAlternative *PA;
  TParamAlternativeItem *AI;
  type_sad = opt_sadacha->type_sadacha;
  type_ogr = opt_sadacha->type_ogr;
  Bd = atof(opt_sadacha->Bd.c_str());
  Td = atof(opt_sadacha->Td.c_str());
  Vd = atof(opt_sadacha->Vd.c_str());
  C1 = atof(opt_sadacha->c1.c_str());
  C2 = atof(opt_sadacha->c2.c_str());
  C3 = atof(opt_sadacha->c3.c_str());


//ищем экстремум , не учитывая те ПА, которые не подходят по ограничениям
  double Max, Min, Func, Func_1;
  int num_extr;

  PDI = f_PartialDecision->Items[0];
  PA = PDI->ParamAlt;
  AI = PA->Items[0];

switch(type_sad)
           {
           case ZAD_1:Max=-1;break;
           case ZAD_2:Min=100000000;break;
           case ZAD_3:Min=100000000;break;
           case ZAD_4:Func=-100000000;break;
           case ZAD_5://нужно найти максимальные и минимальные значения для нормировки
                      Bmax=-1;Tmax=-1;Vmax=-1;
                      Bmin=2;Tmin=100000000;Vmin=100000000;
                      for(int i = 0; i <= PA->Count - 1; i++)
                            {
                             AI = PA->Items[i];	    
                             b = (AI->B_F1N+
                             AI->B_F1B+
                             AI->B_F2N+
                             AI->B_F2B+
                             AI->B_F3N+
                             AI->B_F3B)/6.0;

                             t = (AI->T_F1N+
                             AI->T_F1B+
                             AI->T_F2N+
                             AI->T_F2B+
                             AI->T_F3N+
                             AI->T_F3B)/6.0;

                             v = (AI->V_F1N+
                             AI->V_F1B+
                             AI->V_F2N+
                             AI->V_F2B+
                             AI->V_F3N+
                             AI->V_F3B)/6.0;

                             if(b>Bmax) Bmax=b; if(t>Tmax) Tmax=t; if(v>Vmax) Vmax=v;
                             if(b<Bmin) Bmin=b; if(t<Tmin) Tmin=t; if(v<Vmin) Vmin=v;

                            }
                      if(Bmax==Bmin || Tmax==Tmin || Vmax==Vmin)
                        {
						Application->MessageBox(_T("Деление на ноль при расчете значения критерия оптимальности!\nРешение неверное!"),
						  _T("Ошибка!"), MB_OK);
                        return;
                        }
                      Func=-10000;
                      break;

           case ZAD_6:Func=-1;break;
           }
num_extr=0;
bool n=false,exist_des=false;
int cnt_alt=0;
for(int i = 0; i <= PA->Count - 1; i++)
//while(!char_form->Table1->Eof)
     {
     AI = PA->Items[i];	     
     b = (AI->B_F1N+
     AI->B_F1B+
     AI->B_F2N+
     AI->B_F2B+
     AI->B_F3N+
     AI->B_F3B)/6.0;

     t = (AI->T_F1N+
     AI->T_F1B+
     AI->T_F2N+
     AI->T_F2B+
     AI->T_F3N+
     AI->T_F3B)/6.0;

    v = (AI->V_F1N+
    AI->V_F1B+
    AI->V_F2N+
    AI->V_F2B+
    AI->V_F3N+
    AI->V_F3B)/6.0;

     strcpy(str, AI->SOSTAV.c_str());
          switch(type_sad)//не ищем экстрему среди записей, не подходящих по ограничениям
          {
           case ZAD_1:switch(type_ogr)//задача по В
                    {
                     case 1:if( v > Vd) n=true;//критерий V
                            else n=false;
                            break;
                     case 2:if( t > Td) n=true;//критерий T
                            else n=false;
                            break;
                     case 3:if( v > Vd || t > Td) n=true;//критерий V и T
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( v > Vd||unpack_sostav(str)==0) n=true;//критерий V
                            else n=false;
                            break;
                     case 6:if( t > Td||unpack_sostav(str)==0) n=true;//критерий T
                            else n=false;
                            break;
                     case 7:if( v > Vd || t > Td||unpack_sostav(str)==0) n=true;//критерий V и T
                            else n=false;
                            break;
                    }
              break;
           case ZAD_2:switch(opt_sadacha->type_ogr)//задача по Т
                    {
                     case 1:if( v > Vd) n=true;//критерий V
                            else n=false;
                            break;
                     case 2:if( b < Bd) n=true;//критерий B
                            else n=false;
                            break;
                     case 3:if( b < Bd || v > Vd) n=true;//критерий V и B
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( v > Vd||unpack_sostav(str)==0) n=true;//критерий V
                            else n=false;
                            break;
                     case 6:if( b < Bd||unpack_sostav(str)==0) n=true;//критерий B
                            else n=false;
                            break;
                     case 7:if( b < Bd || v > Vd||unpack_sostav(str)==0) n=true;//критерий V и B
                            else n=false;
                            break;
                    }
              break;
           case ZAD_3:switch(opt_sadacha->type_ogr)//задача по V
                    {
                     case 1:if( b < Bd) n=true;//критерий B
                            else n=false;
                            break;
                     case 2:if( t > Td) n=true;//критерий T
                            else n=false;
                            break;
                     case 3:if( t > Td || b < Bd) n=true;//критерий T и B
                            else n=false;
                            break;
                     case 4:if(unpack_sostav(str)==0)n=true;
                            else n=false;
                            break;
                     case 5:if( b < Bd||unpack_sostav(str)==0) n=true;//критерий B
                            else n=false;
                            break;
                     case 6:if( t > Td||unpack_sostav(str)==0) n=true;//критерий T
                            else n=false;
                            break;
                     case 7:if( t > Td || b < Bd||unpack_sostav(str)==0) n=true;//критерий T и B
                            else n=false;
                            break;

                    }
              break;
           }
   if(!n)//если опдходит по ограничениям
     {
     AI->Tag = 1;
     exist_des=true;
     switch(type_sad)
           {
           case ZAD_1: if(Max<=b) {Max=b;num_extr=i;}
              break;
           case ZAD_2:if(Min>=t) {Min=t;num_extr=i;}
              break;
           case ZAD_3:if(Min>=v) {Min=v;num_extr=i;}
              break;
           case ZAD_4:C1=atof(opt_sadacha->c1.c_str());
                      C2=atof(opt_sadacha->c2.c_str());
                      C3=atof(opt_sadacha->c3.c_str());
                      Func_1=C1*b-C2*t-C3*v;
                      if(Func_1>Func) {Func=Func_1;num_extr=i;}
              break;
           case ZAD_5:C1=atof(opt_sadacha->c1.c_str());
                      C2=atof(opt_sadacha->c2.c_str());
                      C3=atof(opt_sadacha->c3.c_str());
                      Func_1=C1*(b-Bmax)/(Bmax-Bmin)+C2*(t-Tmax)/(Tmax-Tmin)+C3*(v-Vmax)/(Vmax-Vmin);
                      if(Func_1>Func) {Func=Func_1;i;}
              break;
           case ZAD_6:double l,k,m;
                      l=atof(opt_sadacha->c1.c_str());
                      k=atof(opt_sadacha->c2.c_str());
                      m=atof(opt_sadacha->c3.c_str());
                      if(t==0 || v==0)
                        {
						Application->MessageBox(_T("Деление на ноль при расчете значения критерия оптимальности!\nРешение неверное!"),
						  _T("Ошибка!"), MB_OK);
                        return;
                        }
					  Func_1=pow(b,l)/pow(t,k)/pow(v,m);
                      if(Func_1>Func) {Func=Func_1;num_extr=i;}

              break;
           }
      cnt_alt++;
      }
//      char_form->Table1->Next();
     }

//char_form->Table1->First();

if(exist_des==false)
  {
    f_OptB = "(нет)";
    f_OptT = "(нет)";
    f_OptV = "(нет)";
    f_Sostav = "(нет альтернатив,подходящих по ограничениям)";
    f_Cnt_alt = 0;
  }
else
  {
   AI = PA->Items[num_extr];

//отображаем оптимальное решение
 f_OptB = "[["+float_2_string(AI->A1_B_F,4)+
                   ","+float_2_string(AI->B_F1N,6)+
                   ","+float_2_string(AI->B_F1B,6)+
                   "],["+float_2_string(AI->A2_B_F,4)+
                   ","+float_2_string(AI->B_F2N,6)+
                   ","+float_2_string(AI->B_F2B,6)+
                   "],["+float_2_string(AI->A3_B_F,4)+
                   ","+float_2_string(AI->B_F3N,6)+
                   ","+float_2_string(AI->B_F3B,6)+
                   "]]";

         f_OptT = "[["+float_2_string(AI->A1_T_F,4)+
                   ","+float_2_string(AI->T_F1N,10)+
                   ","+float_2_string(AI->T_F1B,10)+
                   "],["+float_2_string(AI->A2_T_F,4)+
                   ","+float_2_string(AI->T_F2N,10)+
                   ","+float_2_string(AI->T_F2B,10)+
                   "],["+float_2_string(AI->A3_T_F,4)+
                   ","+float_2_string(AI->T_F3N,10)+
                   ","+float_2_string(AI->T_F3B,10)+
                   "]]";

         f_OptV = "[["+float_2_string(AI->A1_V_F,4)+
                   ","+float_2_string(AI->V_F1N,10)+
                   ","+float_2_string(AI->V_F1B,10)+
                   "],["+float_2_string(AI->A2_V_F,4)+
                   ","+float_2_string(AI->V_F2N,10)+
                   ","+float_2_string(AI->V_F2B,10)+
                   "],["+float_2_string(AI->A3_V_F,4)+
                   ","+float_2_string(AI->V_F3N,10)+
                   ","+float_2_string(AI->V_F3B,10)+
                   "]]";


    f_Sostav = AI->SOSTAV;
    f_Cnt_alt = cnt_alt;
 }

 f_CntComm = PA->Count;


}


void TZadacha::Nud_podgot()
{
  int m_indx;
  TBaseShape* B;
  TParamAlternative* PA;
  TPredicateTreeItem *TI;

  ozenk_t->Val[0] = ozenk_t_min(NULL);
  ozenk_v->Val[0] = ozenk_v_min(NULL);

  for (int i = CountPTI - 1 ; i >= 0 ; i--)
  {
     TI = PTI[i];
     for(int j = 0; j <= TI->Count - 1; j++)
     {
       B = TI->TFE[j];
       m_indx = TI->TFE_ID[j];
       ozenk_t->Val[m_indx] = ozenk_t_min(B);
       ozenk_v->Val[m_indx] = ozenk_v_min(B);
     }
  }
}



//--------------------------------------------------------------------------------------------------------


double  TZadacha::ozenk_t_min(TBaseShape* B)
{
  double t,Tmin;
  double t_n_f1n,t_n_f1b,t_n_f2n,t_n_f2b,t_n_f3n,t_n_f3b;
  //ищем экстремум , не учитывая те ПА, которые не подходят по ограничениям
  Tmin=100000000;
  if (B && B->ParamAlt)
  {
    TParamAlternative* PA = B->ParamAlt;
    for(int i = 0; i <= PA->Count - 1; i++)
    {
      TParamAlternativeItem* PAI = PA->Items[i];
      if(f_PartialDecision->Type_Char == PROP)
        t = PAI->T;
      else
      {
        t_n_f1n = PAI->T_F1N;
        t_n_f1b = PAI->T_F1B;
        t_n_f2n = PAI->T_F2N;
        t_n_f2b = PAI->T_F2B;
        t_n_f3n = PAI->T_F3N;
        t_n_f3b = PAI->T_F3B;
        t = (t_n_f1n+t_n_f1b+t_n_f2n+t_n_f2b+t_n_f3n+t_n_f3b)/6.0;
      }
      if( t< Tmin)
        Tmin=t;
    }
  }
  return Tmin;
}
//---------------------------------------------------------------------------



double  TZadacha::ozenk_v_min(TBaseShape* B)
{
  double v,Vmin;
  double v_n_f1n,v_n_f1b,v_n_f2n,v_n_f2b,v_n_f3n,v_n_f3b;
  //ищем экстремум , не учитывая те ПА, которые не подходят по ограничениям
  Vmin = 100000000;
  if (B && B->ParamAlt)
  {
    TParamAlternative* PA = B->ParamAlt;
    for(int i = 0; i <= PA->Count - 1; i++)
    {
      TParamAlternativeItem* PAI = PA->Items[i];
      if(f_PartialDecision->Type_Char == PROP)
        v = PAI->V;
      else
      {
        v_n_f1n = PAI->V_F1N;
        v_n_f1b = PAI->V_F1B;
        v_n_f2n = PAI->V_F2N;
        v_n_f2b = PAI->V_F2B;
        v_n_f3n = PAI->V_F3N;
        v_n_f3b = PAI->V_F3B;
        v = (v_n_f1n+v_n_f1b+v_n_f2n+v_n_f2b+v_n_f3n+v_n_f3b)/6.0;
      }
      if( v < Vmin)
        Vmin = v;
    }
  }
  return Vmin;
}

AnsiString TZadacha::Track()
{
   int m_type;
   AnsiString Res;
   TPredicateTreeItem *TI;
   TPredicateScannerItemKnot* Item;
   for(int i = 0; i <= CountPTI -1; i++ )
   {
     TI = PTI[i];
     Item =  new TPredicateScannerItemKnot;
     Item->ParentID = TI->ParentID;
     Item->NumAlt = TI->NumAlt;
     m_type = TI->TypeWorkShape;
     if (m_type == 12)
       m_type = 1;
     Item->TypeKnot = m_type;
     Item->TFE_ID1 = TI->TFE_ID[0];
     Item->TFE_ID2 = TI->TFE_ID[1];
     Item->TFE_ID3 = TI->TFE_ID[2];
     Res = Res + Item->ItemName() + "\r\n";
     delete Item;
   }
   return Res;
}

TPredicateTreeItem* TZadacha::FindToTree(TPredicateScannerItemKnot* AKnot)
{
   TPredicateTreeItem* Item;
   for(int i = 0; i <= f_Tree->Count - 1; i++)
   {
     Item = f_Tree->Items[i];
     if ((Item->ParentID == AKnot->ParentID) && (Item->NumAlt == AKnot->NumAlt) )
     {
        if( (AKnot->TypeKnot == Item->TypeWorkShape) ||
          ( (AKnot->TypeKnot == 1) && (Item->TypeWorkShape == 12)) )
        {
          if( ( AKnot->TFE_ID1 == Item->TFE_ID[0] ) &&
              ( AKnot->TFE_ID2 == Item->TFE_ID[1] ) &&
              ( AKnot->TFE_ID3 == Item->TFE_ID[2] ) )
            return Item;
        }
     }
   }
   return NULL;
}

TPredicateScannerItemKnot*  TZadacha::FindToScanner(TPredicateTreeItem* AItem)
{
   TPredicateScannerItemKnot* Knot;
   for(int i = 0; i <= Scanner->CountKnot - 1; i++)
   {
     Knot = Scanner->ItemsKnot[i];
     if ((AItem->ParentID == Knot->ParentID) && (AItem->NumAlt == Knot->NumAlt) )
     {
        if( (Knot->TypeKnot == AItem->TypeWorkShape) ||
          ( (Knot->TypeKnot == 1) && (AItem->TypeWorkShape == 12)) )
        {
          if( ( Knot->TFE_ID1 == AItem->TFE_ID[0] ) &&
              ( Knot->TFE_ID2 == AItem->TFE_ID[1] ) &&
              ( Knot->TFE_ID3 == AItem->TFE_ID[2] ) )
            return Knot;
        }
     }
   }
   return NULL;
}


AnsiString TZadacha::DoCheckEqualTree()
{
   AnsiString Error = "";
   TPredicateTreeItem* TI;
   TPredicateScannerItemKnot* Knot;
   for(int i = 0; i <= Scanner->CountKnot - 1; i++)
   {
      Knot = Scanner->ItemsKnot[i];
      if(!FindToTree(Knot))
      {
        Error = "Предикат: " + Knot->ItemName() + "  не найден!";
        break;
      }
   }

   if (Error.Length() == 0)
   {
     for(int i = 0; i <= f_Tree->Count - 1; i++)
     {
       TI = f_Tree->Items[i];
       if(!FindToScanner(TI))
       {
         Knot =  new TPredicateScannerItemKnot;
         Knot->ParentID = TI->ParentID;
         Knot->NumAlt = TI->NumAlt;
         int m_type = TI->TypeWorkShape;
         if (m_type == 12)
           m_type = 1;
         Knot->TypeKnot = m_type;
         Knot->TFE_ID1 = TI->TFE_ID[0];
         Knot->TFE_ID2 = TI->TFE_ID[1];
         Knot->TFE_ID3 = TI->TFE_ID[2];
         Error = "Не найден предикат: " + Knot->ItemName();
         delete Knot;
         break;
       }
     }
   }
   return Error;
}

AnsiString TZadacha::DoCheckLogicItemUP(TPredicateScannerItemKnot* AKnot, int AID)
{
  AnsiString Error = "";
  TPredicateScannerItemKnot* Item;
  for(int i = 0; i <= Scanner->CountKnot - 1; i++)
  {
    Item = Scanner->ItemsKnot[i];
    if(Item == AKnot)
      break;

    if (Item->ParentID == AID)
    {
      Error = "В предикате: " + AKnot->ItemName() + " решение для ТФЕ = "
        + IntToStr(AID) + " не может быть найдено!";
      break;
    }
  }
  return Error;
}

AnsiString TZadacha::DoCheckLogicItemDown(TPredicateScannerItemKnot* AKnot, int AID)
{
  int s_cnt = Scanner->CountKnot;
  AnsiString Error = "";
  TPredicateScannerItemKnot* Item;
  for(int i = 0; i <= s_cnt - 1; i++)
  {
    Item = Scanner->ItemsKnot[i];
    if(Item == AKnot)
    {
      for(int j = i + 1; j <= s_cnt - 1; j++)
      {
        Item = Scanner->ItemsKnot[j];
        if (Item->ParentID == AID)
          return  Error;
      }
    }
  }
  Error = "В предикате: " + AKnot->ItemName() + " решение для ТФЕ = "
    + IntToStr(AID) + " не может быть найдено!";
  return Error;
}


AnsiString TZadacha::DoCheckLogic()
{
  int id1, id2, id3;
  AnsiString Error = "";
  TPredicateScannerItemKnot* Knot;
  for(int i = 0; i <= Scanner->CountKnot - 1; i++)
  {
    Knot = Scanner->ItemsKnot[i];
    id1 = Knot->TFE_ID1;
    id2 = Knot->TFE_ID2;
    id3 = Knot->TFE_ID3;
    if(id1 != 0)
    {
      Error = DoCheckLogicItemUP(Knot, id1);
      if ( (Error.Length() == 0) & (id1 < 0) )
        Error = DoCheckLogicItemDown(Knot, id1);
      if (Error.Length())
        return Error;
    }

    if(id2 != 0)
    {
      Error = DoCheckLogicItemUP(Knot, id2);
      if ( (Error.Length() == 0) & (id2 < 0) )
        Error = DoCheckLogicItemDown(Knot, id2);
      if (Error.Length())
        return Error;
    }

    if(id3 != 0)
    {
      Error = DoCheckLogicItemUP(Knot, id3);
      if ( (Error.Length() == 0) & (id3 < 0) )
        Error = DoCheckLogicItemDown(Knot, id3);
      if (Error.Length())
        return Error;
    }
  }
  return Error;
}



AnsiString TZadacha::CheckTrack()
{
   AnsiString Res = "";
   Res = DoCheckEqualTree();
   if(!Res.Length())
     Res = DoCheckLogic();
   return Res;
}

AnsiString TZadacha::AcceptTrackFromScanner()
{
   AnsiString Err = "";
   TPredicateTreeItem* TI;
   TPredicateScannerItemKnot* Knot;
   Err = CheckTrack();
   if(!Err.Length())
   {
      ClearPTI();
      for(int i = 0; i <= Scanner->CountKnot - 1; i++)
      {
        Knot = Scanner->ItemsKnot[i];
        TI = FindToTree(Knot);
        AddPTI(TI);
      }
   }
   return Err;
}

void TZadacha::LoadPredicateTrackCreatorItem(TPredicateTrackCreatorItem* AItem)
{
  TPredicateTreeItem* TI;
  TPredicateScannerItemKnot* Knot;
  if (AItem)
  {
    ClearPTI();
    for(int i = 0; i <= AItem->Count - 1; i++)
    {
      Knot = AItem->Items[i];
      TI = FindToTree(Knot);
      AddPTI(TI);
    }
  }
}

bool TZadacha::CheckOzenk_TFE_v(TPredicateTreeItem* ATI, double AValue)
{
  int num_parent;
  double v1, v2, v_parent;
  TPredicateTreeItem *TI;
  if (!ATI)
    return false;// При оценке алгоритма с указанием проверки на НУД, просто тихо сваливаем

  for (int i = CountPTI - 1 ; i >= 0 ; i--)
  {
    TI = PTI[i];
    num_parent = TI->ParentID;
    if (TI == ATI)
      ozenk_v->Items[1][num_parent] = AValue;
    else
    {
      v1 = Get_V_Min(TI, 0);
      v2 = Get_V_Min(TI, 1);
      v_parent = ozenk_v->Items[1][num_parent]; //bbb
      switch(TI->TypeWorkShape)
      {
        case RAB:
        case RAB_FAKE:
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, v1);
		  break;
		case RAB_POSL:
		case RAB_2par_AND:
		case RAB_2par_OR:
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, (v1 + v2));
		  break;
		case DIAGN:
		case DIAGN_2:
		case PROV_IF:
		case WHILE_DO:
		case WHILE_DO_2:
		case DO_UNTIL:
		case DO_UNTIL_2:
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, (v1 + v2));
		  break;
		case RASV:
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, std::min(v1, v2));
		  break;
		case DO_WHILE_DO:
		case DO_WHILE_DO_2:
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, (v1 + v2));
		  break;
		case RASV_SIM:
		  double temp = v1;
		  TBaseShape *B = TI->TFE[2];
		  if (B && B->ParamAlt)
		  {
			if (!B->ParamAlt->Items[0]->CheckPLG)
			  temp = v2;
		  }
		  ozenk_v->Items[1][num_parent] = std::min(v_parent, temp);
		  break;

	  }
	}
  }
  return ozenk_v->Items[1][num_parent] > f_VMax;
}


bool TZadacha::CheckOzenk_TFE_t(TPredicateTreeItem* ATI, double AValue)
{
  int num_parent;
  double t1, t2, t_parent;
  TPredicateTreeItem *TI;
  if (!ATI)
    return false;// При оценке алгоритма с указанием проверки на НУД, просто тихо сваливаем

  for (int i = CountPTI - 1 ; i >= 0 ; i--)
  {
    TI = PTI[i];
    num_parent = TI->ParentID;
    if (TI == ATI)
      ozenk_t->Items[1][num_parent] = AValue;
    else
    {
      t1 = Get_T_Min(TI, 0);
      t2 = Get_T_Min(TI, 1);
      t_parent = ozenk_t->Items[1][num_parent]; //aaa

      switch(TI->TypeWorkShape)
      {
        case RAB:
        case RAB_FAKE:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, t1);
		  break;
		case RAB_POSL:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, (t1 + t2));
		  break;
		case RAB_2par_AND:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, std::max(t1, t2));
		  break;
		case RAB_2par_OR:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, std::min(t1, t2));
		  break;
        case DIAGN:
        case DIAGN_2:
        case PROV_IF:
        case WHILE_DO:
        case WHILE_DO_2:
        case DO_UNTIL:
        case DO_UNTIL_2:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, (t1 + t2));
		  break;

		case RASV:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, std::min(t1, t2));
		  break;

		case DO_WHILE_DO:
		case DO_WHILE_DO_2:
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, (t1 + t2));
		  break;

		case RASV_SIM:
		  double temp = t1;
		  TBaseShape *B = TI->TFE[2];
		  if (B && B->ParamAlt)
		  {
			if (!B->ParamAlt->Items[0]->CheckPLG)
			  temp = t2;
		  }
		  ozenk_t->Items[1][num_parent] = std::min(t_parent, temp);
		  break;
	  }
	}
  }
  return ozenk_t->Items[1][num_parent] > f_TMax;
}

double TZadacha::Get_V_Min(TPredicateTreeItem* ATI, int AIndex)
{
  int idx = ATI->TFE_ID[AIndex];
  if (idx == 0)
    return  100000000.0;
  if (idx  <  0)
    return ozenk_v->Items[1][idx]; //bbb
  double v1 = ozenk_v->Items[1][idx]; //bbb
  double v2 = ozenk_v->Val[idx]; //bbb
  return std::min(v1, v2);
}

double TZadacha::Get_T_Min(TPredicateTreeItem* ATI, int AIndex)
{
  int idx = ATI->TFE_ID[AIndex];
  if (idx == 0)
    return  100000000.0;
  if (idx  <  0)
    return ozenk_t->Items[1][idx]; //aaa
  double t1 = ozenk_t->Items[1][idx]; //aaa
  double t2 = ozenk_t->Val[idx]; //aaa
  return std::min(t1, t2);
}

void TZadacha::Ozenk_TFEStill(double &AOzenk0, double &AOzenk1)
{
  TPredicateTreeItem *TI;
  TOzenkTFE* mOzenk = new TOzenkTFE(f_PartialDecision);
  for (int i = CountPTI - 1; i >= 0 ; i--)
  {
	TI = PTI[i];
	mOzenk->AddPredicateTree(TI);
  }
  mOzenk->InitMassiv();
  mOzenk->Ozenk();
  AOzenk0 = mOzenk->ValueOzenk(0);
  AOzenk1 = mOzenk->ValueOzenk1(0);
  delete mOzenk;
}

void TZadacha::Ozenk_TFE()
{
  double m0, m1;
  Ozenk_TFEStill(m0, m1);
  ShowOzenk(float_2_string(m0, 10), float_2_string(m1, 10));
}

bool TZadacha::PtiToOgrSovm(TPredicateTreeItem* APTI)
{
  int id1, id2;
  bool res = false;
  TPredicateTreeItem *P, *N;
  TDynamicArray *m_Stack = new TDynamicArray;
  m_Stack->InsertToFirst(APTI);
  P = static_cast<TPredicateTreeItem*>(m_Stack->Pop());
  while(P)
  {
    if ( P->TypeWorkShape ==  12 ) //укрупненная РО
    {
      N = f_Tree->FindByParentID(P->TFE_ID[0]);
      m_Stack->InsertToFirst(N);
    }
    if ( P->TypeWorkShape ==  13 ) // последовательная РО
    {
      id1 = P->TFE_ID[0];
      id2 = P->TFE_ID[1];
      if (id1 > 0)
      {
        res = FOgrSovmArray->IsContainsKnot(id1, 0, 0);
        if (res)
          break;
      }
      else
      {
        N = f_Tree->FindByParentID(id1);
        m_Stack->InsertToFirst(N);
      }
      if (id2 > 0)
      {
        res = FOgrSovmArray->IsContainsKnot(id2, 0, 0);
        if (res)
          break;
      }
      else
      {
        N = f_Tree->FindByParentID(id2);
        m_Stack->InsertToFirst(N);
      }  
    }
    if (P->BaseWorkShape)
    {
      res = FOgrSovmArray->IsContainsTFS(P->BaseWorkShape);
      if (res)
        break;
    }
    P = static_cast<TPredicateTreeItem*>(m_Stack->Pop());
  }
  delete m_Stack;
  return res;
}

TPredicateTreeItem* TZadacha::FindUpperNodeForOgrSovm()
{
  TPredicateTreeItem* Res = NULL;
  TPredicateTreeItem *TI;
  int cnt = CountPTI;
  if (cnt > 0)
  {
    TI = PTI[0];
    if ( PtiToOgrSovm(TI) )
    {
      Res = TI;
      for (int i = 0; i <= cnt - 1; i++)
      {
        TI = PTI[i];
        if ( PtiToOgrSovm(TI) )
        {
          Res = TI;
          if (Res->TypeWorkShape == 13)
          {
            int stp = 0;
            int id1 = Res->TFE_ID[0];
            int id2 = Res->TFE_ID[1];

            if (id1 > 0)
            {
              if ( FOgrSovmArray->IsContainsKnot(id1, 0, 0) )
               stp++;
            }
            else
            {
              TI = f_Tree->FindByParentID(id1);
              if ( PtiToOgrSovm(TI) )
                stp++;
            }

            if (id2 > 0)
            {
              if ( FOgrSovmArray->IsContainsKnot(id2, 0, 0) )
               stp++;
            }
            else
            {
              TI = f_Tree->FindByParentID(id2);
              if ( PtiToOgrSovm(TI) )
                stp++;
            }
            
            if ( stp == 2 )
              break;
          }
          if (Res->BaseWorkShape)
            break;
        }
      }
    }
  }
  return Res;
}



