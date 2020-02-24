//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCommonCalc.h"

#include "opim_f.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
void calc_RAB(double b1,double t1,double v1,double *b,double *t,double *v)
{
  *b = b1;
  *t = t1;
  *v = v1;
}

//------------------------------------------------------------------------------
void calc_RAB_2(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v)
{
  *b = b1 * b2;
  *t = t1 + t2;
  *v = v1 + v2;
}
//------------------------------------------------------------------------------
void calc_RASV_SIM(double b1,double t1,double v1,double b2,double t2,double v2,char *pred, double *b,double *t,double *v)
{
  if( strcmp(pred, "1") == 0 )
  {
	*b = b1;
	*t = t1;
	*v = v1;
  }
  else
  {
	*b = b2;
	*t = t2;
	*v = v2;
  }
}
//------------------------------------------------------------------------------

void calc_RAB_2par_AND(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v)
{
  *b = b1 * b2;
  *t = std::max(t1,t2);
  *v = v1 + v2;
}
//------------------------------------------------------------------------------
void calc_RAB_2par_OR(double b1,double t1,double v1,double b2,double t2,double v2,double *b,double *t,double *v)
{
  *b = 1-(1-b1)*(1-b2);
  *t = std::min(t1,t2);
  *v = v1+v2;
}
//------------------------------------------------------------------------------
//контроль работоспособности
void calc_DIAGN(double b1,double t1,double v1,double pe,double p11,double p00,double td,double vd,double *b,double *t,double *v)
{
  //pe-вероятность того, что контролируемый элемент работоспособен
  double B0,B2;
  B0=pe*(1-p11)+(1-pe)*p00;
  B2=b1*(1-p11)+(1-b1)*p00;
  *b=pe*p11+B0*b1*p11/(1-B2);
  *t=td+B0*(td+t1)/(1-B2);
  *v=vd+B0*(vd+v1)/(1-B2);

}
//------------------------------------------------------------------------------
//развилка
void calc_RASV(double b1,double t1,double v1,double b2,double t2,double v2,double pe,double p11,double p00,double td,double vd,double *b,double *t,double *v)
{
  //pe-вероятность того, что контролируемый элемент работоспособен

  *b=pe*p11*b1+(1-pe)*p00*b2;
  *t=td+(pe*p11+(1-pe)*(1-p00))*t1+(pe*(1-p11)+(1-pe)*p00)*t2;
  *v=vd+(pe*p11+(1-pe)*(1-p00))*v1+(pe*(1-p11)+(1-pe)*p00)*v2;
}
//------------------------------------------------------------------------------

//функциональный контроль
void calc_DIAGN_2(double b1,double t1,double v1,double k11,double k00,double td,double vd,double *b,double *t,double *v)
{
  double L;
  L = b1*(1-k11)+(1-b1)*k00;
  *b = (b1*k11)/(1-L);
  *t = (t1+td)/(1-L);
  *v = (v1+vd)/(1-L);
}
//------------------------------------------------------------------------------
//Цикл WHILE_DO
void calc_WHILE_DO(double b1,double t1,double v1,double pe,double p11,double p00,double td,double vd,double *b,double *t,double *v)
{
  double b0, b2, d2;
  b0 = pe*(1-p11)+(1-pe)*p00;
  b2 = b1*(1-p11)+(1-b1)*p00;
  d2 = 1.0/(1-b2);

  *b=pe*p11+b0*b1*p11*d2;
  *t=t1+(td+t1)*b0*d2;
  *v=v1+(vd+v1)*b0*d2;
}
//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)
{
  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n; *b_f1b=b1_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n;
  *b_f2b=b1_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n; *b_f3b=b1_f3b;
  *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
  *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n; *v_f1b=v1_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n;
  *v_f2b=v1_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n; *v_f3b=v1_f3b;
}

//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)

{

  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n*b2_f1n; *b_f1b=b1_f1b*b2_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n*b2_f2n;
  *b_f2b=b1_f2b*b2_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n*b2_f3n; *b_f3b=b1_f3b*b2_f3b;
  *a1_t_f=a1_t1_f; *t_f1n=t1_f1n+t2_f1n; *t_f1b=t1_f1b+t2_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n+t2_f2n;
  *t_f2b=t1_f2b+t2_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n+t2_f3n; *t_f3b=t1_f3b+t2_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n+v2_f1n; *v_f1b=v1_f1b+v2_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n+v2_f2n;
  *v_f2b=v1_f2b+v2_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n+v2_f3n; *v_f3b=v1_f3b+v2_f3b;

}
//------------------------------------------------------------------------------

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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)

