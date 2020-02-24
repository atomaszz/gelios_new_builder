//---------------------------------------------------------------------------

#ifndef uPaintgridsH
#define uPaintgridsH
#include "uBaseShape.h"
#include "uTTail.H"
#include "uRectLine.h"
#include "uArrowLine.h"
#include "uTfeRectShape.h"
#include "uTfeRhombShape.h"
#include "uTfeEllShape.h"
#include "uTfeHexahedronShape.h"
#include "uWork.h"
#include "uPWork.h"
#include "uZWork.h"
#include "uZWorkOR.h"
#include "uCheckCondition.h"
#include "uCheckConditionCW.h"
#include "uControlWork.h"
#include "uControlFunc.h"
#include "uBifurcation.h"
#include "uCycleWhileDO.h"
#include "uCycleDoWhileDO.h"
#include "uCycleDoWhileDOFC.h"
#include "uArrowWorkShape.h"
#include "uClipPath.h"
#include "uListShape.h"
#include "uListForPaint.h"
#include "uFlagController.h"
#include "uInvalidateList.h"
#include "uLineCutting.h"
#include "uAlternate.h"
#include "uAltWSList.h"
#include "uCompositeBaseWork.h"


const WM_GD_PAINT = WM_USER + 1001;
const WM_GD_GETTYPSHAPE = WM_USER + 1002;
const WM_GD_RESETBUTTON = WM_USER + 1003;
const WM_GD_SETALTERNATE = WM_USER + 1004;
const WM_GD_SETADVANCEDALTERNATE = WM_USER + 1005;
const WM_GD_SETALTERNATEPARAM = WM_USER + 1006;
const WM_GD_SETNEWPOLYGON = WM_USER + 1007;
const WM_GD_SETNEWPOS = WM_USER + 1008;
const WM_GD_ADDWORKSHAPE = WM_USER + 1009;
const WM_GD_PAINTONEPREPARE = WM_USER + 1010;
const WM_GD_TIMEOUTLEAVE = WM_USER + 1011;
const WM_GD_GETNEXTWORKSHAPE = WM_USER + 1012;
const WM_GD_GETPRIORWORKSHAPE = WM_USER + 1013;
const WM_GD_INSERTWORKSHAPE = WM_USER + 1014;
const WM_GD_VISIBLEARROWALL = WM_USER + 1015;
const WM_GD_DELETETFSLIST = WM_USER + 1016;
const WM_GD_INSERTWORKSHAPEFROMFILE = WM_USER + 1017;
const WM_GD_GETMAINTABCOUNT = WM_USER + 1018;
const WM_GD_COPYTFSLIST = WM_USER + 1019;
const WM_GD_INSERTWORKSHAPEFROMCANAL = WM_USER + 1020;



const C_DEFAULTCLIPOFS = 4; //


class TPaintGrid
{
  private:
  //переменные
     int f_Width; //ширина
     int f_Height; //высота
     int f_StepPixels; //Шаг пиксела
     int f_StepPixelsGrid; //Шаг пиксела сетки
     bool f_PaintPixels; //рисовать ли пикселы
     TColor f_FonColor; //цвет фона
     TColor f_PixelColor; //цвет пиксела
     TCanvas *f_Canvas; //канва
     HWND f_OwnerForm;  //форма владельца
     bool f_RefreshFon; //нужно ли перерисовывать фон
     int f_WSPenWidth; //толщина линий ТФЕ
     Graphics::TBitmap *ScrBitmap;
     Graphics::TBitmap *ScrBitmapCopy;
     bool f_LEControl;
//     TWinControl *f_ParentWindow;
     TControl* f_UnderControl;
     HWND f_WndHandler;
     TPoint f_CurrEndPoint; //координаты последней точки
     TClipPath* f_ClipPath; //класс пути отсечения
     TListForPaint* f_ListForPaint; //содержит фигуры для отрисовки
     TFlagController* f_FlagController; //контроллер флагов
     TInvalidateList* f_InvalidateList; //список отрисовываемых фигур реально
     TLineCutting* f_LineCutting; //фигура при перетаскивании
     TAltWSList* f_AltWSList;//содержит ссодержитписок ТФС для показа альтернативы


     int f_X_offs; //смещение по Х
     int f_Y_offs; //смещение по Y
     int f_X_offsSum;
     int f_Y_offsSum;
     TColor f_LineColor;
     bool f_BrushTFE;
     TColor f_BrushColor;
     Graphics::TFont* f_FontTFE;
     TColor f_LeaveFlagColor;
     TColor f_EnterFlagColor;
     int f_FlagType;
     int f_CurrentCommand; // 1- добавление ТФЕ
     int f_TypMouseOperation; //тип операции с мышью
     TBaseShape* f_SelectedTFE; //выбранная ТФЕ
     TBaseWorkShape* f_SelectedTFS; //выбранная ТФС
     TColor f_FrameColorTFE; //цвет линии обрамления ТФЕ
     TColor f_FrameColorTFS; //цвет линии обрамления ТФC
     bool f_WSMoving;
     int f_WSMovingCount;
     TFlagShape* f_SelectedFlag; //выбранный флажок
     int f_Regim;
     TBaseWorkShape* f_SelectedAlternateFirst; //первая выбранная ТФС для альтернативы
     TBaseWorkShape* f_SelectedAlternateLast; //первая выбранная ТФС для альтернативы
     TBaseWorkShape* f_SelectedDeleteTFSFirst; //первая выбранная ТФС для альтернативы
     TBaseWorkShape* f_SelectedDeleteTFSLast; //первая выбранная ТФС для альтернативы

