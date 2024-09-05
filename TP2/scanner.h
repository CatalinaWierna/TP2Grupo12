#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <ctype.h>
#include <stdbool.h> 
#include <stdio.h>
#include <unistd.h>

extern FILE* archivo;

char* obtenerToken();

#endif //SCANNER_H_INCLUDED