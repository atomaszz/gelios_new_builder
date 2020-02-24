//---------------------------------------------------------------------------

#ifndef uArrowWorkShapeH
#define uArrowWorkShapeH
//---------------------------------------------------------------------------
#include "uArrowShape.h"
#include "uBaseWorkShape.h"

class TArrowWorkShape: public TBaseWorkShape
{
   private:
   //  void __fastcall ShapeCopy(TBaseShape *Shape, int Num_Shape);
     int __fastcall GetCountNodeHind();
     int __fastcall GetNodeHintItem(int AIndex);
   public:
     TArrowWorkShape(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id);//: TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id);
     ~TArrowWorkShape();
     bool AddNodeHint(int ANum);
     bool DeleteNodeHint(int ANum);
     bool IsEmptyNodeHint();
     void Init();
     TRect GetRegionRect();
     TRect GetSmallRegionRect();
     __property int CountNodeHint = {read = GetCountNodeHind};
     __property int NodeHind[int AIndex] = { read =  GetNodeHintItem};
};



#endif
