//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uListShape.h"
#include "uAltInfo.h"

#include "uIMRIncl_all.h"
#include "opim_f.H"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TNodeMain::TNodeMain()
{
   IdBlock = 0;
   IdParentShape = 0;
   IdAlternate = 0;
   NumAlt = 0;
   TypeCreate = 0;
   WorkShape = NULL;
   Prior = NULL;
   Next = NULL;
}


TNodeMain::~TNodeMain()       //непонятно зачем то я  коментировал ее код 
{
  if (WorkShape != NULL)
  {
     delete WorkShape;
     WorkShape = NULL;
  }
}


TNodeAncestor::TNodeAncestor()
{
   IdBlock = 0;
   IdShapeAncestor = 0;
}


//------------------------------------------------------------------------
TNodeAlt::TNodeAlt()
{
   ID = -1;
   Num = -1;
   NodeStart = NULL;
   NodeEnd = NULL;
}



//------------------------------------------------------------------------
TNodeSearch::TNodeSearch()
{
   List = new TList;
   UID = 0;
   indexFindChild = 0;
}

TNodeSearch::~TNodeSearch()
{
   delete List;
}


//------------------------------------------------------------------------
TNodeSearchController::TNodeSearchController()
{
   List = new TList;
   MainList = NULL;
}

TNodeSearchController::~TNodeSearchController()
{
    FreeSerchList();
    delete List;
}

int TNodeSearchController::FindNextUid()
{
   int i, j = 1;
   TNodeSearch* Node;
   bool go = true;
   for (j = 1; j < MaxInt - 1; j++)
   {
     if (go)
     {
       go = false;
       for (i = 0; i <= List->Count - 1; i++)
       {
          Node = static_cast<TNodeSearch*>(List->Items[i]);
          if (Node->UID == j)
          {
            go = true;
            break;
          }
       }
     }
     else break;
   }
   return j;
}



void TNodeSearchController::FreeSerchList()
{
   TNodeSearch* Node;
   for (int i = List->Count - 1; i >= 0; i--)
   {
      Node = static_cast<TNodeSearch*>(List->Items[i]);
      delete Node;
      Node = NULL;
      List->Delete(i);
   }
}

void TNodeSearchController::SetMainList(TListNode* AList)
{
   MainList = AList;
}

TNodeSearch* TNodeSearchController::FindNode(int AUID)
{
   TNodeSearch* Node;
   for (int i = List->Count - 1; i >= 0; i--)
   {
      Node = static_cast<TNodeSearch*>(List->Items[i]);
      if (Node->UID == AUID) return Node;
   }
   return NULL;
}

TBaseWorkShape* TNodeSearchController::FindFirstChild(int AltId, int ANumAlt,  int AIdParentShape, int &AUID)
{
   int nUid;
   TNodeMain *TempN;
   TNodeSearch* Node;
   nUid = FindNextUid();
   AUID = nUid;
   Node = new TNodeSearch;
   List->Add(Node);
   Node->UID = nUid;
   Node->indexFindChild = -1;
   TempN = MainList->SearchFirstNodeToAlternate(AltId, ANumAlt, AIdParentShape);
   while (TempN)
   {
      Node->List->Add(TempN->WorkShape);
      TempN = MainList->SearchNextNodeToAlternate(AltId, ANumAlt, TempN);
   }

   if (Node->List->Count > 0 )
   {
     Node->indexFindChild = 0;
     return static_cast<TBaseWorkShape*>(Node->List->Items[Node->indexFindChild]);
   }
   return NULL;
}

TBaseWorkShape* TNodeSearchController::FindNextChild(int AUID)
{
   TNodeSearch* Node = FindNode(AUID);
   if (Node)
   {
      Node->indexFindChild++;
      if (Node->List->Count > Node->indexFindChild)
        return static_cast<TBaseWorkShape*>(Node->List->Items[Node->indexFindChild]);
   }
   return NULL;
}

bool TNodeSearchController::DisableFind(int AUID)
{
   TNodeSearch* Node;
   for (int i = List->Count - 1; i >= 0; i--)
   {
      Node = static_cast<TNodeSearch*>(List->Items[i]);
      if (Node->UID == AUID)
      {
         delete Node;
         Node = NULL;
         List->Delete(i);
         return true;
      }
   }
   return false;
}


void TNodeSearchController::ClearAll()
{
   FreeSerchList();
}





//----------------------------------------------------------------------
TListNode::TListNode()
{
   TNodeAlt* Alt;
   MainList = new TList;
   AncestorList = new TList;
   AlternateList = new TList;
   Searcher = new TNodeSearchController;
   Searcher->SetMainList(this);
   FOnListChange = NULL;
   f_Update = false;
   f_Changes = false;
   f_StackDustController = new TStackDustController();
}


void TListNode::FreeListMain()
{
  int i;
  TNodeMain *currNode;
  for (i = MainList->Count-1; i>=0 ;i--)
  {
    currNode = static_cast<TNodeMain*>(MainList->Items[i]);
    delete currNode;
    currNode = NULL;
    MainList->Delete(i);
  }
}


void TListNode::FreeListAncestor()
{
  int i;
  TNodeAncestor *currNode;
  for (i = AncestorList->Count-1; i>=0 ;i--)
  {
    currNode = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
    delete currNode;
    currNode = NULL;
    AncestorList->Delete(i);
  }
}


TListNode::~TListNode()
{
   FreeListAncestor();
   FreeListMain();
   FreeListAlternate();
   delete MainList;
   delete AncestorList;
   delete AlternateList;
   delete Searcher;
   delete f_StackDustController;
}


bool TListNode::CheckAlternateNode(int ID, int ANumAlt)
{
   TNodeAlt *Alt;
   for(int i = 0; i <= AlternateList->Count - 1; i++ )
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if ( (Alt->ID == ID) && (Alt->Num == ANumAlt) ) return true;
   }
   return false;
}


TNodeAlt* TListNode::CheckFirstNodeAlt()
{
   TNodeAlt* Alt;
   if (AlternateList->Count == 1)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[0]);
      if ( !Alt->NodeStart ) return Alt;
   }
   return NULL;
}

//----------------------------------------------------------------------
TNodeMain* TListNode::FindLastNodeToAlternate(int AltId, int ANumAlt,  int AIdParenShape)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ((TempN->IdAlternate == AltId) && (TempN->NumAlt == ANumAlt)
       && (TempN->IdParentShape == AIdParenShape))
        if (!TempN->Next) return TempN;
  }
  return NULL;
}

//---------------------------------------------------------------------------
TNodeMain* TListNode::FindPriorNodeToAlternate(int AltId, TBaseWorkShape* WBefore)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->IdAlternate == AltId)
        if (TempN->WorkShape == WBefore) return TempN;
  }
  return NULL;
}


//----------------------------------------------------------------------
TNodeMain* TListNode::FindNode(int IdBlock, int &pos)
{
  int i = -1;
  pos = i;
  TNodeMain* TempN;
  for (i = 0; i<=MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->IdBlock == IdBlock)
     {
        pos = i;
        return(TempN);
     }
  }
  return (NULL);
}


TNodeMain* TListNode::FindNode(TBaseWorkShape *WShape)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->WorkShape == WShape)
        return(TempN);
  }
  return (NULL);
}

TNodeAncestor* TListNode::IsExistsNodeAncestor(int AIdBlock, int AIdShapeAncestor)
{
  TNodeAncestor *currNode;
  for (int i = AncestorList->Count-1; i>=0 ;i--)
  {
    currNode = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
    if ( (currNode->IdBlock ==  AIdBlock) && (currNode->IdShapeAncestor == AIdShapeAncestor))
      return currNode;
  }
  return NULL;
}


TNodeAncestor* TListNode::DoAddNodeAncestor(int AIdBlock, int AIdShapeAncestor)
{
   TNodeAncestor* Res = IsExistsNodeAncestor(AIdBlock, AIdShapeAncestor);
   if (!Res)
   {
      TNodeAncestor* NAc = new TNodeAncestor;
      NAc->IdBlock = AIdBlock;
      NAc->IdShapeAncestor = AIdShapeAncestor;
      AncestorList->Add(NAc);
      Res = NAc;
   }
   return Res;
}




void TListNode::AddShapeToList(int AltId, int ANumAlt, TBaseWorkShape *WShape, int IdParentShape)
{
   TNodeMain *Nd;
   TNodeMain *NPrior;
   TNodeAncestor *NAc;
   int ParentBlock;
   int pos;
   if (!CheckAlternateNode(AltId, ANumAlt)) return;
   NPrior = FindLastNodeToAlternate(AltId, ANumAlt, IdParentShape);

   Nd = new TNodeMain;
   Nd->IdBlock = WShape->BlockId;  //s
   Nd->IdParentShape = IdParentShape;
   Nd->WorkShape = WShape;
   Nd->IdAlternate = AltId;
   Nd->NumAlt =  ANumAlt;
   if (NPrior) //не первый узел
   {
      NPrior->Next = Nd;
      Nd->Prior = NPrior;
   }

   MainList->Add(Nd);
   if (FOnListChange && (!f_Update) ) OnListChange();
   f_Changes = true;

   TNodeAlt* NAlt = CheckFirstNodeAlt();
   if (NAlt && (AltId == 0) )
     NAlt->NodeStart = Nd;

   if (IdParentShape != 0)
   {
      DoAddNodeAncestor(Nd->IdBlock, Nd->IdParentShape);
      while (1)
      {
         if (Nd->IdParentShape == 0) return;
         ParentBlock = FindBlockOutShape(Nd->IdParentShape);


         Nd = FindNode(ParentBlock, pos);
         if (Nd->IdParentShape != 0)
            DoAddNodeAncestor(Nd->IdBlock, Nd->IdParentShape);
      }
   }
}


void TListNode::PrepareAddNode(TNodeMain *Nd)
{
   TNodeAlt* NAlt = CheckFirstNodeAlt();
   if (NAlt && (Nd->IdAlternate == 0) )
     NAlt->NodeStart = Nd;
}


