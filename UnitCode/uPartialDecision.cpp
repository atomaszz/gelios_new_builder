//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPartialDecision.h"
#include "uCommonGraph.h"
#include "uIMRIncl_all.h"
#include "opim_f.h"
#include "uCommonCalc.h"
#include "uZadacha.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
const int StrMemSize = 5119;

struct PARAM {
  double par[12];
  double par_fuz[13][9];
  char stv[StrMemSize + 1];
  double sovm;
  double sovm0;
  double sovm1;
};


void CopyAlternateParam(TPartialDecisionItem* ADest, TPartialDecisionItem* ASource)
{
   TParamAlternative* S =  ASource->ParamAlt;
   TParamAlternative* D =  ADest->ParamAlt;
   TParamAlternativeItem *OI;
   for(int i = S->Count - 1; i >= 0 ; i--)
   {
      OI = S->Items[i];
      D->AddItem(OI->Clone());
      S->Delete2(OI);
   }
}

void CopyAlternateParam2(TParamAlternative* ADest, TParamAlternative* ASource, bool AByPassGPL)
{
   if (ADest && ASource)
   {
     TParamAlternativeItem *OI;
     for(int i = 0; i <= ASource->Count - 1; i++)
     {
        OI = ASource->Items[i];
        if (AByPassGPL || OI->CheckPLG)
          ADest->AddItem(OI->Clone());
     }
   }
}


//----------------- TPartialDecisionItem -------------------------------------------------
TPartialDecisionItem::TPartialDecisionItem(TPartialDecision *AParent)
{
  f_Apd = NULL;
  f_WorkItem = NULL;
  f_Parent = AParent;
  f_ParamAlt = new TParamAlternative;
}

TPartialDecisionItem::~TPartialDecisionItem()
{
  delete f_ParamAlt;
  FreeApd();
}

void TPartialDecisionItem::FreeApd()
{
   if (f_Apd)
   {
     delete f_Apd;
     f_Apd = NULL;
   }
}

TParamAlternative* TPartialDecisionItem::GetParamAlternativeByID(int AID)
{
   TBaseShape* B;
   TPartialDecisionItem* PDI;
   if (AID > 0)
   {
      for(int i = 0; i <= f_WorkItem->Count - 1; i++)
      {
         B = f_WorkItem->TFE[i];
         if (B && (B->ID == AID) )
         {
            FreeApd();
            f_Apd = new TParamAlternative;
             CopyAlternateParam2(f_Apd, B->ParamAlt, B->TypeShape == 8);
              
            PDI = f_Parent->FindPartialDecisionItemByParentID(AID);
            if (PDI)
              CopyAlternateParam2(f_Apd, PDI->ParamAlt, false);
            return f_Apd;
         }

      }
   }
   else
   {
      PDI = f_Parent->FindPartialDecisionItemByParentID(AID);
      return PDI->ParamAlt;
   }
   return NULL;
}


