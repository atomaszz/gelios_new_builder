//---------------------------------------------------------------------------

#ifndef uFmParamAlternativeH
#define uFmParamAlternativeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include "uBaseShape.h"
#include <Buttons.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TfmParamAlternative : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TStringGrid *sgParam;
        TPanel *Panel3;
        TLabel *Label1;
        TLabel *Label13;
        TPanel *Panel4;
        TActionList *ActionList1;
        TAction *acAdd;
        TAction *acDel;
        TAction *acForm;
        TImageList *ImageList1;
        TLabel *lbNum;
        TLabel *lbCount;
        TLabel *lbType;
        TLabel *lbTypeParam;
        TLabel *Label6;
        TLabel *Label7;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton4;
        TPaintBox *pbTfs;
        TShape *Shape4;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TAction *acExit;
        TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall acAddExecute(TObject *Sender);
        void __fastcall acDelExecute(TObject *Sender);
        void __fastcall acDelUpdate(TObject *Sender);
        void __fastcall sgParamDblClick(TObject *Sender);
        void __fastcall pbTfsPaint(TObject *Sender);
        void __fastcall acExitExecute(TObject *Sender);
        void __fastcall acFormExecute(TObject *Sender);
private:	// User declarations
  int f_Type_Char;
  int f_ParentShapeID;
  TBaseShape* f_TFE;
  Graphics::TBitmap* f_Glp;
  void StringInit();
  void RefreshData();
  void RefreshDataPROP();
  void RefreshDataFUZZY();
  void LocateRow(void *Bm);
  void DrawGlp();
  double GetMyRandom();
public:		// User declarations
  bool FReadOnly;
        __fastcall TfmParamAlternative(TComponent* Owner);
        __property int Type_Char = {read = f_Type_Char, write = f_Type_Char};
        __property int ParentShapeID = {read = f_ParentShapeID, write =  f_ParentShapeID};
        __property TBaseShape* TFE = {read = f_TFE, write = f_TFE};
        __property Graphics::TBitmap* Glp = {read = f_Glp, write = f_Glp};
};
void ShowParamAlternative(TBaseShape* ATFE, int AParentID, int AType_Char, Graphics::TBitmap* AGlp, bool AReadOnly);
//---------------------------------------------------------------------------
extern PACKAGE TfmParamAlternative *fmParamAlternative;
//---------------------------------------------------------------------------
#endif
