//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uLoaderTFS.h"
#include "uParamAlternativeItem.h"
#include "uIMRIncl_all.h"
#include "opim_f.H"


//---------------------------------------------------------------------------

#pragma package(smart_init)


TLoaderTFSItemMain::TLoaderTFSItemMain(int AId, int ATypeId)
{
   f_Id = AId;
   f_TypeId = ATypeId;
   ListParams = new TList;
}

TLoaderTFSItemMain::~TLoaderTFSItemMain()
{
   delete ListParams;
}


//---------------------------------------------------------------------


TLoaderTFSMain::TLoaderTFSMain()
{
   f_List = new TList;
   f_Tag = NULL;
   f_Tag2 = 0;

}


TLoaderTFSMain::~TLoaderTFSMain()
{
   FreeList();
   delete f_List;
}


void TLoaderTFSMain::FreeList()
{
   TLoaderTFSItemMain* Item;
   for (int i = f_List->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSItemMain*>(f_List->Items[i]);
      delete Item;
      Item = NULL;
      f_List->Delete(i);
   }
}

TLoaderTFSItemMain* TLoaderTFSMain::FindTFE(int AId)
{
   TLoaderTFSItemMain* Item;
   for (int i = f_List->Count - 1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSItemMain*>(f_List->Items[i]);
      if ( Item->Id == AId )
        return Item;
   }
   return NULL;
}

bool TLoaderTFSMain::AddTFE(int AId, int ATypeID)
{
   if ( !FindTFE(AId) )
   {
     f_List->Add(new TLoaderTFSItemMain(AId, ATypeID));
     return true;
   }
   return false;
}

TLoaderTFSItemMain* __fastcall TLoaderTFSMain::GetTFEItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TLoaderTFSItemMain*>(f_List->Items[AIndex]);
   else
     return NULL;
}


int __fastcall TLoaderTFSMain::GetTFECount()
{
   return  f_List->Count;
}

//----------------------------------------------------------------------------
TLoaderTFSAncestor::TLoaderTFSAncestor(int AIdBlock, int AIdShapeAncestor)
{
   f_IdBlock = AIdBlock;
   f_IdShapeAncestor = AIdShapeAncestor;
}


//--------------------------------------------------------
TLoaderTFSItemAlternate::TLoaderTFSItemAlternate(int AId)
{
   f_Id = AId;
}

//-------------------------------------------------------------------------
TLoaderTFSAlternate::TLoaderTFSAlternate()
{
   f_List = new TList;
}


TLoaderTFSAlternate::~TLoaderTFSAlternate()
{
   FreeList();
   delete f_List;
}

void TLoaderTFSAlternate::FreeList()
{
   TLoaderTFSItemAlternate* Item;
   for (int i = f_List->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSItemAlternate*>(f_List->Items[i]);
      delete Item;
      Item = NULL;
      f_List->Delete(i);
   }
}

bool TLoaderTFSAlternate::AddAlt(int AId)
{
   TLoaderTFSItemAlternate* Item;
   for (int i = f_List->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSItemAlternate*>(f_List->Items[i]);
      if (Item->Id == AId)
        return false;
   }
   Item = new TLoaderTFSItemAlternate(AId);
   f_List->Add(Item);
   return true;
}


TLoaderTFSItemAlternate* __fastcall TLoaderTFSAlternate::GetAltItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
	 return static_cast<TLoaderTFSItemAlternate*>(f_List->Items[AIndex]);
   else
	 return NULL;
}


int __fastcall TLoaderTFSAlternate::GetAltCount()
{
   return f_List->Count;
}


TLoaderTFS::TLoaderTFS()
{
   f_ListMain = new TList;
   f_ListAlt = new TList;
   f_ListAnc = new TList;
   f_ErrorString = "";
   f_TypeParam = 0;
   f_OgrSovm = NULL;
}

TLoaderTFS::~TLoaderTFS()
{
   FreeMain();
   FreeAlt();
   FreeAnc();
   delete f_ListMain;
   delete f_ListAlt;
   delete f_ListAnc;
}


void TLoaderTFS::FreeMain()
{
   TLoaderTFSMain* Item;
   for (int i = f_ListMain->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSMain*>(f_ListMain->Items[i]);
      delete Item;
      Item = NULL;
      f_ListMain->Delete(i);
   }
}


void TLoaderTFS::FreeAlt()
{
   TLoaderTFSAlternate* Item;
   for (int i = f_ListAlt->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSAlternate*>(f_ListAlt->Items[i]);
      delete Item;
      Item = NULL;
      f_ListAlt->Delete(i);
   }
}


void TLoaderTFS::FreeAnc()
{
   TLoaderTFSAncestor* Item;
   for (int i = f_ListAnc->Count -1; i>=0; i-- )
   {
      Item = static_cast<TLoaderTFSAncestor*>(f_ListAnc->Items[i]);
      delete Item;
      Item = NULL;
      f_ListAnc->Delete(i);
   }
}


TLoaderTFSMain* __fastcall TLoaderTFS::GetMainNode(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListMain->Count - 1)
     return static_cast<TLoaderTFSMain*>(f_ListMain->Items[AIndex]);
   else
     return NULL;
}

TLoaderTFSAncestor* __fastcall TLoaderTFS::GetAncestor(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListAnc->Count - 1)
     return static_cast<TLoaderTFSAncestor*>(f_ListAnc->Items[AIndex]);
   else
     return NULL;
}

