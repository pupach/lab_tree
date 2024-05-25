#include <stdio.h>
#include "avl\avl_tree.h"
#include "decart\decart_tree.h"
#include "splay\splay_tree.h"
#include "rb\rb_tree.h"
#include "skip\skip_list.h"
#include "bin\bin_tree.h"
#include "b\b_tree.h"

typedef struct{
  clock_t Insert;
  clock_t Remove;
} TestTimeOne;

typedef struct{
  TestTimeOne Avl;
  TestTimeOne Bin;
  TestTimeOne Decart;
  TestTimeOne Splay;
  TestTimeOne RBT;
  TestTimeOne Skip;
  TestTimeOne Btree;
} TestTimeAll;

TestTimeAll do_test(int size, int max_size)
{
  TestTimeAll ret = {};

  node *Avl_elems = calloc(size, sizeof(node));
  if()
  node *Bin_elems = calloc(size, sizeof(node));
  node *Decart_elems = calloc(size, sizeof(node));
  node *Splay_elems = calloc(size, sizeof(node));
  ElemRBT *RBT_elems = calloc(size, sizeof(ElemRBT));
  NodeBTree    *B_tree = calloc(size * 2, sizeof(NodeBTree));

  AvlTree Avl = {};
  BinTree Bin = {};
  btree b_tree = {};
  b_tree.arr = B_tree;
  List skip = {};
  ListInit(&skip, size * 9);
  node *Decart = NULL;
  node *Splay = NULL;
  ElemRBT *RBT = NULL;

  int *data = (int *)calloc(size, sizeof(int));
  int *index = (int *)calloc(size / 2, sizeof(int));
  int begin_cap = skip.size;

  srand(clock());
  for(int i = 0; i < size; i++)
  {
    data[i] = rand() % max_size;

    Avl_elems[i].val = data[i];
    Bin_elems[i].val = data[i];
    Decart_elems[i].val = data[i];
    Decart_elems[i].priorety = rand();
    Splay_elems[i].val = data[i];
    RBT_elems[i].val = data[i];
    skip.arr[skip.size].key = data[i];
    skip.size++;
  }

  ret.Skip.Insert = clock();
  srand(clock());
  for(int i = 0; i < size; i++)
  {
    Insert(&skip, skip.arr + i + begin_cap);
  }
  ret.Skip.Insert = clock() - ret.Skip.Insert;
  printf("Skip done\n");

  ret.Skip.Remove = clock();
  for(int i = 0; i < size / 2; i++)
  {
    Remove(&skip, data[index[i]]);
  }
  ret.Skip.Remove = clock() - ret.Skip.Remove;
  printf("Skip done\n");

  ret.Avl.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    InsertAvl(&Avl, Avl_elems + i);
  }
  ret.Avl.Insert = clock() - ret.Avl.Insert;
  printf("AVL done\n");

  ret.Btree.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    insert(&b_tree, data[i]);
  }
  ret.Btree.Insert = clock() - ret.Btree.Insert;
  printf("Btree done\n");


  ret.Bin.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    InsertBin(&Bin, Bin_elems + i);
  }
  ret.Bin.Insert = clock() - ret.Bin.Insert;
  printf("Bin done\n");

  ret.Decart.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    Decart = InsertDecart(Decart, Decart_elems + i);
  }
  ret.Decart.Insert = clock() - ret.Decart.Insert;

  printf("Decart done\n");
  ret.Splay.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    LOG("i = %d\n", i);
    Splay = InsertSplay(Splay, Splay_elems + i);
  }
  ret.Splay.Insert = clock() - ret.Splay.Insert;

  printf("Splay done\n");
  ret.RBT.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    ElemRBT *ret = InsertRBT(RBT, RBT_elems + i);
    if(ret != NULL)  RBT = ret;
  }
  ret.RBT.Insert = clock() - ret.RBT.Insert;

  printf("RBT done\n");
  ret.Avl.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    //LOG("Avl.Remove = %d head = %d i = %d\n", data[index[i]], Avl.head->val, i);
    Avl.head = AvlRemove(Avl.head, data[index[i]]);
  }
  ret.Avl.Remove = clock() - ret.Avl.Remove;

  ret.Bin.Remove = clock();
  for(int i = 0; i < size / 2; i++)
  {
    RemoveBin(&Bin, data[index[i]]);
  }
  ret.Bin.Remove = clock() - ret.Bin.Remove;
  printf("Bin done\n");

  printf("Avl done\n");
  ret.Decart.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    Decart = RemoveDecart(Decart, data[index[i]]);
  }
  ret.Decart.Remove = clock() - ret.Decart.Remove;

  printf("Decart done\n");
  ret.Splay.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    Splay = RemoveSPlay(  Splay, data[index[i]]);
  }
  ret.Splay.Remove = clock() - ret.Splay.Remove;

  printf("Splay done\n");
  ret.RBT.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    RBT = RemoveRBT(RBT, data[index[i]]);
  }
  ret.RBT.Remove = clock() - ret.RBT.Remove;

  printf("RBT done\n");

  free(data);
  free(index);
  free(Avl_elems);
  free(Decart_elems);
  free(Splay_elems);
  free(RBT_elems);
  free(B_tree);
  free(Bin_elems);
  return ret;
}

