//---------------------------------------------------------------------------

#ifndef uAltSelectorH
#define uAltSelectorH
#include "uBaseWorkShape.h"
#include "uListShape.h"
//--------------------------------------------------------------------------

class TAltSelectorItem
{
   private:
     int f_Num;
     int f_ID;
     int f_ParentShapeID;
   public:
     TAltSelectorItem(int AID, int ANum, int AParentShapeID);
     __property int Num = {read = f_Num};
     __property int ID = {read = f_ID};
     __property int ParentShapeID = {read = f_ParentShapeID};

};


class TAltSelector
{
   private:
     TList* f_List;
     TList* f_FinderList;
     int f_Id;
     int f_pos;
     void FreeList();
   public:
     TAltSelector();
     ~TAltSelector();
     int AddAltItem(int AID);
     TAltSelectorItem* CreateNewAlternateID(int AParentShapeID, int AStartNum = 0);
     TAltSelectorItem* CreateNewAlternateID2(int AID,  int AParentShapeID, int ANum);
     bool DeleteAltItem(int AID, int ANum);
     TAltSelectorItem* FindFirst(int AID, int AParentShapeID);
     TAltSelectorItem* FindNext();
     void ClearAll();
};



#endif