void  TPartialDecisionItem::DoDecision()
{
  struct PARAM  *param1, *param2, *param3, *param_rez; //для результирующих параметров
  TParamAlternativeItem *AI;

  int i1,i2,i3,i_rez; //количество альтернатив
  int n1,n2,n3,n_rez; //номера подблоков
  double s_b,s_t,s_v, s_k11,s_k00,s_tf,s_vf,s_p11,s_p00,s_td,s_vd, s_diagn_el,
    a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
    a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
    a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
    a1_k11_f, k11_f1n, k11_f1b, a2_k11_f, k11_f2n, k11_f2b, a3_k11_f, k11_f3n, k11_f3b,
    a1_k00_f, k00_f1n, k00_f1b, a2_k00_f, k00_f2n, k00_f2b, a3_k00_f, k00_f3n, k00_f3b,
    a1_tf_f, tf_f1n, tf_f1b, a2_tf_f, tf_f2n, tf_f2b, a3_tf_f, tf_f3n, tf_f3b,
    a1_vf_f, vf_f1n, vf_f1b, a2_vf_f, vf_f2n, vf_f2b, a3_vf_f, vf_f3n, vf_f3b,
    a1_p11_f, p11_f1n, p11_f1b, a2_p11_f, p11_f2n, p11_f2b, a3_p11_f, p11_f3n, p11_f3b,
    a1_p00_f, p00_f1n, p00_f1b, a2_p00_f, p00_f2n, p00_f2b, a3_p00_f, p00_f3n, p00_f3b,
    a1_td_f, td_f1n, td_f1b,a2_td_f, td_f2n, td_f2b, a3_td_f, td_f3n, td_f3b,
    a1_vd_f, vd_f1n, vd_f1b, a2_vd_f, vd_f2n, vd_f2b, a3_vd_f, vd_f3n, vd_f3b,
    a1_p_el_f, p_el_f1n, p_el_f1b, a2_p_el_f, p_el_f2n, p_el_f2b, a3_p_el_f, p_el_f3n, p_el_f3b,
    sovmest,sovmest0,sovmest1;
  AnsiString s_name,s_el,s_func, s_predicat, add_name, sostav;

  param1 = NULL;
  param2 = NULL;
  param3 = NULL;
  param_rez = NULL;
  i1 = 0;
  i2 = 0;
  i3 = 0;
  i_rez = 0;
  int type, work_type = f_WorkItem->TypeWorkShape;

  TParamAlternative* PA;
  n_rez = f_WorkItem->Count;
  n1 = f_WorkItem->TFE_ID[i_rez];
  //pull
  PA = GetParamAlternativeByID(n1);
  i1 = PA->Count;
  param1 = (struct PARAM *)malloc(sizeof(struct PARAM)*i1);
  memset(param1, 0, sizeof(struct PARAM)*i1);
  for (int i = 0; i <= i1 - 1; i++)
  {
    AI = PA->Items[i];
    param1[i].par[0] = AI->B;
    param1[i].par[1] = AI->T;
    param1[i].par[2] = AI->V;
    param1[i].par_fuz[0][0] = AI->A1_B_F;
    param1[i].par_fuz[0][1] = AI->B_F1N;
    param1[i].par_fuz[0][2] = AI->B_F1B;
    param1[i].par_fuz[0][3] = AI->A2_B_F;
    param1[i].par_fuz[0][4] = AI->B_F2N;
    param1[i].par_fuz[0][5] = AI->B_F2B;
    param1[i].par_fuz[0][6] = AI->A3_B_F;
    param1[i].par_fuz[0][7] = AI->B_F3N;
    param1[i].par_fuz[0][8] = AI->B_F3B;

    param1[i].par_fuz[1][0] = AI->A1_T_F;
    param1[i].par_fuz[1][1] = AI->T_F1N;
    param1[i].par_fuz[1][2] = AI->T_F1B;
    param1[i].par_fuz[1][3] = AI->A2_T_F;
    param1[i].par_fuz[1][4] = AI->T_F2N;
    param1[i].par_fuz[1][5] = AI->T_F2B;
    param1[i].par_fuz[1][6] = AI->A3_T_F;
    param1[i].par_fuz[1][7] = AI->T_F3N;
    param1[i].par_fuz[1][8] = AI->T_F3B;

    param1[i].par_fuz[2][0] = AI->A1_V_F;
    param1[i].par_fuz[2][1] = AI->V_F1N;
    param1[i].par_fuz[2][2] = AI->V_F1B;
    param1[i].par_fuz[2][3] = AI->A2_V_F;
    param1[i].par_fuz[2][4] = AI->V_F2N;
    param1[i].par_fuz[2][5] = AI->V_F2B;
    param1[i].par_fuz[2][6] = AI->A3_V_F;
    param1[i].par_fuz[2][7] = AI->V_F3N;
    param1[i].par_fuz[2][8] = AI->V_F3B;

    StrLCopy(param1[i].stv, AI->SOSTAV.c_str(), StrMemSize);
    param1[i].stv[StrMemSize] = '\0';
    param1[i].sovm = AI->SOVM;
    param1[i].sovm0 = AI->SOVM0;
    param1[i].sovm1 = AI->SOVM1;
  }
  i_rez++;

  if(n_rez >= 2)
  {
    n2 = f_WorkItem->TFE_ID[i_rez];
    type = 5;
    if( f_WorkItem->TFE[i_rez] )
      type =  f_WorkItem->TFE[i_rez]->TypeShape;
    if (type == 5)
    {
      PA = GetParamAlternativeByID(n2);
      i2 = PA->Count;
      param2 = (struct PARAM *)malloc(sizeof(struct PARAM)*i2);
      memset(param2, 0, sizeof(struct PARAM)*i2);
      for (int i = 0; i <= i2 - 1; i++)
      {
        AI = PA->Items[i];
        param2[i].par[0] = AI->B;
        param2[i].par[1] = AI->T;
        param2[i].par[2] = AI->V;
        param2[i].par_fuz[0][0] = AI->A1_B_F;
        param2[i].par_fuz[0][1] = AI->B_F1N;
        param2[i].par_fuz[0][2] = AI->B_F1B;
        param2[i].par_fuz[0][3] = AI->A2_B_F;
        param2[i].par_fuz[0][4] = AI->B_F2N;
        param2[i].par_fuz[0][5] = AI->B_F2B;
        param2[i].par_fuz[0][6] = AI->A3_B_F;
        param2[i].par_fuz[0][7] = AI->B_F3N;
        param2[i].par_fuz[0][8] = AI->B_F3B;

        param2[i].par_fuz[1][0] = AI->A1_T_F;
        param2[i].par_fuz[1][1] = AI->T_F1N;
        param2[i].par_fuz[1][2] = AI->T_F1B;
        param2[i].par_fuz[1][3] = AI->A2_T_F;
        param2[i].par_fuz[1][4] = AI->T_F2N;
        param2[i].par_fuz[1][5] = AI->T_F2B;
        param2[i].par_fuz[1][6] = AI->A3_T_F;
        param2[i].par_fuz[1][7] = AI->T_F3N;
        param2[i].par_fuz[1][8] = AI->T_F3B;

        param2[i].par_fuz[2][0] = AI->A1_V_F;
        param2[i].par_fuz[2][1] = AI->V_F1N;
        param2[i].par_fuz[2][2] = AI->V_F1B;
        param2[i].par_fuz[2][3] = AI->A2_V_F;
        param2[i].par_fuz[2][4] = AI->V_F2N;
        param2[i].par_fuz[2][5] = AI->V_F2B;
        param2[i].par_fuz[2][6] = AI->A3_V_F;
        param2[i].par_fuz[2][7] = AI->V_F3N;
        param2[i].par_fuz[2][8] = AI->V_F3B;

        StrLCopy(param2[i].stv, AI->SOSTAV.c_str(), StrMemSize);
        param2[i].stv[StrMemSize] = '\0';
        param2[i].sovm = AI->SOVM;
        param2[i].sovm0 = AI->SOVM0;
        param2[i].sovm1 = AI->SOVM1;

      }
      i_rez++;
    }
  }


  if (n_rez >= 2)
  {
    n3 = f_WorkItem->TFE_ID[i_rez];
    type = 5;
    if( f_WorkItem->TFE[i_rez] )
      type =  f_WorkItem->TFE[i_rez]->TypeShape;
    if (type != 5)
    {
      PA = GetParamAlternativeByID(n3);
      i3 = PA->Count;
      param3 = (struct PARAM *)malloc(sizeof(struct PARAM)*i3);
      memset(param3, 0, sizeof(struct PARAM)*i3);
      for (int i = 0; i <= i3 - 1; i++)
      {
        AI = PA->Items[i];

        param3[i].par[3] = AI->P_11;
        param3[i].par[4] = AI->P_00;
        param3[i].par[5] = AI->T_D;
        param3[i].par[6] = AI->V_D;
        param3[i].par[7] = AI->P_DIAGN_EL;
        param3[i].par[8] = AI->K_11;
        param3[i].par[9] = AI->K_00;
        param3[i].par[10] = AI->T_F;
        param3[i].par[11] = AI->V_F;

        param3[i].par_fuz[3][0] = AI->A1_P11_F;
        param3[i].par_fuz[3][1] = AI->P11_F1N;
        param3[i].par_fuz[3][2] = AI->P11_F1B;
        param3[i].par_fuz[3][3] = AI->A2_P11_F;
        param3[i].par_fuz[3][4] = AI->P11_F2N;
        param3[i].par_fuz[3][5] = AI->P11_F2B;
        param3[i].par_fuz[3][6] = AI->A3_P11_F;
        param3[i].par_fuz[3][7] = AI->P11_F3N;
        param3[i].par_fuz[3][8] = AI->P11_F3B;

        param3[i].par_fuz[4][0] = AI->A1_P00_F;
        param3[i].par_fuz[4][1] = AI->P00_F1N;
        param3[i].par_fuz[4][2] = AI->P00_F1B;
        param3[i].par_fuz[4][3] = AI->A2_P00_F;
        param3[i].par_fuz[4][4] = AI->P00_F2N;
        param3[i].par_fuz[4][5] = AI->P00_F2B;
        param3[i].par_fuz[4][6] = AI->A3_P00_F;
        param3[i].par_fuz[4][7] = AI->P00_F3N;
        param3[i].par_fuz[4][8] = AI->P00_F3B;

        param3[i].par_fuz[5][0] = AI->A1_TD_F;
        param3[i].par_fuz[5][1] = AI->TD_F1N;
        param3[i].par_fuz[5][2] = AI->TD_F1B;
        param3[i].par_fuz[5][3] = AI->A2_TD_F;
        param3[i].par_fuz[5][4] = AI->TD_F2N;
        param3[i].par_fuz[5][5] = AI->TD_F2B;
        param3[i].par_fuz[5][6] = AI->A3_TD_F;
        param3[i].par_fuz[5][7] = AI->TD_F3N;
        param3[i].par_fuz[5][8] = AI->TD_F3B;

        param3[i].par_fuz[6][0] = AI->A1_VD_F;
        param3[i].par_fuz[6][1] = AI->VD_F1N;
        param3[i].par_fuz[6][2] = AI->VD_F1B;
        param3[i].par_fuz[6][3] = AI->A2_VD_F;
        param3[i].par_fuz[6][4] = AI->VD_F2N;
        param3[i].par_fuz[6][5] = AI->VD_F2B;
        param3[i].par_fuz[6][6] = AI->A3_VD_F;
        param3[i].par_fuz[6][7] = AI->VD_F3N;
        param3[i].par_fuz[6][8] = AI->VD_F3B;

        param3[i].par_fuz[7][0] = AI->A1_P_EL_F;
        param3[i].par_fuz[7][1] = AI->P_EL_F1N;
        param3[i].par_fuz[7][2] = AI->P_EL_F1B;
        param3[i].par_fuz[7][3] = AI->A2_P_EL_F;
        param3[i].par_fuz[7][4] = AI->P_EL_F2N;
        param3[i].par_fuz[7][5] = AI->P_EL_F2B;
        param3[i].par_fuz[7][6] = AI->A3_P_EL_F;
        param3[i].par_fuz[7][7] = AI->P_EL_F3N;
        param3[i].par_fuz[7][8] = AI->P_EL_F3B;

        param3[i].par_fuz[8][0] = AI->A1_K11_F;
        param3[i].par_fuz[8][1] = AI->K11_F1N;
        param3[i].par_fuz[8][2] = AI->K11_F1B;
        param3[i].par_fuz[8][3] = AI->A2_K11_F;
        param3[i].par_fuz[8][4] = AI->K11_F2N;
        param3[i].par_fuz[8][5] = AI->K11_F2B;
        param3[i].par_fuz[8][6] = AI->A3_K11_F;
        param3[i].par_fuz[8][7] = AI->K11_F3N;
        param3[i].par_fuz[8][8] = AI->K11_F3B;

        param3[i].par_fuz[9][0] = AI->A1_K00_F;
        param3[i].par_fuz[9][1] = AI->K00_F1N;
        param3[i].par_fuz[9][2] = AI->K00_F1B;
        param3[i].par_fuz[9][3] = AI->A2_K00_F;
        param3[i].par_fuz[9][4] = AI->K00_F2N;
        param3[i].par_fuz[9][5] = AI->K00_F2B;
        param3[i].par_fuz[9][6] = AI->A3_K00_F;
        param3[i].par_fuz[9][7] = AI->K00_F3N;
        param3[i].par_fuz[9][8] = AI->K00_F3B;

        param3[i].par_fuz[10][0] = AI->A1_TF_F;
        param3[i].par_fuz[10][1] = AI->TF_F1N;
        param3[i].par_fuz[10][2] = AI->TF_F1B;
        param3[i].par_fuz[10][3] = AI->A2_TF_F;
        param3[i].par_fuz[10][4] = AI->TF_F2N;
        param3[i].par_fuz[10][5] = AI->TF_F2B;
        param3[i].par_fuz[10][6] = AI->A3_TF_F;
        param3[i].par_fuz[10][7] = AI->TF_F3N;
        param3[i].par_fuz[10][8] = AI->TF_F3B;

        param3[i].par_fuz[11][0] = AI->A1_VF_F;
        param3[i].par_fuz[11][1] = AI->VF_F1N;
        param3[i].par_fuz[11][2] = AI->VF_F1B;
        param3[i].par_fuz[11][3] = AI->A2_VF_F;
        param3[i].par_fuz[11][4] = AI->VF_F2N;
        param3[i].par_fuz[11][5] = AI->VF_F2B;
        param3[i].par_fuz[11][6] = AI->A3_VF_F;
        param3[i].par_fuz[11][7] = AI->VF_F3N;
        param3[i].par_fuz[11][8] = AI->VF_F3B;
  //      strcpy(s_predicat.c_str(), AI->PREDICAT.c_str());
        if (AI->CheckPLG)
          s_predicat = "1";
        else
          s_predicat = "0";
        StrLCopy(param3[i].stv, AI->SOSTAV.c_str(), StrMemSize);
        param3[i].stv[StrMemSize]='\0';
        param3[i].sovm = AI->SOVM;
        param3[i].sovm0 = AI->SOVM0;
        param3[i].sovm1 = AI->SOVM1;
      }
    }
  }


////////////////////

int r = 0;
if (i2 == 0)
i2 = 1;
if (i3 == 0)
{
  i3 = 1;
//  param3 = param2;
}

i_rez = i1*i2*i3;
param_rez=(struct PARAM *)malloc(sizeof(struct PARAM)*i_rez);

   for(int k = 0; k < i1; k++)
       for(int n = 0; n < i2; n++)
         for(int h = 0; h < i3; h++)
         {

             type = 5;
             s_name=(AnsiString)"(нет названия)";
             s_func=(AnsiString)"(нет функции)";
             s_el=(AnsiString)"(нет элемента)";


         switch(work_type)
         {

//расчитываем параметры
//и альтернативы результата добавляем в таблицу как альтернативы подблока-родителя
         case 1:
                  //расчитываем параметры для блока РАБОЧАЯ
                  if(f_Parent->Type_Char == PROP)
                           calc_RAB(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                           &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                           calc_RAB_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);
                  //добавляем в таблицу новую альтернативу
                    if(f_Parent->Type_Char == PROP)
                  {s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2]; }
                  else {s_b=1;
                        s_t=0;
                        s_v=0;}
                 // add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0];
                  b_f1n=param_rez[r].par_fuz[0][1];
                  b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3];
                  b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];


                  sostav=param1[k].stv;
                  f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                     s_b,s_t,s_v,
                                     1,1,0,0,1,1,0,0,
                                     "(нет элемента)",1,
                                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                     0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                     0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                     0,0,0,0.5,0,0,1,0,0,
                                     "(нет условия)",sovmest,sovmest0,sovmest1) );
                   break;


         case 12:
                  //расчитываем параметры для блока РАБОЧАЯ
                  if(f_Parent->Type_Char == PROP)
                           calc_RAB(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                           &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                           calc_RAB_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);
                  //добавляем в таблицу новую альтернативу
                    if(f_Parent->Type_Char == PROP)
                  {s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2]; }
                  else {s_b=1;
                        s_t=0;
                        s_v=0;}
                 // add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0];
                  b_f1n=param_rez[r].par_fuz[0][1];
                  b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3];
                  b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];


                  sostav=param1[k].stv;
                  f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                     s_b,s_t,s_v,
                                     1,1,0,0,1,1,0,0,
                                     "(нет элемента)",1,
                                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                     0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                     0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                     0,0,0,0.5,0,0,1,0,0,
                                     "(нет условия)",sovmest,sovmest0,sovmest1) );
                   break;

         case 13://расчитываем параметры для блока РАБОЧАЯ ПОСЛЕД.
                  if(f_Parent->Type_Char == PROP)
                     calc_RAB_2(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                param2[n].par[0],param2[n].par[1],param2[n].par[2],
                                &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else {
                        calc_RAB_2_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param2[n].par_fuz[0][0],param2[n].par_fuz[0][1],param2[n].par_fuz[0][2],
                           param2[n].par_fuz[0][3],param2[n].par_fuz[0][4],param2[n].par_fuz[0][5],
                           param2[n].par_fuz[0][6],param2[n].par_fuz[0][7],param2[n].par_fuz[0][8],
                           param2[n].par_fuz[1][0],param2[n].par_fuz[1][1],param2[n].par_fuz[1][2],
                           param2[n].par_fuz[1][3],param2[n].par_fuz[1][4],param2[n].par_fuz[1][5],
                           param2[n].par_fuz[1][6],param2[n].par_fuz[1][7],param2[n].par_fuz[1][8],
                           param2[n].par_fuz[2][0],param2[n].par_fuz[2][1],param2[n].par_fuz[2][2],
                           param2[n].par_fuz[2][3],param2[n].par_fuz[2][4],param2[n].par_fuz[2][5],
                           param2[n].par_fuz[2][6],param2[n].par_fuz[2][7],param2[n].par_fuz[2][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);
                                               }
                   if(f_Parent->Type_Char == PROP)
                  {s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2]; }
                  else {s_b=1;
                        s_t=0;
                        s_v=0;}
