//---------------------------------------------------------------------------

#ifndef uFlagShapeH
#define uFlagShapeH
#include "uBaseShape.h"
#include "uBaseline.h"
//---------------------------------------------------------------------------
//class TBaseLine;
class TFlagShape: public TBaseShape
{
  private:
    TPoint F_Center;
    double F_Radius;
    int F_TypeFlag;
    TBaseLine* F_Owner;
    TBaseShape* F_ShOwner;
    int F_ShPos;
    void __fastcall SetTypeFlag(int Value);
  protected:
     int __fastcall GetTypeShape();
  public:
   TFlagShape(int Step, TBaseLine* Owner, int number);
   void  Paint(TCanvas *Canvas);
   __property TPoint Center  = {read = F_Center, write = F_Center};
   __property double Radius = {read = F_Radius, write = F_Radius};
   __property int TypeFlag = {read = F_TypeFlag, write = SetTypeFlag};
   __property TBaseLine* Owner = {read = F_Owner, write = F_Owner};
   __property TBaseShape* ShapeOwner = {read = F_ShOwner, write  = F_ShOwner};
   __property int ShapePos = {read = F_ShPos, write = F_ShPos};

};
#endif
