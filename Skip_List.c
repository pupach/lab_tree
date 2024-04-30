//
// Created by pupach on 26.04.24.
//

#include "Skip_List.h"
Node *FindPlaceInList(Node *head, Node *ToInsert)
{
  Node *node;
  if(head->key > ToInsert->key)  return head;

  if(head->key == ToInsert->key)
  {
    if(head->down != NULL)  return FindPlaceInList(head->down, ToInsert);
  }

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
    if((head->key < ToInsert->key) && (node->key > ToInsert->key))
    {
      return FindPlaceInList(head->down, ToInsert);
    }
    else if(node->key >= ToInsert->key) return node;

    else  return head;
  }
}

void BuildNextLevel(Node *ToBuild, List *list)
{
  Node *f, *s, *prev;
  Node *NewLevel = list->arr + list->size;
  list->size++;

  NewLevel->key = ToBuild->key;
  NewLevel->down = ToBuild;

  Node* next = ToBuild;
  while(next->up == NULL)
  {
    next = next->next;
  }
  if(next->key == POISON_POSITIVE)
  {
    f = list->arr + list->size;
    s = list->arr + list->size + 1;
    list->size += 2;
    f->key = POISON_NEGATIVE;
    f->key = POISON_POSITIVE;
    f->next = s;
    s->prev = f;
    f->down = next;
    s->down = next->prev;
    next->up = s;
    prev = next->prev;
    prev->up = f;
    list->head = f;
    list->tail = s;
  }
  NewLevel->next = next;
  NewLevel->prev = next->prev;
  next->prev = NewLevel;
  ToBuild->up = NewLevel;
}

Node *Insert(List *list, Node *ToInsert)
{
  Node *to_ins = FindPlaceInList(list->head, ToInsert);
  ToInsert->prev = to_ins->prev;
  to_ins->prev = ToInsert;
  ToInsert->next = to_ins;

  int ver = rand() % 2;
  while(ver)
  {
    BuildNextLevel(ToInsert, list);
    ToInsert = ToInsert->up;
    ver = rand() % 2;
  }
  return NULL;
}

Node *Remove(List *list, Node *ToRemove)
{
  Node *to_ins = FindPlaceInList(list->head, ToRemove);
  if(to_ins->key != ToRemove->key)  return NULL;

  to_ins = ToRemove->next;
  to_ins->prev = ToRemove->prev;

  to_ins = ToRemove->prev;
  to_ins->next = ToRemove->next;

  while(ToRemove->up != NULL)
  {
    ToRemove = ToRemove->up;

    to_ins = ToRemove->next;
    to_ins->prev = ToRemove->prev;

    to_ins = ToRemove->prev;
    to_ins->next = ToRemove->next;
  }
  return NULL;
}


void ListInit(List *list, int MAX_SIZE_ARR)
{
  Node *f, *s;
  list->arr = (Node *)calloc(sizeof(Node), MAX_SIZE_ARR * 2);
  list->head = list->arr;
  list->tail = list->arr + 1;
  list->head->key = POISON_NEGATIVE;
  list->tail->key = POISON_POSITIVE;
  list->head->next = list->tail;
  list->tail->prev = list->head;

  f = list->arr + 2;
  s = list->arr + 3;
  f->key = POISON_NEGATIVE;
  f->key = POISON_POSITIVE;
  f->next = s;
  s->prev = f;
  s->down = list->tail;
  f->down = list->head;
  list->head->up = f;
  list->tail->up = s;

  list->arr += 4;
}