#include "scanner.h"

int estadoAcumulado; 



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
    else if (caracter == ':'){
        return 5;
    }
    else if(caracter == '='){
        return 6;
    }
    else{
        return 7;
    }

}

int obtenerEstado (char caracter){
    int columna = obtenerColumna(caracter);
    return tablaTransicion[estadoAcumulado][columna];

}

char* asignacionDeMensaje(const char* mensaje){
    char *mensajeAceptor = (char*) malloc(strlen(mensaje) +1);
    if (mensajeAceptor != NULL){
        strcpy(mensajeAceptor, mensaje);
    }
    return mensajeAceptor;
}

typedef struct{ 
    char* unLexema;
    char* unMensaje;
} mensajeLexema;

mensajeLexema casoErrores[] = {
    {"=", "Error en asignacion por = solo"},
    {":", "Error de asignacion por : solo"}
};

mensajeLexema casoAceptacion[] = {
    {";", "Punto y coma"},
    {"(", "Parentesis que abre"},
    {")", "Parentesis que cierra"},
    {",", "Coma"},
    {":=","Asignacion"},
    {"*", "Multiplicacion"},
    {"-", "Menos"},
    {"+", "Mas"},
    {"/", "Divisor"},
    {"%", "Resto"}
};

char* tokenDeError (char* bufferLexema){
    for (int i = 0; i < 2; i++){ 
        if(strcmp(casoErrores[i].unLexema, bufferLexema)==0){
            return asignacionDeMensaje(casoErrores[i].unMensaje);
        }
    }
    return asignacionDeMensaje("Error Comun"); 
}

char* tokenAceptor(char* bufferLexema){
    for (int i = 0; i<10; i++){ 
        if(strcmp(casoAceptacion[i].unLexema,bufferLexema)==0){
            return asignacionDeMensaje(casoAceptacion[i].unMensaje);
        }
    }

    if(isdigit(bufferLexema[0]))
    {
        return asignacionDeMensaje("Constante");
    }

    return asignacionDeMensaje("Identificador");
}

void scanear(FILE* archivo){
    
    char bufferlexema[200];
    int caracteresError;
    int caracterAscii;
    int indicebuffer = 0;
    estadoAcumulado = 0;

    while ((caracterAscii = getc(archivo)) != EOF) {

        estadoAcumulado = obtenerEstado ((char)caracterAscii);
        

        if (estadoAcumulado >= ERROR) {

            if (!(caracterAscii == '=') && !(caracterAscii == ':') && !(caracterAscii == '\n'))
            {

                
                bufferlexema[indicebuffer] = caracterAscii;
                bufferlexema[indicebuffer+1]='\0';
                indicebuffer++;
            }
            

            while ((caracteresError = getc(archivo)) != EOF){
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
            memset(bufferlexema,'\0',200);  
        } 
        else if (estadoAcumulado >= ACEPTOR) {
            if(caracterAscii == '='){
                bufferlexema[indicebuffer] = caracterAscii;
                bufferlexema[indicebuffer+1]='\0';
            } 

            if(!isspace(caracterAscii) && !esAsignacion(bufferlexema)){
                ungetc(caracterAscii,archivo);
            }
            char* aceptor = tokenAceptor(bufferlexema);
            printf("Se encontro '%s' y es '%s'\n",aceptor,bufferlexema);
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

    char* aceptor = tokenAceptor(bufferlexema);
    printf("Se encontro '%s' y es '%s'\n",aceptor,bufferlexema);
    free(aceptor);
    estadoAcumulado = INICIO;
    
    
    
}

bool esAsignacion( char* bufferlexema)
{
    
    return (strcmp(bufferlexema, ":=") == 0);

}
