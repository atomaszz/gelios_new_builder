//---------------------------------------------------------------------------

#ifndef uGLSSmallFontsDefenceH
#define uGLSSmallFontsDefenceH
//---------------------------------------------------------------------------
class TGLSSmallFontsDefence
{
   private:
     TForm* FOwner;
     bool IsSmallFonts();
     void UpdateFont(Graphics::TFont *AFont);
     void UpdateFonts(TWinControl* AControl);
   public:
     TGLSSmallFontsDefence(TForm* AOwner);
     void Update();
};

#endif
