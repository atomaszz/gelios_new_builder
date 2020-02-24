//---------------------------------------------------------------------------

#ifndef ufmPredicatePathConstructorOgrH
#define ufmPredicatePathConstructorOgrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmPredicatePathConstructorOgr : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TLabel *Label1;
        TEdit *edPercent;
        TLabel *Label3;
        TLabel *Label2;
        TEdit *edCount;
        TActionList *ActionList1;
        TAction *acCancel;
        TAction *acOk;
        TGroupBox *gbOzenk;
        TCheckBox *cbOzenk;
        TLabel *lblMaxOpt;
        TEdit *edMaxOpt;
        TCheckBox *cbExclude;
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall cbOzenkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfmPredicatePathConstructorOgr(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfmPredicatePathConstructorOgr *fmPredicatePathConstructorOgr;
//---------------------------------------------------------------------------
bool PredicatePathConstructorOgrShow(int &APercent, int &ACount, bool &AOzenk, bool &AExclude, int &AMaxOptCnt);
#endif
