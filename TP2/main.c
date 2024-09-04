#include "scanner.h"

FILE* archivo;

int main()
{
    archivo = fopen("../TP2/output/entrada.txt", "r");
    char* token = NULL;

    token = obtenerToken(); 
    // do{
    //    token = obtenerToken();
    // } while (token != EOF);  --> Eze: hasta donde lei el "FDT" es el EOF (End Of File) asi que creo que directamente hagamos token != EOF
    // Se usa a futuro

    fclose(archivo);
    return 0;
}
