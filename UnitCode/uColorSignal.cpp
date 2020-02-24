//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uColorSignal.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TColorSignal
{
   public:
     TBaseShape* BS_Flag;
     TBaseWorkShape* BW_Flag;
     int F_position;
     TColor F_ColorEnter;
     TColor F_ColorLeave;
     bool F_RepaintEnter;
     bool F_RepaintLeave;
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
     ApplyFlagBase(TBaseShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave);

     ApplyFlagWork(TBaseWorkShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave);
};
*/

TColorSignal::TColorSignal(TBaseShape* ABS_Flag, TBaseWorkShape* ABW_Flag, int APosition,
              TColor AColorEnter, TColor AColorLeave, bool ARepaintEnter, bool ARepaintLeave)
{
   F_BS_Flag = ABS_Flag;
   F_BW_Flag = ABW_Flag;
   F_Position = APosition;
   F_ColorEnter = AColorEnter;
   F_ColorLeave = AColorLeave;
   F_RepaintEnter = ARepaintEnter;
   F_RepaintLeave = ARepaintLeave;
}


TColorSignalList::TColorSignalList()
{
   F_List = new TList;
}

TColorSignalList::~TColorSignalList()
{
   FreeList();
   delete F_List;
}

TColorSignal* TColorSignalList::FindFlagBase(TBaseShape* Flag, int Position)
{
   TColorSignal* Tmp;
   for (int i = 0 ; i < F_List->Count - 1; i++ )
   {
      Tmp = static_cast<TColorSignal*>(F_List->Items[i]);
      if ( (Tmp->BS_Flag == Flag) && (Tmp->Position) )
         return Tmp;
   }
   return NULL;
}


TColorSignal* TColorSignalList::FindFlagWork(TBaseWorkShape* Flag, int Position)
{
   TColorSignal* Tmp;
   for (int i = 0 ; i < F_List->Count - 1; i++ )
   {
      Tmp = static_cast<TColorSignal*>(F_List->Items[i]);
      if ( (Tmp->BW_Flag == Flag) && (Tmp->Position) )
         return Tmp;
   }
   return NULL;
}


void TColorSignalList::ApplyFlagBase(TBaseShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave)
{
   TColorSignal* Tmp = FindFlagBase(AFlag, APosition);
   if (Tmp)
   {
      Tmp->RepaintEnter = ARepaintEnter;
      Tmp->RepaintLeave = ARepaintLeave;
      Tmp->ColorEnter = AColorEnter;
      Tmp->ColorLeave = AColorLeave;
   }
   else
   {
      Tmp = new TColorSignal(AFlag, NULL, APosition, AColorEnter, AColorLeave,  ARepaintEnter, ARepaintLeave);
      F_List->Add(Tmp);
   }
}

void TColorSignalList::ApplyFlagWork(TBaseWorkShape* AFlag, int APosition , bool ARepaintEnter, TColor AColorEnter,
                bool ARepaintLeave, TColor AColorLeave)
{
   TColorSignal* Tmp = FindFlagWork(AFlag, APosition);
   if (Tmp)
   {
      Tmp->RepaintEnter = ARepaintEnter;
      Tmp->RepaintLeave = ARepaintLeave;
      Tmp->ColorEnter = AColorEnter;
      Tmp->ColorLeave = AColorLeave;
   }
   else
   {
      Tmp = new TColorSignal(NULL,  AFlag, APosition, AColorEnter, AColorLeave,  ARepaintEnter, ARepaintLeave);
      F_List->Add(Tmp);
   }
}

bool TColorSignalList::DeleteFlagBase(TBaseShape* AFlag, int APosition)
{
   TColorSignal* Tmp;
   for (int i = F_List->Count - 1 ; i > 0 ; i-- )
   {
      Tmp = static_cast<TColorSignal*>(F_List->Items[i]);
      if ( (Tmp->BS_Flag == AFlag) && (Tmp->Position) )
      {
         delete Tmp;
         Tmp = NULL;
         F_List->Delete(i);
         return true;
      }
   }
   return false;
}

bool TColorSignalList::DeleteFlagWork(TBaseWorkShape* AFlag, int APosition)
{
   TColorSignal* Tmp;
   for (int i = F_List->Count - 1 ; i > 0 ; i-- )
   {
      Tmp = static_cast<TColorSignal*>(F_List->Items[i]);
      if ( (Tmp->BW_Flag == AFlag) && (Tmp->Position) )
      {
         delete Tmp;
         Tmp = NULL;
         F_List->Delete(i);
         return true;
      }
   }
   return false;

}

