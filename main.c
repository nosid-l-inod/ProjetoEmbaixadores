// Filename: main.c
#include <stdio.h>
#include "include/embaixador.h"
#include "menu.h"

int main() {
    int choice;
    int numeroEstudante;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adicionarEmbaixador("embaixador.dat");
                break;
            case 2:
                listarEmbaixadores("embaixador.dat");
                break;
            case 3:
                printf("Insira o numero do estudante: ");
                scanf("%d", &numeroEstudante);
                consultarEmbaixador(numeroEstudante, "embaixador.dat");
                break;
            case 4:
                editarEmbaixador();
                break;
            case 5:
                eliminarEmbaixador();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 6);

    return 0;
}