{
  if(strcmp(pred,"1")==0)
  {
    *a1_b_f=a1_b1_f; *b_f1n=b1_f1n; *b_f1b=b1_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n;
    *b_f2b=b1_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n; *b_f3b=b1_f3b;
    *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
    *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
    *a1_v_f=a1_v1_f; *v_f1n=v1_f1n; *v_f1b=v1_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n;
    *v_f2b=v1_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n; *v_f3b=v1_f3b;
  }
  else
  {
    *a1_b_f=a1_b2_f; *b_f1n=b2_f1n; *b_f1b=b2_f1b; *a2_b_f=a2_b2_f; *b_f2n=b2_f2n;
    *b_f2b=b2_f2b; *a3_b_f=a3_b2_f; *b_f3n=b2_f3n; *b_f3b=b2_f3b;
    *a1_t_f=a1_t2_f; *t_f1n=t2_f1n; *t_f1b=t2_f1b; *a2_t_f=a2_t2_f; *t_f2n=t2_f2n;
    *t_f2b=t2_f2b; *a3_t_f=a3_t2_f; *t_f3n=t2_f3n; *t_f3b=t2_f3b;
    *a1_v_f=a1_v2_f; *v_f1n=v2_f1n; *v_f1b=v2_f1b; *a2_v_f=a2_v2_f; *v_f2n=v2_f2n;
    *v_f2b=v2_f2b; *a3_v_f=a3_v2_f; *v_f3n=v2_f3n; *v_f3b=v2_f3b;
  }
}

//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)

{
  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n*b2_f1n; *b_f1b=b1_f1b*b2_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n*b2_f2n;
  *b_f2b=b1_f2b*b2_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n*b2_f3n; *b_f3b=b1_f3b*b2_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n+v2_f1n; *v_f1b=v1_f1b+v2_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n+v2_f2n;
  *v_f2b=v1_f2b+v2_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n+v2_f3n; *v_f3b=v1_f3b+v2_f3b;

  if((t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b) >(t2_f1n+t1_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b))
  {
    *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
    *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
  }
  else
  {
    *a1_t_f=a1_t2_f; *t_f1n=t2_f1n; *t_f1b=t2_f1b; *a2_t_f=a2_t2_f; *t_f2n=t2_f2n;
    *t_f2b=t2_f2b; *a3_t_f=a3_t2_f; *t_f3n=t2_f3n; *t_f3b=t2_f3b;
  }
}
//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)
{
  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n*b2_f1n; *b_f1b=b1_f1b*b2_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n*b2_f2n;
  *b_f2b=b1_f2b*b2_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n*b2_f3n; *b_f3b=b1_f3b*b2_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n+v2_f1n; *v_f1b=v1_f1b+v2_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n+v2_f2n;
  *v_f2b=v1_f2b+v2_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n+v2_f3n; *v_f3b=v1_f3b+v2_f3b;

  if((t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b) <(t2_f1n+t1_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b))
  {
    *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
    *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
  }
  else
  {
    *a1_t_f=a1_t2_f; *t_f1n=t2_f1n; *t_f1b=t2_f1b; *a2_t_f=a2_t2_f; *t_f2n=t2_f2n;
    *t_f2b=t2_f2b; *a3_t_f=a3_t2_f; *t_f3n=t2_f3n; *t_f3b=t2_f3b;
  }
}

//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)
{
  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n; *b_f1b=b1_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n;
  *b_f2b=b1_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n; *b_f3b=b1_f3b;
  *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
  *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n; *v_f1b=v1_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n;
  *v_f2b=v1_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n; *v_f3b=v1_f3b;
}

//------------------------------------------------------------------------------
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)

