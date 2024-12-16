// Filename: main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "include/menu.h"
#include "include/embaixador.h"


// Menu
char menu[][100] = {
    "------------------------------",
    "|            MENU            |",
    "|____________________________|",
    "|                            |",
    "|  1. Listar Visitas         |",
    "|  2. Listar Embaixadores    |",
    "|  3. Listar Visita          |",
    "|  4. Consultar Embaixador   |",
    "|  5. Adicionar Visita       |",
    "|  6. Adicionar Embaixador   |",
    "|  7. Autorizar Visita       |",
    "|  15. Sair                  |",
    "|____________________________|",
};

// Definir tamanho do menu
int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);



// Main
int main() {

    // Ficheiros
    const char ficheiroEmbaixador[] = "data/embaixador.csv";
    
    // Vetor de estrutura de dados
    Embaixador embaixador[MAX_EMBAIXADORES];

    // Inicializar o vetor embaixador
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        embaixador[i].numeroEstudante = -1;
    }

    // Carregar dados do ficheiro para o vetor
    carregarDados(embaixador, ficheiroEmbaixador);



    // Mostrar o menu
    int escolha;

    while(1) { 

        system("cls");

        // Mostrar menu
        mostrarMenu(menu, tamanhoMenu);
        Sleep(250);
        
        
        // Pedir uma opção
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        system("cls");
        Sleep(250);

        // Escolhas
        switch(escolha) { 
            case 2:
                listarEmbaixador(embaixador);
                break;
            case 4:
                consultarEmbaixador(embaixador);
                break;
            case 6:
                adicionarEmbaixador(embaixador);
                salvarDados(embaixador, ficheiroEmbaixador);
                break;
            case 15:
                printf("A sair...");
                return 0;
            default:
                printf("Por favor escolhar uma opcao valida.");
        }

        printf("\nContinuar...");
        getchar();   
        getchar();     
    }
    

    return 0;
}
