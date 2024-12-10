// Filename: menu.c
#include <stdio.h>
#include "include/menu.h"


// Function to display menu options
void menu() {
    
    // Menu options
    char menu[][50] = {
        "1 - Listar Visitas",
        "2 - Listar Embaixadores",
        "3 - Consultar Visita",
        "4 - Consultar Embaixadores",
        "5 - Adicionar Visita",
        "6 - Adicionar Embaixador",
        "7 - Autorizar Visita",
        "15 - Sair",
    };
    
    // Menu size
    int size = sizeof(menu) / sizeof(menu[0]);
    int i;

    // Show menu items 
    for (i = 0; i < size; i++) {
        printf("%s\n", menu[i]);
    }
    
    printf("\n");
}