{
  double B1,B2,L1,L2,L12,L22,L13,L23,
      C1,C2,C12,C22,C13,C23;
  if((1-k11_f1b) >=k00_f1n)B1=b1_f1n; else B1=b1_f1b;
  if((1-k11_f1n) >=k00_f1b)B2=b1_f1b; else B2=b1_f1n;
  L1=b1_f1n*(1-k11_f1n)+(1-b1_f1n)*k00_f1n;
  L2=b1_f1b*(1-k11_f1b)+(1-b1_f1b)*k00_f1b;
  L12=b1_f2n*(1-k11_f2n)+(1-b1_f2n)*k00_f2n;
  L22=b1_f2b*(1-k11_f2b)+(1-b1_f2b)*k00_f2b;
  L13=b1_f3n*(1-k11_f3n)+(1-b1_f3n)*k00_f3n;
  L23=b1_f3b*(1-k11_f3b)+(1-b1_f3b)*k00_f3b;
  C1=B1*(1-k11_f1b)+(1-B1)*k00_f1n;
  C2=B2*(1-k11_f1n)+(1-B2)*k00_f1b;
  C12=B1*(1-k11_f2b)+(1-B1)*k00_f2n;
  C22=B2*(1-k11_f2n)+(1-B2)*k00_f2b;
  C13=B1*(1-k11_f3b)+(1-B1)*k00_f3n;
  C23=B2*(1-k11_f3n)+(1-B2)*k00_f3b;

  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n*k11_f1n/(1-L1); *b_f1b=b1_f1b*k11_f1b/(1-L2);
  *a2_b_f=a2_b1_f; *b_f2n=b1_f2n*k11_f2n/(1-L12);
  *b_f2b=b1_f2b*k11_f2b/(1-L22); *a3_b_f=a3_b1_f;
  *b_f3n=b1_f3n*k11_f3n/(1-L13); *b_f3b=b1_f3b*k11_f3b/(1-L23);

  *a1_t_f=a1_t1_f; *t_f1n=(t1_f1n+tf_f1n)/(1-C1);
  *t_f1b=(t1_f1b+tf_f1b)/(1-C2); *a2_t_f=a2_t1_f;
  *t_f2n=(t1_f2n+tf_f2n)/(1-C12); *t_f2b=(t1_f2b+tf_f2b)/(1-C22);
  *a3_t_f=a3_t1_f; *t_f3n=(t1_f3n+tf_f3n)/(1-C13);
  *t_f3b=(t1_f3b+tf_f3b)/(1-C23);

  *a1_v_f=a1_v1_f; *v_f1n=(v1_f1n+vf_f1n)/(1-C1);
  *v_f1b=(v1_f1b+vf_f1b)/(1-C2); *a2_v_f=a2_v1_f;
  *v_f2n=(v1_f2n+vf_f2n)/(1-C12); *v_f2b=(v1_f2b+vf_f2b)/(1-C22);
  *a3_v_f=a3_v1_f; *v_f3n=(v1_f3n+vf_f3n)/(1-C13);
  *v_f3b=(v1_f3b+vf_f3b)/(1-C23);

}
//------------------------------------------------------------------------------
//Цикл WHILE_DO
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)

{
  *a1_b_f=a1_b1_f; *b_f1n=b1_f1n; *b_f1b=b1_f1b; *a2_b_f=a2_b1_f; *b_f2n=b1_f2n;
  *b_f2b=b1_f2b; *a3_b_f=a3_b1_f; *b_f3n=b1_f3n; *b_f3b=b1_f3b;
  *a1_t_f=a1_t1_f; *t_f1n=t1_f1n; *t_f1b=t1_f1b; *a2_t_f=a2_t1_f; *t_f2n=t1_f2n;
  *t_f2b=t1_f2b; *a3_t_f=a3_t1_f; *t_f3n=t1_f3n; *t_f3b=t1_f3b;
  *a1_v_f=a1_v1_f; *v_f1n=v1_f1n; *v_f1b=v1_f1b; *a2_v_f=a2_v1_f; *v_f2n=v1_f2n;
  *v_f2b=v1_f2b; *a3_v_f=a3_v1_f; *v_f3n=v1_f3n; *v_f3b=v1_f3b;
}

