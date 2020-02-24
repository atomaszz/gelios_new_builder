//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufrmAlternateViewSelect.h"
#include "uCompositeWork.h"
#include "uCompositeZWork.h"
#include "uCompositeZWorkOR.h"
#include "uCompositeControlWork.h"
#include "uCompositeControlFunc.h"
#include "uCompositeBifurcation.h"
#include "uCompositeCheckConditionCW.h"
#include "uCompositeCycleWhileDo.h"
#include "uCompositeCycleDoWhileDo.h"
#include "uCompositeCycleDoWhileDoFC.h"
#include "uCompositeCheckCondition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAlternateViewSelect *frmAlternateViewSelect;

TInnerAVSelectItem::TInnerAVSelectItem()
{
   f_List = new TList;
}

TInnerAVSelectItem::~TInnerAVSelectItem()
{
   delete f_List;
}

void TInnerAVSelectItem::Add(TAlternateViewItemTFS *Item)
{
   f_List->Add(Item);
}

TAlternateViewItemTFS* TInnerAVSelectItem::GetItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TAlternateViewItemTFS*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int TInnerAVSelectItem::GetCount()
{
   return f_List->Count;
}


TInnerAVSelect::TInnerAVSelect()
{
    f_List = new TList;
}

TInnerAVSelect::~TInnerAVSelect()
{
    TInnerAVSelectItem* Item;
    for (int i = f_List->Count -1 ; i>=0; i--)
    {
       Item = static_cast<TInnerAVSelectItem*>(f_List->Items[i]);
       delete Item;
    }
    delete f_List;
}

TInnerAVSelectItem* TInnerAVSelect::GetNew()
{
   TInnerAVSelectItem* Item = new TInnerAVSelectItem;
   f_List->Add(Item);
   return Item;
}

TInnerAVSelectItem* TInnerAVSelect::GetItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_List->Count - 1)
     return static_cast<TInnerAVSelectItem*>(f_List->Items[AIndex]);
   else
     return NULL;
}

int TInnerAVSelect::GetCount()
{
   return f_List->Count;
}

