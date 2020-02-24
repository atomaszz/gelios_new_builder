//---------------------------------------------------------------------------

#ifndef uBaseWorkShapeH
#define uBaseWorkShapeH

#include "uBaseShape.h"
#include "uArrowLine.h"
#include "uTrailer.h"
#include "uListFlag.h"

class TBaseWorkShape;
class TCompositeBaseWork;

typedef void __fastcall (__closure *TShapeCopy)(TBaseShape *Shape, int Num_Shape);
typedef void __fastcall (__closure *TLineCopy)(TArrowLine *Line, int Num_Line);

typedef void __fastcall (__closure *TWSFlagCreate)(TFlag* AFlag, TBaseWorkShape *WS);
typedef void __fastcall (__closure *TWSFlagDestroy)(TFlag* AFlag, TBaseWorkShape *WS);
typedef void __fastcall (__closure *TAfterLinePrepare)(TBaseWorkShape *WS);



//---------------------------------------------------------------------------

class TBaseWorkShape
{

   private:
     int F_BlockId;
     TList *WorkShapes;
     TList *WorkLines;
     TPoint F_StartPoint;
     TPoint f_BaseStartPoint;

     TColor F_BrushColor;  //цвет кисти
     TColor F_PenColor;   //цвет пена
     TColor F_FrameColor; //цвет обрамл€ющего пр€моугольника
     Graphics::TFont* F_Font;
     int F_PenWidth;  // ширина пена
     TPenStyle F_PenStyle;  //стиль пена
     TBrushStyle F_BrushStyle; //стиль браша
     bool F_DrawFrame; //рисовать фрейм
     TPenMode F_PenMode;

     TColor F_LineColor;
     int    F_LineWidth;
     TPenStyle F_LineStyle;
     TPenMode  F_LineMode;
     TPoint F_Ofs_Point;

     bool F_IsLineCopy;  //коировать ли свойства линий
     bool F_IsBrushCopy;
     bool F_IsFontCopy;
     bool F_IsPenCopy;

     bool F_DrawCaption;

     bool F_DrawFirstFlag;
     bool F_DrawLastFlag;
     bool F_DrawMiddleFlag;
//     TTrailer *F_FirstTrailer;
//     TTrailer *F_LastTrailer;

     TShapeCopy FOnShapeCopy;
     TLineCopy  FOnLineCopy;
//     TWinControl* F_ParentWindow;
     bool f_LEControl;
     HWND F_WndHandler;
     TControl *F_UnderControl;
     TColor F_FlagColor;
     int F_FlagType;
     TColor F_FlagSColor;
     int F_FlagSType;
     TColor F_FlagEColor;
     int F_FlagEType;
     TColor F_FrameColorTFE;

     TListFlag *ListFlag;
     TWSFlagCreate FOnWSFlagCreate;
     TWSFlagDestroy FOnWSFlagDestroy;
     bool f_ApplyAttribute;
     int f_ParentShapeID;
     int f_Tag;
     TAfterLinePrepare FOnAfterLinePrepare;
     bool f_LEActive;
     int f_BaseOffsetX;
     int f_BaseOffsetY;
     TColor f_BaseLineColor;
     TCompositeBaseWork *f_CompositeWorkShape;


     void PenCopy();
     void BrushCopy();
     void FontCopy();
     void LineCopy();
     void __fastcall SetLEControl(bool Value);
     void __fastcall SetWndHandler(const HWND Value);
     void DoSetLEControl();
     void DoSetWndHandler();
     void __fastcall SetUnderControl(TControl* Value);
     void DoSetUnderCotrol();
     void DoSetFlag();
     void DoSetFlagS();
     void DoSetFlagE();

     void __fastcall FlagCreate(TRectLine *ASender, TFlagShape *AFlag, int APosFlag);
     void __fastcall FlagDestroy(TRectLine *ASender, TFlagShape *AFlag, int APosFlag);

     TRectLine* __fastcall GetRectLineItem(int AIndex);
     int __fastcall GetRectLineCount();
     void  DoSetLEActive();
     void __fastcall SetLEActive(bool AValue);
     void __fastcall SetBaseLineColor(TColor AValue);

