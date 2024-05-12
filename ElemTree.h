//
// Created by pupach on 21.04.24.
//

#ifndef LAB_TREE_ELEMTREE_H
#define LAB_TREE_ELEMTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LOG(args...) \
    //fprintf(stderr, args)

extern struct ElemTree;

typedef struct
{
    struct ElemTree *prev;
    int val;
    int deep;
    int delta;
    int size;
    int priorety;
    struct ElemTree* right;
    struct ElemTree* left;
}ElemTree;

typedef struct{
    ElemTree *min;
    ElemTree *max;
}SlicersTree;

ElemTree *GetParent(ElemTree *elem);

void SetParent(ElemTree *elem, ElemTree *parent);

void RightRotate(ElemTree *head);

void LeftRotate(ElemTree *head);


#endif //LAB_TREE_ELEMTREE_H
