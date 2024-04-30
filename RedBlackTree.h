//
// Created by pupach on 25.04.24.
//

#ifndef LAB_TREE_REDBLACKTREE_H
#define LAB_TREE_REDBLACKTREE_H

#define MODULE 1000000000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "ElemTree.h"


#define POISON_VAL 2000000
#define MAX(a, b) \
  (a > b ? a : b)
#define MAX_SIZE_COM 3
#define LOG(args...) \
    //   fprintf(stderr, args)


typedef struct
{
    struct ElemTree *prev;
    bool red;
    int val;
    struct ElemTree* right;
    struct ElemTree* left;
}ElemRBT;

ElemRBT *InsertRBT(ElemRBT *head, ElemRBT *elem);

ElemRBT *RemoveRBT(ElemRBT *head, int val);

#endif //LAB_TREE_REDBLACKTREE_H
