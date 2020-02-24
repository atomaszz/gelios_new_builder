//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ufrmAlternateView.h"
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
TfrmAlternateView *frmAlternateView;
//---------------------------------------------------------------------------
__fastcall TfrmAlternateView::TfrmAlternateView(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TfrmAlternateView::FormCreate(TObject *Sender)
{
   X_Base = Y_Base = X_Ofs = Y_Ofs = 0;
   f_X_offs = f_Y_offs = 0;
   AV = new TAlternateView;
   f_PainterList = new TAlternateViewPainterList;
   f_ClipPath = new TClipPath;
   f_Stack = new TDynamicArray;
   f_History = new TCompositeStack;
   f_OldSelected = NULL;
   f_Stack->Append(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateView::FormDestroy(TObject *Sender)
{
   FreeBitmap();
   FreePainterList();
   delete AV;
   delete f_PainterList;
   delete f_ClipPath;
   delete f_Stack;
   delete f_History;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlternateView::pbShowPaint(TObject *Sender)
{
   PaintToBitmap();
   pbShow->Canvas->Draw(0, 0, f_ScrBitmap);
}
//---------------------------------------------------------------------------
void TfrmAlternateView::FreeBitmap()
{
  if (f_ScrBitmap)
  {
    delete f_ScrBitmap;
    f_ScrBitmap = NULL;
  }
}

void TfrmAlternateView::LoadAlternative(TTreeList* ATreeList)
{
   AV->Load(ATreeList->MainTreeList);
}


void TfrmAlternateView::ReCreateGrid(int AWidth, int AHeight)
{
   FreeBitmap();
   f_ScrBitmap = new Graphics::TBitmap;
   f_ScrBitmap->Width = AWidth;
   f_ScrBitmap->Height = AHeight;
   pnlShow->Color = MColorSetup->FonColor;
   RepaintFon();
}

void __fastcall TfrmAlternateView::pnlShowResize(TObject *Sender)
{
   ReCreateGrid(pnlShow->Width, pnlShow->Height);
   SetNewPolygon();
}

//---------------------------------------------------------------------------
void TfrmAlternateView::PaintToBitmap()
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

//---------------------------------------------------------------------------

void __fastcall TfrmAlternateView::Button1Click(TObject *Sender)
{
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------


void TfrmAlternateView::SetNewPolygon()
{
   TPoint P;
   P =  GetPointPolygon(sbX->Position, sbY->Position);
   if ((P.x - pbShow->Width - sbX->Position) > 2)
     sbX->Max = P.x  - pbShow->Width + 40;
   if ((P.y - pbShow->Height - sbY->Position) > 2)
     sbY->Max = P.y  - pbShow->Height + 40;
}

TPoint TfrmAlternateView::GetPointPolygon(int AXoffs, int AYoffs)
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


void __fastcall TfrmAlternateView::sbXChange(TObject *Sender)
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

void __fastcall TfrmAlternateView::sbYChange(TObject *Sender)
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
void TfrmAlternateView::ApplyOffset(int AX, int AY)
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

    TempWork = f_PainterList->First();
    while(TempWork)
    {
      P = TempWork->StartPoint;
      P.x += AX;
      P.y += AY;
     // TempWork->StartPoint = P;

      TempWork->ApplyOffset(AX, AY);
      TempWork = f_PainterList->Next();
    }

}

void TfrmAlternateView::RepaintFon()
{
   f_ScrBitmap->Canvas->Brush->Color = MColorSetup->FonColor;
   f_ScrBitmap->Canvas->FillRect(TRect(0,0, f_ScrBitmap->Width, f_ScrBitmap->Height));
}

TBaseShape* TfrmAlternateView::FindTFE(int Ax, int Ay)
{
  TBaseShape * CurrShape;
  TCompositeBaseWork* TempWork;
  TCompositeBaseWorkItem *WI;
  TempWork = f_PainterList->First();
  while(TempWork)
  {
     for (int i = 0; i <= TempWork->ItemCount - 1; i++ )
     {
        WI = TempWork->GetItem(i);
        CurrShape = WI->FindTFE(Ax, Ay);
        if (CurrShape)
          return CurrShape;
     }
     TempWork = f_PainterList->Next();
  }
  return NULL;
}


TCompositeBaseWorkItem* TfrmAlternateView::FindComositeBaseWork(TBaseShape* ATFE, TCompositeBaseWork **AFind)
{
  TCompositeBaseWork* TempWork;
  TCompositeBaseWork* WI, *WF;
  TCompositeBaseWorkItem* Item;
  TempWork = f_PainterList->First();
  while(TempWork)
  {
     Item = TempWork->FindItem(ATFE->ID, &WF);
     if (Item)
     {
       *AFind =  WF;
       return Item;
     }
     TempWork = f_PainterList->Next();
  }
  *AFind = NULL;
  return NULL;
}


TCompositeBaseWorkItem* TfrmAlternateView::FindComositeBaseWork2(int ATFEID, TCompositeBaseWork **AFind)
{
  TCompositeBaseWork* TempWork;
  TCompositeBaseWork* WF;
  TCompositeBaseWorkItem* Item;
  TempWork = f_PainterList->First();
  while(TempWork)
  {
     Item = TempWork->FindItem(ATFEID, &WF);
     if (Item)
     {
       *AFind =  WF;
       return Item;
     }
     TempWork = f_PainterList->Next();
  }
  *AFind = NULL;
  return NULL;
}


void __fastcall TfrmAlternateView::pbShowMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TBaseShape* B;
    B = FindTFE(X, Y);
    if (B)
    {
       f_ClipPath->Clear();
       B->DrawFrame = true;
       f_ClipPath->Add(B->GetFrameRect(), 4);
       if (f_OldSelected && (f_OldSelected != B))
       {
         f_OldSelected->DrawFrame = false;
         f_ClipPath->Add(f_OldSelected->GetFrameRect(), 4);
       }
       f_OldSelected = B;
       RepaintFon();
       InvalidateRgn(pbShow->Parent->Handle, f_ClipPath->GetCliptRgn(), false);
       if ( Button == mbRight )
       {
          TPoint P = pbShow->ClientToScreen(TPoint(X, Y));
          PopupMenu->Popup(P.x, P.y);
       }

    }

}
//---------------------------------------------------------------------------


void __fastcall TfrmAlternateView::acExpandExecute(TObject *Sender)
{
    f_Stack->Append((void*)(f_OldSelected->ID));
    ExpandShape();
}
//---------------------------------------------------------------------------

void TfrmAlternateView::ExpandShape()
{
   TAlternateViewItem* Item;
   TAlternateViewItemTFS* TFS;
   TCompositeBaseWork *W, *Find;
   TCompositeBaseWorkItem* F;
   TCompositeWork *S;
   TPoint PS;
   TCompositeStackItem* STI;
   int mRes;

   int m_id = int(f_Stack->Pop());

   TDynamicArray *D = new TDynamicArray;
   Application->CreateForm(__classid(TfrmAlternateViewSelect), &frmAlternateViewSelect);
   frmAlternateViewSelect->AV = AV;
   frmAlternateViewSelect->MColorSetup = MColorSetup;
   for (int i = 0; i <= AV->ItemCount - 1; i++)
   {
      Item = AV->ItemView[i];
      if (Item->ParentTFE)
      {
        if (Item->ParentTFE->BaseShape->ID == m_id)
        {
           D->Clear();
           for (int j = 0 ; j <= Item->ItemCount - 1; j++)
           {
              TFS = Item->ItemTFS[j];
              D->Append(TFS);
           }
           frmAlternateViewSelect->AddMassiv(D);
         }
      }
      if (!m_id && !Item->ParentTFE)
      {
           D->Clear();
           for (int j = 0 ; j <= Item->ItemCount - 1; j++)
           {
              TFS = Item->ItemTFS[j];
              D->Append(TFS);
           }
           frmAlternateViewSelect->AddMassiv(D);
      }
   }

   mRes = frmAlternateViewSelect->ShowModal();
   if ( mRes == mrOk )
   {
      frmAlternateViewSelect->GetAlternate(D);
      if (!m_id)
      {
        FreePainterList();
        for(int k = 0; k <= D->Count - 1; k++)
        {
          TFS = static_cast<TAlternateViewItemTFS*>(D->Items[k]);
          W = CreateWS(TFS);
          f_History->AddBaseWork(TFS);
          f_PainterList->AddItem(W);
        }
        CoordinateCorrect();
     }
     else
     {
        F = FindComositeBaseWork(f_OldSelected, &Find);
        PS = F->StartPoint;
        f_OldSelected = NULL;
        if (D->Count > 0)
          STI = f_History->CreateItem(m_id);
        for(int k = 0; k <= D->Count - 1; k++)
        {
          TFS = static_cast<TAlternateViewItemTFS*>(D->Items[k]);
          W = CreateWS(TFS);
          W->StartPoint =  PS;
          W->Prepare();
          F->AddCompositeWork(W);
          PS = W->EndPoint;
          STI->AddTFS(TFS);
        }
        Find->Prepare();
        CoordinateCorrect();
     }
   }
   frmAlternateViewSelect->Release();
   delete D;
   if ( (mRes == mrCancel ) &&  !m_id)
     PostMessage(this->Handle, WM_USER + 1, 0 , 0);
   PaintToBitmap();
   RepaintFon();
   XYCorrect();
   SetNewPolygon();


}

void TfrmAlternateView::FreePainterList()
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


void TfrmAlternateView::CoordinateCorrect()
{
   TCompositeBaseWork* Item;
   TPoint P;
   Item = f_PainterList->First();
   if (!Item) return;
   P = Item->OffsetEndCoordinate(Item->StartPoint);
   P = Item->EndPoint;
   Item = f_PainterList->Next();
   while (Item)
   {
      Item->StartPoint = P;
      P = Item->OffsetEndCoordinate(P);
      P = Item->EndPoint;
      Item = f_PainterList->Next();
   }

}


TCompositeBaseWork* TfrmAlternateView::CreateWS(TAlternateViewItemTFS* ATFS)
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



void __fastcall TfrmAlternateView::FormShow(TObject *Sender)
{
   ExpandShape();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlternateView::acExpandUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = (f_OldSelected != NULL) && AV->IsHaveChildShape(f_OldSelected->ID);
}
//---------------------------------------------------------------------------



void __fastcall TfrmAlternateView::acBackUpdate(TObject *Sender)
{
   dynamic_cast<TAction*>(Sender)->Enabled = !f_History->IsEmpty();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlternateView::acBackExecute(TObject *Sender)
{
   TAlternateViewItemTFS* TFS;
   TCompositeBaseWork *W, *Find;
   TCompositeBaseWorkItem* F;
   TPoint PS;
   TCompositeStackItem* STI;
   f_OldSelected = NULL;
   f_History->Pop();
   FreePainterList();
   sbX->Position = 0;
   sbY->Position = 0;
   sbX->Max = 0;
   sbY->Max = 0;
   for(int i = 0; i <= f_History->BaseCount - 1; i++)
   {
      TFS = f_History->BaseItems[i];
      W = CreateWS(TFS);
      f_PainterList->AddItem(W);
   }
   CoordinateCorrect();
   for(int i = 0; i <= f_History->STICount - 1; i++)
   {
      STI = f_History->STIItems[i];
      F = FindComositeBaseWork2(STI->IDShape, &Find);
      PS = F->StartPoint;
      for(int k = 0; k <= STI->TFSCount - 1; k++)
      {
         TFS = STI->TFSItems[k];
         W = CreateWS(TFS);
         W->StartPoint =  PS;
         W->Prepare();
         F->AddCompositeWork(W);
         PS = W->EndPoint;
      }
      Find->Prepare();
      CoordinateCorrect();
   }
   XYCorrect();
   SetNewPolygon();
}
//---------------------------------------------------------------------------
TRect TfrmAlternateView::GetMaxRect()
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

void TfrmAlternateView::XYCorrect()
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




MESSAGE void __fastcall TfrmAlternateView::M_Close(TMessage& Msg)
{
    ModalResult = mrCancel;
}



void __fastcall TfrmAlternateView::acExitExecute(TObject *Sender)
{
   ModalResult = mrOk;  
}
//---------------------------------------------------------------------------





