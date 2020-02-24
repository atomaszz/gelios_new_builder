//---------------------------------------------------------------------------

#ifndef ufrmAlternateViewSelectH
#define ufrmAlternateViewSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "uDynamicArray.h"
#include "uAlternateViewItem.h"
#include <ActnList.hpp>
#include "uAlternateViewPainterList.h"
#include "uClipPath.h"
#include "uCommonGraph.h"
#include <System.Actions.hpp>


class TInnerAVSelectItem
{
   private:
     TList *f_List;
   public:
     TInnerAVSelectItem();
     ~TInnerAVSelectItem();
     void Add(TAlternateViewItemTFS *Item);
     TAlternateViewItemTFS* GetItem(int AIndex);
     int GetCount();
};

class TInnerAVSelect
{
   private:
     TList *f_List;
   public:
     TInnerAVSelect();
     ~TInnerAVSelect();
     TInnerAVSelectItem* GetNew();
     TInnerAVSelectItem* GetItem(int AIndex);
     int GetCount();
};

//---------------------------------------------------------------------------
class TfrmAlternateViewSelect : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnlMain;
        TButton *Button1;
        TStatusBar *SBar;
        TScrollBar *sbX;
        TScrollBar *sbY;
        TTabControl *TabControl;
        TPanel *pnlShow;
        TPaintBox *pbShow;
        TButton *Button2;
        TActionList *ActionList1;
        TAction *acOk;
        TAction *acCancel;
        TAction *acCheckDoubles;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall acOkExecute(TObject *Sender);
        void __fastcall acCancelExecute(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall pbShowPaint(TObject *Sender);
        void __fastcall pnlShowResize(TObject *Sender);
        void __fastcall sbXChange(TObject *Sender);
        void __fastcall sbYChange(TObject *Sender);
        void __fastcall TabControlChange(TObject *Sender);
        void __fastcall acOkUpdate(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall acCheckDoublesUpdate(TObject *Sender);
        void __fastcall acCheckDoublesExecute(TObject *Sender);
private:	// User declarations
        TInnerAVSelect* Mass;
        int X_Base, Y_Base;
        int X_Ofs, Y_Ofs;
        int f_X_offs, f_Y_offs;
        int f_X_offsSum, f_Y_offsSum;


        Graphics::TBitmap *f_ScrBitmap;
        TAlternateViewPainterList* f_PainterList;
        TClipPath *f_ClipPath;
        void ReCreateGrid(int AWidth, int AHeight);
        void FreeBitmap();
        void PaintToBitmap();
        void SetNewPolygon();
        TPoint GetPointPolygon(int AXoffs, int AYoffs);
        void RepaintFon();
        void ApplyOffset(int AX, int AY);
        void PrepareScroll();
        void ListChange(int Aid);
        void FreePainterList();
        void PrepareLevel();
        void CoordinateCorrect();
        bool CheckDubles();
        bool CheckDublesItem(TInnerAVSelectItem* A1, TInnerAVSelectItem* A2);
        TRect GetMaxRect();
        void XYCorrect();


public:		// User declarations

        TAlternateView* AV;
        TColorSetup *MColorSetup;
        TCompositeBaseWork* CreateWS(TAlternateViewItemTFS* ATFS);
        void AddMassiv(TDynamicArray *D);
        void GetAlternate(TDynamicArray *D);
        __fastcall TfrmAlternateViewSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlternateViewSelect *frmAlternateViewSelect;
//---------------------------------------------------------------------------
#endif
