import re
desplazamiento = 11 #Desplazamiento con cifrado César
valor_xor = 0x23

def codificado_cesar_xor(Archivo_Entrada, Archivo_Salida):
    global desplazamiento
    with open(Archivo_Entrada, 'r') as f:
        linea = f.read()

    #Buscamos y convertimos los hexadecimales a bytes
    cadena_bytes = bytearray(int(b, 16) for b in re.findall(r'\\x([0-9a-fA-F]{2})', linea))

    #Aplicamos el desplazamiento a cada byte
    resultado_cesar = bytearray((byte + desplazamiento) % 256 for byte in cadena_bytes)

    #Aplicamos para cada byte un xor
    resultado_xor = bytearray(byte ^ valor_xor for byte in resultado_cesar)

    with open(Archivo_Salida, 'w') as f:
        f.write(''.join(f'\\x{b:02x}' for b in resultado_xor))
        f.write("\n")

def main():
    Archivo_Entrada = 'entrada_original.txt'
    Archivo_Salida = 'salida_codificada.txt'
    codificado_cesar_xor(Archivo_Entrada, Archivo_Salida)

main()
