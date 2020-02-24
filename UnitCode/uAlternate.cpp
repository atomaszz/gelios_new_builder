//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAlternate.h"
#include "uPaintGrids.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TAlternateItem
{
   private:
     int f_Num;
     TBaseWorkShape *f_WSFirst;
     TBaseWorkShape *f_WSLast;
     TArrowWorkShape *f_First;
     TArrowWorkShape *f_Last;
   public:
     TAlternateItem(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast, int ANum);
     ~TAlternateItem();
};
*/

TAlternateItem::TAlternateItem(TBaseWorkShape *AWorkShape, int AIdAlt, int ANumAlt, int AParentIdAlt, int AParentNumAlt, bool AFirst)
{
   int m_step;
   f_IdAlt = AIdAlt;
   f_NumAlt = ANumAlt;
   f_ParentIdAlt = AParentIdAlt;
   f_ParentNumAlt = AParentNumAlt;
   f_WorkShape = AWorkShape;
   m_step = f_WorkShape->Step;
   f_First = AFirst;
   if (AFirst)
     f_ArrowWorkShape = new  TArrowWorkShape(f_WorkShape->StartPoint.x, f_WorkShape->StartPoint.y, m_step, 0, 0, 0);
   else
     f_ArrowWorkShape = new  TArrowWorkShape(f_WorkShape->EndPoint.x, f_WorkShape->EndPoint.y, m_step, 0, 0, 0);
   f_ArrowWorkShape->BrushStyle = bsSolid;
   f_ArrowWorkShape->Init();
   f_ArrowWorkShape->AddNodeHint(f_IdAlt);
   f_Entered = false;
   f_Visible = true;
   f_OtherWorkShape = NULL;

}

TAlternateItem::~TAlternateItem()
{
   delete f_ArrowWorkShape;
}


void __fastcall TAlternateItem::SetArrowColor(TColor AValue)
{
    f_ArrowColor = AValue;

}


void __fastcall TAlternateItem::SetEnterArrowColor(TColor AValue)
{
    f_EnterArrowColor = AValue;
}


/*
class TAlternateController
{
   private:
     TList *f_List;
     void FreeList();
   public:
     TAlternateController();
     ~TAlternateController();
};
*/

TAlternateController::TAlternateController(HWND AOwnerForm)
{
    f_List = new TList;
    FOnListChange = NULL;
    f_OwnerForm = AOwnerForm;
    f_ArrowColor = TColor(0);
    f_EnterArrowColor = TColor(0);
    f_PenColor = TColor(0);
    f_PenWidth = 1;
    f_LEControl = false;
    f_WndHandler = 0;
    f_UnderControl = NULL;
    f_ClipPath = new TClipPath;
    f_UpdateAlternateList = false;
}

TAlternateController::~TAlternateController()
{
   FreeList();
   delete f_List;
   delete f_ClipPath;
}


void TAlternateController::FreeList()
{
   TAlternateItem* Item;
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      delete Item;
      Item = NULL;
      f_List->Delete(i);
   }
}


int TAlternateController::FindAlternateItem(TBaseWorkShape *AWorkShape, bool AFirst)
{
   TAlternateItem* Item;
   TBaseWorkShape *Other = NULL;
   if (AFirst)
     Other = FindPriorWorkShape(AWorkShape);
   else
     Other = FindNextWorkShape(AWorkShape);
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if ((Item->WorkShape == AWorkShape) && (Item->First == AFirst) )
        return i;
      if ((Item->WorkShape == Other) && (Item->First == !AFirst) )
        return i;

   }
   return -1;
}


