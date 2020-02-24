//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGraphTFEConvertor.h"
#include "uAlternativeParser.h"
#include "uCommonGraph.h"
#include "uGraphTFEConvertorTransNum.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
TGlsList *lcList;
void InitTFEConvertor()
{
   lcList = new TGlsList;
}

void FreeTFEConvertor()
{
   delete lcList;
}

int ParentID(TPredicateItemBase* AItem)
{
   if (!AItem->EnvelopeBIG)
     return 0;
   if (AItem->EnvelopeBIG->Rfc)
   {
     TAlternativeParserItemTFE* ITE = AItem->EnvelopeBIG->Rfc->ParentTFE;
     if (ITE)
       return ITE->TFE->BaseShape->ID;
   }
   return AItem->EnvelopeBIG->ID;

}


TGraphTFEConvertorItem::TGraphTFEConvertorItem()
{
  f_Out = "";
  f_Item = NULL;
  f_Parent = NULL;
}

void TGraphTFEConvertorItem::Make(TPredicateItemBase* AItem, TPredicateItemBig* AParent)
{
   f_Item = AItem;
   f_Parent = AParent;
   DoMake();
}

int __fastcall TGraphTFEConvertorItem::GetParentID()
{
   if (!f_Parent)
     return 0;
   if (f_Parent->Rfc)
   {
     TAlternativeParserItemTFE* ITE = f_Parent->Rfc->ParentTFE;
     if (ITE)
       return ITE->TFE->BaseShape->ID;
   }
   return f_Parent->ID;
}

TBaseShape* __fastcall TGraphTFEConvertorItem::GetParentBaseShape()
{
   if (!f_Parent)
     return NULL;
   if (f_Parent->Rfc)
   {
     TAlternativeParserItemTFE* ITE = f_Parent->Rfc->ParentTFE;
     if (ITE)
       return ITE->TFE->BaseShape;
   }
   return NULL;
}


AnsiString __fastcall TGraphTFEConvertorItem::GetAlias()
{
   AnsiString Res = "";
   int mType = f_Item->Who();
   if (mType == 1 )
     return "rab_oper";
   if (mType == 2)
     return "rab_oper_posl";
   mType = dynamic_cast<TPredicateItemTFS*>(f_Item)->TFS->BaseWorkShape->TypeShape;
   switch (mType)
   {
     case 1:
     {
       Res = "rab_oper";
       break;
     }
     case 2:
     {
        Res = "rab_oper_par_AND";
        break;
     }
     case 3:
     {
        Res = "rab_oper_par_OR";
        break;
     }

     case 4:
     {
        Res = "diagn_control_rab";
        break;
     }
     case 5:
     {
        Res = "diagn_func_coltrol";
        break;
     }
     case 6:
     {
        Res = "rasvilka";
        break;
     }

     case 7:
     {
        Res = "proverka_if";
        break;
     }

     case 8:
     {
        Res = "while_do_control_rab";
        break;
     }

     case 9:
     {
        Res = "do_while_do_control_rab";
        break;
     }

     case 10:
     {
        Res = "do_while_do_control_func";
        break;
     }


     case 11:
     {
        Res = "proverka_uslovia";
        break;
     }
  }
   return Res;
}

void TGraphTFEConvertorItem::ListIDFromTFE(TDynamicArray* AL)
{
   f_Item->ListIDFill(AL);
}


AnsiString TGraphTFEConvertorItem::ListIDFromTFE()
{
   int n, cnt;
   AnsiString Res = "";
   TDynamicArray *D = new TDynamicArray;
   f_Item->ListIDFill(D);
   cnt = D->Count;
   for (int i = 0; i <= cnt - 1; i++)
   {
      n = D->Position[i]->Int_Value;
      Res = Res + IntToStr(n);
      if ( (i != cnt - 1) && (cnt > 1) )
        Res = Res + ", ";
   }
   delete D;
   return Res;
}

