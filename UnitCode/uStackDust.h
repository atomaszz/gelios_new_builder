//---------------------------------------------------------------------------

#ifndef uStackDustH
#define uStackDustH
#include "uBaseWorkShape.h"
#include "uListShape.h"
//---------------------------------------------------------------------------
class TNodeMain;
class TNodeAlt;

class TStackDustItemWS
{
   private:
     TNodeMain* f_Node;
     int f_NodePos;  //возможно не нужно
     bool f_CheckNesting;
     bool f_CheckAlternate;
   public:
     TStackDustItemWS(TNodeMain* ANode);
     __property bool CheckNesting = {read = f_CheckNesting, write = f_CheckNesting};
     __property bool CheckAlternate = {read = f_CheckAlternate, write = f_CheckAlternate};
     __property TNodeMain* Node = {read = f_Node};
     __property int NodePos = {read = f_NodePos, write = f_NodePos};

};


class TStackDustController
{
   private:
     TList *f_ListWS;
     TList *f_ListAlt;
     int f_posWS;
     int f_posAlt;
     void FreeListWS();
     bool IsExistsNode(TNodeMain* ANode);
     bool IsExistsAlternate(TNodeAlt *ANodeAlt);
    // void FreeListAlt();
   public:
      TStackDustController();
     ~TStackDustController();
     TStackDustItemWS* FirstWS();
     TStackDustItemWS* NextWS();
     TStackDustItemWS* PriorWS();
     TStackDustItemWS* LastWS();
     TNodeAlt* FirstAlt();
     TNodeAlt* NextAlt();
     TNodeAlt* PriorAlt();
     TNodeAlt* LastAlt();
     void ClearAll();
     void AddNode(TNodeMain* ANode, int APos);
     void AddAlternate(TNodeAlt *ANodeAlt);
};


#endif
