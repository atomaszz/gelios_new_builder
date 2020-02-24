//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uListForPaint.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
TListForPaintItem::TListForPaintItem(void* AClassPoint, int AType)
{
   f_point = AClassPoint;
   f_type = AType;
}


//---------------------------------------------------------------------------
TListForPaint::TListForPaint()
{
   List = new TList;
   f_Count = 0;
}


//---------------------------------------------------------------------------
TListForPaint::~TListForPaint()
{
   FreeList();
   delete List;
}

//---------------------------------------------------------------------------
void TListForPaint::FreeList()
{
   TListForPaintItem* Item;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Item = static_cast<TListForPaintItem*>(List->Items[i]);
      delete Item;
      Item = NULL;
      List->Delete(i);
   }
}


//---------------------------------------------------------------------------
TListForPaintItem* __fastcall TListForPaint::GetItem(int AIndex)
{
    TListForPaintItem* res = NULL;
    if ( (AIndex > f_Count - 1) || (AIndex < 0) ) return res;
    res = static_cast<TListForPaintItem*>(List->Items[AIndex]);
    return res;
}

//---------------------------------------------------------------------------
bool TListForPaint::IsExist(void* AClassPoint)
{
   TListForPaintItem* Item;
   for (int i = List->Count - 1; i>=0; i--)
   {
      Item = static_cast<TListForPaintItem*>(List->Items[i]);
      if (Item->ClassPoint == AClassPoint) return true;
   }
   return false;
}


//---------------------------------------------------------------------------
bool TListForPaint::AddForPaint(void* AClassPoint, int AType)
{
   bool res = IsExist(AClassPoint);
   if (res) return false;
   TListForPaintItem* Item = new TListForPaintItem(AClassPoint, AType);
   List->Add(Item);
   f_Count++;
   return true;

}


//---------------------------------------------------------------------------
void TListForPaint::Clear()
{
   FreeList();
   f_Count = 0;
}
