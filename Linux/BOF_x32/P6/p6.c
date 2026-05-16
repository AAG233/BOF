#include<stdio.h>
#include<string.h>

int Funcion1(char *nombre){
	char buffer[5];
	printf("Dirección de buffer: 0x%x\n", buffer);

	strcpy(buffer, nombre);
	printf("Bienvenido al sistema: %s\n", buffer);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc<2){
		printf("Uso: %s <nombre>\n", argv[0]);
		return 0;
	}
	Funcion1(argv[1]);
	return 0;
}

