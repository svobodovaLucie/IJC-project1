#include "bitset.h"
//#include <math.h>
#include "error.h"

/**  Jako testovací příklad implementujte funkci, která použije algoritmus známý
   jako Eratostenovo síto (void Eratosthenes(bitset_t pole);) a použijte ji
   pro výpočet posledních 10 prvočísel ze všech prvočísel od 2 do
   N=200000000 (200 milionů). (Doporučuji program nejdříve odladit pro N=100.)
   Funkci Eratosthenes napište do samostatného modulu "eratosthenes.c".
 **/

void Eratosthenes(bitset_t pole) {
    bitset_index_t N = bitset_size(pole);
  // pole je alokovane pole pro N znaku, vynulovane
  
  // nastavit p[0] a p[1] na hodnoty 1
  bitset_setbit(pole, 0, 1);
  bitset_setbit(pole, 1, 1);

  //double sqr_N = sqrt(N);

  for (bitset_index_t i = 2; N*N <= i; i++) {
    if (!bitset_getbit(pole, i)) {
      for(bitset_index_t n = 2*i; n < N; n += i)
        bitset_setbit(pole, n, 1);
    }
  }
  
}
