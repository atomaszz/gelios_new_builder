//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "uCompositeBaseWork.h"
#include "uCommonGraph.h"
#include "uTfeRectShape.h"
#include "uTfeRhombShape.h"
#include "uTfeEllShape.h"
#include "uTfeHexahedronShape.h"
#include "uMessengers.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TCompositeBaseWorkItem
{
   private:
     TList *f_ListWL;
     TBaseShape *f_Shape;
     TCompositeBaseWork *f_CompositeWork;
   public:
     TCompositeBaseWorkItem();
     ~TCompositeBaseWorkItem();

};
*/

TCompositeBaseWorkItem::TCompositeBaseWorkItem()
{
    f_Shape = NULL;
    f_SavedShape = NULL;
    f_CompositeWorkList = new TList;
}


TCompositeBaseWorkItem::~TCompositeBaseWorkItem()
{
    if ( f_Shape )
      delete f_Shape;
    else
       FreeList();
    if (f_SavedShape && (!f_Shape) )
      delete f_SavedShape;
    delete f_CompositeWorkList;
}

void TCompositeBaseWorkItem::FreeList()
{
    TCompositeBaseWork* Item;
    for (int i = f_CompositeWorkList->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[i]);
       //delete Item;
       Item->FreeRef();
    }
    f_CompositeWorkList->Clear();
}

void TCompositeBaseWorkItem::Prepare()
{
    TCompositeBaseWork* Item;
    for (int i = f_CompositeWorkList->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[i]);
       Item->Prepare();
    }
}

void TCompositeBaseWorkItem::Paint(TCanvas *ACanvas)
{
    TCompositeBaseWork* Item;
    int mColor;
    if ( f_Shape )
    {
      mColor = GMess->SendMess(1, f_Shape->ID, 0);
      if (mColor != 0)
        f_Shape->PenColor = TColor(mColor);
      f_Shape->Paint(ACanvas);
    }
    for (int i = f_CompositeWorkList->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[i]);
       Item->Paint(ACanvas);
    }
}

void __fastcall TCompositeBaseWorkItem::SetBaseShape(TBaseShape *AShape)
{
   if ( f_CompositeWorkList->Count > 0 )
   {
      FreeList();
   }
   if ( f_Shape && ( f_Shape != AShape ) )
   {
      delete f_Shape;
      delete f_SavedShape;
   }
   f_Shape = AShape;

}

int __fastcall TCompositeBaseWorkItem::GetCompositeWorkCount()
{
   return  f_CompositeWorkList->Count;
}


TCompositeBaseWork* __fastcall TCompositeBaseWorkItem::GetCompositeWork(int AIndex)
{
    if (AIndex >= 0 && AIndex <= f_CompositeWorkList->Count - 1)
     return static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[AIndex]);
   else
     return NULL;
}

void TCompositeBaseWorkItem::AddCompositeWork(TCompositeBaseWork* AWork)
{
   if ( f_Shape )
   {
      f_SavedShape = f_Shape;
      f_Shape = NULL;
   }
   f_CompositeWorkList->Add(AWork);
}


void TCompositeBaseWorkItem::Degenerate()
{
    FreeList();
    f_Shape = f_SavedShape;
    f_SavedShape = NULL;
}


TBaseShape* TCompositeBaseWorkItem::FindTFE(int Ax, int Ay)
{
    TBaseShape* Res = NULL;
    if (f_Shape)
      if (PtInRect(&f_Shape->GetRect(), TPoint(Ax, Ay)))
        return  f_Shape;
    TCompositeBaseWork* Item;
    for (int i = f_CompositeWorkList->Count - 1; i >= 0; i--)
    {
       Item = static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[i]);
       Res = Item->FindTFE(Ax, Ay);
       if (Res)
         return Res;
    }
    return NULL;
}


