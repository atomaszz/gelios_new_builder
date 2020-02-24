//---------------------------------------------------------------------------

#ifndef uZWorkORH
#define uZWorkORH
#include "uBaseWorkShape.h"
#include "uTfeRectShape.h"
//---------------------------------------------------------------------------
class TZWorkOR: public TBaseWorkShape
{
   private:
     TPoint VPoint;
     Graphics::TPen* F_OldPenParent;
     void CreateLines();
   protected:
     TRectLine* __fastcall GetFirstLine();
     TRectLine* __fastcall GetLastLine();
     int CalcBend(int t_x1, int t_x2);
     int __fastcall GetTypeShape();
   public:
     TZWorkOR(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id);
     ~TZWorkOR();
     void Init();
     void Prepare();
     void Paint(TCanvas *Canvas);
     TPoint __fastcall GetEndPoint();
};

#endif