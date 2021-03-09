#include <stdio.h>
#include <time.h>
#include "primes.h"

#define N 200000000

int main(void) {
    clock_t start = clock();
    
    // alokace lokalniho (statickeho) pole
    // bitset_create(array, N);

    // alokace dynamicky alokovaneho pole
    bitset_alloc(pole, N);

    // volani funkce Eratosthenes
    Eratosthenes(pole);
    
    // vypis poslednich 10 prvocisel z bitoveho pole
    // TODO vzestupne poradi!
    char counter = 0;
    bitset_index_t tmp_pole[10] = {0};
    for(bitset_index_t i = bitset_size(pole) - 1; ; i--) {
        if(!(bitset_getbit(pole, i))) {
            tmp_pole[10 - 1 - counter] = i;
            counter++;
        }
        if (counter == 10)
            break;
    }
        
    for (unsigned int i = 0; i < 10; i++)
        printf("%lu\n", tmp_pole[i]);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    
    bitset_free(pole); 
    return 0;
}
