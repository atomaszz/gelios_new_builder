//---------------------------------------------------------------------------

#ifndef ufmParamAlternativeLoaderH
#define ufmParamAlternativeLoaderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmParamAlternativeLoader : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnlCnt;
        TLabel *Label1;
        TGroupBox *gbControlRab;
        TLabel *Label2;
        TLabel *Label3;
        TGroupBox *gbControlFunc;
        TLabel *Label4;
        TLabel *Label5;
        TGroupBox *gbRab;
        TLabel *Label6;
        TPanel *pnlAvg;
        TEdit *edP11_0;
        TImage *Image2;
        TEdit *edP00_0;
        TImage *Image3;
        TEdit *edP11_1;
        TImage *Image4;
        TEdit *edP00_1;
        TImage *Image5;
        TEdit *edK11_0;
        TImage *Image6;
        TEdit *edK11_1;
        TImage *Image7;
        TEdit *edK00_0;
        TEdit *edK00_1;
        TImage *Image8;
        TImage *Image9;
        TEdit *edB_0;
        TImage *Image10;
        TEdit *edB_1;
        TLabel *Label9;
        TImage *Image11;
        TEdit *edT_0;
        TImage *Image12;
        TEdit *edT_1;
        TLabel *Label10;
        TImage *Image13;
        TEdit *edV_0;
        TImage *Image14;
        TEdit *edV_1;
        TImage *Image1;
        TEdit *edCount;
        TPanel *pnlBottom;
        TButton *Button1;
        TButton *Button2;
        TActionList *ActionList1;
        TAction *acOk;
        TAction *acCancel;
        void __fastcall edCountExit(TObject *Sender);
        void __fastcall edK00_0Exit(TObject *Sender);
        void __fastcall edB_0Exit(TObject *Sender);
        void __fastcall edB_1Exit(TObject *Sender);
        void __fastcall edK00_1Exit(TObject *Sender);
        void __fastcall edK11_0Exit(TObject *Sender);
        void __fastcall edK11_1Exit(TObject *Sender);
        void __fastcall edP00_0Exit(TObject *Sender);
        void __fastcall edP00_1Exit(TObject *Sender);
        void __fastcall edP11_0Exit(TObject *Sender);
        void __fastcall edP11_1Exit(TObject *Sender);
        void __fastcall edT_0Exit(TObject *Sender);
        void __fastcall edT_1Exit(TObject *Sender);
        void __fastcall edV_0Exit(TObject *Sender);
        void __fastcall edV_1Exit(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
private:	// User declarations
  int exit_proverka_simb(TEdit *Edit);
  int exit_proverka_0_1(TEdit *Edit);
public:		// User declarations
  void SetType(int AType);
        __fastcall TfmParamAlternativeLoader(TComponent* Owner);
};

int ShowParamAlternativeLoader(int AType, double &AT_0, double &AT_1, double &AV_0, double &AV_1,
  double &AX00_0, double &AX00_1, double &AZ00_0, double &AZ00_1);
//---------------------------------------------------------------------------
//extern PACKAGE TfmParamAlternativeLoader *fmParamAlternativeLoader;
//---------------------------------------------------------------------------
#endif
