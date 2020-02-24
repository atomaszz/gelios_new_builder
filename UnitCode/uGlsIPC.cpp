//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsIPC.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
TGlsIPC::TGlsIPC()
{
  m_hFileMap = NULL;
  m_hMutex = NULL;
  f_High = 0;
}

//---------------------------------------------------------------------------
TGlsIPC::~TGlsIPC()
{
    CloseIPCMMF();
    Unlock();
}

//---------------------------------------------------------------------------
bool TGlsIPC::CreateIPCMMF(DWORD AHigh)
{
  bool bCreated = false;
  f_High = AHigh;

  try
  {
     if(m_hFileMap != NULL)
        return false;    // Уже создан

     m_hFileMap = CreateFileMapping((HANDLE)0xFFFFFFFF,
		 NULL,
         PAGE_READWRITE,
         0,
         AHigh + sizeof(DWORD),
		 _T(IPC_SHARED_MMF));

     if(m_hFileMap != NULL)
        bCreated = true;
  }
  catch(...) {}

  return bCreated;
}

//---------------------------------------------------------------------------
bool TGlsIPC::OpenIPCMMF(void)
{
    bool bOpened = false;

    try
    {
        if(m_hFileMap != NULL)
            return true;

        m_hFileMap =
          OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
            FALSE,
			_T(IPC_SHARED_MMF));
        if(m_hFileMap != NULL)
            bOpened = true;
    }
    catch(...) {}

    return bOpened;
}

//---------------------------------------------------------------------------
void TGlsIPC::CloseIPCMMF(void)
{
    try
    {
        if(m_hFileMap != NULL)
            CloseHandle(m_hFileMap), m_hFileMap = NULL;
    }
    catch(...) {}
}

//---------------------------------------------------------------------------
long TGlsIPC::Length()
{
  DWORD dwSizeofInBuf = 0;
  try
  {
     if(m_hFileMap == NULL)
         return 0;

     DWORD dwBaseMMF = (DWORD)MapViewOfFile(m_hFileMap,
                FILE_MAP_READ | FILE_MAP_WRITE,
         0, 0, 0);

     // Первый DWORD в MMF содержит размер данных
     CopyMemory(&dwSizeofInBuf, (LPVOID)dwBaseMMF, sizeof(DWORD));

     UnmapViewOfFile((LPVOID)dwBaseMMF);
  }
  catch(...) {}

  return dwSizeofInBuf;
}


//---------------------------------------------------------------------------
DWORD TGlsIPC::ReadIPCMMF(void* pBuf, DWORD dwBufSize, DWORD AOffset)
{
  DWORD fDln = 0;
  DWORD fSize;

  try
  {
     if(m_hFileMap == NULL)
         return 0;

     DWORD dwBaseMMF = (DWORD)MapViewOfFile(m_hFileMap,
                FILE_MAP_READ | FILE_MAP_WRITE,
         0, 0, 0);

     // Первый DWORD в MMF содержит размер данных
     CopyMemory(&fSize, (LPVOID)dwBaseMMF, sizeof(DWORD));

     if(dwBufSize != 0)
     {
        if ( AOffset > fSize )
          return  0;
        if ( (AOffset + dwBufSize) > fSize )
          fDln = fSize - AOffset;
        else
          fDln = dwBufSize;
         CopyMemory(pBuf, (LPVOID)(dwBaseMMF + sizeof(DWORD) + AOffset), fDln);
     }
     UnmapViewOfFile((LPVOID)dwBaseMMF);
  }
  catch(...) {}

  return fDln;
}

//---------------------------------------------------------------------------
bool TGlsIPC::WriteIPCMMF(const void* pBuf, const DWORD dwBufSize, DWORD AOffset)
{
    DWORD dwSizeofInBuf = 0;
    DWORD Nd = 0;

    bool bSuccess = true;

    try
    {
        if(m_hFileMap == NULL)
           return false;

        DWORD dwBaseMMF = (DWORD)MapViewOfFile(m_hFileMap,
            FILE_MAP_READ | FILE_MAP_WRITE,
            0, 0, 0);

        // Первый DWORD в MMF содержит размер данных
        CopyMemory(&dwSizeofInBuf, (LPVOID)dwBaseMMF, sizeof(DWORD));

        if (dwSizeofInBuf > AOffset)
          Nd = AOffset + dwBufSize;
        if (dwSizeofInBuf <= AOffset)
          Nd = AOffset + dwBufSize;

        if(Nd > f_High)
        {
          UnmapViewOfFile((LPVOID)dwBaseMMF);
          return false;
        }

        // Первый DWORD в MMF содержит размер данных
        CopyMemory((LPVOID)dwBaseMMF, &Nd, sizeof(DWORD));
        CopyMemory((LPVOID)(dwBaseMMF + sizeof(DWORD) + AOffset),
                            pBuf,
                            dwBufSize);

        UnmapViewOfFile((LPVOID)dwBaseMMF);
    }
    catch(...) {}

    return bSuccess;
}

//---------------------------------------------------------------------------
bool TGlsIPC::Lock(void)
{
    bool bLocked = false;

    try
    {
		m_hMutex = CreateMutex(NULL, FALSE, _T(IPC_MUTEX));
        if(m_hMutex != NULL)
        {
            if(WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0)
                bLocked = true;
        }
    }
    catch(...) {}

    return bLocked;
}

//---------------------------------------------------------------------------
void TGlsIPC::Unlock(void)
{
    try
    {
        if(m_hMutex != NULL)
        {
            ReleaseMutex(m_hMutex);
            CloseHandle(m_hMutex);
            m_hMutex = NULL;
        }
    }
    catch(...) {}
}