void TAlternateController::DoAddAlternateItem(TBaseWorkShape *AWorkShape, int AId, int ANumAlt,
  int AParentId, int AParentNumAlt, bool AFirst)
{
   TAlternateItem* Item;
   TBaseWorkShape *Other;
   int idx = FindAlternateItem(AWorkShape, AFirst);
   if (idx >= 0)
   {
     Item = static_cast<TAlternateItem*>(f_List->Items[idx]);
     Item->ArrowWorkShape->AddNodeHint(AId);
     if (Item->WorkShape != AWorkShape)
       Item->OtherWorkShape = AWorkShape;
   }

   else
   {
     Item = new TAlternateItem(AWorkShape, AId, ANumAlt, AParentId, AParentNumAlt, AFirst);
     Item->ArrowWorkShape->PenWidth = f_PenWidth;
     Item->ArrowWorkShape->LEControl = f_LEControl;
     Item->ArrowWorkShape->WndHandler = f_WndHandler;
     Item->ArrowWorkShape->UnderControl = f_UnderControl;
     Item->ArrowWorkShape->BrushColor = f_ArrowColor;
     Item->ArrowColor = f_ArrowColor;//передача цвета линий для стрелок
     Item->EnterArrowColor = f_EnterArrowColor;//передача цвета линий для стрелок
     f_List->Add(Item);
     if (FOnListChange && f_UpdateAlternateList) OnListChange();
   }
   f_ClipPath->Add(Item->ArrowWorkShape->GetRegionRect(), 0);
}


void TAlternateController::DoDeleteAlternateItem(TBaseWorkShape *AWorkShape, int AId, int ANumAlt, bool AFirst)
{
   TRect R;
   TAlternateItem* Item;
   int idx = FindAlternateItem(AWorkShape, AFirst);
   if ( idx == -1 ) return;
   Item = static_cast<TAlternateItem*>(f_List->Items[idx]);
   Item->ArrowWorkShape->DeleteNodeHint(AId);
   R = Item->ArrowWorkShape->GetRegionRect();
   if ( Item->ArrowWorkShape->IsEmptyNodeHint() )
   {
     Item->WorkShape->OnAfterLinePrepare = NULL;
     delete Item;
     Item = NULL;
     f_List->Delete(idx);
     if (FOnListChange && f_UpdateAlternateList) OnListChange();
   }
   f_ClipPath->Add(R, 0);
}


bool TAlternateController::AddAlternateItem(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast, int AId, int ANumAlt,
  int AParentId, int AParentNumAlt)
{
   if ( (!AWSFirst) || (!AWSLast) ) return false;
   if ( AWSFirst->ParentShapeID != AWSLast->ParentShapeID) return false;
   f_ClipPath->Clear();
   DoAddAlternateItem(AWSFirst, AId, ANumAlt, AParentId, AParentNumAlt, true);
   DoAddAlternateItem(AWSLast, AId, ANumAlt, AParentId, AParentNumAlt, false);
   SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
   return true;
}


void TAlternateController::DeleteAlternateItem(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast, int AId, int ANum)
{
   f_ClipPath->Clear();
   DoDeleteAlternateItem(AWSFirst,AId,  ANum, true);
   DoDeleteAlternateItem(AWSLast,AId,  ANum, false);
   SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
}


void TAlternateController::DeleteAlternateItem2(int AId, bool ASendMessage)
{
   TRect R;
   TAlternateItem* Item;
   f_ClipPath->Clear();
   bool m_del = false;
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      for (int j = 0; j <= Item->ArrowWorkShape->CountNodeHint; j++)
      {
        if ( (Item->ArrowWorkShape->NodeHind[j] == AId)  )
        {
           m_del = true;
           Item->ArrowWorkShape->DeleteNodeHint(AId);
           R = Item->ArrowWorkShape->GetRegionRect();
           if ( Item->ArrowWorkShape->IsEmptyNodeHint() )
           {
              Item->WorkShape->OnAfterLinePrepare = NULL;
              delete Item;
              Item = NULL;
              f_List->Delete(i);
              if (FOnListChange && f_UpdateAlternateList) OnListChange();
              f_ClipPath->Add(R, 0);
              break;
           }
           f_ClipPath->Add(R, 0);

        }
      }
   }

   if (m_del && ASendMessage)
     SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
}



