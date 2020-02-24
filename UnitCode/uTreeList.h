//---------------------------------------------------------------------------

#ifndef uTreeListH
#define uTreeListH
#include "uTreeListItem.h"
#include "uAltInfo.h"
//---------------------------------------------------------------------------
class TListNode;
class TTreeStackItem
{
   private:
     bool f_Fixed;
     int f_Level;
   public:
     TTreeStackItem(){f_Fixed = false; f_Level = -1;};
     __property bool Fixed = {read = f_Fixed, write = f_Fixed};
     __property int Level = {read = f_Level, write = f_Level};
};

class  TTreeStack
{
   private:
     TList* f_List;
     void FreeList();
   public:
     TTreeStack();
     ~TTreeStack();
     void AddToStack(int ALevel);
     void Clear();
     TTreeStackItem* GetLevel();
};

class TTreeList
{
   private:
     TMainTreeList* f_TreeList;
     TTreeStack* f_Stack;
     TAltInfo* f_AltInfo;
     void Init(int ALevel);
     TMainTreeList* FindByLevel(TMainTreeList* ABegin, int ALevel);
   public:
     void FillTreeFromList(TListNode* AListNode);
     void FillTreeFromList(TListNode* AListNode, int AParentShapeID, TBaseWorkShape *AStart, TBaseWorkShape *AEnd);
     TTreeList();
     ~TTreeList();
     __property TMainTreeList* MainTreeList = {read = f_TreeList};
};

#endif
