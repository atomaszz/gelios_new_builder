//---------------------------------------------------------------------------

#ifndef ufmViewPredicateTrackConstructorAutoH
#define ufmViewPredicateTrackConstructorAutoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include "uZadacha.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmViewPredicateTrackConstructorAuto : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TActionList *ActionList1;
        TAction *acRun;
        TAction *acOk;
        TPanel *Panel2;
        TLabel *Label1;
        TEdit *edPercent;
        TAction *acCancel;
        TButton *Button3;
        TTabControl *TabControl;
        TRichEdit *REPredicate;
        TLabel *Label2;
        TEdit *edCount;
        void __fastcall acRunExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall TabControlChange(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall acOkUpdate(TObject *Sender);
private:	// User declarations
  int f_Percent;
  int f_Count;
  TDynamicArray *f_Arr;
  bool CheckRnd();
  void CheckPercent();
  void CheckCount();
  void DoMakeTrack(TPredicateTrackCreatorItem* AItem, TDynamicArray *AStack);
  void MakeTrack();
  void ShowTracks();
  bool DebugCheck();
public:		// User declarations
  TZadacha *Zadacha;
        __fastcall TfmViewPredicateTrackConstructorAuto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmViewPredicateTrackConstructorAuto *fmViewPredicateTrackConstructorAuto;
//---------------------------------------------------------------------------
#endif
