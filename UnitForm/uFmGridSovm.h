//---------------------------------------------------------------------------

#ifndef uFmGridSovmH
#define uFmGridSovmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TFmGridSovm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TStringGrid *sgSovm;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TImageList *ImageList1;
        TActionList *ActionList1;
        TAction *acGridSovmAdd;
        TAction *acGridSovmDel;
        TAction *acSaveSovm;
        TAction *acCancel;
        TButton *Button1;
        TButton *Button2;
        void __fastcall acGridSovmAddExecute(TObject *Sender);
        void __fastcall acGridSovmDelExecute(TObject *Sender);
        void __fastcall acSaveSovmExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFmGridSovm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmGridSovm *FmGridSovm;
//---------------------------------------------------------------------------
#endif
