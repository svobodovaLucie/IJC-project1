// primes.c
// Řešení IJC-DU1, příklad a), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Program vytiskne poslednich 10 prvocisel z 200 milionu cisel

#include <stdio.h>
#include <time.h>
#include "primes.h"
	
#define N 200000000     // zadany pocet cisel do eratostenova sita
#define N_TO_PRINT 10   // zadany pocet prvocisel k vypsani

int main(void) {
    clock_t start = clock();
    
    // alokace lokalniho (statickeho) pole
    bitset_create(pole, N);

    Eratosthenes(pole);
    
    // ulozeni poslednich 10 prvocisel do pomocneho pole
    char counter = 0;
    bitset_index_t arr_to_print[N_TO_PRINT] = {0, };
    for(bitset_index_t i = bitset_size(pole) - 1; i > 0; i--) {
        if(!(bitset_getbit(pole, i))) {
            arr_to_print[N_TO_PRINT - 1 - counter] = i;
            counter++;
        }
        if (counter == N_TO_PRINT)
            break;
    }
    // vypis prvocisel z pomocneho pole
    for (unsigned int i = 0; i < N_TO_PRINT; i++)
        printf("%lu\n", arr_to_print[i]);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
