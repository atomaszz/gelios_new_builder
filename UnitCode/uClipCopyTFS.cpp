//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uClipCopyTFS.h"
#include "uGlsAtmCommon.h"
#include "uPaintgrids.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TList *lc_ClipCopy;

int ClipCopy_CompareNode(void* A, void* B)
{
   TAlternateTreeList* m_A = static_cast<TAlternateTreeList*>(A);
   TAlternateTreeList* m_B = static_cast<TAlternateTreeList*>(B);
   if(m_A->ID > m_B->ID)
     return 1;
   if(m_A->ID < m_B->ID)
     return -1;
   if (m_A->ID == m_B->ID)
   {
      if (m_A->Num > m_B->Num)
        return 1;
      if (m_A->Num < m_B->Num)
        return -1;
   }
   return 0;
}

bool ClipCopy_Inorder(void* A)
{
   TAlternateTreeList* m_A = static_cast<TAlternateTreeList*>(A);
   lc_ClipCopy->Add(m_A);
   return true;
}


TClipCopyTFS::TClipCopyTFS(HWND AOwner, DWORD ABuf)
{
   f_Seek = 0;
   f_OwnerForm = AOwner;
   f_Canal = new TGlsIPC;
   lc_ClipCopy = new TList;
   CanalInit(ABuf);
}

TClipCopyTFS::~TClipCopyTFS()
{
   delete f_Canal;
   delete lc_ClipCopy;
}

void TClipCopyTFS::CanalInit(DWORD ABuf)
{
   f_Canal->Lock();
   f_Canal->CreateIPCMMF(ABuf);
   f_Canal->Unlock();
}

void TClipCopyTFS::CanalSeek(DWORD AOffset)
{
   f_Seek = AOffset;
}

bool TClipCopyTFS::CanalWrite(const void* pBuf,  DWORD dwBufSize)
{
  f_Canal->Lock();
  bool res = f_Canal->WriteIPCMMF(pBuf, dwBufSize, f_Seek);
  f_Canal->Unlock();
  if (res)
    f_Seek+=dwBufSize;
  return res;
}

DWORD TClipCopyTFS::CanalLength()
{
  f_Canal->Lock();
  DWORD res = f_Canal->Length();
  f_Canal->Unlock();
  return res;
}

DWORD TClipCopyTFS::CanalRead(void* pBuf, DWORD dwBufSize)
{
  f_Canal->Lock();
  DWORD res = f_Canal->ReadIPCMMF(pBuf, dwBufSize, f_Seek);
  f_Canal->Unlock();
  f_Seek+=res;
  return res;
}

void TClipCopyTFS::DoLoadMainItem(TMainTreeList* AList, TDynamicArray *D,
  TDynamicArray *AStack)
{
   TTreeListTFS* TFS;
   TTreeListItem* TFE;
   TAlternateTreeList* AT;
   for(int i = 0; i <= AList->ItemCount - 1; i++)
   {
     AT = AList->AlternateItem[i];
     for(int j = 0; j <= AT->ItemCount - 1; j++)
     {
        TFS = AT->TreeTFSItem[j];
        D->Append(TFS->BaseWorkShape);
        for(int k = 0; k <= TFS->ItemCount - 1; k++)
        {
           TFE = TFS->TreeTFEItem[k];
           if (TFE->MainNode)
             AStack->InsertToFirst(TFE->MainNode);
        }
     }
   }
}

void TClipCopyTFS::DoLoadMain(TTreeList* ATree, TDynamicArray *D)
{
   TMainTreeList* P = ATree->MainTreeList;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(P);
   P = static_cast<TMainTreeList*>(m_Stack->Pop());
   while(P)
   {
     DoLoadMainItem(P, D, m_Stack);
     P = static_cast<TMainTreeList*>(m_Stack->Pop());
   }
   delete m_Stack;
}

