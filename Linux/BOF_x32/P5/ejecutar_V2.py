import subprocess
import time
script_a_ejecutar = './p5.exe'
contador = 0
inicio = time.time()
while 1:
    subprocess.run([script_a_ejecutar])
    contador = contador + 1
    fin = time.time()
    tiempos = fin - inicio
    print(f'Intento: {contador}\tTiempo de ejecución: {tiempos:.2f} segundos')
