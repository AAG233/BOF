//C:\MinGW_v9.1.0\mingw64\bin\x86_64-w64-mingw32-gcc.exe -m32 P1_32bits.cpp -lws2_32 -g  -o P1_32bits.exe
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#define TamCli 1800
#define TamSer 1800
#define PUERTO 1010

unsigned char *buffer_global = (unsigned char *)0xffffffff;
unsigned char *reg_ebp = (unsigned char *)0xffffffff;

void FUNCION_0(){
	printf("EXCELENTE: Has logrado ejecutar FUNCION_0\n");
	return;
}

void Copiar_Cadena_En_Buffer(char *Mensaje_Cliente, int bytes){
	char buffer[599];
	printf ( "\nDireccion de inicio del Buffer es \t0x%p \n", &buffer ) ;

	buffer_global = (unsigned char *)buffer;
	__asm__("movl %%ebp, %0" : "=r" (reg_ebp));
	printf("Direccion registro de ebp:\t\t0x%p\n", (void *)reg_ebp);

	memcpy(buffer, Mensaje_Cliente, bytes);
}
int Es_Palindrome(char buffer[], int s, int e){
	if(s == e){return 1;}
	
	if(buffer[s] != buffer[e]){return 0;}

	if(s < e + 1){return Es_Palindrome(buffer, s + 1, e - 1);}

	return 1;
}

int Valida_Cadena(char *Mensaje_Cliente){
	char buffer[1450];
	int ban = 0, n;
	strcpy(buffer, Mensaje_Cliente);
	n = strlen(buffer);
	if(n==0){return 1;}

	ban = Es_Palindrome(buffer, 0, n-1);

	if(ban==0)
		return 0;
	else
		return 1;
}
 
int main(int argc, char* argv[]){
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA wsaData;
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

	printf("Escuchando peticiones por el puerto: %i: \n", PUERTO);

	while (true){
		strcpy(Mensaje_Servidor, "Ingrese una palabra para verificar si es un palindrome: ");

		for(i=0; i<TamCli; i++)
  			Mensaje_Cliente[i] = '\0';

		printf ("Esperando conexiones ... \n");
		cliente_socket = accept(descriptor_socket, (SOCKADDR *)&cliente, &TamanioEstructura);
		
		if(cliente_socket == INVALID_SOCKET){
			printf("Error en accept");
			continue;
		}
 
		printf ("+Conexion aceptada: % s \r \n\n", inet_ntoa (cliente.sin_addr));
    
		send(cliente_socket, Mensaje_Servidor, strlen(Mensaje_Servidor), 0);
		recv(cliente_socket, Mensaje_Cliente, 1450, 0);

		int tamanio=0;
		printf("Cliente: ");
		while(Mensaje_Cliente[tamanio]!=0x0A){
			printf("%c",Mensaje_Cliente[tamanio]);
			tamanio++;
		}printf("\n");
		
		Copiar_Cadena_En_Buffer(Mensaje_Cliente, tamanio);
		Mensaje_Cliente[tamanio]='\0';
		
		ban = Valida_Cadena(Mensaje_Cliente);
		if(ban==1){
			strcpy(Mensaje_Servidor_2, "\nSi, la palabra ingresada es un palindrome\n\n");
			sprintf(Mensaje_Servidor_2 + strlen(Mensaje_Servidor_2), "Direccion inicio de buffer:\t0x%p\n", (void*)buffer_global);
			sprintf(Mensaje_Servidor_2 + strlen(Mensaje_Servidor_2), "Direccion registro de ebp:\t0x%p\n\n", (void*)reg_ebp);
			send(cliente_socket, Mensaje_Servidor_2, strlen(Mensaje_Servidor_2), 0);
		}else{
			strcpy(Mensaje_Servidor, "\nNo, la palabra no es un palindrome\n\n");
			sprintf(Mensaje_Servidor + strlen(Mensaje_Servidor), "Direccion inicio de buffer:\t0x%p\n", (void*)buffer_global);
			sprintf(Mensaje_Servidor + strlen(Mensaje_Servidor), "Direccion registro de ebp:\t0x%p\n\n", (void*)reg_ebp);
			send(cliente_socket, Mensaje_Servidor, strlen(Mensaje_Servidor), 0);
		}
		ban = 1;
		closesocket(cliente_socket);
	}
	
	closesocket(descriptor_socket);
	WSACleanup();
	return 0;
}
