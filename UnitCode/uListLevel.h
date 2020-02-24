//---------------------------------------------------------------------------

#ifndef uListLevelH
#define uListLevelH
//---------------------------------------------------------------------------
class TLevelItem
{
   private:
     int f_IdParentShape;
     int f_X_offsSum, f_Y_offsSum;
   public:
     TLevelItem();
     __property int IdParentShape = {read = f_IdParentShape, write = f_IdParentShape};
     __property int X_offsSum = {read = f_X_offsSum, write = f_X_offsSum};
     __property int Y_offsSum = {read = f_Y_offsSum, write = f_Y_offsSum};

};

class TLevelController
{
   private:
     TList* f_List;
     TLevelItem* f_CurrentLevel;
     void FreeList();
     TLevelItem* FindLevel(int AIdParentShape);
     int __fastcall GetParentShapeID();
     void DeleteLastLevel();
   public:
     TLevelController();
     ~TLevelController();
     TLevelItem* Push(int AIdParentShape);
     TLevelItem* Pop();
     void ClearAll();
     __property TLevelItem* CurrentLevel = {read = f_CurrentLevel};
     __property int ParentShapeID = {read = GetParentShapeID};

};
#endif
