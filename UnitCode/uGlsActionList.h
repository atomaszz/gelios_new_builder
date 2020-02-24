//---------------------------------------------------------------------------

#ifndef uGlsActionListH
#define uGlsActionListH
//---------------------------------------------------------------------------
class TGlsActionListItem
{
   private:
     bool f_Ctrl;
     bool f_Alt;
     bool f_Shift;
     bool f_SubMenu;
     AnsiString f_SCut;
     AnsiString f_ActName;
     AnsiString f_ActHint;
     AnsiString f_ActCaption;
     TAction* f_Action;
   public:
     TGlsActionListItem();
     __property AnsiString SCut = {read = f_SCut,  write = f_SCut};
     __property bool Ctrl  = {read = f_Ctrl, write = f_Ctrl};
     __property bool Alt = {read = f_Alt, write = f_Alt};
     __property bool Shift = {read = f_Shift, write = f_Shift};
     __property bool SubMenu = {read = f_SubMenu, write = f_SubMenu};
     __property AnsiString ActName = {read = f_ActName , write = f_ActName};
     __property AnsiString ActCaption = {read = f_ActCaption , write = f_ActCaption};
     __property AnsiString ActHint = {read = f_ActHint , write = f_ActHint};
     __property TAction* Action = {read = f_Action, write = f_Action};
};

class TGlsActionList
{
   private:
     TList *f_List;
     void FreeList();
     int __fastcall GetCount();
     TGlsActionListItem* __fastcall GetItems(int AIndex);
   public:
     TGlsActionList();
     ~TGlsActionList();
     void FillCharList(TStrings* AList);
     TGlsActionListItem* CreateActionItem(AnsiString AName);
     TGlsActionListItem* FindActionItem(AnsiString AName);
     TGlsActionListItem* FindActionItemByCaption(AnsiString ACaption);
     __property int Count = {read = GetCount};
     __property TGlsActionListItem* Items[int AIndex] = {read = GetItems};
};

#endif
