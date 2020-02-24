//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uArrowLine.h"
#include "uBaseLine.h"
#include "uTrailer.H"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TArrowLine::TArrowLine(int Step, int Number):TRectLine(Step, Number)
{
   F_Step = Step;
}

//-------------------------------------------------------------------------
void TArrowLine::Prepare()
{
   TRectLine::Prepare();
}

//-------------------------------------------------------------------------
void TArrowLine::Paint(TCanvas *Canvas)
{
   TRectLine::Paint(Canvas);
}



