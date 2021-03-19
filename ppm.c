// ppm.c
// Řešení IJC-DU1, příklad b), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Definice funkci pro praci se soubory formatu ppm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bitset.h"
#include "ppm.h"

#define MAX_SIZE 8000   // maximalni velikost xsize a ysize
#define LEN_MAX_SIZE 5  // delka MAX_SIZE ulozene jako retezec (s koncovou '\0')
#define COLORS 3        // barevne slozky - R, G, B

/*  ppm_read: načte obsah PPM souboru do touto funkcí dynamicky alokované struktury. 
    Při chybě formátu použije funkci warning_msg a vrátí NULL. */
struct ppm * ppm_read(const char * filename) {
    // nacteni souboru
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        error_exit("CHYBA: steg-decode: Chyba cteni souboru");

    char buffer[LEN_MAX_SIZE] = {0, };
    unsigned width, height;
    
    // format check
    // 1. P6
    if ((fscanf(f, " %s ", buffer) != 1) || strcmp(buffer, "P6"))
        goto error;
    memset(buffer,0,strlen(buffer));
    
    // 2. ulozeni xsize
    if ((fscanf(f, " %s ", buffer) != 1) || (buffer[LEN_MAX_SIZE - 1] != '\0'))
        goto error;
    char *endptr;
    long num = strtol(buffer, &endptr, 10);
    if (endptr[0] != '\0' || num < 0 || num > MAX_SIZE) {
        goto error;
    }
    width = (unsigned int)num;
    memset(buffer,0,strlen(buffer));

    // 3. ulozeni ysize
    if ((fscanf(f, " %s ", buffer) != 1) || (buffer[LEN_MAX_SIZE - 1] != '\0'))
        goto error;
    num = strtol(buffer, &endptr, 10);
    if (endptr[0] != '\0' || num < 0 || num > MAX_SIZE)
        goto error;
    height = (unsigned int)num;
    memset(buffer,0,strlen(buffer));

    // 4. "255"
    if ((fscanf(f, " %s", buffer) != 1) || strcmp(buffer, "255"))
        goto error;

    char next_char = fgetc(f);
    if (!isspace(next_char))
        goto error;

    // spravny format osetren - > alokace pameti pro strukturu pic
    struct ppm* pic = calloc(sizeof(struct ppm) + COLORS * width * height, 1);
    if (pic == NULL)
        goto error;
    pic->xsize = width;
    pic->ysize = height;

    // ulozeni binarnich dat do struktury pic
    int c;
    unsigned long i = 0;
    while ((c = fgetc(f)) != EOF)
        pic->data[i++] = (char)c; 

    fclose(f);
    return pic;

    error:
        warning_msg("CHYBA: ppm_read: Chybny format souboru");
        fclose(f);
        return NULL;
}

/* ppm_free: Uvolní paměť dynamicky alokovanou v ppm_read */
void ppm_free(struct ppm *p) {
    free(p);
}
