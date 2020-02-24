//---------------------------------------------------------------------------

#ifndef ufmViewPredicateTrackConstructorH
#define ufmViewPredicateTrackConstructorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <Grids.hpp>
#include "uZadacha.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmViewPredicateTrackConstructor : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel5;
        TSplitter *Splitter1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TActionList *ActionList1;
        TAction *acUp;
        TAction *acDown;
        TAction *acOk;
        TAction *acCancel;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TStringGrid *sgBase;
        TStringGrid *sgResult;
        TButton *Button1;
        TButton *Button2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall sgBaseDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall acDownUpdate(TObject *Sender);
        void __fastcall acDownExecute(TObject *Sender);
        void __fastcall acUpUpdate(TObject *Sender);
        void __fastcall acUpExecute(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall acOkUpdate(TObject *Sender);
        void __fastcall sgBaseDblClick(TObject *Sender);
        void __fastcall sgResultDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
private:	// User declarations
  TDynamicArray *f_Arr, *f_Stack;
  void StringInit(TStringGrid *Grid);
  void InsertKnotToGrid(TStringGrid *Grid, TPredicateScannerItemKnot* AKnot);
  void DoInsertToGrid(TStringGrid *Grid, TPredicateScannerItemKnot* AKnot,
    AnsiString ATFSName, int AID1, int AID2, int AID3 );
  void RefreshGrids();
  void RefreshStringGridBase();
  void RefreshStringGridResult();
  void RefreshList();
  bool CanSelect(TPredicateScannerItemKnot* AKnot);
  void FillNegativeDecidedKnot();
  void DeleteBadKnot();
public:		// User declarations
  TPredicateTrackCreatorItem* ResultTrack;
  TZadacha *Zadacha;
        __fastcall TfmViewPredicateTrackConstructor(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfmViewPredicateTrackConstructor *fmViewPredicateTrackConstructor;
//---------------------------------------------------------------------------
#endif
