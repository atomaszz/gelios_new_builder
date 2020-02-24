//---------------------------------------------------------------------------

#ifndef uCycleWhileDoH
#define uCycleWhileDoH
#include "uBaseWorkShape.h"
#include "uTfeRectShape.h"
#include "uTfeRhombShape.h"
//---------------------------------------------------------------------------
class TCycleWhileDo: public TBaseWorkShape
{
   private:
     void CreateLines();
     int CalcBend(int t_x1, int t_x2);
     void __fastcall ShapeCopy(TBaseShape *Shape, int Num_Shape);

   protected:
     TRectLine* __fastcall GetFirstLine();
     TRectLine* __fastcall GetLastLine();
     int __fastcall GetTypeShape();

   public:
     TCycleWhileDo(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id){};
     void Init();
     void Prepare();
     void Paint(TCanvas *Canvas);
     TPoint __fastcall GetEndPoint();
};

#endif