TPoint __fastcall TCompositeBaseWorkItem::GetStartPoint()
{
    TPoint P = TPoint(0, 0);
    if (f_Shape)
      return f_Shape->PointTail_StartShape;
    if ( f_CompositeWorkList->Count > 0 )
    {
       TCompositeBaseWork* Item = CompositeWork[0];
       return Item->StartPoint;
    }
    return P;
}

TPoint __fastcall TCompositeBaseWorkItem::GetEndPoint()
{
    TPoint P = TPoint(0, 0);
    if (f_Shape)
      return f_Shape->PointTail_EndShape;
    if ( f_CompositeWorkList->Count > 0 )
    {
       TCompositeBaseWork* Item = CompositeWork[f_CompositeWorkList->Count - 1];
       return Item->EndPoint;
    }
    return P;
}



void TCompositeBaseWorkItem::ApplyOffset(int Ax, int Ay)
{
   TRect R;
   if (f_Shape)
   {
     R = f_Shape->BoundRect;
     R.Left = R.Left + Ax;
     R.Right = R.Right + Ax;
     R.Top = R.Top + Ay;
     R.Bottom = R.Bottom + Ay;
     f_Shape->BoundRect = R;
   }
   TCompositeBaseWork* Item;
   for (int i = 0; i <= f_CompositeWorkList->Count - 1;  i++)
   {
      Item = static_cast<TCompositeBaseWork*>(f_CompositeWorkList->Items[i]);
      Item->ApplyOffset(Ax, Ay);
   }
}

TRect TCompositeBaseWorkItem::GetAnyRect()
{
   if (f_Shape)
     return f_Shape->GetRect();
   if (f_CompositeWorkList->Count > 0 )
     return CompositeWork[0]->GetAnyRect();
   return TRect(0,0,0,0);
}


TRect __fastcall TCompositeBaseWorkItem::GetMaxRect()
{
  TRect Res = GetAnyRect();
  Res = GetRectSummary(Res);
  return Res;
}


TRect TCompositeBaseWorkItem::GetRectSummary(TRect ARect)
{
   TRect R_tmp;
   TCompositeBaseWork* W;
   TRect Res = ARect;
   if (f_Shape)
   {
     R_tmp =  f_Shape->GetRect();
     Res = RectSumm(Res, R_tmp);
     return Res;
   }
   if (f_CompositeWorkList->Count > 0 )
   {
     for (int i = 0; i <= CompositeWorkCount - 1; i++ )
     {
        W = CompositeWork[i];
        Res = RectSumm(Res, W->GetRectSummary(Res));
     }
     return Res;
   }
   return TRect(0, 0, 0, 0);  
}

void __fastcall TCompositeBaseWorkItem::SetStartPoint(TPoint AValue)
{
   int m_x, m_y;
   TPoint m_startP = StartPoint;
   if ( (m_startP.x != AValue.x ) || (m_startP.y != AValue.y) )
   {
      m_x = AValue.x - m_startP.x;
      m_y = AValue.y - m_startP.y;
      ApplyOffset(m_x, m_y);
   }
}

void TCompositeBaseWorkItem::OffsetEndCoordinate()
{
   TPoint P;
   if (CompositeWorkCount <= 1) return;
   P = CompositeWork[0]->EndPoint;
   for (int i = 1; i <= CompositeWorkCount - 1; i++)
   {
      CompositeWork[i]->StartPoint = P;
      P = CompositeWork[i]->EndPoint;
   }

}



TCompositeBaseWork::TCompositeBaseWork()
{
   f_ListItem = new TList;
   f_ListBL = new TList;
   f_ListRectLine = new TList;
   f_TopBorder = 0;
   f_OffsetTop = 0;
   f_LastLineBend = 0;
   f_FirstLineBend = 0;
   f_ColorSetup = NULL;
   f_Selected = false;
   f_Ref = 1;
   f_History = new TCompositeStack2;
   f_ConvertedBWS = NULL;
}


