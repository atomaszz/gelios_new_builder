//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFmParamAlternative.h"
#include "uIMRIncl_all.h"
#include "uCommonGraph.h"
#include "uGLSSmallFontsDefence.h"
#include "redact_f.h"
#include "ufmParamAlternativeLoader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmParamAlternative *fmParamAlternative;
//---------------------------------------------------------------------------
__fastcall TfmParamAlternative::TfmParamAlternative(TComponent* Owner)
        : TForm(Owner)
{
   TGLSSmallFontsDefence* F = new TGLSSmallFontsDefence(this);
   F->Update();
   delete F; 
}

void ShowParamAlternative(TBaseShape* ATFE, int AParentID, int AType_Char,
  Graphics::TBitmap* AGlp, bool AReadOnly)
{
   Application->CreateForm(__classid(TfmParamAlternative), &fmParamAlternative);
   if (ATFE->Clon)
     fmParamAlternative->TFE = ATFE->Clon;
   else
     fmParamAlternative->TFE = ATFE;
   fmParamAlternative->Type_Char = AType_Char;
   fmParamAlternative->ParentShapeID = AParentID;
   fmParamAlternative->Glp = AGlp;
   fmParamAlternative->FReadOnly = AReadOnly;
   fmParamAlternative->acAdd->Enabled = !AReadOnly;
   fmParamAlternative->acDel->Enabled = !AReadOnly;
   fmParamAlternative->acForm->Enabled = !AReadOnly;
   fmParamAlternative->ShowModal();
   fmParamAlternative->Release();
}


