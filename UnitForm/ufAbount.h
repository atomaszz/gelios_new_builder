//---------------------------------------------------------------------------

#ifndef ufAbountH
#define ufAbountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
const int AB_MAJOR_VERSION  = 0;
const int AB_MINOR_VERSION  = 1;
const int AB_RELEASE        = 2;
const int AB_BUILD          = 3;

class TVersion
{
  private:
    void *FData;
    bool FValid;
  public:
    TVersion();
    ~TVersion();
    int GetVersion(int AType);
};

class TfAbount : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TLabel *Label1;
        TLabel *lblVersion2;
        TLabel *lblBuild2;
        TBevel *Bevel1;
        TLabel *lblVersion;
        TActionList *ActionList1;
        TAction *acOk;
        TLabel *lblBuild;
        TLabel *Label2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
private:	// User declarations
  TVersion *Vers;
public:		// User declarations
        __fastcall TfAbount(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfAbount *fAbount;
//---------------------------------------------------------------------------
void ShowAbout();

#endif
