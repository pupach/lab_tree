#include "rb_tree.h"

void rotate_rightRBT(ElemRBT *head)
{
    ElemRBT *another, *another_prev_head;
    ElemRBT *to_rotate = head->right;
    ElemRBT *prev_head = head->prev;
    ElemRBT *to_change = NULL;
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

void rotate_leftRBT(ElemRBT *head)
{
    ElemRBT *another, *another_prev_head;
    ElemRBT *to_rotate = head->left;
    ElemRBT *prev_head = head->prev;
    ElemRBT *to_change = NULL;
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



bool GetRedRBT(ElemRBT *elem) {
  if (elem == NULL) return false;
  return elem->red;
}

ElemRBT *parent_getRBT(ElemRBT *elem)
{
    if(elem == NULL) return  NULL;
    return elem->prev;

}


void RevertClour(ElemRBT *elem)
{
  if(elem != NULL)  elem->red = !(elem->red);
}

void parent_setRBT(ElemRBT *elem, ElemRBT *parent)
{
    if(elem == NULL) return ;
    elem->prev = parent;
}

ElemRBT *FindUncle(ElemRBT *child)
{
  ElemRBT *grfath = parent_getRBT(child->prev);
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
  else
  {
    if(CurEl->left == NULL)  return CurEl;
    return FindPlaceInTreeRDT(CurEl->left, val);
  }
}

ElemRBT *BalanceColour(ElemRBT *head)
{
  ElemRBT *uncle, *father, *grandfather;

  if(head->prev == NULL)
  {
      head->red = 0;
      return head;
  }
  else if(parent_getRBT(head)->red == 0)
  {
      head->red = 0;
      return NULL;
  }
  else
  {
    uncle = FindUncle(head);

    father = parent_getRBT(head);

    grandfather = parent_getRBT(father);
    bool chvet = GetRedRBT(uncle);

    if(chvet == 1)
    {
      RevertClour(uncle);
      RevertClour(father);
      RevertClour(grandfather);
      return BalanceColour(grandfather);
    }
    else
    {
      if(parent_getRBT(head)->right == father)
      {
        if(father->left == head)
        {
          rotate_leftRBT(father);
        }
        rotate_rightRBT(parent_getRBT(father));
      }
      else
      {
        if(father->right == head)
        {
          rotate_rightRBT(father);
        }
        rotate_leftRBT(parent_getRBT(father));
      }
      RevertClour(father);
      RevertClour(grandfather);

      return NULL;
    }
  }
}

ElemRBT *InsertRBT(ElemRBT *head, ElemRBT *elem)
{
    if(head == NULL)  return elem;
    ElemRBT *res = FindPlaceInTreeRDT(head, elem->val);
    
    elem->prev   = res;
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

    bool chvet = GetRedRBT(res->prev);
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
    father =  parent_getRBT(head);

    if(GetRedRBT(father->left) == 1)
    {
      brother = father->left;
      rotate_leftRBT(father);
      RevertClour(father);
      RevertClour(brother);
      //rotate_leftRBT(father);
    }
    else if(GetRedRBT(father->right) == 1)
    {
      brother = father->right;
      //rotate_leftRBT(head->prev);
      RevertClour(father);
      RevertClour(brother);
      rotate_rightRBT(father);
    }
    else
    {
      if(father->right == head) brother = father->left;
      if(father->left == head) brother = father->right;

      if((GetRedRBT(brother->left) == 0) && (GetRedRBT(brother->right) == 0))
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
        if(GetRedRBT(brother->right) == 0) {
          rotate_leftRBT(brother);
          RevertClour(brother);
          RevertClour(brother->left);
        }
        else
        {
          brother->red = father->red;
          father->red = 0;
          child = brother->right;
          child->red = 0;
          rotate_rightRBT(father);
        }
      }
      else
      {
        if(GetRedRBT(brother->left) == 0) {
          rotate_rightRBT(brother);
          RevertClour(brother);
          RevertClour(brother->right);
        }
        else
        {
          brother->red = father->red;
          father->red = 0;
          child = brother->left;
          child->red = 0;
          rotate_leftRBT(father);
        }
      }
    }
  }
}

ElemRBT *RemoveRBT(ElemRBT *head, int val)
{
  ElemRBT *res = FindPlaceInTreeRDT(head, val);
    if(res->val != val)   return head;

  if((res->left == NULL) && (res->right == NULL))
  {
    if(parent_getRBT(res)->left == res)  parent_getRBT(res)->left = NULL;

    if(parent_getRBT(res)->right == res) parent_getRBT(res)->right = NULL;

    if(res->red == 1) return head;
    BalanceColourRemove(res->prev);
  }
  else if(res->right == NULL)
  {
      if(parent_getRBT(res) == NULL)
      {
          parent_setRBT(res->left, parent_getRBT(res));
      }
    else if(parent_getRBT(res)->left == res) {
      parent_getRBT(res)->left = res->left;
      parent_setRBT(res->left, parent_getRBT(res));
    }

    else if(parent_getRBT(res)->right == res) {
      parent_getRBT(res)->right = res->left;
      parent_setRBT(res->left, parent_getRBT(res));
    }

    if(res->red == 1) return head;
    BalanceColourRemove(res->prev);
  }
  else if(res->left == NULL)
  {
    if(parent_getRBT(res) == NULL)
    {
      parent_setRBT(res->right, parent_getRBT(res));
    }
    else if(parent_getRBT(res)->left == res) {
      parent_getRBT(res)->left = res->right;
      parent_setRBT(res->right, parent_getRBT(res));
    }

    else if(parent_getRBT(res)->right == res) {
      parent_getRBT(res)->right = res->right;
      parent_setRBT(res->right, parent_getRBT(res));
    }

    if(res->red == 1) return head;
    BalanceColourRemove(res->left);
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
  return head;
}




