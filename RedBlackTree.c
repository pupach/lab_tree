#include "RedBlackTree.h"


bool GetRed(ElemRBT *elem) {
  if (elem == NULL) return false;
  return elem->red;
}

void RevertClour(ElemRBT *elem)
{
  if(elem != NULL)  elem->red = !(elem->red);
}

ElemRBT *FindUncle(ElemRBT *child)
{
  ElemRBT *grfath = GetParent(child->prev);
  if(grfath == NULL)  return NULL;

  if(grfath->left == child->prev) return grfath->right;
  if(grfath->right == child->prev) return grfath->left;
}

ElemRBT *FindPlaceInTreeRDT(ElemRBT *CurEl, int val)
{
  if(val == CurEl->val)
  {
    return CurEl;
  }
  else if(val >= CurEl->val)
  {
    if(CurEl->right == NULL)  return CurEl;
    return FindPlaceInTreeRDT(CurEl->right, val);
  }
  else{
    if(CurEl->left == NULL)  return CurEl;
    return FindPlaceInTreeRDT(CurEl->left, val);
  }
}

ElemRBT * BalanceColour(ElemRBT *head)
{
  ElemRBT *uncle, *father, *grandfather;

  if(head->red == 0)  return NULL;

  else
  {
    uncle = FindUncle(head);

    father = GetParent(head);
    if(father == NULL)  return head;

    grandfather = GetParent(father);
    bool chvet = GetRed(uncle);

    if(chvet == 1)
    {
      RevertClour(uncle);
      RevertClour(father);
      RevertClour(grandfather);
      return BalanceColour(grandfather);
    }
    else
    {
      if(GetParent(father)->right == father)
      {
        if(father->left == head)
        {
          LeftRotate(father);
        }
        RightRotate(GetParent(father));
      }
      else
      {
        if(father->right == head)
        {
          RightRotate(father);
        }
        LeftRotate(GetParent(father));
      }
      RevertClour(father);
      RevertClour(grandfather);

      return NULL;
    }
  }
}

ElemRBT *InsertRBT(ElemRBT *head, ElemRBT *elem)
{
  ElemRBT *res = FindPlaceInTreeRDT(head, elem->val);
  elem->prev = res;
  if(res->val == elem->val)
  {
    return head;
  }
  else if(res->val >= elem->val)
  {
    res->right = elem;

  }
  else
  {
    res->left = elem;
  }
  elem->red = 1;
  bool chvet = GetRed(res->prev);
  head->red  = chvet;

  return BalanceColour(elem);
}

void BalanceColourRemove(ElemRBT *head)
{
  if(head == NULL) return;
  ElemRBT *brother, *father, *child;
  if(head->red == 1)
  {
    head->red = 0;
  }
  else
  {
    father =  GetParent(head);

    if(GetRed(father->left) == 1)
    {
      brother = father->left;
      LeftRotate(father);
      RevertClour(father);
      RevertClour(brother);
      //LeftRotate(father);
    }
    else if(GetRed(father->right) == 1)
    {
      brother = father->right;
      //LeftRotate(head->prev);
      RevertClour(father);
      RevertClour(brother);
      RightRotate(father);
    }
    else
    {
      if(father->right == head) brother = father->left;
      if(father->left == head) brother = father->right;

      if((GetRed(brother->left) == 0) && (GetRed(brother->right) == 0))
      {
        RevertClour(brother);
        if(father->red == 0)
        {
          BalanceColourRemove(father);
        }
        else {
          father->red = 0;
        }
      }
      else if(father->right == brother)
      {
        if(GetRed(brother->right) == 0) {
          LeftRotate(brother);
          RevertClour(brother);
          RevertClour(brother->left);
        }
        else
        {
          brother->red = father->red;
          father->red = 0;
          child = brother->right;
          child->red = 0;
          RightRotate(father);
        }
      }
      else
      {
        if(GetRed(brother->left) == 0) {
          RightRotate(brother);
          RevertClour(brother);
          RevertClour(brother->right);
        }
        else
        {
          brother->red = father->red;
          father->red = 0;
          child = brother->left;
          child->red = 0;
          LeftRotate(father);
        }
      }
    }
  }
}

ElemRBT *RemoveRBT(ElemRBT *head, int val)
{
  ElemRBT *res = FindPlaceInTreeRDT(head, val);

  if((res->left == NULL) && (res->right == NULL))
  {
    if(GetParent(res)->left == res)  GetParent(res)->left = NULL;

    if(GetParent(res)->right == res) GetParent(res)->right = NULL;
  }
  else if(res->right == NULL)
  {
    if(GetParent(res)->left == res) {
      GetParent(res)->left = res->left;
      SetParent(res->left, GetParent(res)->left);
    }

    if(GetParent(res)->right == res) {
      GetParent(res)->right = res->left;
      SetParent(res->left, GetParent(res)->right);
    }
  }
  else if(res->left == NULL)
  {
    if(GetParent(res)->left == res) {
      GetParent(res)->left = res->right;
      SetParent(res->right, GetParent(res)->left);
    }

    if(GetParent(res)->right == res) {
      GetParent(res)->right = res->right;
      SetParent(res->right, GetParent(res)->right);
    }
  }
  else
  {
    ElemRBT *child_r = res->right;
    while(child_r->left != NULL)
    {
      child_r = child_r->left;
    }
    res->val = child_r->val;
    child_r->val = POISON_VAL;
    return RemoveRBT(child_r, POISON_VAL);
  }
  if(res->red == 1) return head;
  BalanceColourRemove(res->left);
  BalanceColourRemove(res->right);
  return head;
}




