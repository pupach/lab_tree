#include <stdio.h>
#include "Avl_tree.h"
#include "Decartach.h"
#include "Splay_tree.h"
#include "RedBlackTree.h"

typedef struct{
    clock_t Insert;
    clock_t Remove;

}TestTimeOne;

typedef struct{
    TestTimeOne Avl;
    TestTimeOne Decart;
    TestTimeOne Splay;
    TestTimeOne RBT;

}TestTimeAll;


TestTimeAll DoOneTest(int size, int max_size)
{
  TestTimeAll ret = {};

  ElemTree *Avl_elems = calloc(size, sizeof(ElemTree));
  ElemTree *Decart_elems = calloc(size, sizeof(ElemTree));
  ElemTree *Splay_elems = calloc(size, sizeof(ElemTree));
  ElemRBT *RBT_elems = calloc(size, sizeof(ElemRBT));

  AvlTree Avl = {};
  ElemTree *Decart = {};
  ElemTree *Splay = {};
  ElemRBT *RBT = {};

  int *data = (int *)calloc(size, sizeof(int));
  int *index = (int *)calloc(size / 2, sizeof(int));

  srand(clock());
  for(int i = 0; i < size; i++)
  {
    data[i] = rand() % max_size;

    Avl_elems[i].val = data[i];
    Decart_elems[i].val = data[i];
    Splay_elems[i].val = data[i];
    RBT_elems[i].val = data[i];
  }
  ret.Avl.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    InsertAvl(&Avl, Avl_elems + i);
  }
  ret.Avl.Insert = clock() - ret.Avl.Insert;

  ret.Decart.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    Decart = InsertDecart(Decart, Decart_elems + i);
  }
  ret.Decart.Insert = clock() - ret.Decart.Insert;

  ret.Splay.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    Splay = InsertSplay(Splay, Splay_elems + i);
  }
  ret.Splay.Insert = clock() - ret.Splay.Insert;

  ret.RBT.Insert = clock();
  for(int i = 0; i < size; i++)
  {
    RBT = InsertRBT(RBT, RBT_elems + i);
  }
  ret.RBT.Insert = clock() - ret.RBT.Insert;

  for(int i = 0; i < (size / 2); i++)
  {
    index[i] = rand() & size;
  }
  ret.RBT.Insert = clock() - ret.RBT.Insert;

  ret.Avl.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    RemoveAvl(&Avl, data[index[i]]);
  }
  ret.Avl.Remove = clock() - ret.Avl.Remove;

  ret.Decart.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    Decart = RemoveDecart(Decart, data[index[i]]);
  }
  ret.Decart.Remove = clock() - ret.Decart.Remove;

  ret.Splay.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    Splay = RemoveSPlay(  Splay, data[index[i]]);
  }
  ret.Splay.Remove = clock() - ret.Splay.Remove;

  ret.RBT.Remove = clock();
  for(int i = 0; i < (size / 2); i++)
  {
    RBT = RemoveRBT(RBT, data[index[i]]);
  }
  ret.RBT.Remove = clock() - ret.RBT.Remove;

  return ret;
}

#define SIZE 10

int main() {
  TestTimeAll time;
  FILE *stream_AVL_insert    = fopen("data/AVL_insert",    "w");
  FILE *stream_decart_insert = fopen("data/decart_insert", "w");
  FILE *stream_splay_insert  = fopen("data/splay_insert",  "w");
  FILE *stream_RBT_insert    = fopen("data/RBT_insert",    "w");
  FILE *stream_AVL_remove    = fopen("data/AVL_remove",    "w");
  FILE *stream_decart_remove = fopen("data/decart_remove", "w");
  FILE *stream_splay_remove  = fopen("data/splay_remove",  "w");
  FILE *stream_RBT_remove    = fopen("data/RBT_remove",    "w");
  double time_insert[SIZE][4] = {};
  double time_remove[SIZE][4] = {};

  for(int i = 1; i < SIZE + 1; i += 1)
  {
    for(int j = 0; j < 5; j++)
    {
      time = DoOneTest(i * 100000, 10000000);

      time_insert[i - 1][0] += (double) time.Avl.Insert / 5 / CLOCKS_PER_SEC;
      time_remove[i - 1][0] += (double) time.Avl.Remove / 5 / CLOCKS_PER_SEC;

      time_insert[i - 1][1] += (double) time.Decart.Insert / 5 / CLOCKS_PER_SEC;
      time_remove[i - 1][1] += (double) time.Decart.Remove / 5 / CLOCKS_PER_SEC;

      time_insert[i - 1][2] += (double) time.Splay.Insert / 5 / CLOCKS_PER_SEC;
      time_remove[i - 1][2] += (double) time.Splay.Remove / 5 / CLOCKS_PER_SEC;

      time_insert[i - 1][3] += (double) time.RBT.Insert / 5 / CLOCKS_PER_SEC;
      time_remove[i - 1][3] += (double) time.RBT.Remove / 5 / CLOCKS_PER_SEC;
    }
  }

  /*
  fprintf(stream_AVL_insert, "%d\n", SIZE);
  fprintf(stream_decart_insert, "%d\n", SIZE);
  fprintf(stream_splay_insert, "%d\n", SIZE);
  fprintf(stream_RBT_insert, "%d\n", SIZE);
  fprintf(stream_AVL_remove, "%d\n", SIZE);
  fprintf(stream_decart_remove, "%d\n", SIZE );
  fprintf(stream_splay_remove, "%d\n", SIZE );
  fprintf(stream_RBT_remove, "%d\n", SIZE );
*/

  for(int i = 0; i < SIZE; i++)
  {
    fprintf(stream_AVL_insert, "%d,%d\n", (100000 * (i + 1)), time_insert[i][0]);
    fprintf(stream_decart_insert, "%d,%d\n", (100000 * (i + 1)), time_insert[i][1]);
    fprintf(stream_splay_insert, "%d,%d\n", (100000 * (i + 1)), time_insert[i][2]);
    fprintf(stream_RBT_insert, "%d,%d\n", (100000 * (i + 1)), time_insert[i][3]);
  }

  for(int i = 0; i < SIZE; i++)
  {
    fprintf(stream_AVL_remove, "%d,%d\n", (100000 * (i + 1) / 2), time_remove[i][0]);
    fprintf(stream_decart_remove, "%d,%d\n", (100000 * (i + 1) / 2), time_remove[i][1]);
    fprintf(stream_splay_remove, "%d,%d\n", (100000 * (i + 1) / 2), time_remove[i][2]);
    fprintf(stream_RBT_remove, "%d,%d\n", (100000 * (i + 1) / 2), time_remove[i][3]);
  }


  return 0;
}
