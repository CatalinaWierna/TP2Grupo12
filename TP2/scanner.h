#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <ctype.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


char* asignacionDeMensaje(const char* mensaje);
void scanear(FILE* archivo);
bool esAsignacion(char* bufferlexema);

#endif //SCANNER_H_INCLUDED