void TClipCopyTFS::DoLoadAncsItem(int AParentShapeID, TMainTreeList* AList,
  TDynamicArray *D, TDynamicArray *AStack)
{
   TTreeListTFS* TFS;
   TTreeListItem* TFE;
   TAlternateTreeList* AT;
   for(int i = 0; i <= AList->ItemCount - 1; i++)
   {
     AT = AList->AlternateItem[i];
     for(int j = 0; j <= AT->ItemCount - 1; j++)
     {
        TFS = AT->TreeTFSItem[j];
        if (AList->Level != AParentShapeID )
          D->AppendInteger(AList->Level, TFS->BaseWorkShape);
        for(int k = 0; k <= TFS->ItemCount - 1; k++)
        {
           TFE = TFS->TreeTFEItem[k];
           if (TFE->MainNode)
             AStack->InsertToFirst(TFE->MainNode);
        }
     }
   }
}



void TClipCopyTFS::DoLoadAncs(int AParentShapeID, TTreeList* ATree, TDynamicArray *D)
{
   TMainTreeList* P = ATree->MainTreeList;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(P);
   P = static_cast<TMainTreeList*>(m_Stack->Pop());
   while(P)
   {
     DoLoadAncsItem(AParentShapeID, P, D, m_Stack);
     P = static_cast<TMainTreeList*>(m_Stack->Pop());
   }
   delete m_Stack;
}

void TClipCopyTFS::DoLoadAltItem(TMainTreeList* AList, TDynamicArray *D,
  TDynamicArray *AStack)
{
   TTreeListTFS* TFS;
   TTreeListItem* TFE;
   TAlternateTreeList* AT;
   for(int i = 0; i <= AList->ItemCount - 1; i++)
   {
     AT = AList->AlternateItem[i];
     if (!AT->MainAlternative || !AT->NodeEnd)
       D->Append(AT);
     for(int j = 0; j <= AT->ItemCount - 1; j++)
     {
        TFS = AT->TreeTFSItem[j];
        for(int k = 0; k <= TFS->ItemCount - 1; k++)
        {
           TFE = TFS->TreeTFEItem[k];
           if (TFE->MainNode)
             AStack->InsertToFirst(TFE->MainNode);
        }
     }
   }
}


void TClipCopyTFS::DoLoadAlt(TTreeList* ATree, TDynamicArray *D)
{
   TMainTreeList* P = ATree->MainTreeList;
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(P);
   P = static_cast<TMainTreeList*>(m_Stack->Pop());
   while(P)
   {
     DoLoadAltItem(P, D, m_Stack);
     P = static_cast<TMainTreeList*>(m_Stack->Pop());
   }
   delete m_Stack;
}


void TClipCopyTFS::SortAltList(TDynamicArray* D)
{
   lc_ClipCopy->Clear();
   TGlsBinaryTree* B = new TGlsBinaryTree(ClipCopy_CompareNode);
   for (int i = 0; i <= D->Count - 1; i++)
     B->insert(D->Items[i]);

   B->inorder(ClipCopy_Inorder);
   D->Clear();
   for (int i = 0; i <= lc_ClipCopy->Count - 1; i++)
      D->Append(lc_ClipCopy->Items[i]);
   delete B;
}

void TClipCopyTFS::RenumAltList(TDynamicArray* D)
{
   int old_id;
   int c_id, c_num;
   TAlternateTreeList* AT;
   c_id = 0;
   c_num = 0;
   old_id = -1;
   for(int i = 0; i <= D->Count - 1; i++)
   {
      AT = static_cast<TAlternateTreeList*>(D->Items[i]);
      if(AT->ID == old_id)
      {
        c_num++;
        AT->Num = c_num;
      }
      else
      {
        if (i)
          c_num = 1;
        else
          c_num = 0;
          
        AT->ID = c_id;
        AT->Num = c_num;
        old_id = c_id;
        c_id++;
      }
   }
}

