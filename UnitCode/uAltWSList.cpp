//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAltWSList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TAltWSList::TAltWSList()
{
   f_List = new TList;
}

TAltWSList::~TAltWSList()
{
   delete f_List;
}

void TAltWSList::Add(TBaseWorkShape* AWs)
{
   f_List->Add(AWs);
}

void TAltWSList::Clear()
{
   f_List->Clear();
}

bool TAltWSList::Find(TBaseWorkShape* AWs)
{
   return (f_List->IndexOf(AWs) > -1);
}


TBaseWorkShape* __fastcall TAltWSList::GetItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TBaseWorkShape*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TAltWSList::GetCount()
{
   return  f_List->Count;
}