bool TListNode::IsContainsChildBlock(int IdBlock)
{
  int i, j, mn, mx;
  int pos;
  TNodeMain *Nd;
  Nd = FindNode(IdBlock, pos);
  if (Nd == NULL)
    return false;

  mn = Nd->WorkShape->FirstShapeId;
  mx = Nd->WorkShape->LastShapeId;

  for (j = mn; j <= mx; j++)
  {
    TNodeAncestor *currNode;
    for (i = AncestorList->Count-1; i>=0 ;i--)
    {
      currNode = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
      if ( currNode->IdShapeAncestor == j )
         return true;
    }
  }
  return false;
}


bool TListNode::IsContainsChildShape(int IdShape)
{
  int i;
  TNodeAncestor *currNode;
  for (i = AncestorList->Count-1; i>=0 ;i--)
    {
      currNode = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
      if ( currNode->IdShapeAncestor == IdShape )
         return true;
    }
  return false;
}

int TListNode::DeleteBlock(int IdBlock)
{
  int i, j, mn, mx, res = 0;
  int pos1, pos;
  int idbl;
  TNodeMain *Nd, *NdTemp;
  Nd = FindNode(IdBlock, pos1);

  if (Nd == NULL)
    return -1;
  mn = Nd->WorkShape->FirstShapeId;
  mx = Nd->WorkShape->LastShapeId;

  for (j = mn; j <= mx; j++)
  {
    TNodeAncestor *currNode;
    for (i = AncestorList->Count-1; i>=0 ;i--)
    {
      currNode = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
      if (currNode)
      {
        if ( currNode->IdShapeAncestor == j )
        {
           NdTemp = FindNode(currNode->IdBlock, pos);
           if (NdTemp != NULL)
           {
              delete currNode;
              AncestorList->Items[i] = NULL;

              DeleteBlock(NdTemp->IdBlock);
           }
        }
      }
    }
  }
  MainList->Delete(pos1);
  delete Nd;
  if (FOnListChange && (!f_Update)) FOnListChange();
  f_Changes = true;
  res++;
  return res;
}


int TListNode::FindBlockOutShape(int IdShape)
{
  int i, j, mn, mx;
  TNodeMain* TempN;
  for (i = 0; i<=MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     mn = TempN->WorkShape->FirstShapeId;
     mx = TempN->WorkShape->LastShapeId;
     if ( (IdShape >= mn) && (IdShape <= mx))
       return TempN->IdBlock;
  }
  return 0;
}


TBaseWorkShape* TListNode::FindFirstChild(int AltId, int ANumAlt, int IdParentShape, int &AUid)
{
   return Searcher->FindFirstChild(AltId, ANumAlt,  IdParentShape, AUid);
}



TBaseWorkShape* TListNode::FindNextChild(int AUid)
{
   return Searcher->FindNextChild(AUid);
}


bool TListNode::DisableFind(int AUid)
{
   return Searcher->DisableFind(AUid);
}



bool TListNode::IsFirstWorkShape(TBaseWorkShape *WShape,  int AltId, int ANumAlt, int IdParentShape)
{
  TBaseWorkShape *Tmp;
  int UidFinder;
  Tmp = FindFirstChild(AltId, ANumAlt, IdParentShape, UidFinder);
  DisableFind(UidFinder);
  if (Tmp == NULL) return false;
  return (Tmp == WShape);
}



TBaseWorkShape*  TListNode::GetLastWorkShape(int AltId, int ANumAlt, int IdParentShape)
{
 /* stas19 отключение   TAdWork* TmpAdWork */
  int UidFinder;
  //TAdWork* TmpAdWork;
  TBaseWorkShape *Tmp, *Tmp2;
  Tmp = FindFirstChild(AltId, ANumAlt, IdParentShape, UidFinder);
  Tmp2 = Tmp;
  while (1)
  {
	Tmp = FindNextChild(UidFinder);
	if (Tmp == NULL) break;
  /* stas19 отключение   TAdWork* TmpAdWork
	if (Tmp)
	{
	  if (Tmp->TypeShape == 1000)
	  {
		TmpAdWork = dynamic_cast<TAdWork*>(Tmp);
		if (TmpAdWork->SetPoint) continue;
	  }
	} отключение   TAdWork* TmpAdWork */

	Tmp2 = Tmp;

  }
  DisableFind(UidFinder);
  return (Tmp2);
}

//--------------------------------------------------------------------------------
void TListNode::InsertShapeToList(int AltId, int ANumAlt, TBaseWorkShape* WBefore, TBaseWorkShape *WShape, int IdParentShape)
{
   TNodeMain *Nd;
   TNodeMain *NInsert;
   TNodeAncestor *NAc;
   int ParentBlock;
   int pos;
   if (!CheckAlternateNode(AltId, ANumAlt)) return;
   NInsert = FindPriorNodeToAlternate(AltId, WBefore);
   if (!NInsert) return;


   Nd = new TNodeMain;
   Nd->IdBlock = WShape->BlockId;  //s
   Nd->IdParentShape = IdParentShape;
   Nd->WorkShape = WShape;
   Nd->IdAlternate = AltId;
   Nd->NumAlt = ANumAlt;

   if (NInsert->Prior)
   {
     NInsert->Prior->Next = Nd;
     Nd->Next = NInsert;
     Nd->Prior = NInsert->Prior;
     NInsert->Prior = Nd;
   }
   else
   {
     Nd->Next = NInsert;
     NInsert->Prior = Nd;

   }


   MainList->Add(Nd);
   if (FOnListChange && (!f_Update) ) OnListChange();
   f_Changes = true;

//   MainList->Insert(Position, Nd);
   if (IdParentShape != 0)
   {
      DoAddNodeAncestor(Nd->IdBlock, Nd->IdParentShape);
      while (1)
      {
         if (Nd->IdParentShape == 0) return;
         ParentBlock = FindBlockOutShape(Nd->IdParentShape);


         Nd = FindNode(ParentBlock, pos);
         if (Nd->IdParentShape != 0)
            DoAddNodeAncestor(Nd->IdBlock, Nd->IdParentShape);
      }
   }
}


//-----------------------------------------------------
void TListNode::ClearDeleteBlock()
{
   for (int i = AncestorList->Count-1; i>=0; i--)
   {
     if (!AncestorList->Items[i])
       AncestorList->Delete(i);
   }
}

//-----------------------------------------------------
int TListNode::DecayWorkShape(TBaseWorkShape *WDecay, TBaseWorkShape *WN1, TBaseWorkShape *WN2)
{
  int pos1;
  TNodeMain *Nd;
  Nd = FindNode(WDecay->BlockId, pos1);
  int m_IdParentShape = Nd->IdParentShape;
  if (Nd)
  {
    MainList->Delete(pos1);
    //    delete Nd;
  }
  Nd = new TNodeMain;
  Nd->IdBlock = WN1->BlockId;  //s
  Nd->IdParentShape = m_IdParentShape;
  Nd->WorkShape = WN1;
  MainList->Insert(pos1, Nd);

  pos1++;
  Nd = new TNodeMain;
  Nd->IdBlock = WN2->BlockId;  //s
  Nd->IdParentShape = m_IdParentShape;
  Nd->WorkShape = WN2;
  MainList->Insert(pos1, Nd);
  return pos1;
}


//------------------------------------------------------
void TListNode::FusionWorkShape(TBaseWorkShape *WFusion, TBaseWorkShape *WN1, TBaseWorkShape *WN2)
{
  int pos1, pos2;
  TNodeMain *Nd;
  Nd = FindNode(WN1->BlockId, pos1);
  int m_IdParentShape = Nd->IdParentShape;
  if (Nd)
  {
    MainList->Delete(pos1);
  }
  Nd = FindNode(WN2->BlockId, pos2);
  if (Nd)
  {
    MainList->Delete(pos2);
  }
  WN1->FreeWorkLines();
  WN2->FreeWorkLines();

  Nd = new TNodeMain;
  Nd->IdBlock = WFusion->BlockId;  //s
  Nd->IdParentShape = m_IdParentShape;
  Nd->WorkShape = WFusion;
  MainList->Insert(pos1, Nd);
}


//------------------------------------------------------------------------------
bool TListNode::IsEmpty()
{
   return (MainList->Count == 0);
}

//------------------------------------------------------------------------------

TBaseWorkShape*  TListNode::FindWorkShapeOutBaseShape(TBaseShape* Shape, int &ShapeId)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     ShapeId = TempN->WorkShape->ShapeSupport(Shape);
     if (ShapeId != -1) return TempN->WorkShape;
  }
  return NULL;
}


//------------------------------------------------------------------------------
TBaseWorkShape*  TListNode::FindWorkShapeOutBaseShapeID(int ShapeID, TBaseShape** Shape)
{
  TNodeMain* TempN;
  TBaseShape* Res;
  for (int i = 0; i <= MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     Res = TempN->WorkShape->ShapeSupportID(ShapeID);
     if (Res)
     {
        *Shape = Res;
        return TempN->WorkShape;
     }
  }
  return NULL;
}

//------------------------------------------------------------------------------
void TListNode::FreeListAlternate()
{
  TNodeAlt *Alt;
  for (int i = AlternateList->Count-1; i>=0 ; i--)
  {
    Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
    delete Alt;
    Alt = NULL;
    AlternateList->Delete(i);
  }
}


//------------------------------------------------------------------------------
bool TListNode::CreateAlternate(TBaseWorkShape *WS, TBaseWorkShape *WE, int AID, int ANumAlt)
{
   TNodeAlt* Alt;
   TNodeMain *NS, *NE;
   if (!WS && !WE)
   {
     Alt = new TNodeAlt;
     Alt->ID = AID;
     Alt->NodeStart = NULL;
     Alt->NodeEnd = NULL;
     Alt->Num = ANumAlt;
     AlternateList->Add(Alt);
     return true;
   }
   NS = FindNode(WS);
   NE = FindNode(WE);
   if ( (!NS) || (!NE) ) return false;
   for (int i = 0; i <= AlternateList->Count - 1; i++)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if (Alt->ID == AID)
        return false;
   }
   Alt = new TNodeAlt;
   Alt->ID = AID;
   Alt->NodeStart = NS;
   Alt->NodeEnd = NE;
   Alt->Num = ANumAlt;
   AlternateList->Add(Alt);
   return true;
}


