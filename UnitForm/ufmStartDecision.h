//---------------------------------------------------------------------------

#ifndef ufmStartDecisionH
#define ufmStartDecisionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include "uZadacha.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmStartDecision : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label3;
        TEdit *Edit1;
        TEdit *Edit5;
        TPanel *Panel2;
        TEdit *Edit3;
        TLabel *Label4;
        TEdit *Edit2;
        TEdit *Edit7;
        TLabel *Label5;
        TEdit *Edit4;
        TEdit *Edit6;
        TLabel *Label6;
        TPanel *pnPribl;
        TLabel *Label7;
        TEdit *edPercent;
        TPanel *Panel3;
        TButton *Button1;
        TButton *Button3;
        TActionList *ActionList1;
        TAction *acStart;
        TAction *acCancel;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TButton *Button2;
        TAction *acTrack;
        TButton *Button4;
        TAction *acOzenka;
        void __fastcall acStartExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall edPercentExit(TObject *Sender);
        void __fastcall acTrackExecute(TObject *Sender);
        void __fastcall acOzenkaExecute(TObject *Sender);
        void __fastcall acOzenkaUpdate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    TZadacha *Zadacha;
    int type_char;
    int type_metod;
    void set_sadacha_edit();
        __fastcall TfmStartDecision(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmStartDecision *fmStartDecision;
//---------------------------------------------------------------------------

bool CreateStartDecision(TZadacha *AZadacha, int AType_char, int AType_metod);
void FreeStartDecision();
#endif
