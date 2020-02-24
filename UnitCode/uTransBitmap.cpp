//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTransBitmap.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



TTransBitmap::TTransBitmap()
{
   F_BaseBmp = NULL;
//   F_Bmp = NULL;
   F_MoveBmp = NULL;
   F_ReturnBmp = NULL;
   F_AmountTrans = 80;
   F_BackColor = clRed;
   F_TransparentBkColor = false;
}

void TTransBitmap::FreeBaseBmp()
{
   if (F_BaseBmp)
   {
      F_BaseBmp->FreeImage();
      delete F_BaseBmp;
      F_BaseBmp = NULL;
   }
}


/*
void TTransBitmap::FreeBmp()
{
   if (!F_Bmp)
   {
      F_Bmp->FreeImage();
      delete F_Bmp;
      F_Bmp = NULL;
   }
}
*/

void TTransBitmap::FreeMoveBmp()
{
   if (F_MoveBmp)
   {
      F_MoveBmp->FreeImage();
      delete F_MoveBmp;
      F_MoveBmp = NULL;
   }
}

void TTransBitmap::FreeReturnBmp()
{
   if (F_ReturnBmp)
   {
      F_ReturnBmp->FreeImage();
      delete F_ReturnBmp;
      F_ReturnBmp = NULL;
   }
}


TTransBitmap::~TTransBitmap()
{
   FreeBaseBmp();
//   FreeBmp();
   FreeMoveBmp();
   FreeReturnBmp();
}

bool TTransBitmap::CompareColor(TRGBTriple Color1, TRGBTriple Color2)
{
   return ((Color1.rgbtRed == Color2.rgbtRed) && (Color1.rgbtGreen == Color2.rgbtGreen) && (Color1.rgbtBlue == Color2.rgbtBlue));
}

void __fastcall TTransBitmap::SetBaseBmp(Graphics::TBitmap* Value)
{
   FreeBaseBmp();
   F_BaseBmp = new Graphics::TBitmap;
   F_BaseBmp->Assign(Value);
}

void __fastcall TTransBitmap::SetMoveBmp(Graphics::TBitmap* Value)
{
   FreeMoveBmp();
   F_MoveBmp = new Graphics::TBitmap;
   F_MoveBmp->Assign(Value);

}


Graphics::TBitmap* TTransBitmap::Convert(int aX, int aY)
{
  int x, y, y1, y2, x1, x2;
  TRGBTriple  *ps, *pd;
  TRGBTriple rgb;
  double A1, A2;

  FreeReturnBmp();
  F_ReturnBmp = new Graphics::TBitmap;
  F_ReturnBmp->Assign(F_MoveBmp);


  F_BaseBmp->PixelFormat = pf24bit;
  F_ReturnBmp->PixelFormat = pf24bit;
  A1 = double(  F_AmountTrans / 255.0);
  A2 = 1 - A1;
  y1 = std::max(0, aY);
  x1 = std::max(0, aX);
  x2 = std::min(F_BaseBmp->Width - 1, aX + F_ReturnBmp->Width - 1);
  y2 = std::min(F_BaseBmp->Height - 1, aY + F_ReturnBmp->Height - 1);
  rgb.rgbtRed = int(BackColor & 0xFF);
  rgb.rgbtGreen = int(BackColor >> 8) & 0xFF;
  rgb.rgbtBlue =  int((BackColor >> 8) >> 8) & 0xFF;

  for ( y = y1 ; y <= y2  ; y ++)
  {
    ps = (TRGBTriple*)F_BaseBmp->ScanLine[y];
    pd = (TRGBTriple*)F_ReturnBmp->ScanLine[y - aY];
    ps+=x1;
    if (aX < 0)
      pd = pd + abs(aX);
    for(x= x1; x <= x2; x++)
    {
      if (!(F_TransparentBkColor && CompareColor(*pd, rgb)))
      {
         pd->rgbtBlue = byte(A1 * ps->rgbtBlue + A2 * pd->rgbtBlue);
         pd->rgbtGreen = byte(A1 * ps->rgbtGreen + A2 * pd->rgbtGreen);
         pd->rgbtRed = byte(A1 * ps->rgbtRed + A2 * pd->rgbtRed);
      }
      pd+=1;
      ps+=1;
    }
  }
  return F_ReturnBmp;
}