TNodeMain* TListNode::SearchFirstNodeToAlternate(int AltId, int ANumAlt, int IdParentShape)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ((TempN->IdAlternate == AltId) &&  (TempN->NumAlt == ANumAlt) && (TempN->IdParentShape == IdParentShape))
        if (!TempN->Prior) return TempN;
  }
  return NULL;
}


TNodeMain* TListNode::SearchNextNodeToAlternate(int AltId, int ANumAlt,  TNodeMain* Node)
{
  TNodeMain* TempN;
  if (!Node) return NULL;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ( (TempN->IdAlternate == AltId) && (TempN->NumAlt == ANumAlt) )
        if (TempN->Prior)
           if (TempN->Prior == Node) return TempN;
  }
  return NULL;
}


TNodeMain* TListNode::SearchFirstNodeToAlternate2(int AltId, int IdParentShape)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ((TempN->IdAlternate == AltId) &&  (TempN->IdParentShape == IdParentShape))
        if (!TempN->Prior) return TempN;
  }
  return NULL;
}


TNodeMain* TListNode::SearchNextNodeToAlternate2(int AltId, TNodeMain* Node)
{
  TNodeMain* TempN;
  if (!Node) return NULL;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ( (TempN->IdAlternate == AltId)  )
        if (TempN->Prior)
           if (TempN->Prior == Node) return TempN;
  }
  return NULL;
}


TNodeMain* TListNode::SearchFirstNodeToAlternate3(int AltId, int ANumAlt)
{
  TNodeMain* TempN;
  for (int i = 0; i <= MainList->Count - 1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if ((TempN->IdAlternate == AltId) &&  (TempN->NumAlt == ANumAlt))
        if (!TempN->Prior) return TempN;
  }
  return NULL;
}

TNodeMain* TListNode::SearchNextNodeToAlternate3(int AltId, TNodeMain* Node)
{
   return SearchNextNodeToAlternate2(AltId, Node);
}




TPainterList::TPainterList()
{
   List = new TList;
   f_pos = 0;
}

TPainterList::~TPainterList()
{
   delete List;
}


void TPainterList::ClearAll()
{
   List->Clear();
}


int __fastcall TPainterList::GetCount()
{
   return  List->Count;
}

TBaseWorkShape* TPainterList::First()
{
   TBaseWorkShape* Res = NULL;
   f_pos = 0;
   if (List->Count > 0)
      Res = static_cast<TBaseWorkShape*>(List->Items[f_pos]);
   return Res;
}

TBaseWorkShape* TPainterList::Next()
{
   TBaseWorkShape* Res = NULL;
   f_pos++;
   if ((List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TBaseWorkShape*>(List->Items[f_pos]);
   return Res;
}

TBaseWorkShape* TPainterList::Prior()
{
   TBaseWorkShape* Res = NULL;
   f_pos--;
   if ((List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TBaseWorkShape*>(List->Items[f_pos]);
   return Res;
}

TBaseWorkShape* TPainterList::Last()
{
   TBaseWorkShape* Res = NULL;
   if (List->Count > 0)
   {
      f_pos = List->Count - 1;
      Res = static_cast<TBaseWorkShape*>(List->Items[f_pos]);
   }
   return Res;
}


bool TPainterList::IsExists(TBaseWorkShape* AWS)
{
   for(int i = 0; i <= List->Count -1; i++)
   {
       if ( static_cast<TBaseWorkShape*>(List->Items[i]) == AWS)
          return true;
   }
   return false;
}



void TListNode::FillPainterList(TPainterList* PainterList, int AltId, int ANumAlt,  int IdParentShape)
{
   TBaseWorkShape *WShape;
   int uid;
   PainterList->List->Clear();
   WShape = FindFirstChild(AltId, ANumAlt, IdParentShape, uid);
   while (WShape)
   {
      PainterList->List->Add(WShape);
      WShape = FindNextChild(uid);
   }
   DisableFind(uid);
}


TBaseWorkShape* TListNode::FindNextNode(TBaseWorkShape *W)
{
   TNodeMain* TempN;
   if ( !W ) return NULL;
   for (int i = 0; i <= MainList->Count - 1 ; i++)
   {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->WorkShape == W)
     {
       if (TempN->Next)
         return TempN->Next->WorkShape;
       else
         return NULL;
     }
   }
   return NULL;
}

TBaseWorkShape* TListNode::FindPriorNode(TBaseWorkShape *W)
{
   TNodeMain* TempN;
   if ( !W ) return NULL;
   for (int i = 0; i <= MainList->Count - 1 ; i++)
   {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->WorkShape == W)
     {
       if (TempN->Prior)
         return TempN->Prior->WorkShape;
       else
         return NULL;
     }
   }
   return NULL;
}


TNodeMain* TListNode::FindNextNode2(TBaseWorkShape *W)
{
   TNodeMain* TempN;
   if ( !W ) return NULL;
   for (int i = 0; i <= MainList->Count - 1 ; i++)
   {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->WorkShape == W)
       return TempN->Next;
   }
   return NULL;
}

TNodeMain* TListNode::FindPriorNode2(TBaseWorkShape *W)
{
   TNodeMain* TempN;
   if ( !W ) return NULL;
   for (int i = 0; i <= MainList->Count - 1 ; i++)
   {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     if (TempN->WorkShape == W)
       return TempN->Prior;
   }
   return NULL;
}



bool TListNode::CompareWorkShape(TBaseWorkShape **WS, TBaseWorkShape **WE)
{
   TBaseWorkShape *TS, *TE;
   TNodeMain *Node, *NNext;
   int i = 0;
   TS = TE = NULL;
   if ( (*WS) == (*WE) )  return true;//new
   if ( (*WS) && (*WE) )
   {
      if ( (*WS)->ParentShapeID !=  (*WE)->ParentShapeID )
        return false;
      for( i = 0; i <= MainList->Count - 1; i++)
      {
         Node = static_cast<TNodeMain*>(MainList->Items[i]);
         if (Node->WorkShape == *WS)
           break;
         else Node = NULL;
      }
      if (!Node) return false;
      NNext = SearchFirstNodeToAlternate(Node->IdAlternate, Node->NumAlt, Node->IdParentShape);
      while (NNext)
      {
         if ( (NNext->WorkShape == *WS) || ((NNext->WorkShape == *WE)))
            if (!TS)
              TS = NNext->WorkShape;
            else
              TE = NNext->WorkShape;
         NNext = this->SearchNextNodeToAlternate(Node->IdAlternate, Node->NumAlt, NNext);
      }
   }
   if ( TS && TE  )
   {
      *WS = TS;
      *WE = TE;
   }
   return true;
}


int TListNode::AddAlternate(TBaseWorkShape *WS, TBaseWorkShape *WE, int AID)
{
   int m_max = 0;
   TNodeAlt* Alt;
   TNodeMain *NS, *NE;
   NS = FindNode(WS);
   NE = FindNode(WE);
   if ( (!NS) || (!NE) ) return -1;
   for (int i = 0; i <= AlternateList->Count - 1; i++)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if ( (Alt->ID == AID) && (Alt->NodeStart == NS) && (Alt->NodeEnd == NE) )
      {
         if (m_max < Alt->Num)
           m_max = Alt->Num;
      }
   }
   m_max++;
   Alt = new TNodeAlt;
   Alt->ID = AID;
   Alt->NodeStart = NS;
   Alt->NodeEnd = NE;
   Alt->Num = m_max;
   AlternateList->Add(Alt);
   return m_max;
}

bool TListNode::GetWSToAlternate(int AId, TBaseWorkShape  **AWSFirst, TBaseWorkShape  **AWSLast)
{
   TNodeAlt* Alt;
   TNodeMain *NS, *NE;
   for (int i = 0; i <= AlternateList->Count - 1; i++)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if ( Alt->ID == AId  )
      {
         (*AWSFirst) = Alt->NodeStart->WorkShape;
         (*AWSLast) = Alt->NodeEnd->WorkShape;
         return true;
      }
   }
   return false;
}



bool TListNode::AddAlternate(int AID, int ANumAlt)
{
   TNodeAlt* Alt;
   TNodeMain *NS, *NE;
   int m_exists = 0;
   for (int i = 0; i <= AlternateList->Count - 1; i++)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if ( Alt->ID == AID)
      {
         if (Alt->Num ==  ANumAlt)
           m_exists++;
         NS = Alt->NodeStart;
         NE = Alt->NodeEnd;
      }
   }
   if (!m_exists)
   {
     Alt = new TNodeAlt;
     Alt->ID = AID;
     Alt->NodeStart = NS;
     Alt->NodeEnd = NE;
     Alt->Num = ANumAlt;
     AlternateList->Add(Alt);
   }
   return !m_exists;
}



int TListNode::DeleteAlternate(int AID, int ANum)
{
   TNodeAlt* Alt;
   int cnt = 0;
   for (int i = AlternateList->Count - 1; i >= 0 ; i--)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if ( (Alt->ID == AID) && (Alt->Num == ANum) )
      {
         delete Alt;
         Alt = NULL;
         AlternateList->Delete(i);
         cnt++;
      }
   }
   return cnt;
}

void TListNode::BeginUpdate()
{
   f_Update = true;
}


void TListNode::EndUpdate()
{
   f_Update = false;
}

void TListNode::ClearAll()
{
    BeginUpdate();
    Searcher->ClearAll();
    f_StackDustController->ClearAll();
    FreeListAncestor();
    FreeListMain();
    FreeListAlternate();
    EndUpdate();
}