TCompositeBaseWork::~TCompositeBaseWork()
{
   FreeListItem();
   FreeListBL();
   FreeListRectLine();
   delete  f_ListItem;
   delete  f_ListBL;
   delete  f_ListRectLine;
   delete  f_History;
}

TCompositeBaseWork* TCompositeBaseWork::CopyRef()
{
   f_Ref++;
   return this;
}

void TCompositeBaseWork::FreeRef()
{
   f_Ref--;
   if (!f_Ref)
     delete this;
}


void TCompositeBaseWork::FreeListItem()
{
   TCompositeBaseWorkItem *Item;
   for (int i = f_ListItem->Count - 1; i >=0; i--)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      delete Item;
      f_ListItem->Delete(i);
   }
}

void TCompositeBaseWork::FreeListBL()
{
   TBaseLine *Item;
   for (int i = f_ListBL->Count - 1; i >= 0; i--)
   {
      Item  = static_cast<TBaseLine*>(f_ListBL->Items[i]);
      delete Item;
      f_ListBL->Delete(i);
   }
}

void TCompositeBaseWork::FreeListRectLine()
{
   TRectLine *Item;
   for (int i = f_ListRectLine->Count - 1; i >= 0; i--)
   {
      Item  = static_cast<TRectLine*>(f_ListRectLine->Items[i]);
      delete Item;
      f_ListRectLine->Delete(i);
   }
}


void TCompositeBaseWork::Paint(TCanvas *ACanvas)
{
   TCompositeBaseWorkItem *Item;
   TBaseLine *BL;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      Item->Paint(ACanvas);
   }
   for (int j = 0;  j <= f_ListBL->Count - 1; j++)
   {
      BL = static_cast<TBaseLine*>(f_ListBL->Items[j]);
//      BL->Color = f_ColorSetup->LineColor;
      BL->Paint(ACanvas);
   }
}

void TCompositeBaseWork::ApplyOffset(int Ax, int Ay)
{
   TCompositeBaseWorkItem *Item;
   TBaseLine *BL;
   TRectLine *RL;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      Item->ApplyOffset(Ax, Ay);
   }
   for (int j = 0;  j <= f_ListBL->Count - 1; j++)
   {
      BL = static_cast<TBaseLine*>(f_ListBL->Items[j]);
      BL->ApplyOffset(Ax, Ay);
   }
   for (int k = 0;  k <= f_ListRectLine->Count - 1; k++)
   {
      RL = static_cast<TRectLine*>(f_ListRectLine->Items[k]);
      RL->ApplyOffset(Ax, Ay);
   }
}



void TCompositeBaseWork::AddBaseShape(TBaseShape *ABaseShape, bool IsHaveChild)
{
   if (ABaseShape)
   {
     TCompositeBaseWorkItem *Item = new TCompositeBaseWorkItem;
     Item->BaseShape = ABaseShape;
     f_ListItem->Add(Item);
     if (f_ColorSetup)
     {
        Item->BaseShape->BrushColor = f_ColorSetup->BrushColor;
        if (IsHaveChild)
          Item->BaseShape->PenColor = f_ColorSetup->HaveChildColor;
        else
          Item->BaseShape->PenColor = f_ColorSetup->LineColor;
        Item->BaseShape->FrameColor = f_ColorSetup->FrameColorTFE;
        if ( f_ColorSetup->BrushTFE)
          Item->BaseShape->BrushStyle = bsSolid;
        else
          Item->BaseShape->BrushStyle = bsClear;
        Item->BaseShape->PenWidth = ( f_ColorSetup->BoldTFELine ?  2 : 1 );
        f_ColorSetup->GetFont(Item->BaseShape->Font);
       if (IsHaveChild)
         Item->BaseShape->Tag = 1;
     }

   }
}

void TCompositeBaseWork::AddWorkItemShape(TCompositeBaseWorkItem *ABaseWorkItem)
{
   f_ListItem->Add(ABaseWorkItem);
}


