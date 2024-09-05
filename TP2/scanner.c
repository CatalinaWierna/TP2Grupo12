#include "scanner.h"
bool nuevoLexema = true;
int estadoAcumulado; //El estadoAcumulado nos da la fila que nos interesa, si es mayor a 100 sabemos que tenemos que arrancar con un nuevo lexema e iniciar el acumulado en 0



enum EstadosPrincipales {
    INICIO = 0,
    INTERMEDIO = 1,
    ACEPTOR = 100,
    ERROR = 200,
};

struct AtributosCaracter {
    int estado;
    char caracter;
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

struct AtributosCaracter iniciarAtributos(char c){
    struct AtributosCaracter attrCaracter;
    attrCaracter.caracter = c;
    if (nuevoLexema){
        attrCaracter.estado = 0;
    }
    else {
        attrCaracter.estado = estadoAcumulado;
    }
    return attrCaracter;
}

int obtenerFila (){
    if(nuevoLexema){
        return 0;
    }
    else{
        return estadoAcumulado;
    }
}