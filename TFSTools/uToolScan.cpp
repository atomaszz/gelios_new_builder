//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uToolScan.h"
#include "uToolConsts.h"
#include "uToolCommon.h"

//------------------------------------------------------------------------------
#pragma package(smart_init)
int SimType(char AChar)
{
  if (isdigit(AChar))
	return ST_DIGIT;
  if (AChar == 'T')
	return ST_TRANS;
  if (AChar == 'A')
	return ST_RO;
  if (AChar == 'B')
	return ST_FUNC;
  if (AChar == 'D')
	return ST_DIAG;
  if (AChar == 'C')
	return ST_START;
  if (AChar == 'F')
	return ST_FIN;
  if (AChar == 'H')
	return ST_BEGIN;
  if (AChar == 'K')
	return ST_END;
  if (AChar == '{')
	return ST_BRACE_BEGIN;
  if (AChar == '}')
	return ST_BRACE_END;
  if (AChar == '(')
	return ST_STAPLE_BEGIN;
  if (AChar == ')')
	return ST_STAPLE_END;
  if (AChar == ')')
	return ST_STAPLE_END;
  if (AChar == ',')
	return ST_SEP_0;
  if (AChar == ';')
	return ST_SEP_1;
  return ST_NONE;
}




void TToolScanSim::Init(const AnsiString AString)
{
   FIndex = 0;
   FString = AnsiUpperCase(AString);
   FLen = FString.Length();
}

char TToolScanSim::NextSim()
{
  int r;
  while (true)
  {
    FIndex++;
    if (FIndex > FLen)
      return 0;
    r = static_cast<int>(FString[FIndex]);
    if ( (r == 9) || (r == 32) || (r == 10) || (r == 13) )
      continue;
    else
      return FString[FIndex];
  }
}

//------------------------------------------------------------------------------
TToolScan::TToolScan()
{
  FList = new TList;
  FScan = new TToolScanSim;
}

TToolScan::~TToolScan()
{
  delete FScan;
  delete FList;
}


bool TToolScan::Parse(const AnsiString AText, TFsTable* ATable)
{
   char c;
   int c_typ;
   FErrorCode = 0;
   FScan->Init(AText);
   int state = 0;
   bool CanDigit = false;
   AnsiString D;
   TFsTableItemData Left, Right;
   while (true)
   {
	 if (FErrorCode > 0)
	   break;
	 c = FScan->NextSim();
	 if (c == 0)
	   break;
	 if (state == 9)
	 {
	   FErrorCode = 10;
	   continue;
	 }
	 c_typ = SimType(c);
	 if (state == 0)
	 {
	   if (c_typ == ST_BRACE_BEGIN)
		 state = 1;
	   else
		 FErrorCode = 1;
	   continue;
	 }

     if (state == 1)
     {
       if (c_typ == ST_STAPLE_BEGIN)
       {
         state = 2;
         D = "";
	   }
       else
         FErrorCode = 2;
       continue;
     }

     if (state == 2)
     {
       if (IsTfsAlpha(c_typ))
       {
         state = 3;
         if ((c_typ == ST_BEGIN) || (c_typ == ST_END))
         {
           state = 4;
           CanDigit = false;
         }
         Left.Type = c_typ;
       }
       else
         FErrorCode = 3;
       continue;
     }

	 if (state == 3)
     {
	   if (c_typ == ST_DIGIT)
	   {
		 state = 4;
		 D = c;
		 CanDigit = true;
	   }
       else
         FErrorCode = 4;
       continue;
     }

     if (state == 4) //число
     {
       if ((c_typ == ST_DIGIT) && CanDigit )
         D = D + c;
       else
       {
         if ( IsTfsSep(c_typ) )
           state = 5;
         else
           FErrorCode = 5;
       }
       continue;
     }

     if (state == 5)
     {
       if (IsTfsAlpha(c_typ))
       {
         state = 6;
         if ((c_typ == ST_BEGIN) || (c_typ == ST_END))
         {
           state = 7;
           CanDigit = false;
         }
         Left.Num = StrToIntDef(D, 0);
         Right.Type = c_typ;
       }
       else
         FErrorCode = 6;
       continue;
     }

     if (state == 6)
     {
       if (c_typ == ST_DIGIT)
       {
         state = 7;
         D = c;
         CanDigit = true;
       }
       else
         FErrorCode = 7;
       continue;
     }

     if (state == 7) //число
     {
       if ((c_typ == ST_DIGIT) && CanDigit )
         D = D + c;
       else
       {
         if ( c_typ == ST_STAPLE_END )
           state = 8;
         else
           FErrorCode = 8;
       }
       continue;
     }

     if (state == 8)
     {
	   Right.Num = StrToIntDef(D, 0);
       ATable->AddItem(Left, Right);

	   if (c_typ == ST_BRACE_END)
       {
          state = 9;
       }
       else
       {
         if ( IsTfsSep(c_typ) )
           state = 1;
         else
           FErrorCode = 9;
       }
       continue;
     }
   }
   return (FErrorCode == 0) && (state == 9);
}


