//---------------------------------------------------------------------------

#ifndef uPieModuleH
#define uPieModuleH
//---------------------------------------------------------------------------
typedef void  (__stdcall *Trun1)(char*, int*);

class TPieModule
{
  private:
    HINSTANCE f_Hinstan;
    Trun1 f_Run1;
  public:
    TPieModule();
    ~TPieModule();
    bool CheckModule();
    void RefreshModule();
    int Run1(AnsiString ARunStr);
};
extern TPieModule *gPieModule;

#endif

