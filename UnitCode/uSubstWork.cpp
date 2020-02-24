//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSubstWork.h"
#include "uTfeRectShape.h"
#include "uTfeRhombShape.h"
#include "uTfeEllShape.h"
#include "uTfeHexahedronShape.h"
#include "uCompositeBaseWork.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TSubstWork::TSubstWork()
{
   f_ListShapes = new TList;
   f_ListLines = new TList;
   f_PenColor = clBlack;
   f_FirstLine = NULL;
   f_LastLine = NULL;
   f_FixColorArr = new TDynamicArray;
}

TSubstWork::~TSubstWork()
{
   FreeListShapes();
   FreeListLines();
   delete f_ListShapes;
   delete f_ListLines;
   delete f_FixColorArr;
}

void TSubstWork::FreeListShapes()
{
   TSubstWorkItem *Item;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      Item = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      delete Item;
      f_ListShapes->Items[i] = NULL;
   }
}



void TSubstWork::FreeListLines()
{
   TBaseLine *mLine;
   for (int i = 0; i <= f_ListLines->Count - 1; i++ )
   {
      mLine = static_cast<TBaseLine*>(f_ListLines->Items[i]);
      delete mLine;
      f_ListLines->Items[i] = NULL;

   }
}

TPoint TSubstWork::CheckOffset(TBaseWorkShape* ABaseWorkShape)
{
   int m_x, m_y;
   if ( (ABaseWorkShape->StartPoint.x != ABaseWorkShape->BaseStartPoint.x) ||
     (ABaseWorkShape->StartPoint.y != ABaseWorkShape->BaseStartPoint.y) )
   {
      m_x = ABaseWorkShape->BaseStartPoint.x - ABaseWorkShape->StartPoint.x;
      m_y = ABaseWorkShape->BaseStartPoint.y - ABaseWorkShape->StartPoint.y;
      return TPoint(m_x, m_y);
   }
   return TPoint(0, 0);

}


TBaseShape* TSubstWork::CloneShape(TBaseShape* ADest)
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
   ADest->CopyObject(mShape);
   return mShape;
}

TBaseLine*  TSubstWork::CloneLine(TBaseLine* ADest)
{
   if (!ADest) return NULL;
   TBaseLine* mLine = new TBaseLine(0, 0, 0, 0, 0);
   ADest->CopyObject(mLine);
   return mLine;
}



void TSubstWork::AddShape(TBaseWorkShape* ABaseWorkShape, bool IncFLine, bool IncLLine)
{
   TBaseShape *mShape, *mNewShape;
   TRectLine *rLine;
   TBaseLine *bLine, *bNewLine;
 //  f_FirstLine = NULL;
 //  f_LastLine = NULL;
   TPoint P = CheckOffset(ABaseWorkShape);
   for (int i = 0; i <= ABaseWorkShape->WorkShapesCount - 1; i++ )
   {
      mShape = static_cast<TBaseShape*>(ABaseWorkShape->GetWorkShape(i));
      mNewShape = CloneShape(mShape);
      TSubstWorkItem *WI = new TSubstWorkItem;
      WI->SetShape(mNewShape);
      WI->SetOffsetPosition(P.x, P.y);
      f_ListShapes->Add(WI);
      for (int j = 0; j <= mShape->WorkLineCount - 1; j++)
      {
        rLine = mShape->WorkLine[j];
        if (!IncFLine)
          if ( rLine == ABaseWorkShape->FirstLine )
            continue;
        if (!IncLLine)
          if ( rLine == ABaseWorkShape->LastLine )
            continue;
        bLine = rLine->FirstBaseLine();
        while (bLine)
        {
           bNewLine = CloneLine(bLine);
           if (bNewLine)
           {
             if ( (!f_FirstLine) && (rLine == ABaseWorkShape->FirstLine) )
                f_FirstLine = bNewLine;
             if ( rLine == ABaseWorkShape->LastLine )
                f_LastLine = bNewLine;

             bNewLine->ApplyOffset(P.x, P.y);
             f_ListLines->Add(bNewLine);
             WI->AddWorkLine(bNewLine);
           }
           bLine = rLine->NextBaseLine();
        }
      }
   }
}


