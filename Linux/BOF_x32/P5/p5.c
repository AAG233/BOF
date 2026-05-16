#include<stdio.h>
#include<string.h>

int Funcion1(char *cadena){
        char buffer[100];
        strcpy(buffer, cadena);
        return 1;
}

int main(int argc, char **argv[]){
        char cadena[300];
        FILE *ArchivoMalicioso;

        ArchivoMalicioso = fopen("entrada.txt", "r");
        fread(cadena, sizeof(char), 300, ArchivoMalicioso);
        Funcion1(cadena);

        printf("El programa regresó adecuadamente\n");
        return 0;
}