void TGraphTFEConvertorItem::DoMake()
{
   f_Out = "";
   if (f_Item)
   {
      f_Out = "knot(" + IntToStr(GetParentID()) + "," +  IntToStr(f_Item->NumAlt + 1) +", ";
      f_Out = f_Out + GetAlias() +", " + "[" + ListIDFromTFE() + "]).";
   }
}

//------------TGraphTFEConvertor-----------------------------------------------
int CompareNum(int A, int AN, int B, int BN, bool AMinus)
{
   if (A == B)
   {
     if (AN > BN)
       return 1;
     if (AN < BN)
       return -1;
   }
   if (AMinus)
   {
     if (A > B)
       return -1;
     if (A < B)
       return 1;
   }
   else
   {
     if (A > B)
       return 1;
     if (A < B)
       return -1;
   }
   return 0;
}

int CompareNode(void* A, void* B)
{
   TPredicateItemBase* m_A = static_cast<TPredicateItemBase*>(A);
   TPredicateItemBase* m_B = static_cast<TPredicateItemBase*>(B);
   int A_ID = ParentID(m_A);
   int B_ID = ParentID(m_B);
   int ANum = Sign(A_ID);
   int BNum = Sign(B_ID);
   if ((A_ID > 0) || (B_ID > 0))
   {
     if((A_ID > 0) && (B_ID > 0))
     {
       if ( A_ID > B_ID )
         return 1;
       else
         return -1;
     }
     return 1;
   }
   else
    return CompareNum(A_ID, m_A->NumAlt, B_ID, m_B->NumAlt, ((ANum <= 0) && (BNum <= 0)));
}

bool acp(void* A)
{
   lcList->append(A);
   return true;
}

TGraphTFEConvertor::TGraphTFEConvertor()
{
   f_Item = new TGraphTFEConvertorItem;
   f_BTree = new TGlsBinaryTree(CompareNode);
   f_Tran = new TGraphTFEConvertorTransNum;
}


TGraphTFEConvertor::~TGraphTFEConvertor()
{
   delete f_Item;
   delete f_BTree;
   delete f_Tran;
}


void TGraphTFEConvertor::PushTFS(TPredicateItemTFS *ATFS, TDynamicArray *AStack)
{
   int m_type = ATFS->TFS->BaseWorkShape->TypeShape;
   if ( (m_type != 1) || ( (m_type == 1) && (ATFS->EnvelopeBIG) ) )
     AStack->InsertToFirst(ATFS);
   for (int i = 0; i <= ATFS->TFECount - 1; i++)
     if (ATFS->TFEItems[i]->Big)
       AStack->InsertToFirst(ATFS->TFEItems[i]->Big);
}

void TGraphTFEConvertor::PushBig(TPredicateItemBig *ABig, TDynamicArray *AStack)
{
   if (ABig->Envelope)
   {
     TPredicateItemBase* B = ABig->Items[0];
     B->EnvelopeBIG = ABig;
     int m_who = B->Who();
     if ( (m_who == 2) || (m_who == 1) )
       AStack->InsertToFirst(B);
     if (m_who == 0)
       PushTFS(dynamic_cast<TPredicateItemTFS*>(B), AStack);
   }
   else
     AStack->InsertToFirst(ABig);
}

void TGraphTFEConvertor::PushPWork(TPredicateItemPWork *APWork, TDynamicArray *AStack)
{
    AStack->InsertToFirst(APWork);
}



void TGraphTFEConvertor::CheckParseItem(TPredicateItemBase *ABase, TDynamicArray *AStack)
{
   int m_type;
   TPredicateItemPWork *m_PW;
   if (ABase)
   {
     m_type = ABase->Who();
     if ( m_type == 0 )
       PushTFS(dynamic_cast<TPredicateItemTFS*>(ABase), AStack);
     if ( m_type == 1 )
       PushBig(dynamic_cast<TPredicateItemBig*>(ABase), AStack);
     if ( m_type == 2 )
       PushPWork(dynamic_cast<TPredicateItemPWork*>(ABase), AStack);
   }
}


