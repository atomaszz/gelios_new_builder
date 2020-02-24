//---------------------------------------------------------------------------

#ifndef uBaseLineH
#define uBaseLineH
//#include "uFlagShape.h"

//---------------------------------------------------------------------------
const BL_HORIZONTAL = 0;
const BL_VERTICAL = 1;
const BL_OTHER = 2;
const BL_POINT = 3;

class TBaseLine;
class TFlagShape;
class TBaseShape;

typedef void __fastcall (__closure *TFlagCreate)(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag);
typedef void __fastcall (__closure *TFlagDestroy)(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag);

typedef void __fastcall (__closure *TFlagImport)(TBaseLine *ASource, TBaseLine *ADest, TFlagShape *AFlag, int APosFlag);


class TBaseLine
{
   private:
     int F_Step;
     bool F_DrawFlag;
     bool F_DrawFlagS;
     bool F_DrawFlagE;
     TFlagShape *F_Flag;
     TColor F_FlagColor;
     double F_FlagRadius;

     TFlagShape *F_FlagS;
     TColor F_FlagSColor;
     double F_FlagSRadius;

     TFlagShape *F_FlagE;
     TColor F_FlagEColor;
     double F_FlagERadius;
     int F_FlagType;
     int F_FlagSType;
     int F_FlagEType;

    // TWinControl *F_ParentWindow;
     bool f_LEControl;
     HWND F_WndHandler;
     TControl* F_UnderControl;
     bool F_Visible;
     TColor f_BasePenColor;


     TFlagCreate FOnFlagCreate;
     TFlagDestroy FOnFlagDestroy;
     TFlagImport FOnFlagImport;
     int f_Tag;
     int f_Tag2;

     void __fastcall SetPenColor(TColor Value);
     void __fastcall SetPenWidth(int Value);
     void __fastcall SetPenStyle(TPenStyle  Value);
     void __fastcall SetPenMode(TPenMode  Value);

     int  __fastcall GetTypeLine();

     TColor __fastcall GetPenColor();
     int __fastcall    GetPenWidth();
     TPenStyle __fastcall GetPenStyle();
     TPenMode __fastcall GetPenMode();

     TPoint __fastcall GetPointStart();
     TPoint __fastcall GetPointEnd();
     void __fastcall SetPointStart(TPoint Value);
     void __fastcall SetPointEnd(TPoint Value);
     void  __fastcall SetDrawFlag(bool Value);
     void  __fastcall SetDrawFlagS(bool Value);
     void  __fastcall SetDrawFlagE(bool Value);

     bool GetCoordLines(TPoint &p0, TPoint &p1, TPoint &p2, TPoint &p3, TPoint &Center);
     void DrawLinesAndFlag(TCanvas *Canvas);

     bool GetCoordLinesStart(TPoint &p0, TPoint &Center);
     bool GetCoordLinesEnd(TPoint &p0, TPoint &Center);
     TPoint __fastcall GetStart();
     TPoint __fastcall GetEnd();
     //void __fastcall SetParentWindow(TWinControl* Value);
     void __fastcall SetLEControl(bool Value);
     void __fastcall SetWndHandler(const HWND Value);
     void __fastcall SetUnderControl(TControl* Value);
     void __fastcall SetFlagColor(TColor Value);
     void __fastcall SetFlagSColor(TColor Value);
     void __fastcall SetFlagEColor(TColor Value);
     int  __fastcall GetMinX();
     int  __fastcall GetMinY();
     int  __fastcall GetMaxX();
     int  __fastcall GetMaxY();

