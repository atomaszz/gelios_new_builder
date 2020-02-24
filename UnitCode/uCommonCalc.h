//---------------------------------------------------------------------------

#ifndef uCommonCalcH
#define uCommonCalcH
//---------------------------------------------------------------------------
         /*  ‘ормулы дл€ расчета параметров Ё Ќ  */
void calc_RAB(double b1,double t1,double v1,double *b,double *t,double *v);
void calc_RAB_2(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v);
void calc_RASV_SIM(double b1,double t1,double v1,double b2,double t2,double v2,char *pred,double *b,double *t,double *v);
void calc_RAB_2par_AND(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v);
void calc_RAB_2par_OR(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v);
void calc_DIAGN(double b1,double t1,double v1,double p,double k11,double k00,double td,double vd,double *b,double *t,double *v);
void calc_DIAGN_2(double b1,double t1,double v1,double k11,double k00,double td,double vd,double *b,double *t,double *v);
void calc_WHILE_DO(double b1,double t1,double v1,double pe,double p11,double p00,double td,double vd,double *b,double *t,double *v);
void calc_RASV(double b1,double t1,double v1,double b2,double t2,double v2,double pe,double p11,double p00,double td,double vd,double *b,double *t,double *v);


void calc_RAB_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);

           //  char *b1,char *t1,char *v1,char *b,char *t,char *v);
void calc_RAB_2_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);

void calc_RASV_SIM_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,
  char *pred,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);


void calc_RAB_2par_AND_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);

void calc_RAB_2par_OR_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);

void calc_DIAGN_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_p_el_f, double p_el_f1n, double p_el_f1b,
  double a2_p_el_f, double p_el_f2n, double p_el_f2b, double a3_p_el_f, double p_el_f3n, double p_el_f3b,
  double a1_p11_f, double p11_f1n, double p11_f1b,
  double a2_p11_f, double p11_f2n, double p11_f2b, double a3_p11_f, double p11_f3n, double p11_f3b,
  double a1_p00_f, double p00_f1n, double p00_f1b,
  double a2_p00_f, double p00_f2n, double p00_f2b, double a3_p00_f, double p00_f3n, double p00_f3b,
  double a1_td_f, double td_f1n, double td_f1b,
  double a2_td_f, double td_f2n, double td_f2b, double a3_td_f, double td_f3n, double td_f3b,
  double a1_vd_f, double vd_f1n, double vd_f1b,
  double a2_vd_f, double vd_f2n, double vd_f2b, double a3_vd_f, double vd_f3n, double vd_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);

void calc_DIAGN_2_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_k11_f, double k11_f1n, double k11_f1b,
  double a2_k11_f, double k11_f2n, double k11_f2b, double a3_k11_f, double k11_f3n, double k11_f3b,
  double a1_k00_f, double k00_f1n, double k00_f1b,
  double a2_k00_f, double k00_f2n, double k00_f2b, double a3_k00_f, double k00_f3n, double k00_f3b,
  double a1_tf_f, double tf_f1n, double tf_f1b,
  double a2_tf_f, double tf_f2n, double tf_f2b, double a3_tf_f, double tf_f3n, double tf_f3b,
  double a1_vf_f, double vf_f1n, double vf_f1b,
  double a2_vf_f, double vf_f2n, double vf_f2b, double a3_vf_f, double vf_f3n, double vf_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);


void calc_WHILE_DO_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_p_el_f, double p_el_f1n, double p_el_f1b,
  double a2_p_el_f, double p_el_f2n, double p_el_f2b, double a3_p_el_f, double p_el_f3n, double p_el_f3b,
  double a1_p11_f, double p11_f1n, double p11_f1b,
  double a2_p11_f, double p11_f2n, double p11_f2b, double a3_p11_f, double p11_f3n, double p11_f3b,
  double a1_p00_f, double p00_f1n, double p00_f1b,
  double a2_p00_f, double p00_f2n, double p00_f2b, double a3_p00_f, double p00_f3n, double p00_f3b,
  double a1_td_f, double td_f1n, double td_f1b,
  double a2_td_f, double td_f2n, double td_f2b, double a3_td_f, double td_f3n, double td_f3b,
  double a1_vd_f, double vd_f1n, double vd_f1b,
  double a2_vd_f, double vd_f2n, double vd_f2b, double a3_vd_f, double vd_f3n, double vd_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);


void calc_RASV_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,
  double a1_p_el_f, double p_el_f1n, double p_el_f1b,
  double a2_p_el_f, double p_el_f2n, double p_el_f2b, double a3_p_el_f, double p_el_f3n, double p_el_f3b,
  double a1_p11_f, double p11_f1n, double p11_f1b,
  double a2_p11_f, double p11_f2n, double p11_f2b, double a3_p11_f, double p11_f3n, double p11_f3b,
  double a1_p00_f, double p00_f1n, double p00_f1b,
  double a2_p00_f, double p00_f2n, double p00_f2b, double a3_p00_f, double p00_f3n, double p00_f3b,
  double a1_td_f, double td_f1n, double td_f1b,
  double a2_td_f, double td_f2n, double td_f2b, double a3_td_f, double td_f3n, double td_f3b,
  double a1_vd_f, double vd_f1n, double vd_f1b,
  double a2_vd_f, double vd_f2n, double vd_f2b, double a3_vd_f, double vd_f3n, double vd_f3b,
  double *a1_b_f, double *b_f1n, double *b_f1b,
  double *a2_b_f, double *b_f2n, double *b_f2b, double *a3_b_f, double *b_f3n, double *b_f3b,
  double *a1_t_f, double *t_f1n, double *t_f1b,
  double *a2_t_f, double *t_f2n, double *t_f2b, double *a3_t_f, double *t_f3n, double *t_f3b,
  double *a1_v_f, double *v_f1n, double *v_f1b,
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b);



//----------------------------------------------------------------------------------------------------
bool domin_P_B(double b1,double b2);
bool domin_P_BT(double b1,double b2,double t1,double t2);
bool domin_P_BV(double b1,double b2,double v1,double v2);
bool domin_P_BTV(double b1,double b2,double t1,double t2,double v1,double v2);
bool domin_P_B_S(double b1,double b2,char *S1,char *S2);
bool domin_P_BT_S(double b1,double b2,double t1,double t2,char *S1,char *S2);
bool domin_P_BV_S(double b1,double b2,double v1,double v2,char *S1,char *S2);
bool domin_P_BTV_S(double b1,double b2,double t1,double t2,double v1,double v2,char *S1,char *S2);


bool domin_P_B_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b);
       //char *b1,char *b2);


bool domin_P_BT_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b);


bool domin_P_BV_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b);


bool domin_P_BTV_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b);


bool domin_P_BS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,char *S1,char *S2);


bool domin_P_BTS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,char *S1,char *S2);

bool domin_P_BVS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,char *S1,char *S2);


bool domin_P_BTVS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
  double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
  double a1_b2_f, double b2_f1n, double b2_f1b,
  double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
  double a1_t1_f, double t1_f1n, double t1_f1b,
  double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
  double a1_t2_f, double t2_f1n, double t2_f1b,
  double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,
  double a1_v1_f, double v1_f1n, double v1_f1b,
  double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
  double a1_v2_f, double v2_f1n, double v2_f1b,
  double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,char *S1,char *S2);

int domin_S(char *S1, char *S2);
int unpack_sostav(char *S);

#endif
