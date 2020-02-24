//---------------------------------------------------------------------------

#ifndef uAltInfoH
#define uAltInfoH
//---------------------------------------------------------------------------
/*
    int ID;
    int Num;
    TNodeMain* NodeStart;
    TNodeMain* NodeEnd;
    TNodeAlt();
*/
class TNodeMain;
class TAltInfo;
class TAltInfoItem
{
  friend  TAltInfo;
  private:
    int f_Id;
    int f_Num;
    int f_ParentShapeId;
    TNodeMain* f_NodeStart;
    TNodeMain* f_NodeEnd;
    bool f_Main;
  public:
    TAltInfoItem();
    __property int ID = {read = f_Id};
    __property int Num = {read = f_Num};
    __property int ParentShapeId = {read = f_ParentShapeId};
    __property TNodeMain* NodeStart = {read = f_NodeStart, write = f_NodeStart};
    __property TNodeMain* NodeEnd = {read = f_NodeEnd, write = f_NodeEnd};
    __property bool Main = {read = f_Main, write = f_Main};
};

class TAltInfo
{
   private:
     TList *f_List;
     void FreeList();
     int __fastcall GetItemCount();
     TAltInfoItem* __fastcall GetItem(int AIndex);
     TAltInfoItem* FindItem(int AId, int ANum, int AParentShapeId);
   public:
     TAltInfo();
     ~TAltInfo();
     void Clear();
     TAltInfoItem* AddAltIfo(int AId, int ANum, int AParentShapeId, TNodeMain* ANodeStart, TNodeMain* ANodeEnd);
     __property int ItemCount = {read = GetItemCount};
     __property TAltInfoItem* Item[int AIndex] = {read = GetItem};

};
#endif
