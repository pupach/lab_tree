#include "splay_tree.h"

void rotate_leftSplay(node *head)
{
  node *another, *another_prev_head;
  node *to_rotate = head->right;
  node *prev_head = head->prev;
  node *to_change = NULL;
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

void rotate_rightSplay(node *head)
{
  node *another, *another_prev_head;
  node *to_rotate = head->left;
  node *prev_head = head->prev;
  node *to_change = NULL;
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


node *Zig(node *head)
{
  node *father      = parent_get(head);
  node *grandfather = parent_get(father);
  if(father == NULL)  return head;
  else if(grandfather == NULL)
  {
    if(father->left == head)
    {
      rotate_rightSplay(father);
    }
    else if(father->right == head)
    {
      rotate_leftSplay(father);
    }
    else
    {
      LOG("ERRRRRORRRRR\n");
    }
  }
  else if((grandfather->left == father) && (father->left == head))
  {
    rotate_rightSplay(grandfather);
    rotate_rightSplay(father);
  }
  else if((grandfather->right == father) && (father->right == head))
  {
    rotate_leftSplay(grandfather);
    rotate_leftSplay(father);
  }
  else if((grandfather->left == father) && (father->right == head))
  {
    rotate_leftSplay(father);
    rotate_rightSplay(grandfather);
  }
  else if((grandfather->right == father) && (father->left == head))
  {
    rotate_rightSplay(father);
    rotate_leftSplay(grandfather);
  }
  else
  {
    LOG("ERRRRRORRRRR\n");
  }
  return head;
}

node *Splay(node *elem)
{
  while(elem->prev != NULL)
  {
    Zig(elem);
  }
  return elem;
}


int CmpTreeElem(node *f, int val)
{
  return f->val - val;
}


node *FindMinElSplay(node *tree, int elem)
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

SlicersTree Split(node *tree, int elem)
{
  SlicersTree ret = {};
  if(tree == NULL)  return ret;

  tree = FindMinElSplay(tree, elem);
  LOG("tree-min = %d\n", tree->val);

  if((CmpTreeElem(tree, elem) > 0))
  {
    parent_set(tree->left, NULL);
    ret.min = tree->left;
    ret.max = tree;
    tree->left = NULL;
    return ret;
  }
  else{
      parent_set(tree->right, NULL);

        ret.max = tree->right;
        ret.min = tree;
        tree->right = NULL;
        return ret;
  }
}

node *InsertSplay(node *tree, node *ElemToIns)
{
  SlicersTree ret = Split(tree, ElemToIns->val);
  if(tree != NULL) {
      LOG("tree.val = %d ElemToIns.val = %d\n ret.min = %p ret.max = %p\n", tree->val, ElemToIns->val, ret.min, ret.max);
  }

  parent_set(ret.min, ElemToIns);
  parent_set(ret.max, ElemToIns);
  ElemToIns->left = ret.min;
  ElemToIns->right = ret.max;

  return ElemToIns;
}

node *Merge(node *left, node *right)
{
  if(left == NULL)  return  right;
  if(right == NULL) return  left;

  right = FindMinElSplay(right, left->val);
  right->left = left;
  parent_set(left, right);
  return right;
}

node *RemoveSPlay(node *head, int elem)
{
  head = FindMinElSplay(head, elem);
  if(CmpTreeElem(head, elem) != 0)  return head;
  else
  {
    parent_set(head->left, NULL);
    parent_set(head->right, NULL);

    return Merge(head->left, head->right);
  }
}
