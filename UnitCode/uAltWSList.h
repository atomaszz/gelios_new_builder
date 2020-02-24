//---------------------------------------------------------------------------

#ifndef uAltWSListH
#define uAltWSListH
#include "uBaseWorkShape.h"
//---------------------------------------------------------------------------
class TAltWSList
{
   private:
     TList *f_List;
     TBaseWorkShape* __fastcall GetItem(int AIndex);
     int __fastcall GetCount();
   public:
     TAltWSList();
     ~TAltWSList();
     void Add(TBaseWorkShape* AWs);
     void Clear();
     bool Find(TBaseWorkShape* AWs);
     __property TBaseWorkShape*  Items[int AIndex] = { read =  GetItem};
     __property int Count =  {read = GetCount};
};
#endif
