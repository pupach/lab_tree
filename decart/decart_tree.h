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



#include "..\node.h"

/**
 * @brief Вставляет узел в дерево
 * 
 * @param[in] указатель на узел, являющийся корнем дерева
 * @param[in] Узел для вставки
 *  @return новый узел, являющийся корнем дерева
 */
node *InsertDecart(node *tree, node * val);
/**
 * @brief Удаляет имеющийся ключ из дерева
 * 
 * @param[in] указатель на узел, являющийся корнем дерева
 * @param[in] значение, подлежащее удалению
 *  @return новый узел, являющийся корнем дерева
 */
node *RemoveDecart(node *head, int elem);
#endif //LAB_TREE_DECARTACH_H
