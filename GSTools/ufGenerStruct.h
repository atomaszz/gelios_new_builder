//---------------------------------------------------------------------------

#ifndef ufGenerStructH
#define ufGenerStructH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uMainFrm.h"
#include "uMakerTFS.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

struct WorkAlternativ
{
	int m_nID;
	AnsiString  m_sName;
	double m_dB, m_dT, m_dV;
};

struct CheckAlternativ
{
	int m_nID;
	AnsiString  m_sName;
	double m_dK00, m_dK11, m_dTf, m_dVf;
};

class BasisOperation
{
public:
	TList *m_ListOperationBefore;
	BasisOperation(int nType)
	{
	  m_nType = nType;
    }
	int m_nType;
	virtual void PutOnWork(TMakerTFS* Maker) {};
	virtual void PutOnAlter(TMakerTFS* Maker, int nId) {};
};

class CheckOperation : public BasisOperation
{
public:
	CheckOperation() : BasisOperation(2) {}

	int m_nID;
	TList *m_ListCheckWork;
	TList *m_ListCheckAlter;
	
	void PutOnWork(TMakerTFS* Maker);
	void PutOnAlter(TMakerTFS* Maker, int nId);
};

class WorkOperation : public BasisOperation
{
public:
	WorkOperation() : BasisOperation(1) {}

	int m_nID;
	TList *m_ListWorkAlter;

	CheckOperation* m_pCheckAlone;
	CheckOperation* m_pGroupCheck;

	void PutOnWork(TMakerTFS* Maker);
	void PutOnAlter(TMakerTFS* Maker, int nId);
};

class ParallWorkOperation : public BasisOperation
{
public:
	BasisOperation *m_op1, *m_op2;
	bool m_bParal;
	ParallWorkOperation(BasisOperation *op1, BasisOperation *op2, bool bParal) : BasisOperation(3)
	{
	  m_op1 = op1;
	  m_op2 = op2;
	  m_bParal =  bParal;
      m_ListOperationBefore = new TList;

	  for (int i = 0; i < op1->m_ListOperationBefore->Count; i++) {
		m_ListOperationBefore->Add(op1->m_ListOperationBefore->Items[i]);		
	  }

	  for (int i = 0; i < op2->m_ListOperationBefore->Count; i++) {
		bool bAdd = true;
		for (int j = 0; j < m_ListOperationBefore->Count; j++) {
		 BasisOperation* BO = static_cast<BasisOperation*>(op2->m_ListOperationBefore->Items[i]);
		  if (static_cast<BasisOperation*>(m_ListOperationBefore->Items[j]) == static_cast<BasisOperation*>(op2->m_ListOperationBefore->Items[i])) {
			bAdd = false;
			break;
		  }	
		}
		if (bAdd) {
		   m_ListOperationBefore->Add(op2->m_ListOperationBefore->Items[i]);
		}
	  }
	  if (m_op1->m_nType ==1) {
		m_ListOperationBefore->Add(m_op1);
	  }
	  if (m_op2->m_nType ==1) {
		m_ListOperationBefore->Add(m_op2);
	  }

	}
	void PutOnWork(TMakerTFS* Maker);
	void PutOnAlter(TMakerTFS* Maker, int nId);

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
	TEdit *editK11;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *editNameCheckAlter;
	TEdit *editTf;
	TLabel *Label13;
	TEdit *editK00;
	TLabel *Label14;
	TStringGrid *sgWorkAlterOperation;
	TStringGrid *sgControlAlterOperation;
	TLabel *Label15;
	TEdit *editVf;
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
	void __fastcall delWorkBtnClick(TObject *Sender);
	void __fastcall delControlBtnClick(TObject *Sender);
	void __fastcall extBtnClick(TObject *Sender);

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

	TList* m_ListOut;

	bool SortOfGroup();
	bool SortOfAll();


	int TfmToolGenerStruct::exit_proverka_simb(TEdit *Edit);
	float TfmToolGenerStruct::exit_proverka_0_1(TEdit *Edit);

};

//---------------------------------------------------------------------------
extern PACKAGE TfmToolGenerStruct *fmToolGenerStruct;
//---------------------------------------------------------------------------

bool ShowToolGenerStruct(TfrmMain *frmMain);

//---------------------------------------------------------------------------

#endif
