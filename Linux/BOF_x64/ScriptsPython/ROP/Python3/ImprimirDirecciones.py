#!/usr/bin/python3
import sys

# Dirección inicial en formato hexadecimal
direccion_inicial = input("Introduce la dirección inicial en el siguiente\nformato 0x00007fffffffffff: ")

# Convertir la entrada a entero (base 16)
direccion_inicial = int(direccion_inicial, 16)

# Número total de direcciones que deseas imprimir
num_direcciones = 85

# Imprimir las direcciones en formato hexadecimal de 8 en 8
for i in range(num_direcciones):
    direccion_actual = direccion_inicial + i * 8
    print("{:016x}".format(direccion_actual))
