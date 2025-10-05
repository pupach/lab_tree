//
// Created by pupach on 21.04.24.
//

#ifndef LAB_TREE_node_H
#define LAB_TREE_node_H
#define LOG(args...) \
    //fprintf(stderr, args)

extern struct node;

typedef struct
{
    struct node *prev;
    int val;
    int deep;
    int delta;
    int size;
    int priorety;
    struct node* right;
    struct node* left;
}node;

typedef struct{
    node *min;
    node *max;
}SlicersTree;

node *parent_get(node *elem);

void parent_set(node *elem, node *parent);

void rotate_right(node *head);

void rotate_left(node *head);


#endif //LAB_TREE_node_H
