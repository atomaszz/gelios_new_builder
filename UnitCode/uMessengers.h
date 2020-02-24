//---------------------------------------------------------------------------

#ifndef uMessengersH
#define uMessengersH
//---------------------------------------------------------------------------
typedef int (*TMsgFunc)(int Param1, int Param2);

class TMessangersItem
{
   public:
     int Message;
     TMsgFunc Func;
};

class TMessangers
{
   private:
     TList *f_List;
   public:
     TMessangers();
     ~TMessangers();
     bool RegistrMessage(int AMessage, TMsgFunc AFunc);
     int SendMess(int AMessage, int Param1, int Param2);

};
#endif

extern TMessangers* GMess;
