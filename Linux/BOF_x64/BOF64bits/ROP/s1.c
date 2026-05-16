#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#define TamCli 1800
#define TamSer 1800
#define PUERTO 9999

unsigned char *buffer_global = (unsigned char *)0xffffffffffffffff;
unsigned char *reg_rbp = (unsigned char *)0xffffffffffffffff;

void FUNCION_0(){
        printf("EXCELENTE: Has logrado ejecutar la FUNCIÓN 0\n");
        int a=0;
        return;
}

void FUNCION_PRUEBA(const char *cadena){
        printf("La cadena es: %s\n", cadena);
	printf("La dirección de la cadena es: %p\n", (void*)cadena);
        system(cadena);
        return;
}

void Copiar_Cadena_En_Buffer(char *Mensaje_Cliente, int bytes){
        char buffer[599];
        printf ( "\nDirección de inicio del buffer es \t\t\t%p", &buffer ) ;
        buffer_global = buffer;

        __asm__("movq %%rbp, %0" : "=r" (reg_rbp));
        printf("\nValor de RBP:\t\t\t\t\t\t%p \n", reg_rbp);

        memcpy(buffer, Mensaje_Cliente, bytes);
}

int Es_Palindromo(char buffer[], int s, int e){
        if(s == e){return 1;}

        if(buffer[s] != buffer[e]){return 0;}

        if(s < e + 1){return Es_Palindromo(buffer, s + 1, e - 1);}

        return 1;
}

int Valida_Cadena(char *Mensaje_Cliente){
        char buffer[1300];
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
        servidor.sin_port =htons(PUERTO);

        if(bind(descriptor_socket,(struct sockaddr *)&servidor, sizeof(servidor))<0){
                perror("Error en Bind");
                return 1;
        }

        listen(descriptor_socket, 10);

        printf("Escuchando peticiones por el puerto: %i\n", PUERTO);
        puts("Esperando conexiones...");
        c = sizeof(struct sockaddr_in);

        signal(descriptor_socket, SIG_IGN);

        while(1){
                strcpy(Mensaje_Servidor_1, "Ingresa una palabra para revisar si es un palíndromo: ");
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

                        int tamanio=0;
                        printf("Cliente: ");
                        while(Mensaje_Cliente[tamanio]!=0x0A){ //Imprime hasta que encuentre el enter = 0x0A
                                printf("%c",Mensaje_Cliente[tamanio]);
                                tamanio++;
                        }
                        printf("\n");

                        Copiar_Cadena_En_Buffer(Mensaje_Cliente, tamanio); //Función que causa el buffer overflow
			Mensaje_Cliente[tamanio] = '\0';
			ban = Valida_Cadena(Mensaje_Cliente);

			if (ban == 1) {
			    snprintf(Mensaje_Servidor_2, TamSer,
				     "\nSí, la palabra es palíndromo\n"
				     "Dirección inicio de buffer:\t%p\n"
				     "Dirección registro de rbp:\t%p\n\n",
				     (void *)buffer_global, (void *)reg_rbp);
			    write(cliente_socket, Mensaje_Servidor_2, strlen(Mensaje_Servidor_2));
			} else {
			    snprintf(Mensaje_Servidor_1, TamSer,
				     "\nNo, la palabra no es un palíndromo\n"
				     "Dirección inicio de buffer:\t%p\n"
				     "Dirección registro de rbp:\t%p\n\n",
				     (void *)buffer_global, (void *)reg_rbp);
			    write(cliente_socket, Mensaje_Servidor_1, strlen(Mensaje_Servidor_1));
			}
                        ban = 1;
                        close(cliente_socket);
                        puts("El cliente fue desconectado\n");
                        fflush(stdout);
                }
                else{
                        close(cliente_socket);
                }

       	}
	return 0;
}
