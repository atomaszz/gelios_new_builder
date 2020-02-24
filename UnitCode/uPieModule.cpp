//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPieModule.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TPieModule *gPieModule;

TPieModule::TPieModule()
{
  f_Run1 = 0;
  f_Hinstan = LoadLibrary(_T("pie.dll"));
  if(f_Hinstan > 0)
  {
     FARPROC Fpointer=GetProcAddress(f_Hinstan,"run1");
     if(Fpointer!=NULL)
       f_Run1 = Trun1(Fpointer);
  }
}

TPieModule::~TPieModule()
{
  if(f_Hinstan > 0)
    FreeLibrary(f_Hinstan);
}

bool TPieModule::CheckModule()
{
   return (f_Hinstan && f_Run1 );
}

int TPieModule::Run1(AnsiString ARunStr)
{
   int res = -1;
   if (CheckModule())
      f_Run1(ARunStr.c_str(), &res);
   return res;   
}

void TPieModule::RefreshModule()
{
  if(f_Hinstan > 0)
  {
    FreeLibrary(f_Hinstan);
    f_Run1 = 0;
    f_Hinstan = LoadLibrary(_T("pie.dll"));
    if(f_Hinstan > 0)
    {
       FARPROC Fpointer=GetProcAddress(f_Hinstan,"run1");
       if(Fpointer!=NULL)
         f_Run1 = Trun1(Fpointer);
    }
  }  
}


