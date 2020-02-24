//---------------------------------------------------------------------------

#ifndef uOgrSovmArrayH
#define uOgrSovmArrayH
#include "uDynamicArray.h"
#include "uBaseWorkShape.h"
//---------------------------------------------------------------------------
class TOgrSovmArray
{
  private:
    void *FCheckObj;
    bool FCheck;

    TDynamicArray* f_Array;
  public:
    TOgrSovmArray();
    ~TOgrSovmArray();
    inline void Clear() { f_Array->Clear(); }
    bool AddOgrSovm(TBaseWorkShape* ATFS);
    bool IsContainsKnot(int ATFE1, int ATFE2, int ATFE3);
    bool IsContainsTFS(TBaseWorkShape* ATFS);
    void SetCheckObj(void *P);
    inline void CheckObj(void *P) { if (FCheckObj == P) FCheck = true; }
    inline bool IsCheckObj() {return FCheck;}



};
#endif
 