void TCompositeBaseWork::AddBaseLine(TBaseLine *BL)
{
   if (BL)
   {
      f_ListBL->Add(BL);
      if (f_ColorSetup)
      {
         BL->Color = f_ColorSetup->LineColor;
         BL->Width = ( f_ColorSetup->BoldTFELine ?  2 : 1 );
      }
   }
}


void TCompositeBaseWork::ReplaceShape(int IdShapeReplace, TCompositeBaseWork *ANew)
{
   TCompositeBaseWorkItem *Item;
   TCompositeBaseWorkItem *SI;
   TCompositeBaseWork *Find;
   TPoint PS;
   //for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
     // Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      SI = FindItem(IdShapeReplace, &Find);
      if (SI)
      {
         PS = SI->StartPoint;
         ANew->StartPoint = PS;
         SI->AddCompositeWork(ANew);
         Find->OffsetEndCoordinate(TPoint(0,0));
         return;
      }
   }
}



TPoint TCompositeBaseWork::OffsetEndCoordinate(TPoint AStart)
{
/*   TCompositeBaseWorkItem *Item, *Res = NULL;
   TPoint P;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      if (Item == AItem)
      {
         Res = Item;
         break;
      }
   }
   if (!Res) return;
   if (Res->CompositeWorkCount <= 1) return;
   P = Res->CompositeWork[0]->EndPoint;
   for (int i = 1; i <= Res->CompositeWorkCount - 1; i++)
   {
      Res->CompositeWork[i]->StartPoint = P;
      P = Res->CompositeWork[i]->EndPoint;
   }
   */

   TCompositeBaseWorkItem* Item;
   TPoint P = AStart;
   bool f_comp = false;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      if (!Item->BaseShape)
      {
         f_comp = true;
         break;
      }
   }
   if (f_comp)
   {
     for (int i = 0;  i <= f_ListItem->Count - 1; i++)
     {
        Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
        if (!Item->BaseShape)
        {
           P = Item->CompositeWork[0]->OffsetEndCoordinate(P);
           for (int j = 1; j <= Item->CompositeWorkCount - 1; j++)
           {
             Item->CompositeWork[j]->StartPoint = P;
             P = Item->CompositeWork[j]->OffsetEndCoordinate(P);
           }
        }
     }
    // return P;
    Prepare();

    //  if (Item->CompositeWorkCount <= 1) continue;
     // P = Item->CompositeWork[0]->OffsetEndCoordinate(P);
   }
   return EndPoint;

/*
   P = Item->EndPoint;
   Item = f_PainterList->Next();
   while (Item)
   {
      Item->StartPoint = P;
      P = Item->EndPoint;
      Item = f_PainterList->Next();
   }
 */
}

bool TCompositeBaseWork::ConvertWorkShape(TAlternateViewItemTFS *AWS, TAlternateView* AV)
{

   return false;
}

void TCompositeBaseWork::Prepare()
{
   TCompositeBaseWorkItem *Item;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      Item->Prepare();
   }
}

TCompositeBaseWorkItem* TCompositeBaseWork::GetItem(int ANum)
{
  TCompositeBaseWorkItem* Res = NULL;
  if ( (f_ListItem->Count > 0) && (ANum >= 0) && (ANum <= f_ListItem->Count - 1 ) )
    Res = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[ANum]);
  return Res;
}

int __fastcall TCompositeBaseWork::GetItemCount()
{
   return  f_ListItem->Count;
}



void __fastcall TCompositeBaseWork::SetTopBorder(int AValue)
{
/*   TSubstWork *Item;
   f_TopBorder = AValue;
   TRect R_tmp;
   int m_top = f_TopBorder;
   for (int i = 0;  i <= f_ListSW->Count - 1; i++)
   {
      Item = static_cast<TSubstWork*>(f_ListSW->Items[i]);
      R_tmp = Item->MaxRect;
      if (m_top >  R_tmp.Top)
        m_top = R_tmp.Top;
   }
   int m_y = f_TopBorder - m_top;
   if (m_y > 0)
   {
      SetOffsetPosition(0, m_y);
      f_OffsetTop = m_y;
   }     */
}