//------------------------------------------------------------------------------
//развилка
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
  double *a2_v_f, double *v_f2n, double *v_f2b, double *a3_v_f, double *v_f3n, double *v_f3b)
{
  double P11,P00,PE;
  *a1_b_f=a1_b1_f;
  if(p11_f1n*b1_f1n >= p00_f1n*b2_f1n)*b_f1n=p_el_f1n*p11_f1n*b1_f1n+(1-p_el_f1n)*p00_f1n*b2_f1n;
  else *b_f1n=p_el_f1b*p11_f1n*b1_f1n+(1-p_el_f1b)*p00_f1n*b2_f1n;
  if(p11_f1b*b1_f1b >= p00_f1b*b2_f1b)*b_f1b=p_el_f1b*p11_f1b*b1_f1b+(1-p_el_f1b)*p00_f1b*b2_f1b;
  else *b_f1b=p_el_f1n*p11_f1b*b1_f1b+(1-p_el_f1n)*p00_f1b*b2_f1b;
  *a2_b_f=a2_b1_f;
  if(p11_f2n*b1_f2n >= p00_f2n*b2_f2n)*b_f2n=p_el_f2n*p11_f2n*b1_f2n+(1-p_el_f2n)*p00_f2n*b2_f2n;
  else *b_f2n=p_el_f2b*p11_f2n*b1_f2n+(1-p_el_f2b)*p00_f2n*b2_f2n;
  if(p11_f2b*b1_f2b >= p00_f2b*b2_f2b)*b_f2b=p_el_f2b*p11_f2b*b1_f2b+(1-p_el_f2b)*p00_f2b*b2_f2b;
  else *b_f2b=p_el_f2n*p11_f2b*b1_f2b+(1-p_el_f2n)*p00_f2b*b2_f2b;
  *a3_b_f=a3_b1_f;
  if(p11_f3n*b1_f3n >= p00_f3n*b2_f3n)*b_f3n=p_el_f3n*p11_f3n*b1_f3n+(1-p_el_f3n)*p00_f3n*b2_f3n;
  else *b_f3n=p_el_f3b*p11_f3n*b1_f3n+(1-p_el_f3b)*p00_f3n*b2_f3n;
  if(p11_f3b*b1_f3b >= p00_f3b*b2_f3b)*b_f3b=p_el_f3b*p11_f3b*b1_f3b+(1-p_el_f3b)*p00_f3b*b2_f3b;
  else *b_f3b=p_el_f3n*p11_f3b*b1_f3b+(1-p_el_f3n)*p00_f3b*b2_f3b;

  *a1_t_f=a1_t1_f;
  if(t1_f1n >=t2_f1n){P11=p11_f1n; P00=p00_f1b;}
    else { P11=p11_f1b;P00=p00_f1n;}
  if(t2_f1n+P11*(t1_f1n-t2_f1n)>=t1_f1n+P11*(t2_f1n-t1_f1n))
    PE=p_el_f1n; else PE=p_el_f1b;
  *t_f1n=td_f1n+(PE*P11+(1-PE)*(1-P00))*t1_f1n+ (PE*(1-P11)+(1-PE)*P00)*t2_f1n;
  if(t1_f1b >=t2_f1b){P11=p11_f1b;P00=p00_f1n;}
    else { P11=p11_f1n;P00=p00_f1b;}
  if(t2_f1b+P11*(t1_f1b-t2_f1b)>=t1_f1b+P11*(t2_f1b-t1_f1b))
    PE=p_el_f1b; else PE=p_el_f1n;
  *t_f1b=td_f1b+(PE*P11+(1-PE)*(1-P00))*t1_f1b+ (PE*(1-P11)+(1-PE)*P00)*t2_f1b;

  *a2_t_f=a2_t1_f;
  if(t1_f2n >=t2_f2n){P11=p11_f2n;P00=p00_f2b;}
    else { P11=p11_f2b;P00=p00_f2n;}
  if(t2_f2n+P11*(t1_f2n-t2_f2n)>=t1_f2n+P11*(t2_f2n-t1_f2n))
    PE=p_el_f2n; else PE=p_el_f2b;
  *t_f2n=td_f2n+(PE*P11+(1-PE)*(1-P00))*t1_f2n+ (PE*(1-P11)+(1-PE)*P00)*t2_f2n;
  if(t1_f2b >=t2_f2b){P11=p11_f2b;P00=p00_f2n;}
    else { P11=p11_f2n;P00=p00_f2b;}
  if(t2_f2b+P11*(t1_f2b-t2_f2b)>=t1_f2b+P11*(t2_f2b-t1_f2b))
    PE=p_el_f2b; else PE=p_el_f2n;
  *t_f2b=td_f2b+(PE*P11+(1-PE)*(1-P00))*t1_f2b+ (PE*(1-P11)+(1-PE)*P00)*t2_f2b;

  *a3_t_f=a3_t1_f;
  if(t1_f3n >=t2_f3n){P11=p11_f3n;P00=p00_f3b;}
    else { P11=p11_f3b;P00=p00_f3n;}
  if(t2_f3n+P11*(t1_f3n-t2_f3n)>=t1_f3n+P11*(t2_f3n-t1_f3n))
    PE=p_el_f3n; else PE=p_el_f3b;
  *t_f3n=td_f3n+(PE*P11+(1-PE)*(1-P00))*t1_f3n+ (PE*(1-P11)+(1-PE)*P00)*t2_f3n;
  if(t1_f3b >=t2_f3b){P11=p11_f3b;P00=p00_f3n;}
    else { P11=p11_f3n;P00=p00_f3b;}
  if(t2_f3b+P11*(t1_f3b-t2_f3b)>=t1_f3b+P11*(t2_f3b-t1_f3b))
    PE=p_el_f3b; else PE=p_el_f3n;
  *t_f3b=td_f3b+(PE*P11+(1-PE)*(1-P00))*t1_f3b+ (PE*(1-P11)+(1-PE)*P00)*t2_f3b;

  *a1_v_f=a1_v1_f;
  if(v1_f1n >=v2_f1n){P11=p11_f1n;P00=p00_f1b;}
    else { P11=p11_f1b;P00=p00_f1n;}
  if(v2_f1n+P11*(v1_f1n-v2_f1n)>=v1_f1n+P11*(v2_f1n-v1_f1n))
    PE=p_el_f1n; else PE=p_el_f1b;
  *v_f1n=vd_f1n+(PE*P11+(1-PE)*(1-P00))*v1_f1n+ (PE*(1-P11)+(1-PE)*P00)*v2_f1n;
  if(v1_f1b >=v2_f1b){P11=p11_f1b;P00=p00_f1n;}
    else { P11=p11_f1n;P00=p00_f1b;}
  if(v2_f1b+P11*(v1_f1b-v2_f1b)>=v1_f1b+P11*(v2_f1b-v1_f1b))
    PE=p_el_f1b; else PE=p_el_f1n;
  *v_f1b=vd_f1b+(PE*P11+(1-PE)*(1-P00))*v1_f1b+ (PE*(1-P11)+(1-PE)*P00)*v2_f1b;

  *a2_v_f=a2_v1_f;
  if(v1_f2n >=v2_f2n){P11=p11_f2n;P00=p00_f2b;}
    else {P11=p11_f2b;P00=p00_f2n;}
  if(v2_f2n+P11*(v1_f2n-v2_f2n)>=v1_f2n+P11*(v2_f2n-v1_f2n))
    PE=p_el_f2n; else PE=p_el_f2b;
  *v_f2n=vd_f2n+(PE*P11+(1-PE)*(1-P00))*v1_f2n+ (PE*(1-P11)+(1-PE)*P00)*v2_f2n;
  if(v1_f2b >=v2_f2b){P11=p11_f2b;P00=p00_f2n;}
    else { P11=p11_f2n;P00=p00_f2b;}
  if(v2_f2b+P11*(v1_f2b-v2_f2b)>=v1_f2b+P11*(v2_f2b-v1_f2b))
    PE=p_el_f2b; else PE=p_el_f2n;
  *v_f2b=vd_f2b+(PE*P11+(1-PE)*(1-P00))*v1_f2b+ (PE*(1-P11)+(1-PE)*P00)*v2_f2b;

  *a3_v_f=a3_v1_f;
  if(v1_f3n >=v2_f3n){P11=p11_f3n;P00=p00_f3b;}
	else { P11=p11_f3b;P00=p00_f3n;}
  if(v2_f3n+P11*(v1_f3n-v2_f3n)>=v1_f3n+P11*(v2_f3n-v1_f3n))
	PE=p_el_f3n; else PE=p_el_f3b;
  *v_f3n=vd_f3n+(PE*P11+(1-PE)*(1-P00))*v1_f3n+ (PE*(1-P11)+(1-PE)*P00)*v2_f3n;
  if(v1_f3b >=v2_f3b){P11=p11_f3b;P00=p00_f3n;}
	else { P11=p11_f3n;P00=p00_f3b;}
  if(v2_f3b+P11*(v1_f3b-v2_f3b)>=v1_f3b+P11*(v2_f3b-v1_f3b))
	PE=p_el_f3b; else PE=p_el_f3n;
  *v_f3b=vd_f3b+(PE*P11+(1-PE)*(1-P00))*v1_f3b+ (PE*(1-P11)+(1-PE)*P00)*v2_f3b;

}


