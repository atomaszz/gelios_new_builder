//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCursorStorage.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
class TCursorStorage
{
   private:
     TList* f_List;
   public:
     TCursorStorage();
     ~TCursorStorage();
     void Show(TCursor ACur = crHourGlass);
     void Hide();
};

TCursorStorage* gCursorStorage = NULL;

TCursorStorage::TCursorStorage()
{
   f_List = new TList;
}

TCursorStorage::~TCursorStorage()
{
   delete f_List;
}

void TCursorStorage::Show(TCursor ACur)
{
   f_List->Add((void*)Screen->Cursor);
   Screen->Cursor = ACur;
}

void TCursorStorage::Hide()
{
  int cnt = f_List->Count;
  if (cnt > 0)
  {
    Screen->Cursor = TCursor(f_List->Items[cnt - 1]);
    f_List->Delete(cnt - 1);
  }
}

void ShowCursorStorage(TCursor ACur)
{
   if (!gCursorStorage)
     gCursorStorage = new TCursorStorage;
   gCursorStorage->Show(ACur);
}

void HideCursorStorage()
{
   if (gCursorStorage)
     gCursorStorage->Hide();
}

void FreeCursorStorage()
{
   if (gCursorStorage)
     delete gCursorStorage;
}


