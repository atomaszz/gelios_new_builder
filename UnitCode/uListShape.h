//---------------------------------------------------------------------------

#ifndef uListShapeH
#define uListShapeH
#include "uBaseWorkShape.h"
#include "uStackDust.h"
#include "uGlsXml.h"
#include "uDynamicArray.h"
#include "uCommonGraph.h"
#include "uDischargedMassiv.h"

//------------------------------------------------------------------------------
typedef void __fastcall (__closure *TListChange)();
class TListNode;
class TStackDustController;
class TAltInfo;



class TNodeMain
{
  public:
    int IdAlternate;
    int IdBlock;
    int IdParentShape;
    int NumAlt;
    int TypeCreate;
    TBaseWorkShape *WorkShape;
    TNodeMain *Next;
    TNodeMain *Prior;
    TNodeMain();
    ~TNodeMain();
};

class  TNodeAncestor
{
  public:
    int IdBlock;
    int IdShapeAncestor;
    TNodeAncestor();
};

class TNodeAlt
{
  public:
    int ID;
    int Num;
    TNodeMain* NodeStart;
    TNodeMain* NodeEnd;
    TNodeAlt();
};

class TNodeSearch
{
   public:
     int UID;
     TList* List;
     int indexFindChild;
     TNodeSearch();
     ~TNodeSearch();

};

class TNodeSearchController
{
   private:
     TList* List;
     TListNode* MainList;
     void FreeSerchList();
     int FindNextUid();
     TNodeSearch* FindNode(int AUID);
   public:
     TNodeSearchController();
     ~TNodeSearchController();
     void SetMainList(TListNode* AList);
     TBaseWorkShape* FindFirstChild(int AltId, int ANumAlt,  int AIdParentShape, int &AUID);
     TBaseWorkShape* FindNextChild(int AUID);
     bool DisableFind(int AUID);
     void ClearAll();
};


class TPainterList
{
   friend TListNode;
   private:
     TList* List;
     int f_pos;
     int __fastcall GetCount();
   public:
     TPainterList();
     ~TPainterList();
     TBaseWorkShape* First();
     TBaseWorkShape* Next();
     TBaseWorkShape* Prior();
     TBaseWorkShape* Last();
     void ClearAll();
     bool IsExists(TBaseWorkShape* AWS);
     __property int Count = {read  = GetCount};
};

class  TListNode
{
   private:
     bool f_Update;
     bool f_Changes;
     TNodeSearchController *Searcher;
     TList *MainList;
     TList *AncestorList;
     TList *AlternateList;
     bool CheckAlternateNode(int ID, int ANumAlt);
     TListChange FOnListChange;
     TStackDustController* f_StackDustController;


     TNodeAlt* CheckFirstNodeAlt();
     TNodeMain* FindPriorNodeToAlternate(int AltId, TBaseWorkShape* WBefore);

