//---------------------------------------------------------------------------

#ifndef uParamAlternativeItemH
#define uParamAlternativeItemH
//---------------------------------------------------------------------------
/*

NUMBER
PRED_ISTOR
SOSTAV
NAME
FUNCTION
ELEMENT
PREDICAT
B
T
V
A1_B_F
B_F1N
B_F1B
A2_B_F
B_F2N
B_F2B
A3_B_F
B_F3N
B_F3B
A1_T_F
T_F1N
T_F1B
A2_T_F
T_F2N
T_F2B
A3_T_F
T_F3N
T_F3B
A1_V_F
V_F1N
V_F1B
A2_V_F
V_F2N
V_F2B
A3_V_F
V_F3N
V_F3B
K_11
K_00
T_F
V_F
A1_K11_F
K11_F1N
K11_F1B
A2_K11_F
K11_F2N
K11_F2B
A3_K11_F
K11_F3N
K11_F3B
A1_K00_F
K00_F1N
K00_F1B
A2_K00_F
K00_F2N
K00_F2B
A3_K00_F
K00_F3N
K00_F3B
A1_TF_F
TF_F1N
TF_F1B
A2_TF_F
TF_F2N
TF_F2B
A3_TF_F
TF_F3N
TF_F3B
A1_VF_F
VF_F1N
VF_F1B
A2_VF_F
VF_F2N
VF_F2B
A3_VF_F
VF_F3N
VF_F3B
P_11
P_00
T_D
V_D
A1_P11_F
P11_F1N
P11_F1B
A2_P11_F
P11_F2N
P11_F2B
A3_P11_F
P11_F3N
P11_F3B
A1_P00_F
P00_F1N
P00_F1B
A2_P00_F
P00_F2N
P00_F2B
A3_P00_F
P00_F3N
P00_F3B
A1_TD_F
TD_F1N
TD_F1B
A2_TD_F
TD_F2N
TD_F2B
A3_TD_F
TD_F3N
TD_F3B
A1_VD_F
VD_F1N
VD_F1B
A2_VD_F
VD_F2N
VD_F2B
A3_VD_F
VD_F3N
VD_F3B
TYPE
ELEM_DIAGN
P_DIAGN_EL
A1_P_EL_F
P_EL_F1N
P_EL_F1B
A2_P_EL_F
P_EL_F2N
P_EL_F2B
A3_P_EL_F
P_EL_F3N
P_EL_F3B
SOVM
SOVM0
SOVM1

*/
class TParamAlternativeItem
{
   private:
      int  f_NUMBER;
      AnsiString  f_PRED_ISTOR;
      AnsiString  f_SOSTAV;
      AnsiString  f_NAME;
      AnsiString  f_FUNCTION;
      AnsiString  f_ELEMENT;
      AnsiString  f_PREDICAT;
      double  f_B;
      double  f_T;
      double  f_V;
      double  f_A1_B_F;
      double  f_B_F1N;
      double  f_B_F1B;
      double  f_A2_B_F;
      double  f_B_F2N;
      double  f_B_F2B;
      double  f_A3_B_F;
      double  f_B_F3N;
      double  f_B_F3B;
      double  f_A1_T_F;
      double  f_T_F1N;
      double  f_T_F1B;
      double  f_A2_T_F;
      double  f_T_F2N;
      double  f_T_F2B;
      double  f_A3_T_F;
      double  f_T_F3N;
      double  f_T_F3B;
      double  f_A1_V_F;
      double  f_V_F1N;
      double  f_V_F1B;
      double  f_A2_V_F;
      double  f_V_F2N;
      double  f_V_F2B;
      double  f_A3_V_F;
      double  f_V_F3N;
      double  f_V_F3B;
      double  f_K_11;
      double  f_K_00;
      double  f_T_F;
      double  f_V_F;
      double  f_A1_K11_F;
      double  f_K11_F1N;
      double  f_K11_F1B;
      double  f_A2_K11_F;
      double  f_K11_F2N;
      double  f_K11_F2B;
      double  f_A3_K11_F;
      double  f_K11_F3N;
      double  f_K11_F3B;
      double  f_A1_K00_F;
      double  f_K00_F1N;
      double  f_K00_F1B;
      double  f_A2_K00_F;
      double  f_K00_F2N;
      double  f_K00_F2B;
      double  f_A3_K00_F;
      double  f_K00_F3N;
      double  f_K00_F3B;
      double  f_A1_TF_F;
      double  f_TF_F1N;
      double  f_TF_F1B;
      double  f_A2_TF_F;
      double  f_TF_F2N;
      double  f_TF_F2B;
      double  f_A3_TF_F;
      double  f_TF_F3N;
      double  f_TF_F3B;
      double  f_A1_VF_F;
      double  f_VF_F1N;
      double  f_VF_F1B;
      double  f_A2_VF_F;
      double  f_VF_F2N;
      double  f_VF_F2B;
      double  f_A3_VF_F;
      double  f_VF_F3N;
      double  f_VF_F3B;
      double  f_P_11;
      double  f_P_00;
      double  f_T_D;
      double  f_V_D;
      double  f_A1_P11_F;
      double  f_P11_F1N;
      double  f_P11_F1B;
      double  f_A2_P11_F;
      double  f_P11_F2N;
      double  f_P11_F2B;
      double  f_A3_P11_F;
      double  f_P11_F3N;
      double  f_P11_F3B;
      double  f_A1_P00_F;
      double  f_P00_F1N;
      double  f_P00_F1B;
      double  f_A2_P00_F;
      double  f_P00_F2N;
      double  f_P00_F2B;
      double  f_A3_P00_F;
      double  f_P00_F3N;
      double  f_P00_F3B;
      double  f_A1_TD_F;
      double  f_TD_F1N;
      double  f_TD_F1B;
      double  f_A2_TD_F;
      double  f_TD_F2N;
      double  f_TD_F2B;
      double  f_A3_TD_F;
      double  f_TD_F3N;
      double  f_TD_F3B;
      double  f_A1_VD_F;
      double  f_VD_F1N;
      double  f_VD_F1B;
      double  f_A2_VD_F;
      double  f_VD_F2N;
      double  f_VD_F2B;
      double  f_A3_VD_F;
      double  f_VD_F3N;
      double  f_VD_F3B;
      int  f_TYPE;
      AnsiString  f_ELEM_DIAGN;
      double  f_P_DIAGN_EL;
      double  f_A1_P_EL_F;
      double  f_P_EL_F1N;
      double  f_P_EL_F1B;
      double  f_A2_P_EL_F;
      double  f_P_EL_F2N;
      double  f_P_EL_F2B;
      double  f_A3_P_EL_F;
      double  f_P_EL_F3N;
      double  f_P_EL_F3B;
      double  f_SOVM;
      double  f_SOVM0;
      double  f_SOVM1;
      int f_Tag;
      bool f_CheckPLG;
   public:
      TParamAlternativeItem();
      TParamAlternativeItem* Clone();
      __property int  NUMBER = {read = f_NUMBER, write = f_NUMBER};
      __property AnsiString  PRED_ISTOR = {read = f_PRED_ISTOR, write = f_PRED_ISTOR};
      __property AnsiString  SOSTAV = {read = f_SOSTAV, write = f_SOSTAV};
      __property AnsiString  NAME = {read = f_NAME, write = f_NAME};
//      __property AnsiString  FUNCTION = {read = f_FUNCTION, write = f_FUNCTION};
      __property AnsiString  FUNCTION2 = {read = f_FUNCTION, write = f_FUNCTION};
      __property AnsiString  ELEMENT = {read = f_ELEMENT, write = f_ELEMENT};
      __property AnsiString  PREDICAT = {read = f_PREDICAT, write = f_PREDICAT};
      __property double  B = {read = f_B, write = f_B};
      __property double  T = {read = f_T, write = f_T};
      __property double  V = {read = f_V, write = f_V};
      __property double  A1_B_F = {read = f_A1_B_F, write = f_A1_B_F};
      __property double  B_F1N = {read = f_B_F1N, write = f_B_F1N};
      __property double  B_F1B = {read = f_B_F1B, write = f_B_F1B};
      __property double  A2_B_F = {read = f_A2_B_F, write = f_A2_B_F};
      __property double  B_F2N = {read = f_B_F2N, write = f_B_F2N};
      __property double  B_F2B = {read = f_B_F2B, write = f_B_F2B};
      __property double  A3_B_F = {read = f_A3_B_F, write = f_A3_B_F};
      __property double  B_F3N = {read = f_B_F3N, write = f_B_F3N};
      __property double  B_F3B = {read = f_B_F3B, write = f_B_F3B};
      __property double  A1_T_F = {read = f_A1_T_F, write = f_A1_T_F};
      __property double  T_F1N = {read = f_T_F1N, write = f_T_F1N};
      __property double  T_F1B = {read = f_T_F1B, write = f_T_F1B};
      __property double  A2_T_F = {read = f_A2_T_F, write = f_A2_T_F};
      __property double  T_F2N = {read = f_T_F2N, write = f_T_F2N};
      __property double  T_F2B = {read = f_T_F2B, write = f_T_F2B};
      __property double  A3_T_F = {read = f_A3_T_F, write = f_A3_T_F};
      __property double  T_F3N = {read = f_T_F3N, write = f_T_F3N};
      __property double  T_F3B = {read = f_T_F3B, write = f_T_F3B};
      __property double  A1_V_F = {read = f_A1_V_F, write = f_A1_V_F};
      __property double  V_F1N = {read = f_V_F1N, write = f_V_F1N};
      __property double  V_F1B = {read = f_V_F1B, write = f_V_F1B};
      __property double  A2_V_F = {read = f_A2_V_F, write = f_A2_V_F};
      __property double  V_F2N = {read = f_V_F2N, write = f_V_F2N};
      __property double  V_F2B = {read = f_V_F2B, write = f_V_F2B};
      __property double  A3_V_F = {read = f_A3_V_F, write = f_A3_V_F};
      __property double  V_F3N = {read = f_V_F3N, write = f_V_F3N};
      __property double  V_F3B = {read = f_V_F3B, write = f_V_F3B};
      __property double  K_11 = {read = f_K_11, write = f_K_11};
      __property double  K_00 = {read = f_K_00, write = f_K_00};
      __property double  T_F = {read = f_T_F, write = f_T_F};
      __property double  V_F = {read = f_V_F, write = f_V_F};
      __property double  A1_K11_F = {read = f_A1_K11_F, write = f_A1_K11_F};
      __property double  K11_F1N = {read = f_K11_F1N, write = f_K11_F1N};
      __property double  K11_F1B = {read = f_K11_F1B, write = f_K11_F1B};
      __property double  A2_K11_F = {read = f_A2_K11_F, write = f_A2_K11_F};
      __property double  K11_F2N = {read = f_K11_F2N, write = f_K11_F2N};
      __property double  K11_F2B = {read = f_K11_F2B, write = f_K11_F2B};
      __property double  A3_K11_F = {read = f_A3_K11_F, write = f_A3_K11_F};
      __property double  K11_F3N = {read = f_K11_F3N, write = f_K11_F3N};
      __property double  K11_F3B = {read = f_K11_F3B, write = f_K11_F3B};
      __property double  A1_K00_F = {read = f_A1_K00_F, write = f_A1_K00_F};
      __property double  K00_F1N = {read = f_K00_F1N, write = f_K00_F1N};
      __property double  K00_F1B = {read = f_K00_F1B, write = f_K00_F1B};
      __property double  A2_K00_F = {read = f_A2_K00_F, write = f_A2_K00_F};
      __property double  K00_F2N = {read = f_K00_F2N, write = f_K00_F2N};
      __property double  K00_F2B = {read = f_K00_F2B, write = f_K00_F2B};
      __property double  A3_K00_F = {read = f_A3_K00_F, write = f_A3_K00_F};
      __property double  K00_F3N = {read = f_K00_F3N, write = f_K00_F3N};
      __property double  K00_F3B = {read = f_K00_F3B, write = f_K00_F3B};
      __property double  A1_TF_F = {read = f_A1_TF_F, write = f_A1_TF_F};
      __property double  TF_F1N = {read = f_TF_F1N, write = f_TF_F1N};
      __property double  TF_F1B = {read = f_TF_F1B, write = f_TF_F1B};
      __property double  A2_TF_F = {read = f_A2_TF_F, write = f_A2_TF_F};
      __property double  TF_F2N = {read = f_TF_F2N, write = f_TF_F2N};
      __property double  TF_F2B = {read = f_TF_F2B, write = f_TF_F2B};
      __property double  A3_TF_F = {read = f_A3_TF_F, write = f_A3_TF_F};
      __property double  TF_F3N = {read = f_TF_F3N, write = f_TF_F3N};
      __property double  TF_F3B = {read = f_TF_F3B, write = f_TF_F3B};
      __property double  A1_VF_F = {read = f_A1_VF_F, write = f_A1_VF_F};
      __property double  VF_F1N = {read = f_VF_F1N, write = f_VF_F1N};
      __property double  VF_F1B = {read = f_VF_F1B, write = f_VF_F1B};
      __property double  A2_VF_F = {read = f_A2_VF_F, write = f_A2_VF_F};
      __property double  VF_F2N = {read = f_VF_F2N, write = f_VF_F2N};
      __property double  VF_F2B = {read = f_VF_F2B, write = f_VF_F2B};
      __property double  A3_VF_F = {read = f_A3_VF_F, write = f_A3_VF_F};
      __property double  VF_F3N = {read = f_VF_F3N, write = f_VF_F3N};
      __property double  VF_F3B = {read = f_VF_F3B, write = f_VF_F3B};
      __property double  P_11 = {read = f_P_11, write = f_P_11};
      __property double  P_00 = {read = f_P_00, write = f_P_00};
      __property double  T_D = {read = f_T_D, write = f_T_D};
      __property double  V_D = {read = f_V_D, write = f_V_D};
      __property double  A1_P11_F = {read = f_A1_P11_F, write = f_A1_P11_F};
      __property double  P11_F1N = {read = f_P11_F1N, write = f_P11_F1N};
      __property double  P11_F1B = {read = f_P11_F1B, write = f_P11_F1B};
      __property double  A2_P11_F = {read = f_A2_P11_F, write = f_A2_P11_F};
      __property double  P11_F2N = {read = f_P11_F2N, write = f_P11_F2N};
      __property double  P11_F2B = {read = f_P11_F2B, write = f_P11_F2B};
      __property double  A3_P11_F = {read = f_A3_P11_F, write = f_A3_P11_F};
      __property double  P11_F3N = {read = f_P11_F3N, write = f_P11_F3N};
      __property double  P11_F3B = {read = f_P11_F3B, write = f_P11_F3B};
      __property double  A1_P00_F = {read = f_A1_P00_F, write = f_A1_P00_F};
      __property double  P00_F1N = {read = f_P00_F1N, write = f_P00_F1N};
      __property double  P00_F1B = {read = f_P00_F1B, write = f_P00_F1B};
      __property double  A2_P00_F = {read = f_A2_P00_F, write = f_A2_P00_F};
      __property double  P00_F2N = {read = f_P00_F2N, write = f_P00_F2N};
      __property double  P00_F2B = {read = f_P00_F2B, write = f_P00_F2B};
      __property double  A3_P00_F = {read = f_A3_P00_F, write = f_A3_P00_F};
      __property double  P00_F3N = {read = f_P00_F3N, write = f_P00_F3N};
      __property double  P00_F3B = {read = f_P00_F3B, write = f_P00_F3B};
      __property double  A1_TD_F = {read = f_A1_TD_F, write = f_A1_TD_F};
      __property double  TD_F1N = {read = f_TD_F1N, write = f_TD_F1N};
      __property double  TD_F1B = {read = f_TD_F1B, write = f_TD_F1B};
      __property double  A2_TD_F = {read = f_A2_TD_F, write = f_A2_TD_F};
      __property double  TD_F2N = {read = f_TD_F2N, write = f_TD_F2N};
      __property double  TD_F2B = {read = f_TD_F2B, write = f_TD_F2B};
      __property double  A3_TD_F = {read = f_A3_TD_F, write = f_A3_TD_F};
      __property double  TD_F3N = {read = f_TD_F3N, write = f_TD_F3N};
      __property double  TD_F3B = {read = f_TD_F3B, write = f_TD_F3B};
      __property double  A1_VD_F = {read = f_A1_VD_F, write = f_A1_VD_F};
      __property double  VD_F1N = {read = f_VD_F1N, write = f_VD_F1N};
      __property double  VD_F1B = {read = f_VD_F1B, write = f_VD_F1B};
      __property double  A2_VD_F = {read = f_A2_VD_F, write = f_A2_VD_F};
      __property double  VD_F2N = {read = f_VD_F2N, write = f_VD_F2N};
      __property double  VD_F2B = {read = f_VD_F2B, write = f_VD_F2B};
      __property double  A3_VD_F = {read = f_A3_VD_F, write = f_A3_VD_F};
      __property double  VD_F3N = {read = f_VD_F3N, write = f_VD_F3N};
      __property double  VD_F3B = {read = f_VD_F3B, write = f_VD_F3B};
      __property int  TYPE = {read = f_TYPE, write = f_TYPE};
      __property AnsiString  ELEM_DIAGN = {read = f_ELEM_DIAGN, write = f_ELEM_DIAGN};
      __property double  P_DIAGN_EL = {read = f_P_DIAGN_EL, write = f_P_DIAGN_EL};
      __property double  A1_P_EL_F = {read = f_A1_P_EL_F, write = f_A1_P_EL_F};
      __property double  P_EL_F1N = {read = f_P_EL_F1N, write = f_P_EL_F1N};
      __property double  P_EL_F1B = {read = f_P_EL_F1B, write = f_P_EL_F1B};
      __property double  A2_P_EL_F = {read = f_A2_P_EL_F, write = f_A2_P_EL_F};
      __property double  P_EL_F2N = {read = f_P_EL_F2N, write = f_P_EL_F2N};
      __property double  P_EL_F2B = {read = f_P_EL_F2B, write = f_P_EL_F2B};
      __property double  A3_P_EL_F = {read = f_A3_P_EL_F, write = f_A3_P_EL_F};
      __property double  P_EL_F3N = {read = f_P_EL_F3N, write = f_P_EL_F3N};
      __property double  P_EL_F3B = {read = f_P_EL_F3B, write = f_P_EL_F3B};
      __property double  SOVM = {read = f_SOVM, write = f_SOVM};
      __property double  SOVM0 = {read = f_SOVM0, write = f_SOVM0};
      __property double  SOVM1 = {read = f_SOVM1, write = f_SOVM1};
      __property int Tag = {read = f_Tag, write = f_Tag };
      __property bool CheckPLG = {read = f_CheckPLG, write = f_CheckPLG};

};
#endif
