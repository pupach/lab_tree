#include "avl_tree.h"

node *FindPlaceInTree(node *CurEl, int val)
{

  if(CurEl == NULL)   return NULL;
  //LOG("FindPlaceInTree val = %d val = %d bool = %d", CurEl->val, val, (val == CurEl->val));
  if(val == CurEl->val)
  {
    return CurEl;
  }
  else if(val >= CurEl->val)
  {
    LOG(" baaaaaaaaaaaaad     ");
    if(CurEl->right == NULL)  return CurEl;
    LOG("right\n");
    return FindPlaceInTree(CurEl->right, val);
  }
  else{
    LOG(" baaaaaaaaaaaaad     ");
    if(CurEl->left == NULL)  return CurEl;
    LOG("left\n");
    return FindPlaceInTree(CurEl->left, val);
  }
}

void SetHigh1(node *head)
{
  if(head == NULL)  return;
  node *left_tree = head->left;
  node *right_tree = head->right;
  if(right_tree == NULL)
  {
    if(left_tree != NULL) {
      head->deep = left_tree->deep + 1;
      head->delta = left_tree->deep;
    }
    else {
      head->deep = 1;
      head->delta = 0;
    }
  }
  else if(left_tree == NULL) {
    head->deep = right_tree->deep + 1;
    head->delta = -right_tree->deep;
  }
  else
  {
    head->deep = MAX(left_tree->deep, right_tree->deep) + 1;
    head->delta = left_tree->deep - right_tree->deep;
  }
}

void SetHigh(node *head)
{
  if(head == NULL) return;
  node *prev;

  SetHigh1(head);

  prev = head->prev;
  while(prev!= NULL)
  {
    SetHigh1(prev);
    prev = prev->prev;
  }
}

void LeftBigRotate(node *head) {
  rotate_right(head->left);

  rotate_left(head);
}

void RightBigRotate(node *head) {
  rotate_left(head->right);

  rotate_right(head);
}

node *UpdateDeepTree(node *ElemToUpd)
{
  if(ElemToUpd == NULL) return NULL;
  SetHigh(ElemToUpd);
  node *to_rotate, *may, *k;
  int deep_may, deep_k;

  if(ElemToUpd->delta > 1)
  {
    to_rotate = ElemToUpd->left;
    if(to_rotate!= NULL)
    {
      may = to_rotate->right;
      k   = to_rotate->left;

      if(may == NULL) deep_may = 0;
      else            deep_may = may->deep;

      if(k == NULL) deep_k = 0;
      else            deep_k = k->deep;

      LOG("BID_ROT_CHECK %d %d \n", deep_may, deep_k);

      if(deep_may > deep_k)
      {
        LeftBigRotate(ElemToUpd);
        if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
        else  return ElemToUpd;
      }
    }
    rotate_left(ElemToUpd);
    SetHigh(ElemToUpd);
  }
  else if(ElemToUpd->delta < -1)
  {
    to_rotate = ElemToUpd->right;
    if(to_rotate!= NULL)
    {
      may = to_rotate->right;
      k   = to_rotate->left;

      if(may == NULL) deep_may = 0;
      else            deep_may = may->deep;

      if(k == NULL) deep_k = 0;
      else            deep_k = k->deep;

      LOG("BID_ROT_CHECK %d %d \n", deep_may, deep_k);

      if(deep_may < deep_k)
      {
        RightBigRotate(ElemToUpd);
        if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
        else  return ElemToUpd;
      }
    }
    rotate_right(ElemToUpd);
    SetHigh(ElemToUpd);
  }
  LOG("UpdateDeepTree cur_el = %d deep = %d delta_deep = %d]\n", ElemToUpd->val, ElemToUpd->deep, ElemToUpd->delta);

  if(ElemToUpd->prev != NULL)   return UpdateDeepTree(ElemToUpd->prev);
  else  return ElemToUpd;
}