//-------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool domin_P_B(double b1,double b2)
{
//если частичное решение с b1 доминирует
//частичное решение с b2, то удаляем част. решение b2
if(b1 >= b2) return true;
else return false;
}
//---------------------------------------------------------------------------
bool domin_P_B_S(double b1,double b2, char *S1, char *S2)
{
//если частичное решение с b1 доминирует
//частичное решение с b2, то удаляем част. решение b2
		  if(domin_S(S1,S2)==2)return true;
		  if(domin_S(S1,S2)==0)return false;
		  if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&(b1 >= b2)) return true;
				 else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BT(double b1,double b2,double t1,double t2)
{
if(b1 >= b2  && t1<=t2) return true;
else return false;
}
//---------------------------------------------------------------------------
bool domin_P_BT_S(double b1,double b2,double t1,double t2,char *S1, char *S2)
{
if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&(b1 >= b2  && t1<=t2))return true;
 else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BV(double b1,double b2,double v1,double v2)
{
if(b1 >= b2  && v1<=v2)
return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BV_S(double b1,double b2,double v1,double v2,char *S1, char *S2)
{

          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&(b1 >= b2  && v1<=v2))return true;
else return false;
}
//---------------------------------------------------------------------------
bool domin_P_BTV(double b1,double b2,double t1,double t2,double v1,double v2)
{
if( b1 >= b2 && t1<=t2 && v1<=v2) return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BTV_S(double b1,double b2,double t1,double t2,double v1,double v2,char *S1, char *S2)
{

          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&( b1 >= b2 && t1<=t2 && v1<=v2)) return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_B_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b)
{

if((b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b) >= (b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b))
//if( (s11+s21+s31+s41+s51+s61) > (s12+s22+s32+s42+s52+s62) )
   return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,char *S1, char *S2)
{

          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&((b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b) >= (b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b)))
          return true;
      else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BT_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
