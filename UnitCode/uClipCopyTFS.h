//---------------------------------------------------------------------------
#ifndef uClipCopyTFSH
#define uClipCopyTFSH

#include "uTreeList.h"
#include "uGlsIPC.h"
//---------------------------------------------------------------------------
class TClipCopyTFS
{
  private:
    HWND f_OwnerForm;
    TGlsIPC* f_Canal;
    DWORD f_Seek;
    void CanalInit(DWORD ABuf);
    void DoLoadMainItem(TMainTreeList* AList, TDynamicArray *D, TDynamicArray *AStack);
    void DoLoadMain(TTreeList* ATree, TDynamicArray *D);
    void DoLoadAncsItem(int AParentShapeID, TMainTreeList* AList, TDynamicArray *D, TDynamicArray *AStack);
    void DoLoadAncs(int AParentShapeID, TTreeList* ATree, TDynamicArray *D);
    void DoLoadAltItem(TMainTreeList* AList, TDynamicArray *D, TDynamicArray *AStack);
    void DoLoadAlt(TTreeList* ATree, TDynamicArray *D);
    void SortAltList(TDynamicArray* D);
    void RenumAltList(TDynamicArray* D);

    bool SaveParamAlternateToCanal(TBaseShape* ATFE, SF_TFE A_tfe);
    bool DoSaveMain(TDynamicArray* D);
    bool DoSaveAncs(TDynamicArray* D);
    bool DoSaveAlt(TDynamicArray* D);
    TBaseWorkShape* FindNextWorkShape(TBaseWorkShape *W);
    TBaseWorkShape* FindPriorWorkShape(TBaseWorkShape *W);
  public:
    TClipCopyTFS(HWND AOwner, DWORD ABuf);
    ~TClipCopyTFS();
    bool CanalWrite(const void* pBuf,  DWORD dwBufSize);
    DWORD CanalLength();
    DWORD CanalRead(void* pBuf, DWORD dwBufSize);
    void CanalSeek(DWORD AOffset);
    bool CopyTfsList(TListNode* AListNode, int AParentShapeID, TBaseWorkShape* AWS, TBaseWorkShape* AWE);
};
#endif
