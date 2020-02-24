//---------------------------------------------------------------------------

#ifndef uTransBitmapH
#define uTransBitmapH
//---------------------------------------------------------------------------
class TTransBitmap
{
   private:
     Graphics::TBitmap  *F_BaseBmp;
   //  Graphics::TBitmap  *F_Bmp;
     Graphics::TBitmap  *F_MoveBmp;
     Graphics::TBitmap  *F_ReturnBmp;
     byte F_AmountTrans;
     TColor F_BackColor;
     bool F_TransparentBkColor;
     void FreeBaseBmp();
//     void FreeBmp();
     void FreeMoveBmp();
     void FreeReturnBmp();
     void __fastcall SetBaseBmp(Graphics::TBitmap* Value);
     void __fastcall SetMoveBmp(Graphics::TBitmap* Value);
     bool CompareColor(TRGBTriple Color1, TRGBTriple Color2);
   public:
     TTransBitmap();
     ~TTransBitmap();
     Graphics::TBitmap* Convert(int aX, int aY);
     __property Graphics::TBitmap* BaseBmp = {write = SetBaseBmp};
     __property Graphics::TBitmap* MoveBmp = {write = SetMoveBmp};
     __property TColor BackColor = {read = F_BackColor, write = F_BackColor};
     __property bool TransparentBkColor = {read = F_TransparentBkColor, write = F_TransparentBkColor};
     __property byte AmountTrans = {read = F_AmountTrans, write = F_AmountTrans};



};
#endif
