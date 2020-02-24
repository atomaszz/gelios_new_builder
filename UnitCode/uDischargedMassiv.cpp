//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDischargedMassiv.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TDischargedMassivItem::TDischargedMassivItem()
{
  f_Col = 0;
  f_Row = 0;
}

TDischargedMassiv::TDischargedMassiv(const Variant ADef)
{
  f_Def = ADef;
  f_List = new TList;
}

TDischargedMassiv::~TDischargedMassiv()
{
  FreeList();
  delete f_List;
}

void TDischargedMassiv::FreeList()
{
  TDischargedMassivItem *Item;
  for (int i = 0; i <= f_List->Count - 1; i++)
  {
     Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
     delete Item;
  }
  f_List->Clear();
}

void TDischargedMassiv::DeleteItem(TDischargedMassivItem* ADel)
{
   int idx = f_List->IndexOf(ADel);
   if (idx >= 0)
   {
      delete ADel;
      f_List->Delete(idx);
   }
}


TDischargedMassivItem* TDischargedMassiv::DoFind(int ARow, int ACol)
{
   TDischargedMassivItem *Item;
   for(int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
      if ( (Item->f_Col == ACol) && (Item->f_Row == ARow) )
        return Item;
   }
   return NULL;
}

Variant __fastcall TDischargedMassiv::GetItems(int ARow, int ACol)
{
   TDischargedMassivItem* Item = DoFind(ARow, ACol);
   if (Item)
     return Item->f_Value;
   return f_Def;
}

void __fastcall TDischargedMassiv::SetItems(int ARow, int ACol, const Variant Value)
{
   TDischargedMassivItem* Item = DoFind(ARow, ACol);
   bool m_def = (f_Def == Value);
   if (Item)
   {
      if(m_def)
        DeleteItem(Item);
      else
        Item->f_Value = Value;
   }
   else
   {
      if(!m_def)
      {
         Item = new TDischargedMassivItem;
         Item->f_Col = ACol;
         Item->f_Row = ARow;
         Item->f_Value = Value;
         f_List->Add(Item);
      }

   }

}

int TDischargedMassiv::HiRow()
{
   int Res = 0;
   TDischargedMassivItem *Item;

   if (f_List->Count > 0)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[0]);
      Res = Item->f_Row;
   }

   for(int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
      if ( Item->f_Row > Res )
        Res = Item->f_Row;
   }
   return Res;
}

int TDischargedMassiv::HiCol()
{
   int Res = 0;
   TDischargedMassivItem *Item;

   if (f_List->Count > 0)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[0]);
      Res = Item->f_Col;
   }

   for(int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
      if ( Item->f_Col > Res )
        Res = Item->f_Col;
   }
   return Res;
}


int TDischargedMassiv::LoRow()
{
   int Res = 0;
   TDischargedMassivItem *Item;

   if (f_List->Count > 0)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[0]);
      Res = Item->f_Row;
   }

   for(int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
      if ( Item->f_Row < Res )
        Res = Item->f_Row;
   }
   return Res;
}

int TDischargedMassiv::LoCol()
{
   int Res = 0;
   TDischargedMassivItem *Item;

   if (f_List->Count > 0)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[0]);
      Res = Item->f_Col;
   }

   for(int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDischargedMassivItem*>(f_List->Items[i]);
      if ( Item->f_Col < Res )
        Res = Item->f_Col;
   }
   return Res;
}


Variant TDischargedMassiv::ActualValue(int ARow, int ACol, bool &Actual)
{
   TDischargedMassivItem* Item = DoFind(ARow, ACol);
   if (Item)
   {
     Actual = true;
     return Item->f_Value;
   }
   Actual = false;
   return f_Def;
}

void TDischargedMassiv::Clear()
{
  FreeList();
}

Variant __fastcall TDischargedMassiv::GetVal(int AIndex)
{
   return GetItems(0, AIndex);
}

void __fastcall TDischargedMassiv::SetVal(int AIndex, const Variant Value)
{
   SetItems(0, AIndex, Value);
}

bool TDischargedMassiv::IsEmpty()
{
   return (f_List->Count > 0);
}

double TDischargedMassiv::DoubleValue(int ARow, int ACol)
{
  return VarToDouble(Items[ARow][ACol]);
}

double TDischargedMassiv::DoubleValue(int AIndex)
{
  return VarToDouble(Val[AIndex]);
}



