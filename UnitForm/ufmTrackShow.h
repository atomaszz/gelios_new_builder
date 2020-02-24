//---------------------------------------------------------------------------

#ifndef ufmTrackShowH
#define ufmTrackShowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "uZadacha.h"
#include <Grids.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmTrackShow : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TStatusBar *StatusBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TPageControl *PageControl;
        TTabSheet *tsTable;
        TTabSheet *tsPredicate;
        TRichEdit *REPredicate;
        TStringGrid *sgModel;
        TActionList *ActionList1;
        TAction *acTrackAccept;
        TAction *acTrackCheck;
        TAction *acCancel;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TPopupMenu *pmCreateTrack;
        TAction *acCreateManual;
        TAction *acCreateAuto;
        TMenuItem *N1;
        TMenuItem *N2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall sgModelDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall acTrackAcceptExecute(TObject *Sender);
        void __fastcall acTrackCheckExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall acCreateManualExecute(TObject *Sender);
        void __fastcall PageControlChange(TObject *Sender);
        void __fastcall acCreateAutoExecute(TObject *Sender);
private:	// User declarations
        void StringInit();
		void FillStringGrid();
        void DoInsertToGrid(String ATFSName, int AID1, int AID2, int AID3 );
		void InsertKnotToGrid(TPredicateScannerItemKnot* AKnot);
public:		// User declarations
        TZadacha* Zadacha;
        __fastcall TfmTrackShow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmTrackShow *fmTrackShow;
//---------------------------------------------------------------------------
void CreateTrackShow(TZadacha* AZadacha, AnsiString AText);

#endif
