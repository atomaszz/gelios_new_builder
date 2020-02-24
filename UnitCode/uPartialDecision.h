//---------------------------------------------------------------------------

#ifndef uPartialDecisionH
#define uPartialDecisionH
#include "uPredicateTree.h"
#include "uParamAlternative.h"
#include "uDischargedMassiv.h"

//---------------------------------------------------------------------------
class TPartialDecision;
class TZadacha;


class TPartialDecisionItem
{
    private:
      TPartialDecision *f_Parent;
      TPredicateTreeItem *f_WorkItem;
      TParamAlternative *f_ParamAlt;
      TParamAlternative *f_Apd;
      void FreeApd();
      void DoDecision();
      void proverka_type_krit(int type_krit);
      void proverka_type_krit_fuz(int type_krit);
      TParamAlternative* GetParamAlternativeByID(int AID);
      void proverka_priblj(double ARate);
      void proverka_priblj_fuz(double ARate);
      void proverka_nud();
      void proverka_nud_fuz();
      void sovm_naz(int ind);
      int GetOptZadachaTypeOgrForNUOpt();
    public:
      TPartialDecisionItem(TPartialDecision *AParent);
      ~TPartialDecisionItem();
      void InitDecision(TPredicateTreeItem *AWorkItem);
      void Make();
      void Proverka_NUOpt();
      __property TPartialDecision* Parent = {read = f_Parent};
      __property TParamAlternative *ParamAlt = {read = f_ParamAlt};
      __property TPredicateTreeItem *WorkItem = {read = f_WorkItem};
};

class TPartialDecision
{
    private:
      bool f_CheckNud;
      int f_Type_Char;
      TList* f_List;
      void FreeList();
      int __fastcall GetCount();
      TPartialDecisionItem* __fastcall GetItems(int AIndex);
    public:
      TZadacha* f_Owner;

      TPartialDecision(TZadacha* AOwner);
      ~TPartialDecision();
      void Clear();
      TPartialDecisionItem* FindPartialDecisionItemByParentID(int AID);
      TPartialDecisionItem* FindPartialDecisionItemByTFEID(int AID);
      TPartialDecisionItem* GetNew(TPredicateTreeItem* APTItem);
      bool FreeItem(TPartialDecisionItem* AItem);
      TPartialDecisionItem* PullAlternate(TPartialDecisionItem* AItem);
      bool CheckOzenk_TFE_t(TPartialDecisionItem* AI, double AValue);
      bool CheckOzenk_TFE_v(TPartialDecisionItem* AI, double AValue);
      
      __property int Type_Char = {read = f_Type_Char, write = f_Type_Char};
      __property bool CheckNud = {read = f_CheckNud, write = f_CheckNud};

      __property int Count = {read = GetCount};
      __property TPartialDecisionItem* Items[int AIndex] = { read =  GetItems};
};

#endif
