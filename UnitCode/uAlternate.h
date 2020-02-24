//---------------------------------------------------------------------------

#ifndef uAlternateH
#define uAlternateH
#include "uArrowWorkShape.h"
#include "uClipPath.h"

//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TListChange)();

class TAlternateController;
class TAlternateItem
{
   private:
     int f_IdAlt;
     int f_NumAlt;
     int f_ParentIdAlt;
     int f_ParentNumAlt;
     bool f_First;
     TBaseWorkShape *f_WorkShape;
     TBaseWorkShape *f_OtherWorkShape;
     TArrowWorkShape *f_ArrowWorkShape;
     TColor f_ArrowColor;
     TColor f_EnterArrowColor;
     bool f_Entered;
     bool f_Visible;
     void __fastcall SetArrowColor(TColor AValue);
     void __fastcall SetEnterArrowColor(TColor AValue);
   public:
     TAlternateItem(TBaseWorkShape *AWorkShape, int AIdAlt, int ANumAlt,
       int AParentIdAlt, int AParentNumAlt, bool AFirst);
     ~TAlternateItem();
     __property  TArrowWorkShape* ArrowWorkShape = {read = f_ArrowWorkShape};
     __property  TBaseWorkShape* WorkShape = {read = f_WorkShape, write = f_WorkShape};
     __property  TBaseWorkShape* OtherWorkShape = {read = f_OtherWorkShape, write = f_OtherWorkShape};
     __property  bool First = {read = f_First, write = f_First};
     __property TColor EnterArrowColor = {read = f_EnterArrowColor, write = SetEnterArrowColor};
     __property TColor ArrowColor = {read = f_ArrowColor, write = SetArrowColor};
     __property bool Entered = {read = f_Entered, write = f_Entered};
     __property bool Visible = {read = f_Visible, write = f_Visible};
     __property int IdAlt = {read = f_IdAlt};
     __property int NumAlt = {read = f_NumAlt};
     __property int IdAltParent = {read = f_ParentIdAlt};
     __property int NumAltParent = {read = f_ParentNumAlt};

};


class TAlternateList
{
   friend TAlternateController;
   private:
     TList* f_List;
     int f_pos;
     int __fastcall GetCount();
   public:
     TAlternateList();
     ~TAlternateList();
     TAlternateItem* First();
     TAlternateItem* Next();
     TAlternateItem* Prior();
     TAlternateItem* Last();
     bool EnterByShape(TBaseShape *AFlagShape);
     bool LeaveByShape(TBaseShape *AFlagShape);
     void ClearAll();
     __property int Count = {read  = GetCount};
};


class TAlternateController
{
   private:
     HWND f_OwnerForm;
     TList *f_List;
     TColor f_ArrowColor;
     TColor f_EnterArrowColor;
     TColor f_PenColor;
     int f_PenWidth;
     TListChange FOnListChange;
     TClipPath* f_ClipPath;
     bool f_LEControl;
     HWND f_WndHandler;
     TControl *f_UnderControl;
     bool f_UpdateAlternateList;

     void FreeList();
     int FindAlternateItem(TBaseWorkShape *AWorkShape,  bool AFirst);
     TBaseWorkShape* FindNextWorkShape(TBaseWorkShape *W);
     TBaseWorkShape* FindPriorWorkShape(TBaseWorkShape *W);
     void DoAddAlternateItem(TBaseWorkShape *AWorkShape, int AId, int ANumAlt, int AParentId, int AParentNumAlt, bool AFirst);
     void DoDeleteAlternateItem(TBaseWorkShape *AWorkShape, int AId, int ANumAlt, bool AFirst);
     void __fastcall SetArrowColor(TColor AValue);
     void __fastcall SetEnterArrowColor(TColor AValue);
     void __fastcall SetPenColor(TColor AValue);
     void __fastcall SetPenWidth(int AValue);
     void RecalcCoordArrow();
   public:
     TAlternateController(HWND AOwnerForm);
     ~TAlternateController();

     bool AddAlternateItem(TBaseWorkShape *AWSFirst, TBaseWorkShape  *AWSLast, int AId, int ANumAlt,
       int AParentId, int AParentNumAlt);
     void DeleteAlternateItem(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast, int AId,  int ANum);
     void DeleteAlternateItem2(int AId, bool ASendMessage = true);
     void FillAlternateList(TAlternateList* AlternateList, int AParentShapeID,
         int AId, int ANumAlt);
     void VisibleArrow(TBaseWorkShape *W, bool AVisible);
     void VisibleArrowAll(bool AVisible);
     int IsExistsAlternate(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast);
     void CoordinateCorrect();
     void RecalcPosition(int AParentShapeID, int AId, int ANumAlt);
     bool GetWSToAlternate(int AId, TBaseWorkShape  **AWSFirst, TBaseWorkShape  **AWSLast);
     void ClearAll();
     bool DeleteWorkShape(TBaseWorkShape *AWS);

     __property TListChange  OnListChange = {read = FOnListChange, write = FOnListChange};
     __property TColor ArrowColor = {read = f_ArrowColor, write = SetArrowColor};
     __property TColor EnterArrowColor = {read = f_EnterArrowColor, write = SetEnterArrowColor};
     __property TColor PenColor = {read = f_PenColor, write = SetPenColor};
     __property int PenWidth = {read = f_PenWidth, write = SetPenWidth};
     __property bool LEControl = {read = f_LEControl, write  = f_LEControl};
     __property HWND WndHandler = {read = f_WndHandler, write = f_WndHandler};
     __property TControl* UnderControl = {read = f_UnderControl, write = f_UnderControl};
     __property bool UpdateAlternateList = {read = f_UpdateAlternateList, write = f_UpdateAlternateList};



};
#endif
