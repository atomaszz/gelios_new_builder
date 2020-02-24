//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uClipPath.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void TClipPath::ClearRgn()
{
   int i;
   HRGN r;
   for (i = 0; i<=F_Rgn->Count - 1; i++)
   {
      r = (HRGN)(F_Rgn->Items[i]);
      DeleteObject(r);
   }
   F_Rgn->Clear();

}

TClipPath::TClipPath()
{
   F_Rects = new TList;
   F_Rgn = new TList;
}

TClipPath::~TClipPath()
{
   Clear();
   ClearRgn();
   delete F_Rects;
   delete F_Rgn;
}

void  TClipPath::Clear()
{
   int i;
   TRect* R;
   for (i=0; i<=F_Rects->Count-1 ;i++)
   {
     R = static_cast<TRect*>(F_Rects->Items[i]);
     delete R;
   }
   F_Rects->Clear();
}

void TClipPath::Add(TRect Rect, int Offs)
{
   TRect* R = new TRect;
   (*R) = Rect;
   if (Offs)
   {
     (*R).Left -=Offs;
     (*R).Top -=Offs;
     (*R).Right +=Offs;
     (*R).Bottom +=Offs;
   }
   F_Rects->Add(R);
}

HRGN TClipPath::GetCliptRgn()
{
   int i;
   TRect* R;
   HRGN r = 0;
   if (F_Rects->Count == 0) return r;
   ClearRgn();
   for (i = 0; i<=F_Rects->Count - 1; i++  )
   {
       R = static_cast<TRect*>(F_Rects->Items[i]); 
       r = CreateRectRgn(R->Left, R->Top, R->Right, R->Bottom);
       F_Rgn->Add((void*)r);
   }
   if (F_Rgn->Count > 0)
   {
     r = (HRGN)F_Rgn->Items[0];
     for (i = 1; i<=F_Rgn->Count - 1; i++  )
     {
        if ( CombineRgn( r, r, ((HRGN)F_Rgn->Items[i]), RGN_OR)  == 0)
         ShowMessage("Песец");
     }
   }
   return r;
}
