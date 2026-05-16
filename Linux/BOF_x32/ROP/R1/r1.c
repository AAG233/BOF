#include<stdio.h>
#include<string.h>

void Funcion2(char a[10], int b){
	printf("Bienvenido a la Función 2\n");
	printf("%s, %i\n", a, b);
	char c[10];
	int d;

	memset(c, 'C', sizeof(c)); 
	d = 25700;
	return;
}

void Funcion1(){
	printf("Bienvenido a la Función 1\n");
	Funcion2("AAAAABBBB", 65535);
	return;
}


int main(){
	Funcion1();
	return 0;
}
