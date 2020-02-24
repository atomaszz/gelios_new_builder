//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uStackDust.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TStackDustItem
{
   private:
     TBaseWorkShape* f_WorkShape;
     int f_wsPos;
   public:
     TStackDustItem(TBaseWorkShape* AWorkShape);
};


class TStackDustController
{
   private:
     TList *f_List;
     void FreeList();
   public:
      TStackDustController();
     ~TStackDustController();
};
*/

TStackDustItemWS::TStackDustItemWS(TNodeMain* ANode)
{
   f_Node = ANode;
   f_NodePos = -1;
   f_CheckNesting = f_CheckAlternate = false;

}

TStackDustController::TStackDustController()
{
   f_ListWS = new TList;
   f_ListAlt = new TList;
   f_posWS = f_posAlt = 0;
}

TStackDustController::~TStackDustController()
{
   FreeListWS();
   //FreeListAlt();
   delete f_ListWS;
   delete f_ListAlt;
}


void TStackDustController::ClearAll()
{
    FreeListWS();
    f_ListAlt->Clear();
}


void TStackDustController::FreeListWS()
{
   TStackDustItemWS* Item;
   for (int i = f_ListWS->Count - 1; i>=0; i--)
   {
      Item = static_cast<TStackDustItemWS*>(f_ListWS->Items[i]);
      delete Item;
      Item = NULL;
      f_ListWS->Delete(i);
   }
}


bool TStackDustController::IsExistsNode(TNodeMain* ANode)
{
   TStackDustItemWS* Item;
   for (int i = 0; i <= f_ListWS->Count - 1; i++)
   {
     Item = static_cast<TStackDustItemWS*>(f_ListWS->Items[i]);
     if (Item->Node == ANode)
       return true;
   }
   return false;
}

bool TStackDustController::IsExistsAlternate(TNodeAlt *ANodeAlt)
{
   for (int i = 0; i <= f_ListAlt->Count - 1; i++)
   {
     if (static_cast<TNodeAlt*>(f_ListAlt->Items[i]) == ANodeAlt)
       return true;
   }
   return false;
}


void TStackDustController::AddNode(TNodeMain* ANode, int APos)
{
   if (!IsExistsNode(ANode))
   {
     TStackDustItemWS* Item = new TStackDustItemWS(ANode);
     Item->NodePos = APos;
     f_ListWS->Add(Item);
   }
}

void TStackDustController::AddAlternate(TNodeAlt *ANodeAlt)
{
   if ( !IsExistsAlternate(ANodeAlt) )
     f_ListAlt->Add(ANodeAlt);
}

TStackDustItemWS* TStackDustController::FirstWS()
{
   TStackDustItemWS* Res = NULL;
   f_posWS = 0;
   if (f_ListWS->Count > 0)
      Res = static_cast<TStackDustItemWS*>(f_ListWS->Items[f_posWS]);
   return Res;
}


TStackDustItemWS* TStackDustController::NextWS()
{
   TStackDustItemWS* Res = NULL;
   f_posWS++;
   if ((f_ListWS->Count > f_posWS) && (f_posWS >= 0) )
      Res = static_cast<TStackDustItemWS*>(f_ListWS->Items[f_posWS]);
   return Res;
}

TStackDustItemWS* TStackDustController::PriorWS()
{
   TStackDustItemWS* Res = NULL;
   f_posWS--;
   if ((f_ListWS->Count > f_posWS) && (f_posWS >= 0) )
      Res = static_cast<TStackDustItemWS*>(f_ListWS->Items[f_posWS]);
   return Res;
}

TStackDustItemWS* TStackDustController::LastWS()
{
   TStackDustItemWS* Res = NULL;
   if (f_ListWS->Count > 0)
   {
      f_posWS = f_ListWS->Count - 1;
      Res = static_cast<TStackDustItemWS*>(f_ListWS->Items[f_posWS]);
   }
   return Res;
}


//--------------------------------------------------------------------------
TNodeAlt* TStackDustController::FirstAlt()
{
   TNodeAlt* Res = NULL;
   f_posAlt = 0;
   if (f_ListAlt->Count > 0)
      Res = static_cast<TNodeAlt*>(f_ListAlt->Items[f_posAlt]);
   return Res;
}


TNodeAlt* TStackDustController::NextAlt()
{
   TNodeAlt* Res = NULL;
   f_posAlt++;
   if ((f_ListAlt->Count > f_posAlt) && (f_posAlt >= 0) )
      Res = static_cast<TNodeAlt*>(f_ListAlt->Items[f_posAlt]);
   return Res;
}

TNodeAlt* TStackDustController::PriorAlt()
{
   TNodeAlt* Res = NULL;
   f_posAlt--;
   if ((f_ListAlt->Count > f_posAlt) && (f_posAlt >= 0) )
      Res = static_cast<TNodeAlt*>(f_ListAlt->Items[f_posAlt]);
   return Res;
}


TNodeAlt* TStackDustController::LastAlt()
{
   TNodeAlt* Res = NULL;
   if (f_ListAlt->Count > 0)
   {
      f_posAlt = f_ListAlt->Count - 1;
      Res = static_cast<TNodeAlt*>(f_ListAlt->Items[f_posAlt]);
   }
   return Res;
}



/*
TAlternateList::TAlternateList()
{
   f_List = new TList;
   f_pos = 0;
}


TAlternateList::~TAlternateList()
{
   delete f_List;
}


void TAlternateList::ClearAll()
{
   f_List->Clear();
}


int __fastcall TAlternateList::GetCount()
{
   return  f_List->Count;
}


TAlternateItem* TAlternateList::First()
{
   TAlternateItem* Res = NULL;
   f_pos = 0;
   if (f_List->Count > 0)
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}


TAlternateItem* TAlternateList::Next()
{
   TAlternateItem* Res = NULL;
   f_pos++;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}

TAlternateItem* TAlternateList::Prior()
{
   TAlternateItem* Res = NULL;
   f_pos--;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}

TAlternateItem* TAlternateList::Last()
{
   TAlternateItem* Res = NULL;
   if (f_List->Count > 0)
   {
      f_pos = f_List->Count - 1;
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   }
   return Res;
}


*/