TPredicateItemBig* TGraphTFEConvertor::DoPrintBig(TPredicateItemBig* ABig, TDynamicArray *AStack)
{
   TPredicateItemBig* Res = NULL;
   TPredicateItemBase *m_Base;
   if (!ABig->Envelope)
   {
     if (!ABig->Rfc->ParentTFE && ABig->Print)
       Res = ABig;
     int m_cnt  = ABig->Count;
     for (int i = 0 ; i <= m_cnt -1; i++)
     {
       m_Base = ABig->Items[i];
       m_Base->EnvelopeBIG = ABig;
       CheckParseItem(m_Base, AStack);
     }
   }
   return Res;
}


AnsiString TGraphTFEConvertor::PrintBig(TPredicateItemBig* ABig, TDynamicArray *AStack)
{
   AnsiString Res = "";
   TPredicateItemBase *m_Base;
   if (!ABig->Envelope)
   {
     if (!ABig->Rfc->ParentTFE && ABig->Print)
     {
       f_Item->Make(ABig, ABig->EnvelopeBIG);
       Res = f_Item->OutString;
     }
     int m_cnt  = ABig->Count;
     for (int i = 0 ; i <= m_cnt -1; i++)
     {
       m_Base = ABig->Items[i];
       m_Base->EnvelopeBIG = ABig;
       CheckParseItem(m_Base, AStack);
     }
   }
   return Res;
}

TPredicateItemPWork* TGraphTFEConvertor::DoPrintPWork(TPredicateItemPWork* APWork, TDynamicArray *AStack)
{
   CheckParseItem(APWork->Item1, AStack);
   CheckParseItem(APWork->Item2, AStack);
   return APWork;
}


AnsiString TGraphTFEConvertor::PrintPWork(TPredicateItemPWork* APWork, TDynamicArray *AStack)
{
   AnsiString Res = "";
   f_Item->Make(APWork, APWork->EnvelopeBIG);
   Res = f_Item->OutString;
   CheckParseItem(APWork->Item1, AStack);
   CheckParseItem(APWork->Item2, AStack);
   return Res;
}


TPredicateItemBase* TGraphTFEConvertor::DoParseItem(TPredicateItemBase* ABase,
  TDynamicArray *AStack)
{
   TPredicateItemBase *Res = NULL;
   int m_who = ABase->Who();
   if (m_who == 1)
   {
     TPredicateItemBig* m_Big = dynamic_cast<TPredicateItemBig*>(ABase);
     Res = DoPrintBig(m_Big, AStack);
   }
   if (m_who == 2)
   {
     TPredicateItemPWork* m_PW = dynamic_cast<TPredicateItemPWork*>(ABase);
     Res = DoPrintPWork(m_PW, AStack);
   }
   if (m_who == 0)
     Res = ABase;
   return Res;
}


AnsiString TGraphTFEConvertor::ParseItem(TPredicateItemBase* ABase,
  TDynamicArray *AStack)
{
   AnsiString Res;
   TPredicateItemBase *m_Base;
   int m_who = ABase->Who();
   if (m_who == 1)
   {
     TPredicateItemBig* m_Big = dynamic_cast<TPredicateItemBig*>(ABase);
     Res = PrintBig(m_Big, AStack);
   }
   if (m_who == 2)
   {
     TPredicateItemPWork* m_PW = dynamic_cast<TPredicateItemPWork*>(ABase);
     Res = PrintPWork(m_PW, AStack);
   }

   if (m_who == 0)
   {
      f_Item->Make(ABase, ABase->EnvelopeBIG);
      Res = f_Item->OutString;
   }
   return Res;
}

void TGraphTFEConvertor::MakeElementTFS(TPredicateItemTFS *ATFS)
{
   int n, m_who;
   TBaseShape *B;
   AnsiString S;
   TDynamicArray* D = new TDynamicArray;
   TBaseWorkShape* WS = ATFS->TFS->BaseWorkShape;
   ATFS->ListIDFill(D);
   for (int i = 0; i <= D->Count - 1; i++)
   {
     n = D->Position[i]->Int_Value;
     B = WS->ShapeSupportID(n);
     m_who = B->TypeShape;
     S = B->Make_One_Simple();
     if (S.Length() > 0)
     {
       if (m_who == 5)
         f_PrRab = f_PrRab + S + "\r\n";
       if (m_who == 6)
         f_PrControlRab = f_PrControlRab + S + "\r\n";
       if (m_who == 7)
         f_PrControlFunc = f_PrControlFunc + S + "\r\n";
       if (m_who == 8)
         f_PrCheckCondition = f_PrCheckCondition + S + "\r\n";
     }


   }
   delete D;

}


