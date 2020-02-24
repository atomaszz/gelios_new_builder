//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "uCommonGraph.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TPWork* FusionWork(TWork *W1, TWork *W2)
{
   TPoint PS, PE;
   TBaseShape *N1;
   TPWork* Res = NULL;
   if ( (W1) && (W2) )
   {
     PS = W1->StartPoint;
     Res = new TPWork(PS.x, PS.y, W1->Step, W2->FirstShapeId, W1->BlockId, W1->FirstLineId);
     N1 = W1->GetWorkNode(0);
     Res->AddShape(N1);
     N1 = W2->GetWorkNode(0);
     Res->AddShape(N1);
     Res->OnShapeCopy = W1->OnShapeCopy;
     Res->CreateLines(); //Проблема
     Res->Prepare();
     Res->LEControl = W1->LEControl;
     Res->WndHandler = W1->WndHandler;
     Res->UnderControl = W1->UnderControl;
   }
   return Res;
}

TPoint PointAdd(TPoint APoint, int Ax, int Ay)
{
   return TPoint(APoint.x + Ax, APoint.y + Ay);
}

TPoint PointAdd(TPoint APoint, TPoint APointOfs)
{
   return TPoint(APoint.x + APointOfs.x, APoint.y + APointOfs.y);
}

TPoint PointSub(TPoint APoint, TPoint APointOfs)
{
   return TPoint(APoint.x - APointOfs.x, APoint.y - APointOfs.y);
}


TPoint PointMinX(TPoint APoint1, TPoint APoint2)
{
   TPoint Res = APoint1;
   if (APoint1.x > APoint2.x)
     Res = APoint2;
   return Res;
}

TPoint PointMaxX(TPoint APoint1, TPoint APoint2)
{
   TPoint Res = APoint1;
   if (APoint1.x < APoint2.x)
     Res = APoint2;
   return Res;
}

TPoint PointMax(TPoint APoint1, TPoint APoint2)
{
   TPoint Res;
   Res.x = APoint1.x;
   if (APoint1.x <  APoint2.x)
     Res.x = APoint2.x;

   Res.y = APoint1.y;
   if (APoint1.y <  APoint2.y)
     Res.y = APoint2.y;

   return Res;
}

bool PointIsNull(TPoint APoint)
{
   if ( (APoint.x == 0) && (APoint.y == 0) )
     return true;
   return false;
}

TRect RectSumm(TRect R1, TRect R2)
{
   TRect Res = R1;
   if (R2.Left < Res.Left )  Res.Left = R2.Left;
   if (R2.Right > Res.Right) Res.Right = R2.Right;
   if (R2.Top < Res.Top) Res.Top = R2.Top;
   if (R2.Bottom > Res.Bottom) Res.Bottom = R2.Bottom;
   return Res;
}

TRect RectMaxWidth(TRect R1, TRect R2)
{
   if (R1.Width() > R2.Width())
     return R1;
   return R2;
}


TRect RectMinWidth(TRect R1, TRect R2)
{
   if (R1.Width() > R2.Width())
     return R1;
   return R2;
}

int DivTrunc(int m, int n)
{
   int res;
   double t_m = m * 1.0;
   double t_n = n * 1.0;
   double d = t_m/t_n;
   res = int(d);
   double q = d - res;
   if (q > 0.4999) res++;
   return res;
}

//---------------------------------------------------------------------------
void PaintVShape(TCanvas *ACanvas, TPoint ACenter, int AX, int AY, bool AOR)
{
   TPoint P[3];
   if (AOR)
   {
     P[0] = TPoint(ACenter.x - AX, ACenter.y - AY);
     P[1] = TPoint(ACenter.x, AY + ACenter.y);
     if (ACanvas->Pen->Width == 1)
       P[2] = TPoint(ACenter.x + AX + 1, ACenter.y - AY - 1);
     else
       P[2] = TPoint(ACenter.x + AX , ACenter.y - AY);
   }
   else
   {
      P[0] = TPoint(ACenter.x - AX, AY + ACenter.y);
      P[1] = TPoint(ACenter.x, ACenter.y - AY);
      if (ACanvas->Pen->Width == 1)
        P[2] = TPoint(ACenter.x + AX + 1 , AY + ACenter.y + 1);
      else
        P[2] = TPoint(ACenter.x + AX, AY + ACenter.y );
   }
   ACanvas->Polyline(P, 2);
}

