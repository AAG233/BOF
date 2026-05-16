# Dirección inicial en formato hexadecimal
direccion_inicial = input("Introduce la direccion inicial en el siguiente\nformato 0x00007fffffffffff: ")

# Número total de direcciones que deseas imprimir
num_direcciones = 85

# Imprimir las direcciones en formato hexadecimal de 8 en 8
for i in range(num_direcciones):
    direccion_actual = direccion_inicial + i * 8
    print("{:016x}".format(direccion_actual))


