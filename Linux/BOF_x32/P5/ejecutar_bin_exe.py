import subprocess
ejecutable = './imprime_direccion_bin.exe'
n = 180 

for i in range(n):
    subprocess.run([ejecutable])
    if (i+1) % 3 == 0:
        print (" ")