double a1_t1_f, double t1_f1n, double t1_f1b,
double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
double a1_t2_f, double t2_f1n, double t2_f1b,
double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b)
{

double B1,B2,T1,T2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
T1=t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b; //(d11+d21+d31+d41+d51+d61);
T2=t2_f1n+t2_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b; //(d12+d22+d32+d42+d52+d62);

//если сумма по всем альфа-уровням больше , то решение доминирует
if( B1 >= B2 && T1 <= T2)return true;
else return false;
}
//---------------------------------------------------------------------------
bool domin_P_BTS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
double a1_t1_f, double t1_f1n, double t1_f1b,
double a2_t1_f, double t1_f2n, double t1_f2b, double a3_t1_f, double t1_f3n, double t1_f3b,
double a1_t2_f, double t2_f1n, double t2_f1b,
double a2_t2_f, double t2_f2n, double t2_f2b, double a3_t2_f, double t2_f3n, double t2_f3b,char *S1, char *S2)
{
double B1,B2,T1,T2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
T1=t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b; //(d11+d21+d31+d41+d51+d61);
T2=t2_f1n+t2_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b; //(d12+d22+d32+d42+d52+d62);

          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&( B1 >= B2 && T1 <= T2))return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BV_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
double a1_v1_f, double v1_f1n, double v1_f1b,
double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
double a1_v2_f, double v2_f1n, double v2_f1b,
double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b)
{

double B1,B2,V1,V2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
V1=v1_f1n+v1_f1b+v1_f2n+v1_f2b+v1_f3n+v1_f3b; //(d11+d21+d31+d41+d51+d61);
V2=v2_f1n+v2_f1b+v2_f2n+v2_f2b+v2_f3n+v2_f3b; //(d12+d22+d32+d42+d52+d62);

if( B1 >= B2 && V1 <= V2)
   return true;
else return false;
}
//---------------------------------------------------------------------------

