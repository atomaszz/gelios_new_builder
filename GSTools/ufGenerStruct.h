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
	TButton *acptBtn;
	TButton *extBtn;
	TPanel *Panel1;
	TPanel *Panel3;
	TPanel *Panel4;
	TStringGrid *sgWorkOperation;
	TPanel *Panel2;
	TPanel *Panel5;
	TPanel *Panel6;
	TStringGrid *sgControlOperation;
	TPanel *Panel7;
	TButton *addWorkBtn;
	TButton *editWorkBtn;
	TButton *delWorkBtn;
	TPanel *Panel8;
	TCheckBox *CheckBox1;
	TLabel *Label1;
	TEdit *edPercent;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	TEdit *Edit2;
	TPanel *Panel9;
	TPanel *Panel10;
	TButton *addControlBtn;
	TButton *delControlBtn;
	TButton *editControlBtn;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit3;
	TEdit *Edit4;
	TLabel *Label6;
	TEdit *Edit5;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPageControl *PageControl3;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TPageControl *PageControl4;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	void __fastcall acptBtnClick(TObject *Sender);
	void __fastcall addWorkBtnClick(TObject *Sender);
private:	// User declarations
	void InitTablesHeader();
public:		// User declarations
	__fastcall TfmToolGenerStruct(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmToolGenerStruct *fmToolGenerStruct;
//---------------------------------------------------------------------------

bool ShowToolGenerStruct(TfrmMain *frmMain);

//---------------------------------------------------------------------------

struct paramAlternativ
{
	int m_nWorkID, m_nID;
	AnsiString  m_sName;
	double m_dB, m_dT, m_dV;
};

struct workOperation
{
	int m_nID, m_nNumAlt;
	AnsiString  m_sNameFirstAlt;
    int m_nNumMasBefore;
	int m_nMasBefore [200];
	bool m_bAloneControl;
};

struct controlOperation
{
	int m_nID, m_nNumAlt;
	AnsiString  m_sNameFirstAlt;
	int m_nNumMasControl;
	int m_nMasControl [200];
};
#endif
