#include <registry.hpp>
//---------------------------------------------------------------------------
#ifndef uGlsRegistryH
#define uGlsRegistryH
//---------------------------------------------------------------------------

class TGlsRegistry
{
  private:
    AnsiString f_RegistryPath;
    AnsiString f_LocalPath;
    TRegistry* f_Registry;
    AnsiString GetPath(AnsiString  Name);
  public:
    TGlsRegistry(HKEY AKey = HKEY_CURRENT_USER);
    ~TGlsRegistry();
    void SaveString(AnsiString Name, AnsiString Value);
    AnsiString GetString(AnsiString Name);
    void SaveInteger(AnsiString Name, int Value);
    int GetInteger(AnsiString Name, int DefValue);
    void SaveBool(AnsiString Name, bool Value);
    int GetBool(AnsiString Name, bool DefValue);
    __property AnsiString Path = {read = f_RegistryPath, write = f_RegistryPath};
    __property AnsiString LocalPath = {read = f_LocalPath, write = f_LocalPath};

};

#endif