void  TListNode::PrepareDeleteWorkShape(TBaseWorkShape *AWS)
{
   int mn, mx, m_pos;
   TNodeAncestor *NodeAnc;
   TStackDustItemWS* Item;
   TNodeAlt* AltItem;
   TBaseWorkShape *WSF, *WSL, *TmpWS;
   TNodeMain* Node = FindNode(AWS->BlockId, m_pos);
   if (!Node) return ;
   f_StackDustController->ClearAll();
   f_StackDustController->AddNode(Node, m_pos);
   Item = f_StackDustController->FirstWS();
   while (Item)
   {
      if ( !Item->CheckNesting )
      {
        mn = Item->Node->WorkShape->FirstShapeId;
        mx = Item->Node->WorkShape->LastShapeId;

        for (int j = mn; j <= mx; j++)
        {
           for (int i = AncestorList->Count-1; i >= 0 ;i--)
           {
              NodeAnc = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
              if (NodeAnc)
              {
                 if ( NodeAnc->IdShapeAncestor == j )
                 {
                    Node = FindNode(NodeAnc->IdBlock, m_pos);
                    if (Node)
                    {
                       f_StackDustController->AddNode(Node, m_pos);
                       delete NodeAnc;
                       AncestorList->Items[i] = NULL; //!!!!!!!!!!!!! иначе труба
                    }
                 }
              }
           }
           //ssss
           for (int i = AncestorList->Count-1; i >= 0 ;i--)
           {
              NodeAnc = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
              if (NodeAnc)
              {
                 //if ( (NodeAnc->IdBlock == AWS->BlockId) || (NodeAnc->IdBlock == j) )
                 if ( (NodeAnc->IdBlock == AWS->BlockId)  )
                 {
                    delete NodeAnc;
                    AncestorList->Items[i] = NULL; //!!!!!!!!!!!!! иначе труба
                 }
              }
           }
           //ssss
           ClearDeleteBlock();
		}

		Item->CheckNesting = true;

		if ( !Item->CheckAlternate )
		{
		  for (int k = 0; k <= AlternateList->Count - 1; k++)
		  {
			 AltItem = static_cast<TNodeAlt*>(AlternateList->Items[k]);
			 if (AltItem->ID == 0) continue;//не удалять самую верхнюю альтернативу
			 if ( ( (AltItem->NodeStart) && (AltItem->NodeStart->WorkShape == Item->Node->WorkShape) ) ||
				  ( (AltItem->NodeEnd ) && (AltItem->NodeEnd->WorkShape == Item->Node->WorkShape)) )
			   f_StackDustController->AddAlternate(AltItem);
		  }
		  // проверка по альтернативам не нужна ибо выкосится по анкесторам
		}
		Item->CheckAlternate =  true;
	  Item = f_StackDustController->NextWS();
	}
	}
	ClearDeleteBlock();
	CheckDeleteAlternate(AWS);
}

void TListNode::CheckDeleteAlternate(TBaseWorkShape *AWS)
{
   TNodeAlt* Alt;
   for (int i = AlternateList->Count - 1; i >= 0 ; i--)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if  ( Alt->NodeStart )
        if ( Alt->NodeStart->WorkShape ==  AWS)
           Alt->NodeStart = FindNextNode2(AWS);
      if (Alt->NodeEnd)
         if (Alt->NodeEnd->WorkShape == AWS)
           Alt->NodeEnd = FindPriorNode2(AWS);
   }
}

TNodeAlt*  TListNode::CheckAlternateWSFirst(TBaseWorkShape *AWS)
{
   TNodeAlt* Alt;
   for (int i = AlternateList->Count - 1; i >= 0 ; i--)
   {
  //    if (Alt->ID)
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if (Alt->ID)
      {
        if  ( Alt->NodeStart )
          if ( Alt->NodeStart->WorkShape ==  AWS)
            return Alt;
      }
   }
   return NULL;
}


TNodeAlt*  TListNode::CheckAlternateWSEnd(TBaseWorkShape *AWS)
{
   TNodeAlt* Alt;
   for (int i = AlternateList->Count - 1; i >= 0 ; i--)
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if (Alt->ID)
      {
        if (Alt->NodeEnd)
           if (Alt->NodeEnd->WorkShape == AWS)
            return Alt;
      }
   }
   return NULL;
}


bool TListNode::PrepareLinksBeforeDelete(TBaseWorkShape *AWS)
{
   TNodeMain* Node = FindNode(AWS);
   if (Node)
   {
      if (Node->Prior)
        Node->Prior->Next = Node->Next;
      if (Node->Next)
        Node->Next->Prior = Node->Prior;
   }
   return (Node!=NULL);
}

int TListNode::DeleteWorkShape()
{
   int res = 0;
   TNodeMain* Node;
   TStackDustItemWS* ItemWS;
   ItemWS = f_StackDustController->FirstWS();
   while(ItemWS)
   {
     Node = static_cast<TNodeMain*>(MainList->Items[ItemWS->NodePos]);
     delete Node;
     MainList->Items[ItemWS->NodePos] = NULL;
     res++;
     ItemWS = f_StackDustController->NextWS();
   }
   for(int i = MainList->Count - 1; i>=0; i--)
   {
     Node = static_cast<TNodeMain*>(MainList->Items[i]);
     if(!Node)
     {
       MainList->Delete(i);
       f_Changes = true;
     }
   }

   return res;
}


int __fastcall TListNode::GetNodeMaxID()
{
   TNodeMain* Node;
   int res = 0;
   for(int i = MainList->Count - 1; i>=0; i--)
   {
	 Node = static_cast<TNodeMain*>(MainList->Items[i]);
	 if(Node)
	 {
		if (res < Node->IdBlock)
		  res = Node->IdBlock;
     }
   }
   return res;
}

int __fastcall TListNode::GetTFEMaxID()
{
   TNodeMain* Node;
   TBaseWorkShape* WS;
   int res = 0;
   int m_first, m_last;
   for(int i = MainList->Count - 1; i>=0; i--)
   {
     Node = static_cast<TNodeMain*>(MainList->Items[i]);
     if (Node)
     {
        WS =  Node->WorkShape;
        m_first = WS->FirstShapeId;
        m_last = WS->LastShapeId;
        if (res < m_first)
          res = m_first;
        if (res < m_last)
          res = m_last;
     }
   }
   return res;
}


int __fastcall TListNode::GetAlternateMaxID()
{
   TNodeAlt *Alt;
   int res = 0;
   for(int i = 0; i <= AlternateList->Count - 1; i++ )
   {
      Alt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      if (Alt)
      {
         if (res < Alt->ID)
           res = Alt->ID;
      }
   }
   return res;
}

void TListNode::ClearNodeTypeCreate()
{
   TNodeMain *Node;
   for(int i = MainList->Count - 1; i>=0; i--)
   {
     Node = static_cast<TNodeMain*>(MainList->Items[i]);
     Node->TypeCreate = 0;
   }
}

