//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include "uOzenkTFE.h"
#include "uIMRIncl_all.h"
#include "opim_f.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TOzenkTFE::TOzenkTFE(TPartialDecision* APartialDecision)
{
  f_PartialDecision = APartialDecision;
  f_ozenk = new TDischargedMassiv(0.0);
  f_ozenk1 = new TDischargedMassiv(0.0);
  f_ozenk0 = new TDischargedMassiv(0.0);
  f_ListPredicateTreeItem = new TList;
}

TOzenkTFE::~TOzenkTFE()
{
  delete f_ozenk;
  delete f_ozenk1;
  delete f_ozenk0;
  delete f_ListPredicateTreeItem;
}

void TOzenkTFE::AddPredicateTree(TPredicateTreeItem* ANode)
{
  f_ListPredicateTreeItem->Add(ANode);
}

void TOzenkTFE::FillMassiv(TBaseShape* ATFE)
{
  TParamAlternative* Alt;
  TParamAlternativeItem *OI;
  TPartialDecisionItem* Item = new TPartialDecisionItem(f_PartialDecision);
  Alt = Item->ParamAlt;
  TParamAlternative* S = ATFE->ParamAlt;
  if (S)
  {
    for(int i = 0; i <= S->Count - 1 ; i++)
    {
       OI = S->Items[i];
       Alt->AddItem(OI->Clone());
    }
    Item->Proverka_NUOpt();

    f_ozenk->Val[ATFE->ID] = Alt->Count;
    f_ozenk0->Val[ATFE->ID] = Alt->Count;
    f_ozenk1->Val[ATFE->ID] = 0.0;
  }  
  delete  Item;
}

void TOzenkTFE::InitMassiv()
{
  TPredicateTreeItem* Item;
  for(int i = 0; i <= f_ListPredicateTreeItem->Count - 1; i++)
  {
    Item = static_cast<TPredicateTreeItem*>(f_ListPredicateTreeItem->Items[i]);
	for(int j = 0; j <= Item->Count - 1; j++)
	{
	  TBaseShape* C = Item->TFE[j];
	  if (C)
		FillMassiv(C);
	}
  }
}