void TCompositeBaseWork::Appearance()
{
   return;
}

TBaseLine* __fastcall TCompositeBaseWork::GetBaseLineItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListBL->Count - 1)
     return static_cast<TBaseLine*>(f_ListBL->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TCompositeBaseWork::GetBaseLineCount()
{
   return  f_ListBL->Count;
}


void TCompositeBaseWork::HideLines()
{
   TBaseLine* BL;
   for (int i = 0; i <= BaseLineCount-1; i++)
   {
      BL = BaseLineItem[i];
      BL->Visible = false;
   }
}

void __fastcall TCompositeBaseWork::SetLineColor(TColor AValue)
{
/*   f_LineColor = AValue;
   TSubstWork *Item;
   TBaseLine* BL;
   for (int i = 0;  i <= f_ListSW->Count - 1; i++)
   {
      Item = static_cast<TSubstWork*>(f_ListSW->Items[i]);
      Item->LineColor  = f_LineColor;
   }
   for (int i = 0; i <= BaseLineCount-1; i++)
   {
      BL = BaseLineItem[i];
      BL->Color = f_LineColor;
   }
*/
}


TRect TCompositeBaseWork::GetMaxRect()
{
   TCompositeBaseWorkItem* Item;
   TRect R;
   TRect Res = TRect(0,0,0,0);
   TBaseLine* bLine;
   if ( f_ListItem->Count > 0 )
   {
     Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[0]);
     Res = Item->MaxRect;
     for (int i = 1;  i <= f_ListItem->Count - 1; i++)
     {
        Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
        R = Item->MaxRect;
        if (R.Right > Res.Right) Res.Right = R.Right;
        if (R.Bottom > Res.Bottom ) Res.Bottom  = R.Bottom;
        if (R.Left < Res.Left) Res.Left = R.Left;
        if (R.Top < Res.Top ) Res.Top  = R.Top;
     }
   }
   for (int i = 0; i <= f_ListBL->Count - 1; i++)
   {
     bLine = static_cast<TBaseLine*>(f_ListBL->Items[i]);
     if (bLine->X0 <  Res.Left) Res.Left = bLine->X0;
     if (bLine->X1 <  Res.Left) Res.Left = bLine->X1;
     if (bLine->X0 >  Res.Right) Res.Right = bLine->X0;
     if (bLine->X1 >  Res.Right) Res.Right = bLine->X1;

     if (bLine->Y0 <  Res.Top) Res.Top = bLine->Y0;
     if (bLine->Y1 <  Res.Top) Res.Top = bLine->Y1;
     if (bLine->Y0 >  Res.Bottom) Res.Bottom = bLine->Y0;
     if (bLine->Y1 >  Res.Bottom) Res.Bottom = bLine->Y1;
   }
   return Res;

}

TPoint __fastcall  TCompositeBaseWork::GetEndPoint()
{
   return TPoint(0, 0);
}


TBaseShape* TCompositeBaseWork::FindTFE(int Ax, int Ay)
{
   TCompositeBaseWorkItem* Item;
   TBaseShape* BS;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      BS = Item->FindTFE(Ax, Ay);
      if (BS)
        return BS;
   }
   return NULL;
}


TBaseShape* TCompositeBaseWork::CloneShape(TBaseShape* ADest)
{
   TBaseShape* mShape = NULL;
   if (!ADest) return NULL;
   switch(ADest->TypeShape)
   {
      case 5:
        mShape = new TTfeRectShape(0, 0, 0, 0);
        break;
      case 6:
        mShape = new TTfeRhombShape(0, 0, 0, 0);
        break;
      case 7:
        mShape = new TTfeEllShape(0, 0, 0, 0);
        break;
      case 8:
        mShape = new TTfeHexahedronShape(0, 0, 0, 0);
        break;
   }
   if (!mShape)  return NULL;
   mShape->Clon = ADest;
   ADest->CopyObject(mShape);
   return mShape;
}