TBaseWorkShape* TAlternateController::FindNextWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETNEXTWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}


TBaseWorkShape* TAlternateController::FindPriorWorkShape(TBaseWorkShape *W)
{
   TBaseWorkShape* Res = NULL;
   SendMessage(f_OwnerForm, WM_GD_GETPRIORWORKSHAPE, WPARAM(W), LPARAM(&Res));
   return Res;
}

void TAlternateController::FillAlternateList(TAlternateList* AlternateList, int AParentShapeID,
   int AId, int ANumAlt)
{
   TAlternateItem* Item;
   AlternateList->f_List->Clear();
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if ( (Item->WorkShape->ParentShapeID == AParentShapeID) &&
           (Item->IdAltParent == AId) && (Item->NumAltParent == ANumAlt)


           )
         AlternateList->f_List->Add(Item);
   }
}


void __fastcall TAlternateController::SetArrowColor(TColor AValue)
{
   TAlternateItem* Item;
   {
     f_ArrowColor = AValue;
     for (int i = f_List->Count - 1; i >= 0; i--)
     {
       Item = static_cast<TAlternateItem*>(f_List->Items[i]);
       Item->ArrowColor = f_ArrowColor;
       Item->ArrowWorkShape->BrushColor = f_ArrowColor;
     }
   }

}


void __fastcall TAlternateController::SetEnterArrowColor(TColor AValue)
{
   TAlternateItem* Item;
   {
     f_EnterArrowColor = AValue;
     for (int i = f_List->Count - 1; i >= 0; i--)
     {
       Item = static_cast<TAlternateItem*>(f_List->Items[i]);
       Item->EnterArrowColor = f_EnterArrowColor;
     }
   }
}


void __fastcall TAlternateController::SetPenColor(TColor AValue)
{
   TAlternateItem* Item;
   {
     f_PenColor = AValue;
     for (int i = f_List->Count - 1; i >= 0; i--)
     {
       Item = static_cast<TAlternateItem*>(f_List->Items[i]);
       Item->ArrowWorkShape->PenColor = f_PenColor;
     }
   }
}


void __fastcall TAlternateController::SetPenWidth(int AValue)
{
   TAlternateItem* Item;
   {
     f_PenWidth = AValue;
     for (int i = f_List->Count - 1; i >= 0; i--)
     {
       Item = static_cast<TAlternateItem*>(f_List->Items[i]);
       Item->ArrowWorkShape->PenWidth = f_PenWidth;
     }
   }
}


void TAlternateController::RecalcCoordArrow()
{
   TPoint P, PWS;
   TAlternateItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      P = Item->ArrowWorkShape->StartPoint;
      if (Item->First)
        PWS =  Item->WorkShape->FirstLine->PointStart;//; Item->ArrowWorkShape->StartPoint = WS->StartPoint;
      else
//        PWS =  Item->WorkShape->LastLine->PointEnd;// Item->ArrowWorkShape->StartPoint = WS->EndPoint;
          PWS =  Item->WorkShape->EndPoint;
      Item->ArrowWorkShape->StartPoint = PWS;
      Item->ArrowWorkShape->SetOffsetPosition(-P.x + PWS.x, -P.y + PWS.y);
   }
}





void TAlternateController::VisibleArrow(TBaseWorkShape *W, bool AVisible)
{
   TAlternateItem* Item;
   int cnt = 0;
   TRect R;
   TPoint P, PWS;
   f_ClipPath->Clear();
   TBaseWorkShape *Other = FindNextWorkShape(W);
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if ( (Item->WorkShape == W) || ((!AVisible) && (Item->WorkShape == Other) && Item->First))
      {
         Item->Visible = AVisible;
         Item->ArrowWorkShape->LEActive = AVisible;
         R = Item->ArrowWorkShape->GetRegionRect();
         f_ClipPath->Add(R, 0);
         cnt++;
      }
   }
   if (AVisible)
     RecalcCoordArrow();
   if (cnt)
     SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
}


