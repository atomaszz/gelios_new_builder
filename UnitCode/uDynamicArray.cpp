//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDynamicArray.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TDynamicArray::TDynamicArray()
{
   f_List = new TList;
   f_PosStak = 0;
}

TDynamicArray::~TDynamicArray()
{
   FreeList();
   delete f_List;
}

void TDynamicArray::InitStack()
{
   f_PosStak = f_List->Count;
}

void* TDynamicArray::Pop()
{
   void *res;
   TDynamicArrayItem *Item;
   if (f_PosStak <= 0) return NULL;
   Item = static_cast<TDynamicArrayItem*>(f_List->Items[f_PosStak - 1]);
   f_PosStak--;
   res = Item->P;
   delete Item;
   f_List->Delete(f_PosStak);
//   Delete(Item->P);
   return res;
}


void TDynamicArray::FreeList()
{
   TDynamicArrayItem *Item;
   for (int i = f_List->Count - 1; i >= 0; i-- )
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      delete Item;
      f_List->Delete(i);
   }
}

void TDynamicArray::Clear()
{
   FreeList();
}


void __fastcall TDynamicArray::SetArray(int AIndex, void *AValue)
{
   TDynamicArrayItem *Item, *FindItem = NULL;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index == AIndex)
        FindItem = Item;
   }
   if(!FindItem)
   {
     FindItem = new  TDynamicArrayItem;
     FindItem->Index = AIndex;
     f_List->Add(FindItem);
   }
   FindItem->P = AValue;
}

int __fastcall TDynamicArray::GetCount()
{
   return  f_List->Count;
}

void* __fastcall TDynamicArray::GetArray(int AIndex)
{
   TDynamicArrayItem *Item, *FindItem = NULL;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index == AIndex)
        FindItem = Item;
   }
   if(FindItem)
     return FindItem->P;
   return NULL;
}

void* __fastcall TDynamicArray::GetItems(int AIndex)
{
   TDynamicArrayItem  *Item = NULL;
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     Item = static_cast<TDynamicArrayItem*>(f_List->Items[AIndex]);
   if (Item)
     return  Item->P;
   return NULL;
}

void TDynamicArray::Append(void* P)
{
   int m = -1;
   TDynamicArrayItem* Item;
   if (f_List->Count > 0)
      m = static_cast<TDynamicArrayItem*>(f_List->Items[0])->Index;
   for (int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index > m)
         m =  Item->Index;
   }
   m++;
   Item = new  TDynamicArrayItem;
   Item->Index = m;
   Item->P = P;
   f_List->Add(Item);
   f_PosStak++;
}

void TDynamicArray::InsertToFirst(void* P)
{
   int m = -1;
   TDynamicArrayItem* Item;

   if (f_List->Count > 0)
      m = static_cast<TDynamicArrayItem*>(f_List->Items[0])->Index;
   for (int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index > m)
         m =  Item->Index;
   }
   m++;
   Item = new  TDynamicArrayItem;
   Item->Index = m;
   Item->P = P;
   f_List->Insert(0, Item);
   f_PosStak++;
}


TDynamicArrayItem* TDynamicArray::Find(void* P)
{
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->P == P)
        return Item;
   }
   return NULL;
}


bool TDynamicArray::Delete(void* P)
{
   int m = -1;
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->P == P)
      {
         m = i;
         break;
      }
   }
   if (m > -1)
   {
      delete Item;
      f_List->Delete(m);
   }
   return (m > -1);
}

void TDynamicArray::AppendNamed(AnsiString AName, void* P)
{
   int m = -1;
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( AnsiSameText(Item->Name, AName) )
      {
         Item->P = P;
         return;
      }
   }
   if (f_List->Count > 0)
      m = static_cast<TDynamicArrayItem*>(f_List->Items[0])->Index;
   for (int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index > m)
         m =  Item->Index;

   }
   m++;
   Item = new  TDynamicArrayItem;
   Item->Index = m;
   Item->P = P;
   Item->Name = AName;
   f_List->Add(Item);
   f_PosStak++;
}


bool TDynamicArray::DeleteNamed(AnsiString AName)
{
   int m = -1;
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( AnsiSameText(Item->Name, AName) )
      {
         m = i;
         break;
      }
   }
   if (m > -1)
   {
      delete Item;
      f_List->Delete(m);
   }
   return (m > -1);
}


void* __fastcall TDynamicArray::GetNamed(AnsiString AIndex)
{
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( AnsiSameText(Item->Name, AIndex) )
        return Item->P;
   }
   return NULL;
}

void __fastcall TDynamicArray::SetNamed(AnsiString AIndex, void *AValue)
{
   AppendNamed(AIndex, AValue);
}


//--------------------------------------------------------------------------

void TDynamicArray::AppendInteger(int APos, void *AValue )
{
   int m = -1;
   TDynamicArrayItem* Item;
  /* for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( Item->Int_Value ==  APos)
      {
         Item->P = AValue;
         return;
      }
   }*/
   if (f_List->Count > 0)
      m = static_cast<TDynamicArrayItem*>(f_List->Items[0])->Index;
   for (int i = 1; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if (Item->Index > m)
         m =  Item->Index;
   }
   m++;
   Item = new  TDynamicArrayItem;
   Item->Index = m;
   Item->P = AValue;
   Item->Int_Value = APos;
   f_List->Add(Item);
   f_PosStak++;
}


bool TDynamicArray::DeleteInteger(int APos)
{
   int m = -1;
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( Item->Int_Value ==  APos )
      {
         m = i;
         break;
      }
   }
   if (m > -1)
   {
      delete Item;
      f_List->Delete(m);
   }
   return (m > -1);
}

void* __fastcall TDynamicArray::GetInteger(int APos)
{
   TDynamicArrayItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TDynamicArrayItem*>(f_List->Items[i]);
      if ( Item->Int_Value ==  APos )
        return Item->P;
   }
   return NULL;
}

void __fastcall TDynamicArray::SetInteger(int APos, void *AValue)
{
   AppendInteger(APos, AValue);
}

TDynamicArrayItem* TDynamicArray::Last()
{
   TDynamicArrayItem *Item;
   if (f_PosStak < 0) return NULL;
   Item = static_cast<TDynamicArrayItem*>(f_List->Items[f_PosStak - 1]);
   return Item;
}

TDynamicArrayItem* __fastcall TDynamicArray::GetPosition(int APos)
{
   if (APos >= 0 && APos <= f_List->Count - 1)
     return  static_cast<TDynamicArrayItem*>(f_List->Items[APos]);
   return NULL;
}

int TDynamicArray::DeleteArray(TDynamicArray* AList)
{
   int res = 0;
   TDynamicArrayItem *Curr = NULL;
   if ( ( f_PosStak - 1 ) >= 0 )
      Curr = static_cast<TDynamicArrayItem*>(f_List->Items[f_PosStak - 1]);
   for(int i = 0; i <= AList->Count - 1; i++)
     if ( Delete(AList->Items[i]) )
       res++;
   int pos = 0;
   for(int i = 0; i <= f_List->Count - 1; i++)
   {
     if ( (static_cast<TDynamicArrayItem*>(f_List->Items[i])) == Curr )
     {
         pos = i;
         break;
     }
   }
   f_PosStak = pos+1;
   return res;
}