//  add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
         // s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];

                   sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param2[n].stv;

                    f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                         s_b,s_t,s_v,
                                         1,1,0,0,1,1,0,0,
                                         "(нет элемента)",1,
                                         a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                         a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                         a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                         0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                         0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                         0,0,0,0.5,0,0,1,0,0,
                                         "(нет условия)",sovmest,sovmest0,sovmest1));
                     break;

         case 2://расчитываем параметры для блока РАБОЧАЯ ПАРАЛ И.
                  if(f_Parent->Type_Char == PROP)
                        calc_RAB_2par_AND(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param2[n].par[0],param2[n].par[1],param2[n].par[2],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                        calc_RAB_2par_AND_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param2[n].par_fuz[0][0],param2[n].par_fuz[0][1],param2[n].par_fuz[0][2],
                           param2[n].par_fuz[0][3],param2[n].par_fuz[0][4],param2[n].par_fuz[0][5],
                           param2[n].par_fuz[0][6],param2[n].par_fuz[0][7],param2[n].par_fuz[0][8],
                           param2[n].par_fuz[1][0],param2[n].par_fuz[1][1],param2[n].par_fuz[1][2],
                           param2[n].par_fuz[1][3],param2[n].par_fuz[1][4],param2[n].par_fuz[1][5],
                           param2[n].par_fuz[1][6],param2[n].par_fuz[1][7],param2[n].par_fuz[1][8],
                           param2[n].par_fuz[2][0],param2[n].par_fuz[2][1],param2[n].par_fuz[2][2],
                           param2[n].par_fuz[2][3],param2[n].par_fuz[2][4],param2[n].par_fuz[2][5],
                           param2[n].par_fuz[2][6],param2[n].par_fuz[2][7],param2[n].par_fuz[2][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
// add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];


                          sostav = param1[k].stv+(AnsiString)";"+(AnsiString)param2[n].stv;


                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));
                        break;
         case 3://расчитываем параметры для блока РАБОЧАЯ ПАРАЛ ИЛИ.
                  if(f_Parent->Type_Char == PROP)
                          calc_RAB_2par_OR(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param2[n].par[0],param2[n].par[1],param2[n].par[2],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                         calc_RAB_2par_OR_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param2[n].par_fuz[0][0],param2[n].par_fuz[0][1],param2[n].par_fuz[0][2],
                           param2[n].par_fuz[0][3],param2[n].par_fuz[0][4],param2[n].par_fuz[0][5],
                           param2[n].par_fuz[0][6],param2[n].par_fuz[0][7],param2[n].par_fuz[0][8],
                           param2[n].par_fuz[1][0],param2[n].par_fuz[1][1],param2[n].par_fuz[1][2],
                           param2[n].par_fuz[1][3],param2[n].par_fuz[1][4],param2[n].par_fuz[1][5],
                           param2[n].par_fuz[1][6],param2[n].par_fuz[1][7],param2[n].par_fuz[1][8],
                           param2[n].par_fuz[2][0],param2[n].par_fuz[2][1],param2[n].par_fuz[2][2],
                           param2[n].par_fuz[2][3],param2[n].par_fuz[2][4],param2[n].par_fuz[2][5],
                           param2[n].par_fuz[2][6],param2[n].par_fuz[2][7],param2[n].par_fuz[2][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
//add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
            //  s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];
                          sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param2[n].stv;

                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));
                        break;
         case 4://расчитываем параметры для блока Диагностика работоспособности.
                  if(f_Parent->Type_Char == PROP)
                          calc_DIAGN(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param3[h].par[7],
                                            param3[h].par[3],param3[h].par[4],param3[h].par[5],param3[h].par[6],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                          calc_DIAGN_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param3[h].par_fuz[7][0],param3[h].par_fuz[0][1],param3[h].par_fuz[0][2],
                           param3[h].par_fuz[7][3],param3[h].par_fuz[0][4],param3[h].par_fuz[0][5],
                           param3[h].par_fuz[7][6],param3[h].par_fuz[0][7],param3[h].par_fuz[0][8],
                           param3[h].par_fuz[3][0],param3[h].par_fuz[3][1],param3[h].par_fuz[3][2],
                           param3[h].par_fuz[3][3],param3[h].par_fuz[3][4],param3[h].par_fuz[3][5],
                           param3[h].par_fuz[3][6],param3[h].par_fuz[3][7],param3[h].par_fuz[3][8],
                           param3[h].par_fuz[4][0],param3[h].par_fuz[4][1],param3[h].par_fuz[4][2],
                           param3[h].par_fuz[4][3],param3[h].par_fuz[4][4],param3[h].par_fuz[4][5],
                           param3[h].par_fuz[4][6],param3[h].par_fuz[4][7],param3[h].par_fuz[4][8],
                           param3[h].par_fuz[5][0],param3[h].par_fuz[5][1],param3[h].par_fuz[5][2],
                           param3[h].par_fuz[5][3],param3[h].par_fuz[5][4],param3[h].par_fuz[5][5],
                           param3[h].par_fuz[5][6],param3[h].par_fuz[5][7],param3[h].par_fuz[5][8],
                           param3[h].par_fuz[6][0],param3[h].par_fuz[6][1],param3[h].par_fuz[6][2],
                           param3[h].par_fuz[6][3],param3[h].par_fuz[6][4],param3[h].par_fuz[6][5],
                           param3[h].par_fuz[6][6],param3[h].par_fuz[6][7],param3[h].par_fuz[6][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

//        param1[k].par_fuz[0],param1[k].par_fuz[1],param1[k].par_fuz[2],
//                         param3[h].par_fuz[7],
//                           param3[h].par_fuz[3],param3[h].par_fuz[4],param3[h].par_fuz[5],param3[h].par_fuz[6],
//  param_rez[r].par_fuz[0],param_rez[r].par_fuz[1],param_rez[r].par_fuz[2]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
//add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
                  //        s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];

                          sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param3[h].stv;

                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));
                        break;
         case 5://расчитываем параметры для блока Функциональный контроль
                  if(f_Parent->Type_Char==PROP)
                          calc_DIAGN_2(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param3[h].par[8],param3[h].par[9],param3[h].par[10],param3[h].par[11],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                          calc_DIAGN_2_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param3[h].par_fuz[8][0],param3[h].par_fuz[8][1],param3[h].par_fuz[8][2],
                           param3[h].par_fuz[8][3],param3[h].par_fuz[8][4],param3[h].par_fuz[8][5],
                           param3[h].par_fuz[8][6],param3[h].par_fuz[8][7],param3[h].par_fuz[8][8],
                           param3[h].par_fuz[9][0],param3[h].par_fuz[9][1],param3[h].par_fuz[9][2],
                           param3[h].par_fuz[9][3],param3[h].par_fuz[9][4],param3[h].par_fuz[9][5],
                           param3[h].par_fuz[9][6],param3[h].par_fuz[9][7],param3[h].par_fuz[9][8],
                           param3[h].par_fuz[10][0],param3[h].par_fuz[10][1],param3[h].par_fuz[10][2],
                           param3[h].par_fuz[10][3],param3[h].par_fuz[10][4],param3[h].par_fuz[10][5],
                           param3[h].par_fuz[10][6],param3[h].par_fuz[10][7],param3[h].par_fuz[10][8],
                           param3[h].par_fuz[11][0],param3[h].par_fuz[11][1],param3[h].par_fuz[11][2],
                           param3[h].par_fuz[11][3],param3[h].par_fuz[11][4],param3[h].par_fuz[11][5],
                           param3[h].par_fuz[11][6],param3[h].par_fuz[11][7],param3[h].par_fuz[11][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

                     //     param1[k].par_fuz[0],param1[k].par_fuz[1],param1[k].par_fuz[2],
                     //                       param3[h].par_fuz[8],param3[h].par_fuz[9],param3[h].par_fuz[10],param3[h].par_fuz[11],
                     //                       param_rez[r].par_fuz[0],param_rez[r].par_fuz[1],param_rez[r].par_fuz[2]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
//add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
                         // s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];
                          sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param3[h].stv;

                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "нет условия",sovmest,sovmest0,sovmest1));
                        break;
         case 8:
                  if(f_Parent->Type_Char == PROP)
                          calc_WHILE_DO(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param3[h].par[7],
                                            param3[h].par[3],param3[h].par[4],param3[h].par[5],param3[h].par[6],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                          calc_WHILE_DO_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param3[h].par_fuz[7][0],param3[h].par_fuz[0][1],param3[h].par_fuz[0][2],
                           param3[h].par_fuz[7][3],param3[h].par_fuz[0][4],param3[h].par_fuz[0][5],
                           param3[h].par_fuz[7][6],param3[h].par_fuz[0][7],param3[h].par_fuz[0][8],
                           param3[h].par_fuz[3][0],param3[h].par_fuz[3][1],param3[h].par_fuz[3][2],
                           param3[h].par_fuz[3][3],param3[h].par_fuz[3][4],param3[h].par_fuz[3][5],
                           param3[h].par_fuz[3][6],param3[h].par_fuz[3][7],param3[h].par_fuz[3][8],
                           param3[h].par_fuz[4][0],param3[h].par_fuz[4][1],param3[h].par_fuz[4][2],
                           param3[h].par_fuz[4][3],param3[h].par_fuz[4][4],param3[h].par_fuz[4][5],
                           param3[h].par_fuz[4][6],param3[h].par_fuz[4][7],param3[h].par_fuz[4][8],
                           param3[h].par_fuz[5][0],param3[h].par_fuz[5][1],param3[h].par_fuz[5][2],
                           param3[h].par_fuz[5][3],param3[h].par_fuz[5][4],param3[h].par_fuz[5][5],
                           param3[h].par_fuz[5][6],param3[h].par_fuz[5][7],param3[h].par_fuz[5][8],
                           param3[h].par_fuz[6][0],param3[h].par_fuz[6][1],param3[h].par_fuz[6][2],
                           param3[h].par_fuz[6][3],param3[h].par_fuz[6][4],param3[h].par_fuz[6][5],
                           param3[h].par_fuz[6][6],param3[h].par_fuz[6][7],param3[h].par_fuz[6][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

     //                     param1[k].par_fuz[0],param1[k].par_fuz[1],param1[k].par_fuz[2],
     //                                       param3[h].par_fuz[7],
     //                                       param3[h].par_fuz[3],param3[h].par_fuz[4],param3[h].par_fuz[5],param3[h].par_fuz[6],
     //                                       param_rez[r].par_fuz[0],param_rez[r].par_fuz[1],param_rez[r].par_fuz[2]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
//add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
    //                      s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];
                          sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param3[h].stv;

                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));
                        break;

