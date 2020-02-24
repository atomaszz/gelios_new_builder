//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uArrowWorkShape.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TArrowWorkShape::TArrowWorkShape(int X, int Y, int Step, int NumberShape_Id, int Block_Id, int NumberLine_Id): TBaseWorkShape(X, Y, Step, NumberShape_Id, Block_Id, NumberLine_Id)
{
}

//r = CreateRectRgn(R->Left, R->Top, R->Right, R->Bottom);

TArrowWorkShape::~TArrowWorkShape()
{
}



void TArrowWorkShape::Init()
{
   FreeWorkLines();
   FreeWorkShapes();
   TArrowShape *Shape;
   F_LastShapeId = F_NumberShapeId;
   F_LastShapeId++;
   F_NumberShapeId = F_LastShapeId;
   Shape = new TArrowShape(StartPoint.x, StartPoint.y, F_Step, F_LastShapeId);
   AddShape(Shape);

}

bool TArrowWorkShape::AddNodeHint(int ANum)
{
   TArrowShape *Shape;
   Shape = static_cast<TArrowShape*>(GetWorkShape(0));
   return (Shape->AddNodeHint(ANum));

}

bool TArrowWorkShape::DeleteNodeHint(int ANum)
{
   TArrowShape *Shape;
   Shape = static_cast<TArrowShape*>(GetWorkShape(0));
   return (Shape->DeleteNodeHint(ANum));
}

bool TArrowWorkShape::IsEmptyNodeHint()
{
   TArrowShape *Shape;
   Shape = (TArrowShape *)GetWorkShape(0);
   return (Shape->IsEmptyNodeHint());
}


TRect TArrowWorkShape::GetRegionRect()
{
   TRect R;
   R = GetFrameRectWithLines();
   R.Top = 0;
   R.Left = R.Left - 6;
   R.Right = R.Right + 6;
   R.Bottom = R.Bottom + 6;
   return R;
}

TRect TArrowWorkShape::GetSmallRegionRect()
{
   TRect R;
   R = GetMaxRect();
   return R;
}

int __fastcall TArrowWorkShape::GetCountNodeHind()
{
   TArrowShape *Shape;
   Shape = static_cast<TArrowShape*>(GetWorkShape(0));
   return (Shape->CountNodeHind);
}


int __fastcall TArrowWorkShape::GetNodeHintItem(int AIndex)
{
   TArrowShape *Shape;
   Shape = static_cast<TArrowShape*>(GetWorkShape(0));
   return (Shape->NodeHind[AIndex]);
}