//---------------------------------------------------------------------------
void CreateLineVShapeComposite(TPoint ACenter, int AX,  int AY, bool AOR, TPoint *ARet)
{
   TPoint P[3];
   if (AOR)
   {
     P[0] = TPoint(ACenter.x - AX, ACenter.y - AY);
     P[1] = TPoint(ACenter.x, AY + ACenter.y);
     P[2] = TPoint(ACenter.x + AX , ACenter.y - AY);
   }
   else
   {
      P[0] = TPoint(ACenter.x - AX, AY + ACenter.y);
      P[1] = TPoint(ACenter.x, ACenter.y - AY);
      P[2] = TPoint(ACenter.x + AX, AY + ACenter.y );
   }
   ARet[0] = P[0];
   ARet[1] = P[1];
   ARet[2] = P[2];
}

bool HasParam(AnsiString ParamName)
{
  int i;
  AnsiString S;
  bool Res = false;
  for ( i = 1;  i <= ParamCount(); i++ )
  {
    S = ParamStr(i);
    if ( (S.Length() > 1) && ( (S[1] == '-') || (S[1] == '/') ) &&
         (CompareText(S.c_str() + 1, ParamName) == 0) )
    {
      Res = true;
      break;
    }
  }
  return Res;
}


TColorSetup::TColorSetup()
{
   f_FonColor = clBlack;
   f_BoldTFELine = false;
   f_LineColor = clBlack;
   f_BrushTFE = false;
   f_BrushColor = clWhite;
   f_FrameColorTFE = clRed;
   f_FrameColorTFS = clRed;
   f_HaveChildColor = clGreen;
   f_FontTFE = new Graphics::TFont;
}

TColorSetup::~TColorSetup()
{
   delete  f_FontTFE;
}

void TColorSetup::SetFont(Graphics::TFont* AFont)
{
   if (AFont)
     f_FontTFE->Assign(AFont);
}

void TColorSetup::GetFont(Graphics::TFont* AFont)
{
   AFont->Assign(f_FontTFE);
}

AnsiString GetHelpFile(AnsiString APath, bool &Find)
{
   Find  = false;
   AnsiString App = Application->ExeName;
   AnsiString Path = ExtractFilePath(App);
   AnsiString Temp = AnsiLowerCase(Trim(APath));
   if (Temp.Length() == 0)
      return "";
   if (Temp.Length() < 10)
   {
      if (FileExists(Temp))
      {
        Find = true;
        return Temp;
      }
      else
        return "";
   }
   AnsiString Base = Temp.SubString(1, 10);
   AnsiString Tail = Temp.SubString(11, Temp.Length());
   if ( AnsiSameText(Base, "<programm>" ) )
   {
      App = Path + Tail;
      if (FileExists(App))
      {
        Find = true;
        return App;
      }

   }
   else
   if (FileExists(Temp))
   {
      Find = true;
      return Temp;
   }
   return "";
}


//---------------------------------------------------------------------------
AnsiString Copy(AnsiString S, int Index,  int Count)
{
   AnsiString  Res = "";
   int dln = S.Length();
   if (dln > 0 && Index > 0 && ( Index <= dln ) && (Index + Count - 1 <=  dln) )
   {
      int pos = 0;
      while (pos < Count)
      {
         Res = Res + S[Index + pos];
         pos++;
      }
   }
   return Res;

}

bool isoneof(AnsiString c, AnsiString s)
{
   for (int i = 1; i <= s.Length(); i++)
     if (c == Copy(s, i, 1))
        return true;
   return false;

}

AnsiString Tok( AnsiString sep, AnsiString &s)
{
  AnsiString c, t;
  if (s == "")
    return s;
  c = Copy(s, 1, 1);
  while (isoneof(c, sep))
  {
    s = Copy(s, 2, s.Length() - 1);
    c = Copy(s, 1, 1);
  }
  t = "";
  while (( ! isoneof(c, sep)) && (s != ""))
  {
    t = t + c;
    s = Copy(s, 2, s.Length() - 1);
    c = Copy(s, 1, 1);
  }
  return t;
}


AnsiString FontToStr(TFont *font)
{
  AnsiString Res = "";
  Res = Res + IntToStr(font->Color) + "|";
  Res = Res + IntToStr(font->Height) + "|";
  Res = Res + font->Name + "|";
  Res = Res + IntToStr(int(font->Pitch)) + "|";
  Res = Res + IntToStr(font->PixelsPerInch) + "|";
  Res = Res + IntToStr(font->Size) + "|";
  if (font->Style.Contains(fsBold) )
    Res = Res + "y";
  else
    Res = Res + "n";

  if (font->Style.Contains(fsItalic) )
    Res = Res + "y";
  else
    Res = Res + "n";

  if (font->Style.Contains(fsUnderline) )
    Res = Res + "y";
  else
    Res = Res + "n";

  if (font->Style.Contains(fsStrikeOut) )
    Res = Res + "y";
  else
    Res = Res + "n";

  return Res;
}

