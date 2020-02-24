//---------------------------------------------------------------------------

#ifndef uInvalidateListH
#define uInvalidateListH
#include "uBaseWorkShape.h"
//---------------------------------------------------------------------------
class TInvalidateList
{
   private:
     TList* f_List;
     int f_Width;
     int f_Heigth;
     TBaseWorkShape* __fastcall GetItem(int AIndex);
     int __fastcall GetCount();
   public:
     TInvalidateList();
     ~TInvalidateList();
     void Clear();
     void AddWorkShape(TBaseWorkShape* AShape);
     __property TBaseWorkShape*  Items[int AIndex] = { read =  GetItem};
     __property int Count = {read = GetCount};
     __property int Width = {read = f_Width, write = f_Width};
     __property int Heigth = {read = f_Heigth, write = f_Heigth};



};

#endif
