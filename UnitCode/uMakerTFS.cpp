//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMakerTFS.h"
#include "uParamAlternative.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
TMakerTFS::TMakerTFS(TListNode*  AMainList, TPaintGrid* AGrid, TShapeCopy AOnShapeCopy,
   int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine)
{
  FGrid = AGrid;
  FMainList = AMainList;
  FCurrIDShape = ACurrIDShape;
  FCurrIDBlock = ACurrIDBlock;
  FCurrIDLine = ACurrIDLine;
  FOnShapeCopy = AOnShapeCopy;
  FLevelID = -1;
}

void TMakerTFS::SetCurrentLevel(int ALevelID)
{
  TBaseShape* mTFE;

  FLevelID = -1;
  if (ALevelID > 0)
  {
    if ( FMainList->FindWorkShapeOutBaseShapeID(ALevelID, &mTFE) )
    {
      if ( mTFE->PowerIn() )
      {
        int bl = FMainList->FindBlockOutShape(ALevelID);
        if (bl)
        {
          int m_pos;
          TNodeMain* Nd =  FMainList->FindNode(bl, m_pos);
          if (Nd)
          {
            FLevelID = ALevelID;
            FMainList->FillPainterList(FGrid->g_PainterList, Nd->IdAlternate, Nd->NumAlt, FLevelID);
            FGrid->PrepareLevel();
            FGrid->CoordinateCorrectForCompositeWork();
            FGrid->RecalcAfterConverted(false, TPoint(40, 100));
            FGrid->PreparePaint();
          }
        }
      }
    }
  }
  if ( !ALevelID )
    FLevelID = 0;
}

TBaseWorkShape* TMakerTFS::AddTFSToCurrentLevel(int AType, int AIdAlternative, int ANumAlternative)
{
  AnsiString Error = "TMakerTFS::AddTFSToCurrentLevel не установлен уровень!\r\nВозможно ТФС добавляется в несуществующий ТФЕ, либо этот ТФЕ не допускает структурных альтернатив!";
  if (FLevelID == -1)
	throw(Exception(Error));
  TBaseWorkShape* WH = FGrid->AddWorkShape(AType, FCurrIDShape, FCurrIDBlock, FCurrIDLine);
  assert(WH);
  WH->OnShapeCopy = FOnShapeCopy;
  WH->ParentShapeID = FLevelID;
  FCurrIDShape = WH->LastShapeId;
  FCurrIDLine = WH->LastLineId;
  FCurrIDBlock++;
  FMainList->AddShapeToList(AIdAlternative, ANumAlternative, WH , FLevelID);
  FGrid->PreparePaint();
  return WH;
}

