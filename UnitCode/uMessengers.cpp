//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMessengers.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TMessangers* GMess;


TMessangers::TMessangers()
{
   f_List = new TList;
}

TMessangers::~TMessangers()
{
   TMessangersItem* Item;
   for (int i = f_List->Count - 1; i >= 0 ; i--)
   {
     Item = static_cast<TMessangersItem*>(f_List->Items[i]);
     delete Item;
   }
   delete f_List;
}

bool TMessangers::RegistrMessage(int AMessage, TMsgFunc AFunc)
{
   TMessangersItem* Item;
   for (int i= 0; i <= f_List->Count - 1; i++)
   {
     Item = static_cast<TMessangersItem*>(f_List->Items[i]);
     if (Item->Message == AMessage)
       return false;
   }
   Item = new TMessangersItem;
   Item->Message = AMessage;
   Item->Func = AFunc;
   f_List->Add(Item);
   return true;
}

int TMessangers::SendMess(int AMessage, int Param1, int Param2)
{
   TMessangersItem* Item;
   for (int i= 0; i <= f_List->Count - 1; i++)
   {
     Item = static_cast<TMessangersItem*>(f_List->Items[i]);
     if (Item->Message == AMessage)
        return (*(Item->Func))(Param1, Param2);
   }
   return -1;
}