TPoint __fastcall TCompositeBaseWork::GetStartPoint()
{
   return TPoint(0, 0);
}

void __fastcall TCompositeBaseWork::SetStartPoint(TPoint AValue)
{
   int m_x, m_y;
   TPoint m_startP = StartPoint;
   if ( (m_startP.x != AValue.x ) || (m_startP.y != AValue.y) )
   {
      m_x = AValue.x - m_startP.x;
      m_y = AValue.y - m_startP.y;
      ApplyOffset(m_x, m_y);
   }
}


TBaseLine* __fastcall TCompositeBaseWork::GetEndLine()
{
   return NULL;
}


TRect TCompositeBaseWork::GetAnyRect()
{
   TCompositeBaseWorkItem *Item;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      return Item->GetAnyRect();
   }
   return TRect(0,0,0,0);
}


TRect TCompositeBaseWork::GetRectSummary(TRect ARect)
{
  TRect Res = ARect;
  TBaseLine *bLine;
  TCompositeBaseWorkItem* WI;
  for (int i = 0 ; i <= f_ListItem->Count - 1 ;i++)
  {
    WI = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
    Res = WI->GetRectSummary(Res);
  }

  for (int i = 0; i <= f_ListBL->Count - 1; i++)
  {
     bLine = static_cast<TBaseLine*>(f_ListBL->Items[i]);
     if (bLine->Visible)
     {
       if (bLine->X0 <  Res.Left) Res.Left = bLine->X0;
       if (bLine->X1 <  Res.Left) Res.Left = bLine->X1;
       if (bLine->X0 >  Res.Right) Res.Right = bLine->X0;
       if (bLine->X1 >  Res.Right) Res.Right = bLine->X1;

       if (bLine->Y0 <  Res.Top) Res.Top = bLine->Y0;
       if (bLine->Y1 <  Res.Top) Res.Top = bLine->Y1;
       if (bLine->Y0 >  Res.Bottom) Res.Bottom = bLine->Y0;
       if (bLine->Y1 >  Res.Bottom) Res.Bottom = bLine->Y1;
     }  
  }
  return Res;
}

TCompositeBaseWorkItem* TCompositeBaseWork::FindItem(int ABaseShapeID,  TCompositeBaseWork **AFind)
{
   TCompositeBaseWorkItem *WI;
   TCompositeBaseWorkItem *Res = NULL;
   for (int i = 0; i <= f_ListItem->Count - 1; i++ )
   {
      WI = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      if (WI->BaseShape)
      {
         if (WI->BaseShape->ID == ABaseShapeID)
         {
           *AFind = this;
           return WI;
         }
      }
      for (int j = 0; j <= WI->CompositeWorkCount - 1; j++)
      {
          Res = WI->CompositeWork[j]->FindItem(ABaseShapeID, AFind);
          if (Res)
             return Res;
      }
   }
   return NULL;
}


bool TCompositeBaseWork::ContainedShape(int ABaseShapeID)
{
   TCompositeBaseWorkItem *WI;
   bool Res;
   for (int i = 0; i <= f_ListItem->Count - 1; i++ )
   {
      WI = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      if (WI->BaseShape)
      {
         if (WI->BaseShape->ID == ABaseShapeID)
         {
           return true;
         }
      }
      for (int j = 0; j <= WI->CompositeWorkCount - 1; j++)
      {
          Res = WI->CompositeWork[j]->ContainedShape(ABaseShapeID);
          if (Res)
             return Res;
      }
   }
   return false;
}



TBaseLine* TCompositeBaseWork::GetBaseLine(int AIndex)
{
   TBaseLine *Line = BaseLineItem[AIndex];
   if (!Line)
   {
     Line = new TBaseLine(0, 0, 0, 0, f_step);
     Line->Visible = false;
     AddBaseLine(Line);
   }
   return Line;
}

