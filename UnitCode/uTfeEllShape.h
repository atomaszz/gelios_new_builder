//---------------------------------------------------------------------------

#ifndef uTfeEllShapeH
#define uTfeEllShapeH
#include "uTTail.h"
#include "uEllShape.h"
//---------------------------------------------------------------------------
class TTfeEllShape: public TEllShape
{
  private:
   TTail *T0;
   TTail *T1;
   TTail *T2;
   TTail *T3;

   bool F_TailLeft;
   bool F_TailTop;
   bool F_TailBottom;
   bool F_TailRight;

   void SetTail();
   void __fastcall SetTailLeft(bool Value);
   void __fastcall SetTailTop(bool Value);
   void __fastcall SetTailBottom(bool Value);
   void __fastcall SetTailRight(bool Value);
   void  CopyPen();
  protected:
   TPoint __fastcall GetPointTailStartShape();
   TPoint __fastcall GetPointTailEndShape();
  public:
   TTfeEllShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
   ~TTfeEllShape();
   bool GetTailPoint(int num, TPoint &pt);
   void SetRect(int X, int Y, int Width, int Height);
   void SetRect(TRect Rect);
   void  Paint(TCanvas *Canvas);
   void SetBaseRect(TRect Rect);
   bool CopyObject(TBaseShape *ASource);
   AnsiString Make_One_SimpleItem(int AIndex);
   __property bool TailLeft = {read = F_TailLeft, write = SetTailLeft};
   __property bool TailTop = {read = F_TailTop, write = SetTailTop};
   __property bool TailBottom = {read = F_TailBottom, write = SetTailBottom};
   __property bool TailRight = {read = F_TailRight, write = SetTailRight};
};

#endif
