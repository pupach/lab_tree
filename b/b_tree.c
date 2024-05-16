//
// Created by pupach on 12.05.24.
//

#include "b_tree.h"




NodeBTree* BtreeSearch(NodeBTree* x, int k) {
    int i = 0;
    while (i < x->n && k > x->key[i]) {
        i++;
    }
    if (i < x->n && k == x->key[i]) {
        return x;
    }
    if (x->leaf) {
        return NULL;
    }
    return BtreeSearch(x->child[i], k);
}
void InsertDontFull(btree *tree, NodeBTree *node, int k);

void SplitChild(btree *tree, NodeBTree *node, int i, NodeBTree *y);

void insert(btree *tree, int k)
{
    if (tree->root == NULL)
    {
        tree->root = tree->arr + tree->size;
        tree->root->leaf = true;
        tree->size++;
        tree->root->key[0] = k;
        tree->root->n = 1;
    }
    else
    {
        if (tree->root->n == 2*MAX_CHILDREN-1)
        {
            NodeBTree *s = tree->arr + tree->size;
            s->leaf = false;
            tree->size++;
            s->child[0] = tree->root;

            SplitChild(tree, s, 0, tree->root);

            int i = 0;
            if (s->key[0] < k)
                i++;

            InsertDontFull(tree, s->child[i], k);
            tree->root = s;
        }
        else
        {
            InsertDontFull(tree, tree->root, k);
        }
    }
}

void InsertDontFull(btree *tree, NodeBTree *node, int k)
{
    int i = node->n-1;
    
    if (node->leaf == true)
    {
        while (i >= 0 && node->key[i] > k)
        {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i+1] = k;
        node->n = node->n + 1;
    }
    else {
        while (i >= 0 && node->key[i] > k)
            i--;
        NodeBTree *vers = node->child[i + 1];
        if (vers->n == 2 * MAX_CHILDREN - 1)
        {
            SplitChild(tree,node, i+1, node->child[i+1]);

            if (node->key[i + 1] < k)
                i++;
        }
        InsertDontFull(tree, node->child[i+1], k);
    }
}

void SplitChild(btree *tree, NodeBTree *node, int i, NodeBTree *y)
{
    NodeBTree *z = tree->arr + tree->size;
    z->leaf = y->leaf;
    tree->size++;

    z->n = MAX_CHILDREN - 1;
    for (int j = 0; j < MAX_CHILDREN-1; j++)
        z->key[j] = y->key[j + MAX_CHILDREN];

    if (y->leaf == false)
    {
        for (int j = 0; j < MAX_CHILDREN; j++)
            z->child[j] = y->child[j + MAX_CHILDREN];
    }
    y->n = MAX_CHILDREN - 1;
    for (int j = node->n; j >= i+1; j--)
        node->child[j + 1] = node->child[j];

    node->child[i+1] = z;
    for (int j = node->n-1; j >= i; j--)
        node->key[j+1] = node->key[j];

    node->key[i] = y->key[MAX_CHILDREN - 1];

    node->n = node->n + 1;
}

int FindKey(NodeBTree *node, int k)
{
    int index = 0;
    while (index<node->n && (node->key[index] < k)) {
      ++index;
    }
    return index;
}
void RemoveFromLeaf (NodeBTree *node, int index);

void RemoveFromDontLeaf(NodeBTree *node, int index);

void FillNode(NodeBTree *node, int index);

int Get(NodeBTree *node, int index);

int parent_getBTree(NodeBTree *node, int index);

void BorrowPrev(NodeBTree *node, int index);

void BorrowNext(NodeBTree *node, int index);

void MergeBtree(NodeBTree *node, int index);

void RemoveNodeBTree(NodeBTree *node, int k)
{
    int index = FindKey(node, k);
    
    if (index < node->n && node->key[index] == k)
    {
        if (node->leaf)
            RemoveFromLeaf(node, index);
        else
            RemoveFromDontLeaf(node, index);
    }
    else
    {
        if (node->leaf)
        {
            return;
        }
        bool flag = ( (index==node->n)? true : false );

        NodeBTree *child = node->child[index];
        if (child->n < MAX_CHILDREN)
            FillNode(node, index);

        if (flag && index > node->n)
          RemoveNodeBTree(node->child[index - 1], k);
        else
          RemoveNodeBTree(node->child[index]  , k);
    }
    return;
}

