// Ficheiro: menu.c
// Data: 10/01/2025
// Descrição: Contém funções do menu

#include "../include/menu.h"


// Items do menu
const char menu[][100] = {
    "+------------------------------------------------+",
    "|                      Menu                      |",
    "|------------------------------------------------|",
    "|                                                |",
    "|      1. Listar Visitas                         |",
    "|      2. Listar Embaixadores                    |",
    "|      4. Consultar Embaixador                   |",
    "|      5. Adicionar Visita                       |",
    "|      6. Adicionar Embaixador                   |",
    "|      11. Alterar Informacoes do Embaixador     |",
    "|      13. Remover Embaixador                    |",
    "|      15. Sair                                  |",
    "|                                                |",
    "+------------------------------------------------+"
};

// tamanho do menu
int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);


// Mostrar menu
void mostrarMenu() {
    int i;

    for (i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menu[i]);
    }
}