TBaseShape* TSubstWork::AddBaseShape(TBaseShape* ABaseShape, TBaseWorkShape* ABaseWorkShape)
{
   TBaseShape *mNewShape;
   if (ABaseShape)
   {
     TPoint P = CheckOffset(ABaseWorkShape);
     mNewShape = CloneShape(ABaseShape);
     TSubstWorkItem *WI = new TSubstWorkItem;
     WI->SetShape(mNewShape);
     WI->SetOffsetPosition(P.x, P.y);
     f_ListShapes->Add(WI);
     f_LastLine = NULL;
     return  mNewShape;
   }
   return NULL;
}


void TSubstWork::AddShapeNoLines(TBaseWorkShape* ABaseWorkShape)
{
   TBaseShape *mShape, *mNewShape;
   TPoint P = CheckOffset(ABaseWorkShape);
   for (int i = 0; i <= ABaseWorkShape->WorkShapesCount - 1; i++ )
   {
      mShape = static_cast<TBaseShape*>(ABaseWorkShape->GetWorkShape(i));
      mNewShape = CloneShape(mShape);
      TSubstWorkItem *WI = new TSubstWorkItem;
      WI->SetShape(mNewShape);
      WI->SetOffsetPosition(P.x, P.y);
      f_ListShapes->Add(WI);
   }
   f_LastLine = NULL;
}



void TSubstWork::Paint(TCanvas* ACanvas)
{
   TSubstWorkItem *WI;
   TBaseLine *mLine;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      WI->Paint(ACanvas);
   }
   for (int i = 0; i <= f_ListLines->Count - 1; i++ )
   {
      mLine = static_cast<TBaseLine*>(f_ListLines->Items[i]);
      mLine->Color = f_PenColor;
      mLine->Paint(ACanvas);
   }
}


TRect TSubstWork::GetAnyRect()
{
  TSubstWorkItem* WI;
  for (int i = 0 ; i <= f_ListShapes->Count - 1 ;i++)
  {
    WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
    return WI->GetAnyRect();
  }
  return TRect(0,0,0,0);
}


TRect TSubstWork::GetRectSummary(TRect ARect)
{
  TRect Res = ARect;
  TBaseLine *bLine;
  TSubstWorkItem* WI;
  for (int i = 0 ; i <= f_ListShapes->Count - 1 ;i++)
  {
    WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
    Res = WI->GetRectSummary(Res);
  }

  for (int i = 0; i <= f_ListLines->Count - 1; i++)
  {
     bLine = static_cast<TBaseLine*>(f_ListLines->Items[i]);
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

TRect __fastcall TSubstWork::GetMaxRect()
{
  TRect Res = GetAnyRect();
  Res = GetRectSummary(Res);
  return Res;
}


void  TSubstWork::SetOffsetPosition(int Ax, int Ay)
{
  TRect R;
  TBaseLine *baseLine;
  TSubstWorkItem* WI;
  for (int i = 0 ; i <= f_ListShapes->Count - 1 ;i++)
  {
    WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
    WI->SetOffsetPosition(Ax, Ay);
  }
/*
  for (int i = 0 ; i <= f_ListLines->Count - 1 ;i++)
  {
    baseLine = static_cast<TBaseLine*>(f_ListLines->Items[i]);
    baseLine->ApplyOffset(Ax, Ay);
  }
*/
}

TSubstWorkItem* TSubstWork::FindItem(int ABaseShapeID, TSubstWork **AFind)
{
   TSubstWorkItem *WI;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      if (WI->Type == 0)
      {
         if (WI->Shape->ID == ABaseShapeID)
         {
           *AFind = this;
           return WI;
         }
      }
      if (WI->Type == 1)
      {
          return WI->SubstWork->FindItem(ABaseShapeID, AFind);
      }
   }
   return NULL;
}


TPoint  TSubstWork::RecalcStartPoint()
{
   TPoint res = TPoint(0, 0);
   TSubstWorkItem *WI;
   if (FirstLine)
     res = FirstLine->PointStart;
   else
   {
     if (f_ListShapes->Count > 0)
     {
       WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[0]);
       res = WI->StartPoint;
     }
   }
   return res;
}

