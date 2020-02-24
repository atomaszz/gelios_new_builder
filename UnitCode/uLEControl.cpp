//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uLEControl.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TLEControl::TLEControl()
{
   f_WndHandler = 0;
   f_Source = NULL;
   f_Id = 0;
   f_UnderControl = NULL;
   f_Left = f_Top = f_Width = f_Height = 0;
   f_Enter = false;
   f_Active = true;
}



bool TLEControl::React(TPoint APoint)
{
   TRect R;
   TPoint P;
   if (!f_UnderControl) return false;
   R = TRect(f_Left, f_Top, f_Left + f_Width, f_Top + f_Height);
   P = f_UnderControl->ScreenToClient(APoint);
   if ( PtInRect(&R, P) )
   {
      if (f_Enter) return false;
      f_Enter = true;
      if(WndHandler && f_Active)
        SendMessage(WndHandler, WM_LE_MOUSEENTER, WPARAM(Source), Id);
   }
   else
   {
      if (!f_Enter) return false;
      f_Enter = false;
      if(WndHandler && f_Active)
         SendMessage(WndHandler, WM_LE_MOUSELEAVE, WPARAM(Source), Id);
   }
   return true;
}