     TColor f_AltFlagColor;
     TColor f_AltEnterFlagColor;
     TColor f_AltArrowColor;
     TColor f_AltEnterArrowColor;
     TColor f_AltLineColor;
     TColor f_AltEnabledFlagColor;
     bool f_localVisiblearrowall;

 // функции
    void __fastcall SetStepPixels(int Value);
    void __fastcall SetStepPixelsGrid(int Value);
    void __fastcall SetPaintPixels(bool Value);
    void __fastcall SetFonColor(TColor Value);
    void __fastcall SetPixelColor(TColor Value);
    void __fastcall SetLineColor(TColor Value);
    void __fastcall SetBrushTFE(bool Value);
    void __fastcall SetBrushColor(TColor Value);
    void __fastcall SetFontTFE(Graphics::TFont* Value);
    void __fastcall SetFlagType(int Value);
    void __fastcall SetEnterFlagColor(TColor Value);
    void __fastcall SetLeaveFlagColor(TColor Value);
    void __fastcall SetFrameColorTFE(TColor Value);
    void __fastcall SetFrameColorTFS(TColor Value);
    void __fastcall SetTypMouseOperation(int Value);
    void __fastcall SetAltFlagColor(TColor Value);
    void __fastcall SetAltEnterFlagColor(TColor Value);
    void __fastcall SetAltArrowColor(TColor Value);
    void __fastcall SetAltEnterArrowColor(TColor Value);
    void __fastcall SetAltLineColor(TColor Value);
    void __fastcall SetAltEnabledFlagColor(TColor Value);

    void FreeBitmap();
    void FreeBitmapCopy();
    void CreateGrid(int Ax, int Ay);
    void CreateSrcBitmap(int Ax, int Ay);
    void CreateSrcBitmapCopy(int Ax, int Ay);
    void RepaintFon(int  Ax, int Ay);
    void DoPaint();
    void CopyFon();
    void ApplyAttributeForWorkShape(TBaseWorkShape* WS); // применяет аттрибуты для ТФС
    void ApplyAttributeForCompositeWorkShape(TBaseWorkShape* WS); 
    void BeforeResize();
    void RecalcCurrEndPoint();  // расчет последней координаты последней ТФС в f_CurrEndPoint

    void __fastcall WsFlagCreate(TFlag* AFlag, TBaseWorkShape *WS);
    void __fastcall WsFlagDestroy(TFlag* AFlag, TBaseWorkShape *WS);
    bool SelectTFE(int Ax, int Ay);
    bool SelectTFS(int Ax, int Ay);
    void NilTFE();
    void NilTFS();
    TBaseWorkShape* FindNextWorkShape(TBaseWorkShape *W);
    TBaseWorkShape* FindPriorWorkShape(TBaseWorkShape *W);
    TBaseWorkShape* __fastcall GetLastWorkShape();
    TBaseWorkShape* __fastcall GetFirstWorkShape();
    void RecalcFollowWorkShape(TBaseWorkShape* ABeforeInsertWork,  TBaseWorkShape* AInsertWork);
    void PaintAlternateList();
    bool CreateAternative(TFlagShape* AFlag);
    bool CreateDeleteTFSList(TFlagShape* AFlag);
    void NilAternative();
    void NilDeleteTFSList();
    void __fastcall SetRegim(int Value);
    int GetMainTabCount();


    __property int TypMouseOperation = {read = f_TypMouseOperation, write = SetTypMouseOperation};




  public:
     TPainterList* g_PainterList; //класс содержащие рабочие блоки
     TAlternateList*  g_AlternateList;

     TPaintGrid(TCanvas *ACanvas, HWND AOwnerForm);
     ~TPaintGrid();