void TListNode::SaveParamAlternateToXML(TBaseShape* ATFE, TGlsXmlElement *AElement)
{
   TParamAlternativeItem* mi;
   if(ATFE->ParamAlt)
   {
     for(int i = 0; i <= ATFE->ParamAlt->Count - 1; i++)
     {
       mi = ATFE->ParamAlt->Items[i];
       TGlsXmlElement *xml_item = new TGlsXmlElement("ParamAlt");

       xml_item->SetAttribute("NUMBER", mi->NUMBER);
       xml_item->SetAttribute("PRED_ISTOR", mi->PRED_ISTOR.c_str());
       xml_item->SetAttribute("SOSTAV", mi->SOSTAV.c_str());
       xml_item->SetAttribute("NAME", mi->NAME.c_str());
       xml_item->SetAttribute("FUNCTION", mi->FUNCTION2.c_str());
       xml_item->SetAttribute("ELEMENT", mi->ELEMENT.c_str());
       xml_item->SetAttribute("PREDICAT", mi->PREDICAT.c_str());
       xml_item->SetDoubleAttribute("B", mi->B);
       xml_item->SetDoubleAttribute("T", mi->T);
       xml_item->SetDoubleAttribute("V", mi->V);
       xml_item->SetDoubleAttribute("A1_B_F", mi->A1_B_F);
       xml_item->SetDoubleAttribute("B_F1N", mi->B_F1N);
       xml_item->SetDoubleAttribute("B_F1B", mi->B_F1B);
       xml_item->SetDoubleAttribute("A2_B_F", mi->A2_B_F);
       xml_item->SetDoubleAttribute("B_F2N", mi->B_F2N);
       xml_item->SetDoubleAttribute("B_F2B", mi->B_F2B);
       xml_item->SetDoubleAttribute("A3_B_F", mi->A3_B_F);
       xml_item->SetDoubleAttribute("B_F3N", mi->B_F3N);
       xml_item->SetDoubleAttribute("B_F3B", mi->B_F3B);
       xml_item->SetDoubleAttribute("A1_T_F", mi->A1_T_F);
       xml_item->SetDoubleAttribute("T_F1N", mi->T_F1N);
       xml_item->SetDoubleAttribute("T_F1B", mi->T_F1B);
       xml_item->SetDoubleAttribute("A2_T_F", mi->A2_T_F);
       xml_item->SetDoubleAttribute("T_F2N", mi->T_F2N);
       xml_item->SetDoubleAttribute("T_F2B", mi->T_F2B);
       xml_item->SetDoubleAttribute("A3_T_F", mi->A3_T_F);
       xml_item->SetDoubleAttribute("T_F3N", mi->T_F3N);
       xml_item->SetDoubleAttribute("T_F3B", mi->T_F3B);
       xml_item->SetDoubleAttribute("A1_V_F", mi->A1_V_F);
       xml_item->SetDoubleAttribute("V_F1N", mi->V_F1N);
       xml_item->SetDoubleAttribute("V_F1B", mi->V_F1B);
       xml_item->SetDoubleAttribute("A2_V_F", mi->A2_V_F);
       xml_item->SetDoubleAttribute("V_F2N", mi->V_F2N);
       xml_item->SetDoubleAttribute("V_F2B", mi->V_F2B);
       xml_item->SetDoubleAttribute("A3_V_F", mi->A3_V_F);
       xml_item->SetDoubleAttribute("V_F3N", mi->V_F3N);
       xml_item->SetDoubleAttribute("V_F3B", mi->V_F3B);
       xml_item->SetDoubleAttribute("K_11", mi->K_11);
       xml_item->SetDoubleAttribute("K_00", mi->K_00);
       xml_item->SetDoubleAttribute("T_F", mi->T_F);
       xml_item->SetDoubleAttribute("V_F", mi->V_F);
       xml_item->SetDoubleAttribute("A1_K11_F", mi->A1_K11_F);
       xml_item->SetDoubleAttribute("K11_F1N", mi->K11_F1N);
       xml_item->SetDoubleAttribute("K11_F1B", mi->K11_F1B);
       xml_item->SetDoubleAttribute("A2_K11_F", mi->A2_K11_F);
       xml_item->SetDoubleAttribute("K11_F2N", mi->K11_F2N);
       xml_item->SetDoubleAttribute("K11_F2B", mi->K11_F2B);
       xml_item->SetDoubleAttribute("A3_K11_F", mi->A3_K11_F);
       xml_item->SetDoubleAttribute("K11_F3N", mi->K11_F3N);
       xml_item->SetDoubleAttribute("K11_F3B", mi->K11_F3B);
       xml_item->SetDoubleAttribute("A1_K00_F", mi->A1_K00_F);
       xml_item->SetDoubleAttribute("K00_F1N", mi->K00_F1N);
       xml_item->SetDoubleAttribute("K00_F1B", mi->K00_F1B);
       xml_item->SetDoubleAttribute("A2_K00_F", mi->A2_K00_F);
       xml_item->SetDoubleAttribute("K00_F2N", mi->K00_F2N);
       xml_item->SetDoubleAttribute("K00_F2B", mi->K00_F2B);
       xml_item->SetDoubleAttribute("A3_K00_F", mi->A3_K00_F);
       xml_item->SetDoubleAttribute("K00_F3N", mi->K00_F3N);
       xml_item->SetDoubleAttribute("K00_F3B", mi->K00_F3B);
       xml_item->SetDoubleAttribute("A1_TF_F", mi->A1_TF_F);
       xml_item->SetDoubleAttribute("TF_F1N", mi->TF_F1N);
       xml_item->SetDoubleAttribute("TF_F1B", mi->TF_F1B);
       xml_item->SetDoubleAttribute("A2_TF_F", mi->A2_TF_F);
       xml_item->SetDoubleAttribute("TF_F2N", mi->TF_F2N);
       xml_item->SetDoubleAttribute("TF_F2B", mi->TF_F2B);
       xml_item->SetDoubleAttribute("A3_TF_F", mi->A3_TF_F);
       xml_item->SetDoubleAttribute("TF_F3N", mi->TF_F3N);
       xml_item->SetDoubleAttribute("TF_F3B", mi->TF_F3B);
       xml_item->SetDoubleAttribute("A1_VF_F", mi->A1_VF_F);
       xml_item->SetDoubleAttribute("VF_F1N", mi->VF_F1N);
       xml_item->SetDoubleAttribute("VF_F1B", mi->VF_F1B);
       xml_item->SetDoubleAttribute("A2_VF_F", mi->A2_VF_F);
       xml_item->SetDoubleAttribute("VF_F2N", mi->VF_F2N);
       xml_item->SetDoubleAttribute("VF_F2B", mi->VF_F2B);
       xml_item->SetDoubleAttribute("A3_VF_F", mi->A3_VF_F);
       xml_item->SetDoubleAttribute("VF_F3N", mi->VF_F3N);
       xml_item->SetDoubleAttribute("VF_F3B", mi->VF_F3B);
       xml_item->SetDoubleAttribute("P_11", mi->P_11);
       xml_item->SetDoubleAttribute("P_00", mi->P_00);
       xml_item->SetDoubleAttribute("T_D", mi->T_D);
       xml_item->SetDoubleAttribute("V_D", mi->V_D);
       xml_item->SetDoubleAttribute("A1_P11_F", mi->A1_P11_F);
       xml_item->SetDoubleAttribute("P11_F1N", mi->P11_F1N);
       xml_item->SetDoubleAttribute("P11_F1B", mi->P11_F1B);
       xml_item->SetDoubleAttribute("A2_P11_F", mi->A2_P11_F);
       xml_item->SetDoubleAttribute("P11_F2N", mi->P11_F2N);
       xml_item->SetDoubleAttribute("P11_F2B", mi->P11_F2B);
       xml_item->SetDoubleAttribute("A3_P11_F", mi->A3_P11_F);
       xml_item->SetDoubleAttribute("P11_F3N", mi->P11_F3N);
       xml_item->SetDoubleAttribute("P11_F3B", mi->P11_F3B);
       xml_item->SetDoubleAttribute("A1_P00_F", mi->A1_P00_F);
       xml_item->SetDoubleAttribute("P00_F1N", mi->P00_F1N);
       xml_item->SetDoubleAttribute("P00_F1B", mi->P00_F1B);
       xml_item->SetDoubleAttribute("A2_P00_F", mi->A2_P00_F);
       xml_item->SetDoubleAttribute("P00_F2N", mi->P00_F2N);
       xml_item->SetDoubleAttribute("P00_F2B", mi->P00_F2B);
       xml_item->SetDoubleAttribute("A3_P00_F", mi->A3_P00_F);
       xml_item->SetDoubleAttribute("P00_F3N", mi->P00_F3N);
       xml_item->SetDoubleAttribute("P00_F3B", mi->P00_F3B);
       xml_item->SetDoubleAttribute("A1_TD_F", mi->A1_TD_F);
       xml_item->SetDoubleAttribute("TD_F1N", mi->TD_F1N);
       xml_item->SetDoubleAttribute("TD_F1B", mi->TD_F1B);
       xml_item->SetDoubleAttribute("A2_TD_F", mi->A2_TD_F);
       xml_item->SetDoubleAttribute("TD_F2N", mi->TD_F2N);
       xml_item->SetDoubleAttribute("TD_F2B", mi->TD_F2B);
       xml_item->SetDoubleAttribute("A3_TD_F", mi->A3_TD_F);
       xml_item->SetDoubleAttribute("TD_F3N", mi->TD_F3N);
       xml_item->SetDoubleAttribute("TD_F3B", mi->TD_F3B);
       xml_item->SetDoubleAttribute("A1_VD_F", mi->A1_VD_F);
       xml_item->SetDoubleAttribute("VD_F1N", mi->VD_F1N);
       xml_item->SetDoubleAttribute("VD_F1B", mi->VD_F1B);
       xml_item->SetDoubleAttribute("A2_VD_F", mi->A2_VD_F);
       xml_item->SetDoubleAttribute("VD_F2N", mi->VD_F2N);
       xml_item->SetDoubleAttribute("VD_F2B", mi->VD_F2B);
       xml_item->SetDoubleAttribute("A3_VD_F", mi->A3_VD_F);
       xml_item->SetDoubleAttribute("VD_F3N", mi->VD_F3N);
       xml_item->SetDoubleAttribute("VD_F3B", mi->VD_F3B);
       xml_item->SetAttribute("TYPE", mi->TYPE);
       xml_item->SetAttribute("ELEM_DIAGN", mi->ELEM_DIAGN.c_str());
       xml_item->SetDoubleAttribute("P_DIAGN_EL", mi->P_DIAGN_EL);
       xml_item->SetDoubleAttribute("A1_P_EL_F", mi->A1_P_EL_F);
       xml_item->SetDoubleAttribute("P_EL_F1N", mi->P_EL_F1N);
       xml_item->SetDoubleAttribute("P_EL_F1B", mi->P_EL_F1B);
       xml_item->SetDoubleAttribute("A2_P_EL_F", mi->A2_P_EL_F);
       xml_item->SetDoubleAttribute("P_EL_F2N", mi->P_EL_F2N);
       xml_item->SetDoubleAttribute("P_EL_F2B", mi->P_EL_F2B);
       xml_item->SetDoubleAttribute("A3_P_EL_F", mi->A3_P_EL_F);
       xml_item->SetDoubleAttribute("P_EL_F3N", mi->P_EL_F3N);
       xml_item->SetDoubleAttribute("P_EL_F3B", mi->P_EL_F3B);
       xml_item->SetDoubleAttribute("SOVM", mi->SOVM);
       xml_item->SetDoubleAttribute("SOVM0", mi->SOVM0);
       xml_item->SetDoubleAttribute("SOVM1", mi->SOVM1);

       AElement->LinkEndChild(xml_item);
     }
   }
}

