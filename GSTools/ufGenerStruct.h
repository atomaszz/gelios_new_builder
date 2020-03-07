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

struct WorkAlternativ
{
	AnsiString  m_sName;
	double m_dB, m_dT, m_dV;
};

struct WorkOperation
{
	int m_nNumMasBefore;
	int m_nMasBefore [200];
	bool m_bControl;
	TList *m_ListWorkAlter;
};

struct CheckAlternativ
{
	AnsiString  m_sName;
	double m_dP00, m_dP11, m_dB;
};

struct CheckOperation
{
	int m_nNumMasCheck;
	int m_nMasCheck [200];
	TList *m_ListCheckAlter;
};

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
	TLabel *Label1;
	TLabel *Label2;
	TEdit *editNumAlter;
	TLabel *Label3;
	TEdit *editBeforeOperation;
	TPanel *Panel9;
	TPanel *Panel10;
	TButton *addControlBtn;
	TButton *delControlBtn;
	TButton *editControlBtn;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *editCheckOperation;
	TEdit *editNumCheckAlter;
	TLabel *Label6;
	TEdit *editFirstNameAlter;
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
	TEdit *editNameAlter;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *editB;
	TLabel *Label9;
	TEdit *editT;
	TLabel *Label10;
	TEdit *editV;
	TEdit *editFirstAlterName;
	TEdit *editP11;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *editNameCheckAlter;
	TEdit *editPDiagn;
	TLabel *Label13;
	TEdit *editP00;
	TLabel *Label14;
	TStringGrid *sgWorkAlterOperation;
	TStringGrid *sgControlAlterOperation;
	void __fastcall acptBtnClick(TObject *Sender);
	void __fastcall addWorkBtnClick(TObject *Sender);
	void __fastcall PageControl2Change(TObject *Sender);
	void __fastcall PageControl3Change(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall PageControl4Change(TObject *Sender);
	void __fastcall addControlBtnClick(TObject *Sender);
	void __fastcall sgWorkOperationSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall editWorkBtnClick(TObject *Sender);
	void __fastcall sgWorkAlterOperationSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall sgControlOperationSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall sgControlAlterOperationSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall editControlBtnClick(TObject *Sender);

private:	// User declarations
	void InitWorkTablesHeader();
	void InitWorkAlterTablesHeader();

	void InitCheckTablesHeader();
    void InitCheckAlterTablesHeader();
public:		// User declarations
	__fastcall TfmToolGenerStruct(TComponent* Owner);

	TList *m_ListWorkOper;
	WorkOperation* currWorkOper;
	void RefillWorkGrid();
	void InitFieldsWorkOper();
	void InitCurrWorkOper(int idx);

	WorkAlternativ* currWorkAlter;
	void RefillWorkAlterGrid();
	void InitFieldsWorkAlter();
	void InitCurrWorkAlter(int idx);

	void EnableWorkControls();


	TList *m_ListCheckOper;
	CheckOperation* currCheckOper;
	void RefillCheckGrid();
	void InitFieldsCheckOper();
	void InitCurrCheckOper(int idx);

	CheckAlternativ* currCheckAlter;
	void RefillCheckAlterGrid();
	void InitFieldsCheckAlter();
	void InitCurrCheckAlter(int idx);

	void EnableCheckControls();








	int TfmToolGenerStruct::exit_proverka_simb(TEdit *Edit);
	float TfmToolGenerStruct::exit_proverka_0_1(TEdit *Edit);

};

//---------------------------------------------------------------------------
extern PACKAGE TfmToolGenerStruct *fmToolGenerStruct;
//---------------------------------------------------------------------------

bool ShowToolGenerStruct(TfrmMain *frmMain);

//---------------------------------------------------------------------------

#endif
