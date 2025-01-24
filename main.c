#include <stdio.h>
#include <windows.h>
#include "include/embaixador.h"
#include "include/visita.h"
#include "include/utils.h"
#include "include/menu.h"

// Main
int main() {
    
    // Ficheiros de dados
    const char *ficheiroEmbaixador = "data/embaixador.csv";
    const char *ficheiroVisita = "data/visita.csv";

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];
    Visita visita[MAX_VISITAS];

    // Inicializar vetores
    inicializarEmbaixador(embaixador);
    inicializarVisita(visita);

    // Carregar dados do ficheiro para o vetor
    carregarEmbaixador(embaixador, ficheiroEmbaixador);
    carregarVisita(visita, ficheiroVisita);

    int opcao;
    char continuar;

    while (1) {
        cls();
        mostrarMenu();

        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        cls();

        Sleep(250);

        switch (opcao) {
            case 1:
                listarVisitas(visita);
                break;
            case 2:
                listarEmbaixadores(embaixador);
                break;
            case 3:
                consultarVisita(visita, embaixador);
                break;
            case 4:
                consultarEmbaixador(embaixador);
                break;
            case 5:
                adicionarVisita(visita, embaixador, ficheiroVisita);
                break;
            case 6:
                do {
                    cls();
                    adicionarEmbaixador(embaixador, ficheiroEmbaixador);

                    printf("\n\nAdicionar mais embaixadores? (S/N): ");
                    scanf(" %c", &continuar);
                    while (getchar() != '\n');
                } while (continuar == 's' || continuar == 'S');
                break;
            case 7:
                autorizarVisita(visita, embaixador, ficheiroVisita);
                break;
            case 8:
                cancelarVisita(visita, ficheiroVisita);
                break;
            case 9:
                confirmarRealizacaoVisita(visita, ficheiroVisita);
                break;
            case 10:
                alterarInformacaoVisita(visita, embaixador, ficheiroVisita);
                break;
            case 11:
                alterarInfoEmbaixador(embaixador, ficheiroEmbaixador);
                break;
            case 12:
                eliminarVisita(visita, ficheiroVisita);
                break;
            case 13:
                eliminarEmbaixador(embaixador, ficheiroEmbaixador);
                break;
            case 15:
                sair();
                break;
            default:
                printf("Opcao invalida.\n");
        }

        printf("..");
        getchar();
    }

    return 0;
}
