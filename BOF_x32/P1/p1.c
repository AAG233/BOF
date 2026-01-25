// #/usr/sbin/sysctl -w kernel.randomize_va_space=0
#include<stdio.h>

int main(){
	volatile int bandera;
	char buffer1[100], buffer2[100];

	printf("Direccion de buffer1: 0x%x\n", buffer1);
	printf("Direccion de buffer2: 0x%x\n", buffer2);

	bandera = 0;
	scanf("%s", buffer2);
	scanf("%s", buffer1);
	
	if(bandera !=0 )
		printf("La variable bandera ha sido alterada\n");	
	else
		printf("La variable bandera no ha sido alterada\n");	

	printf("Valor final de bandera = %i\n", bandera);
		
	return 0;
}
