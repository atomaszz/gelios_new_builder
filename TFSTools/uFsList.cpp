//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFsList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void TFsList::Clear()
{
  if(FFirst == NULL) return;
  TFsNode *A = FFirst->Next;
  while (A != FFirst)
  {
    TFsNode *D = A;
    A = A->Next;
    delete D;
  }
  delete FFirst;
  FFirst = NULL;
  FCount = 0;
}

void TFsList::Add(void* AData)
{
  TFsNode *A = new TFsNode;
  A->Data = AData;
  if (FFirst == NULL)//если это первый элемент в списке
  {
    A->Next = A;
    A->Pred = A;
    FFirst = A;
  }
  else
  {
    FFirst->Pred->Next = A;
    A->Pred = FFirst->Pred;
    A->Next = FFirst;
    FFirst->Pred = A;
  }
  FCount++;
}

void* TFsList::Delete(int APos)
{
  if (FFirst == NULL)  return NULL;//спсок пуст
  if (APos < 0 || APos >= FCount) return NULL; //обехопасим
  void* val;
  TFsNode *T = FFirst;
  for(int i = APos; i > 0; i--, T = T->Next);
  if(T == FFirst) FFirst = T->Next;//если пытаемся удалить 1-ый элемент то голова указывает на 2-ой
  if(FFirst == FFirst->Next)
    FFirst = NULL;
  T->Pred->Next = T->Next;//удаляем t элемент
  T->Next->Pred = T->Pred;
  val = T->Data;
  delete T;
  FCount--;
  return val;
}

TFsNode* TFsList::MoveInit(int APos)
{
  FMoveIndex = APos;
  if ( (FMoveIndex < 0) || (FMoveIndex > (FCount - 1)) )
    return NULL;
  FMoveNode = FFirst;
  for(int i = FMoveIndex; i > 0; i--, FMoveNode = FMoveNode->Next);
  return FMoveNode;
}

TFsNode* TFsList::MoveNext()
{
  FMoveIndex++;
  if ( (FMoveIndex < 0) || (FMoveIndex > (FCount - 1)) )
    return NULL;
  FMoveNode = FMoveNode->Next;
  return FMoveNode;
}

bool TFsList::IsExists(void* AData)
{
  if (FFirst == NULL) return false;
  TFsNode *F = FFirst;
  do
  {
    if (F->Data == AData)
      return true;
    F = F->Next;
  }while (F != FFirst);
  return false;
}