TBaseLine* TCompositeBaseWork::GetNewLine()
{
   TBaseLine *Line = new TBaseLine(0, 0, 0, 0, f_step);
   Line->Visible = false;
   AddBaseLine(Line);
   return Line;
}



void StretchLineX(TBaseLine* ALine, int Ax)
{
   int m_x0, m_x1, m_y0, m_y1;
   m_x0 = ALine->MinX;
   m_x1 = ALine->MaxX;
   m_y0 = ALine->MinY;
   m_y1 = ALine->MaxY;
   if ( (m_x0 < Ax) && (m_x1 > Ax) )
     m_x0 = Ax;
   else
   {
      if (Ax < m_x0)
        m_x0 = Ax;
      if (Ax > m_x1)
        m_x1 = Ax;
   }
   ALine->ApplyCoord(m_x0,  m_y0, m_x1, m_y1);
}

void StretchLineY(TBaseLine* ALine, int Ay)
{
   int m_x0, m_x1, m_y0, m_y1;
   m_x0 = ALine->MinX;
   m_x1 = ALine->MaxX;
   m_y0 = ALine->MinY;
   m_y1 = ALine->MaxY;
   if ( (m_y0 < Ay) && (m_y1 > Ay) )
     m_y0 = Ay;
   else
   {
      if (Ay < m_y0)
        m_y0 = Ay;
      if (Ay > m_y1)
        m_y1 = Ay;
   }
   ALine->ApplyCoord(m_x0,  m_y0, m_x1, m_y1);
}

void TCompositeBaseWork::ConvertWorkShapeFromBase(TBaseWorkShape *AWS, TAlternateView* AV)
{
   return;
}


void __fastcall TCompositeBaseWork::SetSelected(bool AValue)
{
   TCompositeBaseWorkItem* Item;
   TBaseLine *BL;
  // if (f_Selected != AValue)
   {
      f_Selected = AValue;
      for (int i = f_ListBL->Count - 1; i >= 0; i--)
      {
         BL  = static_cast<TBaseLine*>(f_ListBL->Items[i]);
         BL->Color = f_Selected ? f_ColorSetup->FrameColorTFS : f_ColorSetup->LineColor;
      }
      for (int i = 0;  i <= f_ListItem->Count - 1; i++)
      {
        Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
        if (Item->BaseShape)
        {
          if (f_Selected)
            Item->BaseShape->PenColor = f_ColorSetup->FrameColorTFS;
          else
            Item->BaseShape->PenColor = Item->BaseShape->Tag ? f_ColorSetup->HaveChildColor : f_ColorSetup->LineColor;
            if (Item->BaseShape->Clon->ParamAlt)
            {
              if (f_ColorSetup->AltParamShapeColorEnable)
              {
                Item->BaseShape->BrushStyle = bsSolid;
                Item->BaseShape->BrushColor = f_ColorSetup->AltParamShapeColor;
              }
              else
                Item->BaseShape->BrushStyle = bsClear;
              Item->BaseShape->PenColor = f_ColorSetup->AltParamLineColor;
            }
        }
        for (int j = 0; j <= Item->CompositeWorkCount - 1; j++)
          Item->CompositeWork[j]->SetSelected(AValue);
      }

  }
}


void TCompositeBaseWork::SetColorAll(TColor AColor)
{
   TCompositeBaseWorkItem* Item;
   TBaseLine *BL;
   for (int i = f_ListBL->Count - 1; i >= 0; i--)
   {
      BL  = static_cast<TBaseLine*>(f_ListBL->Items[i]);
      BL->Color = AColor;
   }
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
     Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
     if (Item->BaseShape)
       Item->BaseShape->PenColor = AColor;
     for (int j = 0; j <= Item->CompositeWorkCount - 1; j++)
       Item->CompositeWork[j]->SetColorAll(AColor);
   }
}

