//---------------------------------------------------------------------------

#ifndef ufmViewResultH
#define ufmViewResultH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include "uPaintgrids.h"
#include "uDecisionScanner.h"
#include <Dialogs.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include "uPredicatePath.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class TfmViewResult : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TToolBar *ToolBar1;
        TPanel *pnlView;
        TPaintBox *pbView;
        TSaveDialog *SaveDLG;
        TActionList *ActionList1;
        TAction *acSaveResult;
        TAction *acClose;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TAction *acShowParam;
        TPopupMenu *pmMenu;
        TMenuItem *N1;
        TScrollBar *sbX;
        TScrollBar *sbY;
        void __fastcall pbViewPaint(TObject *Sender);
        void __fastcall pnlViewResize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall acCloseExecute(TObject *Sender);
        void __fastcall acSaveResultExecute(TObject *Sender);
        void __fastcall pbViewMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall pbViewMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall acShowParamUpdate(TObject *Sender);
        void __fastcall acShowParamExecute(TObject *Sender);
        void __fastcall sbXChange(TObject *Sender);
        void __fastcall sbYChange(TObject *Sender);
private:	// User declarations
        int Type_Char;
        int X_Base, Y_Base;
        int X_Ofs, Y_Ofs;
        
        TListNode* LN;
        TDecisionScanner *DecScaner;
        TDynamicArray *FSortPath;
        void SortPath();
        void DoSortPathItem(TPredicatePathNodeItem* AItem);
        void BuildGlp(TBaseWorkShape* AWN, Graphics::TBitmap* Glp, TBaseShape *ASel);
        void SetNewPolygon();
        MESSAGE void __fastcall M_gd_paint(TMessage& Msg);
public:		// User declarations
        TPaintGrid* Grid;
        char *FStr;
        TPredicatePathItem* FPredicatePathItem;
        void Init(int AType_Char);
        __fastcall TfmViewResult(TComponent* Owner);
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(WM_GD_PAINT, TMessage, M_gd_paint)
        END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmViewResult *fmViewResult;
//---------------------------------------------------------------------------
#endif
