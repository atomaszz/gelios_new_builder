//---------------------------------------------------------------------------
#ifndef uPredicateNumGeneratorH
#define uPredicateNumGeneratorH

//---------------------------------------------------------------------------
class TPredicateNumGenerator
{
   private:
     int f_CurrentNum;
   public:
     TPredicateNumGenerator();
     int NextNum();
     void InitNum(int ACurr = 0);
     int NextLowNum();
};
#endif
