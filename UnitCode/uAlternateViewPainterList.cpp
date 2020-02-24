//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternateViewPainterList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TAlternateViewPainterList::TAlternateViewPainterList()
{
   f_List = new TList;
   f_pos = 0;
}

TAlternateViewPainterList::~TAlternateViewPainterList()
{
   delete f_List;
}


void TAlternateViewPainterList::ClearAll()
{
   f_List->Clear();
}


TCompositeBaseWork* TAlternateViewPainterList::First()
{
   TCompositeBaseWork* Res = NULL;
   f_pos = 0;
   if (f_List->Count > 0)
      Res = static_cast<TCompositeBaseWork*>(f_List->Items[f_pos]);
   return Res;
}

TCompositeBaseWork* TAlternateViewPainterList::Next()
{
   TCompositeBaseWork* Res = NULL;
   f_pos++;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TCompositeBaseWork*>(f_List->Items[f_pos]);
   return Res;
}

TCompositeBaseWork* TAlternateViewPainterList::Prior()
{
   TCompositeBaseWork* Res = NULL;
   f_pos--;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TCompositeBaseWork*>(f_List->Items[f_pos]);
   return Res;
}

TCompositeBaseWork* TAlternateViewPainterList::Last()
{
   TCompositeBaseWork* Res = NULL;
   if (f_List->Count > 0)
   {
      f_pos = f_List->Count - 1;
      Res = static_cast<TCompositeBaseWork*>(f_List->Items[f_pos]);
   }
   return Res;
}

void TAlternateViewPainterList::AddItem(TCompositeBaseWork* AW)
{
    f_List->Add(AW);
}

bool TAlternateViewPainterList::DeleteItem(TCompositeBaseWork* AW)
{
   TCompositeBaseWork* Res = NULL;
   for (int i = 0 ; i <= f_List->Count -1; i++ )
   {
      Res = static_cast<TCompositeBaseWork*>(f_List->Items[f_pos]);
      if (Res == AW)
      {
         f_List->Delete(i);
         return true;
      }
   }
   return false;
}


