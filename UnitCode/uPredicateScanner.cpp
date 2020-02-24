//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPredicateScanner.h"
#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
AnsiString TPredicateScannerItemKnot::ItemName()
{
   AnsiString Knot, Res, Ls;
   switch (f_TypeKnot)
   {
     case 1:
     {
       Knot = "rab_oper";
       break;
     }
     case 2:
     {
        Knot = "rab_oper_par_AND";
        break;
     }
     case 3:
     {
        Knot = "rab_oper_par_OR";
        break;
     }

     case 4:
     {
        Knot = "diagn_control_rab";
        break;
     }
     case 5:
     {
        Knot = "diagn_func_coltrol";
        break;
     }
     case 6:
     {
        Knot = "rasvilka";
        break;
     }

     case 7:
     {
        Knot = "proverka_if";
        break;
     }

     case 8:
     {
        Knot = "while_do_control_rab";
        break;
     }

     case 9:
     {
        Knot = "do_while_do_control_rab";
        break;
     }

     case 10:
     {
        Knot = "do_while_do_control_func";
        break;
     }

     case 11:
     {
        Knot = "proverka_uslovia";
        break;
     }

     case 13:
     {
        Knot = "rab_oper_posl";
        break;
     }

     default:
     {
        Knot = "unknown";
        break;
     }
   }
   Ls = "[";
   if (f_TFE_ID1 != 0)
     Ls = Ls + IntToStr(f_TFE_ID1);
   if (f_TFE_ID2 != 0)
     Ls = Ls + ", " + IntToStr(f_TFE_ID2);
   if (f_TFE_ID3 != 0)
     Ls = Ls + ", " + IntToStr(f_TFE_ID3);
   Ls = Ls + "]";

   Res = "tfs("+ IntToStr(f_ParentID) + ", " + IntToStr(f_NumAlt) + ", " + Knot + ", " + Ls + ").";
   return Res;
}


TPredicateScanner::TPredicateScanner()
{
  f_ListKnot = new TList;
}

TPredicateScanner::~TPredicateScanner()
{
  FreeListKnot();
  delete f_ListKnot;
}

void TPredicateScanner::FreeListKnot()
{
   TPredicateScannerItemKnot* Tmp;
   for (int i = f_ListKnot->Count - 1; i>=0; i--)
   {
      Tmp = static_cast<TPredicateScannerItemKnot*>(f_ListKnot->Items[i]);
      delete Tmp;
   }
   f_ListKnot->Clear();
}

int __fastcall TPredicateScanner::GetCountKnot()
{
   return f_ListKnot->Count;
}

TPredicateScannerItemKnot* __fastcall TPredicateScanner::GetItemsKnot(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListKnot->Count - 1)
     return static_cast<TPredicateScannerItemKnot*>(f_ListKnot->Items[AIndex]);
   else
     return NULL;
}



void TPredicateScanner::InitScanner(bool *AProp, ...)
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

bool TPredicateScanner::IsContainChar(char AChar)
{
   int dl = strlen(f_Simv);
   for(int i = 0; i <= dl - 1; i++)
   {
      if (f_Simv[i] == AChar)
        return true;
   }
   return false;
}



int TPredicateScanner::ScanItem()
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

bool TPredicateScanner::Eof()
{
   return f_Pos >= f_Len;
}

int TPredicateScanner::GetTypePredicate(char *AStr)
{
   LRTrim(AStr);
   if (strcmp(AStr, "rab_oper") == 0 )
     return 1;

   if (strcmp(AStr, "rab_oper_posl") == 0 )
     return 13;

   if (strcmp(AStr, "rab_oper_par_AND") == 0 )
     return 2;

   if (strcmp(AStr, "rab_oper_par_OR") == 0 )
     return 3;

   if (strcmp(AStr, "diagn_control_rab") == 0 )
     return 4;

   if (strcmp(AStr, "diagn_func_coltrol") == 0 )
     return 5;

   if (strcmp(AStr, "rasvilka") == 0 )
     return 6;

   if (strcmp(AStr, "proverka_if") == 0 )
     return 7;

   if (strcmp(AStr, "while_do_control_rab") == 0 )
     return 8;

   if (strcmp(AStr, "do_while_do_control_rab") == 0 )
     return 9;

   if (strcmp(AStr, "do_while_do_control_func") == 0 )
     return 10;

   if (strcmp(AStr, "proverka_uslovia") == 0 )
     return 11;

   return 0;
}