   protected:
     int F_Step;
     int F_NumberShapeId;
     int F_NumberLineId;
     int F_LastShapeId;
     int F_LastLineId;
     int F_WidthWork;
     int F_Indent;
//     TList *AlternateShapeIDList;
     void FreeWorkShapes();
     int __fastcall virtual GetTypeShape();
     TPoint __fastcall virtual GetEndPoint();
     int __fastcall GetWorkLinesCount();
     int __fastcall GetWorkShapesCount();
     void __fastcall virtual SetStartPoint(TPoint Value);
     TPoint __fastcall virtual GetStartPoint();
     void __fastcall  SetBaseStartPoint(TPoint Value);
     bool __fastcall GetDrawCaption();
     void __fastcall SetDrawCaption(bool Value);
     void __fastcall SetFont(Graphics::TFont*  Value);
     int virtual CalcBend(int t_x1, int t_x2);
     void PaintFirstFlag();
     void PaintLastFlag();
     void PaintMiddleFlag();
     virtual  TRectLine* __fastcall GetFirstLine();
     virtual TRectLine* __fastcall GetLastLine();
     virtual TRectLine* __fastcall GetMiddleLine();
     void __fastcall SetDrawFirstFlag(bool Value);
     void __fastcall SetDrawLastFlag(bool Value);
     void __fastcall SetDrawMiddleFlag(bool Value);
     void __fastcall SetApplyAttribute(bool Value);
     virtual void PrepareLines();
     virtual int __fastcall GetOffsetXFromStart();
     virtual int __fastcall  CalcWidthWork();
     void __fastcall SetCompositeWorkShape(TCompositeBaseWork* ACWS);

   public:
     TBaseWorkShape(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id);
     virtual ~TBaseWorkShape();
     virtual void Init();
     virtual void Prepare();
     virtual void  Paint(TCanvas *Canvas);
     virtual  TBaseShape* GetShapeByLine(TRectLine* ALine, int APos);
     void AddShape(TBaseShape *N);
     void AddLine(TArrowLine *L);
     TBaseShape* GetWorkShape(int num);
     TBaseShape* GetWorkNode(int num);
     TArrowLine* GetWorkLine(int num);
     void SetOffsetPosition(int X_Ofs, int Y_Ofs);
     void SetBaseOffsetPosition(int X_Ofs, int Y_Ofs);
     TRect GetFrameRectWithLines();
     TRect FrameRectToRect(TRect R);
     TPoint GetStartPointFromFrameRect(TRect R);
     TRect GetMaxRect();
     bool KeepFlag(TBaseShape *Flag, int &type);
     void FreeWorkLines();
     virtual bool MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor);
     int  ShapeSupport(TBaseShape *AShape);
     TBaseShape*  ShapeSupportID(int AShapeID);
     void ShowAllFlagForSahpe(int AType, TColor AColor);
     void HideAllFlagForSahpe();
     virtual void CreateLines();
     int ReactMouse(TPoint APoint);
     int Bend(int t_x1, int t_x2);
     TPoint OffsetStartPoint();
     TPoint GetStartPointOneComposite();
     virtual void TrimFirstLine(bool ATrimComposite,  TPoint APStart, TPoint APEnd);
     __property TPoint StartPoint = {read = GetStartPoint, write = SetStartPoint};
     __property TPoint BaseStartPoint = {read = f_BaseStartPoint, write = SetBaseStartPoint};

     __property TColor  BrushColor = {read = F_BrushColor, write = F_BrushColor};
     __property TBrushStyle BrushStyle = {read = F_BrushStyle, write = F_BrushStyle};

     __property TColor  PenColor = {read = F_PenColor, write = F_PenColor};
     __property int     PenWidth = {read = F_PenWidth, write = F_PenWidth};
     __property TPenStyle PenStyle = {read = F_PenStyle, write = F_PenStyle};
     __property TPenMode PenMode = {read = F_PenMode, write = F_PenMode};
     __property Graphics::TFont*  Font = {read = F_Font, write = SetFont};
     __property TColor FrameColor  = {read = F_FrameColor, write = F_FrameColor};
     __property TColor FrameColorTFE  = {read = F_FrameColorTFE, write = F_FrameColorTFE};
     __property bool DrawFrame = {read = F_DrawFrame, write = F_DrawFrame};

     __property TColor    LineColor = {read = F_LineColor, write = F_LineColor};
     __property int       LineWidth = {read = F_LineWidth, write = F_LineWidth};
     __property TPenStyle LineStyle = {read = F_LineStyle, write = F_LineStyle};
     __property TPenMode  LineMode  = {read = F_LineMode,  write = F_LineMode};
     __property bool IsLineCopy = {read = F_IsLineCopy, write = F_IsLineCopy};
     __property bool IsBrushCopy = {read = F_IsBrushCopy, write = F_IsBrushCopy};
     __property bool IsFontCopy = {read = F_IsFontCopy, write = F_IsFontCopy};
     __property bool IsPenCopy = {read = F_IsPenCopy, write = F_IsPenCopy};
     __property int  TypeShape = {read = GetTypeShape};
     __property TShapeCopy  OnShapeCopy = {read = FOnShapeCopy, write = FOnShapeCopy};
     __property TLineCopy  OnLineCopy = {read = FOnLineCopy, write = FOnLineCopy};
     __property int FirstShapeId = {read = F_NumberShapeId};
     __property int LastShapeId = {read = F_LastShapeId};
     __property int FirstLineId = {read = F_NumberLineId};
     __property int LastLineId = {read = F_LastLineId};
     __property TPoint EndPoint = {read = GetEndPoint};
     __property int WorkShapesCount = {read = GetWorkShapesCount};
     __property int WorkLinesCount = {read = GetWorkLinesCount};
     __property bool DrawCaption = {read = GetDrawCaption, write = SetDrawCaption};
     __property bool DrawFirstFlag = {read = F_DrawFirstFlag, write = SetDrawFirstFlag};
     __property bool DrawLastFlag = {read = F_DrawLastFlag, write = SetDrawLastFlag};
     __property bool DrawMiddleFlag = {read = F_DrawMiddleFlag, write = SetDrawMiddleFlag};
     __property int BlockId = {read = F_BlockId, write = F_BlockId};
     __property int ShapeId = {read = F_NumberShapeId};
     __property int LineId = {read = F_NumberLineId};
