//---------------------------------------------------------------------------

#ifndef ufmPredicatePathViewH
#define ufmPredicatePathViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uPredicatePath.h"
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Grids.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmPredicatePathView : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TActionList *ActionList1;
        TAction *acOk;
        TAction *acCancel;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TAction *acCreate;
        TAction *acShowPredicate;
        TToolButton *ToolButton2;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TPageControl *PageControl2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TRichEdit *REBase;
        TPageControl *PageControl3;
        TTabSheet *tsUsedGrid;
        TTabSheet *tsUsedEdit;
        TRichEdit *REUsed;
        TStringGrid *sgBase;
        TStringGrid *sgUsed;
        TStringGrid *sgBaseItems;
        TStringGrid *sgUsedItems;
        TSplitter *Splitter2;
        TSplitter *Splitter1;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TAction *acUp;
        TAction *acDown;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall acShowPredicateExecute(TObject *Sender);
        void __fastcall acCreateExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall sgBaseSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall sgUsedSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall acUpExecute(TObject *Sender);
        void __fastcall acDownExecute(TObject *Sender);
        void __fastcall PageControl3Change(TObject *Sender);
        void __fastcall PageControl3Changing(TObject *Sender,
          bool &AllowChange);
	void __fastcall acCreateUpdate(TObject *Sender);
private:	// User declarations
  TPredicatePathItem* FUsedPathToGrid;
  TPredicatePathItem* FBasePathToGrid;
  void RefreshDataToGrid(TStringGrid *AGrid, TPredicatePathItem* APath);
  void RefreshDataItemsToGrid(TStringGrid *AGrid, TPredicatePathNode* ANode);
  AnsiString GetTfsList(AnsiString AStringPathNode);
  AnsiString GetTfsDesc(TPredicatePathNodeItem *AItem,
   int &AID1, int &AID2, int &AID3);
  void UpStringGrid(TStringGrid *AGrid);
  void RefreshStringGridItems(TStringGrid *AGrid, int ARow);
  void RefreshStringGrid(TStringGrid *AGrid, TPredicatePathNode* ANode);
  void DownStringGrid(TStringGrid *AGrid);
public:		// User declarations

  TPredicatePath* PPath;
		__fastcall TfmPredicatePathView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmPredicatePathView *fmPredicatePathView;
//---------------------------------------------------------------------------

bool ShowPredicatePathView(TPredicatePath* APath);
#endif
