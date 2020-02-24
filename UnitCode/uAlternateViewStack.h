//---------------------------------------------------------------------------

#ifndef uAlternateViewStackH
#define uAlternateViewStackH
//---------------------------------------------------------------------------
class  TAVStackItem
{
   private:
     TList *f_List;
   public:
     TAVStackItem();
     ~TAVStackItem();
};

class  TAVStack
{
   private:
     TList *f_List;
   public:
     TAVStack();
     ~TAVStack();
};

#endif
