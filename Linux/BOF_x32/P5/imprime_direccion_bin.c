#include <stdio.h>
#include <stdint.h>  // Para uintptr_t

// Función para imprimir un número en formato binario con 32 bits
void imprimirBinario(uintptr_t valor) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (valor >> i) & 1);  // Desplaza el bit y obtiene 0 o 1
    }
}

// Función principal
void main() {
    char cadr[12];  // Arreglo de ejemplo

    // Imprimir la dirección de memoria de 'cadr' como un número binario
    imprimirBinario((uintptr_t) &cadr);  // Convertimos la dirección de 'cadr' a uintptr_t
    printf("   ");
}