TPoint  TSubstWork::RecalcEndPoint()
{
   TPoint res = TPoint(0, 0);
   TSubstWorkItem *WI;
   if (LastLine)
     res = LastLine->PointEnd;
   else
   {
     if (f_ListShapes->Count > 0)
     {
       WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[f_ListShapes->Count - 1]);
       res = WI->EndPoint;
     }
   }
   return res;
}


void __fastcall TSubstWork::SetStartPoint(TPoint AValue)
{
   int m_x, m_y;
   TPoint m_startP = RecalcStartPoint();
   if ( (m_startP.x != AValue.x ) || (m_startP.y != AValue.y) )
   {
      m_x = AValue.x - m_startP.x;
      m_y = AValue.y - m_startP.y;
      SetOffsetPosition(m_x, m_y);
   }

}


TSubstWorkItem* __fastcall TSubstWork::GetSWItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= f_ListShapes->Count - 1)
     return static_cast<TSubstWorkItem*>(f_ListShapes->Items[AIndex]);
   else
     return NULL;
}

int __fastcall TSubstWork::GetSWItemCount()
{
   return  f_ListShapes->Count;
}

int __fastcall TSubstWork::GetStep()
{
   TSubstWorkItem *WI;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      if (WI->Type == 0)
        return WI->Shape->Step;
      else
        return WI->SubstWork->Step;
   }
   return 0;
}

TPoint __fastcall  TSubstWork::GetEndPoint()
{
   return RecalcEndPoint();
}

TPoint __fastcall  TSubstWork::GetStartPoint()
{
   return RecalcStartPoint();
}

void __fastcall TSubstWork::SetLineColor(TColor AValue)
{
   TSubstWorkItem *WI;
   f_LineColor = AValue;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      if (WI->Type == 0)
      {
        if (!FindFixedColor(WI->Shape))
          WI->Shape->PenColor = f_LineColor;
      }
      else
        WI->SubstWork->LineColor = f_LineColor;
   }


}

bool TSubstWork::FindFixedColor(TBaseShape* ABaseShape)
{
   TBaseShape* B;
   for (int i = 0; i <= f_FixColorArr->Count - 1; i++ )
   {
      B = static_cast<TBaseShape*>(f_FixColorArr->Items[i]);
      if (B == ABaseShape)
        return true;
   }
   return false;
}


bool TSubstWork::FixedColor(TBaseShape* ABaseShape)
{
    TSubstWork *WS;
    TSubstWorkItem* Item = FindItem(ABaseShape->ID, &WS);
    if (Item)
    {
       if (!FindFixedColor(ABaseShape))
          f_FixColorArr->Append(ABaseShape);
       return true;
    }
    return false;
}


TBaseShape* TSubstWork::FindTFE(int Ax, int Ay)
{
   TSubstWorkItem *WI;
   TBaseShape* Res = NULL;
   for (int i = 0; i <= f_ListShapes->Count - 1; i++ )
   {
      WI = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      if (WI->Type == 0)
      {
        if (PtInRect(&WI->Shape->GetRect(), TPoint(Ax, Ay)))
          return WI->Shape;
      }
      else
      {
        Res = WI->SubstWork->FindTFE(Ax, Ay);
        if (Res)
          return Res;
      }   
   }
   return NULL;
}


void TSubstWork::OffsetEndCoordinate(TSubstWork* AfterWork)
{
   TSubstWorkItem  *Item, *Next;
   int X_ofs = 0;
   for (int i = 0;  i <= f_ListShapes->Count - 1; i++)
   {
      Item = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i]);
      if (Item->SubstWork == AfterWork)
      {
        if (i < f_ListShapes->Count - 1)
        {
          Next = static_cast<TSubstWorkItem*>(f_ListShapes->Items[i + 1]);
          X_ofs = Item->EndPoint.x - Next->StartPoint.x;
          continue;
        }  
      }
      Item->StartPoint.x += X_ofs;
      Item->SetOffsetPosition(X_ofs, 0);
   }

}


/*
   int X_ofs = 0;
   for (int i = 0;  i <= f_ListSW->Count - 1; i++)
   {
      Item = static_cast<TSubstWork*>(f_ListSW->Items[i]);
      if (Item == AfterWork)
      {
        X_ofs = Item->EndPoint.x - Item->StartPoint.x;
        continue;
      }
      Item->StartPoint.x += X_ofs;
      Item->SetOffsetPosition(X_ofs, 0);
   }

*/
