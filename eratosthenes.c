// eratosthenes.c
// Řešení IJC-DU1, příklad a), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Program definuje funkci implementujici metodu hledani prvocisel zvanou eratosthenovo sito

#include <math.h>
#include "primes.h"

/*Implementace funkce pouzivajici algoritmus Eratostenovo síto,
  pouzita pro vypočet posledních 10 prvočísel ze všech prvočísel od 2 do
  N=200000000 (200 milionů). */
void Eratosthenes(bitset_t pole)
{
    // pole je alokovane pole pro N znaku, vynulovane
    bitset_index_t N = bitset_size(pole);

    // nastavit p[0] a p[1] na hodnoty 1
    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    double sqr_N = (unsigned long)ceil(sqrt(N)); // pozor na double! prevest na bitset_index_t

    // cyklus prochazi bitove pole a nastavuje bity, na kterych nejsou prvocisla, na 1
    for(bitset_index_t i = 2; i < sqr_N ; i++) {
        // pokud je dane cislo prvocislo (0), nastavi se na hodnotu 1 vsechny jeho nasobky
        if(!(bitset_getbit(pole, i))) {
            for(bitset_index_t j = 2*i; j < N; j += i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }
}
