//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFreeRectLine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TFreeRectLine::TFreeRectLine(int Step, int Number): TRectLine(Step, Number)
{
   f_XBend = 0;
   f_YBend = 0;
}

void TFreeRectLine::Prepare()
{
  TBaseLine *line;
  int midl;
  int t_x0, t_x1, t_y0, t_y1;
  InvisibleLines();

  t_x0 = xStart;
  t_x1 = xEnd;
  t_y0 = yStart;
  t_y1 = yEnd;

  if ((t_x0 > t_x1) && (t_y0 > t_y1))
  {
    t_x0 = xEnd;
    t_x1 = xStart;
    t_y0 = yEnd;
    t_y1 = yStart;
  }

  if ((t_x0 > t_x1) && (t_y0 < t_y1))
  {
    t_x0 = xEnd;
    t_x1 = xStart;
    t_y0 = yEnd;
    t_y1 = yStart;
  }

  if ((t_x0 < t_x1) && (t_y0 < t_y1))
  {
     if (Bend == 0)
     {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, t_y1);
       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y1, t_x1, t_y1);
    }
    if (Bend == 1)
    {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x1, t_y0);
       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x1, t_y0, t_x1, t_y1);
    }
    if (Bend == 2)
    {
       if (f_XBend)
         midl = f_XBend;
       else
         midl = int((t_x1 - t_x0)/2 + t_x0);
       f_XBend = midl;

       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, midl, t_y0);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(midl, t_y0, midl, t_y1);
       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(midl, t_y1, t_x1, t_y1);
    }
    if (Bend == 3)
    {
       if (f_YBend)
         midl = f_YBend;
       else
         midl = int((t_y1 - t_y0)/2 + t_y0);
       f_YBend = midl;
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, midl);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x0, midl, t_x1, midl);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(t_x1, midl, t_x1, t_y1);
    }
  }
  if ((t_x1 > t_x0) && (t_y0 > t_y1))
  {

     if (Bend == 0)
     {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, t_y1);
       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y1, t_x1, t_y1);
    }
    if (Bend == 1)
    {
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x1, t_y0);
       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x1, t_y0, t_x1, t_y1);
    }
    if (Bend == 2)
    {
       if (f_XBend)
         midl = f_XBend;
       else
         midl = int((t_x1 - t_x0)/2 + t_x0);
       f_XBend = midl;

       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, midl, t_y0);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(midl, t_y0, midl, t_y1);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(midl, t_y1, t_x1, t_y1);
    }
    if (Bend == 3)
    {
       if (f_YBend)
         midl = f_YBend;
       else
         midl = int((t_y0 - t_y1)/2 + t_y1);
       f_YBend = midl;
       line = static_cast<TBaseLine*>(GetBaseLine(0));
       line->Visible = true;
       line->ApplyCoord(t_x0, t_y0, t_x0, midl);

       line = static_cast<TBaseLine*>(GetBaseLine(1));
       line->Visible = true;
       line->ApplyCoord(t_x0, midl, t_x1, midl);

       line = static_cast<TBaseLine*>(GetBaseLine(2));
       line->Visible = true;
       line->ApplyCoord(t_x1, midl, t_x1, t_y1);
    }

  }

  if ((xStart==xEnd) || (yStart==yEnd))
  {
     line = static_cast<TBaseLine*>(GetBaseLine(0));
     line->Visible = true;
     line->ApplyCoord(xStart, yStart, xEnd, yEnd);

  }
}