//для всех других типов - просто добавляем "пустые" альтернативы в блок-родитель
        case RASV_SIM: //для подмножеств альтернатив
                  if(f_Parent->Type_Char == PROP)
                     calc_RASV_SIM(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                param2[n].par[0],param2[n].par[1],param2[n].par[2],
                                //param3[h].pred,
                                s_predicat.c_str(),
                                &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                    calc_RASV_SIM_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param2[n].par_fuz[0][0],param2[n].par_fuz[0][1],param2[n].par_fuz[0][2],
                           param2[n].par_fuz[0][3],param2[n].par_fuz[0][4],param2[n].par_fuz[0][5],
                           param2[n].par_fuz[0][6],param2[n].par_fuz[0][7],param2[n].par_fuz[0][8],
                           param2[n].par_fuz[1][0],param2[n].par_fuz[1][1],param2[n].par_fuz[1][2],
                           param2[n].par_fuz[1][3],param2[n].par_fuz[1][4],param2[n].par_fuz[1][5],
                           param2[n].par_fuz[1][6],param2[n].par_fuz[1][7],param2[n].par_fuz[1][8],
                           param2[n].par_fuz[2][0],param2[n].par_fuz[2][1],param2[n].par_fuz[2][2],
                           param2[n].par_fuz[2][3],param2[n].par_fuz[2][4],param2[n].par_fuz[2][5],
                           param2[n].par_fuz[2][6],param2[n].par_fuz[2][7],param2[n].par_fuz[2][8],
                           s_predicat.c_str(),
                          // param3[h].pred,
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];

//  add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
         // s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];

//    if(strcmp(s_predicat.c_str(),"1")==0){sostav=param1[k].stv+(AnsiString)";"+IntToStr(n2)+(AnsiString)".0;"+(AnsiString)param3[h].stv;};
//    else

    if(strcmp(s_predicat.c_str(),"1")==0)sostav=param1[k].stv+(AnsiString)";"+atoi(param2[n].stv)+(AnsiString)".0;"+(AnsiString)param3[h].stv;
       else  sostav=(AnsiString)""+atoi(param1[k].stv)+(AnsiString)".0;"+param2[n].stv+(AnsiString)";"+(AnsiString)param3[h].stv;


                     f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                         s_b,s_t,s_v,
                                         1,1,0,0,1,1,0,0,
                                         "(нет элемента)",1,
                                         a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                         a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                         a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                         0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                         0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                         0,0,0,0.5,0,0,1,0,0,
                                         "(нет условия)",sovmest,sovmest0,sovmest1));
                     break;
                      //развилка
                   case 6:
                                     if(f_Parent->Type_Char == PROP)
                          calc_RASV(param1[k].par[0],param1[k].par[1],param1[k].par[2],
                                            param2[n].par[0],param2[n].par[1],param2[n].par[2],
                                            param3[h].par[7],
                                            param3[h].par[3],param3[h].par[4],param3[h].par[5],param3[h].par[6],
                                            &param_rez[r].par[0],&param_rez[r].par[1],&param_rez[r].par[2]);
                  else
                          calc_RASV_fuz(
                           param1[k].par_fuz[0][0],param1[k].par_fuz[0][1],param1[k].par_fuz[0][2],
                           param1[k].par_fuz[0][3],param1[k].par_fuz[0][4],param1[k].par_fuz[0][5],
                           param1[k].par_fuz[0][6],param1[k].par_fuz[0][7],param1[k].par_fuz[0][8],
                           param1[k].par_fuz[1][0],param1[k].par_fuz[1][1],param1[k].par_fuz[1][2],
                           param1[k].par_fuz[1][3],param1[k].par_fuz[1][4],param1[k].par_fuz[1][5],
                           param1[k].par_fuz[1][6],param1[k].par_fuz[1][7],param1[k].par_fuz[1][8],
                           param1[k].par_fuz[2][0],param1[k].par_fuz[2][1],param1[k].par_fuz[2][2],
                           param1[k].par_fuz[2][3],param1[k].par_fuz[2][4],param1[k].par_fuz[2][5],
                           param1[k].par_fuz[2][6],param1[k].par_fuz[2][7],param1[k].par_fuz[2][8],
                           param2[n].par_fuz[0][0],param2[n].par_fuz[0][1],param2[n].par_fuz[0][2],
                           param2[n].par_fuz[0][3],param2[n].par_fuz[0][4],param2[n].par_fuz[0][5],
                           param2[n].par_fuz[0][6],param2[n].par_fuz[0][7],param2[n].par_fuz[0][8],
                           param2[n].par_fuz[1][0],param2[n].par_fuz[1][1],param2[n].par_fuz[1][2],
                           param2[n].par_fuz[1][3],param2[n].par_fuz[1][4],param2[n].par_fuz[1][5],
                           param2[n].par_fuz[1][6],param2[n].par_fuz[1][7],param2[n].par_fuz[1][8],
                           param2[n].par_fuz[2][0],param2[n].par_fuz[2][1],param2[n].par_fuz[2][2],
                           param2[n].par_fuz[2][3],param2[n].par_fuz[2][4],param2[n].par_fuz[2][5],
                           param2[n].par_fuz[2][6],param2[n].par_fuz[2][7],param2[n].par_fuz[2][8],
                           param3[h].par_fuz[7][0],param3[h].par_fuz[0][1],param3[h].par_fuz[0][2],
                           param3[h].par_fuz[7][3],param3[h].par_fuz[0][4],param3[h].par_fuz[0][5],
                           param3[h].par_fuz[7][6],param3[h].par_fuz[0][7],param3[h].par_fuz[0][8],
                           param3[h].par_fuz[3][0],param3[h].par_fuz[3][1],param3[h].par_fuz[3][2],
                           param3[h].par_fuz[3][3],param3[h].par_fuz[3][4],param3[h].par_fuz[3][5],
                           param3[h].par_fuz[3][6],param3[h].par_fuz[3][7],param3[h].par_fuz[3][8],
                           param3[h].par_fuz[4][0],param3[h].par_fuz[4][1],param3[h].par_fuz[4][2],
                           param3[h].par_fuz[4][3],param3[h].par_fuz[4][4],param3[h].par_fuz[4][5],
                           param3[h].par_fuz[4][6],param3[h].par_fuz[4][7],param3[h].par_fuz[4][8],
                           param3[h].par_fuz[5][0],param3[h].par_fuz[5][1],param3[h].par_fuz[5][2],
                           param3[h].par_fuz[5][3],param3[h].par_fuz[5][4],param3[h].par_fuz[5][5],
                           param3[h].par_fuz[5][6],param3[h].par_fuz[5][7],param3[h].par_fuz[5][8],
                           param3[h].par_fuz[6][0],param3[h].par_fuz[6][1],param3[h].par_fuz[6][2],
                           param3[h].par_fuz[6][3],param3[h].par_fuz[6][4],param3[h].par_fuz[6][5],
                           param3[h].par_fuz[6][6],param3[h].par_fuz[6][7],param3[h].par_fuz[6][8],
                           &param_rez[r].par_fuz[0][0],&param_rez[r].par_fuz[0][1],&param_rez[r].par_fuz[0][2],
                           &param_rez[r].par_fuz[0][3],&param_rez[r].par_fuz[0][4],&param_rez[r].par_fuz[0][5],
                           &param_rez[r].par_fuz[0][6],&param_rez[r].par_fuz[0][7],&param_rez[r].par_fuz[0][8],
                           &param_rez[r].par_fuz[1][0],&param_rez[r].par_fuz[1][1],&param_rez[r].par_fuz[1][2],
                           &param_rez[r].par_fuz[1][3],&param_rez[r].par_fuz[1][4],&param_rez[r].par_fuz[1][5],
                           &param_rez[r].par_fuz[1][6],&param_rez[r].par_fuz[1][7],&param_rez[r].par_fuz[1][8],
                           &param_rez[r].par_fuz[2][0],&param_rez[r].par_fuz[2][1],&param_rez[r].par_fuz[2][2],
                           &param_rez[r].par_fuz[2][3],&param_rez[r].par_fuz[2][4],&param_rez[r].par_fuz[2][5],
                           &param_rez[r].par_fuz[2][6],&param_rez[r].par_fuz[2][7],&param_rez[r].par_fuz[2][8]);

     //                     param1[k].par_fuz[0],param1[k].par_fuz[1],param1[k].par_fuz[2],
     //                                       param3[h].par_fuz[7],
     //                                       param3[h].par_fuz[3],param3[h].par_fuz[4],param3[h].par_fuz[5],param3[h].par_fuz[6],
     //                                       param_rez[r].par_fuz[0],param_rez[r].par_fuz[1],param_rez[r].par_fuz[2]);

                  s_b=param_rez[r].par[0];
                  s_t=param_rez[r].par[1];
                  s_v=param_rez[r].par[2];