void StrToFont(AnsiString str, TFont *AFont)
{
  TFontStyles fs;
  if (str == "") return;
  AFont->Color = TColor(StrToInt(Tok("|", str)));
  AFont->Height = StrToInt(Tok("|", str));
  AFont->Name = Tok("|", str);
  AFont->Pitch = TFontPitch(StrToInt(Tok("|", str)));
  AFont->PixelsPerInch = StrToInt(Tok("|", str));
  AFont->Size = StrToInt(Tok("|", str));
  AFont->Style.Clear();
  if ( str[2] == 'y' )
    fs << fsBold;
  if (str[3] == 'y' )
    fs << fsItalic;
  if (str[4] == 'y')
    fs << fsUnderline;
  if (str[5] == 'y')
    fs << fsStrikeOut;
  AFont->Style = fs;
}


void CopyDynamicArray(TDynamicArray* ASource, TDynamicArray* ADest, bool AInsertToFirst)
{
   for( int i = 0; i <= ASource->Count - 1; i++ )
   {
     if (AInsertToFirst)
       ADest->InsertToFirst(ASource->Items[i]);
     else
       ADest->Append(ASource->Items[i]);
   }
}

void ListIDFromWorkShape(TBaseWorkShape* AWorkShape, TDynamicArray* AList)
{
   int m_s;
   void* p_s;
   TBaseShape* CurrShape;
   int tmp[3] = {-1, -1, -1};
   void* p[3] = {0, 0, 0};

   for( int i = 0; i <= AWorkShape->WorkShapesCount - 1; i++ )
   {
      CurrShape = static_cast<TBaseShape*>(AWorkShape->GetWorkShape(i));
      tmp[i] = CurrShape->ID;
      p[i] = CurrShape;
   }

   bool swap = true;
   while(swap)
   {
      swap = false;
      for( int i = 0; i <= AWorkShape->WorkShapesCount - 2; i++ )
      {
         if ( (tmp[i] > tmp[i+1]) && (tmp[i+1] != -1) )
         {
           m_s = tmp[i];
           p_s = p[i];
           tmp[i] = tmp[i+1];
           p[i] = p[i+1];
           tmp[i+1] = m_s;
           p[i+1] = p_s;
           swap = true;
         }
      }
   }
   for( int i = 0; i <= AWorkShape->WorkShapesCount - 1; i++ )
      AList->AppendInteger(tmp[i], p[i]);
}


int GlsStrPos(char* AStr,  char* APattern)
{
  int plen = strlen(APattern);
  int slen = strlen(AStr);
  int pindx;
  int cmppos;
  int endpos;

  for( endpos = plen-1; endpos < slen ; )
  {
    for( cmppos = endpos, pindx = (plen - 1); pindx >= 0 ; cmppos--, pindx-- )
      if( AStr[cmppos] != APattern[pindx] )
      {
         endpos+=1;
         break;
      }

   if( pindx < 0 ) return ( endpos - (plen-1));
  }
  return -1;
}


void SGCells(TStringGrid *AStringGrid, int ARow, int ACol, String AValue)
{
   AStringGrid->Cells[ACol][ARow] = AValue;
}

String VarToString(Variant Value)
{
  if (VarIsEmpty(Value) || VarIsNull(Value))
    return "";
  else
    return VarAsType(Value, varString);
}

int VarToInteger(Variant Value)
{
  if (VarIsEmpty(Value) || VarIsNull(Value))
    return 0;
  else
    return VarAsType(Value, varInteger);
}

double VarToDouble(Variant Value)
{
  if (VarIsEmpty(Value) || VarIsNull(Value))
    return 0;
  else
    return VarAsType(Value, varDouble);
}


void SGCellsByName(TStringGrid *AStringGrid, int ARow, String AColName, Variant AValue)
{
   String S;
   for(int i = 0; i <= AStringGrid->ColCount - 1; i++)
   {
      if (AnsiSameText(AStringGrid->Cells[i][0], AColName) )
      {
        if ( VarType(AValue) == varDouble )
          S = float_2_string(VarToDouble(AValue), 10);
        else
		  S = VarToString(AValue);
		AStringGrid->Cells[i][ARow] = S;
        return;
	  }
   }
}

