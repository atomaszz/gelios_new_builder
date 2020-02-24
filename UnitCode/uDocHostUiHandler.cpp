//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDocHostUiHandler.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TDocHostUiHandler::TDocHostUiHandler()
{
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::ShowContextMenu(
      DWORD                dwID,
      POINT     __RPC_FAR *ppt,
      IUnknown  __RPC_FAR *pcmdtReserved,
      IDispatch __RPC_FAR *pdispReserved)
{

  return S_OK;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
   ppvObj = 0;
   return S_OK;
}


ULONG STDMETHODCALLTYPE TDocHostUiHandler::AddRef()
{
   return 1;
}

ULONG STDMETHODCALLTYPE TDocHostUiHandler::Release()
{
   return 1;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::ShowUI(
      DWORD                              dwID,
      IOleInPlaceActiveObject __RPC_FAR*  pActiveObject,
      IOleCommandTarget       __RPC_FAR*  pCommandTarget,
      IOleInPlaceFrame        __RPC_FAR*  pFrame,
      IOleInPlaceUIWindow     __RPC_FAR*  pDoc)
{
  return S_FALSE ;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::GetHostInfo(DOCHOSTUIINFO __RPC_FAR* pInfo)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::HideUI()
{
  return S_FALSE;
}


HRESULT STDMETHODCALLTYPE TDocHostUiHandler::UpdateUI()
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::EnableModeless(BOOL fEnable)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::OnDocWindowActivate(BOOL fActivate)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::OnFrameWindowActivate(BOOL fActivate)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::ResizeBorder(LPCRECT  prcBorder,
  IOleInPlaceUIWindow __RPC_FAR* pUIWindow, BOOL fRameWindow)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::TranslateAccelerator(LPMSG lpMsg,
  const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::GetOptionKeyPath(LPOLESTR __RPC_FAR* pchKey,  DWORD dw)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::GetDropTarget(IDropTarget __RPC_FAR* pDropTarget,
   IDropTarget __RPC_FAR* __RPC_FAR* ppDropTarget)
{
      return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::GetExternal( /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
  *ppDispatch = 0;
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::TranslateUrl(DWORD dwTranslate,
  OLECHAR __RPC_FAR* pchURLIn, OLECHAR __RPC_FAR* __RPC_FAR* ppchURLOut)
{
  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE TDocHostUiHandler::FilterDataObject(IDataObject __RPC_FAR* pDO,
  IDataObject __RPC_FAR* __RPC_FAR* ppDORet)
{
  *ppDORet = 0;
  return S_FALSE;
}