void InsertAvl(AvlTree *tree, node *ElemToIns)
{
  if(tree->head == NULL)
  {
    tree->head = ElemToIns;
    ElemToIns->deep = 1;
    UpdateDeepTree(tree->head);
    return;
  }
  node *ptr = FindPlaceInTree(tree->head, ElemToIns->val);

  if(ElemToIns->val == ptr->val)
  {
    UpdateDeepTree(tree->head);
    return;
  }
  else if(ElemToIns->val >= ptr->val)
  {
    ptr->right = ElemToIns;

  }
  else
  {
    ptr->left = ElemToIns;
  }
  ElemToIns->prev = ptr;
  ElemToIns->deep = 1;
  tree->head = UpdateDeepTree(ElemToIns->prev);
  node  *prev = ElemToIns->prev;
}


int FindMinElAvl(AvlTree *tree, int ogr)
{
  int res = -1;
  node *cur_el = tree->head;
  while(cur_el != NULL)
  {
    if(cur_el->val >= ogr)
    {
      res = cur_el->val;
      cur_el = cur_el->left;
    }
    else
    {
      cur_el = cur_el->right;
    }
  }
  return res;
}

/*
void RemoveAvl(AvlTree *avl, int key)
{
  node *key_node = FindPlaceInTree(avl->head, key);
  if ((key_node == NULL) || (key_node->val != key)) return;

  node *left_child = key_node->left;
  node *right_child = key_node->right;


  if (right_child == NULL)
  {
    if(left_child == NULL)
    {
      if(parent_get(key_node) == NULL) avl->head = NULL;
      else if(parent_get(key_node)->left == key_node)   parent_get(key_node)->left = NULL;
      else  parent_get(key_node)->right = NULL;

      avl->head = UpdateDeepTree(parent_get(key_node));
      key_node->prev = NULL;
    }

    else
    {
      node *replace_node_key = FindPlaceInTree(left_child, key_node->val);

      node *to_update_deep = parent_get(replace_node_key);
      if(to_update_deep == key_node) to_update_deep = left_child;

      if(parent_get(replace_node_key)->left == replace_node_key)   parent_get(replace_node_key)->left = NULL;
      else  parent_get(replace_node_key)->right = NULL;


      replace_node_key->prev = parent_get(key_node);

      if(parent_get(key_node) != NULL) {
        if (parent_get(key_node)->left == key_node) parent_get(key_node)->left = replace_node_key;
        else parent_get(key_node)->right = replace_node_key;
      }

      if(key_node->left != replace_node_key) replace_node_key->left = key_node->left;
      else    replace_node_key->left = NULL;

      replace_node_key->right = key_node->right;

      if(left_child != replace_node_key) parent_set(left_child, replace_node_key);
      parent_set(right_child, replace_node_key);

      avl->head = UpdateDeepTree(to_update_deep);
      key_node->prev = NULL;
    }
  }

  else
  {
    node *replace_node_key = FindPlaceInTree(right_child, key);

    node *to_update_deep = parent_get(replace_node_key);
    if(to_update_deep == key_node) to_update_deep = right_child;

    if(parent_get(replace_node_key)->left == replace_node_key)   parent_get(replace_node_key)->left = NULL;
    else  parent_get(replace_node_key)->right = NULL;


    replace_node_key->prev = parent_get(key_node);

    if(parent_get(key_node) != NULL) {
      if (parent_get(key_node)->left == key_node) parent_get(key_node)->left = replace_node_key;
      else parent_get(key_node)->right = replace_node_key;
    }

    if(key_node->right != replace_node_key) replace_node_key->right = key_node->right;
    else    replace_node_key->right = NULL;

    replace_node_key->left = key_node->left;


    if(right_child != replace_node_key) parent_set(right_child, replace_node_key);
    parent_set(left_child, replace_node_key);

    avl->head = UpdateDeepTree(to_update_deep);
    key_node->prev = NULL;
  }
}
*/

#define HEIGHT(subtree) \
    ((subtree) ? (subtree)->deep : 0)

