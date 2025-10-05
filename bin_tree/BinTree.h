//
// Created by pupach on 11.05.24.
//

#ifndef LAB_TREE_BINTREE_H
#define LAB_TREE_BINTREE_H

#include "ElemTree.h"
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

}BinTree;

void InsertBin(BinTree *tree, ElemTree *ElemToIns);

void RemoveBin(BinTree *tree, int elem);


#endif //LAB_TREE_BINTREE_H
