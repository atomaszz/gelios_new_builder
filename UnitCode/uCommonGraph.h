//---------------------------------------------------------------------------

#ifndef uCommonGraphH
#define uCommonGraphH
#include <grids.hpp>
#include "uBaseWorkShape.h"
#include "uWork.h"
#include "uPWork.h"
#include "uDynamicArray.h"

//---------------------------------------------------------------------------
TPWork* FusionWork(TWork *W1, TWork *W2);
TPoint PointAdd(TPoint APoint, int Ax, int Ay);
TPoint PointAdd(TPoint APoint, TPoint APointOfs);
TPoint PointSub(TPoint APoint, TPoint APointOfs);
TPoint PointMinX(TPoint APoint1, TPoint APoint2);
TPoint PointMaxX(TPoint APoint1, TPoint APoint2);
TPoint PointMax(TPoint APoint1, TPoint APoint2);
bool PointIsNull(TPoint APoint);
TRect RectSumm(TRect R1, TRect R2);
TRect RectMaxWidth(TRect R1, TRect R2);
TRect RectMinWidth(TRect R1, TRect R2);
int DivTrunc(int m, int n);
void PaintVShape(TCanvas *ACanvas, TPoint ACenter, int AX, int AY, bool AOR);
void CreateLineVShapeComposite(TPoint ACenter, int AX, int AY, bool AOR, TPoint *ARet);
bool HasParam(AnsiString ParamName);
AnsiString GetHelpFile(AnsiString APath, bool &Find);
AnsiString FontToStr(TFont *font);
void StrToFont(AnsiString str, TFont *AFont);
void CopyDynamicArray(TDynamicArray* ASource, TDynamicArray* ADest, bool InsertToFirst);
void ListIDFromWorkShape(TBaseWorkShape* AWorkShape, TDynamicArray* AList);
int GlsStrPos(char* AStr,  char* APattern);
void SGCells(TStringGrid *AStringGrid, int ARow, int ACol, String AValue);
void SGCellsByName(TStringGrid *AStringGrid, int ARow, String AColName, Variant AValue);
AnsiString  float_2_string(double ff,int pr);
AnsiString  float_2_string(double ff,int pr, int digits);
int read_float(char *data);
void DrawBmpInRect(TCanvas* ACanvas, TRect ARect, Graphics::TBitmap *ABmp );
unsigned short MakeShortCut(AnsiString ACut, bool AShift, bool ACtrl, bool AAlt );
String VarToString(Variant Value);
int VarToInteger(Variant Value);
double VarToDouble(Variant Value);

void SGInsertRow(TStringGrid *AStringGrid, int AfterIndex);
void LRTrim(char *AStr);
bool IsDigit(char *AStr);


class TColorSetup
{
   private:
     TColor f_FonColor;
     bool f_BoldTFELine;
     TColor  f_LineColor;
     bool f_BrushTFE;
     TColor f_BrushColor;
     Graphics::TFont* f_FontTFE;
     TColor f_FrameColorTFE;
     TColor f_FrameColorTFS;
     TColor f_HaveChildColor;
     TColor f_AltParamLineColor;
     TColor f_AltParamShapeColor;
     bool   f_AltParamShapeColorEnable;

   public:
     TColorSetup();
     ~TColorSetup();
     void SetFont(Graphics::TFont* AFont);
     void GetFont(Graphics::TFont* AFont);
     __property TColor FonColor = {read = f_FonColor, write = f_FonColor};
     __property bool BoldTFELine = {read = f_BoldTFELine, write = f_BoldTFELine};
     __property TColor LineColor = {read = f_LineColor, write = f_LineColor};
     __property bool BrushTFE = {read = f_BrushTFE, write = f_BrushTFE};
     __property TColor BrushColor = {read = f_BrushColor, write = f_BrushColor};
     __property TColor FrameColorTFE = {read = f_FrameColorTFE, write = f_FrameColorTFE};
     __property TColor FrameColorTFS = {read = f_FrameColorTFS, write = f_FrameColorTFS};
     __property TColor HaveChildColor = {read = f_HaveChildColor, write = f_HaveChildColor};
     __property TColor AltParamLineColor = {read = f_AltParamLineColor, write = f_AltParamLineColor};
     __property TColor AltParamShapeColor = {read = f_AltParamShapeColor, write = f_AltParamShapeColor};
     __property bool   AltParamShapeColorEnable = {read = f_AltParamShapeColorEnable, write = f_AltParamShapeColorEnable};


};


