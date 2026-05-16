def incrementar_direccion(direccion, incrementos, num_lineas):
    # Convertir la dirección inicial de hexadecimal a un entero
    direccion_actual = int(direccion, 16)
    
    # Imprimir las direcciones en incrementos de 4 bytes
    for _ in range(num_lineas):
        print(hex(direccion_actual))
        direccion_actual += incrementos

direccion_inicial = input("Introduce una dirección (por ejemplo, 0xbfff7781): ")
incrementos = 4
num_lineas = 165

incrementar_direccion(direccion_inicial, incrementos, num_lineas)

