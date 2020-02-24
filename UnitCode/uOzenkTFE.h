//---------------------------------------------------------------------------

#ifndef uOzenkTFEH
#define uOzenkTFEH
//---------------------------------------------------------------------------
#include "uZadacha.h"
#include "uPartialDecision.h"

class TOzenkTFE
{
  private:
    TPartialDecision* f_PartialDecision;
    TList* f_ListPredicateTreeItem;
    TDischargedMassiv* f_ozenk;
    TDischargedMassiv* f_ozenk1;
    TDischargedMassiv* f_ozenk0;
    void FillMassiv(TBaseShape* ATFE);
    void OzenkItem(TPredicateTreeItem* AItem);
  public:
    TOzenkTFE(TPartialDecision* APartialDecision);
    ~TOzenkTFE();
    void AddPredicateTree(TPredicateTreeItem* ANode);
    void InitMassiv();
    double ValueOzenk(int APos);
    double ValueOzenk1(int APos);

    void Ozenk();
};
#endif