//---------------------------------------------------------------------------
void TfmParamAlternative::StringInit()
{
  int m_type = TFE->TypeShape;
  sgParam->ColCount    = 4;
  sgParam->RowCount    = 2;
  sgParam->FixedRows   = 1;

  SGCells(sgParam, 0, 0, "ÍÀÇÂÀÍÈÅ");
  SGCells(sgParam, 0, 1, "ÔÓÍÊÖÈß");
  SGCells(sgParam, 0, 2, "ÝËÅÌÅÍÒ");
  SGCells(sgParam, 0, 3, "ÑÎÑÒÀÂ");

  if(Type_Char == PROP)
  {
     if (m_type == 5)
     {
       sgParam->ColCount = 7;
       SGCells(sgParam, 0, 4, "B");
       SGCells(sgParam, 0, 5, "T");
       SGCells(sgParam, 0, 6, "V");
     }
     if (m_type == 6)
     {
       sgParam->ColCount = 10;
       SGCells(sgParam, 0, 4, "ÝËÅÌÅÍÒ(äèàãí.)");
       SGCells(sgParam, 0, 5, "Â(äèàãí)");
       SGCells(sgParam, 0, 6, "Ï_11");
       SGCells(sgParam, 0, 7, "Ï_00");
       SGCells(sgParam, 0, 8, "T_ä");
       SGCells(sgParam, 0, 9, "V_ä");
     }
     if (m_type == 7)
     {
       sgParam->ColCount = 8;
       SGCells(sgParam, 0, 4, "K_11");
       SGCells(sgParam, 0, 5, "K_00");
       SGCells(sgParam, 0, 6, "T_Ô");
       SGCells(sgParam, 0, 7, "V_Ô");
     }
     if (m_type == 8)
     {
        sgParam->ColCount = 5;
        SGCells(sgParam, 0, 4, "ÓÑËÎÂÈÅ");
     }
  }

  else if(Type_Char == FUZZY)
  {
    if (m_type == 5)
    {
      sgParam->ColCount = 31;
      SGCells(sgParam, 0, 4, "A1_B_F");
      SGCells(sgParam, 0, 5, "Â_F1N");
      SGCells(sgParam, 0, 6, "Â_F1B");
      SGCells(sgParam, 0, 7, "A2_Â_F");
      SGCells(sgParam, 0, 8, "Â_F2N");
      SGCells(sgParam, 0, 9, "Â_F2B");
      SGCells(sgParam, 0, 10, "A3_B_F");
      SGCells(sgParam, 0, 11, "Â_F3N");
      SGCells(sgParam, 0, 12, "Â_F3B");
      SGCells(sgParam, 0, 13, "A1_T_F");
      SGCells(sgParam, 0, 14, "T_F1N");
      SGCells(sgParam, 0, 15, "T_F1B");
      SGCells(sgParam, 0, 16, "A2_T_F");
      SGCells(sgParam, 0, 17, "T_F2N");
      SGCells(sgParam, 0, 18, "T_F2B");
      SGCells(sgParam, 0, 19, "A3_T_F");
      SGCells(sgParam, 0, 20, "T_F3N");
      SGCells(sgParam, 0, 21, "T_F3B");
      SGCells(sgParam, 0, 22, "A1_V_F");
      SGCells(sgParam, 0, 23, "V_F1N");
      SGCells(sgParam, 0, 24, "V_F1B");
      SGCells(sgParam, 0, 25, "A2_V_F");
      SGCells(sgParam, 0, 26, "V_F2N");
      SGCells(sgParam, 0, 27, "V_F2B");
      SGCells(sgParam, 0, 28, "A3_V_F");
      SGCells(sgParam, 0, 29, "V_F3N");
      SGCells(sgParam, 0, 30, "V_F3B");
    }
    if (m_type == 6)
    {
      sgParam->ColCount = 49;
      SGCells(sgParam, 0, 4, "A1_P_EL_F");
      SGCells(sgParam, 0, 5, "P_EL_F1N");
      SGCells(sgParam, 0, 6, "P_EL_F1B");
      SGCells(sgParam, 0, 7, "A2_P_EL_F");
      SGCells(sgParam, 0, 8, "P_EL_F2N");
      SGCells(sgParam, 0, 9, "P_EL_F2B");
      SGCells(sgParam, 0, 10, "A3_P_EL_F");
      SGCells(sgParam, 0, 11, "P_EL_F3N");
      SGCells(sgParam, 0, 12, "P_EL_F3B");
      SGCells(sgParam, 0, 13, "A1_P11_F");
      SGCells(sgParam, 0, 14, "P11_F1N");
      SGCells(sgParam, 0, 15, "P11_F1B");
      SGCells(sgParam, 0, 16, "A2_P11_F");
      SGCells(sgParam, 0, 17, "P11_F2N");
      SGCells(sgParam, 0, 18, "P11_F2B");
      SGCells(sgParam, 0, 19, "A3_P11_F");
      SGCells(sgParam, 0, 20, "P11_F3N");
      SGCells(sgParam, 0, 21, "P11_F3B");
      SGCells(sgParam, 0, 22, "A1_P00_F");
      SGCells(sgParam, 0, 23, "P00_F1N");
      SGCells(sgParam, 0, 24, "P00_F1B");
      SGCells(sgParam, 0, 25, "A2_P00_F");
      SGCells(sgParam, 0, 26, "P00_F2N");
      SGCells(sgParam, 0, 27, "P00_F2B");
      SGCells(sgParam, 0, 28, "A3_P00_F");
      SGCells(sgParam, 0, 29, "P00_F3N");
      SGCells(sgParam, 0, 30, "P00_F3B");
      SGCells(sgParam, 0, 31, "A1_TD_F");
      SGCells(sgParam, 0, 32, "TD_F1N");
      SGCells(sgParam, 0, 33, "TD_F1B");
      SGCells(sgParam, 0, 34, "A2_TD_F");
      SGCells(sgParam, 0, 35, "TD_F2N");
      SGCells(sgParam, 0, 36, "TD_F2B");
      SGCells(sgParam, 0, 37, "A3_TD_F");
      SGCells(sgParam, 0, 38, "A3_TD_F");
      SGCells(sgParam, 0, 39, "TD_F3B");
      SGCells(sgParam, 0, 40, "A1_VD_F");
      SGCells(sgParam, 0, 41, "VD_F1N");
      SGCells(sgParam, 0, 42, "VD_F1B");
      SGCells(sgParam, 0, 43, "A2_VD_F");
      SGCells(sgParam, 0, 44, "VD_F2N");
      SGCells(sgParam, 0, 45, "VD_F2B");
      SGCells(sgParam, 0, 46, "A3_VD_F");
      SGCells(sgParam, 0, 47, "VD_F3N");
      SGCells(sgParam, 0, 48, "VD_F3B");
    }
    if (m_type == 7)
    {
      sgParam->ColCount = 40;
      SGCells(sgParam, 0, 4, "A1_K11_F");
      SGCells(sgParam, 0, 5, "K11_F1N");
      SGCells(sgParam, 0, 6, "K11_F1B");
      SGCells(sgParam, 0, 7, "A2_K11_F");
      SGCells(sgParam, 0, 8, "K11_F2N");
      SGCells(sgParam, 0, 9, "K11_F2B");
      SGCells(sgParam, 0, 10, "A3_K11_F");
      SGCells(sgParam, 0, 11, "K11_F3N");
      SGCells(sgParam, 0, 12, "K11_F3B");
      SGCells(sgParam, 0, 13, "A1_K00_F");
      SGCells(sgParam, 0, 14, "K00_F1N");
      SGCells(sgParam, 0, 15, "K00_F1B");
      SGCells(sgParam, 0, 16, "A2_K00_F");
      SGCells(sgParam, 0, 17, "K00_F2N");
      SGCells(sgParam, 0, 18, "K00_F2B");
      SGCells(sgParam, 0, 19, "A3_K00_F");
      SGCells(sgParam, 0, 20, "K00_F3N");
      SGCells(sgParam, 0, 21, "K00_F3B");
      SGCells(sgParam, 0, 22, "A1_TF_F");
      SGCells(sgParam, 0, 23, "TF_F1N");
      SGCells(sgParam, 0, 24, "TF_F1B");
      SGCells(sgParam, 0, 25, "A2_TF_F");
      SGCells(sgParam, 0, 26, "TF_F2N");
      SGCells(sgParam, 0, 27, "TF_F2B");
      SGCells(sgParam, 0, 28, "A3_TF_F");
      SGCells(sgParam, 0, 29, "TF_F3N");
      SGCells(sgParam, 0, 30, "TF_F3B");
      SGCells(sgParam, 0, 31, "A1_VF_F");
      SGCells(sgParam, 0, 32, "VF_F1N");
      SGCells(sgParam, 0, 33, "VF_F1B");
      SGCells(sgParam, 0, 34, "A2_VF_F");
      SGCells(sgParam, 0, 35, "VF_F2N");
      SGCells(sgParam, 0, 36, "VF_F2B");
      SGCells(sgParam, 0, 37, "A3_VF_F");
      SGCells(sgParam, 0, 38, "VF_F3N");
      SGCells(sgParam, 0, 39, "VF_F3B");
    }
     if (m_type == 8)
     {
        sgParam->ColCount = 5;
        SGCells(sgParam, 0, 4, "ÓÑËÎÂÈÅ");
     }

  }
}

