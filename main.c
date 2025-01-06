// Main.c

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "include/embaixador.h"
#include "include/visita.h"
#include "include/menu.h"


// Main
int main() {

    // Ficheiros csv
    const char *ficheiroEmbaixador = "data/embaixador.csv";
    const char *ficheiroVisita = "data/visita.csv";

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];
    Visita visita[MAX_VISITAS];

    // ContarEmbaixador
    int contarEmbaixadores = 0;

    int escolha;

    while (1) {
        
        system("cls");
        mostrarMenu();

        printf("\nSelecione a opcao: ");
        scanf("%d", &escolha);

        system("cls");

        switch (escolha) {
            case 6:
                adicionarEmbaixador(embaixador, ficheiroEmbaixador);
                break;
            case 15:
                sairMenu();
                break;
            default:
                printf("Opcao invalida.");
        }
        getchar();
        getchar();
    }

    
    return 0;
}