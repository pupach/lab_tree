//
// Created by pupach on 26.04.24.
//

#include "Skip_List.h"
Node *FindPlaceInList(Node *head, Node *ToInsert)
{
  Node *node;
  if(head->key >= ToInsert->key)  return head;

  if(head->down == NULL)
  {
    if(head->key < ToInsert->key)
    {
      return FindPlaceInList(head->next, ToInsert);
    }
    return head;
  }
  else
  {
    node = head->next;
    if((head->key < ToInsert->key) && (node->key < ToInsert->key))
    {
      return FindPlaceInList(head->next, ToInsert);
    }
    else if(node->key >= ToInsert->key) return node;

    else  return head;
  }
}

Node *Insert(List *list, Node *ToInsert)
{
  Node *to_ins = FindPlaceInList(list->head, ToInsert);
  ToInsert->prev = to_ins->prev;
  to_ins->prev = ToInsert;
  ToInsert->next = to_ins;
}

void ListInit(List *list, int MAX_SIZE_ARR)
{
  list->arr = (Node *)calloc(sizeof(Node), MAX_SIZE_ARR * 2);
  
}