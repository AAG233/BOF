import subprocess
ejecutable = './imprime_direccion.exe'
n = 180 

for i in range(n):
    subprocess.run([ejecutable])
    if (i+1) % 6 == 0:
        print (" ")