void TListNode::SaveParamAlternateToBin(TBaseShape* ATFE, SF_TFE A_tfe, THandle AFile)
{
   TParamAlternativeItem* mi;
   SF_PARAMALT sf_param;
   int param_cnt = 0;
   if(ATFE->ParamAlt)
     param_cnt = ATFE->ParamAlt->Count;
   A_tfe.ParamCount = param_cnt;
   FileWrite(AFile, &A_tfe, sizeof(A_tfe));


     for(int i = 0; i <= param_cnt - 1; i++)
     {
       memset(&sf_param, 0, sizeof(sf_param));
       mi = ATFE->ParamAlt->Items[i];

       sf_param.NUMBER = mi->NUMBER;
       strcpy(sf_param.PRED_ISTOR, mi->PRED_ISTOR.c_str());
       strcpy(sf_param.SOSTAV, mi->SOSTAV.c_str());
       strcpy(sf_param.NAME, mi->NAME.c_str());
       strcpy(sf_param.FUNCTION2, mi->FUNCTION2.c_str());
       strcpy(sf_param.ELEMENT, mi->ELEMENT.c_str());
       strcpy(sf_param.PREDICAT, mi->PREDICAT.c_str());
       sf_param.B = mi->B;
       sf_param.T = mi->T;
       sf_param.V = mi->V;
       sf_param.A1_B_F = mi->A1_B_F;
       sf_param.B_F1N = mi->B_F1N;
       sf_param.B_F1B = mi->B_F1B;
       sf_param.A2_B_F = mi->A2_B_F;
       sf_param.B_F2N = mi->B_F2N;
       sf_param.B_F2B = mi->B_F2B;
       sf_param.A3_B_F = mi->A3_B_F;
       sf_param.B_F3N = mi->B_F3N;
       sf_param.B_F3B = mi->B_F3B;
       sf_param.A1_T_F = mi->A1_T_F;
       sf_param.T_F1N = mi->T_F1N;
       sf_param.T_F1B = mi->T_F1B;
       sf_param.A2_T_F = mi->A2_T_F;
       sf_param.T_F2N = mi->T_F2N;
       sf_param.T_F2B = mi->T_F2B;
       sf_param.A3_T_F = mi->A3_T_F;
       sf_param.T_F3N = mi->T_F3N;
       sf_param.T_F3B = mi->T_F3B;
       sf_param.A1_V_F = mi->A1_V_F;
       sf_param.V_F1N = mi->V_F1N;
       sf_param.V_F1B = mi->V_F1B;
       sf_param.A2_V_F = mi->A2_V_F;
       sf_param.V_F2N = mi->V_F2N;
       sf_param.V_F2B = mi->V_F2B;
       sf_param.A3_V_F = mi->A3_V_F;
       sf_param.V_F3N = mi->V_F3N;
       sf_param.V_F3B = mi->V_F3B;
       sf_param.K_11 = mi->K_11;
       sf_param.K_00 = mi->K_00;
       sf_param.T_F = mi->T_F;
       sf_param.V_F = mi->V_F;
       sf_param.A1_K11_F = mi->A1_K11_F;
       sf_param.K11_F1N = mi->K11_F1N;
       sf_param.K11_F1B = mi->K11_F1B;
       sf_param.A2_K11_F = mi->A2_K11_F;
       sf_param.K11_F2N = mi->K11_F2N;
       sf_param.K11_F2B = mi->K11_F2B;
       sf_param.A3_K11_F = mi->A3_K11_F;
       sf_param.K11_F3N = mi->K11_F3N;
       sf_param.K11_F3B = mi->K11_F3B;
       sf_param.A1_K00_F = mi->A1_K00_F;
       sf_param.K00_F1N = mi->K00_F1N;
       sf_param.K00_F1B = mi->K00_F1B;
       sf_param.A2_K00_F = mi->A2_K00_F;
       sf_param.K00_F2N = mi->K00_F2N;
       sf_param.K00_F2B = mi->K00_F2B;
       sf_param.A3_K00_F = mi->A3_K00_F;
       sf_param.K00_F3N = mi->K00_F3N;
       sf_param.K00_F3B = mi->K00_F3B;
       sf_param.A1_TF_F = mi->A1_TF_F;
       sf_param.TF_F1N = mi->TF_F1N;
       sf_param.TF_F1B = mi->TF_F1B;
       sf_param.A2_TF_F = mi->A2_TF_F;
       sf_param.TF_F2N = mi->TF_F2N;
       sf_param.TF_F2B = mi->TF_F2B;
       sf_param.A3_TF_F = mi->A3_TF_F;
       sf_param.TF_F3N = mi->TF_F3N;
       sf_param.TF_F3B = mi->TF_F3B;
       sf_param.A1_VF_F = mi->A1_VF_F;
       sf_param.VF_F1N = mi->VF_F1N;
       sf_param.VF_F1B = mi->VF_F1B;
       sf_param.A2_VF_F = mi->A2_VF_F;
       sf_param.VF_F2N = mi->VF_F2N;
       sf_param.VF_F2B = mi->VF_F2B;
       sf_param.A3_VF_F = mi->A3_VF_F;
       sf_param.VF_F3N = mi->VF_F3N;
       sf_param.VF_F3B = mi->VF_F3B;
       sf_param.P_11 = mi->P_11;
       sf_param.P_00 = mi->P_00;
       sf_param.T_D = mi->T_D;
       sf_param.V_D = mi->V_D;
       sf_param.A1_P11_F = mi->A1_P11_F;
       sf_param.P11_F1N = mi->P11_F1N;
       sf_param.P11_F1B = mi->P11_F1B;
       sf_param.A2_P11_F = mi->A2_P11_F;
       sf_param.P11_F2N = mi->P11_F2N;
       sf_param.P11_F2B = mi->P11_F2B;
       sf_param.A3_P11_F = mi->A3_P11_F;
       sf_param.P11_F3N = mi->P11_F3N;
       sf_param.P11_F3B = mi->P11_F3B;
       sf_param.A1_P00_F = mi->A1_P00_F;
       sf_param.P00_F1N = mi->P00_F1N;
       sf_param.P00_F1B = mi->P00_F1B;
       sf_param.A2_P00_F = mi->A2_P00_F;
       sf_param.P00_F2N = mi->P00_F2N;
       sf_param.P00_F2B = mi->P00_F2B;
       sf_param.A3_P00_F = mi->A3_P00_F;
       sf_param.P00_F3N = mi->P00_F3N;
       sf_param.P00_F3B = mi->P00_F3B;
       sf_param.A1_TD_F = mi->A1_TD_F;
       sf_param.TD_F1N = mi->TD_F1N;
       sf_param.TD_F1B = mi->TD_F1B;
       sf_param.A2_TD_F = mi->A2_TD_F;
       sf_param.TD_F2N = mi->TD_F2N;
       sf_param.TD_F2B = mi->TD_F2B;
       sf_param.A3_TD_F = mi->A3_TD_F;
       sf_param.TD_F3N = mi->TD_F3N;
       sf_param.TD_F3B = mi->TD_F3B;
       sf_param.A1_VD_F = mi->A1_VD_F;
       sf_param.VD_F1N = mi->VD_F1N;
       sf_param.VD_F1B = mi->VD_F1B;
       sf_param.A2_VD_F = mi->A2_VD_F;
       sf_param.VD_F2N = mi->VD_F2N;
       sf_param.VD_F2B = mi->VD_F2B;
       sf_param.A3_VD_F = mi->A3_VD_F;
       sf_param.VD_F3N = mi->VD_F3N;
       sf_param.VD_F3B = mi->VD_F3B;
       sf_param.TYPE = mi->TYPE;
       strcpy(sf_param.ELEM_DIAGN, mi->ELEM_DIAGN.c_str());
       sf_param.P_DIAGN_EL = mi->P_DIAGN_EL;
       sf_param.A1_P_EL_F = mi->A1_P_EL_F;
       sf_param.P_EL_F1N = mi->P_EL_F1N;
       sf_param.P_EL_F1B = mi->P_EL_F1B;
       sf_param.A2_P_EL_F = mi->A2_P_EL_F;
       sf_param.P_EL_F2N = mi->P_EL_F2N;
       sf_param.P_EL_F2B = mi->P_EL_F2B;
       sf_param.A3_P_EL_F = mi->A3_P_EL_F;
       sf_param.P_EL_F3N = mi->P_EL_F3N;
       sf_param.P_EL_F3B = mi->P_EL_F3B;
       sf_param.SOVM = mi->SOVM;
       sf_param.SOVM0 = mi->SOVM0;
       sf_param.SOVM1 = mi->SOVM1;
       FileWrite(AFile, &sf_param, sizeof(sf_param));
     }
}


