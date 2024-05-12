//
// Created by pupach on 11.05.24.
//

#ifndef LAB_HASH_BTREE_H
#define LAB_HASH_BTREE_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT_CHILDREN

typedef struct {
    int rc;
    bool leaf;
    size_t nitems:16;
    int *items[AMOUNT_CHILDREN];
    struct btree_node *children[AMOUNT_CHILDREN];
}btree_node;

typedef struct{

    btree_node *root;        // root node or NULL if empty tree
    size_t count;            // number of items in tree
    size_t height;           // height of tree from root to leaf
    size_t max_items;        // max items allowed per node before needing split
    size_t min_items;        // min items allowed per node before needing join
    btree_node *arr;
    int size;
} btree;


#endif //LAB_HASH_BTREE_H


