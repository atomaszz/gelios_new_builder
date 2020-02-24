//---------------------------------------------------------------------------

#ifndef uWorkH
#define uWorkH
#include "uBaseWorkShape.h"
#include "uTfeRectShape.h"
#include "UFlagShape.h"
//---------------------------------------------------------------------------
class TWork: public TBaseWorkShape
{
   private:
   protected:
     TRectLine* __fastcall GetFirstLine();
     TRectLine* __fastcall GetLastLine();
     int __fastcall GetTypeShape();
   public:
     TWork(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id){};
     void Init();
     void Prepare();
     void Paint(TCanvas *Canvas);
     void CreateLines();
     TBaseShape* GetShapeByLine(TRectLine* ALine, int APos);
     TPoint __fastcall GetEndPoint();
     bool MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor);
};
#endif
