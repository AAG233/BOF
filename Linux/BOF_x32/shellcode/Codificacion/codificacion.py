import re
desplazamiento = 3
valor_xor = 0xaf

def cifrado_cesar_xor(Archivo_Entrada, Archivo_Salida): 
    global desplazamiento 
    with open(Archivo_Entrada, 'r') as f:
        linea = f.read()
    
    # Buscar y convertir las secuencias hexadecimales a bytes
    cadena_bytes = bytearray(int(b, 16) for b in re.findall(r'\\x([0-9a-fA-F]{2})', linea))

    # Aplicar el cifrado César a cada byte
    resultado_cesar = bytearray((byte + desplazamiento) % 256 for byte in cadena_bytes)

    # Aplicar la operación XOR con el valor_xor a cada byte del resultado_cesar
    resultado_xor = bytearray(byte ^ valor_xor for byte in resultado_cesar)
    
    with open(Archivo_Salida, 'w') as f:
        f.write(''.join(f'\\x{b:02x}' for b in resultado_xor))
        f.write("\n")


def main():
    Archivo_Entrada = 'entrada_original.txt'
    Archivo_Salida = 'salida_codificada.txt'
    cifrado_cesar_xor(Archivo_Entrada, Archivo_Salida)

main()
