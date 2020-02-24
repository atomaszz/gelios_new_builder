//---------------------------------------------------------------------------

#ifndef ufrmPredicateViewH
#define ufrmPredicateViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ToolWin.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfrmPredicateView : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TSaveDialog *SDG;
        TToolBar *ToolBar1;
        TActionList *ActionList1;
        TAction *acSave;
        TAction *acExit;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TPageControl *PC;
        TTabSheet *tsStruct;
        TTabSheet *tsRab;
        TRichEdit *REStruct;
        TRichEdit *RERab;
        TTabSheet *tsControlRab;
        TTabSheet *tsControlFunc;
        TTabSheet *tsCheckCondition;
        TTabSheet *tsDopPrav;
        TRichEdit *REControlRab;
        TRichEdit *REControlFunc;
        TRichEdit *RECheckCondition;
        TRichEdit *REDopPrav;
        TAction *acLoadDopPrav;
        TToolButton *ToolButton3;
        TOpenDialog *OD;
        TAction *acAll;
        TToolButton *ToolButton4;
        TTabSheet *tsOptZadacha;
        TRichEdit *REOptZadacha;
        void __fastcall acSaveExecute(TObject *Sender);
        void __fastcall acExitExecute(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall acLoadDopPravUpdate(TObject *Sender);
        void __fastcall acLoadDopPravExecute(TObject *Sender);
        void __fastcall acAllExecute(TObject *Sender);
private:	// User declarations
        bool f_Close;
public:		// User declarations
        __fastcall TfrmPredicateView(TComponent* Owner);
        AnsiString FullModel();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPredicateView *frmPredicateView;
//---------------------------------------------------------------------------

AnsiString FullPredicateModel(AnsiString AStruct, AnsiString ARab,
  AnsiString AControlRab, AnsiString AControlFunc, AnsiString ACheckCondition,
  AnsiString AOptZadacha, AnsiString ADopPrav );
#endif
