#include <stdio.h>
#include <windows.h>

void PermisosVP(){
	char buffer[599];
	printf("Cambio de permisos en el espacio de memoria del stack\n");

	LPVOID bufferAddress = &buffer;
	printf("Dirección del buffer en el stack:\t0x%p\n", bufferAddress);

	//Obtenemos la dirección de la página a la que pertenece la variable buffer
	LPVOID pageAddress = (LPVOID)((DWORD_PTR)bufferAddress & ~(DWORD_PTR)(4095));
	printf("Dirección de la página de memoria:\t0x%p\n", pageAddress);

	DWORD oldProtect;
	printf("ANTES DEL CAMBIO DE PERMISOS\n");
	VirtualProtect(pageAddress, 599, PAGE_EXECUTE_READWRITE, &oldProtect);
	printf("DESPUÉS DEL CAMBIO DE PERMISOS\n");
}
int main(){
	SetConsoleOutputCP(CP_UTF8);
	PermisosVP();
	return 0;
}
