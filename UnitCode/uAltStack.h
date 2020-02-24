//---------------------------------------------------------------------------

#ifndef uAltStackH
#define uAltStackH
//---------------------------------------------------------------------------
class TAltStackItem
{
   private:
     int f_IdAlternative;
     int f_NumAlternative;
     int f_IdAlternativeParent;
     int f_NumAlternativeParent;
   public:
     TAltStackItem(int AIdAlternative, int ANumAlternative,  int AIdAlternativeParent,
        int ANumAlternativeParent);
     __property int IdAlternative = { read = f_IdAlternative , write = f_IdAlternative};
     __property int NumAlternative =  {read =  f_NumAlternative, write = f_NumAlternative};
     __property int IdAlternativeParent = { read = f_IdAlternativeParent, write = f_IdAlternativeParent};
     __property int NumAlternativeParent = { read = f_NumAlternativeParent, write = f_NumAlternativeParent};
};


class TAltStackController
{
   private:
     TList* f_List;
     TAltStackItem* f_CurrentItem;
     void FreeList();
     void DeleteLastLevel();
   public:
     TAltStackController();
     ~TAltStackController();
     TAltStackItem* Push(int AIdAlternative, int ANumAlternative,
       int AIdAlternativeParent,  int ANumAlternativeParent);
     TAltStackItem*  Pop();
     void ClearAll();
     __property TAltStackItem* CurrentItem = {read = f_CurrentItem};

};

#endif
