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
    node *head;
}AvlTree;

/**
 * @brief Inserts the key in tree.
 * 
 * @param[in] указатель на находящиеся в структуре Avl дерево
 * @param[in] Узел для вставки
 */

void InsertAvl(AvlTree *tree, node *ElemToIns);
/**
 * @brief Удаляет имеющийся ключ из дерева
 * 
 * @param[in] указатель на находящиеся в структуре Avl дерево
 * @param[in] знвчение, подлежащее удалению
 */
void RemoveAvl(AvlTree *tree, int elem);

/**
 * @brief Удаляет имеющийся ключ из дерева
 * 
 * @param[in] указатель на корень дерева
 * @param[in] знвчение, подлежащее удалению
 *  @return указатель на узел, наиболее близкий по значению к удаленному
 */
node *AvlRemove(node *avl, int key);

#endif //LAB_TREE_AVL_TREE_H
