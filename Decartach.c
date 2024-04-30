#include "Decartach.h"

void SetHigh1Decartch(ElemTree *head)
{
  if(head == NULL)  return;
  ElemTree *left_tree = head->left;
  ElemTree *right_tree = head->right;
  if((right_tree == NULL) && (left_tree == NULL)) head->size = 1;
  else if(left_tree == NULL)                      head->size = right_tree->size + 1;
  else if(right_tree == NULL)                     head->size = left_tree->size + 1;
  else                                            head->size = left_tree->size + right_tree->size + 1;
}

void SetHighDecartch(ElemTree *head)
{
  deep++;
  if(deep == 1000000)  exit(-1);
  if(head == NULL) return;

  SetHighDecartch(head->left);
  SetHighDecartch(head->right);
  SetHigh1Decartch(head);
}

SlicersTree SliceDecart(ElemTree *head, int val_to_slice)
{
  deep++;
  if(deep == 1000000)  exit(-1);

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

ElemTree *MergeDecart(ElemTree *min, ElemTree *max)
{
  deep++;
  if(deep == 1000000)  exit(-1);

  if((min == NULL) && (max == NULL))  return NULL;
  else if(min == NULL)                return max;
  else if(max == NULL)                return min;
  ElemTree *head, *another;
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


ElemTree *InsertDecart(ElemTree *tree, ElemTree * val)
{
  SlicersTree res = SliceDecart(tree, val->val);
  ElemTree *new_min = MergeDecart(res.min, val);
  tree = MergeDecart(new_min, res.max);
  return tree;
}

ElemTree *DeleteDecart(ElemTree *tree, int val)
{
  SlicersTree res = SliceDecart(tree, val);
  SlicersTree res_new = SliceDecart(res.max, val + 1);
  tree = MergeDecart(res.min, res_new.max );
  return tree;
}

ElemTree *KnumberStatistic(ElemTree *tree, int k)
{
  if(tree == NULL)  return NULL;

  LOG("KnumberStatistic k = %d tree_val = %d tree_size = %d\n", k, tree->val, tree->size);
  ElemTree *left, *right;
  left = tree->left;
  right = tree->right;
  if((left != NULL) && (left->size >= (k + 1)))
  {
    return KnumberStatistic(left, k);
  }
  else if((left != NULL) && (left->size + 1) == (k + 1))
  {
    return tree;
  }
  else if((left == NULL) && ((tree->size - 1) == k))
  {
    return tree;
  }
  else if((left == NULL) && (k == 0)) return tree;
  else
  {
    int left_size;
    if(left == NULL)  left_size = 0;
    else    left_size = left->size;
    return KnumberStatistic(right, k - (left_size + 1));
  }
}

bool ExistsDecart(ElemTree *cur_el, int ogr)
{
  int res = POISON_VAL;
  int cnt = 0;
  while(cur_el != NULL)
  {
    cnt++;
    if(cnt == 100000)  exit(-1);
    if(cur_el->val == ogr)
    {
      return true;
    }
    else if(cur_el->val < ogr)
    {
      cur_el = cur_el->right;
    }
    else if(cur_el->val > ogr)
    {
      cur_el = cur_el->left;
    }
  }
  return false;
}

ElemTree *RemoveDecart(ElemTree *head, int elem)
{
  SlicersTree res = SliceDecart(head, elem);

  if(res.max == NULL) return res.min;

  if(res.max->val == elem)  return head;
  else
  {
    SetParent(res.max->left, NULL);
    SetParent(res.max->right, NULL);
    res.max = MergeDecart(res.max->left, res.max->right);

    return MergeDecart(res.max, res.min);
  }

}



