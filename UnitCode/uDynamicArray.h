//---------------------------------------------------------------------------

#ifndef uDynamicArrayH
#define uDynamicArrayH
//---------------------------------------------------------------------------
class TDynamicArrayItem
{
   public:
     int Index;
     void *P;
     AnsiString Name;
     int Int_Value;
};

class TDynamicArray
{
   private:
     int f_PosStak;
     TList *f_List;
     void FreeList();
     void* __fastcall GetArray(int AIndex);
     void __fastcall SetArray(int AIndex, void *AValue);
     int __fastcall GetCount();
     void* __fastcall GetItems(int AIndex);
     void* __fastcall GetNamed(AnsiString AIndex);
     void __fastcall SetNamed(AnsiString AIndex, void *AValue);
     void* __fastcall GetInteger(int APos);
     void __fastcall SetInteger(int APos, void* AValue);
     TDynamicArrayItem* __fastcall GetPosition(int APos);
   public:
     TDynamicArray();
     ~TDynamicArray();
     void Clear();
     void Append(void* P);
     void InsertToFirst(void* P);
     void AppendNamed(AnsiString AName, void* P = NULL);
     bool DeleteNamed(AnsiString AName);
     void AppendInteger(int APos, void* AValue);
     bool DeleteInteger(int APos);
     bool Delete(void* P);
     void InitStack();
     void* Pop();
     TDynamicArrayItem* Find(void* P);
     TDynamicArrayItem* Last();
     int DeleteArray(TDynamicArray* AList);
     __property int Count = {read = GetCount};
     __property void* Array[int AIndex] = {read = GetArray, write = SetArray};
     __property void* Items[int AIndex] = {read = GetItems};
     __property void* Named[AnsiString AIndex] = {read = GetNamed, write  = SetNamed};
     __property void* Integer[int APos] = {read = GetInteger, write  = SetInteger};
     __property TDynamicArrayItem* Position[int APos] = {read = GetPosition};

};

#endif
