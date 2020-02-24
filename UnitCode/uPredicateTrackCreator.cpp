//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicateTrackCreator.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TPredicateTrackCreatorItem::TPredicateTrackCreatorItem()
{
   f_List = new TList;
}

TPredicateTrackCreatorItem::~TPredicateTrackCreatorItem()
{
   delete f_List;
}


int __fastcall TPredicateTrackCreatorItem::GetCount()
{
   return f_List->Count;
}

TPredicateScannerItemKnot* __fastcall TPredicateTrackCreatorItem::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicateScannerItemKnot*>(f_List->Items[AIndex]);
   else
     return NULL;
}

bool TPredicateTrackCreatorItem::FindKnot(TPredicateScannerItemKnot* AKnot)
{
   return f_List->IndexOf(AKnot) >= 0;
}

void TPredicateTrackCreatorItem::AddKnot(TPredicateScannerItemKnot* AKnot)
{
   if(!FindKnot(AKnot))
     f_List->Add(AKnot);
}

void TPredicateTrackCreatorItem::PushKnot(TPredicateScannerItemKnot* AKnot)
{
   if(!FindKnot(AKnot))
     f_List->Insert(0, AKnot);
}

void TPredicateTrackCreatorItem::DeleteKnot(TPredicateScannerItemKnot* AKnot)
{
   int idx = f_List->IndexOf(AKnot);
   if (idx >= 0)
      f_List->Delete(idx);
}



int TPredicateTrackCreatorItem::CountKnotByParentID(int AID)
{
   int res = 0;
   TPredicateScannerItemKnot* Item;
   for(int i = 0; i <= Count - 1; i++)
   {
     Item = Items[i];
     if (Item->ParentID == AID)
       res++;
   }
   return res;
}


void TPredicateTrackCreatorItem::GetBadKnot(TDynamicArray *OutKnot)
{
  bool b1, b2, b3;
  OutKnot->Clear();
  TPredicateScannerItemKnot* Knot;
  for(int i = 0; i <= Count - 1; i++)
  {
    b1 = true;
    b2 = true;
    b3 = true;
    Knot = Items[i];
    if(Knot->TFE_ID1 < 0)
      b1 = CountKnotByParentID(Knot->TFE_ID1);
    if(Knot->TFE_ID2 < 0)
      b2 = CountKnotByParentID(Knot->TFE_ID2);
    if(Knot->TFE_ID3 < 0)
      b3 = CountKnotByParentID(Knot->TFE_ID3);

    if(!b1 || !b2 || !b3)
      OutKnot->Append(Knot);
  }
}


AnsiString __fastcall TPredicateTrackCreatorItem::GetText()
{
  AnsiString Res = "";
  TPredicateScannerItemKnot* Knot;
  for(int i = 0; i <= Count - 1; i++)
  {
    Knot = Items[i];
    Res = Res + Knot->ItemName() + "\r\n";
  }
  return Res;
}




//---------------------------- PredicateTrackCreator ---------------------------
TPredicateTrackCreator::TPredicateTrackCreator()
{
  f_List = new TList;
  f_ListBase = new TList;
  f_BaseTrack = new TPredicateTrackCreatorItem;
}

TPredicateTrackCreator::~TPredicateTrackCreator()
{
  FreeList();
  ClearBase();
  delete f_List;
  delete f_ListBase;
  delete f_BaseTrack;
}

void TPredicateTrackCreator::FreeList()
{
   TPredicateTrackCreatorItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
     Item = static_cast<TPredicateTrackCreatorItem*>(f_List->Items[i]);
     delete Item;
   }
   f_List->Clear();
}


int __fastcall TPredicateTrackCreator::GetCount()
{
   return f_List->Count;
}

TPredicateTrackCreatorItem* __fastcall TPredicateTrackCreator::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TPredicateTrackCreatorItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

TPredicateTrackCreatorItem* TPredicateTrackCreator::CreateItem()
{
   TPredicateTrackCreatorItem* N;
   N = new TPredicateTrackCreatorItem;
   f_List->Add(N);
   return N;
}

void TPredicateTrackCreator::GetAllTrack(TPredicateTrackCreatorItem* AItem,
  TDynamicArray *OutTrack)
{
  int id1, id2, id3;
  bool b1, b2, b3;
  TPredicateScannerItemKnot* Knot;
  //TPredicateScannerItemKnot* Found;
  OutTrack->Clear();
  if (f_List->IndexOf(AItem) >= 0)
  {
    for(int i = 0; i <= f_BaseTrack->Count - 1; i++)
    {
      Knot = f_BaseTrack->Items[i];
      if (!AItem->FindKnot(Knot))
      {
        b1 = true;
        b2 = true;
        b3 = true;
        id1 = Knot->TFE_ID1;
        id2 = Knot->TFE_ID2;
        id3 = Knot->TFE_ID3;

        if (id1 != 0)
         b1 = f_BaseTrack->CountKnotByParentID(id1) == AItem->CountKnotByParentID(id1);

        if (id2 != 0)
         b2 = f_BaseTrack->CountKnotByParentID(id2) == AItem->CountKnotByParentID(id2);

        if (id3 != 0)
         b3 = f_BaseTrack->CountKnotByParentID(id3) == AItem->CountKnotByParentID(id3);

        if(b1 && b2 && b3)
          OutTrack->Append(Knot);
      }
    }
  }
}