void TfmParamAlternative::RefreshDataPROP()
{
  TParamAlternativeItem* AI;
  int m_type = TFE->TypeShape;
  sgParam->RowCount    = 1;
  sgParam->RowCount    = 2;
  sgParam->FixedRows   = 1;
  sgParam->Rows[1]->Clear();
  if (TFE->ParamAlt)
  {
    int m_cnt = TFE->ParamAlt->Count;
    for (int i = 0; i <= m_cnt - 1; i++)
    {
       if (i+1 > sgParam->RowCount - 1)
         sgParam->RowCount    = sgParam->RowCount + 1;
       AI = TFE->ParamAlt->Items[i];
       sgParam->Objects[0][1+i] = (TObject*)AI;
       AI->SOSTAV = IntToStr(TFE->ID) + ":" + IntToStr(i+1);
       SGCellsByName(sgParam, 1 + i,  "ÍÀÇÂÀÍÈÅ", AI->NAME);
       SGCellsByName(sgParam, 1 + i,  "ÔÓÍÊÖÈß", AI->FUNCTION2);
       SGCellsByName(sgParam, 1 + i,  "ÝËÅÌÅÍÒ", AI->ELEMENT);
       SGCellsByName(sgParam, 1 + i,  "ÑÎÑÒÀÂ", AI->SOSTAV);

       if (m_type == 5)
       {
         SGCellsByName(sgParam, 1 + i, "B", AI->B);
         SGCellsByName(sgParam, 1 + i, "T", AI->T);
         SGCellsByName(sgParam, 1 + i, "V", AI->V);
       }
       if (m_type == 6)
       {
         SGCellsByName(sgParam, 1 + i, "ÝËÅÌÅÍÒ(äèàãí.)", AI->ELEM_DIAGN);
         SGCellsByName(sgParam, 1 + i, "Â(äèàãí)", AI->P_DIAGN_EL);
         SGCellsByName(sgParam, 1 + i, "Ï_11", AI->P_11);
         SGCellsByName(sgParam, 1 + i, "Ï_00", AI->P_00);
         SGCellsByName(sgParam, 1 + i, "T_ä", AI->T_D);
         SGCellsByName(sgParam, 1 + i, "V_ä", AI->V_D);
       }
       if (m_type == 7)
       {
         SGCellsByName(sgParam, 1 + i, "K_11", AI->K_11);
         SGCellsByName(sgParam, 1 + i, "K_00", AI->K_00);
         SGCellsByName(sgParam, 1 + i, "T_Ô", AI->T_F);
         SGCellsByName(sgParam, 1 + i, "V_Ô", AI->V_F);
       }
       if (m_type == 8)
       {
         SGCellsByName(sgParam, 1 + i, "ÓÑËÎÂÈÅ", AI->PREDICAT);
       }

    }
  }
}