    // void DoSetParentWindow();
    // void DoSetWndHandler();
    // void DoSetUnderControl();
   protected:
     int x0, y0, x1, y1;
     Graphics::TPen* Pen;
     Graphics::TPen* OldPenParent;
   public:
     TBaseLine(int x0, int y0, int x1, int y1, int step);
     virtual ~TBaseLine();
     int CompareToPoint(TPoint P);
     virtual void Paint(TCanvas *Canvas);
     virtual void PaintLine(TCanvas *Canvas);
     virtual void PaintFlag(TCanvas *Canvas);
     bool KeepFlag(TBaseShape *Flag, int &type);
     void ApplyCoord(int x0, int y0, int x1, int y1);
     void ApplyOffset(int Ax, int Ay);
     void MoveTo(int Ax, int Ay);
     void MoveTo(TPoint APoint);
     bool ImportFlag(TFlagShape *AFlag, int APos, int ATypeFlag,
           double ARadius, TColor ABrushColor);
    // bool NilFlag(int APos, TFlagShape *AFlag = NULL);
     int NilFlag(TFlagShape* AFlag);
     virtual bool CopyObject(TBaseLine *ASource);
    __property TColor    Color = {read = GetPenColor, write = SetPenColor};
    __property int       Width = {read = GetPenWidth, write = SetPenWidth};
    __property TPenStyle Style = {read = GetPenStyle, write = SetPenStyle};
    __property TPenMode  Mode  = {read = GetPenMode,  write = SetPenMode};
    __property int       TypeLine = {read = GetTypeLine};
    __property TPoint    PointStart = {read  = GetPointStart, write = SetPointStart};
    __property TPoint    PointEnd = {read  = GetPointEnd, write = SetPointEnd};
    __property bool      DrawFlag = {read = F_DrawFlag, write = SetDrawFlag};
    __property TColor      FlagColor = {read = F_FlagColor, write = SetFlagColor};
    __property double       FlagRadius = {read = F_FlagRadius, write = F_FlagRadius};
    __property int FlagType = {read = F_FlagType, write = F_FlagType};

    __property bool      DrawFlagS = {read = F_DrawFlagS, write = SetDrawFlagS};
    __property TColor      FlagSColor = {read = F_FlagSColor, write = SetFlagSColor};
    __property double       FlagSRadius = {read = F_FlagSRadius, write = F_FlagSRadius};
    __property int FlagSType = {read = F_FlagSType, write = F_FlagSType};

    __property bool      DrawFlagE = {read = F_DrawFlagE, write = SetDrawFlagE};
    __property TColor      FlagEColor = {read = F_FlagEColor, write = SetFlagEColor};
    __property double       FlagERadius = {read = F_FlagERadius, write = F_FlagERadius};
    __property int FlagEType = {read = F_FlagEType, write = F_FlagEType};

    __property TPoint Start = {read = GetStart};
    __property TPoint End = {read = GetEnd};

   // __property TWinControl *ParentWindow = {read = F_ParentWindow, write = SetParentWindow};
    __property bool LEControl = {read = f_LEControl, write = SetLEControl};
    __property HWND WndHandler = {read = F_WndHandler, write = SetWndHandler};
    __property TControl* UnderControl = {read = F_UnderControl, write = SetUnderControl};
    __property bool Visible = {read = F_Visible, write = F_Visible};

    __property TFlagCreate   OnFlagCreate = {read = FOnFlagCreate, write = FOnFlagCreate};
    __property TFlagDestroy  OnFlagDestroy = {read = FOnFlagDestroy, write = FOnFlagDestroy};
    __property TFlagImport   OnFlagImport = {read = FOnFlagImport, write = FOnFlagImport};

    __property int  X0 = {read = x0, write = x0};
    __property int  X1 = {read = x1, write = x1};
    __property int  Y0 = {read = y0, write = y0};
    __property int  Y1 = {read = y1, write = y1};
    __property int  MinX = {read = GetMinX};
    __property int  MinY = {read = GetMinY};
    __property int  MaxX = {read = GetMaxX};
    __property int  MaxY = {read = GetMaxY};
    __property TColor BasePenColor = {read = f_BasePenColor, write = f_BasePenColor};
    __property int Tag ={ read = f_Tag, write = f_Tag};
    __property int Tag2 ={ read = f_Tag2, write = f_Tag2};






};
#endif
