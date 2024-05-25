//
// Created by pupach on 11.05.24.
//

#include "BinTree.h"
ElemTree *FindPlaceInTreeBin(ElemTree *CurEl, int val)
{

  if(CurEl == NULL)   return NULL;
  //LOG("FindPlaceInTreeBin val = %d val = %d bool = %d", CurEl->val, val, (val == CurEl->val));
  if(val == CurEl->val)
  {
    return CurEl;
  }
  else if(val >= CurEl->val)
  {
    if(CurEl->right == NULL)  return CurEl;
    return FindPlaceInTreeBin(CurEl->right, val);
  }
  else{
    if(CurEl->left == NULL)  return CurEl;
    return FindPlaceInTreeBin(CurEl->left, val);
  }
}

void InsertBin(BinTree *tree, ElemTree *ElemToIns)
{
  if(tree->head == NULL)
  {
    tree->head = ElemToIns;
    return;
  }
  ElemTree *ptr = FindPlaceInTreeBin(tree->head, ElemToIns->val);

  if(ElemToIns->val == ptr->val)
  {
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
}

void RemoveBin(BinTree *tree, int numb)
{
  if(tree->head == NULL)
  {
    return;
  }
  ElemTree *ptr = FindPlaceInTreeBin(tree->head, numb);

  if(numb != ptr->val)
  {
    return;
  }
  else if((ptr->left != NULL) && (ptr->right != NULL))
  {
    ElemTree *head = FindPlaceInTreeBin(ptr->left, numb);

    if(head != ptr->left) {
      head->left = ptr->left;
      SetParent(ptr->left, head);
      GetParent(head)->right = NULL;
    }
    head->prev = ptr->prev;
    head->right = ptr->right;
    SetParent(ptr->right, head);
    if(GetParent(ptr) != NULL)
    {
      if(GetParent(ptr)->left == ptr)  GetParent(ptr)->left  = head;
      if(GetParent(ptr)->right == ptr) GetParent(ptr)->right = head;
    }
    else
    {
      tree->head = head;
    }
  }
  else if(GetParent(ptr) == NULL)
  {
    if(ptr->left != NULL)
    {
      tree->head = ptr->left;
      SetParent(ptr->left, NULL);
    }
    else if(ptr->right != NULL)
    {
      tree->head = ptr->right;
      SetParent(ptr->right, NULL);
    }
    else
    {
      tree->head = NULL;
    }
  }
  else if(ptr->left != NULL)
  {
    if(GetParent(ptr)->left == ptr)  GetParent(ptr)->left  = ptr->left;
    if(GetParent(ptr)->right == ptr) GetParent(ptr)->right = ptr->left;

    SetParent(ptr->left, GetParent(ptr));
  }
  else if(ptr->right != NULL)
  {
    if(GetParent(ptr)->left == ptr)  GetParent(ptr)->left  = ptr->right;
    if(GetParent(ptr)->right == ptr) GetParent(ptr)->right = ptr->right;

    SetParent(ptr->right, GetParent(ptr));
  }
  else
  {
    if(GetParent(ptr)->left == ptr)  GetParent(ptr)->left  = NULL;
    if(GetParent(ptr)->right == ptr) GetParent(ptr)->right = NULL;
  }
}
