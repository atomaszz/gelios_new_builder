//---------------------------------------------------------------------------

#ifndef ufmPredicateFullH
#define ufmPredicateFullH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmPredicateFull : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TActionList *ActionList1;
        TAction *acRun;
        TLabel *Label1;
        TEdit *edZel;
        TRichEdit *REModel;
        TEdit *STResult;
        TButton *Button1;
        TAction *acExit;
        TButton *Button2;
        void __fastcall acRunExecute(TObject *Sender);
        void __fastcall acRunUpdate(TObject *Sender);
        void __fastcall acExitExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfmPredicateFull(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmPredicateFull *fmPredicateFull;
//---------------------------------------------------------------------------
#endif