     void FreeListMain();
     void FreeListAncestor();
     void FreeListAlternate();
     int __fastcall GetNodeMaxID();
     int __fastcall GetTFEMaxID();
     int __fastcall GetAlternateMaxID();
     void CheckDeleteAlternate(TBaseWorkShape *AWS);
     TNodeAncestor* IsExistsNodeAncestor(int AIdBlock, int AIdShapeAncestor);
     TNodeAncestor* DoAddNodeAncestor(int AIdBlock, int AIdShapeAncestor);
     int __fastcall GetAlternateCount();
     TNodeAlt* __fastcall GetAlternateItem(int AIndex);
     void SaveParamAlternateToXML(TBaseShape* ATFE, TGlsXmlElement *AElement);
     void SaveParamAlternateToBin(TBaseShape* ATFE, SF_TFE A_tfe, THandle AFile);
     void SaveOgrSovmToXML(TDischargedMassiv* AOgrSovm, TGlsXmlElement *AElement);
     void SaveTypeDecision(TGlsXmlElement *AElement);
     void SaveOgrSovmToBin(TDischargedMassiv* AOgrSovm, THandle AFile);
     void SaveTypeDecisionToBin(THandle AFile);
   public:
     TListNode();
     ~TListNode();
     TNodeMain* FindLastNodeToAlternate(int AltId, int ANumAlt, int AIdParenShape);
     void FillPainterList(TPainterList* PainterList, int AltId, int ANumAlt,  int IdParentShape);
     void AddShapeToList(int AltId, int ANumAlt, TBaseWorkShape *WShape, int IdParentShape);
     void InsertShapeToList(int AltId,  int ANumAlt, TBaseWorkShape* WBefore, TBaseWorkShape *WShape, int IdParentShape);
     int DeleteBlock(int IdBlock);
     void ClearDeleteBlock();
     bool IsContainsChildBlock(int IdBlock);
     bool IsContainsChildShape(int IdShape);
     TNodeMain* FindNode(int IdBlock, int &pos);
     TNodeMain* FindNode(TBaseWorkShape *WShape);
     int FindBlockOutShape(int IdShape);
     TBaseWorkShape* FindFirstChild(int AltId, int ANumAlt, int IdParentShape, int &AUid);
     TBaseWorkShape* FindNextChild(int AUid);
     bool DisableFind(int AUid);
     bool IsFirstWorkShape(TBaseWorkShape *WShape,  int AltId, int ANumAlt, int IdParentShape);
     TBaseWorkShape*  GetLastWorkShape(int AltId, int ANumAlt, int IdParentShape);
     bool IsEmpty();
     int  DecayWorkShape(TBaseWorkShape *WDecay, TBaseWorkShape *WN1, TBaseWorkShape *WN2);
     void FusionWorkShape(TBaseWorkShape *WFusion, TBaseWorkShape *WN1, TBaseWorkShape *WN2);
     TBaseWorkShape*  FindWorkShapeOutBaseShape(TBaseShape* Shape, int &ShapeId);
     TBaseWorkShape*  FindWorkShapeOutBaseShapeID(int ShapeID, TBaseShape** Shape);
     bool CreateAlternate(TBaseWorkShape *WS, TBaseWorkShape *WE, int AID, int ANumAlt);
     int AddAlternate(TBaseWorkShape *WS, TBaseWorkShape *WE, int AID);
     bool AddAlternate(int AID, int ANumAlt);
     int DeleteAlternate(int AID, int ANum);
     TNodeMain* SearchFirstNodeToAlternate(int AltId, int ANumAlt, int IdParentShape);
     TNodeMain* SearchNextNodeToAlternate(int AltId, int ANumAlt, TNodeMain* Node);
     TNodeMain* SearchFirstNodeToAlternate2(int AltId, int IdParentShape);
     TNodeMain* SearchNextNodeToAlternate2(int AltId, TNodeMain* Node);
     TNodeMain* SearchFirstNodeToAlternate3(int AltId, int ANumAlt);
     TNodeMain* SearchNextNodeToAlternate3(int AltId, TNodeMain* Node);


     bool PrepareLinksBeforeDelete(TBaseWorkShape *AWS);
     void FillNodeAncestor(TNodeMain *ANode);


     TBaseWorkShape* FindNextNode(TBaseWorkShape *W);
     TBaseWorkShape* FindPriorNode(TBaseWorkShape *W);
     TNodeMain* FindNextNode2(TBaseWorkShape *W);
     TNodeMain* FindPriorNode2(TBaseWorkShape *W);

     bool CompareWorkShape(TBaseWorkShape **WS, TBaseWorkShape **WE);
     bool GetWSToAlternate(int AId, TBaseWorkShape  **AWSFirst, TBaseWorkShape  **AWSLast);
     void BeginUpdate();
     void EndUpdate();
     void ClearAll();
     void PrepareDeleteWorkShape(TBaseWorkShape *AWS);
     int DeleteWorkShape();
     void SaveAllToFile(AnsiString AFileName, int ATypeParam, TDischargedMassiv* AOgrSovm);
     TNodeMain* CreateNode(TBaseWorkShape *WS);
     TNodeAncestor* CreateNodeAncestor(int AId, int AIdAncestor);
     void PrepareAddNode(TNodeMain *Nd);
     void ClearNodeTypeCreate();
     TNodeAlt*  CheckAlternateWSFirst(TBaseWorkShape *AWS);
     TNodeAlt*  CheckAlternateWSEnd(TBaseWorkShape *AWS);
     void LoadInfoForAlternate(TAltInfo* AltIfo, int AParentShapeID);
     bool GetAlternateInfo(int AShapeID, int &AltID, int &NumAlt, int &IDParent);
     void GetAllWorkShape(TDynamicArray *AMass);
     void SaveAllToFileBin(AnsiString AFileName, int ATypeParam, TDischargedMassiv* AOgrSovm);


     __property TStackDustController* StackDustController = {read = f_StackDustController};
     __property TListChange  OnListChange = {read = FOnListChange, write = FOnListChange};
     __property int NodeMaxID = {read = GetNodeMaxID};
     __property int TFEMaxID = {read = GetTFEMaxID};
     __property int AlternateMaxID = {read = GetAlternateMaxID};
     __property int AlternateCount = {read = GetAlternateCount};
     __property TNodeAlt* AlternateItem[int AIndex] = {read = GetAlternateItem};
     __property bool Changes = {read = f_Changes, write = f_Changes}; 



};



#endif