void TAlternateController::VisibleArrowAll(bool AVisible)
{

   TAlternateItem* Item;
   int cnt = 0;
   TRect R;
   f_ClipPath->Clear();
   for (int i = f_List->Count - 1; i >= 0; i--)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      Item->Visible = AVisible;
      Item->ArrowWorkShape->LEActive = AVisible;
      R = Item->ArrowWorkShape->GetRegionRect();
      f_ClipPath->Add(R, 0);
      cnt++;
   }
   if (AVisible)
     RecalcCoordArrow();
   if (cnt)
     SendMessage(f_OwnerForm, WM_GD_PAINT, 1, LPARAM(f_ClipPath->GetCliptRgn()));
}


int TAlternateController::IsExistsAlternate(TBaseWorkShape *AWSFirst, TBaseWorkShape *AWSLast)
{
   TAlternateItem *Item1, *Item2;
   int idx1 = FindAlternateItem(AWSFirst, true);
   int idx2 = FindAlternateItem(AWSLast, false);
   if ( (idx1 >= 0) && (idx2 >= 0) )// return 1;
   {
     Item1 = static_cast<TAlternateItem*>(f_List->Items[idx1]);
     Item2 = static_cast<TAlternateItem*>(f_List->Items[idx2]);
     for (int i = 0 ; i <= Item1->ArrowWorkShape->CountNodeHint -1; i++)
     {
        for (int j = 0 ; j <= Item2->ArrowWorkShape->CountNodeHint -1; j++)
        {
           if (Item1->ArrowWorkShape->NodeHind[i] == Item2->ArrowWorkShape->NodeHind[j])
             return  Item1->ArrowWorkShape->NodeHind[i];
        }
     }
   }
   return -1;





}


void TAlternateController::CoordinateCorrect()
{
   //применяет смещение только для вновь созданных альтернатив
/*   TPoint P;
   TAlternateItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if (Item->NoOffset)
      {*/
        /*if ( (Item->WorkShape->ParentShapeID == AParentShapeID) &&
           (Item->IdAltParent == AId) && (Item->NumAltParent == ANumAlt)
           )*/
/*        {
          P = Item->ArrowWorkShape->StartPoint;
          P.x += AX;
          P.y += AY;
          Item->ArrowWorkShape->StartPoint = P;
          Item->ArrowWorkShape->SetOffsetPosition(AX, AY);
        }
        Item->NoOffset = false;
      }
   }
*/
   TPoint P1, P2;
   TAlternateItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      {
         P1 = Item->ArrowWorkShape->StartPoint;
         if (Item->First)
           P2 = Item->WorkShape->StartPoint;
         else
           P2 = Item->WorkShape->EndPoint;
         if ( (P1.x != P2.x) || ( P1.y != P2.y) )
         {
            Item->ArrowWorkShape->StartPoint = P2;
            Item->ArrowWorkShape->SetOffsetPosition( P2.x - P1.x, P2.y - P1.y);
         }

      }
   }


}


void TAlternateController::RecalcPosition(int AParentShapeID, int AId, int ANumAlt)
{
   TPoint P1, P2;
   TAlternateItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if ( (Item->WorkShape->ParentShapeID == AParentShapeID) &&
           (Item->IdAltParent == AId) && (Item->NumAltParent == ANumAlt)
           )
      {
         P1 = Item->ArrowWorkShape->StartPoint;
         if (Item->First)
           P2 = Item->WorkShape->StartPoint;
         else
           P2 = Item->WorkShape->EndPoint;
         if ( (P1.x != P2.x) || ( P1.y != P2.y) )
         {
            Item->ArrowWorkShape->StartPoint = P2;
            Item->ArrowWorkShape->SetOffsetPosition( P2.x - P1.x, P2.y - P1.y);
         }

      }
   }
}

