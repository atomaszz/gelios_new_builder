//---------------------------------------------------------------------------

#ifndef uColorSignalH
#define uColorSignalH
#include "uBaseShape.h"
#include "uBaseWorkShape.h"
//---------------------------------------------------------------------------
class TColorSignal
{
   private:
     TBaseShape* F_BS_Flag;
     TBaseWorkShape* F_BW_Flag;
     int F_Position;
     TColor F_ColorEnter;
     TColor F_ColorLeave;
     bool F_RepaintEnter;
     bool F_RepaintLeave;

   public:
     TColorSignal(TBaseShape* ABS_Flag, TBaseWorkShape* ABW_Flag, int APosition,
              TColor AColorEnter, TColor AColorLeave, bool ARepaintEnter, bool ARepaintLeave);
     __property TBaseShape* BS_Flag = {read = F_BS_Flag};
     __property TBaseWorkShape* BW_Flag = {read = F_BW_Flag};
     __property int Position = {read = F_Position};
     __property TColor ColorEnter = {read = F_ColorEnter, write = F_ColorEnter};
     __property TColor ColorLeave = {read = F_ColorLeave, write = F_ColorLeave};
     __property bool RepaintEnter = {read = F_RepaintEnter, write = F_RepaintEnter};
     __property bool RepaintLeave = {read = F_RepaintLeave, write = F_RepaintLeave};


};

class TColorSignalList
{
   private:
     TList* F_List;
     void FreeList();
     TColorSignal* FindFlagBase(TBaseShape* Flag, int Position);
     TColorSignal* FindFlagWork(TBaseWorkShape* Flag, int Position);
   public:
     TColorSignalList();
     ~TColorSignalList();
     void ApplyFlagBase(TBaseShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave);

     void ApplyFlagWork(TBaseWorkShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave);

     bool DeleteFlagBase(TBaseShape* AFlag, int APosition);
     bool DeleteFlagWork(TBaseWorkShape* AFlag, int APosition);

};


#endif
