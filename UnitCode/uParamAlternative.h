//---------------------------------------------------------------------------

#ifndef uParamAlternativeH
#define uParamAlternativeH

#include "uParamAlternativeItem.h"

//---------------------------------------------------------------------------
class TParamAlternative
{
   private:
     TList *f_List;
     void FreeList();
     int __fastcall GetCount();
     TParamAlternativeItem* __fastcall GetItems(int AIndex);
   public:
     TParamAlternative();
     ~TParamAlternative();
     void AddItem(TParamAlternativeItem* AItem);
     void Delete(int AIndex);
     void Delete2(void* APointer);
     void Clear();
     __property int Count = {read = GetCount};
     __property TParamAlternativeItem* Items[int AIndex] = {read = GetItems};

};

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
                                     AnsiString predicat, double sovm, double sovm0, double sovm1);

#endif



