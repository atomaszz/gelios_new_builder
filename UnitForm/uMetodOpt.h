//---------------------------------------------------------------------------

#ifndef uMetodOptH
#define uMetodOptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFmMetodOpt : public TForm
{
__published:	// IDE-managed Components
        TComboBox *cbxMetod;
        TRadioGroup *rgMetod;
        TLabel *Label1;
        TLabel *lblPribl;
        TEdit *edPercent;
        TButton *btCancel;
        TButton *btOk;
        void __fastcall cbxMetodClick(TObject *Sender);
        void __fastcall btOkClick(TObject *Sender);
        void __fastcall btCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFmMetodOpt(TComponent* Owner);
        int get_type_metod();
        void set_type_metod(int typ);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmMetodOpt *FmMetodOpt;
//---------------------------------------------------------------------------
bool ShowMetodOpt(int AType, double ARate, int &OutType, double &OutRate);
#endif
