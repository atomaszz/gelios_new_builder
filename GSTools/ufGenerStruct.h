//---------------------------------------------------------------------------

#ifndef ufGenerStructH
#define ufGenerStructH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uMainFrm.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfmToolGenerStruct : public TForm
{
__published:	// IDE-managed Components
	TButton *Button3;
	TButton *Button4;
	TPanel *Panel1;
	TPanel *Panel3;
	TPanel *Panel4;
	TStringGrid *sgWorkOperation;
	TPanel *Panel2;
	TPanel *Panel5;
	TPanel *Panel6;
	TStringGrid *sgControlOperation;
	TPanel *Panel7;
	TButton *addBtn;
	TButton *editBtn;
	TButton *delBtn;
	TPanel *Panel8;
	TCheckBox *CheckBox1;
	TLabel *Label1;
	TEdit *edPercent;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	TEdit *Edit2;
	TButton *Button1;
	TPanel *Panel9;
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
