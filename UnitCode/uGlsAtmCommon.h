//---------------------------------------------------------------------------

#ifndef uGlsAtmCommonH
#define uGlsAtmCommonH
//---------------------------------------------------------------------------
class TGlsNode
{
   protected:
     TGlsNode *_next;
     TGlsNode *_prev;
   public:
     TGlsNode();
     virtual  ~TGlsNode();
     TGlsNode *insert(TGlsNode *ANode);
     TGlsNode *remove();
     void splice(TGlsNode *b);

     __property TGlsNode* Next = {read = _next, write = _next};
     __property TGlsNode* Prev = {read = _prev, write = _prev};
};


class TGlsListNode: public TGlsNode
{
   private:
     void* _val;
   public:
     TGlsListNode( void* AVal ) {_val = AVal;}
     __property void* Val = {read = _val, write = _val};

};


class TGlsList: public TGlsNode
{
   private:
     TGlsListNode* header;
     TGlsListNode* win;
     int _length;
   public:
     TGlsList();
     ~TGlsList();
     void* insert(void* T);
     void* append(void* T);
     TGlsList* append(TGlsList* T);
     void* prepend(void* T);
     void* remove();
     void val(void* T);
     void* val();
     void* next();
     void* prev();
     void* first();
     void* last();
     int length();
     bool isFirst();
     bool isLast();
     bool isHead();
     void clear();
};


class TGlsStack
{
   private:
     TGlsList* s;
   public:
     TGlsStack();
     ~TGlsStack();
     void push(void* T);
     void* pop();
     bool empty();
     int size();
     void* top();
     void* nextToTop();
     void* bottom();
};


class TGlsBTreeNode: public TGlsNode
{
   private:
     TGlsBTreeNode *_lchild;
     TGlsBTreeNode *_rchild;
     void *_val;
   public:
     TGlsBTreeNode(void *T);
     virtual ~TGlsBTreeNode();
     __property void* Val = {read = _val, write = _val};
     __property TGlsBTreeNode* lchild = { read = _lchild, write = _lchild};
     __property TGlsBTreeNode* rchild = { read = _rchild, write = _rchild};

};

typedef int (*TCmp)(void *a, void *b);

class TGlsBinaryTree
{
   private:
     TGlsBTreeNode *root;
     TGlsBTreeNode *win;
     TCmp cmp;
     TGlsBTreeNode* _findMin(TGlsBTreeNode *n);
     TGlsBTreeNode* _findMax(TGlsBTreeNode *n);
   public:
     TGlsBinaryTree(TCmp ACmp);
     virtual ~TGlsBinaryTree();
     bool isEmpty();
     void* find(void *T);
     void* findMin();
     void* findMax();
     void inorder(bool (*) (void*));
     void* insert(void* T);
     void* next();
     void* prev();
     void* first();
     void* last();
     void* val();

};



#endif