//add_name=(AnsiString)child->dad->name+(AnsiString)"."+(AnsiString)(r+1);
                  a1_b_f=param_rez[r].par_fuz[0][0]; b_f1n=param_rez[r].par_fuz[0][1]; b_f1b=param_rez[r].par_fuz[0][2];
                  a2_b_f=param_rez[r].par_fuz[0][3]; b_f2n=param_rez[r].par_fuz[0][4]; b_f2b=param_rez[r].par_fuz[0][5];
                  a3_b_f=param_rez[r].par_fuz[0][6]; b_f3n=param_rez[r].par_fuz[0][7]; b_f3b=param_rez[r].par_fuz[0][8];
                  a1_t_f=param_rez[r].par_fuz[1][0]; t_f1n=param_rez[r].par_fuz[1][1]; t_f1b=param_rez[r].par_fuz[1][2];
                  a2_t_f=param_rez[r].par_fuz[1][3]; t_f2n=param_rez[r].par_fuz[1][4]; t_f2b=param_rez[r].par_fuz[1][5];
                  a3_t_f=param_rez[r].par_fuz[1][6]; t_f3n=param_rez[r].par_fuz[1][7]; t_f3b=param_rez[r].par_fuz[1][8];
                  a1_v_f=param_rez[r].par_fuz[2][0]; v_f1n=param_rez[r].par_fuz[2][1]; v_f1b=param_rez[r].par_fuz[2][2];
                  a2_v_f=param_rez[r].par_fuz[2][3]; v_f2n=param_rez[r].par_fuz[2][4]; v_f2b=param_rez[r].par_fuz[2][5];
                  a3_v_f=param_rez[r].par_fuz[2][6]; v_f3n=param_rez[r].par_fuz[2][7]; v_f3b=param_rez[r].par_fuz[2][8];
    //                      s_b_f=param_rez[r].par_fuz[0];s_t_f=param_rez[r].par_fuz[1];s_v_f=param_rez[r].par_fuz[2];
                          sostav=param1[k].stv+(AnsiString)";"+param2[n].stv+(AnsiString)";"+(AnsiString)param3[h].stv;

                          f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              s_b,s_t,s_v,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                                              a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                                              a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));
                        break;
         case PROV_IF:
                           sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param3[h].stv;
                           f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              1,0,0,
                                              1,1,0,0,1,1,0,0,
											  "(нет элемента)",1,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));

                       break;

         default:

						   sostav=param1[k].stv+(AnsiString)";"+(AnsiString)param2[n].stv+(AnsiString)";"+(AnsiString)param3[h].stv;
                           f_ParamAlt->AddItem( CreateParamAlternativeItem(sostav.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type, f_WorkItem->ParentID,
                                              1,0,0,
                                              1,1,0,0,1,1,0,0,
                                              "(нет элемента)",1,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
                                              0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,0,0,0,0.5,0,0,1,0,0,
											  0,0,0,0.5,0,0,1,0,0,
                                              "(нет условия)",sovmest,sovmest0,sovmest1));

                       break;
         }
            r++;
}




////////////


free(param1);
free(param2);
free(param3);
free(param_rez);
}


void TPartialDecisionItem::Proverka_NUOpt()
{
  if(f_Parent->Type_Char == PROP)
  {
	switch(opt_sadacha->type_sadacha)
	{
      case ZAD_1:
//        switch(opt_sadacha->type_ogr)//задача по В
          switch(GetOptZadachaTypeOgrForNUOpt())
                    {
                     case 0:proverka_type_krit(BB);break;//только по В
                     case 1:proverka_type_krit(BV);break;//критерий V
                     case 2:proverka_type_krit(BT);break;//критерий T
                     case 3:proverka_type_krit(BTV);break;//критерий V и T
                     case 4:proverka_type_krit(BBS);break;//только по В
                     case 5:proverka_type_krit(BVS);break;//критерий V
                     case 6:proverka_type_krit(BTS);break;//критерий T
                     case 7:proverka_type_krit(BTVS);break;//критерий V и T
                    }
              break;
//      case ZAD_2:switch(opt_sadacha->type_ogr)//задача по Т
        case ZAD_2:switch(GetOptZadachaTypeOgrForNUOpt())

                    {
                     case 0:proverka_type_krit(BT);break;//только по Т (плюс всегда В)
                     case 1:proverka_type_krit(BTV);break;//критерий V
                     case 2:proverka_type_krit(BT);break;//критерий B
                     case 3:proverka_type_krit(BTV);break;////критерий V и B
                     case 4:proverka_type_krit(BTS);break;//только по Т (плюс всегда В)
                     case 5:proverka_type_krit(BTVS);break;//критерий V
                     case 6:proverka_type_krit(BTS);break;//критерий B
                     case 7:proverka_type_krit(BTVS);break;////критерий V и B
                    }
              break;
//      case ZAD_3:switch(opt_sadacha->type_ogr)//задача по V
      case ZAD_3:switch(GetOptZadachaTypeOgrForNUOpt())
                    {
                     case 0:proverka_type_krit(BV);break;//нет критериев
                     case 1:proverka_type_krit(BV);break;//критерий B
                     case 2:proverka_type_krit(BTV);break;//критерий T
                     case 3:proverka_type_krit(BTV);break;//критерий T и B
                     case 4:proverka_type_krit(BVS);break;//нет критериев
                     case 5:proverka_type_krit(BVS);break;//критерий B
                     case 6:proverka_type_krit(BTVS);break;//критерий T
                     case 7:proverka_type_krit(BTVS);break;//критерий T и B
                    }
              break;

     case ZAD_4://обобщенные задачи
     case ZAD_5:
//     case ZAD_6: if(opt_sadacha->type_ogr < 4)
     case ZAD_6: if(GetOptZadachaTypeOgrForNUOpt() < 4 )
            {
              proverka_type_krit(BTV);
              break;
            }
            else {
              proverka_type_krit(BTVS);
              break;
            }
   }
  }

  if(f_Parent->Type_Char == FUZZY)
  {
  switch(opt_sadacha->type_sadacha)
   {
//   case ZAD_1:switch(opt_sadacha->type_ogr)//задача по В
   case ZAD_1:switch(GetOptZadachaTypeOgrForNUOpt())
                    {
                     case 0:proverka_type_krit_fuz(BB);break;//только по В
                     case 1:proverka_type_krit_fuz(BV);break;//критерий V
                     case 2:proverka_type_krit_fuz(BT);break;//критерий T
                     case 3:proverka_type_krit_fuz(BTV);break;//критерий V и T
                     case 4:proverka_type_krit_fuz(BBS);break;//только по В
                     case 5:proverka_type_krit_fuz(BVS);break;//критерий V
                     case 6:proverka_type_krit_fuz(BTS);break;//критерий T
                     case 7:proverka_type_krit_fuz(BTVS);break;//критерий V и T
                    }
                    break;
//   case ZAD_2:switch(opt_sadacha->type_ogr)//задача по Т
   case ZAD_2:switch(GetOptZadachaTypeOgrForNUOpt())
                    {
                     case 0:proverka_type_krit_fuz(BT);break;//только по Т (плюс всегда В)
                     case 1:proverka_type_krit_fuz(BTV);break;//критерий V
                     case 2:proverka_type_krit_fuz(BT);break;//критерий B
                     case 3:proverka_type_krit_fuz(BTV);break;////критерий V и B
                     case 4:proverka_type_krit_fuz(BTS);break;//только по Т (плюс всегда В)
                     case 5:proverka_type_krit_fuz(BTVS);break;//критерий V
                     case 6:proverka_type_krit_fuz(BTS);break;//критерий B
                     case 7:proverka_type_krit_fuz(BTVS);break;////критерий V и B
                    }
              break;
//   case ZAD_3:switch(opt_sadacha->type_ogr)//задача по V
   case ZAD_3:switch(GetOptZadachaTypeOgrForNUOpt())
                    {
                     case 0:proverka_type_krit_fuz(BV);break;//нет критериев
                     case 1:proverka_type_krit_fuz(BV);break;//критерий B
                     case 2:proverka_type_krit_fuz(BTV);break;//критерий T
                     case 3:proverka_type_krit_fuz(BTV);break;//критерий T и B
                     case 4:proverka_type_krit_fuz(BVS);break;//нет критериев
                     case 5:proverka_type_krit_fuz(BVS);break;//критерий B
                     case 6:proverka_type_krit_fuz(BTVS);break;//критерий T
                     case 7:proverka_type_krit_fuz(BTVS);break;//критерий T и B
                    }
              break;

   case ZAD_4://обобщенные задачи
   case ZAD_5:
//   case ZAD_6:if(opt_sadacha->type_ogr < 4)
   case ZAD_6:if(GetOptZadachaTypeOgrForNUOpt() < 4 )
   {proverka_type_krit_fuz(BTVS);break;}
               else {proverka_type_krit_fuz(BTVS);break;}

      }
  }

}


