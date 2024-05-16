#include "decart_tree.h"
int deep = 0;

void SetHigh1Decartch(node *head)
{
  if(head == NULL)  return;
  node *left_tree = head->left;
  node *right_tree = head->right;
  if((right_tree == NULL) && (left_tree == NULL)) head->size = 1;
  else if(left_tree == NULL)                      head->size = right_tree->size + 1;
  else if(right_tree == NULL)                     head->size = left_tree->size + 1;
  else                                            head->size = left_tree->size + right_tree->size + 1;
}

void SetHighDecartch(node *head)
{
  deep++;
  //if(deep == 1000000)  exit(-1);
  if(head == NULL) return;

  SetHighDecartch(head->left);
  SetHighDecartch(head->right);
  SetHigh1Decartch(head);
}

SlicersTree SliceDecart(node *head, int val_to_slice)
{
  deep++;

  SlicersTree to_ret = {};
  if(head == NULL)  return to_ret;
  SlicersTree res;
  if(val_to_slice > head->val)
  {
    res = SliceDecart(head->right, val_to_slice);
    head->right = res.min;
    SetHigh1Decartch(head->right);
    SetHigh1Decartch(head);
    if(res.min != NULL) res.min->prev = head ;
    to_ret.min = head;
    to_ret.max = res.max;
    SetHigh1Decartch(res.max);
  }
  else
  {
    res = SliceDecart(head->left, val_to_slice);
    head->left = res.max;
    SetHigh1Decartch(head->left);
    SetHigh1Decartch(head);
    if(res.max != NULL) res.max->prev = head ;
    to_ret.min = res.min;
    to_ret.max = head;
    SetHigh1Decartch(res.min);
  }
  return to_ret;
}

node *MergeDecart(node *min, node *max)
{
  deep++;
  //if(deep == 1000000)  exit(-1);

  if((min == NULL) && (max == NULL))  return NULL;
  else if(min == NULL)                return max;
  else if(max == NULL)                return min;
  node *head, *another;

  if(min->priorety > max->priorety)
  {
    max->left = MergeDecart(min, max->left);
    SetHigh1Decartch(max->left);
    another = max->left;
    if(another != NULL)   another->prev = max;
    SetHigh1Decartch(max);
    return max;
  }
  else
  {
    min->right = MergeDecart(min->right, max);
    SetHigh1Decartch(min->right);
    another = min->right;
    if(another != NULL)   another->prev = min;
    SetHigh1Decartch(min);
    return min;
  }

}


node *InsertDecart(node *tree, node * val)
{
  SlicersTree res = SliceDecart(tree, val->val);
  node *new_min = MergeDecart(res.min, val);
  tree = MergeDecart(new_min, res.max);
  return tree;
}

node *RemoveDecart(node *head, int elem)
{
  SlicersTree res = SliceDecart(head, elem);

  if(res.max == NULL) return res.min;

  if(res.max->val == elem)  return head;
  else
  {
    parent_set(res.max->left, NULL);
    parent_set(res.max->right, NULL);
    res.max = MergeDecart(res.max->left, res.max->right);

    return MergeDecart(res.max, res.min);
  }

}



