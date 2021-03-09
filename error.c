#include "error.h"
/*
Tyto funkce mají
   stejné parametry jako printf(); tisknou text "CHYBA: " a potom
   chybové hlášení podle formátu fmt. Vše se tiskne do stderr
   (funkcí vfprintf) a potom pouze error_exit ukončí program voláním
   funkce exit(1).  Použijte definice ze stdarg.h.
*/

void warning_msg(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   fprintf(stderr, "CHYBA: ");
   vfprintf(stderr, fmt, args);

   va_end(args);
}

void error_exit(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   fprintf(stderr, "CHYBA: ");
   vfprintf(stderr, fmt, args);
   
   va_end(args);
   exit(1);
}