TParamAlternativeItem* TMakerTFS::CreateNewParamAlternative(int ATFEID)
{
  TParamAlternativeItem* Res = NULL;
  TBaseShape* mTFE = NULL;
  if ( FMainList->FindWorkShapeOutBaseShapeID(ATFEID, &mTFE) )
  {
    int type, num;
    AnsiString  add_name,sos;

    type = mTFE->TypeShape;
    num = mTFE->ID;
    if (type == 8 && mTFE->ParamAlt) return Res;

    double s_b, s_t, s_v,s_k11,s_k00,s_tf,s_vf,
           s_p11,s_p00,s_td,s_vd,
           s_p_el,
           s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
           s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
           s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
           s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
           s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
           s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
           s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
           s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
           s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
           s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
           s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
           s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b;
    AnsiString s_name, s_el, s_func, s_e, s_predicat;


    s_name="(нет названия)";
    s_el = "(нет элемента)";
    s_func = "(нет функции)";


    s_b=1;s_t=0;s_v=0;
    s_k11=1;s_k00=1;s_tf=0; s_vf=0;

    s_p11=1;s_p00=1; s_td=0; s_vd=0;
    s_e="(нет элемента)"; s_p_el=1;
    s_a1_p_el_f=0; s_p_el_f1n=0; s_p_el_f1b=0; s_a2_p_el_f=0.5; s_p_el_f2n=0; s_p_el_f2b=0;
    s_a3_p_el_f=1; s_p_el_f3n=0; s_p_el_f3b=0;
    s_a1_b_f=0; s_b_f1n=0; s_b_f1b=0; s_a2_b_f=0.5; s_b_f2n=0; s_b_f2b=0;
    s_a3_b_f=1; s_b_f3n=0; s_b_f3b=0;
    s_a1_t_f=0; s_t_f1n=0; s_t_f1b=0; s_a2_t_f=0.5; s_t_f2n=0; s_t_f2b=0;
    s_a3_t_f=1; s_t_f3n=0; s_t_f3b=0;
    s_a1_v_f=0; s_v_f1n=0; s_v_f1b=0; s_a2_v_f=0.5; s_v_f2n=0; s_v_f2b=0;
    s_a3_v_f=1; s_v_f3n=0; s_v_f3b=0;
    s_a1_k11_f=0; s_k11_f1n=0; s_k11_f1b=0; s_a2_k11_f=0.5; s_k11_f2n=0;
    s_k11_f2b=0; s_a3_k11_f=1; s_k11_f3n=0; s_k11_f3b=0;
    s_a1_k00_f=0; s_k00_f1n=0; s_k00_f1b=0; s_a2_k00_f=0.5; s_k00_f2n=0;
    s_k00_f2b=0; s_a3_k00_f=1; s_k00_f3n=0; s_k00_f3b=0;
    s_a1_tf_f=0; s_tf_f1n=0; s_tf_f1b=0; s_a2_tf_f=0.5; s_tf_f2n=0;
    s_tf_f2b=0; s_a3_tf_f=1; s_tf_f3n=0; s_tf_f3b=0;
    s_a1_vf_f=0; s_vf_f1n=0; s_vf_f1b=0; s_a2_vf_f=0.5; s_vf_f2n=0;
    s_vf_f2b=0; s_a3_vf_f=1; s_vf_f3n=0; s_vf_f3b=0;
    s_a1_p11_f=0; s_p11_f1n=0; s_p11_f1b=0; s_a2_p11_f=0.5; s_p11_f2n=0;
    s_p11_f2b=0; s_a3_p11_f=1; s_p11_f3n=0; s_p11_f3b=0;
    s_a1_p00_f=0; s_p00_f1n=0; s_p00_f1b=0; s_a2_p00_f=0.5; s_p00_f2n=0;
    s_p00_f2b=0; s_a3_p00_f=1; s_p00_f3n=0; s_p00_f3b=0;
    s_a1_td_f=0; s_td_f1n=0; s_td_f1b=0; s_a2_td_f=0.5; s_td_f2n=0;
    s_td_f2b=0; s_a3_td_f=1; s_td_f3n=0; s_td_f3b=0;
    s_a1_vd_f=0; s_vd_f1n=0; s_vd_f1b=0; s_a2_vd_f=0.5; s_vd_f2n=0;
    s_vd_f2b=0; s_a3_vd_f=1; s_vd_f3n=0; s_vd_f3b=0;
    s_predicat="(нет условия)";

    Res = CreateParamAlternativeItem(sos.c_str(),add_name.c_str(),s_name.c_str(),s_func.c_str(),s_el.c_str(),type,num,
                                     s_b,s_t,s_v,
                                     s_k11,s_k00,s_tf,s_vf,
                                     s_p11,s_p00,s_td,s_vd,
                                     s_e,s_p_el,
                                     s_a1_b_f, s_b_f1n, s_b_f1b, s_a2_b_f, s_b_f2n, s_b_f2b, s_a3_b_f, s_b_f3n, s_b_f3b,
                                     s_a1_t_f, s_t_f1n, s_t_f1b, s_a2_t_f, s_t_f2n, s_t_f2b, s_a3_t_f, s_t_f3n, s_t_f3b,
                                     s_a1_v_f, s_v_f1n, s_v_f1b, s_a2_v_f, s_v_f2n, s_v_f2b, s_a3_v_f, s_v_f3n, s_v_f3b,
                                     s_a1_k11_f, s_k11_f1n, s_k11_f1b, s_a2_k11_f, s_k11_f2n, s_k11_f2b, s_a3_k11_f, s_k11_f3n, s_k11_f3b,
                                     s_a1_k00_f, s_k00_f1n, s_k00_f1b, s_a2_k00_f, s_k00_f2n, s_k00_f2b, s_a3_k00_f, s_k00_f3n, s_k00_f3b,
                                     s_a1_tf_f, s_tf_f1n, s_tf_f1b, s_a2_tf_f, s_tf_f2n, s_tf_f2b, s_a3_tf_f, s_tf_f3n, s_tf_f3b,
                                     s_a1_vf_f, s_vf_f1n, s_vf_f1b, s_a2_vf_f, s_vf_f2n, s_vf_f2b, s_a3_vf_f, s_vf_f3n, s_vf_f3b,
                                     s_a1_p11_f, s_p11_f1n, s_p11_f1b, s_a2_p11_f, s_p11_f2n, s_p11_f2b, s_a3_p11_f, s_p11_f3n, s_p11_f3b,
                                     s_a1_p00_f, s_p00_f1n, s_p00_f1b, s_a2_p00_f, s_p00_f2n, s_p00_f2b, s_a3_p00_f, s_p00_f3n, s_p00_f3b,
                                     s_a1_td_f, s_td_f1n, s_td_f1b, s_a2_td_f, s_td_f2n, s_td_f2b, s_a3_td_f, s_td_f3n, s_td_f3b,
                                     s_a1_vd_f, s_vd_f1n, s_vd_f1b, s_a2_vd_f, s_vd_f2n, s_vd_f2b, s_a3_vd_f, s_vd_f3n, s_vd_f3b,
                                     s_a1_p_el_f, s_p_el_f1n, s_p_el_f1b, s_a2_p_el_f, s_p_el_f2n, s_p_el_f2b, s_a3_p_el_f, s_p_el_f3n, s_p_el_f3b,
                                     s_predicat,1.0,1,1);
    mTFE->AddParamAlternativeItem(Res);
  }
  return Res;
}


