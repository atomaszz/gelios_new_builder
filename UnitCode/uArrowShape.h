//---------------------------------------------------------------------------

#ifndef uArrowShapeH
#define uArrowShapeH
//---------------------------------------------------------------------------
#include "uBaseShape.h"
class TNodeHint
{
   private:
     int f_Num;
   public:
     TNodeHint(int ANum);
     __property int Num = {read = f_Num};

};

class TArrowShape: public TBaseShape
{
  private:
    TPoint Region[7];
    TList* NodeHintList;
    int __fastcall GetCountNodeHind();
    int __fastcall GetNodeHintItem(int AIndex);
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
    __property int CountNodeHind = {read = GetCountNodeHind};
    __property int NodeHind[int AIndex] = { read =  GetNodeHintItem};
};

#endif
