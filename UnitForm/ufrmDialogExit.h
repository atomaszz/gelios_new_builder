//---------------------------------------------------------------------------

#ifndef ufrmDialogExitH
#define ufrmDialogExitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmDialogExit : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TButton *BtExit;
        TButton *BtContinue;
        TButton *BtSave;
        TLabel *Label2;
        void __fastcall BtSaveClick(TObject *Sender);
        void __fastcall BtContinueClick(TObject *Sender);
        void __fastcall BtExitClick(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        int MResult;
        __fastcall TfrmDialogExit(TComponent* Owner);
};
int DialogExitExecute();
//---------------------------------------------------------------------------
extern PACKAGE TfrmDialogExit *frmDialogExit;
//---------------------------------------------------------------------------
#endif
