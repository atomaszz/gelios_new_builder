//---------------------------------------------------------------------------

#ifndef uDischargedMassivH
#define uDischargedMassivH
//---------------------------------------------------------------------------
class TDischargedMassivItem
{
   friend class TDischargedMassiv;
   private:
     int f_Col;
     int f_Row;
     Variant f_Value;
   public:
     TDischargedMassivItem();
};

class TDischargedMassiv
{
   private:
     Variant f_Def;
     TList *f_List;
     void FreeList();
     Variant __fastcall GetItems(int ARow, int ACol);
     void __fastcall SetItems(int ARow, int ACol, const Variant Value);
     TDischargedMassivItem* DoFind(int ARow, int ACol);
     void DeleteItem(TDischargedMassivItem* ADel);
     Variant __fastcall GetVal(int AIndex);
     void __fastcall SetVal(int AIndex, const Variant Value);
   public:
     TDischargedMassiv(const Variant ADef);
     ~TDischargedMassiv();
     int HiRow();
     int HiCol();
     int LoRow();
     int LoCol();
     void Clear();
     bool IsEmpty();
     Variant ActualValue(int ARow, int ACol, bool &Actual);
     double DoubleValue(int ARow, int ACol);
     double DoubleValue(int AIndex);
     __property Variant Items[int ARow][int ACol] = {read=GetItems, write=SetItems};
     __property Variant Val[int AIndex] = {read = GetVal, write=SetVal};

};

#endif
 