     void Recreate(int AWidth,  int AHeight);
     void Paint();
     TBaseWorkShape* AddWorkShape(int AType, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine);
     TBaseWorkShape* InsertWorkShape(int AType, TBaseWorkShape* AWBefore, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine);
     HRGN GetRegion(TBaseWorkShape* WS, int AOfs);
     TPoint GetPointPolygon(int AXoffs = 0, int AYoffs = 0); //определение макисмальной точки полигона
     TPoint GetTopPoint(int AXoffs = 0, int AYoffs = 0);
     void ApplyOffset(int AX, int AY);
     void PreparePaint();
     int ApplyVisibleFlag(int APosition, bool AVisible); //показать флажки по всем ТФС по заданной позиции
     int ApplyVisibleFlagForAlternative(bool AVisible);///показать флажки по всем ТФС для создания альтернативы
     int ApplyVisibleFlagForDeleteTFS(bool AVisible);///показать флажки по всем ТФС для удаления от точки до точки
     void ReapintFlag(bool AEnter, TBaseShape* AFlag);
     void ReactMouse(TPoint APoint);
     void MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
     void MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
     void MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
     void PrepareLevel();
     void PrepareLevelOnOffset();
     void ClearAltWSList();
     void AddToAltWSList(TBaseWorkShape* AWS);
     HRGN GetRGNAltWSList();
     bool IsAltWSListEmpty();
     TBaseShape* FindTFE(int Ax, int Ay);
     TBaseWorkShape* FindTFS(int Ax, int Ay);
     TAlternateItem* FindAlternateItem(int Ax, int Ay);
     void ClearAll();
     void RecalcAfterDeleted(bool AFirst, TPoint FPoint);
     void SetWSFlagEvent(TBaseWorkShape *WS);
     void RecalcBaseOffsetPosition();
     void RecalcFollowWorkShape(TBaseWorkShape* ABeforeInsertWork,  TPoint AEndPoint);
     void RecalcAfterConverted(bool AFirst, TPoint FPoint);
     TBaseWorkShape* FindShapeFromCompositeWork(int AShapeID);
     void CoordinateCorrectForCompositeWork();
     TCompositeBaseWorkItem* FindComositeBaseWork2(int ATFEID, TCompositeBaseWork **AFind);
     TBaseWorkShape* CreateTempWorkShape(int AType, TPoint AStart, int ANumberShapeId = 0);

   __property int Width = {read = f_Width};
   __property int Height = {read = f_Height};
   __property int StepPixels = {read = f_StepPixels, write = SetStepPixels};
   __property int StepPixelsGrid = {read = f_StepPixelsGrid, write = SetStepPixelsGrid};
   __property bool PaintPixels = {read = f_PaintPixels, write = SetPaintPixels};
   __property TColor  FonColor = {read = f_FonColor, write = SetFonColor};
   __property TColor  PixelColor = {read = f_PixelColor, write = SetPixelColor};
   __property bool LEControl = {read = f_LEControl, write = f_LEControl};
   __property HWND WndHandler = {read = f_WndHandler, write = f_WndHandler};
   __property TControl* UnderControl = {read = f_UnderControl, write = f_UnderControl};
   __property int WSPenWidth = {read = f_WSPenWidth, write = f_WSPenWidth};
   __property bool RefreshFon = {read = f_RefreshFon, write = f_RefreshFon};

   __property TColor LineColor = {read = f_LineColor, write = SetLineColor};
   __property bool BrushTFE = {read = f_BrushTFE , write  = SetBrushTFE};
   __property TColor BrushColor = {read = f_BrushColor, write = SetBrushColor};
   __property Graphics::TFont* FontTFE = {read = f_FontTFE, write  = SetFontTFE};
   __property int FlagType = {read = f_FlagType, write = SetFlagType};
   __property TColor LeaveFlagColor  = {read = f_LeaveFlagColor, write = SetLeaveFlagColor};
   __property TColor EnterFlagColor  = {read = f_EnterFlagColor, write = SetEnterFlagColor};
   __property TColor FrameColorTFE = {read = f_FrameColorTFE, write = SetFrameColorTFE};
   __property TColor FrameColorTFS = {read = f_FrameColorTFS, write = SetFrameColorTFS};
   __property int Regim = {read = f_Regim, write = SetRegim};
   __property TBaseWorkShape* LastWorkShape = {read = GetLastWorkShape};
   __property TBaseWorkShape* FirstWorkShape = {read = GetFirstWorkShape};
   __property int OffsetSumX = {read = f_X_offsSum};
   __property int OffsetSumY = {read = f_Y_offsSum};
   __property TBaseShape* SelectedTFE = {read = f_SelectedTFE};
   __property TBaseWorkShape* SelectedTFS = {read = f_SelectedTFS, write = f_SelectedTFS};
   __property TColor AltFlagColor = {read = f_AltFlagColor, write = SetAltFlagColor};
   __property TColor AltEnterFlagColor = {read = f_AltEnterFlagColor, write = SetAltEnterFlagColor};
   __property TColor AltArrowColor = {read = f_AltArrowColor, write = SetAltArrowColor};
   __property TColor AltEnterArrowColor = {read = f_AltEnterArrowColor, write = SetAltEnterArrowColor};
   __property TColor AltLineColor = {read = f_AltLineColor, write = SetAltLineColor};
   __property TColor AltEnabledFlagColor = {read = f_AltEnabledFlagColor, write = SetAltEnabledFlagColor};
   __property int MouseOperation = {read = f_TypMouseOperation};



};


#endif