void TPredicateTrackCreator::ClearTrack()
{
   FreeList();
}

void TPredicateTrackCreator::ClearBase()
{
   TPredicateScannerItemKnot* Item;
   for(int i = 0; i <= f_BaseTrack->Count - 1; i++)
   {
      Item = static_cast<TPredicateScannerItemKnot*>(f_BaseTrack->Items[i]);
      delete Item;
   }
   f_BaseTrack->Clear();
}

TPredicateScannerItemKnot* TPredicateTrackCreator::CreateKnotToBase()
{
   TPredicateScannerItemKnot* N  = new TPredicateScannerItemKnot;
   f_ListBase->Add(N);
   f_BaseTrack->AddKnot(N);
   return N;
}

void TPredicateTrackCreator::GetNegativeDecidedKnot(TPredicateTrackCreatorItem* AItem,
  TDynamicArray *OutKnot)
{
  bool b1, b2, b3;
  OutKnot->Clear();
  TPredicateScannerItemKnot* Knot;
  if (f_List->IndexOf(AItem) >= 0)
  {
     for(int i = 0; i <= f_BaseTrack->Count - 1; i++)
     {
       Knot = f_BaseTrack->Items[i];
       if (!AItem->FindKnot(Knot))
       {
          if( (Knot->TFE_ID1 <= 0) && (Knot->TFE_ID2 <= 0) && (Knot->TFE_ID3 <= 0) )
          {
            b1 = true;
            b2 = true;
            b3 = true;
            if (Knot->TFE_ID1 < 0)
              b1 = AItem->CountKnotByParentID(Knot->TFE_ID1) == f_BaseTrack->CountKnotByParentID(Knot->TFE_ID1) ;

            if (Knot->TFE_ID2 < 0)
              b2 = AItem->CountKnotByParentID(Knot->TFE_ID2) == f_BaseTrack->CountKnotByParentID(Knot->TFE_ID2) ;

            if (Knot->TFE_ID3 < 0)
              b3 = AItem->CountKnotByParentID(Knot->TFE_ID3) == f_BaseTrack->CountKnotByParentID(Knot->TFE_ID3) ;

            if(b1 && b2 && b3)
              OutKnot->Append(Knot);
          }
       }
     }
   }
}

TPredicateTrackCreatorItem* TPredicateTrackCreator::CloneItem(TPredicateTrackCreatorItem* ASource)
{
   TPredicateTrackCreatorItem* N;
   N = new TPredicateTrackCreatorItem;
   f_List->Add(N);
   for(int i = 0; i <= ASource->Count - 1; i++)
     N->AddKnot(ASource->Items[i]);
   return N;

}

void TPredicateTrackCreator::GenerateOptSovmTrack(TOgrSovmArray* AOgrSovm)
{
  bool isOgr;
  TPredicateTrackCreatorItem* P;
  TPredicateScannerItemKnot *Knot;
  if (AOgrSovm)
  {
    TDynamicArray *D = new TDynamicArray;
    ClearTrack();
    P = CreateItem();

    isOgr = false;
    while ( true )
    {
      GetAllTrack(P, D);
      if ( D->Count == 0 )
         break;
      for(int i = 0; i <= D->Count - 1; i++)
      {
        Knot = static_cast<TPredicateScannerItemKnot*>(D->Items[i]);
        isOgr = AOgrSovm->IsContainsKnot(Knot->TFE_ID1, Knot->TFE_ID2, Knot->TFE_ID3);
        if ( isOgr )
          P->PushKnot(Knot);
      }
      if ( !isOgr )
        for(int i = 0; i <= D->Count - 1; i++)
          P->PushKnot( static_cast<TPredicateScannerItemKnot*>(D->Items[i]) );

    }
    delete D;
  }
}

/*
  TPredicateTrackCreatorItem* CI;
  TPredicateScannerItemKnot *Knot, *NW;
  TDynamicArray *D = new TDynamicArray;
  Zadacha->TrackCreator->GetAllTrack(AItem, f_Arr);
  if (f_Arr->Count > 0)
  {
    for(int i = 0; i <= f_Arr->Count - 1; i++)
    {
      if (CheckRnd())
      {
         Knot = static_cast<TPredicateScannerItemKnot*>(f_Arr->Items[i]);
         D->Append(Knot);
      }
    }
    if (D->Count == 0)
      D->Append(static_cast<TPredicateScannerItemKnot*>(f_Arr->Items[0]));


    for(int i = 1; i <= D->Count - 1; i++)
    {
       NW = static_cast<TPredicateScannerItemKnot*>(D->Items[i]);
       if (Zadacha->TrackCreator->Count < f_Count )
       {
         CI = Zadacha->TrackCreator->CloneItem(AItem);
         CI->PushKnot(NW);
         AStack->InsertToFirst(CI);
       }
    }

    NW = static_cast<TPredicateScannerItemKnot*>(D->Items[0]);
    AItem->PushKnot(NW);
    AStack->InsertToFirst(AItem);

  }
  delete D;

 */







