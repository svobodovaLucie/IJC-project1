// bitset.c
// Řešení IJC-DU1, příklad a), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Soubor obsahuje deklarace inline funkci pro praci s bitovym polem

#include "bitset.h"

/* Nastaví zadaný bit v poli na hodnotu zadanou výrazem */
extern void bitset_setbit (bitset_t jmeno_pole, bitset_index_t index, char vyraz);

/* Získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
extern char bitset_getbit (bitset_t jmeno_pole, bitset_index_t index);
    
/* Vrátí deklarovanou velikost pole v bitech uloženou na indexu 0 */
extern long unsigned bitset_size (bitset_t jmeno_pole);