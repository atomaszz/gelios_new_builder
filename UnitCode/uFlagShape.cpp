//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFlagShape.h"
#include "uRhombShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TFlagShape::TFlagShape(int Step, TBaseLine* Owner, int number):TBaseShape(0, 0, Step, number)
{
   DrawCaption = false;
   F_Center = TPoint(0,0);
   F_Radius = 0;
   F_TypeFlag = 0;
   F_Owner = Owner;
   BrushStyle = bsSolid;
   F_ShOwner = NULL;
   F_ShPos = -1;
}

//------------------------------------------------------------------
void  TFlagShape::Paint(TCanvas *Canvas)
{
   TRect R;
   TPoint P[4];
   R.Left  = Center.x - int(F_Radius*F_Step);
   R.Top = Center.y - int(F_Radius*F_Step);
   R.Right = Center.x + int(F_Radius*F_Step);
   R.Bottom = Center.y + int(F_Radius*F_Step);
   BoundRect = R;
   SaveCanvas(Canvas);
   TBaseShape::Paint(Canvas);
   switch (F_TypeFlag)
   {
     case 0:
       TRhombShape::GetPointRhomb(P, R);
       Canvas->Polygon(P, 3);
       break;
     case 1:
       Canvas->Ellipse(R);
       break;
     case 2:
       Canvas->Rectangle(R);
       break;
   }
   RestoreCanvas(Canvas);
}


void __fastcall TFlagShape::SetTypeFlag(int Value)
{
   if ((Value > 2) || (Value < 0) )
     F_TypeFlag = 0;
   else
     F_TypeFlag = Value;
}


int __fastcall TFlagShape::GetTypeShape()
{
   return 100;
}