bool TClipCopyTFS::SaveParamAlternateToCanal(TBaseShape* ATFE, SF_TFE A_tfe)
{
   TParamAlternativeItem* mi;
   SF_PARAMALT sf_param;
   int param_cnt = 0;
   if(ATFE->ParamAlt)
     param_cnt = ATFE->ParamAlt->Count;
   A_tfe.ParamCount = param_cnt;
//   FileWrite(fFile, &A_tfe, sizeof(A_tfe));
   if (!CanalWrite(&A_tfe, sizeof(A_tfe)))
     return false;

   for(int i = 0; i <= param_cnt - 1; i++)
     {
       memset(&sf_param, 0, sizeof(sf_param));
       mi = ATFE->ParamAlt->Items[i];

       sf_param.NUMBER = mi->NUMBER;
       strcpy(sf_param.PRED_ISTOR, mi->PRED_ISTOR.c_str());
       strcpy(sf_param.SOSTAV, mi->SOSTAV.c_str());
       strcpy(sf_param.NAME, mi->NAME.c_str());
       strcpy(sf_param.FUNCTION2, mi->FUNCTION2.c_str());
       strcpy(sf_param.ELEMENT, mi->ELEMENT.c_str());
       strcpy(sf_param.PREDICAT, mi->PREDICAT.c_str());
       sf_param.B = mi->B;
       sf_param.T = mi->T;
       sf_param.V = mi->V;
       sf_param.A1_B_F = mi->A1_B_F;
       sf_param.B_F1N = mi->B_F1N;
       sf_param.B_F1B = mi->B_F1B;
       sf_param.A2_B_F = mi->A2_B_F;
       sf_param.B_F2N = mi->B_F2N;
       sf_param.B_F2B = mi->B_F2B;
       sf_param.A3_B_F = mi->A3_B_F;
       sf_param.B_F3N = mi->B_F3N;
       sf_param.B_F3B = mi->B_F3B;
       sf_param.A1_T_F = mi->A1_T_F;
       sf_param.T_F1N = mi->T_F1N;
       sf_param.T_F1B = mi->T_F1B;
       sf_param.A2_T_F = mi->A2_T_F;
       sf_param.T_F2N = mi->T_F2N;
       sf_param.T_F2B = mi->T_F2B;
       sf_param.A3_T_F = mi->A3_T_F;
       sf_param.T_F3N = mi->T_F3N;
       sf_param.T_F3B = mi->T_F3B;
       sf_param.A1_V_F = mi->A1_V_F;
       sf_param.V_F1N = mi->V_F1N;
       sf_param.V_F1B = mi->V_F1B;
       sf_param.A2_V_F = mi->A2_V_F;
       sf_param.V_F2N = mi->V_F2N;
       sf_param.V_F2B = mi->V_F2B;
       sf_param.A3_V_F = mi->A3_V_F;
       sf_param.V_F3N = mi->V_F3N;
       sf_param.V_F3B = mi->V_F3B;
       sf_param.K_11 = mi->K_11;
       sf_param.K_00 = mi->K_00;
       sf_param.T_F = mi->T_F;
       sf_param.V_F = mi->V_F;
       sf_param.A1_K11_F = mi->A1_K11_F;
       sf_param.K11_F1N = mi->K11_F1N;
       sf_param.K11_F1B = mi->K11_F1B;
       sf_param.A2_K11_F = mi->A2_K11_F;
       sf_param.K11_F2N = mi->K11_F2N;
       sf_param.K11_F2B = mi->K11_F2B;
       sf_param.A3_K11_F = mi->A3_K11_F;
       sf_param.K11_F3N = mi->K11_F3N;
       sf_param.K11_F3B = mi->K11_F3B;
       sf_param.A1_K00_F = mi->A1_K00_F;
       sf_param.K00_F1N = mi->K00_F1N;
       sf_param.K00_F1B = mi->K00_F1B;
       sf_param.A2_K00_F = mi->A2_K00_F;
       sf_param.K00_F2N = mi->K00_F2N;
       sf_param.K00_F2B = mi->K00_F2B;
       sf_param.A3_K00_F = mi->A3_K00_F;
       sf_param.K00_F3N = mi->K00_F3N;
       sf_param.K00_F3B = mi->K00_F3B;
       sf_param.A1_TF_F = mi->A1_TF_F;
       sf_param.TF_F1N = mi->TF_F1N;
       sf_param.TF_F1B = mi->TF_F1B;
       sf_param.A2_TF_F = mi->A2_TF_F;
       sf_param.TF_F2N = mi->TF_F2N;
       sf_param.TF_F2B = mi->TF_F2B;
       sf_param.A3_TF_F = mi->A3_TF_F;
       sf_param.TF_F3N = mi->TF_F3N;
       sf_param.TF_F3B = mi->TF_F3B;
       sf_param.A1_VF_F = mi->A1_VF_F;
       sf_param.VF_F1N = mi->VF_F1N;
       sf_param.VF_F1B = mi->VF_F1B;
       sf_param.A2_VF_F = mi->A2_VF_F;
       sf_param.VF_F2N = mi->VF_F2N;
       sf_param.VF_F2B = mi->VF_F2B;
       sf_param.A3_VF_F = mi->A3_VF_F;
       sf_param.VF_F3N = mi->VF_F3N;
       sf_param.VF_F3B = mi->VF_F3B;
       sf_param.P_11 = mi->P_11;
       sf_param.P_00 = mi->P_00;
       sf_param.T_D = mi->T_D;
       sf_param.V_D = mi->V_D;
       sf_param.A1_P11_F = mi->A1_P11_F;
       sf_param.P11_F1N = mi->P11_F1N;
       sf_param.P11_F1B = mi->P11_F1B;
       sf_param.A2_P11_F = mi->A2_P11_F;
       sf_param.P11_F2N = mi->P11_F2N;
       sf_param.P11_F2B = mi->P11_F2B;
       sf_param.A3_P11_F = mi->A3_P11_F;
       sf_param.P11_F3N = mi->P11_F3N;
       sf_param.P11_F3B = mi->P11_F3B;
       sf_param.A1_P00_F = mi->A1_P00_F;
       sf_param.P00_F1N = mi->P00_F1N;
       sf_param.P00_F1B = mi->P00_F1B;
       sf_param.A2_P00_F = mi->A2_P00_F;
       sf_param.P00_F2N = mi->P00_F2N;
       sf_param.P00_F2B = mi->P00_F2B;
       sf_param.A3_P00_F = mi->A3_P00_F;
       sf_param.P00_F3N = mi->P00_F3N;
       sf_param.P00_F3B = mi->P00_F3B;
       sf_param.A1_TD_F = mi->A1_TD_F;
       sf_param.TD_F1N = mi->TD_F1N;
       sf_param.TD_F1B = mi->TD_F1B;
       sf_param.A2_TD_F = mi->A2_TD_F;
       sf_param.TD_F2N = mi->TD_F2N;
       sf_param.TD_F2B = mi->TD_F2B;
       sf_param.A3_TD_F = mi->A3_TD_F;
       sf_param.TD_F3N = mi->TD_F3N;
       sf_param.TD_F3B = mi->TD_F3B;
       sf_param.A1_VD_F = mi->A1_VD_F;
       sf_param.VD_F1N = mi->VD_F1N;
       sf_param.VD_F1B = mi->VD_F1B;
       sf_param.A2_VD_F = mi->A2_VD_F;
       sf_param.VD_F2N = mi->VD_F2N;
       sf_param.VD_F2B = mi->VD_F2B;
       sf_param.A3_VD_F = mi->A3_VD_F;
       sf_param.VD_F3N = mi->VD_F3N;
       sf_param.VD_F3B = mi->VD_F3B;
       sf_param.TYPE = mi->TYPE;
       strcpy(sf_param.ELEM_DIAGN, mi->ELEM_DIAGN.c_str());
       sf_param.P_DIAGN_EL = mi->P_DIAGN_EL;
       sf_param.A1_P_EL_F = mi->A1_P_EL_F;
       sf_param.P_EL_F1N = mi->P_EL_F1N;
       sf_param.P_EL_F1B = mi->P_EL_F1B;
       sf_param.A2_P_EL_F = mi->A2_P_EL_F;
       sf_param.P_EL_F2N = mi->P_EL_F2N;
       sf_param.P_EL_F2B = mi->P_EL_F2B;
       sf_param.A3_P_EL_F = mi->A3_P_EL_F;
       sf_param.P_EL_F3N = mi->P_EL_F3N;
       sf_param.P_EL_F3B = mi->P_EL_F3B;
       sf_param.SOVM = mi->SOVM;
       sf_param.SOVM0 = mi->SOVM0;
       sf_param.SOVM1 = mi->SOVM1;
//       FileWrite(fFile, &sf_param, sizeof(sf_param));
       if (!CanalWrite(&sf_param, sizeof(sf_param)))
         return false;
     }
   return true;
}