#define AMOUNT_TEST 10
#define COUNT_HASH_TABLE 6
#define AMOUNT_TRY 5



int main() {
  TestTimeAll time;
  double time_insert[AMOUNT_TEST][COUNT_HASH_TABLE] = {};
  double time_remove[AMOUNT_TEST][COUNT_HASH_TABLE] = {};

  FILE *stream_BTree_insert  = fopen("../data/BTree_insert.txt",  "w");
  FILE *stream_Skip_insert   = fopen("../data/skip_insert.txt",   "w");
  FILE *stream_Skip_remove   = fopen("../data/skip_remove.txt",   "w");
  FILE *stream_Bin_insert    = fopen("../data/bin_insert.txt",    "w");
  FILE *stream_Bin_remove    = fopen("../data/bin_remove.txt",    "w");
  FILE *stream_AVL_insert    = fopen("../data/avl_insert.txt",    "w");
  FILE *stream_AVL_remove    = fopen("../data/avl_remove.txt",    "w");
  FILE *stream_decart_insert = fopen("../data/decart_insert.txt", "w");
  FILE *stream_decart_remove = fopen("../data/decart_remove.txt", "w");
  FILE *stream_splay_insert  = fopen("../data/splay_insert.txt",  "w");
  FILE *stream_splay_remove  = fopen("../data/splay_remove.txt",  "w");
  FILE *stream_RBT_insert    = fopen("../data/rb_insert.txt",     "w");
  FILE *stream_RBT_remove    = fopen("../data/rb_remove.txt",     "w");

  for(int i = 1; i < AMOUNT_TEST + 1; i ++)
  {
    for(int j = 0; j < AMOUNT_TRY; j++)
    {
      fprintf(stderr, "i*j = %d\n", 3*i - 3 + j );
      time = do_test(i * 100000, 10000000);

      time_insert[i - 1][0] += (double) time.Avl.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][0] += (double) time.Avl.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][1] += (double) time.Decart.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][1] += (double) time.Decart.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][2] += (double) time.Splay.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][2] += (double) time.Splay.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][3] += (double) time.RBT.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][3] += (double) time.RBT.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][4] += (double) time.Skip.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][4] += (double) time.Skip.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][5] += (double) time.Bin.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;
      time_remove[i - 1][5] += (double) time.Bin.Remove / AMOUNT_TRY / CLOCKS_PER_SEC;

      time_insert[i - 1][6] += (double) time.Btree.Insert / AMOUNT_TRY / CLOCKS_PER_SEC;

    }
  }

  for(int i = 0; i < AMOUNT_TEST; i++)
  {
    fprintf(stream_AVL_insert, "%d,%lf\n",    (100000 * (i + 1)), time_insert[i][0]);
    fprintf(stream_decart_insert, "%d,%lf\n", (100000 * (i + 1)), time_insert[i][1]);
    fprintf(stream_splay_insert, "%d,%lf\n",  (100000 * (i + 1)), time_insert[i][2]);
    fprintf(stream_RBT_insert, "%d,%lf\n",    (100000 * (i + 1)), time_insert[i][3]);
    fprintf(stream_Skip_insert, "%d,%lf\n",   (100000 * (i + 1)), time_insert[i][4]);
    fprintf(stream_Bin_insert, "%d,%lf\n",    (100000 * (i + 1)), time_insert[i][5]);
    fprintf(stream_BTree_insert, "%d,%lf\n",  (100000 * (i + 1)), time_insert[i][6]);
  }

  for(int i = 0; i < AMOUNT_TEST; i++)
  {
    fprintf(stream_AVL_remove, "%d,%lf\n",    (100000 * (i + 1) / 2), time_remove[i][0]);
    fprintf(stream_decart_remove, "%d,%lf\n", (100000 * (i + 1) / 2), time_remove[i][1]);
    fprintf(stream_splay_remove, "%d,%lf\n",  (100000 * (i + 1) / 2), time_remove[i][2]);
    fprintf(stream_RBT_remove, "%d,%lf\n",    (100000 * (i + 1) / 2), time_remove[i][3]);
    fprintf(stream_Skip_remove, "%d,%lf\n",   (100000 * (i + 1) / 2), time_remove[i][4]);
    fprintf(stream_Bin_remove, "%d,%lf\n",    (100000 * (i + 1) / 2), time_remove[i][5]);
  }

  fclose(stream_Skip_insert);
  fclose(stream_Skip_remove);
  fclose(stream_AVL_remove);
  fclose(stream_decart_remove);
  fclose(stream_splay_remove);
  fclose(stream_RBT_remove);
  fclose(stream_AVL_insert);
  fclose(stream_Bin_remove);
  fclose(stream_Bin_insert);
  fclose(stream_decart_insert);
  fclose(stream_splay_insert);
  fclose(stream_RBT_insert);
  fclose(stream_BTree_insert);

  return 0;
}