//c:\MinGW\bin\g++.exe P1_64bits.cpp -lws2_32 -o P1_64bits.exe
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#define TamCli 1800
#define TamSer 1800
#define PUERTO 1011

unsigned char *buffer_global = (unsigned char *)0xffffffffffffffff;
unsigned char *reg_rbp = (unsigned char *)0xffffffffffffffff;
unsigned char *dir_vp = (unsigned char *)0xffffffffffffffff;

void Instrucciones_Ensamblador() {
    asm("call *%rax\n\t"
        "sub $0x2D8, %rsp\n\t"
        "ret"
       );
}

void FUNCION_0(){
	printf("EXCELENTE: Has logrado ejecutar FUNCIÓN_0\n");
	return;
}

void DireccionVirtualProtect(){
	HMODULE hKernel32 = GetModuleHandle("kernel32.dll");
	FARPROC virtualProtectFunc = GetProcAddress(hKernel32, "VirtualProtect");
	printf("Dirección de la VirtualProtect en kernel32.dll:     \t0x%p\n\n", virtualProtectFunc);
	dir_vp = (unsigned char *)(void *)virtualProtectFunc;
	return;
}
 
void Copiar_Cadena_En_Buffer(char *Mensaje_Cliente, int bytes){
	char buffer[599];
	printf ( "\nDirección de inicio del buffer es \t\t\t0x%p \n", &buffer ) ;
	buffer_global = (unsigned char *)buffer;

	__asm__("movq %%rbp, %0" : "=r" (reg_rbp));
	printf("Valor de RBP:\t\t\t\t\t\t0x%p \n", reg_rbp);

	memcpy(buffer, Mensaje_Cliente, bytes);
}

int Es_Palindromo(char buffer[], int s, int e){
	if(s == e){return 1;}
	
	if(buffer[s] != buffer[e]){return 0;}

	if(s < e + 1){return Es_Palindromo(buffer, s + 1, e - 1);}

	return 1;
}

int Valida_Cadena(char *Mensaje_Cliente, int tamanio){
	char buffer[1300];
	int ban = 0, n;
	strcpy(buffer, Mensaje_Cliente);
	n = tamanio;

	if(n==0){return 1;}

	ban = Es_Palindromo(buffer, 0, n-1);

	if(ban==0)
		return 0;
	else
		return 1;
}
 
int main(int argc, char* argv[]){
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA wsaData; SetConsoleOutputCP(CP_UTF8); 
	if(WSAStartup(sockVersion, &wsaData)!=0)
		return 0;
 
	SOCKET descriptor_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(descriptor_socket == INVALID_SOCKET){
		printf("Error al crear el socket\n");
		return 0;
	}

	sockaddr_in servidor;
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PUERTO);
	servidor.sin_addr.S_un.S_addr = INADDR_ANY; 
	if(bind(descriptor_socket, (LPSOCKADDR)&servidor, sizeof(servidor)) == SOCKET_ERROR){
		printf("Error en bind\n");
		return 0;
	}
 
	if(listen(descriptor_socket, 5) == SOCKET_ERROR){
		printf("Error en listen\n");
		return 0;
	}
 
	SOCKET cliente_socket;
	sockaddr_in cliente;
	int TamanioEstructura = sizeof(cliente), ban=1, i;
	char Mensaje_Cliente[TamCli], Mensaje_Servidor[TamSer], Mensaje_Servidor_2[TamSer];
    	for(i=0; i<TamSer; i++)
		Mensaje_Servidor_2[i] = '\0';
    	for(i=0; i<TamSer; i++)
		Mensaje_Servidor[i] = '\0';
	printf("Escuchando peticiones por el puerto: %i\n", PUERTO);

	while (true){
		strcpy(Mensaje_Servidor, "Ingrese una palabra para verificar si es un palíndromo: ");

		for(i=0; i<TamCli; i++)
  			Mensaje_Cliente[i] = '\0';

		printf ("Esperando conexiones ... \n");
		
		cliente_socket = accept(descriptor_socket, (SOCKADDR *)&cliente, &TamanioEstructura);
		
		if(cliente_socket == INVALID_SOCKET){
			printf("Error en accept");
			continue;
		}
                
		printf ("+Conexión recibida: % s \r \n", inet_ntoa (cliente.sin_addr));
    
		send(cliente_socket, Mensaje_Servidor, strlen(Mensaje_Servidor), 0);
		recv(cliente_socket, Mensaje_Cliente, 1300, 0);

		int tamanio=0;
		printf("Cliente: ");
		while(Mensaje_Cliente[tamanio]!=0x0A){
			printf("%c",Mensaje_Cliente[tamanio]);
			tamanio++;
		}
		printf("\n");

		Copiar_Cadena_En_Buffer(Mensaje_Cliente, tamanio); 
		Mensaje_Cliente[tamanio]='\0';
		DireccionVirtualProtect(); 

		ban = Valida_Cadena(Mensaje_Cliente, tamanio);
		
		if(ban==1){
			strcpy(Mensaje_Servidor_2, "\nSí, la palabra ingresada es un palíndromo\n\n");
			sprintf(Mensaje_Servidor_2 + strlen(Mensaje_Servidor_2), "Dirección inicio de buffer:\t0x%p\n", (void*)buffer_global);
			sprintf(Mensaje_Servidor_2 + strlen(Mensaje_Servidor_2), "Dirección registro de rbp:\t0x%p\n", (void*)reg_rbp);
			sprintf(Mensaje_Servidor_2 + strlen(Mensaje_Servidor_2), "Dirección de VirtualProtect:\t0x%p\n\n", (void*)dir_vp);
			send(cliente_socket, Mensaje_Servidor_2, strlen(Mensaje_Servidor_2), 0);
		}else{
			strcpy(Mensaje_Servidor, "\nNo, la palabra no es un palíndromo\n\n");
			sprintf(Mensaje_Servidor + strlen(Mensaje_Servidor), "Dirección inicio de buffer:\t0x%p\n", (void*)buffer_global);
			sprintf(Mensaje_Servidor + strlen(Mensaje_Servidor), "Dirección registro de rbp:\t0x%p\n", (void*)reg_rbp);
			sprintf(Mensaje_Servidor + strlen(Mensaje_Servidor), "Dirección de VirtualProtect:\t0x%p\n\n", (void*)dir_vp);
			send(cliente_socket, Mensaje_Servidor, strlen(Mensaje_Servidor), 0);
		}
		ban = 1;
		closesocket(cliente_socket);
	}
	closesocket(descriptor_socket);
	WSACleanup();
	return 0;
}

//msfvenom -a x86 --platform windows -p windows/exec cmd=calc.exe -b '\x00\xDA\x0A\x0D' -f c