void TfmParamAlternative::RefreshDataFUZZY()
{
  TParamAlternativeItem* AI;
  int m_type = TFE->TypeShape;
  sgParam->RowCount    = 1;
  sgParam->RowCount    = 2;
  sgParam->FixedRows   = 1;
  sgParam->Rows[1]->Clear();
  if (TFE->ParamAlt)
  {
    int m_cnt = TFE->ParamAlt->Count;
    for (int i = 0; i <= m_cnt - 1; i++)
    {
       if (i+1 > sgParam->RowCount - 1)
         sgParam->RowCount    = sgParam->RowCount + 1;
       AI = TFE->ParamAlt->Items[i];
       sgParam->Objects[0][1+i] = (TObject*)AI;
       AI->SOSTAV = IntToStr(TFE->ID) + ":" + IntToStr(i+1);
       SGCellsByName(sgParam, 1 + i,  "ÍÀÇÂÀÍÈÅ", AI->NAME);
       SGCellsByName(sgParam, 1 + i,  "ÔÓÍÊÖÈß", AI->FUNCTION2);
       SGCellsByName(sgParam, 1 + i,  "ÝËÅÌÅÍÒ", AI->ELEMENT);
       SGCellsByName(sgParam, 1 + i,  "ÑÎÑÒÀÂ", AI->SOSTAV);

       if (m_type == 5)
       {
         SGCellsByName(sgParam, 1 + i, "A1_B_F", AI->A1_B_F);
         SGCellsByName(sgParam, 1 + i, "Â_F1N", AI->B_F1N);
         SGCellsByName(sgParam, 1 + i, "Â_F1B", AI->B_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_Â_F", AI->A2_B_F);
         SGCellsByName(sgParam, 1 + i, "Â_F2N", AI->B_F2N);
         SGCellsByName(sgParam, 1 + i, "Â_F2B", AI->B_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_B_F", AI->A3_B_F);
         SGCellsByName(sgParam, 1 + i, "Â_F3N", AI->B_F3N);
         SGCellsByName(sgParam, 1 + i, "Â_F3B", AI->B_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_T_F", AI->A1_T_F);
         SGCellsByName(sgParam, 1 + i, "T_F1N", AI->T_F1N);
         SGCellsByName(sgParam, 1 + i, "T_F1B", AI->T_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_T_F", AI->A2_T_F);
         SGCellsByName(sgParam, 1 + i, "T_F2N", AI->T_F2N);
         SGCellsByName(sgParam, 1 + i, "T_F2B", AI->T_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_T_F", AI->A3_T_F);
         SGCellsByName(sgParam, 1 + i, "T_F3N", AI->T_F3N);
         SGCellsByName(sgParam, 1 + i, "T_F3B", AI->T_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_V_F", AI->A1_V_F);
         SGCellsByName(sgParam, 1 + i, "V_F1N", AI->V_F1N);
         SGCellsByName(sgParam, 1 + i, "V_F1B", AI->V_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_V_F", AI->A2_V_F);
         SGCellsByName(sgParam, 1 + i, "V_F2N", AI->V_F2N);
         SGCellsByName(sgParam, 1 + i, "V_F2B", AI->V_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_V_F", AI->A3_V_F);
         SGCellsByName(sgParam, 1 + i, "V_F3N", AI->V_F3N);
         SGCellsByName(sgParam, 1 + i, "V_F3B", AI->V_F3B);
       }
       if (m_type == 6)
       {
         SGCellsByName(sgParam, 1 + i, "A1_P_EL_F", AI->A1_P_EL_F);
         SGCellsByName(sgParam, 1 + i, "P_EL_F1N", AI->P_EL_F1N);
         SGCellsByName(sgParam, 1 + i, "P_EL_F1B", AI->P_EL_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_P_EL_F", AI->A2_P_EL_F);
         SGCellsByName(sgParam, 1 + i, "P_EL_F2N", AI->P_EL_F2N);
         SGCellsByName(sgParam, 1 + i, "P_EL_F2B", AI->P_EL_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_P_EL_F", AI->A3_P_EL_F);
         SGCellsByName(sgParam, 1 + i, "P_EL_F3N", AI->P_EL_F3N);
         SGCellsByName(sgParam, 1 + i, "P_EL_F3B", AI->P_EL_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_P11_F", AI->A1_P11_F);
         SGCellsByName(sgParam, 1 + i, "P11_F1N", AI->P11_F1N);
         SGCellsByName(sgParam, 1 + i, "P11_F1B", AI->P11_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_P11_F", AI->A2_P11_F);
         SGCellsByName(sgParam, 1 + i, "P11_F2N", AI->P11_F2N);
         SGCellsByName(sgParam, 1 + i, "P11_F2B", AI->P11_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_P11_F", AI->A3_P11_F);
         SGCellsByName(sgParam, 1 + i, "P11_F3N", AI->P11_F3N);
         SGCellsByName(sgParam, 1 + i, "P11_F3B", AI->P11_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_P00_F", AI->A1_P00_F);
         SGCellsByName(sgParam, 1 + i, "P00_F1N", AI->P00_F1N);
         SGCellsByName(sgParam, 1 + i, "P00_F1B", AI->P00_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_P00_F", AI->A2_P00_F);
         SGCellsByName(sgParam, 1 + i, "P00_F2N", AI->P00_F2N);
         SGCellsByName(sgParam, 1 + i, "P00_F2B", AI->P00_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_P00_F", AI->A3_P00_F);
         SGCellsByName(sgParam, 1 + i, "P00_F3N", AI->P00_F3N);
         SGCellsByName(sgParam, 1 + i, "P00_F3B", AI->P00_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_TD_F", AI->A1_TD_F);
         SGCellsByName(sgParam, 1 + i, "TD_F1N", AI->TD_F1N);
         SGCellsByName(sgParam, 1 + i, "TD_F1B", AI->TD_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_TD_F", AI->A2_TD_F);
         SGCellsByName(sgParam, 1 + i, "TD_F2N", AI->TD_F2N);
         SGCellsByName(sgParam, 1 + i, "TD_F2B", AI->TD_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_TD_F", AI->A3_TD_F);
         SGCellsByName(sgParam, 1 + i, "TD_F3N", AI->TD_F3N);
         SGCellsByName(sgParam, 1 + i, "TD_F3B", AI->TD_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_VD_F", AI->A1_VD_F);
         SGCellsByName(sgParam, 1 + i, "VD_F1N", AI->VD_F1N);
         SGCellsByName(sgParam, 1 + i, "VD_F1B", AI->VD_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_VD_F", AI->A2_VD_F);
         SGCellsByName(sgParam, 1 + i, "VD_F2N", AI->VD_F2N);
         SGCellsByName(sgParam, 1 + i, "VD_F2B", AI->VD_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_VD_F", AI->A3_VD_F);
         SGCellsByName(sgParam, 1 + i, "VD_F3N", AI->VD_F3N);
         SGCellsByName(sgParam, 1 + i, "VD_F3B", AI->VD_F3B);
       }
       if (m_type == 7)
       {
         SGCellsByName(sgParam, 1 + i, "A1_K11_F", AI->A1_K11_F);
         SGCellsByName(sgParam, 1 + i, "K11_F1N", AI->K11_F1N);
         SGCellsByName(sgParam, 1 + i, "K11_F1B", AI->K11_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_K11_F", AI->A2_K11_F);
         SGCellsByName(sgParam, 1 + i, "K11_F2N", AI->K11_F2N);
         SGCellsByName(sgParam, 1 + i, "K11_F2B", AI->K11_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_K11_F", AI->A3_K11_F);
         SGCellsByName(sgParam, 1 + i, "K11_F3N", AI->K11_F3N);
         SGCellsByName(sgParam, 1 + i, "K11_F3B", AI->K11_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_K00_F", AI->A1_K00_F);
         SGCellsByName(sgParam, 1 + i, "K00_F1N", AI->K00_F1N);
         SGCellsByName(sgParam, 1 + i, "K00_F1B", AI->K00_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_K00_F", AI->A2_K00_F);
         SGCellsByName(sgParam, 1 + i, "K00_F2N", AI->K00_F2N);
         SGCellsByName(sgParam, 1 + i, "K00_F2B", AI->K00_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_K00_F", AI->A3_K00_F);
         SGCellsByName(sgParam, 1 + i, "K00_F3N", AI->K00_F3N);
         SGCellsByName(sgParam, 1 + i, "K00_F3B", AI->K00_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_TF_F", AI->A1_TF_F);
         SGCellsByName(sgParam, 1 + i, "TF_F1N", AI->TF_F1N);
         SGCellsByName(sgParam, 1 + i, "TF_F1B", AI->TF_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_TF_F", AI->A2_TF_F);
         SGCellsByName(sgParam, 1 + i, "TF_F2N", AI->TF_F2N);
         SGCellsByName(sgParam, 1 + i, "TF_F2B", AI->TF_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_TF_F", AI->A3_TF_F);
         SGCellsByName(sgParam, 1 + i, "TF_F3N", AI->TF_F3N);
         SGCellsByName(sgParam, 1 + i, "TF_F3B", AI->TF_F3B);
         SGCellsByName(sgParam, 1 + i, "A1_VF_F", AI->A1_VF_F);
         SGCellsByName(sgParam, 1 + i, "VF_F1N", AI->VF_F1N);
         SGCellsByName(sgParam, 1 + i, "VF_F1B", AI->VF_F1B);
         SGCellsByName(sgParam, 1 + i, "A2_VF_F", AI->A2_VF_F);
         SGCellsByName(sgParam, 1 + i, "VF_F2N", AI->VF_F2N);
         SGCellsByName(sgParam, 1 + i, "VF_F2B", AI->VF_F2B);
         SGCellsByName(sgParam, 1 + i, "A3_VF_F", AI->A3_VF_F);
         SGCellsByName(sgParam, 1 + i, "VF_F3N", AI->VF_F3N);
         SGCellsByName(sgParam, 1 + i, "VF_F3B", AI->VF_F3B);
       }
       if (m_type == 8)
       {
         SGCellsByName(sgParam, 1 + i, "ÓÑËÎÂÈÅ", AI->PREDICAT);
       }

    }
  }
}

void TfmParamAlternative::RefreshData()
{
   if (Type_Char == PROP)
     RefreshDataPROP();
   if (Type_Char == FUZZY)
     RefreshDataFUZZY();
   if (TFE->ParamAlt)
     lbCount->Caption = IntToStr(TFE->ParamAlt->Count);
   else
     lbCount->Caption = "0";
}






void __fastcall TfmParamAlternative::FormShow(TObject *Sender)
{
   int m_type = TFE->TypeShape;
   if (m_type == 5)
    lbType->Caption = "Ðàáî÷àÿ îïåðàöèÿ";
   if (m_type == 6)
    lbType->Caption = "Êîíòðîëü ðàáîòîñïîñîáíîñòè";
   if (m_type == 7)
    lbType->Caption = "Ôóíêöèîíàëüíûé êîíòðîëü";
   if (m_type == 8)
    lbType->Caption = "Ïðîâåðêà óñëîâèÿ";

   if ( Type_Char == FUZZY )
     lbTypeParam->Caption = "Íå÷åòêèå õàðàêòåðèñòèêè";
   if ( Type_Char == PROP )
     lbTypeParam->Caption = "Âåðîÿòíîñòíûå õàðàêòåðèñòèêè";

   lbNum->Caption = IntToStr(ParentShapeID);

   StringInit();
   RefreshData();

}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternative::acAddExecute(TObject *Sender)
{

AnsiString  add_name,sos;
int type, num;
type = TFE->TypeShape;
num = TFE->ID;
  if (type == 8 && TFE->ParamAlt) return;



 double s_b, s_t, s_v,s_k11,s_k00,s_tf,s_vf,
           s_p11,s_p00,s_td,s_vd,
           s_p_el,
           s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
           s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
           s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
           s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
           s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
           s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
           s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
           s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
           s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
           s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
           s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
           s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b;
AnsiString s_name, s_el, s_func, s_e, s_predicat;


s_name="(íåò íàçâàíèÿ)";
s_el = "(íåò ýëåìåíòà)";
if (!TFE->ParamAlt)
  s_func = "(íåò ôóíêöèè)";
else
  s_func = TFE->ParamAlt->Items[0]->FUNCTION2;


s_b=1;s_t=0;s_v=0;
s_k11=1;s_k00=1;s_tf=0; s_vf=0;

s_p11=1;s_p00=1; s_td=0; s_vd=0;
s_e="(íåò ýëåìåíòà)"; s_p_el=1;
s_a1_p_el_f=0; s_p_el_f1n=0; s_p_el_f1b=0; s_a2_p_el_f=0.5; s_p_el_f2n=0; s_p_el_f2b=0;
s_a3_p_el_f=1; s_p_el_f3n=0; s_p_el_f3b=0;
s_a1_b_f=0; s_b_f1n=0; s_b_f1b=0; s_a2_b_f=0.5; s_b_f2n=0; s_b_f2b=0;
s_a3_b_f=1; s_b_f3n=0; s_b_f3b=0;
s_a1_t_f=0; s_t_f1n=0; s_t_f1b=0; s_a2_t_f=0.5; s_t_f2n=0; s_t_f2b=0;
s_a3_t_f=1; s_t_f3n=0; s_t_f3b=0;
s_a1_v_f=0; s_v_f1n=0; s_v_f1b=0; s_a2_v_f=0.5; s_v_f2n=0; s_v_f2b=0;
s_a3_v_f=1; s_v_f3n=0; s_v_f3b=0;
s_a1_k11_f=0; s_k11_f1n=0; s_k11_f1b=0; s_a2_k11_f=0.5; s_k11_f2n=0;
s_k11_f2b=0; s_a3_k11_f=1; s_k11_f3n=0; s_k11_f3b=0;
s_a1_k00_f=0; s_k00_f1n=0; s_k00_f1b=0; s_a2_k00_f=0.5; s_k00_f2n=0;
s_k00_f2b=0; s_a3_k00_f=1; s_k00_f3n=0; s_k00_f3b=0;
s_a1_tf_f=0; s_tf_f1n=0; s_tf_f1b=0; s_a2_tf_f=0.5; s_tf_f2n=0;
s_tf_f2b=0; s_a3_tf_f=1; s_tf_f3n=0; s_tf_f3b=0;
s_a1_vf_f=0; s_vf_f1n=0; s_vf_f1b=0; s_a2_vf_f=0.5; s_vf_f2n=0;
s_vf_f2b=0; s_a3_vf_f=1; s_vf_f3n=0; s_vf_f3b=0;
s_a1_p11_f=0; s_p11_f1n=0; s_p11_f1b=0; s_a2_p11_f=0.5; s_p11_f2n=0;
s_p11_f2b=0; s_a3_p11_f=1; s_p11_f3n=0; s_p11_f3b=0;
s_a1_p00_f=0; s_p00_f1n=0; s_p00_f1b=0; s_a2_p00_f=0.5; s_p00_f2n=0;
s_p00_f2b=0; s_a3_p00_f=1; s_p00_f3n=0; s_p00_f3b=0;
s_a1_td_f=0; s_td_f1n=0; s_td_f1b=0; s_a2_td_f=0.5; s_td_f2n=0;
s_td_f2b=0; s_a3_td_f=1; s_td_f3n=0; s_td_f3b=0;
s_a1_vd_f=0; s_vd_f1n=0; s_vd_f1b=0; s_a2_vd_f=0.5; s_vd_f2n=0;
s_vd_f2b=0; s_a3_vd_f=1; s_vd_f3n=0; s_vd_f3b=0;
s_predicat="(íåò óñëîâèÿ)";

TParamAlternativeItem* NI = CreateParamAlternativeItem(sos.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type,num,
                                     s_b,s_t,s_v,
                                     s_k11,s_k00,s_tf,s_vf,
                                     s_p11,s_p00,s_td,s_vd,
                                     s_e,s_p_el,
                                     s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
                                     s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
                                     s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
                                     s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
                                     s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
                                     s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
                                     s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
                                     s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
                                     s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
                                     s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
                                     s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
                                     s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b,
                                     s_predicat,1.0,1,1);
TFE->AddParamAlternativeItem(NI);
RefreshData();

}
//---------------------------------------------------------------------------



void __fastcall TfmParamAlternative::acDelExecute(TObject *Sender)
{
  void *pd = (void*)sgParam->Objects[0][sgParam->Row];
  TFE->DeleteParamAlternativeItem2(pd);
  RefreshData();
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternative::acDelUpdate(TObject *Sender)
{
  TAction* C = dynamic_cast<TAction*>(Sender);
  C->Enabled = !FReadOnly && TFE->ParamAlt;
}
//---------------------------------------------------------------------------

void __fastcall TfmParamAlternative::sgParamDblClick(TObject *Sender)
{
   void *pd = (void*)sgParam->Objects[0][sgParam->Row];
   if (!FReadOnly && pd)
   {
      TParamAlternativeItem *T = static_cast<TParamAlternativeItem*>(pd);
      ShowParamAlternativeEditor(TFE, T, Type_Char, false);
      RefreshData();
      LocateRow(pd);
   }
}

void TfmParamAlternative::LocateRow(void *Bm)
{
   void *t;
   for (int i = 0; i <= sgParam->RowCount - 1; i++)
   {
      t = (void*)sgParam->Objects[0][i];
      if (t == Bm)
      {
         sgParam->Row = i;
         return;
      }
   }
}

//---------------------------------------------------------------------------

void TfmParamAlternative::DrawGlp()
{
   if (f_Glp)
   {
      pbTfs->Canvas->Draw(0,0, f_Glp);
   }
}


void __fastcall TfmParamAlternative::pbTfsPaint(TObject *Sender)
{
   DrawGlp();
}
//---------------------------------------------------------------------------


void __fastcall TfmParamAlternative::acExitExecute(TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

double TfmParamAlternative::GetMyRandom()
{
  return rand()*1.0/RAND_MAX;
}


void __fastcall TfmParamAlternative::acFormExecute(TObject *Sender)
{
  AnsiString  add_name,sos;
  int num = f_TFE->ID;


  double s_b, s_t, s_v;
  double s_p11, s_p00, s_td, s_vd;
  double s_k11, s_k00, s_tf, s_vf;


  double   s_p_el,
           s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
           s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
           s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
           s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
           s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
           s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
           s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
           s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
           s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
           s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
           s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
           s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b;
  AnsiString s_name, s_el, s_func, s_e, s_predicat;

  s_name="(íåò íàçâàíèÿ)";
  s_el = "(íåò ýëåìåíòà)";
  if (!TFE->ParamAlt)
    s_func = "(íåò ôóíêöèè)";
  else
    s_func = TFE->ParamAlt->Items[0]->FUNCTION2;

  s_e="(íåò ýëåìåíòà)"; s_p_el=1;
  s_a1_p_el_f=0; s_p_el_f1n=0; s_p_el_f1b=0; s_a2_p_el_f=0.5; s_p_el_f2n=0; s_p_el_f2b=0;
  s_a3_p_el_f=1; s_p_el_f3n=0; s_p_el_f3b=0;
  s_a1_b_f=0; s_b_f1n=0; s_b_f1b=0; s_a2_b_f=0.5; s_b_f2n=0; s_b_f2b=0;
  s_a3_b_f=1; s_b_f3n=0; s_b_f3b=0;
  s_a1_t_f=0; s_t_f1n=0; s_t_f1b=0; s_a2_t_f=0.5; s_t_f2n=0; s_t_f2b=0;
  s_a3_t_f=1; s_t_f3n=0; s_t_f3b=0;
  s_a1_v_f=0; s_v_f1n=0; s_v_f1b=0; s_a2_v_f=0.5; s_v_f2n=0; s_v_f2b=0;
  s_a3_v_f=1; s_v_f3n=0; s_v_f3b=0;
  s_a1_k11_f=0; s_k11_f1n=0; s_k11_f1b=0; s_a2_k11_f=0.5; s_k11_f2n=0;
  s_k11_f2b=0; s_a3_k11_f=1; s_k11_f3n=0; s_k11_f3b=0;
  s_a1_k00_f=0; s_k00_f1n=0; s_k00_f1b=0; s_a2_k00_f=0.5; s_k00_f2n=0;
  s_k00_f2b=0; s_a3_k00_f=1; s_k00_f3n=0; s_k00_f3b=0;
  s_a1_tf_f=0; s_tf_f1n=0; s_tf_f1b=0; s_a2_tf_f=0.5; s_tf_f2n=0;
  s_tf_f2b=0; s_a3_tf_f=1; s_tf_f3n=0; s_tf_f3b=0;
  s_a1_vf_f=0; s_vf_f1n=0; s_vf_f1b=0; s_a2_vf_f=0.5; s_vf_f2n=0;
  s_vf_f2b=0; s_a3_vf_f=1; s_vf_f3n=0; s_vf_f3b=0;
  s_a1_p11_f=0; s_p11_f1n=0; s_p11_f1b=0; s_a2_p11_f=0.5; s_p11_f2n=0;
  s_p11_f2b=0; s_a3_p11_f=1; s_p11_f3n=0; s_p11_f3b=0;
  s_a1_p00_f=0; s_p00_f1n=0; s_p00_f1b=0; s_a2_p00_f=0.5; s_p00_f2n=0;
  s_p00_f2b=0; s_a3_p00_f=1; s_p00_f3n=0; s_p00_f3b=0;
  s_a1_td_f=0; s_td_f1n=0; s_td_f1b=0; s_a2_td_f=0.5; s_td_f2n=0;
  s_td_f2b=0; s_a3_td_f=1; s_td_f3n=0; s_td_f3b=0;
  s_a1_vd_f=0; s_vd_f1n=0; s_vd_f1b=0; s_a2_vd_f=0.5; s_vd_f2n=0;
  s_vd_f2b=0; s_a3_vd_f=1; s_vd_f3n=0; s_vd_f3b=0;
  s_predicat="(íåò óñëîâèÿ)";


  int m_cnt;
  int type = f_TFE->TypeShape;
  double T_0, T_1, V_0, V_1, X_0, X_1, Z_0, Z_1;
  if ( (type >= 5) && (type <= 7) )
  {
	m_cnt = ShowParamAlternativeLoader(type, T_0, T_1, V_0, V_1, X_0, X_1, Z_0, Z_1);
    if (m_cnt)
    {
      for (int i = 0; i <= m_cnt - 1; i++)
      {
        s_b = 0;
        s_t = 0;
        s_v = 0;
        s_p11 = 0;
        s_p00 = 0;
        s_td = 0;
        s_vd = 0;
        s_k11 = 0;
        s_k00 = 0;
        s_tf = 0;
        s_vf = 0;

        switch( type )
        {
          case(5):
            s_b = (X_1 - X_0) * GetMyRandom()  + X_0;
            s_t = (T_1 - T_0) * GetMyRandom()  + T_0;
            s_v = (V_1 - V_0) * GetMyRandom()  + V_0;
            break;

          case(6):
            s_p11 = (Z_1 - Z_0) * GetMyRandom()  + Z_0;
            s_p00 = (X_1 - X_0) * GetMyRandom()  + X_0;
            s_td  = (T_1 - T_0) * GetMyRandom()  + T_0;
            s_vd  = (V_1 - V_0) * GetMyRandom()  + V_0;
            break;

          case(7):
            s_k11 = (Z_1 - Z_0) * GetMyRandom() + Z_0;
            s_k00 = (X_1 - X_0) * GetMyRandom() + X_0;
            s_tf  = (T_1 - T_0) * GetMyRandom() + T_0;
            s_vf  = (V_1 - V_0) * GetMyRandom() + V_0;
            break;
        }
        TParamAlternativeItem* NI = CreateParamAlternativeItem(sos.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type,num,
                                     s_b,s_t,s_v,
                                     s_k11,s_k00,s_tf,s_vf,
                                     s_p11,s_p00,s_td,s_vd,
                                     s_e,s_p_el,
                                     s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
                                     s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
                                     s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
                                     s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
                                     s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
                                     s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
                                     s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
                                     s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
                                     s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
                                     s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
                                     s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
                                     s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b,
                                     s_predicat,1.0,1,1);
        TFE->AddParamAlternativeItem(NI);
      }
    }
  }
  RefreshData();
}
//---------------------------------------------------------------------------