//---------------------------------------------------------------------------
__fastcall TfrmAlternateViewSelect::TfrmAlternateViewSelect(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::FormCreate(TObject *Sender)
{
   Mass = new TInnerAVSelect;
   X_Base = Y_Base = X_Ofs = Y_Ofs = 0;
   f_X_offs = f_Y_offs = 0;
   f_X_offsSum = f_Y_offsSum = 0;
   f_PainterList = new TAlternateViewPainterList;
   f_ClipPath = new TClipPath;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::FormDestroy(TObject *Sender)
{
   FreeBitmap();
   FreePainterList();
   delete Mass;
   delete f_PainterList;
   delete f_ClipPath;
}
//---------------------------------------------------------------------------
void TfrmAlternateViewSelect::AddMassiv(TDynamicArray *D)
{
   TAlternateViewItemTFS* Item;
   TInnerAVSelectItem* N = Mass->GetNew();
   for (int i = 0 ; i <= D->Count - 1; i++)
   {
      Item = static_cast<TAlternateViewItemTFS*>(D->Items[i]);
      N->Add(Item);
   }
}

void TfrmAlternateViewSelect::GetAlternate(TDynamicArray *D)
{
   D->Clear();
   if (TabControl->TabIndex == -1) return;
   int index = reinterpret_cast<int>(TabControl->Tabs->Objects[TabControl->TabIndex]);
   TInnerAVSelectItem *Item = Mass->GetItem(index);
   if (Item)
   {
      for (int i = 0 ; i <= Item->GetCount() - 1; i++)
        D->Append(Item->GetItem(i));
   }
}



//---------------------------------------------------------------------------

void __fastcall TfrmAlternateViewSelect::acOkExecute(TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::acCancelExecute(TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::FormShow(TObject *Sender)
{
   AnsiString S;
   for (int i = 0; i <= Mass->GetCount() - 1; i++)
   {
     S = "Альтернатива №("+IntToStr(i+1)+")";
     TabControl->Tabs->AddObject(S, reinterpret_cast<TObject*>(i));
   }
   TabControlChange(NULL);

}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::pbShowPaint(TObject *Sender)
{
   PaintToBitmap();
   pbShow->Canvas->Draw(0, 0, f_ScrBitmap);

}
//---------------------------------------------------------------------------

void TfrmAlternateViewSelect::FreeBitmap()
{
  if (f_ScrBitmap)
  {
    delete f_ScrBitmap;
    f_ScrBitmap = NULL;
  }
}


void TfrmAlternateViewSelect::ReCreateGrid(int AWidth, int AHeight)
{
   FreeBitmap();
   f_ScrBitmap = new Graphics::TBitmap;
   f_ScrBitmap->Width = AWidth;
   f_ScrBitmap->Height = AHeight;
   pnlShow->Color = MColorSetup->FonColor;
   RepaintFon();
}

void __fastcall TfrmAlternateViewSelect::pnlShowResize(TObject *Sender)
{
   ReCreateGrid(pnlShow->Width, pnlShow->Height);
   XYCorrect();
   SetNewPolygon();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TfrmAlternateViewSelect::PaintToBitmap()
{
    TCompositeBaseWork *WS;
    WS = f_PainterList->First();
    while (WS)
    {
       WS->Prepare();
       WS->Paint(f_ScrBitmap->Canvas);
       WS = f_PainterList->Next();
    }
}


void TfrmAlternateViewSelect::SetNewPolygon()
{
   TPoint P;
   P =  GetPointPolygon(sbX->Position, sbY->Position);
   if ((P.x - pbShow->Width - sbX->Position) > 2)
     sbX->Max = P.x  - pbShow->Width + 40;
   if ((P.y - pbShow->Height - sbY->Position) > 2)
     sbY->Max = P.y  - pbShow->Height + 40;
}

TRect TfrmAlternateViewSelect::GetMaxRect()
{
    TRect Res = Bounds(0, 0, 0, 0);
    TRect RT;
    TCompositeBaseWork *WS;
    WS = f_PainterList->First();
    if (WS)
      Res = WS->GetMaxRect();
    WS = f_PainterList->Next();
    while (WS)
    {
       RT = WS->GetMaxRect();
       Res = RectSumm(Res, RT);
       WS = f_PainterList->Next();
    }
    return Res;
}


void TfrmAlternateViewSelect::XYCorrect()
{
   TRect R = GetMaxRect();
   if (R.Top < 20 + sbY->Position)
   {
      int my = 20 - R.Top - sbY->Position;
      ApplyOffset(0, my);
   }
   if (R.Left < 20 + sbX->Position)
   {
      int my = 20 - R.Left - sbX->Position;
      ApplyOffset(my, 0);
   }
   RepaintFon();
   pbShow->Invalidate();
}

TPoint TfrmAlternateViewSelect::GetPointPolygon(int AXoffs, int AYoffs)
{
   TPoint res = TPoint(0,0);
   TRect temp = TRect(0,0,0,0);
   TCompositeBaseWork *TempWork;

   TempWork = f_PainterList->First();
   while (TempWork)
   {
     temp = TempWork->GetMaxRect();
     if (temp.Right > res.x) res.x = temp.Right;
     if (temp.Bottom > res.y ) res.y  = temp.Bottom;
     TempWork = f_PainterList->Next();
   }
   res.x = res.x + AXoffs;
   res.y = res.y + AYoffs;
   return res;

}


void TfrmAlternateViewSelect::RepaintFon()
{
   f_ScrBitmap->Canvas->Brush->Color = MColorSetup->FonColor;
   f_ScrBitmap->Canvas->FillRect(TRect(0,0, f_ScrBitmap->Width, f_ScrBitmap->Height));
}

void __fastcall TfrmAlternateViewSelect::sbXChange(TObject *Sender)
{
   TRect R;
   X_Ofs = sbX->Position - X_Base;
   X_Base = sbX->Position;
   ApplyOffset(-X_Ofs, 0);
   RepaintFon();
   PaintToBitmap();
   if (X_Ofs < 0)
     R = TRect(0,0, abs(X_Ofs) + 3, pbShow->Height);
   else
     R = TRect(pbShow->Width - X_Ofs  - 3, 0, pbShow->Width, pbShow->Height);
   ScrollDC(pbShow->Canvas->Handle, -X_Ofs, 0, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlShow->Handle, &R, false);
   UpdateWindow(pnlShow->Handle);

}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateViewSelect::sbYChange(TObject *Sender)
{
   TRect R;
   Y_Ofs = sbY->Position - Y_Base;
   Y_Base = sbY->Position;
   ApplyOffset(0, -Y_Ofs);
   RepaintFon();
   PaintToBitmap();
   if (Y_Ofs < 0)
     R = TRect(0,0,  pbShow->Width, abs(Y_Ofs) + 3);
   else
     R = TRect(0, pbShow->Height - Y_Ofs  - 3, pbShow->Width, pbShow->Height);

   ScrollDC(pbShow->Canvas->Handle, 0, - Y_Ofs, NULL, NULL, NULL, NULL);
   InvalidateRect(pnlShow->Handle, &R, false);
   UpdateWindow(pnlShow->Handle);
   
}
//---------------------------------------------------------------------------

void TfrmAlternateViewSelect::ApplyOffset(int AX, int AY)
{
    TCompositeBaseWork* TempWork;
    TPoint P;
    if ( (AX <= 0) != (f_X_offs <= 0) )
       f_X_offs = AX;
    else
       f_X_offs += AX;

    if ( (AY <= 0) != (f_Y_offs <= 0) )
       f_Y_offs = AY;
    else
       f_Y_offs += AY;

    f_X_offsSum+= AX;
    f_Y_offsSum+= AY;
    TempWork = f_PainterList->First();
    while(TempWork)
    {
      P = TempWork->StartPoint;
      P.x += AX;
      P.y += AY;
  //    TempWork->StartPoint = P;

      TempWork->ApplyOffset(AX, AY);
      TempWork = f_PainterList->Next();
    }

}

void __fastcall TfrmAlternateViewSelect::TabControlChange(TObject *Sender)
{
   if (TabControl->TabIndex == -1) return;
   int m_id =  reinterpret_cast<int>(TabControl->Tabs->Objects[TabControl->TabIndex]);
   PrepareScroll();
   ListChange(m_id);
   PrepareLevel();
   PaintToBitmap();
   CoordinateCorrect();
   RepaintFon();
   XYCorrect();
   SetNewPolygon();
   InvalidateRgn(pbShow->Parent->Handle, NULL, false);

}

void TfrmAlternateViewSelect::PrepareLevel()
{
   f_X_offs = 0; //смещение по Х
   f_Y_offs = 0; //смещение по Y
   f_X_offsSum = f_Y_offsSum = 0;
}

void TfrmAlternateViewSelect::FreePainterList()
{
   TCompositeBaseWork* Item;
   Item = f_PainterList->First();
   while (Item)
   {
      Item->FreeRef();
      Item = f_PainterList->Next();
   }
   f_PainterList->ClearAll();
}


void TfrmAlternateViewSelect::ListChange(int Aid)
{
   TInnerAVSelectItem* Item;
   TAlternateViewItemTFS* TFS;
   FreePainterList();
   Item = Mass->GetItem(Aid);
   for (int i = 0 ; i <= Item->GetCount() - 1 ; i++)
   {
       TFS = Item->GetItem(i);
       f_PainterList->AddItem(CreateWS(TFS));
   }
}

TCompositeBaseWork* TfrmAlternateViewSelect::CreateWS(TAlternateViewItemTFS* ATFS)
{

    TCompositeBaseWork* WS = NULL;
    if (ATFS->BaseWorkShape->CompositeWorkShape)
     WS = ATFS->BaseWorkShape->CompositeWorkShape->CopyRef();
    if (!WS)
    {
      switch (ATFS->BaseWorkShape->TypeShape)
      {
         case 1:
         {
            WS = new TCompositeWork;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 2:
         {
            WS = new TCompositeZWork;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 3:
         {
            WS = new TCompositeZWorkOR;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 4:
         {
            WS = new TCompositeControlWork;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 5:
         {
            WS = new TCompositeControlFunc;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 6:
         {
            WS = new TCompositeBifurcation;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 7:
         {
            WS = new TCompositeCheckConditionCW;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 8:
         {
            WS = new TCompositeCycleWhileDo;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 9:
         {
            WS = new TCompositeCycleDoWhileDo;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 10:
         {
            WS = new TCompositeCycleDoWhileDoFC;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
         case 11:
         {
            WS = new TCompositeCheckCondition;
            WS->ColorSetup = MColorSetup;
            WS->ConvertWorkShape(ATFS, AV);
            break;
         }
      }
    }  
    return WS;

}

//---------------------------------------------------------------------------

void TfrmAlternateViewSelect::PrepareScroll()
{
   X_Base = Y_Base =  X_Ofs = Y_Ofs = 0;
   sbY->Max = 0;
   sbX->Max = 0;
   ApplyOffset(-f_X_offsSum, -f_Y_offsSum);
}

void TfrmAlternateViewSelect::CoordinateCorrect()
{
    TCompositeBaseWork* TempWork;
    TPoint P, PN;
    TempWork = f_PainterList->First();
    if (!TempWork) return;

    while(TempWork)
    {
      P = TempWork->EndPoint;
      TempWork = f_PainterList->Next();
      if (!TempWork) break;
      TempWork->StartPoint = P;
    }

}



void __fastcall TfrmAlternateViewSelect::acOkUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled =  (TabControl->TabIndex > -1);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlternateViewSelect::FormKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
   if (Key == VK_ESCAPE)
     acCancelExecute(NULL);
}
//---------------------------------------------------------------------------

bool TfrmAlternateViewSelect::CheckDublesItem(TInnerAVSelectItem* A1, TInnerAVSelectItem* A2)
{
   TAlternateViewItemTFS *T1, *T2;
   int m_c1, m_c2, m_all;
   m_c1 = A1->GetCount();
   m_c2 = A2->GetCount();
   if (m_c1 != m_c2) return false;
   m_all = 0;
   for (int i = 0 ; i <= m_c1 - 1; i++)
   {
       T1 = A1->GetItem(i);
       T2 = A2->GetItem(i);
       if (T1->BaseWorkShape == T2->BaseWorkShape)
        m_all++;
   }
   return ( m_all == m_c1 );
}


bool TfrmAlternateViewSelect::CheckDubles()
{
   int m_cnt = Mass->GetCount();
   if (!m_cnt) return true;
   TInnerAVSelectItem *Item, *Curr;
   for (int i = 0 ; i <= m_cnt - 1; i++)
   {
      Curr = Mass->GetItem(i);
      for (int j = 0 ; j <= m_cnt - 1; j++)
      {
        if (i != j)
        {
           Item = Mass->GetItem(j);
           if ( CheckDublesItem(Curr, Item) )
           {
             ShowMessage("Найдены совпадения " + IntToStr(i + 1) + "  и  " + IntToStr(j + 1));
             return true;
           }
        }
      }
   }
   return false;

}


void __fastcall TfrmAlternateViewSelect::acCheckDoublesUpdate(
      TObject *Sender)
{
   bool m_deb = HasParam("DEBUG");
   dynamic_cast<TAction*>(Sender)->Enabled = m_deb;
   dynamic_cast<TAction*>(Sender)->Visible = m_deb;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlternateViewSelect::acCheckDoublesExecute(
      TObject *Sender)
{
   if ( !CheckDubles() )
     ShowMessage("Cовпадений нет");
}
//---------------------------------------------------------------------------

