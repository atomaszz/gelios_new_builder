//---------------------------------------------------------------------------

#ifndef uListFlagH
#define uListFlagH
#include "uBaseShape.h"
#include "uRectLine.h"
#include "uFlagShape.h"
//---------------------------------------------------------------------------
class TFlag
{
   private:
//     int F_Type;
     int F_Position;
     TBaseShape* F_Shape;
     TRectLine* F_Line;
     TFlagShape* F_Flag;
   public:
     TFlag();
//     __property int Type = {read = F_Type, write = F_Type};
     __property int Position = {read = F_Position, write = F_Position};
     __property TBaseShape* Shape = {read = F_Shape, write = F_Shape};
     __property TRectLine* Line = {read = F_Line, write = F_Line};
     __property TFlagShape* Flag = {read = F_Flag, write = F_Flag};

};

class TListFlag
{
   private:
      TList* List;
      void FreeList();
      int __fastcall GetCount();
      TFlag* __fastcall GetItem(int AIndex);
   public:
      TListFlag();
     ~TListFlag();
     TFlag* AddFlag(TFlagShape* AFlag, TBaseShape* AShape, TRectLine* ALine,
         int APosition,  bool &AFlagExits );
     TFlag* DeleteFlagByShape(TFlagShape* AFlag);
     bool DeleteFlagByFlag(TFlag* AFlag);
     __property int Count = {read = GetCount};
     __property TFlag* Items[int AIndex] = { read =  GetItem};
};

#endif
