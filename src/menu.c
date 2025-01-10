// Menu.c

#include <stdio.h>

#include "../include/menu.h"

// Items do menu
char menuItems[][75] = {
    "---------------------------------------------------",
    "|                       MENU                       |",
    "|__________________________________________________|",
    "|                                                  |",
    "|      1. Listar Visitas                           |",
    "|      2. Listar Embaixadores                      |",
    "|      3. Consultar Visita                         |",
    "|      4. Consultar Embaixador                     |",
    "|      5. Adicionar Visita                         |",
    "|      6. Adicionar Embaixador                     |",
    "|      7. Autorizar Visita                         |",
    "|      8. Cancelar Visita                          |",
    "|      9. Confirmar Visita                         |",
    "|      10. Alterar Informacao da Visita            |",
    "|      11. Alterar Informacao do Embaixador        |",
    "|      12. Eliminar Visita                         |",
    "|      13. Eliminar Embaixador                     |",
    "|      14. Gravar Visitas                          |",
    "|      15. Sair                                    |",
    "|                                                  |",
    "|__________________________________________________|",
};

// Tamanho do mnenu
int tamanhoMenu = sizeof(menuItems) / sizeof(menuItems[0]);


// Mostrar menu 
void mostrarMenu() {
    
    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menuItems[i]);
    }
}