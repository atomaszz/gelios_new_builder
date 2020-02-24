//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGdiList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TGdiList::TGdiList()
{
   List = new TList;
   F_CurrIndex = 0;
}

//------------------------------------------------------------------------------
TGdiList::~TGdiList()
{
   delete List;
}

//------------------------------------------------------------------------------
void TGdiList::Add(int val)
{
   List->Add((void*)val);
}

//------------------------------------------------------------------------------
bool TGdiList::First(int &res)
{
   F_CurrIndex = 0;
   res = -1;
   bool rt = (List->Count > 0);
   if (rt)
      res = int(List->Items[F_CurrIndex]);
   return rt;
}

//------------------------------------------------------------------------------
bool TGdiList::Next(int &res)
{
   res = -1;
   bool rt = (List->Count > 0);
   if (rt)
   {
      F_CurrIndex++;
      rt = (F_CurrIndex <= List->Count -1);
      if (rt)
        res = int(List->Items[F_CurrIndex]);
   }
   return rt;
}

//------------------------------------------------------------------------------
bool TGdiList::Prior(int &res)
{
   res = -1;
   bool rt = (List->Count > 0);
   if (rt)
   {
      F_CurrIndex--;
      if (F_CurrIndex < 0) F_CurrIndex = 0;
      rt = (F_CurrIndex <= List->Count - 1);
      if (rt)
        res = int(List->Items[F_CurrIndex]);
   }
   return rt;
}

//------------------------------------------------------------------------------
bool TGdiList::Last(int &res)
{
   res = -1;
   bool rt = (List->Count > 0);
   if (rt)
   {
      F_CurrIndex = List->Count - 1;
      res = int(List->Items[F_CurrIndex]);
   }
   return rt;
}


//------------------------------------------------------------------------------
int TGdiList::Index()
{
   return F_CurrIndex;
}


//------------------------------------------------------------------------------
bool TGdiList::Delete(int pos)
{
   bool rt = (List->Count > 0) && (pos <= List->Count - 1);
   if (rt)
     List->Delete(pos);
   return rt;

}

//------------------------------------------------------------------------------
bool TGdiList::Eof()
{
   return (F_CurrIndex >= List->Count - 1);
}

//------------------------------------------------------------------------------
void TGdiList::Erase()
{
   List->Clear();
}



//---------------------------------------------------------------------------
bool DrawLine(TGdiList* GL, TCanvas *Canvas, TPoint Sp, int Step)
{
   int m_1, m_2, m_3, m_4;
   bool res;
   GL->Next(m_1);
   GL->Next(m_2);
   GL->Next(m_3);
   res = GL->Next(m_4);
   if (res)
   {
     m_1 = m_1*Step + Sp.x;
     m_2 = m_2*Step + Sp.y;
     m_3 = m_3*Step + Sp.x;
     m_4 = m_4*Step + Sp.y;

     Canvas->MoveTo(m_1, m_2);
     Canvas->LineTo(m_3, m_4);
   }
   return res;
}


bool DrawRect(TGdiList* GL, TCanvas *Canvas, TPoint Sp, int Step)
{
   int m_1, m_2, m_3, m_4;
   bool res;
   GL->Next(m_1);
   GL->Next(m_2);
   GL->Next(m_3);
   res =  GL->Next(m_4);
   if (res)
   {
       m_1 = m_1*Step + Sp.x;
       m_2 = m_2*Step + Sp.y;
       m_3 = m_3*Step + Sp.x;
       m_4 = m_4*Step + Sp.y;

      Canvas->Rectangle(m_1, m_2, m_3, m_4);
   }
   return res;
}


bool DrawEllipse(TGdiList* GL, TCanvas *Canvas, TPoint Sp, int Step)
{
   int m_1, m_2, m_3, m_4;
   bool res;
   GL->Next(m_1);
   GL->Next(m_2);
   GL->Next(m_3);
   res =  GL->Next(m_4);
   if (res)
   {
       m_1 = m_1*Step + Sp.x;
       m_2 = m_2*Step + Sp.y;
       m_3 = m_3*Step + Sp.x;
       m_4 = m_4*Step + Sp.y;

      Canvas->Ellipse(m_1, m_2, m_3, m_4);
   }
   return res;
}

bool DrawArc(TGdiList* GL, TCanvas *Canvas, TPoint Sp, int Step)
{
   int m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8;
   bool res;
   GL->Next(m_1);
   GL->Next(m_2);
   GL->Next(m_3);
   GL->Next(m_4);
   GL->Next(m_5);
   GL->Next(m_6);
   GL->Next(m_7);
   res = GL->Next(m_8);
   if (res)
   {
     m_1 = m_1*Step + Sp.x;
     m_2 = m_2*Step + Sp.y;
     m_3 = m_3*Step + Sp.x;
     m_4 = m_4*Step + Sp.y;
     m_5 = m_5*Step + Sp.x;
     m_6 = m_6*Step + Sp.y;
     m_7 = m_7*Step + Sp.x;
     m_8 = m_8*Step + Sp.y;
     Canvas->Arc(m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8);
   }
   return res;
}


bool DrawPolygon(TGdiList* GL, TCanvas *Canvas, TPoint Sp, int Step)
{
    int m_d, m_x, m_y, i, cnt;
    TPoint *point;
    bool ret = GL->Next(cnt);
    if (ret)
    {
       point = new TPoint[cnt];
       for (i = 0; i <= cnt - 1; i++ )
       {
          ret = GL->Next(m_x);
          ret = GL->Next(m_y);
          point[i].x = m_x*Step + Sp.x;
          point[i].y = m_y*Step + Sp.y;
       }
       if (ret)
         Canvas->Polygon(point, cnt - 1);
       delete []point;
    }
    return ret;

}



