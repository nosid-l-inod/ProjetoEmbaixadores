// Main.c


#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "include/menu.h"
#include "include/embaixador.h"


// Main
int main() {

    // Ficheiros de dados
    const char *ficheiroEmbaixador = "data/embaixador.csv";
    const char *ficheiroVisita = "data/visita.csv";

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];

    // Inicializar vetores
    inicializarEmbaixador(embaixador);
    
    // Gerir dados
    carregarEmbaixador(embaixador, ficheiroEmbaixador);
    // salvarEmbaixador(embaixador, ficheiroEmbaixador);
    
    int escolha;


    // Loop infinito
    while (1) {
        
        system("cls");
        mostrarMenu();
        Sleep(250);

        printf("\nSelecione a opcao: ");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1:
                printf("Listar visitas");
                break;
            case 2:
                printf("Listar embaixadores");
                listarEmbaixadores(embaixador);
                break;
            case 3:
                printf("Consultar visita");
                break;
            case 4:
                printf("Consultar embaixador");
                break;
            case 5:
                printf("Adicionar visita");
                break;
            case 6:
                printf("Adicionar embaixador");
                break;
            case 7:
                printf("Autorizar visita");
                break;
            case 8:
                printf("Cancelar visita");
                break;
            case 9:
                printf("Confirmar realização da visita");
                break;
            case 10:
                printf("Alterar informação da visita");
                break;
            case 11:
                printf("Alterar informação do embaixador");
                break;
            case 12:
                printf("Eliminar visita");
                break;
            case 13:
                printf("Eliminar embaixador");
                break;
            case 14:
                printf("Gravar visitas");
                break;
            case 15:
                printf("Sair");
                break;
            default:
                printf("Opcao invalida");
        } 

        getchar();
        getchar();
    }

    
    return 0;
}