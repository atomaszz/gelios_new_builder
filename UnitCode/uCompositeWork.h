//---------------------------------------------------------------------------

#ifndef uCompositeWorkH
#define uCompositeWorkH
#include "uCompositeBaseWork.h"
#include "uBaseWorkShape.h"
#include "uAlternateViewItem.h"
#include "uDynamicArray.h"
//---------------------------------------------------------------------------

class TCompositeWork: public TCompositeBaseWork
{
   private:
     TRectLine *f_Rct;
     TBaseWorkShape *f_BWS;
     TBaseLine *f_LastLine;
     TBaseLine *f_FirstLine;
     TDynamicArray *f_LastRCT;
     TDynamicArray *f_FirstRCT;
     TRectLine *f_FirstRectLine;
     TPoint f_LP;
     void CreateLines(TBaseWorkShape *AWS);
     void PrepareDrawFlags();
   protected:
     TPoint __fastcall GetEndPoint();
     TPoint __fastcall GetStartPoint();
     TBaseLine* __fastcall GetEndLine();
     TRectLine* __fastcall GetFirstLine();
   public:
     TCompositeWork();
     ~TCompositeWork();
     bool ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV);
     void ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV);
     void Prepare();
     void MakeFirstLine(TPoint AStart, int ABend);

};


#endif
