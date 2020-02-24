//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uParamAlternative.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TParamAlternative::TParamAlternative()
{
   f_List = new TList;
}


TParamAlternative::~TParamAlternative()
{
   FreeList();
   delete f_List;
}

void TParamAlternative::FreeList()
{
   TParamAlternativeItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TParamAlternativeItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

void TParamAlternative::Clear()
{
   FreeList();
}

void TParamAlternative::AddItem(TParamAlternativeItem* AItem)
{
   f_List->Add(AItem);
}

void TParamAlternative::Delete(int AIndex)
{
   TParamAlternativeItem* Item = Items[AIndex];
   if (Item)
   {
      delete Item;
      f_List->Delete(AIndex);
   }
}

void TParamAlternative::Delete2(void* APointer)
{
   int index = f_List->IndexOf(APointer);
   Delete(index);
}



int __fastcall TParamAlternative::GetCount()
{
  return f_List->Count;
}

TParamAlternativeItem* __fastcall TParamAlternative::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TParamAlternativeItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TParamAlternativeItem* CreateParamAlternativeItem(char *sostav,char *history,char *name,char *func,char *elem,int type,short number,
                                     double b,double t,double v,
                                     double k11,double k00,double tf,double vf,
                                     double p11,double p00,double td,double vd,
                                     AnsiString elem_diagn,double p_elem,
                                     double a1_b_f, double b_f1n, double b_f1b,
                                     double a2_b_f, double b_f2n, double b_f2b,
                                     double a3_b_f, double b_f3n, double b_f3b,
                                     double a1_t_f, double t_f1n, double t_f1b,
                                     double a2_t_f, double t_f2n, double t_f2b,
                                     double a3_t_f, double t_f3n, double t_f3b,
                                     double a1_v_f, double v_f1n, double v_f1b,
                                     double a2_v_f, double v_f2n, double v_f2b,
                                     double a3_v_f, double v_f3n, double v_f3b,
                                     double a1_k11_f, double k11_f1n, double k11_f1b,
                                     double a2_k11_f, double k11_f2n, double k11_f2b,
                                     double a3_k11_f, double k11_f3n, double k11_f3b,
                                     double a1_k00_f, double k00_f1n, double k00_f1b,
                                     double a2_k00_f, double k00_f2n, double k00_f2b,
                                     double a3_k00_f, double k00_f3n, double k00_f3b,
                                     double a1_tf_f, double tf_f1n, double tf_f1b,
                                     double a2_tf_f, double tf_f2n, double tf_f2b,
                                     double a3_tf_f, double tf_f3n, double tf_f3b,
                                     double a1_vf_f, double vf_f1n, double vf_f1b,
                                     double a2_vf_f, double vf_f2n, double vf_f2b,
                                     double a3_vf_f, double vf_f3n, double vf_f3b,
                                     double a1_p11_f, double p11_f1n, double p11_f1b,
                                     double a2_p11_f, double p11_f2n, double p11_f2b,
                                     double a3_p11_f, double p11_f3n, double p11_f3b,
                                     double a1_p00_f, double p00_f1n, double p00_f1b,
                                     double a2_p00_f, double p00_f2n, double p00_f2b,
                                     double a3_p00_f, double p00_f3n, double p00_f3b,
                                     double a1_td_f, double td_f1n, double td_f1b,
                                     double a2_td_f, double td_f2n, double td_f2b,
                                     double a3_td_f, double td_f3n, double td_f3b,
                                     double a1_vd_f, double vd_f1n, double vd_f1b,
                                     double a2_vd_f, double vd_f2n, double vd_f2b,
                                     double a3_vd_f, double vd_f3n, double vd_f3b,
                                     double a1_p_el_f, double p_el_f1n, double p_el_f1b,
                                     double a2_p_el_f, double p_el_f2n, double p_el_f2b,
                                     double a3_p_el_f, double p_el_f3n, double p_el_f3b,
                                     AnsiString predicat, double sovm, double sovm0, double sovm1)
{
  TParamAlternativeItem* Item = new TParamAlternativeItem;
  Item->SOSTAV = sostav;
  Item->PRED_ISTOR = history;
  Item->NAME = name;
  Item->FUNCTION2 = func;
  Item->ELEMENT = elem;
  Item->TYPE = type;
  Item->NUMBER = number;
  Item->SOVM = sovm;
  Item->SOVM0 = sovm0;
  Item->SOVM1 = sovm0;
  Item->PREDICAT = predicat;

  switch (type)
  {
    case 5:
      Item->B = b;
      Item->T = t;
      Item->V = v;

      Item->A1_B_F = a1_b_f;
      Item->B_F1N = b_f1n;
      Item->B_F1B = b_f1b;
      Item->A2_B_F = a2_b_f;
      Item->B_F2N = b_f2n;
      Item->B_F2B = b_f2b;
      Item->A3_B_F = a3_b_f;
      Item->B_F3N = b_f3n;
      Item->B_F3B = b_f3b;

      Item->A1_T_F = a1_t_f;
      Item->T_F1N = t_f1n;
      Item->T_F1B = t_f1b;
      Item->A2_T_F = a2_t_f;
      Item->T_F2N = t_f2n;
      Item->T_F2B = t_f2b;
      Item->A3_T_F = a3_t_f;
      Item->T_F3N = t_f3n;
      Item->T_F3B = t_f3b;

      Item->A1_V_F = a1_v_f;
      Item->V_F1N = v_f1n;
      Item->V_F1B = v_f1b;
      Item->A2_V_F = a2_v_f;
      Item->V_F2N = v_f2n;
      Item->V_F2B = v_f2b;
      Item->A3_V_F = a3_v_f;
      Item->V_F3N = v_f3n;
      Item->V_F3B = v_f3b;
      break;
    case 7:
      Item->K_11 = k11;
      Item->K_00 = k00;
      Item->T_F = tf;
      Item->V_F = vf;

      Item->A1_K11_F = a1_k11_f;
      Item->K11_F1N = k11_f1n;
      Item->K11_F1B = k11_f1b;
      Item->A2_K11_F = a2_k11_f;
      Item->K11_F2N = k11_f2n;
      Item->K11_F2B = k11_f2b;
      Item->A3_K11_F = a3_k11_f;
      Item->K11_F3N = k11_f3n;
      Item->K11_F3B = k11_f3b;

      Item->A1_K00_F = a1_k00_f;
      Item->K00_F1N = k00_f1n;
      Item->K00_F1B = k00_f1b;
      Item->A2_K00_F = a2_k00_f;
      Item->K00_F2N = k00_f2n;
      Item->K00_F2B = k00_f2b;
      Item->A3_K00_F = a3_k00_f;
      Item->K00_F3N = k00_f3n;
      Item->K00_F3B = k00_f3b;

      Item->A1_TF_F = a1_tf_f;
      Item->TF_F1N = tf_f1n;
      Item->TF_F1B = tf_f1b;
      Item->A2_TF_F = a2_tf_f;
      Item->TF_F2N = tf_f2n;
      Item->TF_F2B = tf_f2b;
      Item->A3_TF_F = a3_tf_f;
      Item->TF_F3N = tf_f3n;
      Item->TF_F3B = tf_f3b;

      Item->A1_VF_F = a1_vf_f;
      Item->VF_F1N = vf_f1n;
      Item->VF_F1B = vf_f1b;
      Item->A2_VF_F = a2_vf_f;
      Item->VF_F2N = vf_f2n;
      Item->VF_F2B = vf_f2b;
      Item->A3_VF_F = a3_vf_f;
      Item->VF_F3N = vf_f3n;
      Item->VF_F3B = vf_f3b;
      break;

    case 6:
      Item->ELEM_DIAGN = elem_diagn;

      Item->P_11 = p11;
      Item->P_00 = p00;
      Item->T_D = td;
      Item->V_D = vd;

      Item->P_DIAGN_EL = p_elem;

      Item->A1_P11_F = a1_p11_f;
      Item->P11_F1N = p11_f1n;
      Item->P11_F1B = p11_f1b;
      Item->A2_P11_F = a2_p11_f;
      Item->P11_F2N = p11_f2n;
      Item->P11_F2B = p11_f2b;
      Item->A3_P11_F = a3_p11_f;
      Item->P11_F3N = p11_f3n;
      Item->P11_F3B = p11_f3b;

      Item->A1_P00_F = a1_p00_f;
      Item->P00_F1N = p00_f1n;
      Item->P00_F1B = p00_f1b;
      Item->A2_P00_F = a2_p00_f;
      Item->P00_F2N = p00_f2n;
      Item->P00_F2B = p00_f2b;
      Item->A3_P00_F = a3_p00_f;
      Item->P00_F3N = p00_f3n;
      Item->P00_F3B = p00_f3b;

      Item->A1_TD_F = a1_td_f;
      Item->TD_F1N = td_f1n;
      Item->TD_F1B = td_f1b;
      Item->A2_TD_F = a2_td_f;
      Item->TD_F2N = td_f2n;
      Item->TD_F2B = td_f2b;
      Item->A3_TD_F = a3_td_f;
      Item->TD_F3N = td_f3n;
      Item->TD_F3B = td_f3b;

      Item->A1_VD_F = a1_vd_f;
      Item->VD_F1N = vd_f1n;
      Item->VD_F1B = vd_f1b;
      Item->A2_VD_F = a2_vd_f;
      Item->VD_F2N = vd_f2n;
      Item->VD_F2B = vd_f2b;
      Item->A3_VD_F = a3_vd_f;
      Item->VD_F3N = vd_f3n;
      Item->VD_F3B = vd_f3b;

      Item->A1_P_EL_F = a1_p_el_f;
      Item->P_EL_F1N = p_el_f1n;
      Item->P_EL_F1B = p_el_f1b;
      Item->A2_P_EL_F = a2_p_el_f;
      Item->P_EL_F2N = p_el_f2n;
      Item->P_EL_F2B = p_el_f2b;
      Item->A3_P_EL_F = a3_p_el_f;
      Item->P_EL_F3N = p_el_f3n;
      Item->P_EL_F3B = p_el_f3b;
      break;

    case 8: Item->PREDICAT = predicat;
  }
  return Item;
}