void TGraphTFEConvertor::MakeElement(TPredicateItemBase* AElement)
{
   int m_who = AElement->Who();
   if (m_who == 1)
   {
     //throw(Exception("недопустимое использование MakeElement(TPredicateItemBase* AElement). Обратитесь с этой ошибкой к разработчикам!"));
   }
   if (m_who == 2)
   {
     TPredicateItemPWork* m_PW = dynamic_cast<TPredicateItemPWork*>(AElement);
     MakeElement(m_PW->Item1);
     MakeElement(m_PW->Item2);
   }
   if (m_who == 0)
   {
      TPredicateItemTFS* m_TFS = dynamic_cast<TPredicateItemTFS*>(AElement);
      MakeElementTFS(m_TFS);
   }
}

void TGraphTFEConvertor::AddElementToTree(TPredicateTree*  APredicateTree)
{
   TPredicateTreeItem* N = APredicateTree->NewPredicateTreeItem();
   N->ParentID = f_Item->ParentID;
   N->ParentShape = f_Item->ParentBaseShape;
   N->NumAlt = f_Item->Item->NumAlt + 1;
   int m_type, m_who = f_Item->Item->Who();
   m_type = -1;
   if (m_who == 0)
   {
     N->BaseWorkShape = dynamic_cast<TPredicateItemTFS*>(f_Item->Item)->TFS->BaseWorkShape;
     m_type =  N->BaseWorkShape->TypeShape;
   }
   if (m_who == 1 )
     m_type = 12;
   if (m_who == 2)
     m_type = 13;
   N->TypeWorkShape = m_type;

   TDynamicArray *D = new TDynamicArray;
   f_Item->Item->ListIDFill(D);
   int cnt = D->Count;
   for (int i = 0; i <= cnt - 1; i++)
     N->AddBaseShape(static_cast<TBaseShape*>(D->Position[i]->P), D->Position[i]->Int_Value);
   delete D;
}

void TGraphTFEConvertor::Init(TPredicateItemBig* AHead, TPredicateTree* APredicateTree)
{
   AnsiString SC;
   bool pass;
   TPredicateItemBase *Base, *NC;
   f_PrStruct = "";
   f_PrRab = "";
   f_PrControlRab = "";
   f_PrControlFunc = "";
   f_PrCheckCondition = "";
   TDynamicArray *m_Stack = new TDynamicArray;
   m_Stack->InsertToFirst(AHead);
   Base = static_cast<TPredicateItemBase*>(m_Stack->Pop());
   while(Base)
   {
     NC = DoParseItem(Base, m_Stack);
     if (NC)
       f_BTree->insert(NC);
/*
      f_Item->Make(NC, NC->EnvelopeBIG);
      SC = f_Item->OutString;
      if (SC.Length() > 0)
         f_PrStruct = f_PrStruct + SC + "\r\n";

*/
     Base = static_cast<TPredicateItemBase*>(m_Stack->Pop());
   }
   delete m_Stack;


   lcList->clear();
   f_BTree->inorder(acp);
   lcList->first();
   for (int i = 0; i <= lcList->length() - 1; i++)
   {
      Base = static_cast<TPredicateItemBase*>(lcList->val());
      f_Item->Make(Base, Base->EnvelopeBIG);
      SC = f_Item->OutString;
      if (SC.Length() > 0)
      {
         f_PrStruct = f_PrStruct + SC + "\r\n";
         MakeElement(Base);
         if (APredicateTree)
           AddElementToTree(APredicateTree);
      }
    //  MakeElement(Base);
    //  f_Tran->AddGTItem(f_Item);
      lcList->next();
   }
  // f_TextRecalc = f_Tran->Make();

}

