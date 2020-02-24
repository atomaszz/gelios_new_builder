//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uArrowShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
class TNodeHint
{
   private:
     int f_Num;
   public:
     TNodeHint(int ANum);
     __property int Num = {read = f_Num}

};

class TArrowShape: public TBaseShape
{
  private:
    TPoint Region[7];
    TList* NodeHintList;
    void FreeNodeHintList();
    void DrawHint(TCanvas *Canvas);
    void CalcRegion();
  public:
    TArrowShape(int X, int Y, int step, int number=0);//:TBaseShape(number);
    ~TArrowShape();
    bool AddNodeHint(int ANum);
    bool DeleteNodeHint(int ANum);
    bool IsEmptyNodeHint();
    void  Paint(TCanvas *Canvas);
};

*/


TNodeHint::TNodeHint(int ANum)
{
   f_Num = ANum;
}


void TArrowShape::CalcRegion()
{
   Region[0] = TPoint(BoundRect.Left +int(0.25*F_Step), BoundRect.Top);
   Region[1] = TPoint(BoundRect.Left +int(0.25*F_Step), BoundRect.Top+int(2*F_Step));
   Region[2] = TPoint(BoundRect.Left, Region[1].y);
   Region[3] = TPoint(BoundRect.Left + int(0.5*F_Step), BoundRect.Top+int(3*F_Step));
   Region[4] = TPoint(BoundRect.Left + F_Step, Region[1].y);
   Region[5] = TPoint(BoundRect.Left + int(0.75*F_Step), Region[1].y);
   Region[6] = TPoint(Region[5].x, Region[0].y);

}

void TArrowShape::DrawHint(TCanvas *Canvas)
{
   int i;
   int t_w, t_h;
   int x, y;
   TNodeHint *N;
   AnsiString h;
   TPoint P = TPoint(BoundRect.Left +int(0.5*F_Step), BoundRect.Top);
   for (i = 0; i<=NodeHintList->Count - 1; i++)
   {
      N = static_cast<TNodeHint*>(NodeHintList->Items[i]);
      h = "( "+IntToStr(N->Num)+" )";
      t_w = Canvas->TextWidth(h);
      t_h = Canvas->TextHeight(h);
      t_h = (t_h + 2)*(i+1);
      x = P.x - int(t_w/2);
      y = P.y - t_h;
      Canvas->TextOut(x, y, h);
   }
}

void TArrowShape::Paint(TCanvas *Canvas)
{
  SaveCanvas(Canvas);
  TBaseShape::Paint(Canvas);
  CalcRegion();
  Canvas->Polygon(Region, 6);
  Canvas->Brush->Style = bsClear;
  DrawHint(Canvas);
  RestoreCanvas(Canvas);
}

TArrowShape::TArrowShape(int X, int Y, int step, int number):TBaseShape(X, Y, step, number)
{
   TRect R;
   F_TypeShape = 80;
   NodeHintList = new TList;
   R.Left = X - int(0.5*step);
   R.Top = Y - step*3;
   R.Right = X + int(0.5*step);
   R.Bottom = Y;
   BoundRect = R;
}

void TArrowShape::FreeNodeHintList()
{
   int i;
   TNodeHint *N;
   for (i = NodeHintList->Count - 1; i>=0; i--)
   {
      N = static_cast<TNodeHint*>(NodeHintList->Items[i]);
      delete N;
      N = NULL;
      NodeHintList->Delete(i);
   }
}

TArrowShape::~TArrowShape()
{
   FreeNodeHintList();
   delete NodeHintList;
}


bool TArrowShape::AddNodeHint(int ANum)
{
   int i;
   TNodeHint *N;
   for (i = NodeHintList->Count - 1; i>=0; i--)
   {
      N = static_cast<TNodeHint*>(NodeHintList->Items[i]);
      if ( N->Num == ANum)
        return false;
   }
   N = new TNodeHint(ANum);
   NodeHintList->Add(N);
   return true;
}

bool TArrowShape::DeleteNodeHint(int ANum)
{
   int i;
   TNodeHint *N;
   for (i = NodeHintList->Count - 1; i>=0; i--)
   {
      N = static_cast<TNodeHint*>(NodeHintList->Items[i]);
      if ( (N->Num == ANum)  )
      {
        delete N;
        N = NULL;
        NodeHintList->Delete(i);
        return true;
      }
   }
   return false;
}


bool TArrowShape::IsEmptyNodeHint()
{
   return  (NodeHintList->Count == 0);
}


int __fastcall TArrowShape::GetCountNodeHind()
{
   return  NodeHintList->Count;
}


int __fastcall TArrowShape::GetNodeHintItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= NodeHintList->Count - 1)
     return static_cast<TNodeHint*>(NodeHintList->Items[AIndex])->Num;
   else
     return -1;
}

/*

__property TRectLine*  RectLineItems[int AIndex] = { read =  GetRectLineItem};
TRectLine* __fastcall TBaseWorkShape::GetRectLineItem(int AIndex)
{
   if (AIndex >= 0 && AIndex <= WorkLines->Count - 1)
     return static_cast<TRectLine*>(WorkLines->Items[AIndex]);
   else
     return NULL;
}
*/