bool TClipCopyTFS::DoSaveMain(TDynamicArray* D)
{
//   TNodeMain *CurrNode;
//   TNodeAncestor *CurrAncestor;
//   TNodeAlt *CurrAlt;
   TBaseWorkShape *WS, *T;
   TBaseShape* ShapeTFE;
   int m_start_x, m_start_y, m_blockid, m_nextid, m_priorid;
   int m_offset_x, m_offset_y;
   int m_typeTfs;
   int m_Block;
   int ws_cnt, mn_count;
   SF_TFS s_tfs;
   SF_TFE s_tfe;



   mn_count = D->Count;
//   FileWrite(fFile, SF_HADERBIN, strlen(SF_HADERBIN));
//   FileWrite(fFile, &mn_count, sizeof(mn_count));
   if (!CanalWrite(&mn_count, sizeof(mn_count)))
     return false;

   for (int i = 0; i <= mn_count - 1; i++)
   {
      memset(&s_tfs, 0, sizeof(s_tfs));
      WS = static_cast<TBaseWorkShape*>(D->Items[i]);
      if (i==0)
      {
        m_start_x = 40; //WS->BaseStartPoint.x + WS->BaseOffsetX;
        m_start_y = 100;//WS->BaseStartPoint.y + WS->BaseOffsetY;
      }
      else
      {
        m_start_x = WS->BaseStartPoint.x;
        m_start_y = WS->BaseStartPoint.y;
      }
      if (i==0)
      {
        m_offset_x = 0;
        m_offset_y = 0;
      }
      else
      {
        m_offset_x = WS->BaseOffsetX;
        m_offset_y = WS->BaseOffsetY;
      }
      m_blockid = WS->BlockId;
      m_nextid = m_priorid = -1;

      T = FindNextWorkShape(WS);
      if (T && D->Find(T))
        m_nextid = T->BlockId;
      T = FindPriorWorkShape(WS);
      if (T && D->Find(T))
        m_priorid = T->BlockId;

      m_typeTfs = WS->TypeShape;
      ws_cnt = WS->WorkShapesCount;

      s_tfs.ID = m_blockid;
      s_tfs.TypeID = m_typeTfs;
      s_tfs.StartPointX = m_start_x;
      s_tfs.StartPointY = m_start_y;
      s_tfs.OffsetX = m_offset_x;
      s_tfs.OffsetY = m_offset_y;
      s_tfs.NextID = m_nextid;
      s_tfs.PriorID = m_priorid;
      s_tfs.TFECount = ws_cnt;

//      FileWrite(fFile, &s_tfs, sizeof(s_tfs));
      if (!CanalWrite(&s_tfs, sizeof(s_tfs)))
        return false;

      for (int j = 0; j <= ws_cnt - 1; j++ )
      {
         memset(&s_tfe, 0, sizeof(s_tfe));
         ShapeTFE = static_cast<TBaseShape*>(WS->GetWorkShape(j));
         s_tfe.ID = ShapeTFE->ID;
         s_tfe.TypeID = ShapeTFE->TypeShape;
         if(!SaveParamAlternateToCanal(ShapeTFE, s_tfe))
           return false;
      }
   }
   return true;
}


