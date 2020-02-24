//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ufmViewPredicateTrackConstructorAuto.h"
#include "uCursorStorage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmViewPredicateTrackConstructorAuto *fmViewPredicateTrackConstructorAuto;
//---------------------------------------------------------------------------
__fastcall TfmViewPredicateTrackConstructorAuto::TfmViewPredicateTrackConstructorAuto(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructorAuto::acRunExecute(
      TObject *Sender)
{
  CheckPercent();
  CheckCount();
  MakeTrack();
  ShowTracks();
  TabControlChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfmViewPredicateTrackConstructorAuto::FormCreate(
      TObject *Sender)
{
  randomize();
  f_Arr = new TDynamicArray;
}
//---------------------------------------------------------------------------
void TfmViewPredicateTrackConstructorAuto::CheckPercent()
{
   f_Percent = StrToIntDef(edPercent->Text, 0);
   if (f_Percent < 0)
     f_Percent = 0;
   if (f_Percent > 100)
     f_Percent = 100;
   edPercent->Text = IntToStr(f_Percent);
}

void TfmViewPredicateTrackConstructorAuto::CheckCount()
{
   f_Count = StrToIntDef(edCount->Text, 1000);
   if (f_Count < 0)
     f_Count = 1;
   edCount->Text = IntToStr(f_Count);
}


bool TfmViewPredicateTrackConstructorAuto::CheckRnd()
{
   int r = random(100);
   return (r <= f_Percent);
}

void TfmViewPredicateTrackConstructorAuto::DoMakeTrack(
  TPredicateTrackCreatorItem* AItem, TDynamicArray *AStack)
{
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
}

bool TfmViewPredicateTrackConstructorAuto::DebugCheck()
{
  int cnt;
  TPredicateTrackCreatorItem *Item, *Item2;
  for(int i = 0; i <=  Zadacha->TrackCreator->Count - 1; i++)
  {
    Item = Zadacha->TrackCreator->Items[i];
    for(int j = i+1; j <=  Zadacha->TrackCreator->Count - 1; j++)
    {
      Item2 = Zadacha->TrackCreator->Items[j];
      if (Item->Count == Item2->Count)
      {
         int pos = 0;
         cnt = Item->Count;
         for(int k = 0; k <= cnt - 1; k++)
         if(Item->Items[k] == Item2->Items[k])
           pos++;
         if (pos == cnt)
           return true;

      }
    }
  }
  return false;
}


void TfmViewPredicateTrackConstructorAuto::MakeTrack()
{

   TPredicateTrackCreatorItem* P;
   ShowCursorStorage();
   Zadacha->TrackCreator->ClearTrack();
   P = Zadacha->TrackCreator->CreateItem();
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(P);
   P = static_cast<TPredicateTrackCreatorItem*>(m_Stack->Pop());
   while(P)
   {
     DoMakeTrack(P, m_Stack);
     P = static_cast<TPredicateTrackCreatorItem*>(m_Stack->Pop());
   }
   delete m_Stack;
   HideCursorStorage();
}

void __fastcall TfmViewPredicateTrackConstructorAuto::FormDestroy(
      TObject *Sender)
{
  delete f_Arr;
}
//---------------------------------------------------------------------------

void TfmViewPredicateTrackConstructorAuto::ShowTracks()
{
   TPredicateTrackCreatorItem* Item;
   ShowCursorStorage();
   TabControl->Tabs->Clear();
   for(int i = 0; i <= Zadacha->TrackCreator->Count - 1; i++)
   {
     Item = Zadacha->TrackCreator->Items[i];
     TabControl->Tabs->AddObject(IntToStr(i+1), reinterpret_cast<TObject*>(Item));
   }
   HideCursorStorage();
}

void __fastcall TfmViewPredicateTrackConstructorAuto::TabControlChange(
      TObject *Sender)
{
   TPredicateTrackCreatorItem* Item;
   Item = reinterpret_cast<TPredicateTrackCreatorItem*>(TabControl->Tabs->Objects[TabControl->TabIndex]);
   if (Item)
     REPredicate->Text = Item->Text;
   else
     REPredicate->Text = "";
       
}
//---------------------------------------------------------------------------




void __fastcall TfmViewPredicateTrackConstructorAuto::acOkExecute(
      TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructorAuto::acCancelExecute(
      TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfmViewPredicateTrackConstructorAuto::acOkUpdate(
      TObject *Sender)
{
  dynamic_cast<TAction*>(Sender)->Enabled = REPredicate->Text.Length() > 0;
}
//---------------------------------------------------------------------------


