#include "scanner.h"

int estadoAcumulado; //El estadoAcumulado nos da la fila que nos interesa, si es mayor a 100 sabemos que tenemos que arrancar con un nuevo lexema e iniciar el acumulado en 0



enum EstadosPrincipales {
    INICIO = 0,
    INTERMEDIO = 1,
    ACEPTOR = 100,
    ERROR = 200,
};

int tablaTransicion [7] [8] = {
    {0,1,2,3,4,5,6,200},
    {100,1,1,100,100,100,100,200},
    {101,200,2,101,101,101,101,200},
    {102,102,102,102,102,102,102,200},
    {103,103,103,103,103,103,103,200},
    {201,201,201,201,201,201,104,200},
    {202,202,202,202,202,202,202,202},
};
bool esOperando(char caracter){
    return (caracter == '+' || caracter == '-' || caracter == '/' || caracter == '%' || caracter == '*');
}
bool esPuntuacion(char caracter){
    return (caracter == ')' || caracter == '(' || caracter == ',' || caracter == ';');
}

int obtenerColumna (char caracter){
    if(isspace(caracter)){
        return 0;
    }
    else if(isalpha(caracter)){
        return 1;
    }
    else if(isdigit(caracter)){
        return 2;
    }
    else if(esOperando(caracter)){
        return 3;
    }
    else if(esPuntuacion(caracter)){
        return 4;
    }
    else if (caracter==':'){
        return 5;
    }
    else if(caracter=='='){
        return 6;
    }
    else{
        return 7;
    }

}




int obtenerEstado (char caracter){
    int columna = obtenerColumna(caracter);
    return tablaTransicion[columna][estadoAcumulado];

}

char* tokenDeError (char* bufferLexema){
    char* msjError = (char*) malloc(200);
    if (strcmp("=",bufferLexema)){
        strcpy(msjError, "Error de asignacion =");
    }
    else if(strcmp(":",bufferLexema)){
        strcpy(msjError, "Error de asignacion :");
    }
    else {
        strcpy(msjError, "Error comun");
    }
    return msjError;
}

char* tokenAceptor (char* bufferLexema){
    char* msjAceptor = (char*) malloc(200);
    if(strcmp(";",bufferLexema)){
        strcpy(msjAceptor, "Punto y Coma");
    }
    else if(strcmp("(",bufferLexema)){
        strcpy(msjAceptor, "Parentesis que abre");
    }
    else if(strcmp(")",bufferLexema)){
        strcpy(msjAceptor, "Parentesis que cierra");
    }
    else if(strcmp(",",bufferLexema)){
        strcpy(msjAceptor, "Coma");
    }
    else if(strcmp(":=",bufferLexema)){
        strcpy(msjAceptor, "Asignacion");
    }
    else if(strcmp("*",bufferLexema)){
        strcpy(msjAceptor, "Multiplicacion");
    }
    else if(strcmp("-",bufferLexema)){
        strcpy(msjAceptor, "Menos");
    }
    else if(strcmp("+",bufferLexema)){
        strcpy(msjAceptor, "Mas");
    }
    else if(strcmp("/",bufferLexema)){
        strcpy(msjAceptor, "Division");
    }
    else if(strcmp("%",bufferLexema)){
        strcpy(msjAceptor, "Resto");
    }
    else{
        strcpy(msjAceptor, "Identificador");
    }

}

void scanear(FILE* archivo){
    
    static char bufferlexema[200];
    int caracteresError;
    int caracterAscii;
    int indicebuffer = 0;

    while ((caracterAscii = fgetc(archivo)) != EOF) {
    putchar(caracterAscii);

    estadoAcumulado = obtenerEstado ((char)caracterAscii);

    if (estadoAcumulado >= ERROR) {
        while ((caracteresError = getc(archivo)) != EOF){//Tuve que agregar este bucle, ya que si hay un caracter que tira error, hay que leer toda la cadena hasta que finaliza
            if(isspace((char)caracteresError)){
                break;
            }
            else{
                bufferlexema[indicebuffer] = caracteresError;
                bufferlexema[indicebuffer+1]='\0';
                indicebuffer++;
            }
        }
        char* error = tokenDeError (bufferlexema);
        printf("%s   %s\n",error,bufferlexema);
        free(error);
        estadoAcumulado = INICIO;
        indicebuffer = 0;
        memset(bufferlexema,'\0',200); //Esto pone en cero al buffer  
    } 
    else if (estadoAcumulado >= ACEPTOR) {
        if(!isspace(caracterAscii)){//Tengo que chequear que el siguiente caracter no sea parte de otro lexema, si lo es lo vuelvo a dejar en el flujo Ej: 4+5
            ungetc(caracterAscii,archivo);
        }
        char* aceptor = tokenAceptor(bufferlexema);
        printf("%s   %s\n",aceptor,bufferlexema);
        free(aceptor);
        estadoAcumulado = INICIO;
        indicebuffer = 0;
        memset(bufferlexema,'\0',200);     
    } 
    else if (estadoAcumulado >= INTERMEDIO) {
        bufferlexema[indicebuffer] = caracterAscii;
        bufferlexema[indicebuffer+1]='\0';
        indicebuffer++;
    }
}

}