bool TClipCopyTFS::DoSaveAncs(TDynamicArray* D)
{
   SF_ANCS s_ancs;
   int Parent_ID;
   TDynamicArrayItem* Item;
   TBaseWorkShape* W;
   int an_count = D->Count;
//   FileWrite(fFile, &an_count, sizeof(an_count));
   if (!CanalWrite(&an_count, sizeof(an_count)))
      return false;

   for (int i = 0; i <= an_count - 1; i++)
   {
     memset(&s_ancs, 0, sizeof(s_ancs) );
     Item = D->Position[i];
     W  = static_cast<TBaseWorkShape*>(Item->P);
     Parent_ID = Item->Int_Value;
     s_ancs.IdBlock = W->BlockId;
     s_ancs.IdShapeAncestor = Parent_ID;
//     FileWrite(fFile, &s_ancs, sizeof(s_ancs));
     if (!CanalWrite(&s_ancs, sizeof(s_ancs)))
       return false;
   }
   return true;
}

bool TClipCopyTFS::DoSaveAlt(TDynamicArray* D)
{
   SF_ALT s_alt;
   int m_nextid, m_priorid, item_count;
   TAlternateTreeList* AT;
   int al_count = D->Count;
//   FileWrite(fFile, &al_count, sizeof(al_count));
   if (!CanalWrite(&al_count, sizeof(al_count)))
      return false;

   for(int i = 0; i <= al_count - 1; i++ )
   {
      memset(&s_alt, 0, sizeof(s_alt));
      AT = static_cast<TAlternateTreeList*>(D->Items[i]);
      s_alt.ID = AT->ID;
      s_alt.Num = AT->Num;
      m_nextid = m_priorid = -1;
      if (AT->NodeStart)
        m_nextid = AT->NodeStart->WorkShape->BlockId;
      if (AT->NodeEnd)
        m_priorid = AT->NodeEnd->WorkShape->BlockId;

      s_alt.NodeStartID = m_nextid;
      s_alt.NodeEndID = m_priorid;

      item_count = AT->ItemCount;
      s_alt.Count = item_count;
//      FileWrite(fFile, &s_alt, sizeof(s_alt));
      if (!CanalWrite(&s_alt, sizeof(s_alt)))
         return false;


      for (int  j = 0; j <= item_count - 1; j++ )
      {
        TTreeListTFS* TFS = AT->TreeTFSItem[j];
        int m_Block = TFS->BaseWorkShape->BlockId;
//        FileWrite(fFile, &m_Block, sizeof(m_Block));
        if (!CanalWrite(&m_Block, sizeof(m_Block)))
          return false;

      }
   }
   return true;
}

bool TClipCopyTFS::CopyTfsList(TListNode* AListNode, int AParentShapeID,
  TBaseWorkShape* AWS, TBaseWorkShape* AWE)
{
   TDynamicArray *DMain = new TDynamicArray;
   TDynamicArray *DAncs = new TDynamicArray;
   TDynamicArray *DAlt = new TDynamicArray;
   TTreeList* m_TreeList = new TTreeList;

   m_TreeList->FillTreeFromList(AListNode, AParentShapeID, AWS, AWE);
   DoLoadMain(m_TreeList, DMain);
   DoLoadAncs(AParentShapeID, m_TreeList, DAncs);
   DoLoadAlt(m_TreeList, DAlt);
  // SortAltList(DAlt);
  // RenumAltList(DAlt);

   CanalSeek(0);
   bool res = DoSaveMain(DMain);
   if (res)
     res = DoSaveAncs(DAncs);
   if (res)
     res = DoSaveAlt(DAlt);

   delete m_TreeList;
   delete DAlt;
   delete DAncs;
   delete DMain;
   return res;
}

TBaseWorkShape* TClipCopyTFS::FindNextWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETNEXTWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}


TBaseWorkShape* TClipCopyTFS::FindPriorWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETPRIORWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}

