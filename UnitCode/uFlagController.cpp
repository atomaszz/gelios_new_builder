//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFlagController.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TFlagControllerItem
{
    private:
      TFlag *F_Flag;
      TBaseWorkShape *F_BaseWorkShape;
      TColor F_ColorEnter;
      TColor F_ColorLeave;
    public:
      TFlagControllerItem(TFlag *AFlag, TBaseWorkShape *ABaseWorkShape = NULL);
      __property TFlag* Flag = {read = F_Flag};
      __property TBaseWorkShape* BaseWorkShape = {read = F_BaseWorkShape};
      __property TColor ColorEnter = {read = F_ColorEnter, write = F_ColorEnter};
      __property TColor ColorLeave = {read = F_ColorLeave, write = F_ColorLeave};

};

class TFlagController
{
    private:
      TList* List;
      HWND F_WndMess;
      TTimer* F_Timer;
      int F_NumberMess;
    public:
      TFlagController(int AWndMess, int ANumberMess);
      ~TFlagController();
};
*/

TFlagControllerItem::TFlagControllerItem(TFlag *AFlag, TBaseWorkShape *ABaseWorkShape)
{
   F_ColorEnter = clWhite;
   F_ColorLeave  = clWhite;;
   F_Flag = AFlag;
   F_BaseWorkShape = ABaseWorkShape;
   F_Entered = false;
   f_ApplyColor = true;
}




TFlagController::TFlagController()
{
   List = new TList;
//   F_Timer = new TTimer(NULL);
 //  F_Timer->Interval = 12000;
//   F_Timer->Enabled = false;
//   F_Timer->OnTimer = TimerFunc;
//   F_WndMess = AWndMess;
//   F_NumberMess = ANumberMess;
}

TFlagController::~TFlagController()
{
   FreeList();
   delete List;
//   delete F_Timer;
}


void TFlagController::FreeList()
{
   TFlagControllerItem* Tmp;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Tmp = static_cast<TFlagControllerItem*>(List->Items[i]);
      delete Tmp;
      Tmp = NULL;
      List->Delete(i);
   }
}

/*
void __fastcall TFlagController::TimerFunc(System::TObject* Sender)
{
   TPoint P;
   TFlagControllerItem* Item;
   int cnt = 0;
   for (int i = 0; i <= List->Count - 1; i++)
   {
     Item = static_cast<TFlagControllerItem*>(List->Items[i]);
     {
       if (Item->Entered)
       {
          P = Item->Signal->Flag->GetPointLEControlToClient(Mouse->CursorPos);
          if ( !PtInRect(&(Item->Signal->Flag->GetRectLEControl()), P) )
          {
             Item->Signal->Flag->BrushColor = Item->ColorLeave;
             Item->Entered = false;
             PostMessage(F_WndMess, F_NumberMess, WPARAM(Item->Signal), 0);
          }
          else cnt++;
       }
     }
  }
  F_Timer->Enabled = cnt > 0;
}
*/


TFlagControllerItem* TFlagController::Find(TFlag *AFlag, int &APos)
{
   APos = -1;
   TFlagControllerItem* Res = NULL;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Res = static_cast<TFlagControllerItem*>(List->Items[i]);
      if (Res->Signal == AFlag)
      {
         APos = i;
         return Res;
      }
   }
   return NULL;
}


TFlagControllerItem* TFlagController::FindByFlagShape(TFlagShape *AFlagShape)
{
   TFlagControllerItem* Res;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Res = static_cast<TFlagControllerItem*>(List->Items[i]);
      if (Res->Signal->Flag == AFlagShape)
         return Res;
   }
   return NULL;
}


void TFlagController::AddFlag(TFlag *AFlag, TColor AColorEnter,
          TColor AColorLeave, TBaseWorkShape *ABaseWorkShape )
{
   int pos;
   TFlagControllerItem* Item = Find(AFlag, pos);
   if (!Item)
   {
      Item = new TFlagControllerItem(AFlag, ABaseWorkShape);
      Item->ColorEnter = AColorEnter;
      Item->ColorLeave = AColorLeave;
      AFlag->Flag->BrushColor = AColorLeave;
      List->Add(Item);
   }
}


