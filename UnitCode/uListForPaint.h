//---------------------------------------------------------------------------

#ifndef uListForPaintH
#define uListForPaintH
//---------------------------------------------------------------------------
class TListForPaintItem
{
    private:
      void* f_point; //указатель на класс который надо перерисовывать
      int f_type; //тип класса
    public:
      TListForPaintItem(void* AClassPoint, int AType);
      __property void* ClassPoint = {read = f_point};
      __property int Type = {read = f_type};

};

class TListForPaint
{
    private:
      int f_Count;
      TList* List;
      void FreeList();
      TListForPaintItem* __fastcall GetItem(int AIndex);
      bool IsExist(void* AClassPoint);
    public:
      TListForPaint();
      ~TListForPaint();
      bool AddForPaint(void* AClassPoint, int AType);
      void Clear();
      __property TListForPaintItem* Items[int AIndex] = { read =  GetItem};
      __property int Count = {read = f_Count};
};


#endif