void TListNode::SaveAllToFile(AnsiString AFileName, int ATypeParam, TDischargedMassiv* AOgrSovm)
{
   TNodeMain *CurrNode;
   TNodeAncestor *CurrAncestor;
   TNodeAlt *CurrAlt;
   TBaseWorkShape* WS;
   TBaseShape* ShapeTFE;
   int m_start_x, m_start_y, m_blockid, m_nextid, m_priorid;
   int m_offset_x, m_offset_y;
   int m_typeTfs;
   int m_parentShapeID;
   TGlsXmlDocument *xml_dom;
   TGlsXmlDeclaration *xml_dec;
   TGlsXmlElement *xml_root, *xml_main, *xml_anc, *xml_alt, *xml_item;
   TGlsXmlElement *xml_tfe, *xml_tfs, *xml_params, *xml_ogrsovm, *xml_type_param;
   TGlsXmlElement *xml_TypeDecision;
   xml_dom = new TGlsXmlDocument();
   xml_dec = new  TGlsXmlDeclaration("1.0", "windows-1251", "no");
   xml_root = new TGlsXmlElement("ROOT");
   xml_main = new  TGlsXmlElement("MAINLIST");
   xml_anc = new  TGlsXmlElement("ANCESTORLIST");
   xml_alt = new TGlsXmlElement("ALTERNATELIST");
   xml_ogrsovm = new TGlsXmlElement("OGRSOVMLIST");
   xml_type_param = new TGlsXmlElement("TYPEPARAM");
   xml_TypeDecision = new TGlsXmlElement("TYPEDECISION");
   //xml_alt = new  TGlsXmlElement("ALTERNATE");

   xml_dom->LinkEndChild(xml_dec);
   xml_dom->LinkEndChild(xml_root);
   xml_root->LinkEndChild(xml_main);
   xml_root->LinkEndChild(xml_anc);
   xml_root->LinkEndChild(xml_alt);
   xml_root->LinkEndChild(xml_ogrsovm);
   xml_root->LinkEndChild(xml_type_param);
   xml_root->LinkEndChild(xml_TypeDecision);

   for (int i = 0; i <= MainList->Count - 1; i++)
   {
      CurrNode = static_cast<TNodeMain*>(MainList->Items[i]);
      WS = CurrNode->WorkShape;
      m_start_x = WS->BaseStartPoint.x;
      m_start_y = WS->BaseStartPoint.y;
      m_offset_x = WS->BaseOffsetX;
      m_offset_y = WS->BaseOffsetY;
      m_blockid = CurrNode->IdBlock;
      m_nextid = m_priorid = -1;
      if (CurrNode->Next)
        m_nextid = CurrNode->Next->IdBlock;
      if (CurrNode->Prior)
        m_priorid = CurrNode->Prior->IdBlock;
      m_typeTfs = CurrNode->WorkShape->TypeShape;
      xml_item = new  TGlsXmlElement("TFS");
      xml_item->SetAttribute("ID", m_blockid);
      xml_item->SetAttribute("TypeID", m_typeTfs);
      xml_item->SetAttribute("StartPointX", m_start_x);
      xml_item->SetAttribute("StartPointY", m_start_y);
      xml_item->SetAttribute("OffsetX", m_offset_x);
      xml_item->SetAttribute("OffsetY", m_offset_y);
      xml_item->SetAttribute("NextID", m_nextid);
      xml_item->SetAttribute("PriorID", m_priorid);

      for (int j = 0; j <= WS->WorkShapesCount - 1; j++ )
      {
         ShapeTFE = static_cast<TBaseShape*>(WS->GetWorkShape(j));
         xml_tfe = new TGlsXmlElement("TFE");
         xml_tfe->SetAttribute("ID", ShapeTFE->ID);
         xml_tfe->SetAttribute("TypeID", ShapeTFE->TypeShape);

         xml_params = new TGlsXmlElement("PARAMS");
         SaveParamAlternateToXML(ShapeTFE, xml_params);
         xml_tfe->LinkEndChild(xml_params);

         xml_item->LinkEndChild(xml_tfe);
      }
      xml_main->LinkEndChild(xml_item);
   }

   for (int i = 0; i <= AncestorList->Count-1; i++)
   {
     CurrAncestor = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
     xml_item = new  TGlsXmlElement("ANCS");
     xml_item->SetAttribute("IdBlock", CurrAncestor->IdBlock);
     xml_item->SetAttribute("IdShapeAncestor", CurrAncestor->IdShapeAncestor);
     xml_anc->LinkEndChild(xml_item);
   }

   for(int i = 0; i <= AlternateList->Count - 1; i++ )
   {
      CurrAlt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      xml_item = new  TGlsXmlElement("ALT");
      xml_item->SetAttribute("ID", CurrAlt->ID);
      xml_item->SetAttribute("Num", CurrAlt->Num);
      m_nextid = m_priorid = -1;
      if (CurrAlt->NodeStart)
        m_nextid = CurrAlt->NodeStart->WorkShape->BlockId;
      if (CurrAlt->NodeEnd)
        m_priorid = CurrAlt->NodeEnd->WorkShape->BlockId;
      xml_item->SetAttribute("NodeStartID", m_nextid);
      xml_item->SetAttribute("NodeEndID", m_priorid);

      m_parentShapeID = 0;
      if (CurrAlt->NodeStart)
        m_parentShapeID = CurrAlt->NodeStart->IdParentShape;
      CurrNode = SearchFirstNodeToAlternate(CurrAlt->ID, CurrAlt->Num, m_parentShapeID);
      while (CurrNode)
      {
         xml_tfs = new  TGlsXmlElement("ITEM");
         xml_tfs->SetAttribute("ID", CurrNode->WorkShape->BlockId);
         xml_item->LinkEndChild(xml_tfs);
         CurrNode = SearchNextNodeToAlternate(CurrAlt->ID, CurrAlt->Num, CurrNode);
      }
      xml_alt->LinkEndChild(xml_item);

   }
   SaveOgrSovmToXML(AOgrSovm, xml_ogrsovm);
   xml_type_param->SetAttribute("Value", ATypeParam);
   SaveTypeDecision(xml_TypeDecision);
   xml_dom->SaveFile(AFileName.c_str());
   delete xml_dom;
}


TNodeMain* TListNode::CreateNode(TBaseWorkShape *WS)
{
   TNodeMain* Nd = NULL;
   Nd = new TNodeMain;
   Nd->IdBlock = WS->BlockId;
   Nd->IdParentShape = -1;
   Nd->WorkShape = WS;
   Nd->IdAlternate = -1;
   Nd->NumAlt =  -1;
   Nd->Next = NULL;
   Nd->Prior = NULL;
   Nd->TypeCreate = 1;
   MainList->Add(Nd);
   f_Changes = true;
   return Nd;
}

TNodeAncestor* TListNode::CreateNodeAncestor(int AId, int AIdAncestor)
{
   return DoAddNodeAncestor(AId, AIdAncestor);
}

void TListNode::FillNodeAncestor(TNodeMain *ANode)
{
   int ParentBlock, pos;
   TNodeMain *Nd = ANode;
   DoAddNodeAncestor(ANode->IdBlock, ANode->IdParentShape);
   while (1)
   {
      if (Nd->IdParentShape == 0) return;
      ParentBlock = FindBlockOutShape(Nd->IdParentShape);
      Nd = FindNode(ParentBlock, pos);
      if (Nd->IdParentShape != 0)
         DoAddNodeAncestor(Nd->IdBlock, Nd->IdParentShape);
   }
}

int __fastcall TListNode::GetAlternateCount()
{
   return AlternateList->Count;
}


TNodeAlt* __fastcall TListNode::GetAlternateItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= AlternateList->Count - 1)
     return static_cast<TNodeAlt*>(AlternateList->Items[AIndex]);
   else
     return NULL;
}

void TListNode::LoadInfoForAlternate(TAltInfo* AltIfo, int AParentShapeID)
{
   TNodeAlt* Itm;
   TNodeMain *Node, *First, *Last;
   TAltInfoItem* AI;
   AltIfo->Clear();
   for (int i = 0; i <= AlternateCount - 1; i++)
   {
      Itm = AlternateItem[i];
      if (Itm->NodeStart->IdParentShape == AParentShapeID)
      {
         AI = AltIfo->AddAltIfo(Itm->ID, Itm->Num, AParentShapeID, Itm->NodeStart, Itm->NodeEnd);
         if (AI && (Itm->ID == 0) && (Itm->Num == 0) && (AParentShapeID == 0) )
            AI->Main = true;

      }
   }
   for(int i = 0; i <= MainList->Count - 1; i++)
   {
     Node = static_cast<TNodeMain*>(MainList->Items[i]);
     if(Node && Node->IdParentShape == AParentShapeID)
     {
       AI =  AltIfo->AddAltIfo(Node->IdAlternate, Node->NumAlt, AParentShapeID, First, Last);
       if (AI)
       {
         AI->Main = true;
         First = Node;
         while(First->Prior)
           First = First->Prior;

         Last = Node;
         while(Last->Next)
           Last = Last->Next;

         AI->NodeStart = First;
         AI->NodeEnd = Last;
       }
     }
   }

}


bool TListNode::GetAlternateInfo(int AShapeID, int &AltID, int &NumAlt, int &IDParent)
{
  TNodeMain* TempN;
  TBaseShape* BS = NULL;
  for (int i = 0; i <= MainList->Count-1 ; i++)
  {
     TempN = static_cast<TNodeMain*>(MainList->Items[i]);
     BS = TempN->WorkShape->ShapeSupportID(AShapeID);
     if (BS)
       break;
  }
  if (BS)
  {
     AltID = TempN->IdAlternate;
     NumAlt = TempN->NumAlt;
     IDParent = TempN->IdParentShape;
  }
  return (!BS );
}


void TListNode::GetAllWorkShape(TDynamicArray *AMass)
{
   if(AMass)
   {
     AMass->Clear();
     for (int i = 0; i <= MainList->Count - 1; i++)
       AMass->Append(static_cast<TNodeMain*>(MainList->Items[i])->WorkShape);
   }

}