void TPartialDecisionItem::proverka_type_krit(int type_krit)
{
//Алгоритм
//признак удаления в FALSE
//Начинаем с начала отфильтрованной таблицы
//Цикл (  пока признак удаления = = TRUE )
//1. Берем ПА (параметрическую альтернативу)
//2. Сравниваем с остальными ПА
//   Если для текущей ПА не выполняется НУОпт - удаляем эту ПА и признак удаления в TRUE
//   Иначе идем дальше по таблице
//3. Если конец таблицы, то снова в начало

//фильтр для текущего подблока


  char str[StrMemSize + 1], str_next[StrMemSize + 1];
  double b,t,v,b_next,t_next,v_next; //,sovm,sovm_next;

  TParamAlternativeItem *AI, *AJ;

  TDynamicArray *mDel = new TDynamicArray;
  for (int i = 0; i <= f_ParamAlt->Count - 1; i++)
  {
    AI = f_ParamAlt->Items[i];
    if (!mDel->Find(AI))
    {
      b = AI->B;
      t = AI->T;
      v = AI->V;
      strcpy(str, AI->SOSTAV.c_str());
      for (int j = 0; j <= f_ParamAlt->Count - 1; j++)
      {
        AJ = f_ParamAlt->Items[j];
        if ( (i != j) && (!mDel->Find(AJ)) )
        {
          b_next = AJ->B;
          t_next = AJ->T;
          v_next = AJ->V;
          strcpy(str_next, AJ->SOSTAV.c_str());

          //если частичное решение с b_next доминирует частичное решение с b, то удаляем решение b
          switch(type_krit)
          {
            case BB:if(domin_P_B(b_next,b)) mDel->Append(AI); break;
            case BT:if(domin_P_BT(b_next,b,t_next,t)) mDel->Append(AI); break;
            case BV:if(domin_P_BV(b_next,b,v_next,v)) mDel->Append(AI); break;
            case BTV:if(domin_P_BTV(b_next,b,t_next,t,v_next,v)) mDel->Append(AI); break;
            case BBS:if(domin_P_B_S(b_next,b,str_next,str)) mDel->Append(AI); break;
            case BTS:if(domin_P_BT_S(b_next,b,t_next,t,str_next,str)) mDel->Append(AI); break;
            case BVS:if(domin_P_BV_S(b_next,b,v_next,v,str_next,str)) mDel->Append(AI); break;
            case BTVS:if(domin_P_BTV_S(b_next,b,t_next,t,v_next,v,str_next,str)) mDel->Append(AI); break;
          }
        }
      }
    }
  }
  for (int i = 0; i <= mDel->Count - 1; i++)
    f_ParamAlt->Delete2(mDel->Items[i]);
  delete mDel;
  proverka_priblj(opt_sadacha->Rate);
  if(f_Parent->CheckNud)
	proverka_nud();
}


void TPartialDecisionItem::proverka_type_krit_fuz(int type_krit)
{
//Алгоритм
//признак удаления в FALSE
//Начинаем с начала отфильтрованной таблицы
//Цикл (  пока признак удаления = = TRUE )
//1. Берем ПА (параметрическую альтернативу)
//2. Сравниваем с остальными ПА
//   Если для текущей ПА не выполняется НУОпт - удаляем эту ПА и признак удаления в TRUE
//   Иначе идем дальше по таблице
//3. Если конец таблицы, то снова в начало


  char str[StrMemSize + 1], str_next[StrMemSize + 1];
  double a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
	a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
    a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,
    a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
    a1_t_n_f, t_n_f1n, t_n_f1b, a2_t_n_f, t_n_f2n, t_n_f2b, a3_t_n_f, t_n_f3n, t_n_f3b,
    a1_v_n_f, v_n_f1n, v_n_f1b, a2_v_n_f, v_n_f2n, v_n_f2b, a3_v_n_f, v_n_f3n, v_n_f3b;

  TParamAlternativeItem *AI, *AJ;

  TDynamicArray *mDel = new TDynamicArray;
  for (int i = 0; i <= f_ParamAlt->Count - 1; i++)
  {
    AI = f_ParamAlt->Items[i];
    if (!mDel->Find(AI))
    {

      a1_b_f = AI->A1_B_F;
      b_f1n = AI->B_F1N;
      b_f1b = AI->B_F1B;
      a2_b_f = AI->A2_B_F;
      b_f2n = AI->B_F2N;
      b_f2b = AI->B_F2B;
      a3_b_f = AI->A3_B_F;
      b_f3n = AI->B_F3N;
      b_f3b = AI->B_F3B;

      a1_t_f = AI->A1_T_F;
      t_f1n = AI->T_F1N;
      t_f1b = AI->T_F1B;
      a2_t_f = AI->A2_T_F;
      t_f2n = AI->T_F2N;
      t_f2b = AI->T_F2B;
      a3_t_f = AI->A3_T_F;
      t_f3n = AI->T_F3N;
      t_f3b = AI->T_F3B;

      a1_v_f = AI->A1_V_F;
      v_f1n = AI->V_F1N;
      v_f1b = AI->V_F1B;
      a2_v_f = AI->A2_V_F;
      v_f2n = AI->V_F2N;
      v_f2b = AI->V_F2B;
      a3_v_f = AI->A3_V_F;
      v_f3n = AI->V_F3N;
      v_f3b = AI->V_F3B;
      strcpy(str, AI->SOSTAV.c_str());

      for (int j = 0; j <= f_ParamAlt->Count - 1; j++)
      {
        AJ = f_ParamAlt->Items[j];
        if ( (i != j) && (!mDel->Find(AJ)) )
        {
          a1_b_n_f = AJ->A1_B_F;
          b_n_f1n = AJ->B_F1N;
          b_n_f1b = AJ->B_F1B;
          a2_b_n_f = AJ->A2_B_F;
          b_n_f2n = AJ->B_F2N;
          b_n_f2b = AJ->B_F2B;
          a3_b_n_f = AJ->A3_B_F;
          b_n_f3n = AJ->B_F3N;
          b_n_f3b = AJ->B_F3B;

          a1_t_n_f = AJ->A1_T_F;
          t_n_f1n = AJ->T_F1N;
          t_n_f1b = AJ->T_F1B;
          a2_t_n_f = AJ->A2_T_F;
          t_n_f2n = AJ->T_F2N;
          t_n_f2b = AJ->T_F2B;
          a3_t_n_f = AJ->A3_T_F;
          t_n_f3n = AJ->T_F3N;
          t_n_f3b = AJ->T_F3B;

          a1_v_n_f = AJ->A1_V_F;
          v_n_f1n = AJ->V_F1N;
          v_n_f1b = AJ->V_F1B;
          a2_v_n_f = AJ->A2_V_F;
          v_n_f2n = AJ->V_F2N;
          v_n_f2b = AJ->V_F2B;
          a3_v_n_f = AJ->A3_V_F;
          v_n_f3n = AJ->V_F3N;
          v_n_f3b = AJ->V_F3B;
          strcpy(str_next, AJ->SOSTAV.c_str());

          //если частичное решение с b_next доминирует частичное решение с b, то удаляем решение b
          switch(type_krit)
          {
            case BB:if(domin_P_B_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                               a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b)) mDel->Append(AI); break;
            case BT:if(domin_P_BT_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_t_n_f, t_n_f1n, t_n_f1b, a2_t_n_f, t_n_f2n, t_n_f2b, a3_t_n_f, t_n_f3n, t_n_f3b,
                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b)) mDel->Append(AI); break;
            case BV:if(domin_P_BV_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_v_n_f, v_n_f1n, v_n_f1b, a2_v_n_f, v_n_f2n, v_n_f2b, a3_v_n_f, v_n_f3n, v_n_f3b,
                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b )) mDel->Append(AI); break;
            case BTV:if(domin_P_BTV_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_t_n_f, t_n_f1n, t_n_f1b, a2_t_n_f, t_n_f2n, t_n_f2b, a3_t_n_f, t_n_f3n, t_n_f3b,
                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                     a1_v_n_f, v_n_f1n, v_n_f1b, a2_v_n_f, v_n_f2n, v_n_f2b, a3_v_n_f, v_n_f3n, v_n_f3b,
                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b)) mDel->Append(AI); break;
            case BBS:if(domin_P_BS_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                               a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,str_next,str)) mDel->Append(AI); break;
            case BTS:if(domin_P_BTS_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_t_n_f, t_n_f1n, t_n_f1b, a2_t_n_f, t_n_f2n, t_n_f2b, a3_t_n_f, t_n_f3n, t_n_f3b,
                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,str_next,str)) mDel->Append(AI); break;
            case BVS:if(domin_P_BVS_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_v_n_f, v_n_f1n, v_n_f1b, a2_v_n_f, v_n_f2n, v_n_f2b, a3_v_n_f, v_n_f3n, v_n_f3b,
                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,str_next,str)) mDel->Append(AI); break;
            case BTVS:if(domin_P_BTVS_fuz(a1_b_n_f, b_n_f1n, b_n_f1b, a2_b_n_f, b_n_f2n, b_n_f2b, a3_b_n_f, b_n_f3n, b_n_f3b,
                     a1_b_f, b_f1n, b_f1b, a2_b_f, b_f2n, b_f2b, a3_b_f, b_f3n, b_f3b,
                     a1_t_n_f, t_n_f1n, t_n_f1b, a2_t_n_f, t_n_f2n, t_n_f2b, a3_t_n_f, t_n_f3n, t_n_f3b,
                     a1_t_f, t_f1n, t_f1b, a2_t_f, t_f2n, t_f2b, a3_t_f, t_f3n, t_f3b,
                     a1_v_n_f, v_n_f1n, v_n_f1b, a2_v_n_f, v_n_f2n, v_n_f2b, a3_v_n_f, v_n_f3n, v_n_f3b,
                     a1_v_f, v_f1n, v_f1b, a2_v_f, v_f2n, v_f2b, a3_v_f, v_f3n, v_f3b,str_next,str)) mDel->Append(AI); break;
          }
        }
      }
    }
  }
  for (int i = 0; i <= mDel->Count - 1; i++)
    f_ParamAlt->Delete2(mDel->Items[i]);
  delete mDel;
  proverka_priblj_fuz(opt_sadacha->Rate);
  if(f_Parent->CheckNud)
	proverka_nud_fuz();
}