//--------------------------------------------------------------
TToolScanSuperPos::TToolScanSuperPos()
{
   FItems = new TList;
   FScan = new TToolScanSim;
}

TToolScanSuperPos::~TToolScanSuperPos()
{
   FreeList();
   delete FItems;
   delete FScan;
}

void TToolScanSuperPos::Clear()
{
   FFuncSet = "";
   FreeList();
}

void TToolScanSuperPos::FreeList()
{
   TToolScanSuperPosItem* Item;
   for (int i = 0; i <= FItems->Count - 1; i++)
   {
	  Item = static_cast<TToolScanSuperPosItem*>(FItems->Items[i]);
	  delete Item;
   }
   FItems->Clear();
}

int __fastcall TToolScanSuperPos::GetCount()
{
   return FItems->Count;
}

TToolScanSuperPosItem* __fastcall TToolScanSuperPos::GetItems(int AIndex)
{
   if (AIndex >= 0 && AIndex <= FItems->Count - 1)
	 return static_cast<TToolScanSuperPosItem*>(FItems->Items[AIndex]);
   else
	 return NULL;
}

TToolScanSuperPosItem* TToolScanSuperPos::Find(int ANum)
{
   TToolScanSuperPosItem* Item;
   for (int i = 0; i <= FItems->Count - 1; i++)
   {
	  Item = static_cast<TToolScanSuperPosItem*>(FItems->Items[i]);
	  if (Item->Num == ANum)
		return Item;
   }
   return NULL;
}

void TToolScanSuperPos::Add(int ANum, const AnsiString AText)
{
  TToolScanSuperPosItem* Item = new TToolScanSuperPosItem;
  Item->Num = ANum;
  Item->Text = AText;
  FItems->Add(Item);
}

bool TToolScanSuperPos::Parse(const AnsiString AText)
{
   char c;
   int c_typ;
   int state = 0;
   bool isFs = false;
   bool isA = false;
   FErrorCode = 0;
   AnsiString D;
   TStringBuilder* SB = new TStringBuilder();
   bool CanDigit = false;
   FScan->Init(AText);
   Clear();
   while (true)
   {
	 if (FErrorCode > 0)
	   break;
	 c = FScan->NextSim();
	 if (c == 0)
	   break;
	 c_typ = SimType(c);
	 if (state == 0)
	 {
	   if (c_typ == ST_BRACE_BEGIN)
		 state = 1;
	   else if (c == 'F')
		 state = 2;
	   else if (c == 'A')
		 state = 3;
	   else
		 FErrorCode = 1;
	   continue;
	 }

	 if (state == 2)
	 {
	   if (c == 'S')
		 state = 4;
	   else
		 FErrorCode = 2;
	   continue;
	 }

	 if (state == 4)
	 {
	   if (c == ':')
		 state = 5;
	   else
		 FErrorCode = 3;
	   continue;
	 }

	 if (state == 5)
	 {
	   if (c_typ == ST_BRACE_BEGIN)
	   {
		 isFs = true;
		 state = 1;
       }
	   else
		 FErrorCode = 4;
	   continue;
	 }

	 if (state == 3)
	 {
	   if (c_typ == ST_DIGIT)
	   {
		 state = 6;
		 D = c;
	   }
	   else
		 FErrorCode = 5;
	   continue;
	 }

	 if (state == 6)
	 {
	   if (c_typ == ST_DIGIT)
		 D = D + c;
	   else if (c == ':')
		 state = 7;
	   else
		 FErrorCode = 6;
	   continue;
	 }

	 if (state == 7)
	 {
	   if (c_typ == ST_BRACE_BEGIN)
	   {
		 isA = true;
		 state = 1;
	   }
	   else
		 FErrorCode = 7;
	   continue;
	 }

	 if (state == 1)
	 {
	   if (!isA) isFs = true;
	   if (c_typ != ST_BRACE_END)
	   {
		 SB->Append("{");
		 SB->Append(WideChar(c));
		 state = 8;
	   }
	   else
	   {
		 state = 9;
		 goto bad;
	   }
	   continue;
	 }

	 if (state == 8)
	 {
	   if (c_typ != ST_BRACE_END)
		 SB->Append(WideChar(c));
	   else
	   {
		 SB->Append("}");
		 state = 9;
		 goto bad;
	   }
	   continue;
	 }

bad: if (state == 9)
	 {
	   if (isFs)
	   {
		 if (FFuncSet.Length() == 0)
		   FFuncSet = SB->ToString();
		 else
		   FErrorCode = 8;
	   }
	   if (isA)
	   {
		 AnsiString s = SB->ToString();
		 if (s.Length() > 0)
		 {
		   int Num = StrToIntDef(D, 0);
		   if (Num > 0)
		   {
			 TToolScanSuperPosItem* Item = Find(Num);
			 if (!Item)
			   Add(Num, s);
			 else
               FErrorCode = 9;
		   }
		 }
	   }
	   isFs = false;
	   isA = false;
	   state = 0;
	   SB->Clear();
	   continue;
	 }
   }
   delete SB;
   return (state == 0) && (FErrorCode == 0) && (FFuncSet.Length() > 0);
}


