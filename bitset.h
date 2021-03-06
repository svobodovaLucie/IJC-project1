#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
//#include <math.h>

#include "error.h"

#define UL_BITS sizeof(unsigned long) * 8
#define UL_BYTES sizeof(unsigned long)
#define RESERVED 1

// Typ indexu do bitového pole.
typedef unsigned long bitset_index_t;

// Typ bitového pole (pro předávání parametru do funkce odkazem).
typedef unsigned long bitset_t[];


#define bitset_create(array,size)                                 \
      static_assert(size > 0 && size < ULLONG_MAX, "ERROR: Invalid size of array");    \
      unsigned long array[((size)/UL_BITS) + 1 + RESERVED] = {size};\
      array[0] = size

#define bitset_alloc(array,size)                                                                 \
      static_assert(size > 0 && size <= ULLONG_MAX, "CHYBA: Invalid size of array");      \
      unsigned long *array = calloc((size/UL_BITS) + 1 + RESERVED, sizeof(bitset_index_t));                    \
      if(array == NULL) error_exit("bitset_alloc: Chyba alokace paměti");                 \
      array[0] = size

#define bitset_free(array) free(array)

#define bitset_size(array) array[0] 

#define bitset_setbit(array, index, value)                                     \
   if (value) array[(index/UL_BITS) + RESERVED] |= (1UL << (index % UL_BITS)); \
   else array[(index/UL_BITS) + RESERVED] &= ~(1UL << (index % UL_BITS))

#define bitset_getbit(array,index) (array[(index/UL_BITS) + RESERVED] >> (index % UL_BITS)) & 1UL

/*
#define bitset_getbit(array,index) \
      if(index >= bitset_size(array)) error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(array)); \
      (array[(index/UL_BITS) + RESERVED] & (1UL << (index % UL_BITS)));
*/      