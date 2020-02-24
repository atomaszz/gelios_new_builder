//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uOgrSovmArray.h"
#include "opim_f.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TOgrSovmArray::TOgrSovmArray()
{
  FCheck = false;
  FCheckObj = NULL;
  f_Array = new TDynamicArray;
}

TOgrSovmArray::~TOgrSovmArray()
{
  delete f_Array;
}

bool TOgrSovmArray::AddOgrSovm(TBaseWorkShape* ATFS)
{
  bool add = false;
  if (ATFS)
  {
	for (int i = 0; (!add && (i <= ATFS->WorkShapesCount - 1)); i++)
	  add = opt_sadacha->InOgrSovm(ATFS->GetWorkShape(i)->ID);
	if (add && !f_Array->Find(ATFS))
	  f_Array->Append(ATFS);
  }
  return add;
}

bool TOgrSovmArray::IsContainsKnot(int ATFE1, int ATFE2, int ATFE3)
{
  TBaseShape* B;
  TBaseWorkShape* mTFS;
  int cnt = f_Array->Count;
  for(int i = 0; i <= cnt - 1; i++)
  {
    mTFS = static_cast<TBaseWorkShape*>(f_Array->Items[i]);
    B = mTFS->ShapeSupportID(ATFE1);
    if (B)
      return true;
    B = mTFS->ShapeSupportID(ATFE2);
    if (B)
      return true;
    B = mTFS->ShapeSupportID(ATFE3);
    if (B)
      return true;
  }
  return false;
}

bool TOgrSovmArray::IsContainsTFS(TBaseWorkShape* ATFS)
{
  return f_Array->Find(ATFS);
}

void TOgrSovmArray::SetCheckObj(void *P)
{
  FCheckObj = P;
  FCheck = !FCheckObj;
}









