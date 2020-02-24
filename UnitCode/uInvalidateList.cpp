//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uInvalidateList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
/*
class TInvalidateList
{
   private:
     TList* f_List;
     TBaseWorkSshape* __fastcall GetItem(int AIndex);
   public:
     TInvalidateList();
     ~TInvalidateList();
     void Clear();
     void AddWorkShape(TBaseWorkSshape* AShape);
      __property TBaseWorkSshape*  Items[int AIndex] = { read =  GetItem};
      __property int Count = {read = GetCount};

};*/

TInvalidateList::TInvalidateList()
{
   f_List = new TList;
   f_Width = f_Heigth = 0;
}


TInvalidateList::~TInvalidateList()
{
   delete f_List;
}

void TInvalidateList::Clear()
{
   f_List->Clear();
}

int __fastcall TInvalidateList::GetCount()
{
   return (f_List->Count);
}

void TInvalidateList::AddWorkShape(TBaseWorkShape* AShape)
{
    TRect R;
    TRect Bounds = TRect(0, 0, f_Width, f_Heigth);
    TPoint P1, P2;
    TBaseWorkShape *Tmp;
    for (int i = 0; i <= f_List->Count - 1; i++)
    {
       Tmp = static_cast<TBaseWorkShape*>(f_List->Items[i]);
       if (Tmp == AShape) return;
    }
    R = AShape->GetFrameRectWithLines();
    P1 = TPoint(R.Left, R.Top);
    P2 = TPoint(R.Right, R.Bottom);
//    if (PtInRect(&Bounds, P1) || PtInRect(&Bounds, P2) )
    if ( (R.Top <= f_Heigth) || (R.Bottom <= f_Heigth) || (R.Left) )
       f_List->Add(AShape);
}

TBaseWorkShape* __fastcall TInvalidateList::GetItem(int AIndex)
{
    TBaseWorkShape* res = NULL;
    if ( (AIndex >= 0) && (AIndex <= f_List->Count - 1))
       res = static_cast<TBaseWorkShape*>(f_List->Items[AIndex]);
    return res;
}


