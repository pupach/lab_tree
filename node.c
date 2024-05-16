//
// Created by pupach on 21.04.24.
//

#include "node.h"
#include <stddef.h>

node *parent_get(node *elem)
{
  if(elem == NULL) return  NULL;
  return elem->prev;

}

void parent_set(node *elem, node *parent)
{
  if(elem == NULL) return ;
  elem->prev = parent;
}

void rotate_right(node *head)
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

void rotate_left(node *head)
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

