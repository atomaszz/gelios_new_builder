//---------------------------------------------------------------------------

#ifndef ufToolMainH
#define ufToolMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "uToolScan.h"
#include "uCheckSuperPos.h"
//---------------------------------------------------------------------------
class TfmToolMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TPanel *Panel2;
        TPanel *Panel3;
        TMemo *mmSource;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TMemo *mmStep;
        TMemo *mmRo;
        TPanel *Panel8;
        TButton *Button2;
        TEdit *edTransit;
	TPanel *Panel9;
	TButton *Button3;
	TButton *Button4;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
  TFsTable *FTable;
  TCheckSuperPos *FChecker;
public:		// User declarations
		__fastcall TfmToolMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfmToolMain *fmToolMain;
//---------------------------------------------------------------------------

bool ShowToolTFS(String AText);

#endif
