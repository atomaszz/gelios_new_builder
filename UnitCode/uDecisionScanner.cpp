//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDecisionScanner.h"
#include "uMessengers.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TDecisionScannerItemTFS::TDecisionScannerItemTFS()
{
  f_TFS = NULL;
  f_List = new TList;
}

TDecisionScannerItemTFS::~TDecisionScannerItemTFS()
{
  for(int i = 0; i <= f_List->Count - 1; i++)
  {
    TDecisionScannerItemTFE* Item = static_cast<TDecisionScannerItemTFE*>(f_List->Items[i]);
    delete Item;
  }
  delete f_List;
}


TDecisionScannerItemTFE* __fastcall TDecisionScannerItemTFS::GetTFEItem(int AIndex)
{
  if (AIndex >= 0 && AIndex <= f_List->Count - 1)
    return static_cast<TDecisionScannerItemTFE*>(f_List->Items[AIndex]);
  else
    return NULL;
}

TDecisionScannerItemTFE* TDecisionScannerItemTFS::CreateTFE()
{
  TDecisionScannerItemTFE* Item  = new TDecisionScannerItemTFE;
  f_List->Add(Item);
  return Item;
}

int TDecisionScannerItemTFS::GetMinShapeID()
{
  int res = -1;
  TDecisionScannerItemTFE* mTfe;
  if (f_List->Count > 0)
  {
    mTfe = static_cast<TDecisionScannerItemTFE*>(f_List->Items[0]);
    res = mTfe->TFE->ID;
    for(int i = 1; i <= f_List->Count - 1; i++)
    {
      mTfe = static_cast<TDecisionScannerItemTFE*>(f_List->Items[i]);
      if (res > mTfe->TFE->ID)
        res = mTfe->TFE->ID;
    }
  }
  return res;  
}

//----------------------- TDecisionScanner -------------------------------------
TDecisionScanner::TDecisionScanner()
{
  f_List = new TList;
}

TDecisionScanner::~TDecisionScanner()
{
  FreeList();
  delete f_List;
}

void TDecisionScanner::FreeList()
{
  TDecisionScannerItemTFS* Item;
  for(int i = 0; i <= f_List->Count - 1; i++)
  {
    Item = static_cast<TDecisionScannerItemTFS*>(f_List->Items[i]);
    delete Item;
  }
  f_List->Clear();
}

TDecisionScannerItemTFS* TDecisionScanner::FindTFS(TBaseWorkShape* ATFS)
{
  TDecisionScannerItemTFS* Item;
  for(int i = 0; i <= f_List->Count - 1; i++)
  {
    Item = static_cast<TDecisionScannerItemTFS*>(f_List->Items[i]);
    if (Item->TFS == ATFS)
      return Item;
  }
  return NULL;
}

void TDecisionScanner::LoadTFE(int ATfeID, int AParamAltId)
{
  TBaseShape* BS = NULL;
  TDecisionScannerItemTFS* mTfs;
  TDecisionScannerItemTFE* mTfe;
  TBaseWorkShape* BW = reinterpret_cast<TBaseWorkShape*>(GMess->SendMess(6, ATfeID, 0));
  if (BW)
  {
    mTfs = FindTFS(BW);
    if (!mTfs)
    {
      mTfs = new TDecisionScannerItemTFS;
      mTfs->TFS = BW;
      f_List->Add(mTfs);
    }
    mTfe = mTfs->CreateTFE();
    for(int i = 0; i <= BW->WorkShapesCount - 1; i++)
    {
      BS = BW->GetWorkShape(i);
      if (BS->ID == ATfeID)
        break;
    }
    mTfe->TFE = BS;
    if (AParamAltId > 0)
      mTfe->Alternative = BS->ParamAlt->Items[AParamAltId - 1];
  }
}

void TDecisionScanner::ScanTFE(char* AStr)
{
  int tfe_num, alt_num;
  tfe_num = alt_num = 0;
  char par[32];
  int dln = strlen(AStr);
  memset(par, 0, sizeof(par));
  int j = 0;
  for(int i = 0; i <= dln - 1; i++)
  {
    if ( (AStr[i] == ':') || (AStr[i] == '.') )
    {
      tfe_num = atoi(par);
      memset(par, 0, sizeof(par));
      j = 0;
      continue;
    }
    par[j] = AStr[i];
    j++;
    if ( i == dln - 1 )
      alt_num = atoi(par);
  }
  LoadTFE(tfe_num, alt_num);
}

void TDecisionScanner::Scan(char* AStr)
{
  char par[64];
  FreeList();
  int dln = strlen(AStr);
  memset(par, 0, sizeof(par));
  int j = 0;
  for(int i = 0; i <= dln - 1; i++)
  {
    if (AStr[i] == ';')
    {
      ScanTFE(par);
      memset(par, 0, sizeof(par));
      j = 0;
    }
    else
    {
      par[j] = AStr[i];
      j++;
    }
    if (i == dln - 1)
      ScanTFE(par);
  }
}

TDecisionScannerItemTFS* __fastcall TDecisionScanner::GetTFS(int AIndex)
{
  if (AIndex >= 0 && AIndex <= f_List->Count - 1)
    return static_cast<TDecisionScannerItemTFS*>(f_List->Items[AIndex]);
  else
    return NULL;
}

