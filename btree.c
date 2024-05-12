//
// Created by pupach on 11.05.24.
//

#include "btree.h"

static size_t btree_node_size(struct btree *btree, bool leaf)
{
    size_t size =
    if (!leaf) {
        // add children as flexible array
        size += sizeof(struct btree_node*)*(btree->max_items+1);
    }

    return size;
}


btree_node *btree_node_new(btree *btree, bool leaf) {
    btree_node *node = btree->arr + btree->size;
    btree->size++;
    node->leaf = leaf;
    return node;
}

enum btree_mut_result {
    BTREE_NOCHANGE,
    BTREE_NOMEM,
    BTREE_MUST_SPLIT,
    BTREE_INSERTED,
    BTREE_REPLACED,
    BTREE_DELETED,
};

size_t btree_search(const btree *btree, btree_node *node,
                           int key, bool *found, int depth)
{
    int low = 0;
    int high = node->nitems-1;
    int index;

    while ( low <= high ) {
        int mid = (low + high) / 2;
        int item = node->items[mid];
        int cmp = (key - item);
        if (cmp == 0) {
            *found = true;
            return mid;
        }
        else if (cmp < 0) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    *found = false;
    return low;
}


enum btree_mut_result btree_node_set(btree *btree, btree_node *node, int item, int depth)
{
    bool found = false;
    size_t i = btree_search(btree, node, item, &found, depth);
    if (found) {
        return BTREE_REPLACED;
    }
    if (node->leaf) {
        if (node->nitems == btree->max_items) {
            return BTREE_MUST_SPLIT;
        }
        btree_node_shift_right(btree, node, i);
        btree_set_item_at(btree, node, i, item);
        return BTREE_INSERTED;
    }
    btree_cow_node_or(node->children[i], return BTREE_NOMEM);
    enum btree_mut_result result = btree_node_set(btree, node->children[i],
                                                  item, hint, depth+1);
    if (result == BTREE_INSERTED || result == BTREE_REPLACED) {
        return result;
    } else if (result == BTREE_NOMEM) {
        return BTREE_NOMEM;
    }
    // Split the child node
    if (node->nitems == btree->max_items) {
        return BTREE_MUST_SPLIT;
    }
    void *median = NULL;
    struct btree_node *right = NULL;
    btree_node_split(btree, node->children[i], &right, &median);
    if (!right) {
        return BTREE_NOMEM;
    }
    btree_node_shift_right(btree, node, i);
    btree_set_item_at(btree, node, i, median);
    node->children[i+1] = right;
    return btree_node_set(btree, node, item, hint, depth);
}


void *btree_set(btree *btree, int item)
{
    if (!btree->root) {
        btree->root = btree_node_new(btree, true);
        btree->root->items[0] = item;
        btree->root->rc++;
        btree->root->nitems = 1;
        btree->count++;
        btree->height++;

        return NULL;
    }
    enum btree_mut_result result;
    //set:
    result = btree_node_set(btree, btree->root, item, 0);
    if (result == BTREE_REPLACED) {
        return NULL;
    } else if (result == BTREE_INSERTED) {
        btree->count++;
        return NULL;
    }
    void *old_root = btree->root;
    struct btree_node *new_root = btree_node_new(btree, false);

    struct btree_node *right = NULL;
    void *median = NULL;
    btree_node_split(btree, old_root, &right, &median);

    btree->root = new_root;
    btree->root->children[0] = old_root;
    btree_set_item_at(btree, btree->root, 0, median);
    btree->root->children[1] = right;
    btree->root->nitems = 1;
    btree->height++;
    //goto set;

}
