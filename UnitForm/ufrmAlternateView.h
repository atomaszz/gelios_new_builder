//---------------------------------------------------------------------------

#ifndef ufrmAlternateViewH
#define ufrmAlternateViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "uTreeList.h"
#include "uAlternateView.h"
#include "uAlternateViewPainterList.h"
#include <ComCtrls.hpp>
#include "uClipPath.h"
#include <ActnList.hpp>
#include "uCompositeStack.h"
#include "uCommonGraph.h"
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
const WM_G_CLOSE = WM_USER + 1;

//---------------------------------------------------------------------------
class TfrmAlternateView : public TForm
{
__published:	// IDE-managed Components
        TScrollBar *sbX;
        TScrollBar *sbY;
        TPanel *pnlShow;
        TPaintBox *pbShow;
        TStatusBar *SBar;
        TPopupMenu *PopupMenu;
        TActionList *ActionList1;
        TAction *acExpand;
        TMenuItem *N1;
        TAction *acBack;
        TImageList *ILMain;
        TImageList *ILHot;
        TAction *acExit;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall pbShowPaint(TObject *Sender);
        void __fastcall pnlShowResize(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall sbXChange(TObject *Sender);
        void __fastcall sbYChange(TObject *Sender);
        void __fastcall pbShowMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall acExpandExecute(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall acExpandUpdate(TObject *Sender);
        void __fastcall acBackUpdate(TObject *Sender);
        void __fastcall acBackExecute(TObject *Sender);
        void __fastcall acExitExecute(TObject *Sender);
private:	// User declarations

        int X_Base, Y_Base;
        int X_Ofs, Y_Ofs;
        int f_X_offs, f_Y_offs;

		Graphics::TBitmap *f_ScrBitmap;
        TAlternateView* AV;
        TAlternateViewPainterList* f_PainterList;
        TClipPath *f_ClipPath;
        TBaseShape *f_OldSelected;
        TDynamicArray *f_Stack;
        TCompositeStack *f_History;
        void ReCreateGrid(int AWidth, int AHeight);
        void PaintToBitmap();
        void FreeBitmap();
        void SetNewPolygon();
        TPoint GetPointPolygon(int AXoffs, int AYoffs);
        void ApplyOffset(int AX, int AY);
        void RepaintFon();
        TBaseShape* FindTFE(int Ax, int Ay);
        void ExpandShape();
        void FreePainterList();
        TCompositeBaseWorkItem* FindComositeBaseWork(TBaseShape* ATFE, TCompositeBaseWork **AFind);
        TCompositeBaseWorkItem* FindComositeBaseWork2(int ATFEID, TCompositeBaseWork **AFind);
        void CoordinateCorrect();
        TRect GetMaxRect();
        void XYCorrect();
        TCompositeBaseWork* CreateWS(TAlternateViewItemTFS* ATFS);
        MESSAGE void __fastcall M_Close(TMessage& Msg);
public:		// User declarations

        void LoadAlternative(TTreeList* ATreeList);
        __fastcall TfrmAlternateView(TComponent* Owner);
        TColorSetup *MColorSetup;
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(WM_G_CLOSE, TMessage, M_Close)
        END_MESSAGE_MAP(TForm);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlternateView *frmAlternateView;
//---------------------------------------------------------------------------
#endif
