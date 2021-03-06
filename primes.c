#include <time.h>
#include "bitset.h"
#include "eratosthenes.c"

#define N 200000000

int main(void) {
  clock_t start = clock();
  bitset_alloc(array, N);
  //bitset_create(array, N);
  Eratosthenes(array);

  char sum = 0;
  bitset_index_t i = N - 1;


  while (sum < 10) {
    if (!bitset_getbit(array, i)) {
      printf("%lu\n", i);
      sum++;
    }
    i--;
  }

  fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

  bitset_free(array);
  return 0;
}
