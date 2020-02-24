//---------------------------------------------------------------------------

#ifndef ufmOzenkViewH
#define ufmOzenkViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfmOzenkView : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TEdit *edPower;
        TEdit *edWork;
        TButton *Button1;
private:	// User declarations
public:		// User declarations
        __fastcall TfmOzenkView(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfmOzenkView *fmOzenkView;
//---------------------------------------------------------------------------
void ShowOzenk(AnsiString APower, AnsiString AWork);
#endif
