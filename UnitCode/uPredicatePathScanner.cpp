//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicatePathScanner.h"
#include "uDynamicArray.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool TPredicatePathScanner::IsContainChar(char AChar)
{
   int dl = strlen(f_Simv);
   for(int i = 0; i <= dl - 1; i++)
   {
      if (f_Simv[i] == AChar)
        return true;
   }
   return false;
}


void TPredicatePathScanner::InitScanner(bool *AProp, ...)
{
   memset(f_Simv, 0, 256);
   f_Prop = (*AProp);
   va_list ap;
   char arg;
   va_start(ap, AProp);
   int i = 0;
   while ((arg = va_arg(ap, char)) != 0)
   {
      f_Simv[i] = arg;
      i++;
   }
   va_end(ap);
}


bool TPredicatePathScanner::Eof()
{
   return f_Pos >= f_Len;
}


int TPredicatePathScanner::ScanItem()
{
   bool m_ct, cont;
   memset(f_Scan, 0, 256);
   cont = true;
   while(cont)
   {
      if (f_Pos >= f_Len)
        return 0;
      m_ct = IsContainChar(f_Str[f_Pos]);
      if (f_Prop && !m_ct)
      {
        if (strlen(f_Scan) > 255)
          return -1;
        strncat(f_Scan, &(f_Str[f_Pos]), 1);
        return true;
      }

      if (!f_Prop && m_ct)
         return true;

      if (!f_Prop && !m_ct)
      {
        if (strlen(f_Scan) > 255)
          return -1;
        strncat(f_Scan, &(f_Str[f_Pos]), 1);
      }
      f_Pos++;
   }
   return 1;
}


int TPredicatePathScanner::ScanComment()
{
   bool mp = false;
   InitScanner(&mp, '\n', NULL);
   return ScanItem();
}

char TPredicatePathScanner::LastScanChar()
{
   return f_Str[f_Pos];
}


int TPredicatePathScanner::DoScanBranch()
{
  int m_ID, m_Num;
  bool mp = false;
  TDynamicArray *D = new TDynamicArray;
  InitScanner(&mp, ',', '\n',  NULL);
  IncPos();
  int res = ScanItem();
  if (res > 0)
  {
    if (IsDigit(f_Scan))
    {
      m_ID = atoi(f_Scan);
      InitScanner(&mp, ',', '\n',  NULL);
      IncPos();
      res = ScanItem();
      if(res > 0)
      {
        if (IsDigit(f_Scan))
        {
          m_Num = atoi(f_Scan);
          InitScanner(&mp, '[', '\n',  NULL);
          IncPos();
          res = ScanItem();
          if (res > 0)
          {
            IncPos();
            while(res > 0)
            {
              InitScanner(&mp, ',', ']', '\n',  NULL);
              res = ScanItem();
              if (res > 0)
              {
                LRTrim(f_Scan);
                if (IsDigit(f_Scan))
                  D->Append((void*)atoi(f_Scan));
                else
                  res = -6;
                if (  (res >  0) && (LastScanChar() == ']') )
                {
                  IncPos();
                  break;
                }
              }
              else
                break;
              IncPos();
            }
            if (res != -6)
            {
              InitScanner(&mp, '.', '\n',  NULL);
              res = ScanItem();
              if (res > 0)
              {
                LRTrim(f_Scan);
                if ( (f_Scan[0] == ')') &&  strlen(f_Scan) == 1)
                {
                   res = 1;
                   IncPos();
                }
                else
                  res = -7;
              }
            }
          }
          else
            res = -5;
        }
        else
          res = -4;
      }
      else
        res = -3;
    }
    else
      res = -2;
  }
  if ( (res > 0) && ( D->Count > 0 ) )
  {
    TPredicatePathNode* PN = f_Dest->CreatePathNode(NULL);
    PN->ID = m_ID;
    PN->NumAlt = m_Num;
    for(int i = 0; i <= D->Count - 1; i++)
    {
       TPredicatePathNodeItem* PI = PN->CreateItem();
       PI->BlockID = int(D->Items[i]);
    }

  }
  delete D;
  return res;
}


int TPredicatePathScanner::ScanBranch()
{
   bool mp = false;
   InitScanner(&mp, '(', NULL);
   int res = ScanItem();
   if (res > 0)
   {
     if (strcmp(f_Scan, "vector") == 0 )
       res = DoScanBranch();
     else
       res = -1;
   }
   return res;
}



bool TPredicatePathScanner::Scan(char *AStr, TPredicatePathItem *ADest)
{
   bool mp;
   int state;
   Error = "";
   f_Pos = 0;
   f_Str = AStr;
   f_Len = strlen(f_Str);
   f_Dest = ADest;
   f_Dest->Clear();
   while (!Eof())
   {
     state = 0;
     mp = true;
     InitScanner(&mp, ' ', char(9), '\r', '\n', NULL);
     if (ScanItem())
     {
       if(f_Scan[0] == '%')
         state = 1;
       else if(isalpha(f_Scan[0]))
         state = 2;
       else
         state = -6;



       switch (state)
       {
         case 1:
           state = ScanComment();
           break;
         case 2:
           state = ScanBranch();
           break;
       }
     }
     if (state <= 0)
     {
       if (state < 0)
         Error = "Ошибка интерпретации!" ;
       break;
     }
  }
  return Error == "";
}

