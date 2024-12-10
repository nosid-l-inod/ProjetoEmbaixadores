// Filename: main.c


#include <stdio.h>
#include "include/embaixador.h"
#include "include/menu.h"


// Main function
int main() {

    int choice;

    do {
        // displayMenu();
        menu();
        choice = getValidatedInt("");

        switch (choice) {
            case 1:
                adicionarEmbaixador("embaixador.dat");
                break;
            case 2:
                listarEmbaixadores("embaixador.dat");
                break;
            case 3:
                consultarEmbaixador(getValidatedInt("Insira o numero do estudante: "), "embaixador.dat");
                break;
            case 4:
                editarEmbaixador();
                break;
            case 5:
                eliminarEmbaixador();
                break;
            case 15:
                printf("A sair do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 6);

    return 0;
}