bool domin_P_BVS_fuz(double a1_b1_f, double b1_f1n, double b1_f1b,
double a2_b1_f, double b1_f2n, double b1_f2b, double a3_b1_f, double b1_f3n, double b1_f3b,
double a1_b2_f, double b2_f1n, double b2_f1b,
double a2_b2_f, double b2_f2n, double b2_f2b, double a3_b2_f, double b2_f3n, double b2_f3b,
double a1_v1_f, double v1_f1n, double v1_f1b,
double a2_v1_f, double v1_f2n, double v1_f2b, double a3_v1_f, double v1_f3n, double v1_f3b,
double a1_v2_f, double v2_f1n, double v2_f1b,
double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,char *S1, char *S2)
{

double B1,B2,V1,V2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
V1=v1_f1n+v1_f1b+v1_f2n+v1_f2b+v1_f3n+v1_f3b; //(d11+d21+d31+d41+d51+d61);
V2=v2_f1n+v2_f1b+v2_f2n+v2_f2b+v2_f3n+v2_f3b; //(d12+d22+d32+d42+d52+d62);


          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&( B1 >= B2 && V1 <= V2))
   return true;
else return false;
}
//---------------------------------------------------------------------------

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
double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b)
{

double B1,B2,V1,V2,T1,T2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
T1=t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b; //(d11+d21+d31+d41+d51+d61);
T2=t2_f1n+t2_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b;
V1=v1_f1n+v1_f1b+v1_f2n+v1_f2b+v1_f3n+v1_f3b; //(d11+d21+d31+d41+d51+d61);
V2=v2_f1n+v2_f1b+v2_f2n+v2_f2b+v2_f3n+v2_f3b;


if(B1 >= B2 && T1<=T2 && V1<=V2) return true;
else return false;
}
//---------------------------------------------------------------------------

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
double a2_v2_f, double v2_f2n, double v2_f2b, double a3_v2_f, double v2_f3n, double v2_f3b,char *S1, char *S2)
{

double B1,B2,V1,V2,T1,T2;
B1=b1_f1n+b1_f1b+b1_f2n+b1_f2b+b1_f3n+b1_f3b; //(s11+s21+s31+s41+s51+s61);
B2=b2_f1n+b2_f1b+b2_f2n+b2_f2b+b2_f3n+b2_f3b; //(s12+s22+s32+s42+s52+s62);
T1=t1_f1n+t1_f1b+t1_f2n+t1_f2b+t1_f3n+t1_f3b; //(d11+d21+d31+d41+d51+d61);
T2=t2_f1n+t2_f1b+t2_f2n+t2_f2b+t2_f3n+t2_f3b;
V1=v1_f1n+v1_f1b+v1_f2n+v1_f2b+v1_f3n+v1_f3b; //(d11+d21+d31+d41+d51+d61);
V2=v2_f1n+v2_f1b+v2_f2n+v2_f2b+v2_f3n+v2_f3b;

          if(domin_S(S1,S2)==2)return true;
          if(domin_S(S1,S2)==0)return false;
          if((domin_S(S1,S2)==1||domin_S(S1,S2)==3)&&(B1 >= B2 && T1<=T2 && V1<=V2)) return true;
else return false;
}