struct SF_TFS
{
  int ID;
  int TypeID;
  int StartPointX;
  int StartPointY;
  int OffsetX;
  int OffsetY;
  int NextID;
  int PriorID;
  int TFECount;
};

struct SF_TFE
{
  int ID;
  int TypeID;
  int ParamCount;
};

struct SF_ANCS
{
   int IdBlock;
   int IdShapeAncestor;
};

struct SF_ALT
{
   int ID;
   int Num;
   int NodeStartID;
   int NodeEndID;
   int Count;
};


struct SF_PARAMALT
{
  int NUMBER;
  char PRED_ISTOR[256];
  char SOSTAV[256];
  char NAME[256];
  char FUNCTION2[256];
  char ELEMENT[256];
  char PREDICAT[256];
  double B;
  double T;
  double V;
  double A1_B_F;
  double B_F1N;
  double B_F1B;
  double A2_B_F;
  double B_F2N;
  double B_F2B;
  double A3_B_F;
  double B_F3N;
  double B_F3B;
  double A1_T_F;
  double T_F1N;
  double T_F1B;
  double A2_T_F;
  double T_F2N;
  double T_F2B;
  double A3_T_F;
  double T_F3N;
  double T_F3B;
  double A1_V_F;
  double V_F1N;
  double V_F1B;
  double A2_V_F;
  double V_F2N;
  double V_F2B;
  double A3_V_F;
  double V_F3N;
  double V_F3B;
  double K_11;
  double K_00;
  double T_F;
  double V_F;
  double A1_K11_F;
  double K11_F1N;
  double K11_F1B;
  double A2_K11_F;
  double K11_F2N;
  double K11_F2B;
  double A3_K11_F;
  double K11_F3N;
  double K11_F3B;
  double A1_K00_F;
  double K00_F1N;
  double K00_F1B;
  double A2_K00_F;
  double K00_F2N;
  double K00_F2B;
  double A3_K00_F;
  double K00_F3N;
  double K00_F3B;
  double A1_TF_F;
  double TF_F1N;
  double TF_F1B;
  double A2_TF_F;
  double TF_F2N;
  double TF_F2B;
  double A3_TF_F;
  double TF_F3N;
  double TF_F3B;
  double A1_VF_F;
  double VF_F1N;
  double VF_F1B;
  double A2_VF_F;
  double VF_F2N;
  double VF_F2B;
  double A3_VF_F;
  double VF_F3N;
  double VF_F3B;
  double P_11;
  double P_00;
  double T_D;
  double V_D;
  double A1_P11_F;
  double P11_F1N;
  double P11_F1B;
  double A2_P11_F;
  double P11_F2N;
  double P11_F2B;
  double A3_P11_F;
  double P11_F3N;
  double P11_F3B;
  double A1_P00_F;
  double P00_F1N;
  double P00_F1B;
  double A2_P00_F;
  double P00_F2N;
  double P00_F2B;
  double A3_P00_F;
  double P00_F3N;
  double P00_F3B;
  double A1_TD_F;
  double TD_F1N;
  double TD_F1B;
  double A2_TD_F;
  double TD_F2N;
  double TD_F2B;
  double A3_TD_F;
  double TD_F3N;
  double TD_F3B;
  double A1_VD_F;
  double VD_F1N;
  double VD_F1B;
  double A2_VD_F;
  double VD_F2N;
  double VD_F2B;
  double A3_VD_F;
  double VD_F3N;
  double VD_F3B;
  int TYPE;
  char ELEM_DIAGN[256];
  double P_DIAGN_EL;
  double A1_P_EL_F;
  double P_EL_F1N;
  double P_EL_F1B;
  double A2_P_EL_F;
  double P_EL_F2N;
  double P_EL_F2B;
  double A3_P_EL_F;
  double P_EL_F3N;
  double P_EL_F3B;
  double SOVM;
  double SOVM0;
  double SOVM1;
};

const char SF_HADERBIN[] = "GRF(v001)";

// ---- пошли шаблоны
template<class Type> int Sign(Type ANum)
{
   int sign = (ANum > 0) - (ANum < 0);
   return sign;
}


#endif