int TPredicateScanner::DoScanListID(int AType, int &AId1, int &AId2, int &AId3)
{
   AId1 = 0;
   AId2 = 0;
   AId3 = 0;
   int k;
   switch(AType)
   {
      case 1:
        k = 1;
        break;
      case 2:
        k = 2;
        break;
      case 3:
        k = 2;
        break;
      case 4:
        k = 2;
        break;
      case 5:
        k = 2;
        break;
      case 6:
        k = 3;
        break;
      case 7:
        k = 2;
        break;
      case 8:
        k = 2;
        break;
      case 9:
        k = 3;
        break;
      case 10:
        k = 3;
        break;
      case 11:
        k = 3;
        break;
      case 12:
        k = 1;
        break;
      case 13:
        k = 2;
        break;
      default:
        k = 0;
        break;
   }
   bool mp = false;
   InitScanner(&mp, '[', '\n',  NULL);
   int res = ScanItem();
   if (res > 0 )
   {
     IncPos();
     for(int i = 0;  i <= k - 1; i++)
     {
       InitScanner(&mp, ',', ']', '\n',  NULL);
       res = ScanItem();
       if (res > 0)
       {
         if (IsDigit(f_Scan))
         {
           if (i == 0)
             AId1 = atoi(f_Scan);
           if (i == 1)
             AId2 = atoi(f_Scan);
           if (i == 2)
             AId3 = atoi(f_Scan);
         }
         else
         {
           res = -2;
           break;
         }
       }
       else
         break;
       IncPos();
     }
   }
   return res;
}


int TPredicateScanner::DoScanKnot()
{
   bool mp = false;
   int id1, id2, id3;
   int m_parent, m_numalt, m_type;
   m_parent = m_numalt = m_type = 0;
   InitScanner(&mp, ',', '\n',  NULL);
   IncPos();
   int res = ScanItem();
   if (res > 0)
   {
      if (IsDigit(f_Scan))
      {
         m_parent = atoi(f_Scan);
         InitScanner(&mp, ',', '\n',  NULL);
         IncPos();
         res = ScanItem();
         if(res > 0)
         {
           if (IsDigit(f_Scan))
           {
             m_numalt = atoi(f_Scan);
             InitScanner(&mp, ',', '\n',  NULL);
             IncPos();
             res = ScanItem();
             if (res > 0)
             {
                m_type = GetTypePredicate(f_Scan);
                res = m_type;
                if (res > 0)
                {
                   res = DoScanListID(res, id1, id2, id3);
                   if (res > 0)
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
                           res = -5;
                      }
                   }
                }
                else
                  res = -4;
             }
           }
           else
             res = -3;
         }
      }
      else
        res = -3;
   }
   if (res > 0)
   {
     TPredicateScannerItemKnot* N  = CreateKnot();
     N->ParentID = m_parent;
     N->NumAlt = m_numalt;
     N->TypeKnot = m_type;
     N->TFE_ID1 = id1;
     N->TFE_ID2 = id2;
     N->TFE_ID3 = id3;
   }
   return res;
}

int TPredicateScanner::ScanComment()
{
   bool mp = false;
   InitScanner(&mp, '\n', NULL);
   return ScanItem();
}

int TPredicateScanner::ScanPredicate()
{
   bool mp = false;
   InitScanner(&mp, '(', NULL);
   int res = ScanItem();
   if (res > 0)
   {
     if (strcmp(f_Scan, "tfs") == 0 )
       res = DoScanKnot();
     else
       res = -1;
   }
   return res;
}


bool TPredicateScanner::Scan(char *AStr)
{
   bool mp;
   int state;
   Error = "";
   f_Pos = 0;
   f_Str = AStr;
   f_Len = strlen(f_Str);
   FreeListKnot();
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
           state = ScanPredicate();
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

TPredicateScannerItemKnot* TPredicateScanner::CreateKnot()
{
   TPredicateScannerItemKnot* Res  = new TPredicateScannerItemKnot;
   f_ListKnot->Add(Res);
   return Res;
}