TLoaderTFSAlternate* __fastcall TLoaderTFS::GetAlternate(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListAlt->Count - 1)
     return static_cast<TLoaderTFSAlternate*>(f_ListAlt->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TLoaderTFS::GetMainNodeCount()
{
  return f_ListMain->Count;
}

int __fastcall TLoaderTFS::GetAncestorCount()
{
  return f_ListAnc->Count;
}

int __fastcall TLoaderTFS::GetAlternateCount()
{
  return f_ListAlt->Count;
}

TLoaderTFSMain* TLoaderTFS::FindMainNode(int AId)
{
   TLoaderTFSMain* Item = NULL;
   for (int i = 0; i <= f_ListMain->Count - 1; i++)
   {
      Item = static_cast<TLoaderTFSMain*>(f_ListMain->Items[i]);
      if (Item->Id == AId)
        return Item;
   }
   return NULL;
}

TLoaderTFSAncestor* TLoaderTFS::FindAncestor(int AIdBlock, int AIdShapeAncestor)
{
   TLoaderTFSAncestor* Item = NULL;
   for (int i = 0; i <= f_ListAnc->Count - 1; i++)
   {
      Item = static_cast<TLoaderTFSAncestor*>(f_ListAnc->Items[i]);
      if ( (Item->IdBlock == AIdBlock) && (Item->IdShapeAncestor == AIdShapeAncestor) )
        return Item;
   }
   return NULL;
}


TLoaderTFSAlternate* TLoaderTFS::FindAlternate(int AId, int ANum)
{
   TLoaderTFSAlternate* Item = NULL;
   for (int i = 0; i <= f_ListAlt->Count - 1; i++)
   {
      Item = static_cast<TLoaderTFSAlternate*>(f_ListAlt->Items[i]);
      if ( (Item->Id == AId) && (Item->Num == ANum) )
        return Item;
   }
   return NULL;
}


TLoaderTFSMain* TLoaderTFS::AddMainNode(int AId)
{
   TLoaderTFSMain* Item = FindMainNode(AId);
   if (!Item)
   {
      Item = new TLoaderTFSMain;
      Item->Id = AId;
      f_ListMain->Add(Item);
   }
   return Item;
}

TLoaderTFSAncestor* TLoaderTFS::AddAncestor(int AIdBlock, int AIdShapeAncestor)
{
    TLoaderTFSAncestor* Item = FindAncestor(AIdBlock, AIdShapeAncestor);
    if (!Item)
    {
       Item = new TLoaderTFSAncestor(AIdBlock, AIdShapeAncestor);
       f_ListAnc->Add(Item);
    }
    return Item;
}

TLoaderTFSAlternate* TLoaderTFS::AddAlternate(int AId, int ANum)
{
    TLoaderTFSAlternate* Item = FindAlternate(AId, ANum);
    if (!Item)
    {
       Item = new TLoaderTFSAlternate;
       Item->Id = AId;
       Item->Num = ANum;
       f_ListAlt->Add(Item);
    }
    return Item;
}




void TLoaderTFS::Clear()
{
   f_ErrorString = "";
   FreeMain();
   FreeAlt();
   FreeAnc();
}

void* TLoaderTFS::CreateAlternateParams(TGlsXmlNode* ANode)
{
   int i_v;
   double d_v;
   TGlsXmlElement* TodoElement = ANode->ToElement();
   TParamAlternativeItem *NI = NULL;

   if ( strcmp(TodoElement->Value(), "ParamAlt") == 0 )
   {
     NI = new TParamAlternativeItem;
     if ( TodoElement->QueryIntAttribute("NUMBER" , &i_v ) != TGLSXML_SUCCESS )
       i_v = 0;
     NI->NUMBER = i_v;

     NI->PRED_ISTOR = TodoElement->Attribute("PRED_ISTOR");
     NI->SOSTAV = TodoElement->Attribute("SOSTAV");
     NI->NAME = TodoElement->Attribute("NAME");
     NI->FUNCTION2 = TodoElement->Attribute("FUNCTION");
     NI->ELEMENT = TodoElement->Attribute("ELEMENT");
     NI->PREDICAT = TodoElement->Attribute("PREDICAT");
     if ( TodoElement->QueryDoubleAttribute("B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B = d_v;

     if ( TodoElement->QueryDoubleAttribute("T" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T = d_v;

     if ( TodoElement->QueryDoubleAttribute("V" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_B_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_B_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_B_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_B_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_B_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_B_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("B_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->B_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_T_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_T_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_T_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_T_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_T_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_T_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_V_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_V_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_V_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_V_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_V_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_V_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("K_11" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K_11 = d_v;

     if ( TodoElement->QueryDoubleAttribute("K_00" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K_00 = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_K11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_K11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_K11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_K11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_K11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_K11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K11_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K11_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_K00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_K00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_K00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_K00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_K00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_K00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("K00_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->K00_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_TF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_TF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_TF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_TF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_TF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_TF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TF_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TF_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_VF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_VF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_VF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_VF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_VF_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_VF_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VF_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VF_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_11" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_11 = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_00" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_00 = d_v;

     if ( TodoElement->QueryDoubleAttribute("T_D" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->T_D = d_v;

     if ( TodoElement->QueryDoubleAttribute("V_D" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->V_D = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_P11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_P11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_P11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_P11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_P11_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_P11_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P11_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P11_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_P00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_P00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_P00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_P00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_P00_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_P00_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P00_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P00_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_TD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_TD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_TD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_TD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_TD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_TD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("TD_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->TD_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_VD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_VD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_VD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_VD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_VD_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_VD_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("VD_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->VD_F3B = d_v;

     if ( TodoElement->QueryIntAttribute("TYPE" , &i_v ) != TGLSXML_SUCCESS )
       i_v = 0;
     NI->TYPE = i_v;

     NI->ELEM_DIAGN = TodoElement->Attribute("ELEM_DIAGN");
     if ( TodoElement->QueryDoubleAttribute("P_DIAGN_EL" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_DIAGN_EL = d_v;

     if ( TodoElement->QueryDoubleAttribute("A1_P_EL_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A1_P_EL_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F1N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F1N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F1B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F1B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A2_P_EL_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A2_P_EL_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F2N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F2N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F2B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F2B = d_v;

     if ( TodoElement->QueryDoubleAttribute("A3_P_EL_F" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->A3_P_EL_F = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F3N" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F3N = d_v;

     if ( TodoElement->QueryDoubleAttribute("P_EL_F3B" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->P_EL_F3B = d_v;

     if ( TodoElement->QueryDoubleAttribute("SOVM" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->SOVM = d_v;

     if ( TodoElement->QueryDoubleAttribute("SOVM0" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->SOVM0 = d_v;

     if ( TodoElement->QueryDoubleAttribute("SOVM1" , &d_v ) != TGLSXML_SUCCESS )
       d_v = 0.0;
     NI->SOVM1 = d_v;
   }
   return NI;
}

void TLoaderTFS::DoAddParams(TGlsXmlNode* ANode, TLoaderTFSItemMain* AItem)
{
   void *p;
   TGlsXmlNode* xml_item;
   if ( !ANode->NoChildren() )
   {
     xml_item = ANode->FirstChild();
     while(xml_item)
     {
       p = CreateAlternateParams(xml_item);
       if (p)
         AItem->ListParams->Add(p);
       xml_item = xml_item->NextSibling();
     }

   }

}


AnsiString TLoaderTFS::DoAddMainNodeFromXML(TGlsXmlNode* ANode)
{
   AnsiString Errors = "";
   TLoaderTFSMain* ItemMain;
   TGlsXmlNode* xml_tfe;
   TGlsXmlNode* xml_params;
   TGlsXmlElement* TodoElement = NULL;
   int m_id, m_typeId, m_sx, m_sy, m_offx, m_offy, m_nextid, m_priorid;
   if (!ANode)
   {
     Errors = "Пустой узел!";
     return Errors;
   }
   if (ANode->NoChildren() )
   {
     Errors = "TFS не содержит TFE!";
     return Errors;
   }
   TodoElement = ANode->ToElement();
   if ( TodoElement->QueryIntAttribute("ID" , &m_id) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута ID!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("TypeID" , &m_typeId) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута TypeID!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("StartPointX" , &m_sx) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута StartPointX!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("StartPointY" , &m_sy) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута StartPointY!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("OffsetX" , &m_offx) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута OffsetX!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("OffsetY" , &m_offy) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута OffsetY!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("NextID" , &m_nextid) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута NextID!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("PriorID" , &m_priorid) != TGLSXML_SUCCESS )
   {
     Errors = "TFS не содержит атрибута PriorID!";
     return Errors;
   }

   ItemMain = AddMainNode(m_id);
   if (!ItemMain)
   {
     Errors = "Несколько TFS с одинаковым ID !";
     return Errors;
   }
   ItemMain->TypeId =  m_typeId;
   ItemMain->StartPoint.x = m_sx;
   ItemMain->StartPoint.y = m_sy;
   ItemMain->OffsetX = m_offx;
   ItemMain->OffsetY = m_offy;
   ItemMain->NextId = m_nextid;
   ItemMain->PriorId = m_priorid;
   xml_tfe = ANode->FirstChild();
   while(xml_tfe)
   {
     if ( strcmp(xml_tfe->Value(), "TFE") != 0 )
     {
        Errors = "Нет узла TFE!";
        return Errors;
     }
     TodoElement = xml_tfe->ToElement();
     if ( TodoElement->QueryIntAttribute("ID" , &m_id) != TGLSXML_SUCCESS )
     {
       Errors = "TFE не содержит атрибута ID!";
       return Errors;
     }
     if ( TodoElement->QueryIntAttribute("TypeID" , &m_typeId) != TGLSXML_SUCCESS )
     {
       Errors = "TFE не содержит атрибута TypeID!";
       return Errors;
     }
     if (! ItemMain->AddTFE(m_id, m_typeId) )
     {
       Errors = "Обнаружены одинаковые TFE !";
       return Errors;
     }
     xml_params = xml_tfe->FirstChild();
     DoAddParams(xml_params, ItemMain->FindTFE(m_id));
     xml_tfe = xml_tfe->NextSibling();
   }
   return Errors;
}


AnsiString TLoaderTFS::DoAddAncestor(TGlsXmlNode* ANode)
{
   AnsiString Errors = "";
   TLoaderTFSAncestor* ItemAncestor;
   TGlsXmlElement* TodoElement = NULL;
   int m_IdBlock, m_IdShapeAncestor;
   if (!ANode)
   {
     Errors = "Пустой узел!";
     return Errors;
   }
   TodoElement = ANode->ToElement();
   if ( TodoElement->QueryIntAttribute("IdBlock" , &m_IdBlock) != TGLSXML_SUCCESS )
   {
     Errors = "ANCS не содержит атрибута IdBlock!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("IdShapeAncestor" , &m_IdShapeAncestor) != TGLSXML_SUCCESS )
   {
     Errors = "ANCS не содержит атрибута IdShapeAncestor!";
     return Errors;
   }

   ItemAncestor = AddAncestor(m_IdBlock, m_IdShapeAncestor);
   if (!ItemAncestor)
   {
     Errors = "Несколько одинаковых узлов ANCS!";
     return Errors;
   }
   return Errors;
}

AnsiString TLoaderTFS::DoAddAlternate(TGlsXmlNode* ANode)
{
   AnsiString Errors = "";
   TLoaderTFSAlternate* ItemAlternate;
   TGlsXmlNode* xml_item;
   TGlsXmlElement* TodoElement = NULL;
   int m_ID, m_Num, m_NodeStartID, m_NodeEndID;
   if (!ANode)
   {
     Errors = "Пустой узел!";
     return Errors;
   }
   if (ANode->NoChildren() )
   {
     Errors = "ALT не содержит ITEM!";
     return Errors;
   }
   TodoElement = ANode->ToElement();
   if ( TodoElement->QueryIntAttribute("ID" , &m_ID) != TGLSXML_SUCCESS )
   {
     Errors = "ALT не содержит атрибута ID!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("Num" , &m_Num) != TGLSXML_SUCCESS )
   {
     Errors = "ALT не содержит атрибута Num!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("NodeStartID" , &m_NodeStartID) != TGLSXML_SUCCESS )
   {
     Errors = "ALT не содержит атрибута NodeStartID!";
     return Errors;
   }
   if ( TodoElement->QueryIntAttribute("NodeEndID" , &m_NodeEndID) != TGLSXML_SUCCESS )
   {
     Errors = "ALT не содержит атрибута NodeEndID!";
     return Errors;
   }

   ItemAlternate = AddAlternate(m_ID, m_Num);
   if (!ItemAlternate)
   {
     Errors = "Несколько одинаковым узлов ALT!";
     return Errors;
   }
   ItemAlternate->NodeStartID = m_NodeStartID;
   ItemAlternate->NodeEndID = m_NodeEndID;

   xml_item = ANode->FirstChild();
   while(xml_item)
   {
     if ( strcmp(xml_item->Value(), "ITEM") != 0 )
     {
        Errors = "Нет узла ITEM!";
        return Errors;
     }
     TodoElement = xml_item->ToElement();
     if ( TodoElement->QueryIntAttribute("ID" , &m_ID) != TGLSXML_SUCCESS )
     {
       Errors = "ITEM не содержит атрибута ID!";
       return Errors;
     }
     if (! ItemAlternate->AddAlt(m_ID) )
     {
       Errors = "Обнаружены одинаковые ITEM!";
       return Errors;
     }
     xml_item = xml_item->NextSibling();
   }
   return Errors;
}




bool TLoaderTFS::DoLoad(AnsiString AFileName, TGlsXmlDocument *AXml_dom, TGlsXmlString *AXml_str)
{
   AnsiString Errors;
   TGlsXmlElement *xml_root;
   TGlsXmlNode *xml_main, *xml_anc, *xml_alt, *xml_node;
   TGlsXmlNode *xml_type_param, *xml_ogrsovm, *xml_typedecision;
   xml_main = xml_anc = xml_alt = NULL;
   TLoaderTFSMain* ItemMain;
   if ( ! AXml_dom->LoadFile(AFileName.c_str()) )
   {
      Errors = AXml_dom->ErrorDesc();
      Errors = Errors + "\r\nСтрока: "+IntToStr(AXml_dom->ErrorRow())+ "\r\nСтолбец: "+IntToStr(AXml_dom->ErrorCol());
      f_ErrorString = "Ошибка загрузки файла!\r\n\r\n" + Errors;
      return false;
   }
   xml_root = AXml_dom->RootElement();
   *AXml_str = xml_root->Value();
   if ( *AXml_str != "ROOT")
   {
      f_ErrorString = "Нет корневого узла!";
      return false;
   }

   xml_main = xml_root->FirstChild();
   if (xml_main)
     *AXml_str = xml_main->Value();
   if (*AXml_str != "MAINLIST")
   {
      f_ErrorString = "Нет главного списка!";
      return false;
   }
   xml_anc = xml_main->NextSibling();
   if (xml_anc)
     *AXml_str = xml_anc->Value();
   if (*AXml_str != "ANCESTORLIST")
   {
      f_ErrorString = "Нет списка предков!";
      return false;
   }
   xml_alt = xml_anc->NextSibling();
   if (xml_alt)
     *AXml_str = xml_alt->Value();
   if (*AXml_str != "ALTERNATELIST")
   {
      f_ErrorString = "Нет списка альтернатив!";
      return false;
   }

   /* Главный список */
   if ( xml_main->NoChildren() )
   {
      f_ErrorString = "Главный список пуст!";
      return false;
   }
   xml_node = xml_main->FirstChild();
   while (xml_node)
   {
      *AXml_str = xml_node->Value();
      if (*AXml_str != "TFS")
      {
         f_ErrorString = "Неверно заполнен главный список!";
         return false;
      }
      if ( xml_node->NoChildren() )
      {
         f_ErrorString = "Неверно заполнен главный список (нет TFE)!";
         return false;
      }

      DoAddMainNodeFromXML(xml_node);
      xml_node = xml_node->NextSibling();
   }

   /* Предки */
   xml_node = xml_anc->FirstChild();
   while (xml_node)
   {
      *AXml_str = xml_node->Value();
      if (*AXml_str != "ANCS")
      {
         f_ErrorString = "Неверно заполнен список предков!";
         return false;
      }

      DoAddAncestor(xml_node);
      xml_node = xml_node->NextSibling();
   }


   /* Альтернативы */
   if ( xml_alt->NoChildren() )
   {
      f_ErrorString = "Список альтернатв пуст!";
      return false;
   }
   xml_node = xml_alt->FirstChild();
   while (xml_node)
   {
      *AXml_str = xml_node->Value();
      if (*AXml_str != "ALT")
      {
         f_ErrorString = "Неверно заполнен список альтернатив!";
         return false;
      }
      if ( xml_node->NoChildren() )
      {
         f_ErrorString = "Неверно заполнен список алтернатив (нет составляющих)!";
         return false;
      }
      DoAddAlternate(xml_node);
      xml_node = xml_node->NextSibling();
   }
   xml_ogrsovm = xml_alt->NextSibling();
   DoLoadOgrSovmFromXML(xml_ogrsovm);
   xml_type_param  = xml_ogrsovm->NextSibling();
   if ( xml_type_param->ToElement()->QueryIntAttribute("Value" , &f_TypeParam ) != TGLSXML_SUCCESS )
     f_TypeParam = 0;
   xml_typedecision = xml_type_param->NextSibling();
   DoLoadTypeDecisionFromXML(xml_typedecision);
   f_ErrorString = CheckValid();
   return f_ErrorString == "";
}


bool TLoaderTFS::DoCheckValidAlternate()
{
   TLoaderTFSAlternate* Alt;
   TLoaderTFSItemAlternate* AltItem;
   TLoaderTFSMain* Main;
   for (int i = 0; i <= AlternateCount - 1; i++ )
   {
      Alt = Alternate[i];
      if ( (Alt->Id) || (Alt->Num) )
      {
         Main = FindMainNode(Alt->NodeStartID);
         if (!Main)
           return false;
      }
      for(int j = 0; j <= Alt->AltCount - 1; j++)
      {
         AltItem = Alt->AltItems[j];
         Main = FindMainNode(AltItem->Id);
         if (!Main)
           return false;
      }
      if ( Alt->AltCount > 0 )
      {
         AltItem = Alt->AltItems[0];
         Main = FindMainNode(AltItem->Id);
         if (Main->PriorId != -1)
           return false;
         AltItem = Alt->AltItems[Alt->AltCount - 1];
         Main = FindMainNode(AltItem->Id);
         if (Main->NextId != -1)
           return false;
       }
   }
   return true;
}


bool TLoaderTFS::DoCheckValidAncestor()
{
   TLoaderTFSAncestor* Anc;
   TLoaderTFSMain* Main;
   for (int i = 0; i <= AncestorCount - 1; i++ )
   {
      Anc = Ancestor[i];
      Main = FindMainNode(Anc->IdBlock);
      if (!Main)
        return false;
      if ( CountTFE(Anc->IdShapeAncestor) != 1 )
        return false;
   }
   return true;
}

bool TLoaderTFS::DoCheckMainNode()
{
   TLoaderTFSMain* Main;
   TLoaderTFSMain* FN;
   TLoaderTFSItemMain* TFE;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      if (Main->NextId != -1)
      {
        FN = FindMainNode(Main->NextId);
        if (!FN)
          return false;
      }
      if (Main->PriorId != -1)
      {
        FN = FindMainNode(Main->PriorId);
        if (!FN)
          return false;
      }
      for (int j = 0; j <= Main->TFECount - 1; j++)
      {
         TFE = Main->TFEItems[j];
         if ( CountTFE(TFE->Id) != 1 )
           return false;
      }
   }
   return true;
}


int TLoaderTFS::CountTFE(int AId)
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemMain* TFE;
   int res = 0;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      for (int j = 0; j <= Main->TFECount - 1; j++)
      {
         TFE = Main->TFEItems[j];
         if (TFE->Id == AId)
           res++;
      }
   }
   return res;
}


AnsiString TLoaderTFS::CheckValid()
{
   AnsiString Errors = "";
   if(  !DoCheckValidAlternate() )
   {
      Errors = "Невалидный список альтернатив!";
      return Errors;
   }

   if( !DoCheckValidAncestor() )
   {
      Errors = "Невалидный список предков!";
      return Errors;
   }
   if( !DoCheckMainNode() )
   {
      Errors = "Невалидный главный список!";
      return Errors;
   }
   return Errors;
}

int __fastcall TLoaderTFS::GetMinTfeID()
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemMain* TFE;
   int res = 0;
   bool set_f = false;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      for (int j = 0; j <= Main->TFECount - 1; j++)
      {
         TFE = Main->TFEItems[j];
         if (!set_f)
         {
           res = TFE->Id;
           set_f = true;
         }
         if (res > TFE->Id)
           res = TFE->Id;
      }
   }
   return res;
}

int __fastcall TLoaderTFS::GetMinTfsID()
{
   TLoaderTFSMain* Main;
   int res = 0;
   bool set_f = false;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      if (!set_f)
      {
        res = Main->Id;
        set_f = true;
      }
      if (res > Main->Id)
        res = Main->Id;
   }
   return res;
}

int __fastcall TLoaderTFS::GetMinAltID()
{
   TLoaderTFSAlternate* Item;
   int res = 0;
   bool set_f = false;
   for (int i = 0; i <= AlternateCount - 1; i++)
   {
      Item = Alternate[i];
      if (!set_f && Item->Id)
      {
         res = Item->Id;
         set_f = true;
      }
      if ( (res > Item->Id) && Item->Id )
        res = Item->Id;
   }
   return res;
}

void TLoaderTFS::IncTfeID(int ACnt)
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemMain* TFE;
   TLoaderTFSAncestor* Ances;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      for (int j = 0; j <= Main->TFECount - 1; j++)
      {
         TFE = Main->TFEItems[j];
         TFE->Id = TFE->Id + ACnt;
      }
   }

   for (int i = 0; i <= AncestorCount - 1; i++)
   {
      Ances = Ancestor[i];
      Ances->IdShapeAncestor = Ances->IdShapeAncestor + ACnt;
   }

}


void TLoaderTFS::IncTfsID(int ACnt)
{
   TLoaderTFSMain* Main;
   TLoaderTFSAncestor* Ances;
   TLoaderTFSAlternate* Alt;
   TLoaderTFSItemAlternate* AItem;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      Main->Id = Main->Id + ACnt;
      if (Main->NextId > 0)
        Main->NextId = Main->NextId + ACnt;
      if (Main->PriorId > 0)
        Main->PriorId = Main->PriorId + ACnt;

   }
   for (int i = 0; i <= AncestorCount - 1; i++)
   {
      Ances = Ancestor[i];
      Ances->IdBlock = Ances->IdBlock + ACnt;
   }
   for (int i = 0; i <= AlternateCount - 1; i++)
   {
      Alt = Alternate[i];
      Alt->NodeStartID = Alt->NodeStartID + ACnt;
      Alt->NodeEndID = Alt->NodeEndID + ACnt;
      for (int j = 0 ; j <= Alt->AltCount - 1; j++)
      {
        AItem = Alt->AltItems[j];
        AItem->Id = AItem->Id + ACnt;
      }
   }

}

void TLoaderTFS::IncAltID(int ACnt, int AParentID, int AParentNum)
{
   TLoaderTFSAlternate* Item;
   for (int i = 0; i <= AlternateCount - 1; i++)
   {
      Item = Alternate[i];
      if (Item->Id)
        Item->Id = Item->Id + ACnt;
      else
      {
         Item->Id = AParentID;
         Item->Num = AParentNum;
      }

   }
}

TLoaderTFSMain* TLoaderTFS::FindNext(TLoaderTFSMain* ANode)
{
   TLoaderTFSMain* Main = NULL;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      if ( Main == ANode )
      {
         if ( Main->NextId == -1 )
           return NULL;
         break;
      }
   }
   if (Main)
   {
     for (int i = 0; i <= MainNodeCount - 1; i++)
      if ( MainNode[i]->Id == Main->NextId )
          return MainNode[i];
   }
   return NULL;
}

TLoaderTFSMain* TLoaderTFS::FindPrior(TLoaderTFSMain* ANode)
{
   TLoaderTFSMain* Main = NULL;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      if ( Main == ANode )
      {
         if ( Main->PriorId == -1 )
           return NULL;
         break;
      }
   }
   if (Main)
   {
     for (int i = 0; i <= MainNodeCount - 1; i++)
      if ( MainNode[i]->Id == Main->PriorId )
          return MainNode[i];
   }
   return NULL;
}


TLoaderTFSMain* TLoaderTFS::FindLastToAlternate(int AId, int ANum)
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemAlternate* AItem;
   TLoaderTFSAlternate* Alt = FindAlternate(AId, ANum);
   if (!Alt) return NULL;
   for(int i = 0; i <= Alt->AltCount - 1; i++ )
   {
      AItem = Alt->AltItems[i];
      Main = FindMainNode(AItem->Id);
      if (Main->NextId == -1)
        return Main;
   }
   return NULL;


}


TLoaderTFSAncestor* TLoaderTFS::FindAncestorNew(TLoaderTFSMain* ANode)
{
   if (ANode)
     return DoFindAncestor(ANode->Id);
   return NULL;
}


TLoaderTFSAlternate* TLoaderTFS::FindAlternative(TLoaderTFSMain* ANode)
{
    TLoaderTFSAlternate* Alt;
    TLoaderTFSItemAlternate* Item;
    TLoaderTFSAlternate* ANx = NULL;
    TLoaderTFSAncestor* Anc;
    TLoaderTFSMain* NMain;
    int c_break, find_bl;

    for(int i = 0; i <= AlternateCount-1; i++)
    {
       Alt = Alternate[i];
       for (int j = 0; j <= Alt->AltCount - 1; j++)
       {
          Item = Alt->AltItems[j];
          if (Item->Id == ANode->Id)
            return Alt;
       }
    }

    c_break = MainNodeCount;
    find_bl = ANode->Id;
    while( (!ANx) || c_break)
    {

       for(int i = 0; i <= AncestorCount-1; i++)
       {
       Anc = Ancestor[i];
       if (Anc->IdBlock == find_bl)
       {
         NMain = FindNodeOutTFEID(Anc->IdShapeAncestor);
         ANx = FindAlternative(NMain);

         if (ANx)
           return ANx;
         else
         {
            c_break--;
            find_bl = NMain->Id;

         }
       }
       }
    }



    return NULL;
}

TLoaderTFSMain* TLoaderTFS::FindNodeOutTFEID(int ATFEId)
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemMain* Item;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
     Main = MainNode[i];
     for (int j = 0; j <= Main->TFECount - 1; j++)
     {
        Item = Main->TFEItems[j];
        if (Item->Id == ATFEId)
          return Main;
     }
   }
   return NULL;
}


TLoaderTFSAlternate* TLoaderTFS::FindAlternativeFromAncestor(TLoaderTFSMain* ANode)
{
   TLoaderTFSAlternate* Alt;
   TLoaderTFSItemAlternate* Item;
   TLoaderTFSAncestor* Ances = NULL;
   TLoaderTFSMain* Main;
   for (int i = 0; i <= AncestorCount - 1; i++)
   {
      Ances = Ancestor[i];
      if (Ances->IdBlock == ANode->Id )
        break;
   }
   if (Ances)
   {
      Main =  FindNodeOutTFEID(Ances->IdShapeAncestor);
      if (Main)
        return FindAlternative(Main);
   }
   return NULL;

}



TLoaderTFSAncestor* TLoaderTFS::FindAncestorOutBlockID(int ABockId)
{
   TLoaderTFSMain* Main = NULL;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
      Main = MainNode[i];
      if ( MainNode[i]->Id == ABockId)
      {
         Main = MainNode[i];
         break;
      }
   }
   if (Main)
      return FindAncestorNew(Main);
   return NULL;
}


TLoaderTFSMain* TLoaderTFS::FindNodeOutBlockID(int ABockId)
{
   for (int i = 0; i <= MainNodeCount - 1; i++)
     if ( MainNode[i]->Id == ABockId)
        return MainNode[i];
   return NULL;
}

TLoaderTFSAlternate* TLoaderTFS::FindAlternativeParent(TLoaderTFSAlternate* AChild)
{
    TLoaderTFSAlternate* Alt;
    TLoaderTFSAlternate* ANx = NULL;
    TLoaderTFSItemAlternate* Item;
    TLoaderTFSAncestor* Anc;
    TLoaderTFSMain* NMain;
    int c_break, find_bl;
    for(int i = 0; i <= AlternateCount-1; i++)
    {
       Alt = Alternate[i];
       for (int j = 0; j <= Alt->AltCount - 1; j++)
       {
          Item = Alt->AltItems[j];
          if (Item->Id == AChild->NodeStartID)
            return Alt;
       }
    }
    c_break = MainNodeCount;
    find_bl = AChild->NodeStartID;
    while( (!ANx) || c_break)
    {

       for(int i = 0; i <= AncestorCount-1; i++)
       {
       Anc = Ancestor[i];
       if (Anc->IdBlock == find_bl)
       {
         NMain = FindNodeOutTFEID(Anc->IdShapeAncestor);
         ANx = FindAlternative(NMain);

         if (ANx)
         //  return FindAlternativeParent(ANx);
            return ANx;
         else
         {
            c_break--;
            find_bl = NMain->Id;

         }
       }
       }
    }

    return NULL;


}

TLoaderTFSAlternate* TLoaderTFS::FindAlternativeParentNew(TLoaderTFSAlternate* AChild)
{
   if(!AChild) return NULL;
   if(AChild->NodeEndID == -1) return NULL;  //ss44
   return FindAlternativeNew(FindNodeOutBlockID(AChild->NodeStartID));
}



TLoaderTFSAncestor*  TLoaderTFS::DoFindAncestor(int ABlockID)
{
   TLoaderTFSAncestor* Anc;
   for(int i = 0; i <= AncestorCount-1; i++)
   {
     Anc = Ancestor[i];
     if (Anc->IdBlock == ABlockID)
       return Anc;
   }
   return NULL;
}

TLoaderTFSMain* TLoaderTFS::DoFindMainNodeFromTFE(int ATFEId)
{
   TLoaderTFSMain* Main;
   TLoaderTFSItemMain* Item;
   for (int i = 0; i <= MainNodeCount - 1; i++)
   {
     Main = MainNode[i];
     for (int j = 0; j <= Main->TFECount - 1; j++)
     {
        Item = Main->TFEItems[j];
        if (Item->Id == ATFEId)
          return Main;
     }
   }
   return NULL;
}


TLoaderTFSAlternate* TLoaderTFS::DoFindAlternate(int ABlockID)
{
   TLoaderTFSAlternate* Alt;
   TLoaderTFSItemAlternate* AltItem;
   for(int i = 0; i <= AlternateCount-1; i++)
   {
      Alt = Alternate[i];
      for (int j = 0; j <= Alt->AltCount - 1; j++)
      {
         AltItem = Alt->AltItems[j];
         if (AltItem->Id == ABlockID)
           return Alt;
      }
   }
   return NULL;
}


TLoaderTFSAlternate* TLoaderTFS::FindAlternativeNew(TLoaderTFSMain* ANode)
{
   TLoaderTFSAlternate* Res;
   TLoaderTFSAncestor* Anc;
   TLoaderTFSMain* MNode;
   Res = DoFindAlternate(ANode->Id);
   if (Res)
      return Res;
   MNode = ANode;
   for (int i = 0; i <= AncestorCount - 1; i++)
   {
     Anc = DoFindAncestor(MNode->Id);
     if (!Anc)
        return NULL;
     MNode = DoFindMainNodeFromTFE(Anc->IdShapeAncestor);
     Res = DoFindAlternate(MNode->Id);
     if (Res)
        return Res;
   }
   return NULL;
}




bool TLoaderTFS::LoadFromFile(AnsiString AFileName, TDischargedMassiv *AOgrSovm)
{
   bool Res;
   f_OgrSovm = AOgrSovm;
   TGlsXmlDocument *xml_dom = new TGlsXmlDocument();
   TGlsXmlString *xml_str = new TGlsXmlString();
   Clear();
   Res = DoLoad(AFileName, xml_dom, xml_str);
   if ( !Res )
	 Application->MessageBox(f_ErrorString.c_str(), _T("Загрузка файла"), MB_ICONSTOP);
   delete xml_str;
   delete xml_dom;
   return Res;
}

int __fastcall TLoaderTFSMain::GetMinTFE()
{
   int res = TFEItems[0]->Id - 1;
   for (int i = 1; i <= TFECount - 1; i++)
   {
      if ( (TFEItems[i]->Id - 1) < res )
        res = (TFEItems[i]->Id - 1);
   }
   return res;
}


//----------------------------------------------------------------------------------
bool TLoaderTFS::LoadFromFileBin(AnsiString AFileName, TDischargedMassiv *AOgrSovm)
{
   bool Res;
   Clear();
   f_OgrSovm = AOgrSovm;
   Res = DoLoadBin(AFileName);
   if ( !Res )
     Application->MessageBox(f_ErrorString.c_str(), _T("Загрузка файла"), MB_ICONSTOP);
   return Res;
}

void* TLoaderTFS::CreateAlternateParamsBin(SF_PARAMALT Alt)
{
  TParamAlternativeItem *NI = new TParamAlternativeItem;

  NI->NUMBER = Alt.NUMBER;

  NI->PRED_ISTOR = Alt.PRED_ISTOR;
  NI->SOSTAV = Alt.SOSTAV;
  NI->NAME = Alt.NAME;
  NI->FUNCTION2 = Alt.FUNCTION2;
  NI->ELEMENT = Alt.ELEMENT;
  NI->PREDICAT = Alt.PREDICAT;

  NI->B = Alt.B;
  NI->T = Alt.T;
  NI->V = Alt.V;

  NI->A1_B_F = Alt.A1_B_F;

  NI->B_F1N = Alt.B_F1N;

  NI->B_F1B = Alt.B_F1B;

  NI->A2_B_F = Alt.A2_B_F;

  NI->B_F2N = Alt.B_F2N;

  NI->B_F2B = Alt.B_F2B;

  NI->A3_B_F = Alt.A3_B_F;

  NI->B_F3N = Alt.B_F3N;

  NI->B_F3B = Alt.B_F3B;

  NI->A1_T_F = Alt.A1_T_F;

  NI->T_F1N = Alt.T_F1N;

  NI->T_F1B = Alt.T_F1B;

  NI->A2_T_F = Alt.A2_T_F;

  NI->T_F2N = Alt.T_F2N;

  NI->T_F2B = Alt.T_F2B;

  NI->A3_T_F = Alt.A3_T_F;

  NI->T_F3N = Alt.T_F3N;

  NI->T_F3B = Alt.T_F3B;

  NI->A1_V_F = Alt.A1_V_F;

  NI->V_F1N = Alt.V_F1N;

  NI->V_F1B = Alt.V_F1B;

  NI->A2_V_F = Alt.A2_V_F;

  NI->V_F2N = Alt.V_F2N;

  NI->V_F2B = Alt.V_F2B;

  NI->A3_V_F = Alt.A3_V_F;

  NI->V_F3N = Alt.V_F3N;

  NI->V_F3B = Alt.V_F3B;

  NI->K_11 = Alt.K_11;

  NI->K_00 = Alt.K_00;

  NI->T_F = Alt.T_F;

  NI->V_F = Alt.V_F;

  NI->A1_K11_F = Alt.A1_K11_F;

  NI->K11_F1N = Alt.K11_F1N;

  NI->K11_F1B = Alt.K11_F1B;

  NI->A2_K11_F = Alt.A2_K11_F;

  NI->K11_F2N = Alt.K11_F2N;

  NI->K11_F2B = Alt.K11_F2B;

  NI->A3_K11_F = Alt.A3_K11_F;

  NI->K11_F3N = Alt.K11_F3N;

  NI->K11_F3B = Alt.K11_F3B;

  NI->A1_K00_F = Alt.A1_K00_F;

  NI->K00_F1N = Alt.K00_F1N;

  NI->K00_F1B = Alt.K00_F1B;

  NI->A2_K00_F = Alt.A2_K00_F;

  NI->K00_F2N = Alt.K00_F2N;

  NI->K00_F2B = Alt.K00_F2B;

  NI->A3_K00_F = Alt.A3_K00_F;

  NI->K00_F3N = Alt.K00_F3N;

  NI->K00_F3B = Alt.K00_F3B;

  NI->A1_TF_F = Alt.A1_TF_F;

  NI->TF_F1N = Alt.TF_F1N;

  NI->TF_F1B = Alt.TF_F1B;

  NI->A2_TF_F = Alt.A2_TF_F;

  NI->TF_F2N = Alt.TF_F2N;

  NI->TF_F2B = Alt.TF_F2B;

  NI->A3_TF_F = Alt.A3_TF_F;

  NI->TF_F3N = Alt.TF_F3N;

  NI->TF_F3B = Alt.TF_F3B;

  NI->A1_VF_F = Alt.A1_VF_F;

  NI->VF_F1N = Alt.VF_F1N;

  NI->VF_F1B = Alt.VF_F1B;

  NI->A2_VF_F = Alt.A2_VF_F;

  NI->VF_F2N = Alt.VF_F2N;

  NI->VF_F2B = Alt.VF_F2B;

  NI->A3_VF_F = Alt.A3_VF_F;

  NI->VF_F3N = Alt.VF_F3N;

  NI->VF_F3B = Alt.VF_F3B;

  NI->P_11 = Alt.P_11;

  NI->P_00 = Alt.P_00;

  NI->T_D = Alt.T_D;

  NI->V_D = Alt.V_D;

  NI->A1_P11_F = Alt.A1_P11_F;

  NI->P11_F1N = Alt.P11_F1N;

  NI->P11_F1B = Alt.P11_F1B;

  NI->A2_P11_F = Alt.A2_P11_F;

  NI->P11_F2N = Alt.P11_F2N;

  NI->P11_F2B = Alt.P11_F2B;

  NI->A3_P11_F = Alt.A3_P11_F;

  NI->P11_F3N = Alt.P11_F3N;

  NI->P11_F3B = Alt.P11_F3B;

  NI->A1_P00_F = Alt.A1_P00_F;

  NI->P00_F1N = Alt.P00_F1N;

  NI->P00_F1B = Alt.P00_F1B;

  NI->A2_P00_F = Alt.A2_P00_F;

  NI->P00_F2N = Alt.P00_F2N;

  NI->P00_F2B = Alt.P00_F2B;

  NI->A3_P00_F = Alt.A3_P00_F;

  NI->P00_F3N = Alt.P00_F3N;

  NI->P00_F3B = Alt.P00_F3B;

  NI->A1_TD_F = Alt.A1_TD_F;

  NI->TD_F1N = Alt.TD_F1N;

  NI->TD_F1B = Alt.TD_F1B;

  NI->A2_TD_F = Alt.A2_TD_F;

  NI->TD_F2N = Alt.TD_F2N;

  NI->TD_F2B = Alt.TD_F2B;

  NI->A3_TD_F = Alt.A3_TD_F;

  NI->TD_F3N = Alt.TD_F3N;

  NI->TD_F3B = Alt.TD_F3B;

  NI->A1_VD_F = Alt.A1_VD_F;

  NI->VD_F1N = Alt.VD_F1N;

  NI->VD_F1B = Alt.VD_F1B;

  NI->A2_VD_F = Alt.A2_VD_F;

  NI->VD_F2N = Alt.VD_F2N;

  NI->VD_F2B = Alt.VD_F2B;

  NI->A3_VD_F = Alt.A3_VD_F;

  NI->VD_F3N = Alt.VD_F3N;

  NI->VD_F3B = Alt.VD_F3B;

  NI->TYPE = Alt.TYPE;

  NI->ELEM_DIAGN = Alt.ELEM_DIAGN;

  NI->P_DIAGN_EL = Alt.P_DIAGN_EL;

  NI->A1_P_EL_F = Alt.A1_P_EL_F;

  NI->P_EL_F1N = Alt.P_EL_F1N;

  NI->P_EL_F1B = Alt.P_EL_F1B;

  NI->A2_P_EL_F = Alt.A2_P_EL_F;

  NI->P_EL_F2N = Alt.P_EL_F2N;

  NI->P_EL_F2B = Alt.P_EL_F2B;

  NI->A3_P_EL_F = Alt.A3_P_EL_F;

  NI->P_EL_F3N = Alt.P_EL_F3N;

  NI->P_EL_F3B = Alt.P_EL_F3B;

  NI->SOVM = Alt.SOVM;

  NI->SOVM0 = Alt.SOVM0;

  NI->SOVM1 = Alt.SOVM1;

  return NI;
}

void TLoaderTFS::DoAddParamsBin(THandle AFile, SF_TFE ATfe, TLoaderTFSItemMain* AItem)
{
   int m_cnt = ATfe.ParamCount;
   SF_PARAMALT s_alt;
   for(int i = 0; i <= m_cnt - 1; i++)
   {
      memset(&s_alt, 0, sizeof(s_alt));
      FileRead(AFile, &s_alt, sizeof(s_alt));
      AItem->ListParams->Add(CreateAlternateParamsBin(s_alt));
   }
}

void TLoaderTFS::DoAddMainNodeFromBin(THandle AFile, SF_TFS ATfs)
{
   SF_TFE s_tfe;
   TLoaderTFSMain* ItemMain;
   int m_id, m_typeId, m_sx, m_sy, m_offx, m_offy, m_nextid, m_priorid, m_cnt;
   m_id = ATfs.ID;
   m_typeId = ATfs.TypeID;
   m_sx = ATfs.StartPointX;
   m_sy = ATfs.StartPointY;
   m_offx = ATfs.OffsetX;
   m_offy = ATfs.OffsetY;
   m_nextid = ATfs.NextID;
   m_priorid = ATfs.PriorID;
   m_cnt = ATfs.TFECount;

   ItemMain = AddMainNode(m_id);
   ItemMain->TypeId =  m_typeId;
   ItemMain->StartPoint.x = m_sx;
   ItemMain->StartPoint.y = m_sy;
   ItemMain->OffsetX = m_offx;
   ItemMain->OffsetY = m_offy;
   ItemMain->NextId = m_nextid;
   ItemMain->PriorId = m_priorid;

   for( int i = 0; i <= m_cnt - 1; i++)
   {
     FileRead(AFile, &s_tfe, sizeof(s_tfe));
     m_id = s_tfe.ID;
     m_typeId = s_tfe.TypeID;
     ItemMain->AddTFE(m_id, m_typeId);
     DoAddParamsBin(AFile, s_tfe, ItemMain->FindTFE(m_id));
   }
}


void TLoaderTFS::DoAddAncestorBin(SF_ANCS Ancs)
{
   int m_IdBlock, m_IdShapeAncestor;
   m_IdBlock = Ancs.IdBlock;
   m_IdShapeAncestor = Ancs.IdShapeAncestor;
   AddAncestor(m_IdBlock, m_IdShapeAncestor);
}

void TLoaderTFS::DoAddAlternateBin(THandle AFile, SF_ALT Alt)
{
   TLoaderTFSAlternate* ItemAlternate;
   int m_ID, m_Num, m_NodeStartID, m_NodeEndID, m_Cnt;
   m_ID = Alt.ID;
   m_Num = Alt.Num;
   m_NodeStartID = Alt.NodeStartID;
   m_NodeEndID = Alt.NodeEndID;
   m_Cnt = Alt.Count;


   ItemAlternate = AddAlternate(m_ID, m_Num);
   ItemAlternate->NodeStartID = m_NodeStartID;
   ItemAlternate->NodeEndID = m_NodeEndID;

   for (int i = 0; i <= m_Cnt- 1; i++)
   {
     FileRead(AFile, &m_ID, sizeof(m_ID));
     ItemAlternate->AddAlt(m_ID);
   }
}


bool TLoaderTFS::DoLoadBin(AnsiString AFileName)
{
   AnsiString Errors;
   char m_header[10];
   TLoaderTFSMain* ItemMain;
   SF_TFS s_tfs;
   SF_ANCS s_ancs;
   SF_ALT s_alt;


   THandle HF = THandle(INVALID_HANDLE_VALUE);
   if ( FileExists(AFileName) )
     HF  = FileOpen(AFileName, fmOpenRead);
   if (HF == THandle(INVALID_HANDLE_VALUE) )
   {
     f_ErrorString = "Ошибка загрузки файла!\r\n\r\n";
     FileClose(HF);
     return false;
   }

   //проверим заголовок
   memset(m_header, 0, sizeof(m_header));
   FileRead(HF, m_header, 9);
   if( strcmp(m_header, SF_HADERBIN) != 0 )
   {
     f_ErrorString = "Неправильный формат файла!\r\n\r\n";
     FileClose(HF);
     return false;
   }

   int m_count;
   FileRead(HF, &m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_tfs, 0, sizeof(s_tfs));
     FileRead(HF, &s_tfs, sizeof(s_tfs));
     DoAddMainNodeFromBin(HF, s_tfs);
   }

   FileRead(HF, &m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_ancs, 0, sizeof(s_ancs) );
     FileRead(HF, &s_ancs, sizeof(s_ancs));
     DoAddAncestorBin(s_ancs);
   }

   FileRead(HF, &m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_alt, 0, sizeof(s_alt) );
     FileRead(HF, &s_alt, sizeof(s_alt));
     DoAddAlternateBin(HF, s_alt);
   }
   DoLoadOgrSovmFromBin(HF);
   FileRead(HF, &f_TypeParam, sizeof(f_TypeParam));
   DoLoadTypeDecisionFromBin(HF);
   FileClose(HF);
   return true;

}

void TLoaderTFS::DoAddParamsCanal(TClipCopyTFS* AClipCopy, SF_TFE ATfe, TLoaderTFSItemMain* AItem)
{
   int m_cnt = ATfe.ParamCount;
   SF_PARAMALT s_alt;
   for(int i = 0; i <= m_cnt - 1; i++)
   {
      memset(&s_alt, 0, sizeof(s_alt));
      //FileRead(AFile, &s_alt, sizeof(s_alt));
      AClipCopy->CanalRead(&s_alt, sizeof(s_alt));
      AItem->ListParams->Add(CreateAlternateParamsBin(s_alt));
   }

}


void TLoaderTFS::DoAddMainNodeFromCanal(TClipCopyTFS* AClipCopy, SF_TFS ATfs)
{
   SF_TFE s_tfe;
   TLoaderTFSMain* ItemMain;
   int m_id, m_typeId, m_sx, m_sy, m_offx, m_offy, m_nextid, m_priorid, m_cnt;
   m_id = ATfs.ID;
   m_typeId = ATfs.TypeID;
   m_sx = ATfs.StartPointX;
   m_sy = ATfs.StartPointY;
   m_offx = ATfs.OffsetX;
   m_offy = ATfs.OffsetY;
   m_nextid = ATfs.NextID;
   m_priorid = ATfs.PriorID;
   m_cnt = ATfs.TFECount;

   ItemMain = AddMainNode(m_id);
   ItemMain->TypeId =  m_typeId;
   ItemMain->StartPoint.x = m_sx;
   ItemMain->StartPoint.y = m_sy;
   ItemMain->OffsetX = m_offx;
   ItemMain->OffsetY = m_offy;
   ItemMain->NextId = m_nextid;
   ItemMain->PriorId = m_priorid;

   for( int i = 0; i <= m_cnt - 1; i++)
   {
     //FileRead(AFile, &s_tfe, sizeof(s_tfe));
     AClipCopy->CanalRead(&s_tfe, sizeof(s_tfe));
     m_id = s_tfe.ID;
     m_typeId = s_tfe.TypeID;
     ItemMain->AddTFE(m_id, m_typeId);
     DoAddParamsCanal(AClipCopy, s_tfe, ItemMain->FindTFE(m_id));
   }
}

void TLoaderTFS::DoAddAlternateCanal(TClipCopyTFS* AClipCopy, SF_ALT Alt)
{
   TLoaderTFSAlternate* ItemAlternate;
   int m_ID, m_Num, m_NodeStartID, m_NodeEndID, m_Cnt;
   m_ID = Alt.ID;
   m_Num = Alt.Num;
   m_NodeStartID = Alt.NodeStartID;
   m_NodeEndID = Alt.NodeEndID;
   m_Cnt = Alt.Count;


   ItemAlternate = AddAlternate(m_ID, m_Num);
   ItemAlternate->NodeStartID = m_NodeStartID;
   ItemAlternate->NodeEndID = m_NodeEndID;

   for (int i = 0; i <= m_Cnt- 1; i++)
   {
     //FileRead(AFile, &m_ID, sizeof(m_ID));
     AClipCopy->CanalRead(&m_ID, sizeof(m_ID));
     ItemAlternate->AddAlt(m_ID);
   }
}

void TLoaderTFS::DoLoadCanal(TClipCopyTFS* AClipCopy)
{
   TLoaderTFSMain* ItemMain;
   SF_TFS s_tfs;
   SF_ANCS s_ancs;
   SF_ALT s_alt;

   AClipCopy->CanalSeek(0);
   int m_count;
//   FileRead(HF, &m_count, sizeof(m_count));
   AClipCopy->CanalRead(&m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_tfs, 0, sizeof(s_tfs));
     //FileRead(HF, &s_tfs, sizeof(s_tfs));
     AClipCopy->CanalRead(&s_tfs, sizeof(s_tfs));
     DoAddMainNodeFromCanal(AClipCopy, s_tfs);
   }

//   FileRead(HF, &m_count, sizeof(m_count));
   AClipCopy->CanalRead(&m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_ancs, 0, sizeof(s_ancs) );
     //FileRead(HF, &s_ancs, sizeof(s_ancs));
     AClipCopy->CanalRead(&s_ancs, sizeof(s_ancs));
     DoAddAncestorBin(s_ancs);
   }

//   FileRead(HF, &m_count, sizeof(m_count));
   AClipCopy->CanalRead(&m_count, sizeof(m_count));
   for (int i = 0; i <= m_count - 1; i++)
   {
     memset(&s_alt, 0, sizeof(s_alt) );
     //FileRead(HF, &s_alt, sizeof(s_alt));
     AClipCopy->CanalRead( &s_alt, sizeof(s_alt));
     DoAddAlternateCanal(AClipCopy, s_alt);
   }
}


void TLoaderTFS::LoadFromCanal(TClipCopyTFS* AClipCopy)
{
   Clear();
   DoLoadCanal(AClipCopy);
}

void TLoaderTFS::DoLoadOgrSovmFromXML(TGlsXmlNode* ANode)
{
   int Row, Col, Value;
   bool bR, bC, bV;
   TGlsXmlNode* xml_item;
   TGlsXmlElement* TodoElement;
   if (f_OgrSovm)
   {
     f_OgrSovm->Clear();
     xml_item = ANode->FirstChild();
     while(xml_item)
     {
       if ( strcmp(xml_item->Value(), "OGR") == 0 )
       {
         TodoElement = xml_item->ToElement();
         bR = TodoElement->QueryIntAttribute("Row" , &Row) == TGLSXML_SUCCESS;
         bC = TodoElement->QueryIntAttribute("Col" , &Col) == TGLSXML_SUCCESS;
         bV = TodoElement->QueryIntAttribute("Value" , &Value) == TGLSXML_SUCCESS;
         if (bR && bC && bV)
            f_OgrSovm->Items[Row][Col] = Value;
       }
       xml_item = xml_item->NextSibling();
     }
   }
}

void TLoaderTFS::DoLoadOgrSovmFromBin(THandle AFile)
{
  struct s_ogr
  {
     int Row;
     int Col;
     int Value;
  };
  int cnt;
  s_ogr tmp;
  if (f_OgrSovm)
  {
    f_OgrSovm->Clear();
    FileRead(AFile, &cnt, sizeof(cnt));
    for (int i = 0; i <= cnt - 1; i++)
    {
      FileRead(AFile, &tmp, sizeof(tmp));
      f_OgrSovm->Items[tmp.Row][tmp.Col] = tmp.Value;
    }
  }
}


void TLoaderTFS::DoLoadTypeDecisionFromXML(TGlsXmlNode* ANode)
{
   int m_type, m_sovm, m_atr;
   double m_val;
   TGlsXmlNode* xml_params;
   TGlsXmlElement* TodoElement;
   if (f_OgrSovm)
   {
	 TodoElement = ANode->ToElement();
	 TodoElement->QueryIntAttribute("Type" , &m_type);
	 TodoElement->QueryIntAttribute("Sovm" , &m_sovm);
	 xml_params = ANode->FirstChild();
	 TodoElement = xml_params->ToElement();
	 switch(m_type)
	 {
	   case ZAD_1:
		 opt_sadacha->CheckBox1->Checked = true;
		 TodoElement->QueryIntAttribute("V", &m_atr);
		 opt_sadacha->CheckBox7->Checked = m_atr;

		 TodoElement->QueryIntAttribute("T", &m_atr);
		 opt_sadacha->CheckBox8->Checked = m_atr;

		 TodoElement->QueryDoubleAttribute("VD", &m_val);
		 opt_sadacha->Edit4->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("TD", &m_val);
		 opt_sadacha->Edit5->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;


	   case ZAD_2:
		 opt_sadacha->CheckBox2->Checked = true;
		 TodoElement->QueryIntAttribute("V", &m_atr);
		 opt_sadacha->CheckBox7->Checked = m_atr;

		 TodoElement->QueryIntAttribute("B", &m_atr);
		 opt_sadacha->CheckBox8->Checked = m_atr;

		 TodoElement->QueryDoubleAttribute("VD", &m_val);
		 opt_sadacha->Edit6->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("BD", &m_val);
		 opt_sadacha->Edit7->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;

	   case ZAD_3:
		 opt_sadacha->CheckBox3->Checked = true;
		 TodoElement->QueryIntAttribute("B", &m_atr);
		 opt_sadacha->CheckBox7->Checked = m_atr;

		 TodoElement->QueryIntAttribute("T", &m_atr);
		 opt_sadacha->CheckBox8->Checked = m_atr;

		 TodoElement->QueryDoubleAttribute("BD", &m_val);
		 opt_sadacha->Edit8->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("TD", &m_val);
		 opt_sadacha->Edit9->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;

	   case ZAD_4:
		 opt_sadacha->CheckBox4->Checked = true;

		 TodoElement->QueryDoubleAttribute("C1", &m_val);
		 opt_sadacha->Edit10->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C2", &m_val);
		 opt_sadacha->Edit11->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C3", &m_val);
		 opt_sadacha->Edit12->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;
	   case ZAD_5:
		 opt_sadacha->CheckBox5->Checked = true;

		 TodoElement->QueryDoubleAttribute("C1", &m_val);
		 opt_sadacha->Edit1->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C2", &m_val);
		 opt_sadacha->Edit2->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C3", &m_val);
		 opt_sadacha->Edit3->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;
	   case ZAD_6:
		 opt_sadacha->CheckBox6->Checked = true;

		 TodoElement->QueryDoubleAttribute("C1", &m_val);
		 opt_sadacha->Edit13->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C2", &m_val);
		 opt_sadacha->Edit14->Text = float_2_string(m_val, 6);

		 TodoElement->QueryDoubleAttribute("C3", &m_val);
		 opt_sadacha->Edit15->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;
	 }
   }
}


void TLoaderTFS::DoLoadTypeDecisionFromBin(THandle AFile)
{
   int m_type, m_sovm, m_atr;
   double m_val;
   if (f_OgrSovm)
   {
	 FileRead(AFile, &m_type, sizeof(m_type));
	 FileRead(AFile, &m_sovm, sizeof(m_sovm));

     switch(m_type)
     {
       case ZAD_1:
         opt_sadacha->CheckBox1->Checked = true;
         FileRead(AFile, &m_atr, sizeof(m_atr));
         opt_sadacha->CheckBox7->Checked = m_atr;

         FileRead(AFile, &m_atr, sizeof(m_atr));
         opt_sadacha->CheckBox8->Checked = m_atr;

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit4->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit5->Text = float_2_string(m_val, 6);

         opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;


	   case ZAD_2:
		 opt_sadacha->CheckBox2->Checked = true;
		 FileRead(AFile, &m_atr, sizeof(m_atr));
		 opt_sadacha->CheckBox7->Checked = m_atr;

		 FileRead(AFile, &m_atr, sizeof(m_atr));
		 opt_sadacha->CheckBox8->Checked = m_atr;

		 FileRead(AFile, &m_val, sizeof(m_val));
		 opt_sadacha->Edit6->Text = float_2_string(m_val, 6);

		 FileRead(AFile, &m_val, sizeof(m_val));
		 opt_sadacha->Edit7->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;

	   case ZAD_3:
		 opt_sadacha->CheckBox3->Checked = true;
		 FileRead(AFile, &m_atr, sizeof(m_atr));
         opt_sadacha->CheckBox7->Checked = m_atr;

         FileRead(AFile, &m_atr, sizeof(m_atr));
         opt_sadacha->CheckBox8->Checked = m_atr;

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit8->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit9->Text = float_2_string(m_val, 6);

         opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
         break;

       case ZAD_4:
         opt_sadacha->CheckBox4->Checked = true;

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit10->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit11->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit12->Text = float_2_string(m_val, 6);

         opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
         break;

       case ZAD_5:
         opt_sadacha->CheckBox5->Checked = true;

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit1->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit2->Text = float_2_string(m_val, 6);

         FileRead(AFile, &m_val, sizeof(m_val));
         opt_sadacha->Edit3->Text = float_2_string(m_val, 6);

         opt_sadacha->CheckBox9->Checked = m_sovm;
		 opt_sadacha->Button1Click(NULL);
		 break;
	   case ZAD_6:
		 opt_sadacha->CheckBox6->Checked = true;

		 FileRead(AFile, &m_val, sizeof(m_val));
		 opt_sadacha->Edit13->Text = float_2_string(m_val, 6);

		 FileRead(AFile, &m_val, sizeof(m_val));
		 opt_sadacha->Edit14->Text = float_2_string(m_val, 6);

		 FileRead(AFile, &m_val, sizeof(m_val));
		 opt_sadacha->Edit15->Text = float_2_string(m_val, 6);

		 opt_sadacha->CheckBox9->Checked = m_sovm;
         opt_sadacha->Button1Click(NULL);
         break;
     }
   }
}
