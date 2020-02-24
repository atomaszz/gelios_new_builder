//---------------------------------------------------------------------------

#ifndef uToolScanH
#define uToolScanH

#include "uFsTable.h"
//---------------------------------------------------------------------------
class TToolScanSim
{
  private:
    int FIndex;
    int FLen;
	AnsiString FString;
  public:
	void Init(const AnsiString AString);
	char NextSim();
};

class TToolScan
{
  private:
	TList *FList;
	TToolScanSim *FScan;
	int FErrorCode;
  public:
	TToolScan();
	~TToolScan();
	bool Parse(const AnsiString AText, TFsTable* ATable);
	__property int ErrorCode = {read = FErrorCode};
};

class TToolScanSuperPosItem
{
  private:
	int FNum;
	AnsiString FText;
  public:
	__property int Num = {read = FNum, write = FNum};
	__property AnsiString Text = {read = FText, write = FText};
};

class TToolScanSuperPos
{
  private:
	TList *FItems;
	AnsiString FFuncSet;
	TToolScanSim *FScan;
	String FErrorText;
	int FErrorCode;

	void Clear();
	void FreeList();
	TToolScanSuperPosItem* Find(int ANum);
	int __fastcall GetCount();
	TToolScanSuperPosItem* __fastcall GetItems(int AIndex);
  public:
	TToolScanSuperPos();
	~TToolScanSuperPos();
	bool Parse(const AnsiString AText);
	void Add(int ANum, const AnsiString AText);
	__property int Count = {read = GetCount};
	__property TToolScanSuperPosItem* Items[int AIndex] = {read = GetItems};
	__property AnsiString FuncSet = {read = FFuncSet};
	__property int ErrorCode = {read = FErrorCode};
	__property String ErrorText = {read = FErrorText};
};



#endif
