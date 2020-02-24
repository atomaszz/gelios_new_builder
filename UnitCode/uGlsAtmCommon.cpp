//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGlsAtmCommon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
TGlsNode::TGlsNode()
{
   _next = this;
   _prev = this;
}

TGlsNode::~TGlsNode()
{
}

TGlsNode* TGlsNode::insert(TGlsNode *ANode)
{
   TGlsNode* c = _next;
   ANode->_next = c;
   ANode->_prev = this;
   _next = ANode;
   c->_prev = ANode;
   return ANode;
}

TGlsNode* TGlsNode::remove()
{
   _prev->_next = _next;
   _next->_prev = _prev;
   _next =_prev = this;
   return this;
}

void TGlsNode::splice(TGlsNode *b)
{
   TGlsNode *a  = this;
   TGlsNode *an = a->_next;
   TGlsNode *bn = b->_next;
   a->_next = bn;
   b->_next = an;
   an->_prev = b;
   bn->_prev = a;
}

//------------------------------------------------------------------------------
TGlsList::TGlsList()
{
   header = new TGlsListNode(NULL);
   win = header;
   _length = 0;
}

TGlsList::~TGlsList()
{
   clear();
   delete header;
}

void TGlsList::clear()
{
   while ( length() > 0 )
   {
      first();
      remove();
   }
}


void* TGlsList::insert(void* T)
{
   win->insert(new TGlsListNode(T));
   ++_length;
   return T;
}

void* TGlsList::prepend(void* T)
{
   header->insert(new TGlsListNode(T));
   ++_length;
   return T;
}

void* TGlsList::append(void* T)
{
   header->Prev->insert(new TGlsListNode(T));
   ++_length;
   return T;
}

TGlsList* TGlsList::append(TGlsList* T)
{
   TGlsListNode *a = dynamic_cast<TGlsListNode*>(header->Prev);
   a->splice(T->header);
   _length+= T->_length;
   T->header->remove();
   T->_length = 0;
   T->win = header;
   return this;
}

void*  TGlsList::remove()
{
   if (win != header)
   {
     void *val = win->Val;
     win = dynamic_cast<TGlsListNode*>(win->Prev);
     delete dynamic_cast<TGlsListNode*>(win->Next->remove());
     --_length;
     return val;
   }
   return NULL;
}

void TGlsList::val(void* T)
{
   if (win != header)
     win->Val = T;
}

void* TGlsList::val()
{
   return win->Val;
}

void* TGlsList::next()
{
   win = dynamic_cast<TGlsListNode*>(win->Next);
   return win->Val;
}

void* TGlsList::prev()
{
   win = dynamic_cast<TGlsListNode*>(win->Prev);
   return win->Val;
}

void* TGlsList::first()
{
   win = dynamic_cast<TGlsListNode*>(header->Next);
   return win->Val;
}

void* TGlsList::last()
{
   win = dynamic_cast<TGlsListNode*>(header->Prev);
   return win->Val;
}

int TGlsList::length()
{
   return _length;
}

bool TGlsList::isFirst()
{
   return ( (win == header->Next ) && (_length >0) );
}

bool TGlsList::isLast()
{
   return ( (win == header->Next ) && (_length >0) );
}

bool TGlsList::isHead()
{
   return ( win == header );
}


//------------------------------------------------------------------------------
TGlsStack::TGlsStack()
{
   s = new TGlsList;
}

TGlsStack::~TGlsStack()
{
   delete s;
}

void TGlsStack::push(void* T)
{
   s->prepend(T);
}

void* TGlsStack::pop()
{
   s->first();
   return s->remove();
}

bool TGlsStack::empty()
{
   return (s->length() == 0);
}

int TGlsStack::size()
{
   return s->length();
}
                           
void* TGlsStack::top()
{
   return s->first();
}

void* TGlsStack::nextToTop()
{
   s->first();
   return s->next();
}

void* TGlsStack::bottom()
{
   return s->last();
}


//------------------------------------------------------------------------------
TGlsBTreeNode::TGlsBTreeNode(void *T)
{
    TGlsNode::TGlsNode();
   _val = T;
   _lchild = NULL;
   _rchild = NULL;
}

TGlsBTreeNode::~TGlsBTreeNode()
{
   if (_lchild) delete _lchild;
   if (_rchild) delete _rchild;
}


//------------------------------------------------------------------------------
TGlsBinaryTree::TGlsBinaryTree(TCmp ACmp)
{
   cmp = ACmp;
   win = root = new TGlsBTreeNode(NULL);
}

TGlsBinaryTree::~TGlsBinaryTree()
{
   delete root;
}

bool TGlsBinaryTree::isEmpty()
{
   return (root == root->Next);
}

void* TGlsBinaryTree::find(void *T)
{
   int res;
   TGlsBTreeNode *n = root->rchild;
   while(n)
   {
      res = (*cmp)(T, n->Val);
      if (res < 0)
        n = n->lchild;
      else if (res > 0)
        n = n->rchild;
      else
      {
        win = n;
        return n->Val;
      }
   }
   return NULL;
}


void* TGlsBinaryTree::findMin()
{
   win = dynamic_cast<TGlsBTreeNode*>(root->Next);
   return win->Val;
}

void* TGlsBinaryTree::findMax()
{
   win = dynamic_cast<TGlsBTreeNode*>(root->Prev);
   return win->Val;
}


void* TGlsBinaryTree::next()
{
   win = dynamic_cast<TGlsBTreeNode*>(win->Next);
   return win->Val;
}

void* TGlsBinaryTree::prev()
{
   win = dynamic_cast<TGlsBTreeNode*>(win->Prev);
   return win->Val;
}

void* TGlsBinaryTree::val()
{
   return win->Val;
}

void* TGlsBinaryTree::first()
{
   return findMin();
}

void* TGlsBinaryTree::last()
{
   return findMax();
}



void TGlsBinaryTree::inorder(bool (*acp) (void*))
{
   TGlsBTreeNode* n = dynamic_cast<TGlsBTreeNode*>(root->Next);
   while(n != root)
   {
      if (!((*acp)(n->Val))) break;
      n = dynamic_cast<TGlsBTreeNode*>(n->Next);
   }
}


void* TGlsBinaryTree::insert(void* T)
{
   int res = 1;
   TGlsBTreeNode *p = root;
   TGlsBTreeNode *n = root->rchild;
   while(n)
   {
      p = n;
      res = (*cmp)(T, p->Val);
      if (res <= 0)
         n = p->lchild;
      else
         n = p->rchild;
   }
   win = new TGlsBTreeNode(T);
   if ( res <= 0 )
   {
      p->lchild = win;
      p->Prev->insert(win);
   }
   else
   {
      p->rchild = win;
      p->insert(win);
   }
   return T;
}