void TCompositeBaseWork::SetBrushColorAll(TColor AColor)
{
   TCompositeBaseWorkItem* Item;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
     Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
     if (Item->BaseShape)
       Item->BaseShape->BrushColor = AColor;
     for (int j = 0; j <= Item->CompositeWorkCount - 1; j++)
       Item->CompositeWork[j]->SetBrushColorAll(AColor);

   }
}

void TCompositeBaseWork::SetBrushStyleAll(TBrushStyle AStyle)
{
   TCompositeBaseWorkItem* Item;
   for (int i = 0;  i <= f_ListItem->Count - 1; i++)
   {
     Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
     if (Item->BaseShape)
       Item->BaseShape->BrushStyle = AStyle;
     for (int j = 0; j <= Item->CompositeWorkCount - 1; j++)
       Item->CompositeWork[j]->SetBrushStyleAll(AStyle);

   }
}



TRectLine* __fastcall TCompositeBaseWork::GetFirstLine()
{
   return NULL;
}


void TCompositeBaseWork::AddRectLine(TRectLine *ARectLine)
{
   f_ListRectLine->Add(ARectLine);
}


void TCompositeBaseWork::GetAllLines(TDynamicArray *R, bool AMarkFirst)
{
   int i, j;
   TCompositeBaseWorkItem *Item;
   TBaseLine *BL;
   for (i = f_ListBL->Count - 1; i >= 0; i--)
   {
      BL  = static_cast<TBaseLine*>(f_ListBL->Items[i]);
      if (AMarkFirst && BL->Tag)
        BL->Tag2 = BL->Tag;
      R->Append(BL);
   }
   for (i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      for (j = 0; j <= Item->CompositeWorkCount - 1; j++)
         Item->CompositeWork[j]->GetAllLines(R, false);
   }
}

void TCompositeBaseWork::GetAllShapes(TDynamicArray *R)
{
   int i, j;
   TCompositeBaseWorkItem *Item;
   for (i = 0;  i <= f_ListItem->Count - 1; i++)
   {
      Item = static_cast<TCompositeBaseWorkItem*>(f_ListItem->Items[i]);
      if (Item->BaseShape)
        R->Append(Item->BaseShape);
      for (j = 0; j <= Item->CompositeWorkCount - 1; j++)
         Item->CompositeWork[j]->GetAllShapes(R);
   }
}

void TCompositeBaseWork::MakeFirstLine(TPoint AStart, int ABend)
{
   return;
}

void TCompositeBaseWork::DeleteLine(void *Line)
{
  int index = f_ListBL->IndexOf(Line);
  if (index >= 0)
  {
     TBaseLine *Item = static_cast<TBaseLine*>(f_ListBL->Items[index]);
     delete Item;
     f_ListBL->Delete(index);
  }
}


void  TCompositeBaseWork::TrimFirstLine(TPoint APStart, TPoint APEnd)
{
   TPoint PS, PE, PC;
//   int mx, my;
   TRectLine* RL = FirstLine;
   if (RL)
   {
     //StartPoint = APStart;
     PE =  RL->PointEnd;
     PS = PointAdd(PE, -f_step, 0);
    // RL->SetCoord(APStart., APStart.y, APStart.x + f_step, APStart.y, 0);
     RL->SetCoord(PS.x, PS.y, PE.x , PE.y, 0);
    // Prepare();

      }
//     int mX = RL->xEnd - APEnd.x ;
//     int mY = RL->yEnd - APEnd.y;

/*
     PS = RL->PointStart;
     PE = RL->PointEnd;
     if (PS.x > PE.x)
       PC.x = PE.x;
     else
       PC.x = PS.x;

     if (PS.y > PE.y)
       PC.y = PE.y;
     else
       PC.y = PS.y;

     RL->SetCoord(PC.x - f_step, PC.y, PC.x + f_step, PC.y, 0);

   }   */
}