void RemoveFromLeaf (NodeBTree *node, int index)
{
    for (int i = index + 1; i < MAX_CHILDREN; ++i)
        node->key[i - 1] = node->key[i];

    node->n--;
    return;
}

void RemoveFromDontLeaf(NodeBTree *node, int index)
{

    int k = node->key[index];

    NodeBTree *child = node->child[index];
    if (child->n >= MAX_CHILDREN)
    {
        int pred = parent_getBTree(node, index);
        node->key[index] = pred;
        RemoveNodeBTree(node->child[index], pred);
    }
    else if  ((child + 1)->n >= MAX_CHILDREN)
    {
        int succ = Get(node, index);
        node->key[index] = succ;
        RemoveNodeBTree(node->child[index + 1], succ);
    }
    else
    {
        MergeBtree(node, index);
        RemoveNodeBTree(node->child[index], k);
    }
    return;
}

int parent_getBTree(NodeBTree *node, int index)
{
    NodeBTree *cur = node->child[index];
    while (!cur->leaf)
        cur = cur->child[cur->n];
    
    return cur->key[cur->n-1];
}

int Get(NodeBTree *node, int index)
{
    NodeBTree *cur = node->child[index + 1];
    while (!cur->leaf)
        cur = cur->child[0];
    
    return cur->key[0];
}

void FillNode(NodeBTree *node, int index)
{
  if(index!=0 ) {
    NodeBTree *child = node->child[index - 1];
    if (child->n >= MAX_CHILDREN) {
      BorrowPrev(node, index);
    } else if (index != node->n && (child + 2)->n >= MAX_CHILDREN) {
      BorrowNext(node, index);
    } else {
      if (index != node->n)
        MergeBtree(node, index);
      else
        MergeBtree(node, index - 1);
    }
    return;
  }
  NodeBTree *child = node->child[index + 1];
  if (index != node->n && (child + 2)->n >= MAX_CHILDREN) {
    BorrowNext(node, index);
  }
  else {
    if (index != node->n)
      MergeBtree(node, index);
    else
      MergeBtree(node, index - 1);
  }
}

void BorrowPrev(NodeBTree *node, int index)
{

    NodeBTree *child = node->child[index];
    NodeBTree *sibling = node->child[index - 1];
    
    for (int i=child->n-1; i>=0; --i)
        child->key[i+1] = child->key[i];
    
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->child[i+1] = child->child[i];
    }
    child->key[0] = node->key[index - 1];
    
    if(!child->leaf)
        child->child[0] = sibling->child[sibling->n];
    
    node->key[index - 1] = sibling->key[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
    return;
}

void BorrowNext(NodeBTree *node, int index)
{

    NodeBTree *child = node->child[index];
    NodeBTree *sibling = node->child[index+1];
    
    child->key[(child->n)] = node->key[index];
    if (!(child->leaf))
        child->child[(child->n)+1] = sibling->child[0];
    node->key[index] = sibling->key[0];

    for (int i=1; i<sibling->n; ++i)
        sibling->key[i-1] = sibling->key[i];

    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->child[i-1] = sibling->child[i];
    }
    child->n += 1;
    sibling->n -= 1;
    return;
}

void MergeBtree(NodeBTree *node, int index)
{
    NodeBTree *child = node->child[index];
    NodeBTree *sibling = node->child[index + 1];
    child->key[MAX_CHILDREN - 1] = node->key[index];

    for (int i = 0; i < sibling->n; ++i)
        child->key[i + MAX_CHILDREN] = sibling->key[i];

    if (!child->leaf)
    {
        for(int i = 0; i <= sibling->n; ++i)
            child->child[i + MAX_CHILDREN] = sibling->child[i];
    }
    for (int i = index + 1; i < node->n; ++i)
        node->key[i - 1] = node->key[i];

    for (int i = index + 2; i <= node->n; ++i)
        child[i - 1] = child[i];

    child->n += sibling->n + 1;
    node->n--;
    return;
}

void removeBtree(btree *tree, int k)
{
    if (!tree->root)
    {
        return;
    }
    RemoveNodeBTree(tree->root, k);

    if (tree->root->n==0)
    {
        NodeBTree *tmp = tree->root;
        if (tree->root->leaf)
            tree->root = NULL;
        else
            tree->root = tree->root->child[0];
    }
    return;
}

