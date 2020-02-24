//---------------------------------------------------------------------------

#ifndef uFlagControllerH
#define uFlagControllerH
#include "uBaseWorkShape.h"
#include "uListFlag.h"
//---------------------------------------------------------------------------
class TFlagControllerItem
{
    private:
      TFlag *F_Flag;
      TBaseWorkShape *F_BaseWorkShape;
      TColor F_ColorEnter;
      TColor F_ColorLeave;
      bool F_Entered;
      bool f_ApplyColor;
    public:
      TFlagControllerItem(TFlag *AFlag, TBaseWorkShape *ABaseWorkShape);
      __property TFlag* Signal = {read = F_Flag};
      __property TBaseWorkShape* BaseWorkShape = {read = F_BaseWorkShape};
      __property TColor ColorEnter = {read = F_ColorEnter, write = F_ColorEnter};
      __property TColor ColorLeave = {read = F_ColorLeave, write = F_ColorLeave};
      __property bool Entered = {read =  F_Entered, write = F_Entered };
      __property bool ApplyColor = {read = f_ApplyColor, write = f_ApplyColor};


};

class TFlagController
{
    private:
      TList* List;
     // HWND F_WndMess;
     // TTimer* F_Timer;
     // int F_NumberMess;
      void __fastcall TimerFunc(System::TObject* Sender);
      void FreeList();
      TFlagControllerItem* Find(TFlag *AFlag, int &APos);
    public:
      TFlagController();
      ~TFlagController();
      TFlagControllerItem* FindByFlagShape(TFlagShape *AFlagShape);
      void AddFlag(TFlag *AFlag, TColor AColorEnter, TColor AColorLeave,
              TBaseWorkShape *ABaseWorkShape = NULL);
      void DeleteFlag(TFlag *AFlag);
      bool Enter(TFlag *AFlag);
      bool Leave(TFlag *AFlag);
      bool EnterByShape(TFlagShape *AFlagShape);
      bool LeaveByShape(TFlagShape *AFlagShape);
      void ApplyLeaveColor(TColor AColor);
      void ApplyEnterColor(TColor AColor);
      TBaseWorkShape* FindWorkShape(TFlagShape *AFlagShape);
      TFlagShape*  FindFlagShape(TBaseWorkShape* ABaseShape);
      bool ApplyFlagColor(TFlagShape *AFlagShape, TColor AEnter, TColor ALeave);
      bool ResetFlagColor(TFlagShape *AFlagShape);
      void ClearAll();


};

#endif
