define imprimir_memoria
	set $i = 0
	set $direccion = $esp + 260 
	while ($i < 52)  
		printf "0x%x: 0x", $direccion
		set $valor1 = *(unsigned char *)$direccion
		set $valor2 = *(unsigned char *)($direccion + 1)
		set $valor3 = *(unsigned char *)($direccion + 2)
		set $valor4 = *(unsigned char *)($direccion + 3)
		printf "%02x%02x%02x%02x\n", $valor4, $valor3, $valor2, $valor1
		set $direccion = $direccion + 4
		set $i = $i + 1
	end
end
