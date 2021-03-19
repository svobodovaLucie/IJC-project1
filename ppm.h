// ppm.h
// Řešení IJC-DU1, příklad b), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Hlavickovy soubor vyuzivany pri praci se soubory formatu ppm

#ifndef _PPM_H
#define _PPM_H

#include "error.h"
#include "bitset.h"

// struktura pro ulozeni dat formatu ppm
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif