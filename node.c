//
// Created by pupach on 21.04.24.
//

#include "node.h"

ElemTree *GetParent(ElemTree *elem)
{
  if(elem == NULL) return  NULL;
  return elem->prev;

}

void SetParent(ElemTree *elem, ElemTree *parent)
{
  if(elem == NULL) return ;
  elem->prev = parent;
}

void RightRotate(ElemTree *head)
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

void LeftRotate(ElemTree *head)
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

