// steg-decode.c
// Řešení IJC-DU1, příklad b), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Program nacte obrazek ve formatu ppm a vypise tajnou zpravu

#include <limits.h>
#include <ctype.h>
#include <stdio.h>
#include "error.h"
#include "ppm.h"
#include "primes.h"

#define PRIME_TO_START 23   // prvocislo, od ktereho zjistujeme tajnou zpravu
#define COLORS 3            // barevne slozky - R, G, B

int main (int argc, char *argv[]) {

    // kontrola poctu argumentu
    if (argc != 2)
        error_exit("steg-decode: Chybny pocet zadanych argumentu");
    
    // nacteni obrazovych dat ze souboru do struktury pic
    const char *filename = argv[argc - 1];
    struct ppm *pic = ppm_read(filename);
    if (pic == NULL) {
        error_exit("steg-decode: Chyba nacteni obrazku");
    }

    // alokace bitoveho pole pro zjisteni prvocisel pomoci eratostenova sita
    unsigned long pic_size = COLORS * pic->xsize * pic->ysize;
    bitset_alloc(bitset_array, pic_size);    
    Eratosthenes(bitset_array);
    
    //vypis tajne zpravy na stdout
    char secret_char = '\0';
    unsigned i_secret = 0;
    for (unsigned long i = PRIME_TO_START; i < bitset_size(bitset_array); i++) {
        if (!bitset_getbit(bitset_array, i)) {
            secret_char |= (pic->data[i] & 1) << i_secret;
            i_secret++;
        }
        if (i_secret == CHAR_BIT) {
            i_secret = 0;
            if (secret_char == '\0') {
		fputc('\n', stdout);
                break;
	    }
            fputc(secret_char, stdout);
            secret_char = '\0';
        }
    }
    if (secret_char != '\0')
        error_exit("steg-decode: Zprava neni korektne ukoncena (musi koncit znakem '\0')");

    // uvolneni alokovane pameti
    bitset_free(bitset_array);
    ppm_free(pic);

    return 0;
}
