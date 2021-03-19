// error.c
// Řešení IJC-DU1, příklad b), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Soubor obsahuje definice funkci volanych pri chybe

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

/* Funkce tiskne text "CHYBA: " a potom chybové hlášení podle formátu fmt. */
void warning_msg(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   fprintf(stderr, "CHYBA: ");
   vfprintf(stderr, fmt, args);

   va_end(args);
}

/* Funkce tiskne text "CHYBA: " a potom chybové hlášení podle formátu fmt,
   ukonci program volanim funkce exit(0). */

void error_exit(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   fprintf(stderr, "CHYBA: ");
   vfprintf(stderr, fmt, args);
   
   va_end(args);
   exit(1);
}