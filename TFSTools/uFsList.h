//---------------------------------------------------------------------------

#ifndef uFsListH
#define uFsListH
//---------------------------------------------------------------------------
struct TFsNode//описание структуры
{
  void* Data;
  TFsNode *Next;
  TFsNode *Pred;
};

class TFsList
{
  private:
    TFsNode* FFirst;
    TFsNode* FMoveNode;
    int FMoveIndex;
    int FCount;
  public:
    TFsList() {FFirst = NULL; FMoveIndex = 0; FCount = 0;}
    ~TFsList() {Clear();}
    void Clear();
    void Add(void* AData);
    void* Delete(int APos);
    bool IsEmpty(){ return FFirst == NULL; }
    bool IsExists(void* AData);
    TFsNode* MoveInit(int APos);
    TFsNode* MoveNext();
    __property TFsNode* First = {read = FFirst};
    __property int Count = {read = FCount};



};

#endif
