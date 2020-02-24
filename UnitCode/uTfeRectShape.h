//---------------------------------------------------------------------------

#ifndef uTfeRectShapeH
#define uTfeRectShapeH
#include "uRectShape.h"
#include "uTTail.h"
//---------------------------------------------------------------------------
class TTfeRectShape: public TRectShape
{
  private:
   TTail *Start;
   TTail *End;
   void SetTail();
   void CopyPen();
  protected:
   TBaseLine* __fastcall  GetBaseLine(int AIndex);
   int __fastcall  GetBaseLineCount();
   TPoint __fastcall GetPointTailStartShape();
   TPoint __fastcall GetPointTailEndShape();

  public:
   TTfeRectShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
   ~TTfeRectShape();
   bool GetTailPoint(int num, TPoint &pt);
   void SetRect(int X, int Y, int Width, int Height);
   void SetRect(TRect Rect);
   void SetBaseRect(TRect Rect);
   void  Paint(TCanvas *Canvas);
   bool CopyObject(TBaseShape *ASource);
   AnsiString Make_One_SimpleItem(int AIndex);
};

#endif
