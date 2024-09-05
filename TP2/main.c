#include "scanner.h"

FILE* archivo;

int main()
{
    archivo = fopen("../TP2/output/entrada.txt", "r");
    char* token = NULL;

    if (archivo == NULL){
        printf("Contenido vacio en el archivo.\n");
        fclose(archivo);
        return 1;
    }

    token = obtenerToken(); 
    do{
        token = obtenerToken();
    } while (token != EOF);


    fclose(archivo);
    return 0;
}



