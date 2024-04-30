#include "Avl_tree.h"

ElemTree *FindPlaceInTree(ElemTree *CurEl, int val)
{
  if(val == CurEl->val)
  {
    return CurEl;
  }
  else if(val >= CurEl->val)
  {
    if(CurEl->right == NULL)  return CurEl;
    return FindPlaceInTree(CurEl->right, val);
  }
  else{
    if(CurEl->left == NULL)  return CurEl;
    return FindPlaceInTree(CurEl->left, val);
  }
}

void SetHigh1(ElemTree *head)
{
  if(head == NULL)  return;
  ElemTree *left_tree = head->left;
  ElemTree *right_tree = head->right;
  if(right_tree == NULL)
  {
    if(left_tree != NULL) {
      head->deep = left_tree->deep + 1;
      head->delta = left_tree->deep;
    }
    else {
      head->deep = 1;
      head->delta = 0;
    }
  }
  else if(left_tree == NULL) {
    head->deep = right_tree->deep + 1;
    head->delta = -right_tree->deep;
  }
  else
  {
    head->deep = MAX(left_tree->deep, right_tree->deep) + 1;
    head->delta = left_tree->deep - right_tree->deep;
  }
}

void SetHigh(ElemTree *head)
{
  ElemTree *prev;

  SetHigh1(head);

  prev = head->prev;
  while(prev!= NULL)
  {
    SetHigh1(prev);
    prev = prev->prev;
  }
}

void LeftBigRotate(ElemTree *head) {
  RightRotate(head->left);

  LeftRotate(head);
}

void RightBigRotate(ElemTree *head) {
  LeftRotate(head->right);

  RightRotate(head);
}

ElemTree *UpdateDeepTree(ElemTree *ElemToUpd)
{
  SetHigh(ElemToUpd);
  ElemTree *to_rotate, *may, *k;
  int deep_may, deep_k;

  if(ElemToUpd->delta > 1)
  {
    to_rotate = ElemToUpd->left;
    if(to_rotate!= NULL)
    {
      may = to_rotate->right;
      k   = to_rotate->left;

      if(may == NULL) deep_may = 0;
      else            deep_may = may->deep;

      if(k == NULL) deep_k = 0;
      else            deep_k = k->deep;

      LOG("BID_ROT_CHECK %d %d \n", deep_may, deep_k);

      if(deep_may > deep_k)
      {
        LeftBigRotate(ElemToUpd);
        if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
        else  return ElemToUpd;
      }
    }
    LeftRotate(ElemToUpd);
    SetHigh(ElemToUpd);
  }
  else if(ElemToUpd->delta < -1)
  {
    to_rotate = ElemToUpd->right;
    if(to_rotate!= NULL)
    {
      may = to_rotate->right;
      k   = to_rotate->left;

      if(may == NULL) deep_may = 0;
      else            deep_may = may->deep;

      if(k == NULL) deep_k = 0;
      else            deep_k = k->deep;

      LOG("BID_ROT_CHECK %d %d \n", deep_may, deep_k);

      if(deep_may < deep_k)
      {
        RightBigRotate(ElemToUpd);
        if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
        else  return ElemToUpd;
      }
    }
    RightRotate(ElemToUpd);
    SetHigh(ElemToUpd);
  }
  LOG("UpdateDeepTree cur_el = %d deep = %d delta_deep = %d]\n", ElemToUpd->val, ElemToUpd->deep, ElemToUpd->delta);

  if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
  else  return ElemToUpd;
}

void InsertAvl(AvlTree *tree, ElemTree *ElemToIns)
{
  if(tree->head == NULL)
  {
    tree->head = ElemToIns;
    ElemToIns->deep = 1;
    UpdateDeepTree(tree->head);
    return;
  }
  ElemTree *ptr = FindPlaceInTree(tree->head, ElemToIns->val);

  if(ElemToIns->val == ptr->val)
  {
    UpdateDeepTree(tree->head);
    return;
  }
  else if(ElemToIns->val >= ptr->val)
  {
    ptr->right = ElemToIns;

  }
  else
  {
    ptr->left = ElemToIns;
  }
  ElemToIns->prev = ptr;
  ElemToIns->deep = 1;
  tree->head = UpdateDeepTree(ElemToIns->prev);
  ElemTree  *prev = ElemToIns->prev;
  LOG("Insert after %d HEAD = %d \n", prev->val, tree->head->val);
}


int FindMinElAvl(AvlTree *tree, int ogr)
{
  int res = -1;
  ElemTree *cur_el = tree->head;
  while(cur_el != NULL)
  {
    if(cur_el->val >= ogr)
    {
      res = cur_el->val;
      cur_el = cur_el->left;
    }
    else
    {
      cur_el = cur_el->right;
    }
  }
  return res;
}

void RemoveAvl(AvlTree *tree, int elem)
{
  ElemTree  *res = FindPlaceInTree(tree, elem);
  if(res != NULL)
  {
    ElemTree *min = FindPlaceInTree(tree, res->val);
    if(min == NULL)
    {
      
    }
  }
}