//     __property TTrailer* FirstTrailer = {read = F_FirstTrailer};
//     __property TTrailer* LastTrailer = {read = F_LastTrailer};
     __property TRectLine* FirstLine = {read = GetFirstLine};
     __property TRectLine* LastLine = {read = GetLastLine};
     __property TRectLine* MiddleLine = {read = GetMiddleLine};
//     __property TWinControl *ParentWindow = {read = F_ParentWindow, write = SetParentWindow};
     __property bool LEControl = {read = f_LEControl, write  = SetLEControl};
     __property HWND WndHandler = {read = F_WndHandler, write = SetWndHandler};
     __property TControl* UnderControl = {read = F_UnderControl, write = SetUnderControl};
     __property TColor      FlagColor = {read = F_FlagColor, write = F_FlagColor};
     __property int      FlagType = {read = F_FlagType, write = F_FlagType};

     __property TColor      FlagSColor = {read = F_FlagSColor, write = F_FlagSColor};
     __property int      FlagSType = {read = F_FlagSType, write = F_FlagSType};

     __property TColor      FlagEColor = {read = F_FlagEColor, write = F_FlagEColor};
     __property int      FlagEType = {read = F_FlagEType, write = F_FlagEType};
     __property int Step = {read = F_Step};

     __property TWSFlagCreate   OnWSFlagCreate = {read = FOnWSFlagCreate, write = FOnWSFlagCreate};
     __property TWSFlagDestroy  OnWSFlagDestroy = {read = FOnWSFlagDestroy, write = FOnWSFlagDestroy};

     __property TRectLine*  RectLineItems[int AIndex] = { read =  GetRectLineItem};
     __property int RectLineCount = {read = GetRectLineCount};
     __property bool ApplyAttribute = {read = f_ApplyAttribute, write = SetApplyAttribute};
     __property int ParentShapeID = {read = f_ParentShapeID, write = f_ParentShapeID};
     __property int Tag = {read = f_Tag, write = f_Tag};
     __property TAfterLinePrepare OnAfterLinePrepare =  {read = FOnAfterLinePrepare, write = FOnAfterLinePrepare};
     __property bool LEActive = {read = f_LEActive, write = SetLEActive};
     __property int OffsetXFromStart = {read = GetOffsetXFromStart};
     __property int BaseOffsetX = {read = f_BaseOffsetX};
     __property int BaseOffsetY = {read = f_BaseOffsetY};
     __property int WidthWork = {read = CalcWidthWork};
     __property int Indent = {read = F_Indent};
     __property TColor BaseLineColor = {read = f_BaseLineColor, write = SetBaseLineColor};
     __property TCompositeBaseWork* CompositeWorkShape = {read = f_CompositeWorkShape, write = SetCompositeWorkShape};

};


#endif