void TListNode::SaveAllToFileBin(AnsiString AFileName, int ATypeParam, TDischargedMassiv* AOgrSovm)
{
   TNodeMain *CurrNode;
   TNodeAncestor *CurrAncestor;
   TNodeAlt *CurrAlt;
   TBaseWorkShape* WS;
   TBaseShape* ShapeTFE;
   int m_start_x, m_start_y, m_blockid, m_nextid, m_priorid;
   int m_offset_x, m_offset_y;
   int m_typeTfs;
   int m_Block;
   int m_parentShapeID, ws_cnt, mn_count, an_count, al_count, item_count;
   SF_TFS s_tfs;
   SF_TFE s_tfe;
   SF_ANCS s_ancs;
   SF_ALT s_alt;

   THandle HF;

   if ( FileExists(AFileName) )
     HF  = FileOpen(AFileName, fmOpenReadWrite);
   else
     HF  = FileCreate(AFileName);

   if (HF == THandle(INVALID_HANDLE_VALUE) )
     throw Exception("Ошибка при сохранении в файл!");

   FileWrite(HF, SF_HADERBIN, strlen(SF_HADERBIN));
   TList *TL = new TList;
   mn_count = MainList->Count;
   FileWrite(HF, &mn_count, sizeof(mn_count));
   for (int i = 0; i <= mn_count - 1; i++)
   {
      memset(&s_tfs, 0, sizeof(s_tfs));
      CurrNode = static_cast<TNodeMain*>(MainList->Items[i]);
      WS = CurrNode->WorkShape;
      m_start_x = WS->BaseStartPoint.x;
      m_start_y = WS->BaseStartPoint.y;
      m_offset_x = WS->BaseOffsetX;
      m_offset_y = WS->BaseOffsetY;
      m_blockid = CurrNode->IdBlock;
      m_nextid = m_priorid = -1;
      if (CurrNode->Next)
        m_nextid = CurrNode->Next->IdBlock;
      if (CurrNode->Prior)
        m_priorid = CurrNode->Prior->IdBlock;
      m_typeTfs = CurrNode->WorkShape->TypeShape;
      ws_cnt = WS->WorkShapesCount;

      s_tfs.ID = m_blockid;
      s_tfs.TypeID = m_typeTfs;
      s_tfs.StartPointX = m_start_x;
      s_tfs.StartPointY = m_start_y;
      s_tfs.OffsetX = m_offset_x;
      s_tfs.OffsetY = m_offset_y;
      s_tfs.NextID = m_nextid;
      s_tfs.PriorID = m_priorid;
      s_tfs.TFECount = ws_cnt;
      FileWrite(HF, &s_tfs, sizeof(s_tfs));

      for (int j = 0; j <= ws_cnt - 1; j++ )
      {
         memset(&s_tfe, 0, sizeof(s_tfe));
         ShapeTFE = static_cast<TBaseShape*>(WS->GetWorkShape(j));
         s_tfe.ID = ShapeTFE->ID;
         s_tfe.TypeID = ShapeTFE->TypeShape;
         SaveParamAlternateToBin(ShapeTFE, s_tfe, HF);
      }
   }

   an_count = AncestorList->Count;
   FileWrite(HF, &an_count, sizeof(an_count));
   for (int i = 0; i <= an_count - 1; i++)
   {
     memset(&s_ancs, 0, sizeof(s_ancs) );
     CurrAncestor = static_cast<TNodeAncestor*>(AncestorList->Items[i]);
     s_ancs.IdBlock = CurrAncestor->IdBlock;
     s_ancs.IdShapeAncestor = CurrAncestor->IdShapeAncestor;
     FileWrite(HF, &s_ancs, sizeof(s_ancs));
   }

   al_count = AlternateList->Count;
   FileWrite(HF, &al_count, sizeof(al_count));
   for(int i = 0; i <= al_count - 1; i++ )
   {
      memset(&s_alt, 0, sizeof(s_alt));
      CurrAlt = static_cast<TNodeAlt*>(AlternateList->Items[i]);
      s_alt.ID = CurrAlt->ID;
      s_alt.Num = CurrAlt->Num;
      m_nextid = m_priorid = -1;
      if (CurrAlt->NodeStart)
        m_nextid = CurrAlt->NodeStart->WorkShape->BlockId;
      if (CurrAlt->NodeEnd)
        m_priorid = CurrAlt->NodeEnd->WorkShape->BlockId;

      s_alt.NodeStartID = m_nextid;
      s_alt.NodeEndID = m_priorid;

      m_parentShapeID = 0;
      if (CurrAlt->NodeStart)
        m_parentShapeID = CurrAlt->NodeStart->IdParentShape;

      TL->Clear();
      CurrNode = SearchFirstNodeToAlternate(CurrAlt->ID, CurrAlt->Num, m_parentShapeID);
      while (CurrNode)
      {
         TL->Add(CurrNode);
         CurrNode = SearchNextNodeToAlternate(CurrAlt->ID, CurrAlt->Num, CurrNode);
      }
      item_count = TL->Count;
      s_alt.Count = item_count;
      FileWrite(HF, &s_alt, sizeof(s_alt));

      for (int  j = 0; j <= item_count - 1; j++ )
      {
        CurrNode = static_cast<TNodeMain*>(TL->Items[j]);
        int m_Block = CurrNode->WorkShape->BlockId;
        FileWrite(HF, &m_Block, sizeof(m_Block));
      }
   }
   delete TL;
   SaveOgrSovmToBin(AOgrSovm, HF);
   FileWrite(HF, &ATypeParam, sizeof(ATypeParam));
   SaveTypeDecisionToBin(HF);
   FileClose(HF);
}


void TListNode::SaveOgrSovmToXML(TDischargedMassiv* AOgrSovm, TGlsXmlElement *AElement)
{
  Variant V;
  bool Actual;
  TGlsXmlElement  *xml_item;
  int rc = AOgrSovm->HiCol();
  int rw = AOgrSovm->HiRow();
  for (int i = 0; i <= rw; i++)
  {
    for(int j = 0; j <= rc; j++)
    {
      V = AOgrSovm->ActualValue(i, j, Actual);
      if (Actual)
      {
         xml_item = new  TGlsXmlElement("OGR");
         xml_item->SetAttribute("Row", i);
         xml_item->SetAttribute("Col", j);
         xml_item->SetAttribute("Value", VarToInteger(V));
         AElement->LinkEndChild(xml_item);
      }

    }
  }
}

void TListNode::SaveTypeDecision(TGlsXmlElement *AElement)
{
  int m_type = opt_sadacha->type_sadacha;
  TGlsXmlElement* xml_item = new  TGlsXmlElement("Params");
  AElement->LinkEndChild(xml_item);
  AElement->SetAttribute("Type", m_type);
  if (opt_sadacha->type_ogr > 3)
	AElement->SetAttribute("Sovm", 1);
  else
	AElement->SetAttribute("Sovm", 0);
  switch(m_type)
  {
    case ZAD_1:
      if (opt_sadacha->CheckBox7->Checked)
        xml_item->SetAttribute("V", 1);
      else
        xml_item->SetAttribute("V", 0);
      if (opt_sadacha->CheckBox8->Checked)
        xml_item->SetAttribute("T", 1);
      else
        xml_item->SetAttribute("T", 0);
      xml_item->SetAttribute("VD", opt_sadacha->Vd.c_str());
      xml_item->SetAttribute("TD", opt_sadacha->Td.c_str());
      break;

    case ZAD_2:
      if (opt_sadacha->CheckBox7->Checked)
        xml_item->SetAttribute("V", 1);
      else
        xml_item->SetAttribute("V", 0);
      if (opt_sadacha->CheckBox8->Checked)
        xml_item->SetAttribute("B", 1);
      else
        xml_item->SetAttribute("B", 0);
      xml_item->SetAttribute("VD", opt_sadacha->Vd.c_str());
      xml_item->SetAttribute("BD", opt_sadacha->Bd.c_str());
      break;

    case ZAD_3:
      if (opt_sadacha->CheckBox7->Checked)
        xml_item->SetAttribute("B", 1);
      else
        xml_item->SetAttribute("B", 0);
      if (opt_sadacha->CheckBox8->Checked)
        xml_item->SetAttribute("T", 1);
      else
        xml_item->SetAttribute("T", 0);
      xml_item->SetAttribute("BD", opt_sadacha->Bd.c_str());
      xml_item->SetAttribute("TD", opt_sadacha->Td.c_str());
      break;

    case ZAD_4:
      xml_item->SetAttribute("C1", opt_sadacha->c1.c_str());
      xml_item->SetAttribute("C2", opt_sadacha->c2.c_str());
      xml_item->SetAttribute("C3", opt_sadacha->c3.c_str());
      break;

    case ZAD_5:
      xml_item->SetAttribute("C1", opt_sadacha->c1.c_str());
      xml_item->SetAttribute("C2", opt_sadacha->c2.c_str());
      xml_item->SetAttribute("C3", opt_sadacha->c3.c_str());
      break;

    case ZAD_6:
      xml_item->SetAttribute("C1", opt_sadacha->c1.c_str());
      xml_item->SetAttribute("C2", opt_sadacha->c2.c_str());
      xml_item->SetAttribute("C3", opt_sadacha->c3.c_str());
      break;
  }

}

void TListNode::SaveOgrSovmToBin(TDischargedMassiv* AOgrSovm, THandle AFile)
{
  Variant V;
  bool Actual;
  struct s_ogr
  {
     int Row;
     int Col;
     int Value;
  };
  TDynamicArray* D = new TDynamicArray;
  int rc = AOgrSovm->HiCol();
  int rw = AOgrSovm->HiRow();
  for (int i = 0; i <= rw; i++)
  {
    for(int j = 0; j <= rc; j++)
    {
      V = AOgrSovm->ActualValue(i, j, Actual);
      if (Actual)
      {
         s_ogr* tmp = new s_ogr;
         tmp->Row = i;
         tmp->Col = j;
         tmp->Value = VarToInteger(V);
         D->Append(tmp);
      }

    }
  }
  int m_cnt = D->Count;
  FileWrite(AFile, &m_cnt, sizeof(m_cnt));
  for (int i = 0; i <= m_cnt - 1; i++)
  {
     s_ogr* tmp = static_cast<s_ogr*>(D->Items[i]);
     FileWrite(AFile, tmp, sizeof(s_ogr));
  }
  for (int i = 0; i <= m_cnt - 1; i++)
  {
     s_ogr* tmp = static_cast<s_ogr*>(D->Items[i]);
     delete tmp;
  }

  delete D;
}

void TListNode::SaveTypeDecisionToBin(THandle AFile)
{
  int data;
  double atr;
  int m_type = opt_sadacha->type_sadacha;
  int m_sovm = 0;
  if (opt_sadacha->type_ogr > 3)
	m_sovm = 1;
  FileWrite(AFile, &m_type, sizeof(m_type));
  FileWrite(AFile, &m_sovm, sizeof(m_sovm));
  switch(m_type)
  {
	case ZAD_1:

	  if (opt_sadacha->CheckBox7->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  if (opt_sadacha->CheckBox8->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  atr = atof(opt_sadacha->Vd.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));

	  atr = atof(opt_sadacha->Td.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;

	case ZAD_2:
	  if (opt_sadacha->CheckBox7->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  if (opt_sadacha->CheckBox8->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  atr = atof(opt_sadacha->Vd.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));

	  atr = atof(opt_sadacha->Bd.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;

	case ZAD_3:
	  if (opt_sadacha->CheckBox7->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  if (opt_sadacha->CheckBox8->Checked)
		data = 1;
	  else
		data = 0;
	  FileWrite(AFile, &data, sizeof(data));

	  atr = atof(opt_sadacha->Bd.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));

	  atr = atof(opt_sadacha->Td.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;

	case ZAD_4:
	  atr = atof(opt_sadacha->c1.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c2.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c3.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;

	case ZAD_5:
	  atr = atof(opt_sadacha->c1.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c2.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c3.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;

	case ZAD_6:
	  atr = atof(opt_sadacha->c1.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c2.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  atr = atof(opt_sadacha->c3.c_str());
	  FileWrite(AFile, &atr, sizeof(atr));
	  break;
  }
}







