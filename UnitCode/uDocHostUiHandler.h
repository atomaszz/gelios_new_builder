#include <windows.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <oaidl.h>

#ifndef DOC_HOST_UI_HANDLER_H__
#define DOC_HOST_UI_HANDLER_H__

class TDocHostUiHandler : public IDocHostUIHandler {


  public:
    TDocHostUiHandler();
    virtual ~TDocHostUiHandler() {};
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID FAR* ppvObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

  HRESULT STDMETHODCALLTYPE ShowContextMenu(
      DWORD                dwID,
      POINT     __RPC_FAR *ppt,
      IUnknown  __RPC_FAR *pcmdtReserved,
      IDispatch __RPC_FAR *pdispReserved);

  HRESULT STDMETHODCALLTYPE ShowUI(
      DWORD                              dwID,
      IOleInPlaceActiveObject __RPC_FAR*  pActiveObject,
      IOleCommandTarget       __RPC_FAR*  pCommandTarget,
      IOleInPlaceFrame        __RPC_FAR*  pFrame,
      IOleInPlaceUIWindow     __RPC_FAR*  pDoc);

  HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO __RPC_FAR* pInfo);

  HRESULT STDMETHODCALLTYPE HideUI();

  HRESULT STDMETHODCALLTYPE UpdateUI();

  HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);

  HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate);

  HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate);

  HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT  prcBorder,
    IOleInPlaceUIWindow __RPC_FAR* pUIWindow, BOOL fRameWindow);

  HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg, const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID);

  HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR __RPC_FAR* pchKey, DWORD dw);

  HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget __RPC_FAR* pDropTarget, IDropTarget __RPC_FAR* __RPC_FAR* ppDropTarget);
  HRESULT STDMETHODCALLTYPE GetExternal( /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);

  HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate, OLECHAR __RPC_FAR* pchURLIn, OLECHAR __RPC_FAR* __RPC_FAR* ppchURLOut);

  HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject __RPC_FAR* pDO, IDataObject __RPC_FAR* __RPC_FAR* ppDORet);
};
#endif
