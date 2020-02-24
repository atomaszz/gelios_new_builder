//---------------------------------------------------------------------------

#ifndef uMakerTFSH
#define uMakerTFSH

#include "uPaintgrids.h"
#include "uListShape.h"
//---------------------------------------------------------------------------
class TMakerTFS
{
  private:
    TPaintGrid* FGrid;
    TListNode*  FMainList;
    TShapeCopy  FOnShapeCopy;
    int FCurrIDShape, FCurrIDBlock, FCurrIDLine, FLevelID;
  public:
    TMakerTFS(TListNode*  AMainList, TPaintGrid* AGrid, TShapeCopy AOnShapeCopy, int ACurrIDShape, int ACurrIDBlock, int ACurrIDLine);
	void SetCurrentLevel(int ALevelID);
	TBaseWorkShape* AddTFSToCurrentLevel(int AType, int AIdAlternative, int ANumAlternative);
    TParamAlternativeItem* CreateNewParamAlternative(int ATFEID);
    __property int CurrIDShape = { read = FCurrIDShape };
    __property int CurrIDBlock = { read = FCurrIDBlock };
    __property int CurrIDLine = { read = FCurrIDLine };
};
#endif