#define max(a, b) \
    ((a) > (b) ? (a) : (b))


static int avlGetDiff(node *avl)
{
  if (!avl) return 0;
  node *left = avl->left;
  node *right = avl->right;
  if(!left && !right) return 0;
  if(!left) return -right->deep;
  if(!right) return left->deep;

  return left->deep - right->deep;
}

static void avlUpdateHeight(node *avl)
{
  if (!avl) return;

  node *left = avl->left;
  node *right = avl->right;
  if(!left && !right) avl->deep = 1;
  else if(!left)  avl->deep = right->deep;
  else if(!right) avl->deep = left->deep;
  else  avl->deep = max(left->deep, right->deep);
}

static node *avlRotateLL(node *avl)
{
  if (!avl) return NULL;

  node *parent = avl->prev;
  node *RChild = avl->right;

  avl->right = RChild->left;
  if (avl->right) parent_set(RChild->right, avl);

  RChild->left         = avl;
  parent_set(RChild->left, RChild);

  RChild->prev = parent;

  avlUpdateHeight(avl);
  avlUpdateHeight(RChild);

  return RChild;
}

static node *avlRotateRR(node *avl)
{
  if (!avl) return NULL;

  node *parent = avl->prev;
  node *LChild = avl->left;

  avl->left = LChild->right;
  if (avl->left) parent_set(LChild->left, avl);

  LChild->right         = avl;
  parent_set(LChild->right, LChild);

  LChild->prev = parent;

  avlUpdateHeight(avl);
  avlUpdateHeight(LChild);

  return LChild;
}

static node *avlRotateLR(node *avl)
{
  avl->left = avlRotateLL(avl->left);
  parent_set(avl->left, avl);
  avl       = avlRotateRR(avl);

  return avl;
}

static node *avlRotateRL(node *avl)
{
  avl->right = avlRotateRR(avl->right);
  parent_set(avl->right, avl);
  avl        = avlRotateLL(avl);

  return avl;
}

static node *avlRebalance(node *avl)
{
  if (!avl) return NULL;

  int diffNode  = avlGetDiff(avl);
  if (diffNode != -2 && diffNode != 2) return avl;

  int diffLeft  = avlGetDiff(avl->left);
  int diffRight = avlGetDiff(avl->right);

  if (diffNode == -2)
  {
    if      (diffRight ==  1)                      avl = avlRotateRL(avl);
    else /* (diffRight == -1 || diffRight == 0) */ avl = avlRotateLL(avl);
  }
  else // (diffNode == 2)
  {
    if      (diffLeft  == -1)                      avl = avlRotateLR(avl);
    else /* (diffLeft  ==  1 || diffRight == 0) */ avl = avlRotateRR(avl);
  }

  return avl;
}



node *AvlRemove(node *avl, int key)
{
  node *parent  = NULL;
  if(avl == NULL) return avl;

  node *keyNode = FindPlaceInTree(avl, key);
  if (keyNode->val != key) return avl;

  parent = keyNode->prev;
  node *LChild = keyNode->left;
  node *RChild = keyNode->right;

  if (!RChild)
  {
    if      (!parent)                  avl     = LChild;
    else if ( parent->left == keyNode) parent->left  = LChild;
    else                               parent->right = LChild;

    if (LChild) LChild->prev = parent;
  }

  else
  {
    node *change   = FindPlaceInTree(RChild, key);
    int changedKey = change->val;

    AvlRemove(RChild, changedKey);
    keyNode->val = changedKey;

    parent = keyNode;
  }

  node *cur = parent;
  avlUpdateHeight(cur);
  while (avlGetDiff(cur) != 0)
  {
    cur = avlRebalance(cur);
    if (!cur->prev) return cur;

    node *curParent = cur->prev;
    if (cur->val < curParent->val) curParent->left  = cur;
    else                           curParent->right = cur;

    cur = cur->prev;
    avlUpdateHeight(cur);
  }
  return avl;
}
