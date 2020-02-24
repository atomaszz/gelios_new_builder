//---------------------------------------------------------------------------

#ifndef uCheckConditionCWH
#define uCheckConditionCWH
#include "uBaseWorkShape.h"
#include "uTfeRectShape.h"
#include "uTfeRhombShape.h"

//---------------------------------------------------------------------------
class TCheckConditionCW: public TBaseWorkShape
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
     TCheckConditionCW(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id){};
     void Init();
     void Prepare();
     void Paint(TCanvas *Canvas);
     TPoint __fastcall GetEndPoint();
     bool CanAlternate(int ID_Shape1, int ID_Shape2);
};

#endif
