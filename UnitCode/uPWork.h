//---------------------------------------------------------------------------

#ifndef uPWorkH
#define uPWorkH
#include "uBaseWorkShape.h"
#include "uTfeRectShape.h"
#include "uWork.h"
//---------------------------------------------------------------------------
class TPWork: public TBaseWorkShape
{
   private:
     TWork *F_Work1;
     TWork *F_Work2;

     void __fastcall ShapeCopy(TBaseShape *Shape, int Num_Shape);
//     void __fastcall LineCopy(TArrowLine *Line, int Num_Line);
   protected:
     TRectLine* __fastcall GetFirstLine();
     TRectLine* __fastcall GetLastLine();
     TRectLine* __fastcall GetMiddleLine();

   public:
     TPWork(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id);
     void Init();
     void Prepare();
     void Paint(TCanvas *Canvas);
     void CreateLines();
     TPoint __fastcall GetEndPoint();
     TBaseShape* GetShapeByLine(TRectLine* ALine, int APos);
     bool MakeFlagForShape(TBaseShape* AShape, bool ACreate, int APos, int AType, TColor AColor);
     bool CanAlternate(int ID_Shape1, int ID_Shape2);
     void Decay(TWork **W1, TWork **W2, int a_lastLineId, int a_lastBlockId,
                int &a_retLastLineId);
};

#endif
