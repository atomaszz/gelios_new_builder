//---------------------------------------------------------------------------

#ifndef ufmPredicatePathConstructorH
#define ufmPredicatePathConstructorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "uPredicatePath.h"
#include <ActnList.hpp>
#include <Grids.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
struct TPredicatePathConstructorStruct
{
  double oz0;
  double oz1;
};

class TfmPredicatePathConstructor : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TButton *Button3;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TTabControl *TabControl;
        TActionList *ActionList1;
        TAction *acRun;
        TButton *Button4;
        TAction *acShowPredicate;
        TAction *acOk;
        TAction *acCancel;
        TPanel *pnlOzenk;
        TLabel *Label1;
        TEdit *edPower;
        TLabel *Label2;
        TEdit *edWork;
        TPageControl *PageControl2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TRichEdit *REText;
        TStringGrid *sgTable;
        TStringGrid *sgTableItems;
        TSplitter *Splitter1;
        void __fastcall TabControlChange(TObject *Sender);
        void __fastcall acRunExecute(TObject *Sender);
        void __fastcall acShowPredicateUpdate(TObject *Sender);
        void __fastcall acShowPredicateExecute(TObject *Sender);
        void __fastcall acOkUpdate(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall sgTableSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
private:	// User declarations
  int f_Percent;
  int f_Count;
  int f_MaxOptCnt;
  bool f_Ozenk;
  bool f_Exclude;
  TList* f_Items;
  TPredicatePathItem* FPredicatePathItem;
  void FreeItems();
  void OzenkPathItem(TPredicatePathItem* AItem, double &AOz0, double &AOz1);
  void MakeTabControl();
  void SortItems();
  void ExcludeItems();
  void DelItems();
  void ShowValueOzenk();
  void RefreshDataToGrid(TStringGrid *AGrid,
    TPredicatePathItem* APath);
  AnsiString GetTfsList(AnsiString AStringPathNode);
  void RefreshDataItemsToGrid(TStringGrid *AGrid,
    TPredicatePathNode* ANode);
  AnsiString GetTfsDesc(TPredicatePathNodeItem *AItem,
    int &AID1, int &AID2, int &AID3);
//  void CheckInput();
public:		// User declarations
  TPredicatePath* PPath;
        __fastcall TfmPredicatePathConstructor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmPredicatePathConstructor *fmPredicatePathConstructor;
//---------------------------------------------------------------------------
AnsiString  ShowPredicatePathConstructor(TPredicatePath* APath);
#endif
