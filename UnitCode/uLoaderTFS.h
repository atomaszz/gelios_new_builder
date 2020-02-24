//---------------------------------------------------------------------------

#ifndef uLoaderTFSH
#define uLoaderTFSH
#include "uGlsXml.h"
#include "uCommonGraph.h"
#include "uClipCopyTFS.h"
#include "uDischargedMassiv.h"

//---------------------------------------------------------------------------
class TLoaderTFSItemMain
{
   private:
     int f_Id;
     int f_TypeId;
   public:
     TLoaderTFSItemMain(int AId, int ATypeId);
     ~TLoaderTFSItemMain();
     TList *ListParams;
     __property int Id = {read = f_Id, write = f_Id};
     __property int TypeId = {read = f_TypeId, write = f_TypeId};
};



class TLoaderTFSMain
{
   private:
     int f_Id;
     int f_TypeId;
     TPoint f_StartPoint;
     int f_OffsetX;
     int f_OffsetY;
     int f_NextId;
     int f_PriorId;
     TList *f_List;
     void* f_Tag;
     int f_Tag2;
     void FreeList();
     TLoaderTFSItemMain* __fastcall GetTFEItem(int AIndex);
     int __fastcall GetTFECount();
     int __fastcall GetMinTFE();
   public:
     TLoaderTFSMain();
     ~TLoaderTFSMain();
     TLoaderTFSItemMain* FindTFE(int AId);
     bool AddTFE(int AId, int ATypeID);
     __property int Id = { read = f_Id, write = f_Id};
     __property int TypeId = {read = f_TypeId, write = f_TypeId};
     __property TPoint StartPoint = {read = f_StartPoint, write = f_StartPoint};
     __property int OffsetX = { read = f_OffsetX, write = f_OffsetX};
     __property int OffsetY = { read = f_OffsetY, write = f_OffsetY};
     __property int NextId =  { read = f_NextId, write = f_NextId};
     __property int PriorId = {read = f_PriorId, write = f_PriorId};
     __property TLoaderTFSItemMain*  TFEItems[int AIndex] = { read =  GetTFEItem};
     __property int TFECount = {read = GetTFECount};
     __property void* Tag = {read = f_Tag, write = f_Tag};
     __property int Tag2 = {read = f_Tag2, write = f_Tag2};
     __property int MinTFE = {read = GetMinTFE};



};

class TLoaderTFSAncestor
{
   private:
     int f_IdBlock;
     int f_IdShapeAncestor;
   public:
     TLoaderTFSAncestor(int AIdBlock, int AIdShapeAncestor);
     __property int IdBlock =  { read = f_IdBlock, write = f_IdBlock};
     __property int IdShapeAncestor =  { read = f_IdShapeAncestor, write = f_IdShapeAncestor};
};


class TLoaderTFSItemAlternate
{
   private:
     int f_Id;
   public:
     TLoaderTFSItemAlternate(int AId);
     __property int Id = { read = f_Id, write = f_Id};
};


class TLoaderTFSAlternate
{
   private:
     int f_Id;
     int f_Num;
     int f_NodeStartID;
     int f_NodeEndID;
     TList *f_List;
     void FreeList();
     TLoaderTFSItemAlternate* __fastcall GetAltItem(int AIndex);
     int __fastcall GetAltCount();

   public:
     TLoaderTFSAlternate();
     ~TLoaderTFSAlternate();
     bool AddAlt(int AId);
     __property int Id = { read = f_Id, write = f_Id};
     __property int Num = { read = f_Num, write = f_Num};
     __property int NodeStartID = { read = f_NodeStartID, write = f_NodeStartID};
     __property int NodeEndID = { read = f_NodeEndID, write = f_NodeEndID};
     __property TLoaderTFSItemAlternate*  AltItems[int AIndex] = { read =  GetAltItem};
     __property int AltCount = {read = GetAltCount};

};

