//
// Created by pupach on 25.04.24.
//

#ifndef LAB_TREE_AVL_TREE_H
#define LAB_TREE_AVL_TREE_H

#include "..\node.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PowerUniverse 2147483647
#define MAX_RAND 1000000000
#define MAX_SIZE_TABLE 10000000
#define MAX_SIZE_CONSTS 3
#define MAX(a, b) \
  (a > b ? a : b)
#define MAX_SIZE_COM 3


typedef struct{
    ElemTree *head;
}AvlTree;

void InsertAvl(AvlTree *tree, ElemTree *ElemToIns);

void RemoveAvl(AvlTree *tree, int elem);

ElemTree *AvlRemove(ElemTree *avl, int key);

#endif //LAB_TREE_AVL_TREE_H
