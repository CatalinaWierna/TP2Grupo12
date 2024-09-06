#include "scanner.h"

FILE* archivo;

int main()
{
    archivo = fopen("../TP2/output/entrada.txt", "r");

    if (archivo == NULL){
        printf("Contenido vacio en el archivo.\n");
        fclose(archivo);
        return 1;
    }
    else {
        scanear (archivo);
    }

    fclose(archivo);
    return 0;
}



