#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAMANIO 700

void Funcion_A(){
	printf("Bienvenido a la Función A\n");
	return;
}

void Funcion_B(){
	printf("Bienvenido a la Función B\n");
	return;
}

int Funcion_C(char *contenido, int tamanio){
        printf("Tamaño original de la cadena %i\n", tamanio);
        char buffer[233];
	char *reg_ebp_frame;
        printf("Dirección de buffer: 0x%x\n", buffer);

	asm("movl %%ebp, %0" : "=r" (reg_ebp_frame));
	printf("Valor del registro ebp:\t 0x%x\n", reg_ebp_frame);

	memcpy(buffer, contenido, tamanio);
	return 0;
}

void Funcion_D(int x){
	printf("Valor del argumento 0x%.8x\n", x);
	return;
}

int main(int argc, char *argv[]){
        if(argc<2){
                printf("Uso: %s TamañoDeCaracteresALeer\n", argv[0]);
                return 0;
        }

	char *contenido = (char *)malloc(TAMANIO * sizeof(char));
	FILE *archivo = fopen("entrada.txt", "rb");

	int i=0;
	while (i < atoi(argv[1])){
		int ch = fgetc(archivo);
		if (ch == EOF){
			if (feof(archivo)){
				printf("Se alcanzó el fin del archivo.\n");
			}else{
				perror("Error al leer el archivo");
			}
			break;
		}
		contenido[i] = (char)ch; i++;
	}
	
	fclose(archivo);
	printf("Contenido del archivo:\n%s\n", contenido);

        Funcion_C(contenido, i);
	free(contenido);
        return 0;
}

