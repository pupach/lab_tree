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


#define POISON_VAL 2000000
#define MAX(a, b) \
  (a > b ? a : b)
#define MAX_SIZE_COM 3


typedef struct
{
    struct ElemRBT *prev;
    bool red;
    int val;
    struct ElemRBT* right;
    struct ElemRBT* left;
}ElemRBT;

/**
 * @brief Вставляет узел в дерево
 * 
 * @param[in] указатель на узел, являющийся корнем дерева
 * @param[in] Узел для вставки
 *  @return новый узел, являющийся корнем дерева
 */
ElemRBT *InsertRBT(ElemRBT *head, ElemRBT *elem);

/**
 * @brief Удаляет имеющийся ключ из дерева
 * 
 * @param[in] указатель на узел, являющийся корнем дерева
 * @param[in] значение, подлежащее удалению
 *  @return новый узел, являющийся корнем дерева
 */
ElemRBT *RemoveRBT(ElemRBT *head, int val);

#endif //LAB_TREE_REDBLACKTREE_H
