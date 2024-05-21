//
// Created by pupach on 12.05.24.
//

#ifndef LAB_HASH_B_TREE_H
#define LAB_HASH_B_TREE_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 10
#define MAX_CHILDREN 10

typedef struct{
    int n;
    int key[MAX_KEYS * 2];
    struct NodeBTree *child[MAX_CHILDREN * 2 + 1];
    bool leaf;
}NodeBTree;

typedef struct{

    NodeBTree *root;
    size_t count;
    size_t height;
    NodeBTree *arr;
    int size;
} btree;


/**
 * @brief Удаляет имеющийся ключ из дерева
 * 
 * @param[in] указатель на структуру самого дерева
 * @param[in] значение, подлежащее удалению
 */
void removeBtree(btree *tree, int k);

/**
 * @brief Вставляет узел в дерево
 * 
 * @param[in] указатель на структуру самого дерева
 * @param[in] Значение для вставки
 */
void insert(btree *tree, int k);

#endif //LAB_HASH_B_TREE_H