void TPartialDecisionItem::proverka_priblj(double ARate)
{
  TParamAlternativeItem *AI;
  int in_zad, paramCnt;
  double b, t, v, I11, I1;
  double b_cr, t_cr, v_cr;

  b_cr=0;
  t_cr=0;
  v_cr=0;
  I11 = 0.0;

  int type_metod = opt_sadacha->get_type_metod();
  TDynamicArray *mDel = new TDynamicArray;
  if(type_metod==PRIBLJ2)
  {
    paramCnt = f_ParamAlt->Count;
    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      b = AI->B;
      t = AI->T;
      v = AI->V;
      switch(opt_sadacha->type_sadacha)//не ищем экстрему среди записей, не подходящих по ограничениям
          {
           case ZAD_1:switch(opt_sadacha->type_ogr)//задача по В
                    {
                     case 1: v_cr = v_cr+ v;//критерий V
                             in_zad=3;
                             break;
                     case 2: t_cr=t_cr+ t;//критерий T
                             in_zad=2;
                             break;
                     case 3: v_cr=v_cr+ v;
                             t_cr=t_cr+ t;
                             in_zad=6;
                            break;
                     case 4:break;
                     case 5: v_cr=v_cr+ v;
                             in_zad=3;
                            break;
                     case 6: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 7: v_cr=v_cr+ v;
                             t_cr=t_cr+ t;
                             in_zad=6;
                             break;
                     }
              break;
           case ZAD_2:switch(opt_sadacha->type_ogr)//задача по Т
                    {
                     case 1: v_cr=v_cr+ v;
                             in_zad=3;
                             break;
                     case 2: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 3: v_cr=v_cr+ v;
                             b_cr=b_cr+ (1-b);
                             in_zad=5;
                             break;
                     case 4: break;
                     case 5: v_cr=v_cr+ v;
                             in_zad=3;
                             break;
                     case 6: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 7: v_cr=v_cr+ v;
                             b_cr=b_cr+ (1-b);
                             in_zad=5;
                             break;
                    }
              break;
           case ZAD_3:switch(opt_sadacha->type_ogr)//задача по V
                    {
                     case 1: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 2: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 3: b_cr=b_cr+ (1-b);
                             t_cr=t_cr+ t;
                             in_zad=4;
                             break;
                     case 4: break;
                     case 5: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 6: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 7: b_cr=b_cr+ (1-b);
                             t_cr=t_cr+ t;
                             in_zad=4;
                             break;
                    }
              break;
           }

    }
    if(paramCnt > 0)
    {
      b_cr = b_cr/paramCnt;
      t_cr = t_cr/paramCnt;
      v_cr = v_cr/paramCnt;
    }

    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      b = AI->B;
      t = AI->T;
      v = AI->V;
      if(in_zad==1)
      {
        if (b_cr == 0) continue;
        I11=(1-b)/b_cr;
      }
      if(in_zad==2)
      {
        if(t_cr == 0) continue;
        I11=t/t_cr;
      }
      if(in_zad==3)
      {
         if(v_cr == 0) continue;
         I11=v/v_cr;
      }
      if(in_zad==4)
      {
        if((b_cr == 0)  || (t_cr == 0)) continue;
        I11=0.5*((1-b)/b_cr+t/t_cr);
      }
      if(in_zad==5)
      {
        if((b_cr == 0)  || (v_cr == 0)) continue;
        I11 = 0.5*((1-b)/b_cr+v/v_cr);
      }
      if(in_zad==6)
      {
        if((v_cr == 0)  || (t_cr == 0)) continue;
        I11=0.5*(v/v_cr+t/t_cr);
      }
      I1 = random(100)*1.0;
      if ( (I1 - I11*ARate) < 0.0 )
          mDel->Append(AI);
    }
  }
  if(type_metod==PRIBLJ1)
  {
    paramCnt = f_ParamAlt->Count;
    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      I1 = random(100)*1.0;
      if ( (I1 - ARate) < 0.0 )
         mDel->Append(AI);
    }
  }

  for (int i = 0; i <= mDel->Count - 1; i++)
  {
    if (f_ParamAlt->Count > 1)
      f_ParamAlt->Delete2(mDel->Items[i]);
  }
  delete mDel;
}

void TPartialDecisionItem::proverka_priblj_fuz(double ARate)
{
  TParamAlternativeItem *AI;
  int in_zad, paramCnt;
  double b, t, v, I11, I1;
  double b_cr, t_cr, v_cr;

  double b_n_f1n, b_n_f1b, b_n_f2n, b_n_f2b, b_n_f3n, b_n_f3b;
  double t_n_f1n, t_n_f1b, t_n_f2n, t_n_f2b, t_n_f3n, t_n_f3b;
  double v_n_f1n, v_n_f1b, v_n_f2n, v_n_f2b, v_n_f3n, v_n_f3b;

  b_cr=0;
  t_cr=0;
  v_cr=0;
  I11 = 0.0;

  int type_metod = opt_sadacha->get_type_metod();
  TDynamicArray *mDel = new TDynamicArray;
  if(type_metod==PRIBLJ2)
  {
    paramCnt = f_ParamAlt->Count;
    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      b_n_f1n = AI->B_F1N;
      b_n_f1b = AI->B_F1B;
      b_n_f2n = AI->B_F2N;
      b_n_f2b = AI->B_F2B;
      b_n_f3n = AI->B_F3N;
      b_n_f3b = AI->B_F3B;

      t_n_f1n = AI->T_F1N;
      t_n_f1b = AI->T_F1B;
      t_n_f2n = AI->T_F2N;
      t_n_f2b = AI->T_F2B;
      t_n_f3n = AI->T_F3N;
      t_n_f3b = AI->T_F3B;

      v_n_f1n = AI->V_F1N;
      v_n_f1b = AI->V_F1B;
      v_n_f2n = AI->V_F2N;
      v_n_f2b = AI->V_F2B;
      v_n_f3n = AI->V_F3N;
      v_n_f3b = AI->V_F3B;

      b = (b_n_f1n+b_n_f1b+b_n_f2n+b_n_f2b+b_n_f3n+b_n_f3b)/6.0;

      t = (t_n_f1n+t_n_f1b+t_n_f2n+t_n_f2b+t_n_f3n+t_n_f3b)/6.0;

      v = (v_n_f1n+v_n_f1b+v_n_f2n+v_n_f2b+v_n_f3n+v_n_f3b)/6.0;

      switch(opt_sadacha->type_sadacha)
      {
           case ZAD_1:switch(opt_sadacha->type_ogr)
                    {
                     case 1: v_cr=v_cr+ v;
                             in_zad=3;
                             break;
                     case 2: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 3: v_cr=v_cr+ v;
                             t_cr=t_cr+ t;
                             in_zad=6;
                            break;
                     case 4:break;
                     case 5: v_cr=v_cr+ v;
                             in_zad=3;
                            break;
                     case 6: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 7: v_cr=v_cr+ v;
                             t_cr=t_cr+ t;
                             in_zad=6;
                             break;
                     }
              break;
           case ZAD_2:switch(opt_sadacha->type_ogr)
                    {
                     case 1: v_cr=v_cr+ v;
                             in_zad=3;
                             break;
                     case 2: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 3: v_cr=v_cr+ v;
                             b_cr=b_cr+ (1-b);
                             in_zad=5;
                             break;
                     case 4: break;
                     case 5: v_cr=v_cr+ v;
                             in_zad=3;
                             break;
                     case 6: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 7: v_cr=v_cr+ v;
                             b_cr=b_cr+ (1-b);
                             in_zad=5;
                             break;
                    }
              break;
           case ZAD_3:switch(opt_sadacha->type_ogr)
                    {
                     case 1: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 2: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 3: b_cr=b_cr+ (1-b);
                             t_cr=t_cr+ t;
                             in_zad=4;
                             break;
                     case 4: break;
                     case 5: b_cr=b_cr+ (1-b);
                             in_zad=1;
                             break;
                     case 6: t_cr=t_cr+ t;
                             in_zad=2;
                             break;
                     case 7: b_cr=b_cr+ (1-b);
                             t_cr=t_cr+ t;
                             in_zad=4;
                             break;
                    }
              break;
      }
    }
    if(paramCnt > 0)
    {
      b_cr = b_cr/paramCnt;
      t_cr = t_cr/paramCnt;
      v_cr = v_cr/paramCnt;
    }

    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      b_n_f1n = AI->B_F1N;
      b_n_f1b = AI->B_F1B;
      b_n_f2n = AI->B_F2N;
      b_n_f2b = AI->B_F2B;
      b_n_f3n = AI->B_F3N;
      b_n_f3b = AI->B_F3B;

      t_n_f1n = AI->T_F1N;
      t_n_f1b = AI->T_F1B;
      t_n_f2n = AI->T_F2N;
      t_n_f2b = AI->T_F2B;
      t_n_f3n = AI->T_F3N;
      t_n_f3b = AI->T_F3B;

      v_n_f1n = AI->V_F1N;
      v_n_f1b = AI->V_F1B;
      v_n_f2n = AI->V_F2N;
      v_n_f2b = AI->V_F2B;
      v_n_f3n = AI->V_F3N;
      v_n_f3b = AI->V_F3B;

      b = (b_n_f1n+b_n_f1b+b_n_f2n+b_n_f2b+b_n_f3n+b_n_f3b)/6.0;

      t = (t_n_f1n+t_n_f1b+t_n_f2n+t_n_f2b+t_n_f3n+t_n_f3b)/6.0;

      v = (v_n_f1n+v_n_f1b+v_n_f2n+v_n_f2b+v_n_f3n+v_n_f3b)/6.0;

      if(in_zad==1)
      {
        if (b_cr == 0) continue;
        I11=(1-b)/b_cr;
      }
      if(in_zad==2)
      {
        if (t_cr == 0) continue;
        I11=t/t_cr;
      }
      if(in_zad==3)
      {
        if(v_cr == 0) continue;
        I11=v/v_cr;
      }
      if(in_zad==4)
      {
        if( (b_cr == 0) || (t_cr == 0) ) continue;
        I11=0.5*((1-b)/b_cr+t/t_cr);
      }
      if(in_zad==5)
      {
        if( (b_cr == 0) || (v_cr == 0) ) continue;
        I11=0.5*((1-b)/b_cr+v/v_cr);
      }
      if(in_zad==6)
      {
        if( (v_cr == 0) || (t_cr == 0) ) continue;
        I11=0.5*(v/v_cr+t/t_cr);
      }  

      I1=random(100)*1.0;
      if ( (I1 - I11*ARate) < 0.0 )
          mDel->Append(AI);
    }
  }
  if(type_metod==PRIBLJ1)
  {
    paramCnt = f_ParamAlt->Count;
    for (int i = 0; i <= paramCnt - 1; i++)
    {
      AI = f_ParamAlt->Items[i];
      I1 = random(100)*1.0;
      if ( (I1 - ARate) < 0.0 )
         mDel->Append(AI);
    }
  }

  for (int i = 0; i <= mDel->Count - 1; i++)
  {
    if (f_ParamAlt->Count > 1)
      f_ParamAlt->Delete2(mDel->Items[i]);
  }
  delete mDel;
}

