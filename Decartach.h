//
// Created by pupach on 25.04.24.
//

#ifndef LAB_TREE_DECARTACH_H
#define LAB_TREE_DECARTACH_H
#define MODULE 1000000000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define POISON_VAL 2000000
#define MAX(a, b) \
  (a > b ? a : b)
#define MAX_SIZE_COM 3
#define LOG(args...) \
    //   fprintf(stderr, args)

int deep = 0;

#include "ElemTree.h"

ElemTree *InsertDecart(ElemTree *tree, ElemTree * val);
ElemTree *DeleteDecart(ElemTree *tree, int val);
ElemTree *RemoveDecart(ElemTree *head, int elem);
#endif //LAB_TREE_DECARTACH_H