void SGInsertRow(TStringGrid *AStringGrid, int AfterIndex)
{
   int row_count = AStringGrid->RowCount;
   SendMessage(AStringGrid->Handle, WM_SETREDRAW, 0, 0);
   AStringGrid->RowCount = row_count + 1;

   for (int row = row_count; row > AfterIndex + 1; row--)
     AStringGrid->Rows[row] = AStringGrid->Rows[row - 1];

   AStringGrid->Rows[AfterIndex + 1]->Clear();
   SendMessage(AStringGrid->Handle, WM_SETREDRAW, 1, 0);

   RECT R = AStringGrid->CellRect(0, AfterIndex);
   InflateRect(&R, AStringGrid->Width, AStringGrid->Height);
   InvalidateRect(AStringGrid->Handle, &R, false);
}


AnsiString  float_2_string(double ff,int pr)
{
  AnsiString sResult;
  FormatSettings.DecimalSeparator = '.';
  sResult = FloatToStrF(ff, ffFixed, pr, 5);
  if (  sResult == "NAN"  || sResult == "INF" || sResult == "-INF" )
    sResult = "0.00000";
  return sResult;
}

AnsiString  float_2_string(double ff,int pr, int digits)
{
  AnsiString sResult;
  FormatSettings.DecimalSeparator = '.';
  sResult = FloatToStrF(ff, ffFixed, pr, digits);
  if (  sResult == "NAN"  || sResult == "INF" || sResult == "-INF" )
    sResult = "0";
  return sResult;
}



//---------------------------------------------------------------------------
//---проверка правильности ввода чисел типa float---
int read_float(char *data)
{
  char *ptr;
  short fl=0;
  ptr=data;
  //проверка наличия знакового символа
  if(*ptr=='-' || *ptr=='+')//если есть - идем на след.символ
     ptr++;
  for(fl=0;*ptr!='\0';ptr++)//проверка ввода только цифр без учета знакового символа
  {
    if(!isdigit(*ptr))
    {  if(*ptr=='.')
       {
         if(fl==0)
           fl=1;                //т.е. пропускаем 1 точку
         else
           if(fl==1)
             return 1;
       }
       else
         return 1;  //если не точка - то выход по ошибке
    }
  }
  return 0;
}


void DrawBmpInRect(TCanvas* ACanvas, TRect ARect, Graphics::TBitmap *ABmp )
{
  int  mx, my;
  mx = ARect.Left + ( ARect.Right - ARect.Left - ABmp->Width ) / 2;
  my = ARect.Top + ( ARect.Bottom - ARect.Top - ABmp->Height ) / 2;
  ACanvas->BrushCopy( Classes::Rect( mx, my, mx + ABmp->Width, my + ABmp->Height), ABmp,
    Classes::Rect( 0, 0, ABmp->Width, ABmp->Height ), ABmp->TransparentColor );
}



unsigned short MakeShortCut(AnsiString ACut, bool AShift, bool ACtrl, bool AAlt )
{
   AnsiString S = "";
   if (AShift)
     S = "Shift";
   if (ACtrl)
   {
     if (S.Length() > 0)
       S = S +"+";
     S = S +"Ctrl";
   }
   if (AAlt)
   {
     if (S.Length() > 0)
       S = S + "+";
     S = S +"Alt";
   }
   if (S.Length() > 0)
     S = S + "+";
   S = S + ACut;
   return TextToShortCut(S);
}



void LRTrim(char *AStr)
{
   int dl = strlen(AStr);
   char *nStr = new char[dl+1];
   int j = 0;
   bool fr = false;
   for(int i = 0; i <= dl - 1;  i++)
   {
      if ( (AStr[i] != ' ') && !fr)
       fr = true;
      if (fr)
      {
        nStr[j] = AStr[i];
        j++;
      }
   }
   nStr[j] = 0;
   dl = strlen(nStr);
   for(int i = dl - 1; i >= 0; i--)
   {
      if (nStr[i] == ' ')
        nStr[i] = 0;
      else
        break;
   }
   strcpy(AStr, nStr);
   delete  []nStr;
}


bool IsDigit(char *AStr)
{
   int dl = strlen(AStr);
   char *nStr = new char[dl+1];
   strcpy(nStr, AStr);
   LRTrim(nStr);
   int err = 0;
   dl = strlen(nStr);
   for(int i = 0; i <= dl - 1; i++)
   {
      if ( !((nStr[i] >= '0') && (nStr[i] <= '9')) )
      {
         if (!( (i==0) && ( (nStr[i] == '+') || (nStr[i] == '-') ) ) )
           err++;
      }
   }
   delete  []nStr;
   return err == 0;
}