class TLoaderTFS
{
   private:
     int f_TypeParam;
     TList *f_ListMain;
     TList *f_ListAlt;
     TList *f_ListAnc;
     String f_ErrorString;
     TDischargedMassiv *f_OgrSovm;
     void FreeMain();
     void FreeAlt();
     void FreeAnc();
     TLoaderTFSMain* __fastcall GetMainNode(int AIndex);
     TLoaderTFSAncestor* __fastcall GetAncestor(int AIndex);
     TLoaderTFSAlternate* __fastcall GetAlternate(int AIndex);
     int __fastcall GetMainNodeCount();
     int __fastcall GetAncestorCount();
     int __fastcall GetAlternateCount();
     bool DoLoad(AnsiString AFileName, TGlsXmlDocument *AXml_dom, TGlsXmlString *AXml_str);
     bool DoLoadBin(AnsiString AFileName);
     void DoLoadCanal(TClipCopyTFS* AClipCopy);
     TLoaderTFSMain* FindMainNode(int AId);
     TLoaderTFSAncestor* FindAncestor(int AIdBlock, int AIdShapeAncestor);
     TLoaderTFSAlternate* FindAlternate(int AId, int ANum);
     int CountTFE(int AId);
     bool DoCheckValidAlternate();
     bool DoCheckValidAncestor();
     bool DoCheckMainNode();
     AnsiString CheckValid();
     AnsiString DoAddMainNodeFromXML(TGlsXmlNode* ANode);
     AnsiString DoAddAncestor(TGlsXmlNode* ANode);
     AnsiString DoAddAlternate(TGlsXmlNode* ANode);
     int __fastcall GetMinTfeID();
     int __fastcall GetMinTfsID();
     int __fastcall GetMinAltID();
     TLoaderTFSAlternate* DoFindAlternate(int ABlockID);
     TLoaderTFSAncestor*  DoFindAncestor(int ABlockID);
     TLoaderTFSMain* DoFindMainNodeFromTFE(int ATFEId);
     void* CreateAlternateParams(TGlsXmlNode* ANode);
     void DoAddParams(TGlsXmlNode* ANode, TLoaderTFSItemMain* AItem);

     void DoAddMainNodeFromBin(THandle AFile, SF_TFS ATfs);
     void DoAddAncestorBin(SF_ANCS Ancs);
     void DoAddAlternateBin(THandle AFile, SF_ALT Alt);
     void DoAddParamsBin(THandle AFile, SF_TFE ATfe, TLoaderTFSItemMain* AItem);
     void* CreateAlternateParamsBin(SF_PARAMALT Alt);

     void DoAddParamsCanal(TClipCopyTFS* AClipCopy, SF_TFE ATfe, TLoaderTFSItemMain* AItem);
     void DoAddMainNodeFromCanal(TClipCopyTFS* AClipCopy, SF_TFS ATfs);
     void DoAddAlternateCanal(TClipCopyTFS* AClipCopy, SF_ALT Alt);
     void DoLoadOgrSovmFromXML(TGlsXmlNode* ANode);
     void DoLoadTypeDecisionFromXML(TGlsXmlNode* ANode);
     void DoLoadOgrSovmFromBin(THandle AFile);
     void DoLoadTypeDecisionFromBin(THandle AFile);
   public:
     TLoaderTFS();
     ~TLoaderTFS();
     void Clear();

     bool LoadFromFile(AnsiString AFileName, TDischargedMassiv *AOgrSovm);
     bool LoadFromFileBin(AnsiString AFileName, TDischargedMassiv *AOgrSovm);
     void LoadFromCanal(TClipCopyTFS* AClipCopy);
     TLoaderTFSMain* AddMainNode(int AId);
     TLoaderTFSAncestor* AddAncestor(int AIdBlock, int AIdShapeAncestor);
     TLoaderTFSAlternate* AddAlternate(int AId, int ANum);
     void IncTfeID(int ACnt);
     void IncTfsID(int ACnt);
     void IncAltID(int ACnt, int AParentID, int AParentNum);
     TLoaderTFSMain* FindNext(TLoaderTFSMain* ANode);
     TLoaderTFSMain* FindPrior(TLoaderTFSMain* ANode);
     TLoaderTFSAncestor* FindAncestorNew(TLoaderTFSMain* ANode);
     TLoaderTFSAlternate* FindAlternative(TLoaderTFSMain* ANode);
     TLoaderTFSAlternate* FindAlternativeFromAncestor(TLoaderTFSMain* ANode);
     TLoaderTFSAncestor* FindAncestorOutBlockID(int ABockId);
     TLoaderTFSMain* FindNodeOutBlockID(int ABockId);
     TLoaderTFSMain* FindNodeOutTFEID(int ATFEId);
     TLoaderTFSAlternate* FindAlternativeParent(TLoaderTFSAlternate* AChild);
     TLoaderTFSAlternate* FindAlternativeParentNew(TLoaderTFSAlternate* AChild);
     TLoaderTFSAlternate* FindAlternativeNew(TLoaderTFSMain* ANode);
     TLoaderTFSMain* FindLastToAlternate(int AId, int ANum);


     __property TLoaderTFSMain* MainNode[int AIndex] = {read = GetMainNode};
     __property TLoaderTFSAncestor* Ancestor[int AIndex] = {read = GetAncestor};
     __property TLoaderTFSAlternate*  Alternate[int AIndex] = { read =  GetAlternate};
     __property int MainNodeCount = {read = GetMainNodeCount};
     __property int AncestorCount = {read = GetAncestorCount};
     __property int AlternateCount = {read = GetAlternateCount};
     __property int MinTfeID = {read = GetMinTfeID};
     __property int MinTfsID = {read = GetMinTfsID};
     __property int MinAltID = {read = GetMinAltID};
     __property int TypeParam = {read = f_TypeParam};
};



#endif
