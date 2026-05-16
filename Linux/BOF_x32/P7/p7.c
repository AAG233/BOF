//#/usr/sbin/sysctl -w kernel.randomize_va_space=0
//$gcc p7.c -g -z execstack -fno-stack-protector -o p7.exe
//Palíndromo
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#define TamCli 300
#define TamSer 500
#define puerto 9012

unsigned char *buffer_global = (unsigned char *)0xffffffff;
unsigned char *reg_ebp = (unsigned char *)0xffffffff;

void Copiar_Cadena_En_Buffer(char *Mensaje_Cliente){
        char buffer[399];
	printf("Dirección inicio de buffer[]:\t %p\n", (void *)buffer);
	buffer_global = buffer;

	asm("movl %%ebp, %0" : "=r" (reg_ebp));
	printf("Dirección registro de ebp:\t %p\n", (void *)reg_ebp);

        strcpy(buffer, Mensaje_Cliente);
}

int Es_Palindromo(char buffer[], int s, int e){
        if(s == e){return 1;}

        if(buffer[s] != buffer[e]){return 0;}

        if(s < e + 1){return Es_Palindromo(buffer, s + 1, e - 1);}

        return 1;
}

int Valida_Cadena(char *Mensaje_Cliente){
        char buffer[200];
        int ban = 0, n;
        strcpy(buffer, Mensaje_Cliente);
        n = strlen(buffer);
        if(n==0){return 1;}

        ban = Es_Palindromo(buffer, 0, n-1);

        if(ban==0)
                return 0;
        else
                return 1;
}

int main(int argc, char *argv[]){
        int descriptor_socket, cliente_socket, c, i, ban=1;
        struct sockaddr_in servidor, cliente;
        char Mensaje_Cliente[TamCli], Mensaje_Servidor_1[TamSer], Mensaje_Servidor_2[TamSer];
        for(i=0; i<TamSer; i++)
                Mensaje_Servidor_2[i] = '\0';
        for(i=0; i<TamSer; i++)
                Mensaje_Servidor_1[i] = '\0';

        descriptor_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(descriptor_socket == -1)
                printf("El socket no puede ser creado\n");

        servidor.sin_family =  AF_INET;
        servidor.sin_addr.s_addr = INADDR_ANY;
        servidor.sin_port =htons(puerto);

        if(bind(descriptor_socket,(struct sockaddr *)&servidor, sizeof(servidor))<0){
                perror("Error en Bind");
                return 1;
        }

        listen(descriptor_socket, 10);
	char str[39];
	snprintf(str, sizeof(str), "Esperando conexión por el puerto %d\n", puerto);

        puts(str);
        c = sizeof(struct sockaddr_in);

        signal(descriptor_socket, SIG_IGN);

        while(1){
                strcpy(Mensaje_Servidor_1, "Ingresa una palabra para saber si es palíndromo o no: ");

                for(i=0; i<TamCli; i++)
                        Mensaje_Cliente[i] = '\0';

                cliente_socket = accept(descriptor_socket, (struct sockaddr *)&cliente, (socklen_t*)&c);
                if(cliente_socket <0){
                        perror("Las conexiones no pueden ser aceptadas\n");
                        return 1;
                }

                puts("Conexión aceptada...");

                if(fork()==0){
                        write(cliente_socket, Mensaje_Servidor_1, strlen(Mensaje_Servidor_1));
                        recv(cliente_socket, Mensaje_Cliente, 1300, 0);

                        if(Mensaje_Cliente[strlen(Mensaje_Cliente)-1]==0x0A){
                                Mensaje_Cliente[strlen(Mensaje_Cliente)-1] = '\0';
                                Mensaje_Cliente[strlen(Mensaje_Cliente)+1] = '\0';
                                Mensaje_Cliente[strlen(Mensaje_Cliente)] = '\0';
                        }

                        printf("Cliente: %s\n", Mensaje_Cliente);
                        Copiar_Cadena_En_Buffer(Mensaje_Cliente); //Buffer overflow
                        ban = Valida_Cadena(Mensaje_Cliente);
                        if(ban==1){
				snprintf(Mensaje_Servidor_2, TamSer,
				     "\nSi, la palabra es palíndromo\n"
				     "Dirección inicio de buffer:\t%p\n"
				     "Dirección registro de ebp:\t%p\n\n",
				     (void *)buffer_global, (void *)reg_ebp);
                                write(cliente_socket, Mensaje_Servidor_2, strlen(Mensaje_Servidor_2));
                        }
                        else{
				snprintf(Mensaje_Servidor_1, TamSer,
				     "\nNo, la palabra no es un palíndromo\n"
				     "Dirección inicio de buffer:\t%p\n"
				     "Dirección registro de ebp:\t%p\n\n",
				     (void *)buffer_global, (void *)reg_ebp);
                                write(cliente_socket, Mensaje_Servidor_1, strlen(Mensaje_Servidor_1));
                        }
                        ban = 1;
                        close(cliente_socket);
                        puts("El cliente se ha desconectado\n");
                        fflush(stdout);
                }
                else{
                        close(cliente_socket);
                }
        }
        return 0;
}
