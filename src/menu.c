// Filename: menu.c
#include <stdio.h>
#include "../include/menu.h"


// Mostrar o menu
void mostrarMenu(char menu[][100], int tamanho) {

    // Mostrar items
    for (int i = 0; i < tamanho; i++) {
        printf("%s\n", menu[i]);
    }

    printf("\n");
}