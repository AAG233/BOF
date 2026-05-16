#include<stdio.h>
#include<string.h>
#define maximo 1500
#define tamanio_cadena 10
#define archivo "entrada.txt"

int BuscarPalabra(char *argumento){
        int ban=0, contador=0;
        char cadena[tamanio_cadena];
        char linea[maximo];
        char *comparacion;

        printf("Dirección de cadena: 0x%x\n", cadena);
        strcpy(cadena, argumento);
        printf("Archivo: %s\n", archivo);
        printf("Buscar palabra: %s\n", cadena);

        FILE *fp = fopen (archivo, "r");
        if (!fp){
                fprintf (stderr, "Error al abrir el archivo: '%s'.\n", archivo);
                return -1;
        }

        while ((fgets(linea, maximo, fp))!= NULL){
                comparacion = strstr(linea,cadena);
                if(comparacion!=NULL){
                        ban = contador;
                        break;
                }
                contador++;
        }
        return ban;
}

int main(int argc, char *argv[]){
        int i;
        if (argc < 2)
                {printf("Uso: %s Cadena_A_Buscar\n", argv[0]); return 0;}

        printf("Presiona una tecla para continuar\n");
	int ch = getchar();
        i = BuscarPalabra(argv[1]);
        if(i==0){
                printf("Cadena no encontrada\n");
        }
        else{
                printf("Cadena encontrada en la línea %i\n", i);
        }
        return 0;
}
