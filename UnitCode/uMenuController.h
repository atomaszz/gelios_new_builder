//---------------------------------------------------------------------------

#ifndef uMenuControllerH
#define uMenuControllerH
//---------------------------------------------------------------------------
class TMenuController
{
    private:
      TList* f_List;
      void FreeList();
    public:
       TMenuController();
      ~TMenuController();
      void AddMenu(TMenuItem *Item);
      void Clear();
};
#endif
