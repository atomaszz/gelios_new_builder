//---------------------------------------------------------------------------

#ifndef ufmViewDecisionH
#define ufmViewDecisionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "uParamAlternative.h"
#include "uPredicatePath.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmViewDecision : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TActionList *ActionList1;
        TAction *acClose;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TStringGrid *sgAlternative;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TLabel *Label1;
        TBevel *bvVert;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *edVid1;
        TEdit *edVid2;
        TEdit *edOgr1;
        TEdit *edOgr2;
        TEdit *edKoef;
        TBevel *Bevel2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TBevel *Bevel1;
        TPanel *Panel8;
        TPanel *Panel9;
        TLabel *Label4;
        TEdit *edT;
        TLabel *Label5;
        TEdit *edB;
        TLabel *Label6;
        TEdit *edV;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label9;
        TLabel *Label10;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TEdit *edOptSostav;
        TLabel *Label11;
        TEdit *edTime;
        TBevel *Bevel6;
        TButton *Button2;
        TAction *acShowResult;
        void __fastcall acCloseExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall sgAlternativeDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall acShowResultExecute(TObject *Sender);
private:	// User declarations
//        TDecisionScanner *DecScaner;
        void DrawBevel();
        void StringInit();
        void RefreshDataPROP();
        void RefreshDataFUZZY();
        void RefreshData();
public:		// User declarations
        int Type_Char;
        TParamAlternative* ParamAlt;
        TPredicatePathItem* FPredicatePathItem;
        TColor VwColorAlt;
        TColor VwColorBadAlt;
        __fastcall TfmViewDecision(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmViewDecision *fmViewDecision;
//---------------------------------------------------------------------------
#endif
