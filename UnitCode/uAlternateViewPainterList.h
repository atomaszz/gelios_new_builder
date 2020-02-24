//---------------------------------------------------------------------------

#ifndef uAlternateViewPainterListH
#define uAlternateViewPainterListH
#include "uCompositeBaseWork.h"
//---------------------------------------------------------------------------
class TAlternateViewPainterList
{
   private:
     TList* f_List;
     int f_pos;
   public:
     TAlternateViewPainterList();
     ~TAlternateViewPainterList();
     TCompositeBaseWork* First();
     TCompositeBaseWork* Next();
     TCompositeBaseWork* Prior();
     TCompositeBaseWork* Last();
     void ClearAll();
     void AddItem(TCompositeBaseWork* AW);
     bool DeleteItem(TCompositeBaseWork* AW);
};
#endif
