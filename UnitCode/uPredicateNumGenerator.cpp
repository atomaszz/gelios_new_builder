//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicateNumGenerator.h"
#include "uPredicateTFSConvertor.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TPredicateNumGenerator::TPredicateNumGenerator()
{
   f_CurrentNum = 0;
}

void TPredicateNumGenerator::InitNum(int ACurr)
{
   f_CurrentNum = ACurr;
}

int TPredicateNumGenerator::NextNum()
{
   f_CurrentNum++;
   return f_CurrentNum;
}

int TPredicateNumGenerator::NextLowNum()
{
   f_CurrentNum--;
   return f_CurrentNum;
}


