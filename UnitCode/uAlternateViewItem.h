//---------------------------------------------------------------------------

#ifndef uAlternateViewItemH
#define uAlternateViewItemH
#include "uBaseShape.h"
#include "uBaseWorkShape.h"
#include "uDynamicArray.h"


//---------------------------------------------------------------------------
class TAlternateViewItemTFS;
class TAlternateViewItemTFE;
class TMainTreeList;
class TAlternateViewItem
{
   private:
     TList * f_List;
     TBaseWorkShape* f_WSStart;
     TBaseWorkShape* f_WSEnd;
     TMainTreeList* f_MainTreeList;
     bool f_Fixed;
     TAlternateViewItemTFE* f_ParentTFE;
     TAlternateViewItem* f_Parent;
     void FreeList();
     int __fastcall GetItemCount();
     TAlternateViewItemTFS* __fastcall GetItemTFS(int AIndex);
   public:
     TDynamicArray *ArrayChild;
     TAlternateViewItem();
     ~TAlternateViewItem();
     TAlternateViewItemTFS* AddItemTFS(TBaseWorkShape* ABaseWorkShape, bool ACheck);
     void SetFixedTFE(TBaseShape *ABaseShape, bool AFixed);

     __property int ItemCount = {read = GetItemCount};
     __property TAlternateViewItemTFS* ItemTFS[int AIndex] = {read = GetItemTFS};
     __property TBaseWorkShape* WSStart = {read = f_WSStart, write = f_WSStart};
     __property TBaseWorkShape* WSEnd = {read = f_WSEnd, write= f_WSEnd};
     __property TMainTreeList* MainTreeList = {read = f_MainTreeList, write= f_MainTreeList};
     __property bool Fixed = {read =f_Fixed, write = f_Fixed};
     __property TAlternateViewItemTFE* ParentTFE = {read = f_ParentTFE, write = f_ParentTFE};
     __property TAlternateViewItem* Parent = {read = f_Parent, write = f_Parent};

};


class TAlternateViewItemTFS
{
   private:
     TList * f_List;
     TBaseWorkShape *f_BaseWorkShape;
     bool f_Check;
     void FreeList();
     int __fastcall GetItemCount();
     TAlternateViewItemTFE* __fastcall GetItemTFE(int AIndex);
   public:
     TAlternateViewItemTFS(TBaseWorkShape* ABaseWorkShape);
     ~TAlternateViewItemTFS();
     __property TBaseWorkShape* BaseWorkShape = {read = f_BaseWorkShape};
     __property int ItemCount = {read = GetItemCount};
     __property TAlternateViewItemTFE* ItemTFE[int AIndex] = {read = GetItemTFE};
     __property bool Check = {read = f_Check, write = f_Check};

};


class TAlternateViewItemTFE
{
   private:
     TBaseShape* f_BaseShape;
     TAlternateViewItem* f_NextItem;
     bool f_Fixed;
   public:
     TAlternateViewItemTFE(TBaseShape* ABaseShape);
     ~TAlternateViewItemTFE();
     __property TAlternateViewItem* NextItem = {read = f_NextItem, write = f_NextItem};
     __property TBaseShape* BaseShape = {read = f_BaseShape};
     __property bool Fixed = {read = f_Fixed, write = f_Fixed};

};

#endif
