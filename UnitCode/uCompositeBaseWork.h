//---------------------------------------------------------------------------

#ifndef uCompositeBaseWorkH
#define uCompositeBaseWorkH
#include "uAlternateViewItem.h"
#include "uAlternateView.h"
#include "URectLine.h"
#include "uBaseShape.h"
#include "uCommonGraph.h"
#include "uCompositeStack2.h"
//---------------------------------------------------------------------------
const czw_ofsx = 3;

class TCompositeBaseWork;


class TCompositeBaseWorkItem
{
   private:
     TBaseShape *f_Shape;
     TBaseShape *f_SavedShape;
     TList* f_CompositeWorkList;
     void __fastcall SetBaseShape(TBaseShape *AShape);
     TCompositeBaseWork* __fastcall GetCompositeWork(int AIndex);
     int __fastcall GetCompositeWorkCount();
     TPoint __fastcall GetStartPoint();
     TPoint __fastcall GetEndPoint();
     TRect __fastcall GetMaxRect();
     void __fastcall SetStartPoint(TPoint AValue);
     void FreeList();
   public:
     TCompositeBaseWorkItem();
     ~TCompositeBaseWorkItem();
     void Prepare();
     void Paint(TCanvas *ACanvas);
     TBaseShape* FindTFE(int Ax, int Ay);
     void ApplyOffset(int Ax, int Ay);
     void AddCompositeWork(TCompositeBaseWork* AWork);
     TRect GetAnyRect();
     TRect GetRectSummary(TRect ARect);
     void OffsetEndCoordinate();
     void Degenerate();
     __property TBaseShape* BaseShape = {read = f_Shape, write = SetBaseShape};
     __property TCompositeBaseWork* CompositeWork[int AIndex] = {read = GetCompositeWork};
     __property int CompositeWorkCount = {read = GetCompositeWorkCount};
     __property TPoint StartPoint = {read = GetStartPoint, write = SetStartPoint};
     __property TPoint EndPoint = {read = GetEndPoint};
     __property TRect MaxRect = {read = GetMaxRect};
};

class TCompositeBaseWork
{
   private:
     TList *f_ListItem;
     TList *f_ListBL;
     TList *f_ListRectLine;
     int f_TopBorder;
     int f_OffsetTop;
     bool f_Selected;
     TPoint f_StartPoint;
     TColorSetup* f_ColorSetup;
     unsigned int f_Ref;
     TCompositeStack2 *f_History;
     TBaseLine* __fastcall GetBaseLineItem(int AIndex);
     int __fastcall GetBaseLineCount();
     TBaseWorkShape *f_ConvertedBWS;
   protected:
     int f_step;
     int f_LastLineBend;
     int f_FirstLineBend;
     TPoint f_EndPoint;
     void FreeListItem();
     void FreeListBL();
     void HideLines();
     void FreeListRectLine();
     void __fastcall virtual SetTopBorder(int AValue);
     void __fastcall SetLineColor(TColor AValue);
     int __fastcall GetItemCount();
     TPoint __fastcall virtual GetEndPoint();
     TPoint __fastcall virtual  GetStartPoint();
     virtual  TBaseLine* __fastcall GetEndLine();
     void __fastcall virtual SetStartPoint(TPoint AValue);
     void __fastcall SetSelected(bool AValue);
     TBaseLine* GetBaseLine(int AIndex);
     TBaseLine* GetNewLine();
     virtual TRectLine* __fastcall  GetFirstLine();
   public:
     TCompositeBaseWork();
     virtual ~TCompositeBaseWork();
     TCompositeBaseWorkItem* GetItem(int ANum);
     void AddBaseShape(TBaseShape *ABaseShape, bool IsHaveChild);
     void AddWorkItemShape(TCompositeBaseWorkItem *ABaseWorkItem);
     void AddBaseLine(TBaseLine *BL);
     void AddRectLine(TRectLine *ARectLine);
     TPoint OffsetEndCoordinate(TPoint AStart);
//     TSubstWork* GetSubstWork(int ANum);
     virtual void Prepare();
     virtual void Paint(TCanvas *ACanvas);
     virtual void ReplaceShape(int IdShapeReplace, TCompositeBaseWork *ANew);
     virtual void Appearance();
     virtual bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     virtual void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     TRect GetMaxRect();
//     void SetOffsetPosition(int Ax, int Ay);
     TBaseShape* FindTFE(int Ax, int Ay);
     TBaseShape* CloneShape(TBaseShape* ADest);
     virtual void ApplyOffset(int Ax, int Ay);
     TRect GetAnyRect();
     TRect GetRectSummary(TRect ARect);
     TCompositeBaseWorkItem* FindItem(int ABaseShapeID, TCompositeBaseWork **AFind);
     bool ContainedShape(int ABaseShapeID);
     TCompositeBaseWork* CopyRef();
     void FreeRef();
     void GetAllLines(TDynamicArray *R, bool AMarkFirst);
     void GetAllShapes(TDynamicArray *R);
     virtual void MakeFirstLine(TPoint AStart, int ABend);
     void SetColorAll(TColor AColor);
     void SetBrushColorAll(TColor AColor);
     void SetBrushStyleAll(TBrushStyle AStyle);
     virtual void  TrimFirstLine(TPoint APStart, TPoint APEnd);
     void DeleteLine(void *Line);


     __property int TopBorder = {read = f_TopBorder, write = SetTopBorder};
     __property int OffsetTop = {read = f_OffsetTop};
     __property TBaseLine* BaseLineItem[int AIndex] = {read = GetBaseLineItem};
     __property int BaseLineCount = {read = GetBaseLineCount};
     __property int ItemCount = {read = GetItemCount };
     __property int LastLineBend = {read = f_LastLineBend};
     __property int FirstLineBend = {read = f_FirstLineBend};
     __property TPoint StartPoint = {read = GetStartPoint, write = SetStartPoint};
     __property TPoint EndPoint = {read = GetEndPoint};
     __property TBaseLine* EndLine = {read = GetEndLine};
     __property TColorSetup* ColorSetup = {read = f_ColorSetup, write = f_ColorSetup};
     __property bool Selected = {read=  f_Selected, write = SetSelected};
     __property TRectLine* FirstLine = {read = GetFirstLine};
     __property TCompositeStack2* History = {read = f_History};
     __property TBaseWorkShape *ConvertedBWS = {read = f_ConvertedBWS, write = f_ConvertedBWS};

};

void StretchLineX(TBaseLine* ALine, int Ax);
void StretchLineY(TBaseLine* ALine, int Ay);

#endif
