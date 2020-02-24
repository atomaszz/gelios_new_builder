//---------------------------------------------------------------------------

#ifndef uGdiListH
#define uGdiListH
//---------------------------------------------------------------------------
class TGdiList
{
   private:
     int F_CurrIndex;
     TList *List;
   public:
     TGdiList();
     ~TGdiList();
     void Add(int val);

     bool First(int &res);
     bool Next(int &res);
     bool Prior(int &res);
     bool Last(int &res);
     int Index();
     bool Delete(int pos);
     bool Eof();
     void Erase();
};

bool DrawLine(TGdiList* G, TCanvas *Canvas, TPoint Sp,  int Step = 1);
bool DrawRect(TGdiList* G, TCanvas *Canvas, TPoint Sp, int Step = 1);
bool DrawEllipse(TGdiList* G, TCanvas *Canvas, TPoint Sp, int Step = 1);
bool DrawArc(TGdiList* G, TCanvas *Canvas, TPoint Sp, int Step = 1);
bool DrawPolygon(TGdiList* G, TCanvas *Canvas, TPoint Sp, int Step = 1);



#endif
