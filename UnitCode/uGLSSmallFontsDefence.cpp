//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGLSSmallFontsDefence.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

class  TShowFont: public TControl
{
   __published:
     __property Font;
};


TGLSSmallFontsDefence::TGLSSmallFontsDefence(TForm* AOwner)
{
   FOwner = AOwner;
}

void TGLSSmallFontsDefence::Update()
{
  if (!IsSmallFonts())
  {
    FOwner->Scaled = false;
    UpdateFonts(FOwner);
  }
}

bool TGLSSmallFontsDefence::IsSmallFonts()
{
   HDC DC = GetDC(0);;
   bool Result = (GetDeviceCaps(DC, LOGPIXELSX) == 96);
   ReleaseDC(0, DC);
   return  Result;
}

void TGLSSmallFontsDefence::UpdateFont(Graphics::TFont* AFont)
{
    if (CompareText(AFont->Name, "MS Sans Serif") == 0 )
      AFont->Name = "Arial";
}

void TGLSSmallFontsDefence::UpdateFonts(TWinControl* AControl)
{
  TWinControl *W;
  TShowFont* X = (TShowFont*)(dynamic_cast<TControl*>(AControl));
  UpdateFont(X->Font);
  for (int i = 0; i <= AControl->ControlCount - 1; i++)
  {
    X = (TShowFont*)AControl->Controls[i];
    UpdateFont(X->Font);
    W = dynamic_cast<TWinControl*>(AControl->Controls[i]);
    if (W)
      UpdateFonts(W);
  }
}