void TOzenkTFE::OzenkItem(TPredicateTreeItem* AItem)
{
  double M3,M1,M2,M22,N1,N2,N22,min,max,r2,K,K1,K2,MM3,MM1,MM2,MM22;
  int n1,n2,n3,in,i5,D;

  n1 = AItem->TFE_ID[0];
  n2 = AItem->TFE_ID[1];
  n3 = AItem->TFE_ID[2];
  if ( (AItem->TypeWorkShape == 4) ||
	(AItem->TypeWorkShape == 5) ||
	(AItem->TypeWorkShape == 7) ||
	(AItem->TypeWorkShape == 8) )
  {
	int sn = n2;
	n2 = n3;
	n3 = sn;
	//ой как криво
  }

  M1 = f_ozenk->DoubleValue(n1);  M2 = f_ozenk->DoubleValue(n2);  M22 = f_ozenk->DoubleValue(n3);
  MM1= f_ozenk0->DoubleValue(n1); MM2 = f_ozenk0->DoubleValue(n2); MM22 = f_ozenk0->DoubleValue(n3);
  N1 = f_ozenk1->DoubleValue(n1); N2 = f_ozenk1->DoubleValue(n2); N22 = f_ozenk1->DoubleValue(n3);
  if(f_PartialDecision->Type_Char == PROP)
	K1 = 1;
  else K1 = 1.4;

  int num_parent = AItem->ParentID;

  switch(opt_sadacha->type_sadacha)
  {
    case ZAD_1:
    case ZAD_2:
    case ZAD_3:switch(opt_sadacha->type_ogr)//задача по В
                    {
                     case 0:D=1;break;//только по В
                     case 1:
                     case 2:D=2;break;//критерий T
                     case 3:D=3;break;//критерий V и T
                     case 4:D=1;break;//только по В
                     case 5:
                     case 6:D=2;break;//критерий T
                     case 7:D=3;break;//критерий V и T
                    }
              break;

    case ZAD_4://обобщенные задачи
    case ZAD_5:
    case ZAD_6: D=3;break;
  }

  if( D ==1 )
  {
    f_ozenk->Val[num_parent] = 1.0;
    return;
  }

  switch(AItem->TypeWorkShape)
  {
       case RAB:
       case RAB_FAKE:

       if(f_ozenk->Val[num_parent]!=0)
          f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(M1+f_ozenk->DoubleValue(num_parent));
       else  f_ozenk->Val[num_parent]=M1;
          M3=M1;
         if(f_ozenk0->Val[num_parent]!=0)
          f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(MM1+f_ozenk0->DoubleValue(num_parent));
       else  f_ozenk0->Val[num_parent]=MM1;
          MM3=MM1;K=1;
          break;
       case RAB_POSL:
       case RAB_2par_AND:
       case RAB_2par_OR:
          M3=M1*M2;
         if(M2<M1){min=M2; max=M1;}
	 else {min=M1;max=M2;}
	r2=pow(0.57,log(min)/(double)(D-1.0));
	if(max!=min)r2=M3*(r2-0.02*r2*(1-pow(0.5,max-min)));
        else r2=r2*M3;
    //    M5=r2+f_ozenk->Val[num_parent];
        if(f_ozenk->Val[num_parent]!=0)
        f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(r2+f_ozenk->DoubleValue(num_parent));
        else  f_ozenk->Val[num_parent]=r2;
           MM3=MM1*MM2;
         if(MM2<MM1){min=MM2; max=MM1;}
	 else {min=MM1;max=MM2;}
	r2=pow(0.57,log(min)/(double)(D-1.0));
	if(max!=min)r2=MM3*(r2-0.02*r2*(1-pow(0.5,max-min)));
        else r2=r2*MM3;
    //    M5=r2+f_ozenk->Val[num_parent];
        if(f_ozenk0->Val[num_parent]!=0)
        f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(r2+f_ozenk0->DoubleValue(num_parent));
        else  f_ozenk0->Val[num_parent]=r2;
             K=1.2;
                 break;
       case DIAGN:
       case DIAGN_2:
       case PROV_IF:
       case WHILE_DO:
       case WHILE_DO_2:
       case DO_UNTIL:
       case DO_UNTIL_2:
        M3=M1*M22;
 	if(M1==1) r2=pow(0.49+0.04* (double)D,log(M22))*M3;
	else r2=M3*pow(0.333,log(M22)/log((double)D*3.0))*(1.0-(0.9/(double)D)*(1-pow(0.8,log(M1))));
        if(f_ozenk->Val[num_parent]!=0)
        f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)D))*(r2+f_ozenk->DoubleValue(num_parent));
        else f_ozenk->Val[num_parent]= r2;
         MM3=MM1*MM22;
 	if(MM1==1) r2=pow(0.49+0.04* (double)D,log(MM22))*MM3;
	else r2=MM3*pow(0.333,log(MM22)/log((double)D*3.0))*(1.0-(0.9/(double)D)*(1-pow(0.8,log(MM1))));
        if(f_ozenk0->Val[num_parent]!=0)
        f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)D))*(r2+f_ozenk0->DoubleValue(num_parent));
        else f_ozenk0->Val[num_parent]= r2;
        K=1.3;
         break;
       case RASV:
       case DO_WHILE_DO:
       case DO_WHILE_DO_2:
         M3=M1*M2*M22;
         if(M1==1) r2=pow(0.49+0.04*(double)D,log(M22))*M3;
	 else r2=M3*pow(0.333,log(M22)/log((double)D*3.0))*(1.0-(0.9/(double)D)*(1.0-pow(0.8,log(M1))))*(1-(1.4/(double)D)*(1-pow(0.8,log(M2))));  //4.4
         if(M22==1)r2=0.97*M3;
         if(f_ozenk->Val[num_parent]!=0)
         f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)D))*(r2+f_ozenk->DoubleValue(num_parent));
         else  f_ozenk->Val[num_parent]=r2;
         MM3=MM1*MM2*MM22;
         if(MM1==1) r2=pow(0.49+0.04*(double)D,log(MM22))*MM3;
	 else r2=MM3*pow(0.333,log(MM22)/log((double)D*3.0))*(1.0-(0.9/(double)D)*(1.0-pow(0.8,log(MM1))))*(1-(1.4/(double)D)*(1-pow(0.8,log(MM2))));  //4.4
         if(MM22==1)r2=0.97*MM3;
         if(f_ozenk0->Val[num_parent]!=0)
         f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)D))*(r2+f_ozenk0->DoubleValue(num_parent));
         else  f_ozenk0->Val[num_parent]=r2;
         K=1.3;
         break;

    case RASV_SIM: //для подмножеств альтернатив
          i5 = 0;
          TBaseShape *B = AItem->TFE[2];
          if (B && B->ParamAlt)
          {
            if (B->ParamAlt->Items[0]->CheckPLG)
              i5 = 1;
          }
          if(i5==1)
           {if(f_ozenk->Val[num_parent]!=0)
            f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(M1+f_ozenk->DoubleValue(num_parent));
            else f_ozenk->Val[num_parent]=M1; M3=M1;}
         else
           {if(f_ozenk->Val[num_parent]!=0)
            f_ozenk->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(M2+f_ozenk->DoubleValue(num_parent));
            else f_ozenk->Val[num_parent]=M2; M3=M2;}
   //      if(strcmp(s.c_str(),"1")==0)
          if(i5==0)
           {if(f_ozenk0->Val[num_parent]!=0)
            f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(MM1+f_ozenk0->DoubleValue(num_parent));
            else f_ozenk0->Val[num_parent]=MM1; MM3=MM1;}
         else
           {if(f_ozenk0->Val[num_parent]!=0)
            f_ozenk0->Val[num_parent]=(1.0-pow(0.5,(double)(D)))*(MM2+f_ozenk->DoubleValue(num_parent));
            else f_ozenk0->Val[num_parent]=MM2; MM3=MM2;}
            K=1;
   //         char_form->Table1->Edit();
  //       if(ozenk1[n1]>ozenk1[n2])
  //          char_form->Table1->FieldByName("PREDICAT")->AsString="0";
  //        else char_form->Table1->FieldByName("PREDICAT")->AsString="1";
         break;
    }
    if(num_parent != 0 && ( M3 < 5 || M3/f_ozenk->DoubleValue(num_parent) < 1.2) )
    {
      f_ozenk->Val[num_parent] = M3;
      f_ozenk1->Val[num_parent] = f_ozenk1->DoubleValue(num_parent) + N1 + N2 + N22 + D*K*K1*M3*0.004/3;  //021106
    }
      else{
         M3 = M3* (f_ozenk0->DoubleValue(num_parent) * 1.0)/(f_ozenk->DoubleValue(num_parent) * 1.0);
         f_ozenk->Val[num_parent]=f_ozenk0->DoubleValue(num_parent);
         f_ozenk1->Val[num_parent]=f_ozenk1->DoubleValue(num_parent)+N1+N2+N22+D*K*K1*M3*0.004;
		 }


}

void TOzenkTFE::Ozenk()
{
  TPredicateTreeItem* Item;
  for(int i = 0; i <= f_ListPredicateTreeItem->Count - 1; i++)
  {
    Item = static_cast<TPredicateTreeItem*>(f_ListPredicateTreeItem->Items[i]);
    OzenkItem(Item);
  }
}

double TOzenkTFE::ValueOzenk(int APos)
{
  return f_ozenk->DoubleValue(APos);
}

double TOzenkTFE::ValueOzenk1(int APos)
{
  return f_ozenk1->DoubleValue(APos);
}

