#include <stdio.h>
#include "../include/menu.h"

// Mostrar menu
void mostrarMenu() {

    // Items do menu
    const char menu[][100] = {
        "+------------------------------------------------+",
        "|                      Menu                      |",
        "|------------------------------------------------|",
        "|                                                |",
        "|      1. Listar Visitas                         |",
        "|      2. Listar Embaixadores                    |",
        "|      3. Consultar Visita                       |",
        "|      4. Consultar Embaixador                   |",
        "|      5. Adicionar Visita                       |",
        "|      6. Adicionar Embaixador                   |",
        "|      7. Autorizar visita                       |",
        "|      8. Cancelar Visita                        |",
        "|      9. Confirmar Realizacao da Visita         |",
        "|      10. Alterar Informacao da Visita          |",
        "|      11. Alterar Informacoes do Embaixador     |",
        "|      12. Eliminar visita                       |",
        "|      13. Remover Embaixador                    |",
        "|      15. Sair                                  |",
        "|                                                |",
        "+------------------------------------------------+"
    };

    // tamanho do menu
    int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);

    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menu[i]);
    }
}
