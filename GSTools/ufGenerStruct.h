//---------------------------------------------------------------------------

#ifndef ufGenerStructH
#define ufGenerStructH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uMainFrm.h"
//---------------------------------------------------------------------------
class TfmToolGenerStruct : public TForm
{
__published:	// IDE-managed Components
	TButton *Button3;
	TButton *Button4;
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmToolGenerStruct(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmToolGenerStruct *fmToolGenerStruct;
//---------------------------------------------------------------------------

bool ShowToolGenerStruct(TfrmMain *frmMain);
#endif
