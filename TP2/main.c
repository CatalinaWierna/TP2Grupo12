#include "scanner.h"

FILE* archivo;

int main()
{
    archivo = fopen("../TP2/output/entrada.txt", "r");
    char* token = NULL;

    token = obtenerToken(); 
    // do{
    //    token = obtenerToken();
    // } while (token != "FDT");
    // Se usa a futuro

    fclose(archivo);
    return 0;
}
