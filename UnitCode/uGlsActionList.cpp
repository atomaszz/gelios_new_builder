//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsActionList.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
TGlsActionListItem::TGlsActionListItem()
{
  f_Ctrl = false;
  f_Alt = false;
  f_Shift = false;
  f_SubMenu = false;
  f_SCut = "[нет]";
  f_Action = NULL;
}


//-----------------------------------------------------------------------------
TGlsActionList::TGlsActionList()
{
   f_List = new TList;
}

TGlsActionList::~TGlsActionList()
{
   FreeList();
   delete f_List;
}

void TGlsActionList::FreeList()
{
   TGlsActionListItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TGlsActionListItem*>(f_List->Items[i]);
      delete Item;
   }
   f_List->Clear();
}

int __fastcall TGlsActionList::GetCount()
{
  return f_List->Count;
}

TGlsActionListItem* __fastcall TGlsActionList::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TGlsActionListItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

void TGlsActionList::FillCharList(TStrings* AList)
{
  AList->Add("[нет]");
  AList->Add("0");
  AList->Add("1");
  AList->Add("2");
  AList->Add("3");
  AList->Add("4");
  AList->Add("5");
  AList->Add("6");
  AList->Add("7");
  AList->Add("8");
  AList->Add("9");
  AList->Add("A");
  AList->Add("B");
  AList->Add("C");
  AList->Add("D");
  AList->Add("E");
  AList->Add("F");
  AList->Add("G");
  AList->Add("H");
  AList->Add("I");
  AList->Add("J");
  AList->Add("K");
  AList->Add("L");
  AList->Add("M");
  AList->Add("N");
  AList->Add("O");
  AList->Add("P");
  AList->Add("Q");
  AList->Add("R");
  AList->Add("S");
  AList->Add("T");
  AList->Add("U");
  AList->Add("V");
  AList->Add("W");
  AList->Add("X");
  AList->Add("Y");
  AList->Add("Z");
  AList->Add("/");
  AList->Add("[");
  AList->Add("]");
  AList->Add("F2");
  AList->Add("F3");
  AList->Add("F4");
  AList->Add("F5");
  AList->Add("F6");
  AList->Add("F7");
  AList->Add("F8");
  AList->Add("F9");
  AList->Add("F10");
  AList->Add("F11");
  AList->Add("F12");
  AList->Add("BkSp");
  AList->Add("Tab");
  AList->Add("Num 5");
  AList->Add("Enter");
  AList->Add("Space");
  AList->Add("PgUp");
  AList->Add("PgDn");
  AList->Add("End");
  AList->Add("Home");
  AList->Add("Left");
  AList->Add("Up");
  AList->Add("Right");
  AList->Add("Down");
  AList->Add("Ins");
  AList->Add("Del");
  AList->Add("Pause");
  AList->Add("Scroll Lock");
}


TGlsActionListItem* TGlsActionList::CreateActionItem(AnsiString AName)
{
   TGlsActionListItem* Item = FindActionItem(AName);
   if (!Item)
   {
     Item = new TGlsActionListItem;
     Item->ActName = AName;
     f_List->Add(Item);
   }
   return Item;
}

TGlsActionListItem* TGlsActionList::FindActionItem(AnsiString AName)
{
   TGlsActionListItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TGlsActionListItem*>(f_List->Items[i]);
      if ( SameText(Item->ActName, AName) )
        return Item;
   }
   return NULL;
}

TGlsActionListItem* TGlsActionList::FindActionItemByCaption(AnsiString ACaption)
{
   TGlsActionListItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TGlsActionListItem*>(f_List->Items[i]);
      if ( SameText(Item->ActCaption, ACaption) )
        return Item;
   }
   return NULL;
}