void TFlagController::DeleteFlag(TFlag *AFlag)
{
   int pos;
   TFlagControllerItem* Tmp;
   Find(AFlag, pos);
   if ( pos >= 0 )
   {
     Tmp = static_cast<TFlagControllerItem*>(List->Items[pos]);
     delete Tmp;
     List->Delete(pos);
   }
}


bool TFlagController::Enter(TFlag *AFlag)
{
   int pos;
   bool res = false;
   TFlagControllerItem* Item = Find(AFlag, pos);
   if (Item)
   {
       AFlag->Flag->BrushColor = Item->ColorEnter;
       Item->Entered = true;
      // F_Timer->Enabled = true;
       res = true;
   }
   return res;
}

bool TFlagController::Leave(TFlag *AFlag)
{
   int pos;
   bool res = false;
   TFlagControllerItem* Item = Find(AFlag, pos);
   if (Item)
   {
       AFlag->Flag->BrushColor = Item->ColorLeave;
       Item->Entered = false;
       res = true;
   }
   return res;
}


bool TFlagController::EnterByShape(TFlagShape *AFlagShape)
{
   bool res = false;
   TFlagControllerItem* Item = FindByFlagShape(AFlagShape);
   if (Item)
   {
       AFlagShape->BrushColor = Item->ColorEnter;
       Item->Entered = true;
    //   F_Timer->Enabled = true;
       res = true;
   }
   return res;

}


bool TFlagController::LeaveByShape(TFlagShape *AFlagShape)
{
   bool res = false;
   TFlagControllerItem* Item = FindByFlagShape(AFlagShape);
   if (Item)
   {
       AFlagShape->BrushColor = Item->ColorLeave;
       Item->Entered = false;
       res = true;
   }
   return res;
}


void TFlagController::ApplyLeaveColor(TColor AColor)
{
   TFlagControllerItem* Item;
   for (int i = 0; i <= List->Count - 1; i++)
   {
      Item = static_cast<TFlagControllerItem*>(List->Items[i]);
      if (Item->ApplyColor)
      {
        Item->ColorLeave = AColor;
        Item->Signal->Flag->BrushColor = AColor;
      }
   }
}



void TFlagController::ApplyEnterColor(TColor AColor)
{
   TFlagControllerItem* Item;
   for (int i = 0; i <= List->Count - 1; i++)
   {
      Item = static_cast<TFlagControllerItem*>(List->Items[i]);
      if (Item->ApplyColor)
        Item->ColorEnter = AColor;
   }
}


TBaseWorkShape* TFlagController::FindWorkShape(TFlagShape *AFlagShape)
{
   TFlagControllerItem* Item = FindByFlagShape(AFlagShape);
   if (Item)
      return Item->BaseWorkShape;
   return NULL;
}

TFlagShape*  TFlagController::FindFlagShape(TBaseWorkShape* ABaseShape)
{
   TFlagControllerItem* Res;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Res = static_cast<TFlagControllerItem*>(List->Items[i]);
      if (Res->BaseWorkShape == ABaseShape)
         return Res->Signal->Flag;
   }
   return NULL;
}



bool TFlagController::ApplyFlagColor(TFlagShape *AFlagShape, TColor AEnter, TColor ALeave)
{
   TFlagControllerItem* Item = FindByFlagShape(AFlagShape);
   if (Item)
   {
      Item->ColorEnter = AEnter;
      Item->ColorLeave = ALeave;
      Item->ApplyColor = false;
      return true;
   }
   return false;
}


bool TFlagController::ResetFlagColor(TFlagShape *AFlagShape)
{
   TFlagControllerItem* Item = FindByFlagShape(AFlagShape);
   if (Item)
   {
      Item->ApplyColor = false;
      return true;
   }
   return false;
}


void TFlagController::ClearAll()
{
   FreeList();
}

