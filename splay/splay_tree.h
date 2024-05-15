//
// Created by pupach on 25.04.24.
//

#ifndef LAB_TREE_SPLAY_TREE_H
#define LAB_TREE_SPLAY_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "..\node.h"


#define PowerUniverse 2147483647
#define MAX_RAND 1000000000
#define MAX_SIZE_TABLE 10000000
#define MAX_SIZE_CONSTS 30
#define MAX(a, b) \
  (a > b ? a : b)
#define MAX_SIZE_COM 3


ElemTree *InsertSplay(ElemTree *tree, ElemTree *ElemToIns);

ElemTree *RemoveSPlay(ElemTree *head, int elem);

#endif //LAB_TREE_SPLAY_TREE_H
