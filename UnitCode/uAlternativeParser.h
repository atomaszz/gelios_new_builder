//---------------------------------------------------------------------------

#ifndef uAlternativeParserH
#define uAlternativeParserH

#include "uTreeList.h"
#include "uDynamicArray.h"
#include "uAlternativeParserGrp.h"
//---------------------------------------------------------------------------
class TAlternativeParserItemBig;
class TAlternativeParserItemBase
{
   private:
     int f_NumAlt;
     TMainTreeList* f_MainTree;
     TAlternativeParserItemBig *f_OwnerBig;
   public:
     TAlternativeParserItemBase();
     virtual int Who() {return -1;}
     virtual ~TAlternativeParserItemBase();
     __property TMainTreeList* MainTreeList = {read = f_MainTree, write = f_MainTree};
     __property TAlternativeParserItemBig* OwnerBig = {read = f_OwnerBig, write = f_OwnerBig};
     __property int NumAlt = {read = f_NumAlt, write = f_NumAlt};
};


class TAlternativeParserItemList
{
   private:
     TList* f_List;
     void FreeList();
     int __fastcall GetCount();
     TAlternativeParserItemBase* __fastcall GetItems(int AIndex);
   public:
      TAlternativeParserItemList();
      ~TAlternativeParserItemList();
      void Append(TAlternativeParserItemBase* AItem);
      __property int Count = {read = GetCount};
      __property TAlternativeParserItemBase* Items[int AIndex] = {read = GetItems};
};

class TAlternativeParserItemTFE
{
    private:
      TTreeListItem* f_TFE;
      TAlternativeParserItemBig* f_Big;
      void __fastcall SetTFE(TTreeListItem* ATFE);
    public:
      TAlternativeParserItemTFE();
      ~TAlternativeParserItemTFE();
      __property TTreeListItem*  TFE = {read = f_TFE, write = SetTFE};
      __property TAlternativeParserItemBig*  Big = {read = f_Big};
};

class TAlternativeParserItemTFS: public TAlternativeParserItemBase
{
    private:
      TTreeListTFS* f_TFS;
      TList *f_List;
      void FreeList();
      void __fastcall SetTFS(TTreeListTFS* ATFS);
      int __fastcall GetTFECount();
      TAlternativeParserItemTFE* __fastcall GetTFEItems(int AIndex);
    public:
      TAlternativeParserItemTFS();
      ~TAlternativeParserItemTFS();
      int Who() {return 0;}
      __property TTreeListTFS* TFS = {read = f_TFS, write = SetTFS};
      __property int TFECount = {read = GetTFECount};
      __property TAlternativeParserItemTFE* TFEItems[int AIndex] = {read = GetTFEItems};

};


class TAlternativeParserItemBig: public TAlternativeParserItemBase
{
    private:
      bool f_Check;
      bool f_BadBasis;
      int f_Enlarge;
      bool f_EnlargeSetNum;
      TList *f_List;
      TDynamicArray *f_Basis;
      bool f_Cross;
      void FreeList();
      TAlternativeParserItemList* f_MainList;
      TAlternativeParserItemTFE* f_ParentTFE;
      int __fastcall GetCountBig();
      TAlternativeParserItemBig* __fastcall GetItemsBig(int AIndex);
      int __fastcall GetBasisCount();
      TTreeListTFS* __fastcall GetBasisItems(int AIndex);
      TTreeListTFS* FirstFromBasis();
      TTreeListTFS* LastFromBasis();
    public:
      TAlternativeParserItemBig();
      ~TAlternativeParserItemBig();
      int Who() {return 1;}
      void BasisClear();
      void BasisAdd(TTreeListTFS* ATFS);
      void FillBasisFromGrpItemList(TAlternativeParserGrpItemList* AList);
      void FillBasisAlternateTreeList(TAlternateTreeList* ALT);
      void FillBasisFromEnlarge(TAlternativeParserGrpCrossItemEnlarge* AEnl);
      bool CompareBasisAndAlternateTreeList(TAlternateTreeList *AList);
      bool CompareBasisAndMassiv(TDynamicArray *AMass);
      bool IsTailAlternateTreeList(TAlternateTreeList *AList);
      void AddBig(TAlternativeParserItemBig* ABig);
      void GetTreeListTFSFromBasis(TAlternateTreeList* Alternative,
        TDynamicArray *D, bool &AValid);
      void GetAllFirstBigsNoCheck(TDynamicArray *AMass);
      void HookBasisBig();
      __property TAlternativeParserItemList* MainList = {read = f_MainList};
      __property int BasisCount = {read = GetBasisCount};
      __property TTreeListTFS* BasisItems[int AIndex] = {read = GetBasisItems};
      __property int CountBig = {read = GetCountBig};
      __property TAlternativeParserItemBig* ItemsBig[int AIndex] = {read = GetItemsBig};
      __property bool Check = {read = f_Check, write = f_Check};
      __property TAlternativeParserItemTFE* ParentTFE = {read = f_ParentTFE, write = f_ParentTFE};
      __property bool Cross = {read = f_Cross, write = f_Cross};
      __property bool BadBasis = {read = f_BadBasis, write = f_BadBasis};
      __property int Enlarge = {read = f_Enlarge, write = f_Enlarge};
      __property bool EnlargeSetNum = {read = f_EnlargeSetNum, write = f_EnlargeSetNum};
};



class TAlternativeParser
{
    private:
      TList* f_ListEnlarge;
      TAlternativeParserGrp* f_Grp;
      TAlternativeParserItemBig *f_Head;
      void FreeHead();
      void CreateHead();
      void DoMakeAlternative();
      void DoParse(TMainTreeList* AMainTree);
      void MakeBig(TAlternativeParserItemBig *ABig, bool AByPass);
      void FillBigFromGrp(TAlternativeParserItemBig *ABig);
      void CreateParserGrpItemList(TDynamicArray *AMass, TAlternateTreeList* Alternative);
      void CrossToBigs(TAlternativeParserGrpCrossItem* ACrossItem, TAlternativeParserItemBig *ABig);
      void FillItemGrp(TAlternativeParserGrpItemBase* AItem, TAlternativeParserItemBig *ABig );
      bool CheckEnlarge(TAlternativeParserItemBig* ABig);

    public:
      TAlternativeParser();
      ~TAlternativeParser();
      void Parse(TMainTreeList* AMainTree);
      __property TAlternativeParserItemBig* Head = {read = f_Head};
};
#endif
