//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsRegistry.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TGlsRegistry::TGlsRegistry(HKEY AKey)
{
   f_Registry = new TRegistry;
   f_Registry->RootKey = AKey;
   f_RegistryPath = "";
   f_LocalPath = "";

}

TGlsRegistry::~TGlsRegistry()
{
   delete f_Registry;
}


AnsiString TGlsRegistry::GetPath(AnsiString  Name)
{
   AnsiString  Res;
   if ( f_LocalPath.Length() > 0 )
     Res = f_RegistryPath + "\\" + f_LocalPath;
   else
     Res = f_RegistryPath + "\\" + Name;
   return Res;
}


void TGlsRegistry::SaveString(AnsiString Name, AnsiString Value)
{
   if (f_RegistryPath.Length() == 0 ) return;
   AnsiString  S = GetPath(Name);
   try
   {
      f_Registry->OpenKey( S, true );
      f_Registry->WriteString( Name, Value );
   }
   catch(...){}
}

AnsiString TGlsRegistry::GetString(AnsiString Name)
{
   if (f_RegistryPath.Length() == 0 ) return "";
   AnsiString  S = GetPath(Name);
   AnsiString  Res = "";
   try
   {
      if  (f_Registry->OpenKey( S, false ) )
        Res = f_Registry->ReadString(Name);
   }
   catch(...)
   {
   }
   return Res;
}


void TGlsRegistry::SaveInteger(AnsiString Name, int Value)
{
   if (f_RegistryPath.Length() == 0 ) return;
   AnsiString  S = GetPath(Name);
   try
   {
      f_Registry->OpenKey( S, true );
      f_Registry->WriteInteger(Name, Value);
   }
   catch(...){}
}

int TGlsRegistry::GetInteger(AnsiString Name, int DefValue)
{
   if (f_RegistryPath.Length() == 0 ) return DefValue;
   AnsiString  S = GetPath(Name);
   int  Res = DefValue;
   try
   {
      if ( f_Registry->OpenKey( S, false ) )
        Res = f_Registry->ReadInteger(Name);
   }
   catch(...)
   {
   }
   return Res;
}

void TGlsRegistry::SaveBool(AnsiString Name, bool Value)
{
   if (f_RegistryPath.Length() == 0 ) return;
   AnsiString  S = GetPath(Name);
   try
   {
      f_Registry->OpenKey( S, true );
      f_Registry->WriteBool(Name, Value);
   }
   catch(...){}
}

int TGlsRegistry::GetBool(AnsiString Name, bool DefValue)
{
   if (f_RegistryPath.Length() == 0 ) return DefValue;
   AnsiString  S = GetPath(Name);
   bool  Res = DefValue;
   try
   {
      if ( f_Registry->OpenKey( S, false ) )
        Res = f_Registry->ReadBool(Name);
   }
   catch(...)
   {
   }
   return Res;
}