void TPartialDecisionItem::proverka_nud()
{
  double t, v;
  TParamAlternativeItem *AI;

  TDynamicArray *mDel = new TDynamicArray;
  for (int i = 0; i <= f_ParamAlt->Count - 1; i++)
  {
	AI = f_ParamAlt->Items[i];
	if (!mDel->Find(AI))
	{
	  t = AI->T;
	  v = AI->V;
	  switch(opt_sadacha->type_t_v())
      {
        case 1:
          if (f_Parent->CheckOzenk_TFE_t(this, t))
            mDel->Append(AI);
          break;

        case 2:
          if (f_Parent->CheckOzenk_TFE_v(this, v))
            mDel->Append(AI);
          break;

        case 3:
          if (f_Parent->CheckOzenk_TFE_t(this, t) || f_Parent->CheckOzenk_TFE_v(this, v))
            mDel->Append(AI);
          break;
      }
    }
  }
  for (int i = 0; i <= mDel->Count - 1; i++)
    f_ParamAlt->Delete2(mDel->Items[i]);
  delete mDel;
}

void TPartialDecisionItem::proverka_nud_fuz()
{
  double t, v;
  double t_n_f1n, t_n_f1b, t_n_f2n, t_n_f2b, t_n_f3n, t_n_f3b;
  double v_n_f1n, v_n_f1b, v_n_f2n, v_n_f2b, v_n_f3n, v_n_f3b;
  TParamAlternativeItem *AI;

  TDynamicArray *mDel = new TDynamicArray;
  for (int i = 0; i <= f_ParamAlt->Count - 1; i++)
  {
    AI = f_ParamAlt->Items[i];
    if (!mDel->Find(AI))
    {
      t_n_f1n = AI->T_F1N;
      t_n_f1b = AI->T_F1B;
      t_n_f2n = AI->T_F2N;
      t_n_f2b = AI->T_F2B;
      t_n_f3n = AI->T_F3N;
      t_n_f3b = AI->T_F3B;
      t = (t_n_f1n+t_n_f1b+t_n_f2n+t_n_f2b+t_n_f3n+t_n_f3b)/6;

      v_n_f1n = AI->V_F1N;
      v_n_f1b = AI->V_F1B;
      v_n_f2n = AI->V_F2N;
      v_n_f2b = AI->V_F2B;
      v_n_f3n = AI->V_F3N;
      v_n_f3b = AI->V_F3B;
      v = (v_n_f1n+v_n_f1b+v_n_f2n+v_n_f2b+v_n_f3n+v_n_f3b)/6;

	  switch(opt_sadacha->type_t_v())
      {
        case 1:
          if (f_Parent->CheckOzenk_TFE_t(this, t))
            mDel->Append(AI);
          break;

        case 2:
          if (f_Parent->CheckOzenk_TFE_v(this, v))
            mDel->Append(AI);
          break;

        case 3:
          if (f_Parent->CheckOzenk_TFE_t(this, t) || f_Parent->CheckOzenk_TFE_v(this, v))
            mDel->Append(AI);
          break;
      }
    }
  }
  for (int i = 0; i <= mDel->Count - 1; i++)
    f_ParamAlt->Delete2(mDel->Items[i]);
  delete mDel;
}





void TPartialDecisionItem::InitDecision(TPredicateTreeItem *AWorkItem)
{
   f_WorkItem = AWorkItem;
   f_ParamAlt->Clear();
}

void TPartialDecisionItem::Make()
{
   DoDecision();
   Proverka_NUOpt();
}

void TPartialDecisionItem::sovm_naz(int ind)
{
  char str[1024], str_next[1024];
}

int TPartialDecisionItem::GetOptZadachaTypeOgrForNUOpt()
{
  int res = opt_sadacha->type_ogr;
  if ( f_Parent->f_Owner->OptOgrSovm  )
  {
	if ( f_Parent->f_Owner->FOgrSovmArray->IsCheckObj() )
	  res -= 4;
	f_Parent->f_Owner->FOgrSovmArray->CheckObj(f_WorkItem);
  }
  return res;
}



//------------------------ TPartialDecision --------------------------------
TPartialDecision::TPartialDecision(TZadacha* AOwner)
{
  f_Type_Char = 0;
  f_CheckNud = false;
  f_List = new TList;
  f_Owner = AOwner;
}

TPartialDecision::~TPartialDecision()
{
  FreeList();
  delete f_List;
}

void TPartialDecision::FreeList()
{
   TPartialDecisionItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPartialDecisionItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}


TPartialDecisionItem* TPartialDecision::FindPartialDecisionItemByParentID(int AID)
{
   TPartialDecisionItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPartialDecisionItem*>(f_List->Items[i]);
      if (Item->WorkItem->ParentID == AID)
        return Item;
   }
   return NULL;
}


TPartialDecisionItem* TPartialDecision::GetNew(TPredicateTreeItem* APTItem)
{
   TPartialDecisionItem* Item = new TPartialDecisionItem(this);
   Item->InitDecision(APTItem);
   f_List->Add(Item);
   return Item;
}

bool TPartialDecision::FreeItem(TPartialDecisionItem* AItem)
{
   int idx =  f_List->IndexOf(AItem);
   if (idx >= 0)
   {
      delete AItem;
      f_List->Delete(idx);
   }
   return (idx >= 0);
}


void TPartialDecision::Clear()
{
  FreeList();
}


int __fastcall TPartialDecision::GetCount()
{
   return f_List->Count;
}

TPartialDecisionItem* __fastcall TPartialDecision::GetItems(int AIndex)
{
    TPartialDecisionItem* res = NULL;
    if ( (AIndex >= 0) && (AIndex <= f_List->Count - 1))
       res = static_cast<TPartialDecisionItem*>(f_List->Items[AIndex]);
    return res;
}


TPartialDecisionItem* TPartialDecision::PullAlternate(TPartialDecisionItem* AItem)
{
   int m_id;
   TPartialDecisionItem* Item;
   m_id = AItem->WorkItem->ParentID;
   for( int j = 0; j <= f_List->Count - 1; j++)
   {
     Item = static_cast<TPartialDecisionItem*>(f_List->Items[j]);
     if( (Item->WorkItem->ParentID == m_id) && (Item != AItem) )
     {
       CopyAlternateParam(AItem, Item);
       return Item;
     }
   }
   return NULL;
}


TPartialDecisionItem* TPartialDecision::FindPartialDecisionItemByTFEID(int AID)
{
   TPartialDecisionItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TPartialDecisionItem*>(f_List->Items[i]);
      for (int j = 0; j <= Item->WorkItem->Count -1; j++)
      {
        if (Item->WorkItem->TFE_ID[j] == AID)
          return Item;
      }
   }
   return NULL;
}




bool TPartialDecision::CheckOzenk_TFE_t(TPartialDecisionItem* AI, double AValue)
{
  return f_Owner->CheckOzenk_TFE_t(AI->WorkItem, AValue);
}


bool TPartialDecision::CheckOzenk_TFE_v(TPartialDecisionItem* AI, double AValue)
{
  return f_Owner->CheckOzenk_TFE_v(AI->WorkItem, AValue);
}







