//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufToolMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


#include "uFsList.h"
#include "uTFSTemplate.h"
#include "uFsList.h"

bool ShowToolTFS(String AText)
{
  TfmToolMain *fmToolMain;
  Application->CreateForm(__classid(TfmToolMain), &fmToolMain);
  bool res = fmToolMain->ShowModal() == mrOk;
  fmToolMain->Release();
  return res;
}

//---------------------------------------------------------------------------
__fastcall TfmToolMain::TfmToolMain(TComponent* Owner)
		: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmToolMain::Button1Click(TObject *Sender)
{
/*
  String s;
  TToolScan C;
  TBigWork* BigWork;
  TCheckSuperPosItem* SuperPosItem;
  mmRo->Clear();
  mmStep->Clear();
  FTable->Clear();
  if (!C.Parse(mmSource->Text, FTable))
  {
	ShowMessage("Ошибка в описании! Код: " + IntToStr(C.ErrorCode));
	return;
  }
  FChecker->InitFromTable(FTable);
  if (!FChecker->Check())
  {
	ShowMessage("Суперпозиция не может быть построена!");
	return;
  }
  for(int i = 0; i < FChecker->CountSuperPos; i++)
  {
	SuperPosItem = FChecker->ItemsSuperPos[i];
	mmStep->Lines->Add(SuperPosItem->ToString());
	s = "";
	for (int j = 0; j < SuperPosItem->Count; j++)
	{
	  TFsTableItem* TI;
	  TI = SuperPosItem->Items[j];
	  s = s + " +++ " +TI->ToString();
	}
	ShowMessage(s);

  }

  for(int i = 0; i < FChecker->CountBigWork; i++)
  {
	BigWork = FChecker->ItemsBigWork[i];
	mmRo->Lines->Add(BigWork->ToString());
  }
  */
  TToolScanSuperPos C;
  if (!C.Parse(mmSource->Text))
  {
	ShowMessage("Ошибка! Код: " + IntToStr(C.ErrorCode));
	return;
  }
  ShowMessage("ФС " + C.FuncSet);
  for(int i = 0; i < C.Count; i++)
  {
	TToolScanSuperPosItem* Item = C.Items[i];
	ShowMessage(IntToStr(Item->Num) + " = " + Item->Text);
  }


}
//---------------------------------------------------------------------------




void __fastcall TfmToolMain::FormCreate(TObject *Sender)
{
  FTable = new TFsTable;
  FChecker = new TCheckSuperPos;
}
//---------------------------------------------------------------------------

void __fastcall TfmToolMain::FormDestroy(TObject *Sender)
{
  delete FTable;
  delete FChecker;        
}
//---------------------------------------------------------------------------

void __fastcall TfmToolMain::Button2Click(TObject *Sender)
{
  TFsTableItem* Item;
  TFsTableItemData *E, *T;
  AnsiString Rep;
  TFsList List;
  TFsNode* Node;
  AnsiString S;
  int num = StrToIntDef(edTransit->Text, 0);
  if (num <= 0)
  {
    ShowMessage("Задайте правильный номер транзита!");
    return;
  }
  if (FChecker->CountSuperPos <= 0)
  {
    ShowMessage("Нет представления ФС в виде суперпозиции!");
    return;
  }
  T = FChecker->LevelHeap->Find2(ST_TRANS, num);
  if (!T)
  {
    ShowMessage("Транзит не найден!");
    return;
  }
  for(int i = 0; i < FChecker->LevelHeap->Count; i++)
  {
    E = FChecker->LevelHeap->Items[i];
    if (E->IsTrans() && (E->Num != num) && (E->Level == T->Level))
      List.Add(E);
  }

  TStringList *SL = new TStringList;
  Node = List.MoveInit(0);
  while(Node)
  {
    T = (TFsTableItemData*)Node->Data;
    S = "T" + IntToStr(T->Num);
    if (SL->IndexOf(S) < 0)
      SL->Add(S);
    Node = List.MoveNext();
  }
  Rep = SL->Text;
  delete SL;
  if (Rep.Length() == 0)
    Rep = "Не найдено подходящих транзитов!";
  ShowMessage(Rep);

}
//---------------------------------------------------------------------------









