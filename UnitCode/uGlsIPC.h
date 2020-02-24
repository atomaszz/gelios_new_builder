//---------------------------------------------------------------------------

#ifndef uGlsIPCH
#define uGlsIPCH
//---------------------------------------------------------------------------

#define IPC_SHARED_MMF  "{791C4326-1886-453A-8E38-8AD46AF4892F}"
#define IPC_MUTEX       "{791C4327-1886-453A-8E38-8AD46AF4892F}"

//  ласс дл€ межпроцессовой св€зи использу€
// отображаемые в пам€ть файлы
class TGlsIPC
{
  private:
    DWORD f_High;
    HANDLE m_hFileMap;
    HANDLE m_hMutex;
  public:
    TGlsIPC();
    virtual ~TGlsIPC();

    bool CreateIPCMMF(DWORD AHigh);
    bool OpenIPCMMF(void);
    void CloseIPCMMF(void);

    bool IsOpen(void) const {return (m_hFileMap != NULL);}

    DWORD ReadIPCMMF(void* pBuf, DWORD dwBufSize, DWORD AOffset = 0);
    bool WriteIPCMMF(const void* pBuf,
                     const DWORD dwBufSize, DWORD AOffset = 0);

    bool Lock(void);
    void Unlock(void);
    long Length();

};

#endif
