#ifndef _BITSET_H
#define _BITSET_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

#define UL_BITS (sizeof(unsigned long) * CHAR_BIT) // 64
#define UL_BYTES sizeof(unsigned long) // 8
#define RESERVED 1 // prvni prvek pole je rezervovan pro ulozeni velikosti pole

/* Typ indexu do bitového pole. */
typedef unsigned long bitset_index_t;
/* Typ bitového pole (pro předávání parametru do funkce odkazem). */
typedef long unsigned *bitset_t;

// MAKRA
/* Definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno_pole, velikost) \
    static_assert(velikost > 0 && velikost < ULLONG_MAX, "CHYBA: bitset_create: Chybna velikost pole."); \
    bitset_index_t jmeno_pole[(velikost)/UL_BITS + 1 + RESERVED] = {velikost}

/* Definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
 * vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky. */
#define bitset_alloc(jmeno_pole,velikost)\
    _Static_assert(velikost > 0 && velikost < ULONG_MAX, "CHYBA: bitset_alloc: Chybna velikost pole."); \
    bitset_t jmeno_pole =  calloc(((velikost)/UL_BYTES) + UL_BYTES, 1); \
    if(jmeno_pole == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); \
    jmeno_pole[0] = velikost

/* Uvolní paměť dynamicky (bitset_alloc) alokovaného pole. */
#define bitset_free(jmeno_pole)\
    free(jmeno_pole)



#ifndef USE_INLINE
    /* MAKRA */

    /* Nastaví zadaný bit v poli na hodnotu zadanou výrazem */
    #define bitset_setbit(jmeno_pole, index, vyraz) \
        if(index >= bitset_size(jmeno_pole)) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole));\
        ((vyraz) ? \
        (jmeno_pole[(index/UL_BITS) + RESERVED] |= 1UL << (index % UL_BITS))\
        : (jmeno_pole[(index/UL_BITS) + RESERVED] &= ~(1UL << (index % UL_BITS))))   

    /* Získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
    #define bitset_getbit(jmeno_pole, index) \
        ((index >= bitset_size(jmeno_pole)) ? (error_exit("Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole)),0) \
        :((jmeno_pole[(index/UL_BITS + RESERVED)] >> (index % UL_BITS )) & 1UL))
        

    /* Vrátí deklarovanou velikost pole v bitech uloženou na indexu 0 */
    #define bitset_size(jmeno_pole) \
        jmeno_pole[0]

#else
    /* INLINE FUNKCE */

    /* Vrátí deklarovanou velikost pole v bitech uloženou na indexu 0 */
    inline bitset_index_t bitset_size(bitset_t jmeno_pole) {
        return jmeno_pole[0];
    }

    /* Nastaví zadaný bit v poli na hodnotu zadanou výrazem */
    inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, char vyraz) {
        if (index >= bitset_size(jmeno_pole))
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
        if (vyraz)
            jmeno_pole[(index/UL_BITS) + RESERVED] |= 1UL << (index % UL_BITS);
        else
            jmeno_pole[(index/UL_BITS) + RESERVED] &= ~(1UL << (index % UL_BITS));
    }

    /* Získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
    inline char bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
        if (index >= bitset_size(jmeno_pole))
            error_exit("Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
        return jmeno_pole[(index/UL_BITS + RESERVED)] >> (index % UL_BITS ) & 1UL;
    }
#endif

#endif