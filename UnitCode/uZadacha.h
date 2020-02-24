//---------------------------------------------------------------------------

#ifndef uZadachaH
#define uZadachaH
//---------------------------------------------------------------------------
#include "uPredicateTree.h"
#include "uDynamicArray.h"
#include "uPartialDecision.h"
#include "uPredicateScanner.h"
#include "uPredicateTrackCreator.h"
#include "uPredicatePath.h"

class TZadacha
{
   private:
     double f_TMax;
     double f_VMax;
     AnsiString f_OptB;
     AnsiString f_OptT;
     AnsiString f_OptV;
     AnsiString f_Sostav;
     int f_Cnt_alt;
     int f_CntComm;
     bool f_CheckNud;
     TPredicateTree* f_Tree;
     TDynamicArray* f_Equal;
     TPartialDecision* f_PartialDecision;
     TList *f_ListPTI;
     TDischargedMassiv* ozenk_t;
     TDischargedMassiv* ozenk_v;
     AnsiString f_FullPredcateModel;

     void DoEqual();
     void SavePredicateModelToTempFile();
     bool CheckCanDecision(int &AID);
     bool CheckPLGParamAlternative(TParamAlternative* AL);
     bool CheckCanPLGDecision(int &AID);
     void ChekDeleted(TPredicateTreeItem* AI);
     void get_opt_alt();
     void get_opt_alt_fuz();
     void Nud_podgot();
     double ozenk_t_min(TBaseShape* B);
     double ozenk_v_min(TBaseShape* B);
     void ClearPTI();
     void AddPTI(TPredicateTreeItem* AItem);
     TPredicateTreeItem* __fastcall GetPTI(int AIndex);
     int __fastcall GetCountPTI(){return f_ListPTI->Count;}
     AnsiString DoCheckEqualTree();
     AnsiString DoCheckLogic();
     AnsiString DoCheckLogicItemUP(TPredicateScannerItemKnot* AKnot, int AID);
     AnsiString DoCheckLogicItemDown(TPredicateScannerItemKnot* AKnot, int AID);
     TPredicateTreeItem* FindToTree(TPredicateScannerItemKnot* AKnot);
     TPredicateScannerItemKnot*  FindToScanner(TPredicateTreeItem* AItem);
     double Get_V_Min(TPredicateTreeItem* ATI, int AIndex);
     double Get_T_Min(TPredicateTreeItem* ATI, int AIndex);
     bool PtiToOgrSovm(TPredicateTreeItem* APTI);
     TPredicateTreeItem* FindUpperNodeForOgrSovm();
   public:
     TPredicateScanner *Scanner;
     TPredicateTrackCreator *TrackCreator;
     bool OptOgrSovm;
     TOgrSovmArray *FOgrSovmArray;

     TZadacha();
     ~TZadacha();
     void Clear();
     void Init(int AType_Char, bool ACheckNud, bool AOptOgrSovm, TOgrSovmArray *AOgrSovmArray, AnsiString AFullPredcateModel);
     void Process();
     AnsiString Check();
     AnsiString CheckTrack();
     AnsiString Track();
     AnsiString AcceptTrackFromScanner();
     bool CheckOzenk_TFE_v(TPredicateTreeItem* ATI, double AValue);
     bool CheckOzenk_TFE_t(TPredicateTreeItem* ATI, double AValue);
     void ShowDecision(TColor AColorAlt, TColor AColorBadAlt, unsigned int ATime, TPredicatePathItem* APredicatePathItem);
     void Ozenk_TFEStill(double &AOzenk0, double &AOzenk1);
     void Ozenk_TFE();
     void LoadPredicateTrackCreatorItem(TPredicateTrackCreatorItem* AItem);
     __property TPredicateTree* Tree = {read = f_Tree};
     __property TPredicateTreeItem* PTI[int AIndex] = {read = GetPTI};
     __property int CountPTI = {read = GetCountPTI};

};
#endif
