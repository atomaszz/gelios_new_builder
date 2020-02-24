//---------------------------------------------------------------------------

#ifndef uClipPathH
#define uClipPathH
//---------------------------------------------------------------------------
class TClipPath
{
   private:
     TList *F_Rects;
     TList *F_Rgn;
     void ClearRgn();
   public:
     TClipPath();
     ~TClipPath();
     void Clear();
     void Add(TRect Rect, int Offs = 0);
     HRGN GetCliptRgn();

};
#endif
