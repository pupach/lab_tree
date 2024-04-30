#include "Splay_tree.h"

void LeftRotateSplay(ElemTree *head)
{
  ElemTree *another, *another_prev_head;
  ElemTree *to_rotate = head->right;
  ElemTree *prev_head = head->prev;
  ElemTree *to_change = NULL;
  if(to_rotate != NULL )    to_change = to_rotate->left;


  if(head->prev != NULL)
  {
    if (prev_head->left == head)
    {
      prev_head->left = to_rotate;
    }
    else
    {
      prev_head->right = to_rotate;
    }
  }

  to_rotate->prev = prev_head;
  to_rotate->left  = head;
  head->prev = to_rotate;


  if(to_change != NULL)   to_change->prev = head;
  head->right = to_change;

}

void RightRotateSplay(ElemTree *head)
{
  ElemTree *another, *another_prev_head;
  ElemTree *to_rotate = head->left;
  ElemTree *prev_head = head->prev;
  ElemTree *to_change = NULL;
  if(to_rotate != NULL )    to_change = to_rotate->right;

  if(head->prev != NULL)
  {
    if (prev_head->left == head)
    {
      prev_head->left = to_rotate;
    }
    else
    {
      prev_head->right = to_rotate;
    }
  }

  to_rotate->prev = prev_head;
  to_rotate->right  = head;
  head->prev = to_rotate;


  if(to_change != NULL)   to_change->prev = head;
  head->left = to_change;
}


ElemTree *Zig(ElemTree *head)
{
  ElemTree *father      = GetParent(head);
  ElemTree *grandfather = GetParent(father);
  if(father == NULL)  return head;
  else if(grandfather == NULL)
  {
    if(father->left == head)
    {
      RightRotateSplay(father);
    }
    else if(father->right == head)
    {
      LeftRotateSplay(father);
    }
    else
    {
      LOG("ERRRRRORRRRR\n");
    }
  }
  else if((grandfather->left == father) && (father->left == head))
  {
    RightRotateSplay(grandfather);
    RightRotateSplay(father);
  }
  else if((grandfather->right == father) && (father->right == head))
  {
    LeftRotateSplay(grandfather);
    LeftRotateSplay(father);
  }
  else if((grandfather->left == father) && (father->right == head))
  {
    LeftRotateSplay(father);
    RightRotateSplay(grandfather);
  }
  else if((grandfather->right == father) && (father->left == head))
  {
    RightRotateSplay(father);
    LeftRotateSplay(grandfather);
  }
  else
  {
    LOG("ERRRRRORRRRR\n");
  }
  return head;
}

ElemTree *Splay(ElemTree *elem)
{
  while(elem->prev != NULL)
  {
    Zig(elem);
  }
  return elem;
}


int CmpTreeElem(ElemTree *f, int val)
{
  return f->val - val;
}


ElemTree *FindMinElSplay(ElemTree *tree, int elem)
{
  if(tree == NULL)  return NULL;

  if(CmpTreeElem(tree, elem) == 0)
  {
    Splay(tree);
    return tree;
  }
  else if((CmpTreeElem(tree, elem) > 0) && (tree->left != NULL))
  {
    return FindMinElSplay(tree->left, elem);
  }
  else if((CmpTreeElem(tree, elem) < 0) && (tree->right != NULL))
  {
    return FindMinElSplay(tree->right, elem);
  }
  else
  {
    return Splay(tree);
  }
}

SlicersTree Split(ElemTree *tree, int elem)
{
  SlicersTree ret = {};
  if(tree == NULL)  return ret;

  tree = FindMinElSplay(tree, elem);
  if((CmpTreeElem(tree, elem) > 0))
  {
    SetParent(tree->left, NULL);


    ret.min = tree->left;
    ret.max = tree;
    tree->left = NULL;
    return ret;
  }
  else if((CmpTreeElem(tree, elem) < 0))
  {
    SetParent(tree->right, NULL);


    ret.max = tree->right;
    ret.min = tree;
    tree->right = NULL;
    return ret;
  }
}

ElemTree *InsertSplay(ElemTree *tree, ElemTree *ElemToIns)
{
  SlicersTree ret = Split(tree, ElemToIns->val);

  SetParent(ret.min, ElemToIns);
  SetParent(ret.max, ElemToIns);
  ElemToIns->left = ret.min;
  ElemToIns->right = ret.max;

  return ElemToIns;
}

ElemTree *Merge(ElemTree *left, ElemTree *right)
{
  if(left == NULL)  return  right;
  if(right == NULL) return  left;

  right = FindMinElSplay(right, left->val);
  right->left = left;
  SetParent(left, right);
  return right;
}

ElemTree *RemoveSPlay(ElemTree *head, int elem)
{
  head = FindMinElSplay(head, elem);
  if(CmpTreeElem(head, elem) != 0)  return head;
  else
  {
    SetParent(head->left, NULL);
    SetParent(head->right, NULL);

    return Merge(head->left, head->right);
  }
}
