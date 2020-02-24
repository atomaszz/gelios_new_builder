//---------------------------------------------------------------------------

#ifndef uRectLineH
#define uRectLineH
#include "uBaseLine.h"

class TRectLine;
class TFlagShape;

typedef void __fastcall (__closure *TRctFlagCreate)(TRectLine *ASender, TFlagShape *AFlag, int APosFlag);
typedef void __fastcall (__closure *TRctFlagDestroy)(TRectLine *ASender, TFlagShape *AFlag, int APosFlag);

//---------------------------------------------------------------------------
class TRectLine
{
   private:
     int x0, y0, x1, y1;
     int F_id;
     int F_bend;
     int F_Step;
     void CalcCoord();
     void FreeLines();
//     void DrawFlagFalse();
     int F_Width;
     TColor  F_Color;
     TPenStyle F_Style;
     TPenMode F_PenMode;
     bool F_DrawFlag;
     TColor F_FlagColor;
     int F_FlagType;

     bool F_DrawFlagS;
     TColor F_FlagSColor;
     int F_FlagSType;

     bool F_DrawFlagE;
     TColor F_FlagEColor;
     int F_FlagEType;
     bool f_LEControl;
     HWND F_WndHandler;
     TControl *F_UnderControl;
     TFlagShape *F_MiddleFlag;

     TRctFlagCreate FOnRctFlagCreate;
     TRctFlagDestroy FOnRctFlagDestroy;
     int f_CurrentBaseLine;
     bool f_PaintLine;
     TColor f_BaseLineColor;

     void __fastcall SetBend(int Value);
     TPoint __fastcall GetPointStart();
     TPoint __fastcall GetPointEnd();
     void __fastcall SetPointStart(TPoint Value);
     void __fastcall SetPointEnd(TPoint Value);
     void SetDrawFlagS();
     void SetDrawFlagE();
     void SetColorFlagS();
     void SetColorFlagE();
     void __fastcall SetLEControl(bool Value);
     void __fastcall SetWndHandler(const HWND Value);
     void __fastcall SetUnderControl(TControl* Value);
     void  DoSetLEControl();
     void  DoSetWndHandler();
     void  DoSetUnderControl();
     void ReverseLines();
     void CreateMiddleFlagToLine(TBaseLine* ALine, bool ADrawFlag);
     void __fastcall FlagImport(TBaseLine *ASource, TBaseLine *ADest, TFlagShape *AFlag, int APosFlag);
     void __fastcall SetBaseLineColor(TColor AValue);

   protected:
     TList *Lines;
     void InvisibleLines();
     TBaseLine* GetBaseLine(int num);
   public:
     void __fastcall FlagCreate(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag);
     void __fastcall FlagDestroy(TBaseLine *ASender, TFlagShape *AFlag, int APosFlag);
     TRectLine(int step, int number);
     void SetCoord(int x0, int y0, int x1, int y1, int bend=0);
     virtual ~TRectLine();
     virtual void Prepare();
     virtual void Paint(TCanvas *Canvas);
     bool KeepFlag(TBaseShape *Flag, int &type);
     void ApplyOffset(int Ax, int Ay);
     TBaseLine* FirstBaseLine();
     TBaseLine* NextBaseLine();


     __property int  xEnd = {read = x1, write = x1};
     __property int  yEnd = {read = y1, write = y1};
     __property int  xStart = {read = x0, write = x0};
     __property int  yStart = {read = y0, write = y0};

     __property TColor    Color = {read = F_Color, write = F_Color};
     __property int       Width = {read = F_Width, write = F_Width};
     __property TPenStyle Style = {read = F_Style, write = F_Style};
     __property TPenMode  Mode  = {read = F_PenMode,  write = F_PenMode};
     __property int Bend = {read = F_bend, write = SetBend};
     __property int ID = {read = F_id, write = F_id};
     __property TPoint    PointStart = {read  = GetPointStart, write = SetPointStart};
     __property TPoint    PointEnd = {read  = GetPointEnd, write = SetPointEnd};

     __property bool      DrawFlag = {read = F_DrawFlag, write = F_DrawFlag};
     __property TColor      FlagColor = {read = F_FlagColor, write = F_FlagColor};
     __property int      FlagType = {read = F_FlagType, write = F_FlagType};

     __property bool      DrawFlagS = {read = F_DrawFlagS, write = F_DrawFlagS};
     __property TColor      FlagSColor = {read = F_FlagSColor, write = F_FlagSColor};
     __property int      FlagSType = {read = F_FlagSType, write = F_FlagSType};

     __property bool      DrawFlagE = {read = F_DrawFlagE, write = F_DrawFlagE};
     __property TColor      FlagEColor = {read = F_FlagEColor, write = F_FlagEColor};
     __property int      FlagEType = {read = F_FlagEType, write = F_FlagEType};

     __property bool LEControl = {read = f_LEControl, write = SetLEControl};
     __property HWND WndHandler = {read = F_WndHandler, write = SetWndHandler};
     __property TControl* UnderControl = {read = F_UnderControl, write = SetUnderControl};

     __property TRctFlagCreate   OnRctFlagCreate = {read = FOnRctFlagCreate, write = FOnRctFlagCreate};
     __property TRctFlagDestroy  OnRctFlagDestroy = {read = FOnRctFlagDestroy, write = FOnRctFlagDestroy};
     __property bool PaintLine = {read = f_PaintLine, write = f_PaintLine};
     __property TColor BaseLineColor = {read = f_BaseLineColor, write = SetBaseLineColor};




};
#endif
