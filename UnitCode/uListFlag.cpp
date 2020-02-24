//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uListFlag.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TFlag::TFlag()
{
//  F_Type = -1;
  F_Position = -1;
  F_Shape = NULL;
  F_Line = NULL;
  F_Flag = NULL;
}

/*
class TListFlag
{
   private:
      TList* List;
      void FreeList();
   public:
      TListFlag();
     ~TListFlag();
     void AddFlag(int AType, int APosition, TRectLine* ALine);
     bool DeleteFlag(void *);
     bool DeleteFlag(int APosition, TBaseShape* AShape);
     TFlagShape* GetFlag(int APosition, TBaseShape* AShape);
     TFlagShape* GetFlag(int AType);
     bool UpadteFlag(TFlagShape* AFlag);
}; */

TListFlag::TListFlag()
{
   List = new TList;
}


TListFlag::~TListFlag()
{
   FreeList();
   delete List;
}

/*
void TListFlag::AddFlag(int AType, int APosition, TRectLine* ALine, TBaseShape* AShape)
{
   TFlag* Member;
   Member = new TFlag;
   Member->Type = AType;
   Member->Position = APosition;
   Member->Line = ALine;
   Member->Shape = AShape;
   List->Add(Member);
} */

/*
bool TListFlag::UpadteFlag(TFlagShape* AFlag, int APosition)
{
   TFlag* Member;
   TBaseLine* MLine;
   int APos;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      MLine = Member->Flag->Owner;
      APos =  Member->Position;
      if ( (AFlag->Owner == MLine) && (APos == APosition) )
      {
        Member->Flag = AFlag;
        return true;
      }

   }
   return false;
*/


TFlag* TListFlag::AddFlag(TFlagShape* AFlag, TBaseShape* AShape, TRectLine* ALine, int APosition
              , bool &AFlagExits )
{
   TFlag* Member;
   TBaseLine* MLine;
   int APos;
   AFlagExits = true;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      if (Member->Flag == AFlag) return Member;
   }
   Member = new TFlag;
//   Member->Type = AType;
   Member->Position = APosition;
   Member->Shape = AShape;
   Member->Line = ALine;
   Member->Flag = AFlag;
   List->Add(Member);
   AFlagExits = false;
   return Member;
}


int __fastcall TListFlag::GetCount()
{
   return List->Count;
}

TFlag* __fastcall TListFlag::GetItem(int AIndex)
{
    TFlag* res = NULL;
    if ( (AIndex >= 0) && (AIndex <= List->Count - 1))
       res = static_cast<TFlag*>(List->Items[AIndex]);
    return res;
}
/*
bool TListFlag::DeleteFlag(int APosition, TBaseShape* AShape)
{
   TFlag* Member;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      if ( (Member->Position == APosition) && (Member->Shape == AShape) )
      {
         delete Member;
         Member = NULL;
         List->Delete(i);
         return true;
      }
   }
   return false;
}


bool TListFlag::DeleteFlagByType(int AType)
{
   bool res = false;
   TFlag* Member;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      if ( (Member->Type == AType) )
      {
         delete Member;
         Member = NULL;
         List->Delete(i);
         res = true;
      }
   }
   return res;
}
*/


TFlag* TListFlag::DeleteFlagByShape(TFlagShape* AFlag)
{
  TFlag *Member, *Res = NULL;
  for (int i = List->Count - 1 ; i>=0 ; i--)
  {
     Member = static_cast<TFlag*>(List->Items[i]);
     if (Member->Flag == AFlag)
     {
        Res = Member;
        delete Member;
        Member = NULL;
        List->Delete(i);
     }
  }
  return Res;

}

bool TListFlag::DeleteFlagByFlag(TFlag* AFlag)
{
  TFlag* Member;
  bool res = false;
  for (int i = List->Count - 1 ; i>=0 ; i--)
  {
     Member = static_cast<TFlag*>(List->Items[i]);
     if (Member == AFlag)
     {
        delete Member;
        Member = NULL;
        List->Delete(i);
        res = true;
     }
  }
  return res;
}

/*
TFlag* TListFlag::GetFlag(int APosition, TBaseShape* AShape)
{
   TFlag* Member;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      if ( (Member->Position == APosition) && (Member->Shape == AShape) )
      {
         return Member;
      }
   }
   return NULL;
}


TFlag* TListFlag::GetFlag(int AType)
{
   TFlag* Member;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      if ( (Member->Type == AType) )
      {
        return Member;
      }
   }
   return NULL;
}

bool TListFlag::UpadteFlag(TFlagShape* AFlag, int APosition)
{
   TFlag* Member;
   TBaseLine* MLine;
   int APos;
   for (int i = List->Count - 1 ; i>=0 ; i--)
   {
      Member = static_cast<TFlag*>(List->Items[i]);
      MLine = Member->Flag->Owner;
      APos =  Member->Position;
      if ( (AFlag->Owner == MLine) && (APos == APosition) )
      {
        Member->Flag = AFlag;
        return true;
      }

   }
   return false;

}
*/
void TListFlag::FreeList()
{
  TFlag* Member;
  for (int i = List->Count - 1 ; i>=0 ; i--)
  {
     Member = static_cast<TFlag*>(List->Items[i]);
     delete Member;
     Member = NULL;
     List->Delete(i);
  }
}
