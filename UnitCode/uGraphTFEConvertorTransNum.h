//---------------------------------------------------------------------------
#include "uPredicateNumGenerator.h"
#include "uGraphTFEConvertor.h"

#ifndef uGraphTFEConvertorTransNumH
#define uGraphTFEConvertorTransNumH
//---------------------------------------------------------------------------
class TGraphTFEConvertorTransNumItem
{
   private:
     int f_ID;
     int f_OldID;
     int f_Prefix;
   public:
     TGraphTFEConvertorTransNumItem(){f_ID = 0; f_OldID = 0; f_Prefix = 0;}
     __property int ID = {read = f_ID, write = f_ID};
     __property int OldID = {read = f_OldID, write = f_OldID};
     __property int Prefix = {read = f_Prefix, write = f_Prefix};
};

class TGraphTFEConvertorTransNumTFS
{
   private:
     TList* f_ListItem;
     AnsiString f_Name;
     int f_NumAlt;
     int f_ParentID;
     int f_ParentIDReal;
     void FreeList();
     int __fastcall GetItemCount();
     TGraphTFEConvertorTransNumItem* __fastcall GetItems(int AIndex);
   public:
     TGraphTFEConvertorTransNumTFS();
     ~TGraphTFEConvertorTransNumTFS();
     TGraphTFEConvertorTransNumItem* AddItem(int AId, int AOldId, int APrefix);
     __property AnsiString Name = {read = f_Name, write = f_Name};
     __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};
     __property int ParentID = {read = f_ParentID, write = f_ParentID};
     __property int ParentIDReal = {read = f_ParentIDReal, write = f_ParentIDReal};

     __property int ItemCount = {read = GetItemCount};
     __property TGraphTFEConvertorTransNumItem* Items[int AIndex] = {read = GetItems};


};

class TGraphTFEConvertorTransNum
{
   private:
     TList* f_List;
     TPredicateNumGenerator* f_NGen;
     void FreeList();
     int GetPrefix(TGraphTFEConvertorItem* AItem);
     int GetParentID(TGraphTFEConvertorItem* AItem, int APrefix);
     int GetPrefixForItem(int ANum);
     AnsiString DoMake(TGraphTFEConvertorTransNumTFS* AItem);
     AnsiString ListIDFromItem(TGraphTFEConvertorTransNumTFS* AItem);
   public:
     TGraphTFEConvertorTransNum();
     ~TGraphTFEConvertorTransNum();
     void AddGTItem(TGraphTFEConvertorItem* AItem);
     AnsiString Make();

};

#endif
