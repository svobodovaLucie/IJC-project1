#include <limits.h>
#include <ctype.h>
#include <stdio.h>

#include "error.h"
#include "ppm.h"
#include "primes.h"

// spusteni: ./steg-decode du1-obrazek.ppm

#define TROJKA 3

int main (int argc, char *argv[]) {

    // kontrola poctu argumentu
    if (argc != 2)
        error_exit("CHYBA: steg-decode: Chybny pocet zadanych argumentu");
    
    const char *filename = argv[argc - 1];
    struct ppm *pic = ppm_read(filename);
    if (pic == NULL) {
        error_exit("steg-decode: Chyba nacteni obrazku");
    }

    unsigned long pic_size = 3 * pic->xsize * pic->ysize;
    bitset_alloc(bitset_array, pic_size);    
    Eratosthenes(bitset_array);
    
    
    char secret_char = '\0';
    unsigned i_secret = 0;

    for (unsigned long i = 23; i < bitset_size(bitset_array); i++) {
        if (!bitset_getbit(bitset_array, i)) {
            secret_char |= (pic->data[i] & 1) << i_secret;
            i_secret++;
        }
        if (i_secret == CHAR_BIT) {
            i_secret = 0;
            if (secret_char == '\0')
                break;
            fputc(secret_char, stdout);
            secret_char = '\0';
        }
    }

    bitset_free(bitset_array);
    ppm_free(pic);

    return 0;
}