int domin_S(char *S1, char *S2)
{
  int i1,I,J;
  char n1[1024],n2[1024];
  int n3[1024],n4[1024],n40[1024],n30[1024];
  char *p;
  // num=opt_sadacha->StringGrid1->ColCount;
  n1[0]='\0';
  n2[0]='\0';
  for(i1=0;i1 < opt_sadacha->OptSovm->HiCol() + 1 ;i1++){n3[i1]=0;n4[i1]=0;
  n30[i1]=0;n40[i1]=0;}
   p=S1;
     for(;;)
      {i1=0; while( *p!=';'&&*p!=':'&&*p!='\0') n1[i1++]=*(p++); n1[i1]='\0';
       p++;i1=0; while( *p!=';'&&*p!=':'&&*p!='\0') n2[i1++]=*(p++); n2[i1]='\0';
       n3[StrToInt(atoi(n1))]=StrToInt(atoi(n2));
       if(*p!='\0'){p++;continue;}
        else break;
        }
   p=S2;
     for(;;)
      {i1=0; while(  *p!=';'&&*p!=':'&&*p!='\0') n1[i1++]=*(p++); n1[i1]='\0';
       p++;i1=0; while( *p!=';'&&*p!=':'&&*p!='\0') n2[i1++]=*(p++); n2[i1]='\0';
       n4[StrToInt(atoi(n1))]=StrToInt(atoi(n2));
       if(*p!='\0'){p++;continue;}
        else break;
        }

      int k=0,k1=0,k2;
       for (I = 0; I < opt_sadacha->OptSovm->HiRow()+ 1 ; I++)
        {
         for (J = 0; J <  opt_sadacha->OptSovm->HiCol()+ 1 ; J++)
          {if(opt_sadacha->OptSovm->Items[I][J] != 0 )k++;
          if((opt_sadacha->OptSovm->Items[I][J]!= 0) && (opt_sadacha->OptSovm->Items[I][J] == n4[J])){n40[J] = n4[J];k1++;}}
          if((k1!=k)||(k==0)){k=0;k1=0;continue;}
          else return 2;  //надо удалять безусловно
          }
       k=0;k1=0;
       for (I = 0; I < opt_sadacha->OptSovm->HiRow()+ 1 ; I++)
        {
         for (J = 0; J < opt_sadacha->OptSovm->HiCol()+ 1 ; J++)
          {if(opt_sadacha->OptSovm->Items[I][J] != 0 )k++;
          if((opt_sadacha->OptSovm->Items[I][J] != 0 )&&(opt_sadacha->OptSovm->Items[I][J] == n3[J])){n30[J] = n3[J];k1++;}}
          if((k1!=k)||(k==0)){k=0;k1=0;continue;}
          else return 0;  //нельзя удалять
          }

      k=0,k1=0;k2=0;
       for (J = 0; J < opt_sadacha->OptSovm->HiCol()+ 1 ; J++)
          {if(n30[J]!=0)k++;
//          if(n30[J]!=0&&n30[J]!=n40[J]||n40[J]!=0&&n30[J]!=n40[J])k2++;
          if(n30[J]!=n40[J])k2++;
          if((n30[J]!=0)&&(n30[J]==n40[J]))k1++;}
          if(k2==0) return 3;
          if(k1!=k) return 0;
          else return 1; // надо проверить условие на параметры

  //return 3;
}

int unpack_sostav(char *S)
{
  int i1,I,J;
  char n1[1024],n2[1024];
  int n3[1024];
  char *p;
  n1[0] = '\0';
  n2[0] = '\0';
  p = S;
  for(i1=0;i1 < opt_sadacha->OptSovm->HiCol() + 1 ;i1++)
    n3[i1]=0;
  for(;;)
  {i1=0; while( *p!=';'&&*p!=':'&&*p!='\0') n1[i1++]=*(p++); n1[i1]='\0';
   p++;i1=0; while( *p!=';'&&*p!=':'&&*p!='\0') n2[i1++]=*(p++); n2[i1]='\0';
   n3[StrToInt(atoi(n1))]=StrToInt(atoi(n2));
   if(*p!='\0'){p++;continue;}
    else break;
  }

  int k=0,k1=0;
  for (I = 0; I < opt_sadacha->OptSovm->HiRow()+ 1; I++)
  {
   for (J = 0; J <  opt_sadacha->OptSovm->HiCol()+ 1; J++)
    {if(opt_sadacha->OptSovm->Items[I][J] != 0 )k++;
    if((opt_sadacha->OptSovm->Items[I][J]!= 0)&&(opt_sadacha->OptSovm->Items[I][J] == n3[J]))k1++;}
    if((k1!=k)||(k==0)){k=0;k1=0;continue;}
    else return 0;
    }
  return 1;

}