bool TAlternateController::DeleteWorkShape(TBaseWorkShape *AWS)
{
   TAlternateItem* Item;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      if (Item->WorkShape == AWS)
      {
         if(!Item->OtherWorkShape)
           return false;
         Item->WorkShape = Item->OtherWorkShape;
         Item->First = !Item->First;
      }
   }
   return true;
}


bool TAlternateController::GetWSToAlternate(int AId, TBaseWorkShape  **AWSFirst, TBaseWorkShape  **AWSLast)
{
   TAlternateItem* Item;
   TArrowWorkShape* Shape = NULL;
   int m_f = 0;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      for (int j = 0 ; j <= Item->ArrowWorkShape->CountNodeHint - 1; j++)
      {
         if ( Item->ArrowWorkShape->NodeHind[j] == AId )
         {
            m_f++;
            (*AWSFirst) = Item->WorkShape;
            (*AWSFirst)->Tag = 1;
            if (Item->First)
              (*AWSFirst)->Tag = 0;
            Shape  = Item->ArrowWorkShape;
            break;
         }
      }
      if (m_f == 1) break;
   }

   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Item = static_cast<TAlternateItem*>(f_List->Items[i]);
      for (int j = 0 ; j <= Item->ArrowWorkShape->CountNodeHint - 1; j++)
      {
         if ( (Item->ArrowWorkShape->NodeHind[j] == AId) && (Shape != Item->ArrowWorkShape) )
         {
            m_f++;
            (*AWSLast) = Item->WorkShape;
            (*AWSLast)->Tag = 1;
            if (Item->First)
              (*AWSLast)->Tag = 0;
            break;
         }
      }
      if (m_f == 2) break;
   }
   return (m_f == 2);
}


void TAlternateController::ClearAll()
{
   FreeList();
}


TAlternateList::TAlternateList()
{
   f_List = new TList;
   f_pos = 0;
}


TAlternateList::~TAlternateList()
{
   delete f_List;
}


void TAlternateList::ClearAll()
{
   f_List->Clear();
}


int __fastcall TAlternateList::GetCount()
{
   return  f_List->Count;
}


TAlternateItem* TAlternateList::First()
{
   TAlternateItem* Res = NULL;
   f_pos = 0;
   if (f_List->Count > 0)
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}


TAlternateItem* TAlternateList::Next()
{
   TAlternateItem* Res = NULL;
   f_pos++;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}

TAlternateItem* TAlternateList::Prior()
{
   TAlternateItem* Res = NULL;
   f_pos--;
   if ((f_List->Count > f_pos) && (f_pos >= 0) )
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   return Res;
}

TAlternateItem* TAlternateList::Last()
{
   TAlternateItem* Res = NULL;
   if (f_List->Count > 0)
   {
      f_pos = f_List->Count - 1;
      Res = static_cast<TAlternateItem*>(f_List->Items[f_pos]);
   }
   return Res;
}




bool TAlternateList::EnterByShape(TBaseShape *AFlagShape)
{
   bool res = false;
   TAlternateItem *Tmp, *Item = NULL;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Tmp = static_cast<TAlternateItem*>(f_List->Items[i]);
      if (Tmp->ArrowWorkShape->GetWorkShape(0) == AFlagShape )
      {
        Item = Tmp;
        break;
      }
   }
   if (Item)
   {
       Tmp->ArrowWorkShape->BrushColor = Item->EnterArrowColor;
       Item->Entered = true;
       res = true;
   }
   return res;
}


bool TAlternateList::LeaveByShape(TBaseShape *AFlagShape)
{
   bool res = false;
   TAlternateItem *Tmp, *Item = NULL;
   for (int i = 0; i <= f_List->Count - 1; i++)
   {
      Tmp = static_cast<TAlternateItem*>(f_List->Items[i]);
      if (Tmp->ArrowWorkShape->GetWorkShape(0) == AFlagShape )
      {
        Item = Tmp;
        break;
      }
   }
   if (Item)
   {
       Tmp->ArrowWorkShape->BrushColor = Item->ArrowColor;
       Item->Entered = false;
       res = true;
   }
   return res;
}






