// error.h
// Řešení IJC-DU1, příklad b), 12.3.2021
// Autor: Lucie Svobodova, xsvobo1x, FIT
// Přeloženo: gcc 9.3.0
// Hlavickovy soubor s deklaraci funkci volanych pri chybe

#ifndef _ERROR_H
#define _ERROR_H

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif