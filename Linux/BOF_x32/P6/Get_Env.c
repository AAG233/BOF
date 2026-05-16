#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	if(argc<2){
		printf("Uso: ./Get_Env.exe NombreVariable\n");
		return 0;
	}
	
	char *shell = (char *)getenv(argv[1]);
	if(shell){
		printf("Valor %s\n", shell);
		printf("Dirección %x\n", (unsigned int)shell);
	}else
		printf("No existe la variable de entorno: %s\n", argv[1]);
	return 0;
}
