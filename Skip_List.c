//
// Created by pupach on 26.04.24.
//

#include "Skip_List.h"

#define LOG(args...) \
    fprintf(stderr, args)


Node *FindPlaceInList(Node *head, int ToInsert)
{
  Node *node;
  if(head->key > ToInsert)  return head;

  if(head->key == ToInsert)
  {
    if(head->down != NULL)  return FindPlaceInList(head->down, ToInsert);

    else return head;
  }

  if(head->down == NULL)
  {
    if(head->key < ToInsert)
    {
      return FindPlaceInList(head->next, ToInsert);
    }
    LOG("ERRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOORRRRRRRRRRRR\n");
  }
  else
  {
    node = head->next;
    if(node->key > ToInsert)
    {
      return FindPlaceInList(head->down, ToInsert);
    }
    else if(node->key <= ToInsert) return FindPlaceInList(head->next, ToInsert);;

      LOG("ERRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOORRRRRRRRRRRR\n");
  }
}

void BuildNextLevel(Node *ToBuild, List *list)
{
  Node *f = NULL, *s = NULL, *prev = NULL;
  Node *NewLevel = list->arr + list->size;
  list->size++;

  NewLevel->key = ToBuild->key;
  NewLevel->down = ToBuild;
  Node* next = ToBuild;


  while(next->up == NULL)
  {
    next = next->next;
  }
  ToBuild->up = NewLevel;

  Node *up = next->up;
  if((next->key == POISON_POSITIVE) && (up->up == NULL))
  {
    f = list->arr + list->size;
    s = list->arr + list->size + 1;
    list->size += 2;
    f->key = POISON_NEGATIVE;
    s->key = POISON_POSITIVE;
    f->next = s;
    s->prev = f;
    s->down = up;
    f->down = up->prev;
    up->up = s;
    prev = up->prev;
    prev->up = f;
    list->head = up->prev;
    list->tail = up;
  }
  NewLevel->next = up;
  NewLevel->prev = up->prev;
  Node *prevs = up->prev;
  prevs->next = NewLevel;
  up->prev = NewLevel;
}

Node *Insert(List *list, Node *ToInsert)
{
  Node *to_ins = FindPlaceInList(list->head, ToInsert->key);
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
void RemoveNode(Node *rem)
{
  Node *next = rem->next;
  next->prev = rem->prev;

  Node *prev = rem->prev;
  prev->next = rem->next;
  if(rem->up != NULL) {
    rem = rem->up;
    rem->down = NULL;
    RemoveNode(rem);
  }

}
Node *Remove(List *list, int KeyToRemove)
{
  Node *to_rem = FindPlaceInList(list->head, KeyToRemove);
  if(to_rem->key != KeyToRemove)  return NULL;

  RemoveNode(to_rem);
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
  s->key = POISON_POSITIVE;
  f->next = s;
  s->prev = f;
  s->down = list->tail;
  f->down = list->head;
  list->head->up = f;
  list->tail->up = s;

  list->arr += 4;
}