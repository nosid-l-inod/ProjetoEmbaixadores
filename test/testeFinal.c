// Última versão de teste

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_EMBAIXADORES 100
#define MAX_VISITAS 1000
#define MAX_EMBAIXADORES_VISITA 9


// Estrutura do embaixador
typedef struct {
    int numero_estudante;
    char escola[5];
    char nomeCompleto[100];
    char nif[10];
} Embaixador;

// Estrutura da visita
typedef struct {
    int IdVisita;
    int listaEmbaixadores[MAX_EMBAIXADORES_VISITA];
    char estado[20];
    char local[100];
    char data[20];
} Visita;

// Protótipo de funções do embaixador
void addEmbaixador(Embaixador embaixador[]);
void showEmbaixadores(Embaixador embaixador[]);
void viewEmbaixadorDetails(Embaixador embaixador[]);
void removeEmbaixador(Embaixador embaixador[]);
void editEmbaixador(Embaixador embaixador[]);

// Protótipo de funções da visita
void showVisitas(Visita visitas[]);
void viewVisitaDetails(Visita visitas[]);
void saveVisitas(Visita visitas[], const char *filename);
void addVisita(Visita visitas[], Embaixador embaixador[], int *next_IdVisita, const char *filename);
void authorizeVisita(Visita visitas[]);

// Protótipo de funções do menu
void showMenu();

// Protótipo de funções de gestão de dados
void saveData(Embaixador embaixador[], const char *filename);
void loadData(Embaixador embaixador[], const char *filename);

// Protótipo de funções para gestão e validação de dados
int getValidInteger(const char *prompt);
void getValidName(char *name, const char *prompt);
void getValidNIF(char *nif, const char *prompt);
void sortEmbaixadoresByName(Embaixador embaixador[]);
void capitalizeName(char *name);
void sortEmbaixadoresByName(Embaixador embaixador[]);

// Protótipo de funções adicionais
void initializeVisitas(Visita visitas[]);
void initializeEmbaixadores(Embaixador embaixador[]);
void showEmbaixadoresIndex(Embaixador embaixador[]);
void cls();


// Main
int main() {

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];
    Visita visitas[MAX_VISITAS];

    // Ficheiros de dados
    char filename_embaixador[] = "embaixador.csv";
    char filename_visita[] = "visita.csv";

    // Contadores
    int next_numero_estudante = 1;
    int next_IdVisita = 1;

    // Inicializar vetores
    initializeEmbaixadores(embaixador);
    initializeVisitas(visitas);

    // Carregar dados   
    loadData(embaixador, filename_embaixador);

    // Atualizar o numero de estudante
    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
        if (embaixador[i].numero_estudante >= next_numero_estudante) {
            next_numero_estudante = embaixador[i].numero_estudante + 1;
        }
    }

    char continuar;
    int choice;

    // Loop infinito
    while (1) {
        cls();
        showMenu();

        printf("\nSelecione uma opcao: ");
        scanf("%d", &choice);

        cls();
        Sleep(200);

        switch (choice) {
            case 1:
                do {
                    addEmbaixador(embaixador);
                    saveData(embaixador, filename_embaixador);

                    printf("Adicionar mais embaixadores? (S/N) ");
                    scanf(" %c", &continuar);
                }
                while (continuar == 's' || continuar == 'S');
                
                break;
            case 2:
                removeEmbaixador(embaixador);
                saveData(embaixador, filename_embaixador);
                break;
            case 3:
                editEmbaixador(embaixador);
                saveData(embaixador, filename_embaixador);
                break;
            case 4:
                showEmbaixadores(embaixador);
                break;
            case 5:
                viewEmbaixadorDetails(embaixador);
                break;
            case 6:
                addVisita(visitas, embaixador, &next_IdVisita, filename_visita);
                break;
            case 7:
                showVisitas(visitas);
                break;
            case 8:
                viewVisitaDetails(visitas);
                break;
            case 9:
                authorizeVisita(visitas);
                break;
            case 15:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nContinuar..");
        getchar();
        getchar();
    }
    
    return 0;
}


// Limpar
void cls() {
    system("cls");
}

// Menu
void showMenu() {
    // Items do menu
    char menuItems[][75] = {
        "___________________________________________________",
        "|                                                  |",
        "|                       MENU                       |",
        "|__________________________________________________|",
        "|                                                  |",
        "|      1. Adicionar Embaixador                     |",
        "|      2. Remover Embaixador                       |",
        "|      3. Editar Embaixador                        |",
        "|      4. Listar Embaixadores                      |",
        "|      5. Ver detalhes de embaixador               |",
        "|      6. Adicionar Visita                         |",
        "|      7. Listar Visitas                           |",
        "|      8. Ver Detalhes de Visitas                  |",
        "|      15. Sair                                    |",
        "|                                                  |",
        "|__________________________________________________|",
    };

    // Tamanho do mnenu
    int tamanhoMenu = sizeof(menuItems) / sizeof(menuItems[0]);

    // Mostrar menu 
    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menuItems[i]);
    }
}

// Salvar dados no ficheiro
void saveData(Embaixador embaixador[], const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Unable to open the file to save data\n");
        return;
    }

    fprintf(file, "NumeroEstudante, Escola, NomeCompleto, NIF\n");
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numero_estudante == -1) {
            break;
        }
        fprintf(
            file, 
            "%d, %s, %s, %s\n", 
            embaixador[i].numero_estudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
    }
    fclose(file);
}

// Carregar dados do ficheiro
void loadData(Embaixador embaixador[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file\n");
        return;
    }

    char line[256];
    int i = 0;
    fgets(line, sizeof(line), file); // Skip the header

    while (fgets(line, sizeof(line), file) && i < MAX_EMBAIXADORES) {
        sscanf(
            line, 
            "%d, %[^,], %[^,], %s", 
            &embaixador[i].numero_estudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        i++;
    }
    
    // Initialize the next slot as the sentinel
    if (i < MAX_EMBAIXADORES) {
        embaixador[i].numero_estudante = -1;
    }
    
    fclose(file);
}

// Iniciializar embaixadores
void initializeEmbaixadores(Embaixador embaixador[]) {
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        embaixador[i].numero_estudante = -1;
    }
}

// Inicializar visitas
void initializeVisitas(Visita visitas[]) {
    for (int i = 0; i < MAX_VISITAS; i++) {
        visitas[i].IdVisita = -1;
    }
}

// Validar inteiros
int getValidInteger(const char *prompt) {
    int value, valid = 0;
    while (!valid) {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            printf("Input invalido. Por favor insira um numero.\n\n");
            while (getchar() != '\n');
        } else {
            valid = 1;
        }
    }

    return value;
}

// Validar nome
void getValidName(char *name, const char *prompt) {
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';  // Remove the newline character

        valid = 1;
        for (int i = 0; name[i] != '\0'; i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                printf("Nome invalido. Insira um nome sem numeros ou caracteres especiais.\n");
                valid = 0;
                break;
            }
        }
    }
}

// Validar NIF
void getValidNIF(char *nif, const char *prompt) {
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);
        fgets(nif, 10, stdin);
        nif[strcspn(nif, "\n")] = '\0';

        valid = 1;

        // Verificar se tem 9 digitos
        if (strlen(nif) != 9) {
            valid = 0;
            printf("NIF invalido. Insira o NIF com 9 digitos.\n");
        } else {
            for (int i = 0; nif[i] != '\0'; i++) {

                if (!isdigit(nif[i])) {
                    printf("Nif invalido. Insira um nif com apenas numeros.\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
}

// Capitalizar nome
void capitalizeName(char *name) {
    int in_word = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!in_word && isalpha(name[i])) {
            name[i] = toupper(name[i]);
            in_word = 1;
        } else if (in_word && isalpha(name[i])) {
            name[i] = tolower(name[i]);
        } else {
            in_word = 0;
        }
    }
}

// Ordenar embaixadores
void sortEmbaixadoresByName(Embaixador embaixador[]) {
    for (int i = 0; i < MAX_EMBAIXADORES - 1 && embaixador[i].numero_estudante != -1; i++) {
        for (int j = i + 1; j < MAX_EMBAIXADORES && embaixador[j].numero_estudante != -1; j++) {
            if (strcmp(embaixador[i].nomeCompleto, embaixador[j].nomeCompleto) > 0) {
                Embaixador temp = embaixador[i];
                embaixador[i] = embaixador[j];
                embaixador[j] = temp;
            }
        }
    }
}

// Adicionar embaixador
void addEmbaixador(Embaixador embaixador[]) {
    int i, escolha;
    char nif[10];

    // Encontrar o slot vazio
    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numero_estudante == -1) {
            break;
        }
    }

    // Verificar o limite de embaixadores
    if (i >= MAX_EMBAIXADORES) {
        printf("O limite de embaixadores foi atingido.\n");
        return;
    }

    // Numero de estudaante
    int numero_estudante;

    numero_estudante = getValidInteger("Numero de estudante: ");
    embaixador[i].numero_estudante = numero_estudante;

    // Escola
    const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
    int num_escolas = sizeof(escolas) / sizeof(escolas[0]);

    // Mostrar escolas
    printf("\nEscolas disponiveis: \n");
    for (int j = 0; j < num_escolas; j++) {
        printf("%d. %s\n", j + 1, escolas[j]);
    }
    
    // Selecionar escola
    int valid_input = 0;

    while (!valid_input) {
        printf("\nInsira a escola (1-%d): ", num_escolas);
        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > num_escolas) {
            printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", num_escolas);
            while (getchar() != '\n');
        } else {
            valid_input = 1;
        }
    }

    // Adicionar escola
    strcpy(embaixador[i].escola, escolas[escolha - 1]);
    while (getchar() != '\n');

    //  Nome completo
    char nomeCompleto[150];

    getValidName(nomeCompleto, "\nNome completo: ");
    nomeCompleto[strlen(nomeCompleto) - 1] = '\0';

    // printf("\nNome completo: ");
    // fgets(nomeCompleto, 150, stdin);

    // Capitalizar o nome
    capitalizeName(nomeCompleto);

    strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

    // NIF
    getValidNIF(nif, "\nNIF: ");
    strcpy(embaixador[i].nif, nif);

    // Reservar o próximo slot
    if (i + 1 < MAX_EMBAIXADORES) {
        embaixador[i + 1].numero_estudante = -1;
    }

    printf("\nEmbaixador adicionado com sucesso.\n");

    }

// Listar embaixadores
void showEmbaixadores(Embaixador embaixador[]) {
    
    // Ordenar embaixadores pelo nome
    sortEmbaixadoresByName(embaixador);

    printf("Embaixadores:\n");
    printf("+-----------------+-------+--------------------+------------+\n");
    printf("| %-15s | %-5s | %-18s | %-9s |\n", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+-----------------+-------+--------------------+------------+\n");
    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
        printf("| %-15d | %-5s | %-18s | %-9s |\n", embaixador[i].numero_estudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
        printf("+-----------------+-------+--------------------+---------+\n");
    }
}

// Listar embaixadores e incluir o index
void showEmbaixadoresIndex(Embaixador embaixador[]) {
    
    // Ordenar embaixadores pelo nome
    sortEmbaixadoresByName(embaixador);

    printf("Embaixadores registados: \n");
    printf("+----+---------------------+---------+-------------------------------------------+------------+\n");
    printf("| %-2s | %-19s | %-7s | %-41s | %-10s |\n", "No", "Numero de Estudante", "Escola", "Nome Completo", "NIF");
    printf("+----+---------------------+---------+-------------------------------------------+------------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
        printf("| %-2d | %-19d | %-7s | %-41s | %-10s |\n", i + 1, embaixador[i].numero_estudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
        printf("+----+---------------------+---------+-------------------------------------------+------------+\n");
    }
}


// Listar detalhes do embaixador
void viewEmbaixadorDetails(Embaixador embaixador[]) {
    int numero_estudante, found = 0;

    // Show the list of embaixadores before viewing details
    showEmbaixadores(embaixador);

    printf("Enter the NumeroEstudante of the embaixador to view details: ");
    scanf("%d", &numero_estudante);

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
        if (embaixador[i].numero_estudante == numero_estudante) {
            printf("Details of Embaixador with NumeroEstudante %d:\n", numero_estudante);
            printf("Nome Completo: %s\n", embaixador[i].nomeCompleto);
            printf("Escola: %s\n", embaixador[i].escola);
            printf("NIF: %s\n", embaixador[i].nif);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Embaixador with NumeroEstudante %d not found.\n", numero_estudante);
    }
}

// Sample remover embaixador
void removeEmbaixador(Embaixador embaixador[]) {

    // Listar embaixadores
    // showEmbaixadores(embaixador);
    showEmbaixadoresIndex(embaixador);

    int escolha;

    printf("\nSelecione o embaixador para remover: ");
    scanf("%d", &escolha);


}

// Remover embaixador
// void removeEmbaixador(Embaixador embaixador[]) {
//     int choice, numero_estudante, index, found = 0;
//     char nomeCompleto[100];

//     // Opções para remover embaixadores
//     char opcoes[][50] = {"1. Numero Estudante", "2. Nome Completo", "3. Index"};
//     int tamanhoOpcoes = sizeof(opcoes) / sizeof(opcoes[0]);

//     printf("Remover por: \n");
//     for (int i = 0; i < tamanhoOpcoes; i++) {
//         printf("%s\n", opcoes[i]);
//     }

//     printf("\nEnter your choice: ");
//     scanf("%d", &choice);

//     switch (choice) {

//         // Remover por numero de estudante
//         case 1:
//             showEmbaixadores(embaixador);
              
//             printf("Insira o numero de estudante: ");
//             scanf("%d", &numero_estudante);

//             for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
//                 if (embaixador[i].numero_estudante == numero_estudante) {
//                     for (int j = i; j < MAX_EMBAIXADORES - 1; j++) {
//                         embaixador[j] = embaixador[j + 1];
//                         if (embaixador[j].numero_estudante == -1) {
//                             break;
//                         }
//                     }
//                     found = 1;
//                     // Mark the new last slot as the sentinel
//                     if (i < MAX_EMBAIXADORES - 1) {
//                         embaixador[MAX_EMBAIXADORES - 1].numero_estudante = -1;
//                     }
//                     break;
//                 }
//             }
//             if (!found) {
//                 printf("O embaixador com numero de estudante %d nao foi encontrado.\n", numero_estudante);
//             }
//             break;

//         // Remover por nome completo
//         case 2:

//             // Mostrar lista de embaixadores
//             showEmbaixadores(embaixador);

//             printf("Enter the NomeCompleto of the embaixador to remove: ");
//             scanf(" %[^\n]", nomeCompleto);

//             for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numero_estudante != -1; i++) {
//                 if (strcmp(embaixador[i].nomeCompleto, nomeCompleto) == 0) {
//                     for (int j = i; j < MAX_EMBAIXADORES - 1; j++) {
//                         embaixador[j] = embaixador[j + 1];
//                         if (embaixador[j].numero_estudante == -1) {
//                             break;
//                         }
//                     }
//                     found = 1;
//                     // Mark the new last slot as the sentinel
//                     if (i < MAX_EMBAIXADORES - 1) {
//                         embaixador[MAX_EMBAIXADORES - 1].numero_estudante = -1;
//                     }
//                     break;
//                 }
//             }
//             if (!found) {
//                 printf("Embaixador with NomeCompleto '%s' not found.\n", nomeCompleto);
//             }
//             break;

//         // Remover pela posição no vetor
//         case 3:
//             printf("Enter the index of the embaixador to remove: ");
//             scanf("%d", &index);
//             index--;  // Convert from 1-based to 0-based index

//             if (index < 0 || index >= MAX_EMBAIXADORES || embaixador[index].numero_estudante == -1) {
//                 printf("Invalid index.\n");
//             } else {
//                 for (int j = index; j < MAX_EMBAIXADORES - 1; j++) {
//                     embaixador[j] = embaixador[j + 1];
//                     if (embaixador[j].numero_estudante == -1) {
//                         break;
//                     }
//                 }
//                 // Mark the new last slot as the sentinel
//                 if (index < MAX_EMBAIXADORES - 1) {
//                     embaixador[MAX_EMBAIXADORES - 1].numero_estudante = -1;
//                 }
//                 found = 1;
//             }
//             break;

//         default:
//             printf("Invalid choice.\n");
//             break;
//     }

//     if (found) {
//         printf("Embaixador removed successfully.\n");
//     }
// }

// Editar embaixador
void editEmbaixador(Embaixador embaixador[]) {
    int index, found = 0;
    char nomeCompleto[100];
    char nif[10];

    // Show the list of embaixadores before editing
    showEmbaixadores(embaixador);

    printf("Enter the index (No) of the embaixador to edit: ");
    scanf("%d", &index);
    index--;  // Convert from 1-based to 0-based index

    if (index < 0 || index >= MAX_EMBAIXADORES || embaixador[index].numero_estudante == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Editing embaixador with No %d\n", index + 1);

        // Clear the input buffer before using fgets
        while (getchar() != '\n');

        // Get and validate nomeCompleto
        getValidName(nomeCompleto, "Enter new nomeCompleto: ");
        strcpy(embaixador[index].nomeCompleto, nomeCompleto);

        // Get and validate nif
        getValidNIF(nif, "Enter new nif: ");
        strcpy(embaixador[index].nif, nif);

        found = 1;
    }

    if (!found) {
        printf("Embaixador with No %d not found.\n", index + 1);
    }
}

// Listar visitas
void showVisitas(Visita visitas[]) {
    printf("+----+-----------------------+---------------------+------------+----------------+\n");
    printf("| %-2s | %-21s | %-19s | %-10s | %-14s |\n", "ID", "Estado", "Local", "Data", "ListaEmbaixadores");
    printf("+----+-----------------------+---------------------+------------+----------------+\n");
    for (int i = 0; i < MAX_VISITAS && visitas[i].IdVisita != -1; i++) {
        printf("| %-2d | %-21s | %-19s | %-10s | ", visitas[i].IdVisita, visitas[i].estado, visitas[i].local, visitas[i].data);
        for (int j = 0; j < MAX_EMBAIXADORES_VISITA && visitas[i].listaEmbaixadores[j] != 0; j++) {
            printf("%d ", visitas[i].listaEmbaixadores[j]);
        }
        printf("\n");
        printf("+----+-----------------------+---------------------+------------+----------------+\n");
    }
}

// Ver detalhes da visita
void viewVisitaDetails(Visita visitas[]) {
    int IdVisita, found = 0;

    printf("Enter the IdVisita of the visita to view details: ");
    scanf("%d", &IdVisita);

    for (int i = 0; i < MAX_VISITAS && visitas[i].IdVisita != -1; i++) {
        if (visitas[i].IdVisita == IdVisita) {
            printf("Details of Visita with IdVisita %d:\n", IdVisita);
            printf("Estado: %s\n", visitas[i].estado);
            printf("Local: %s\n", visitas[i].local);
            printf("Data: %s\n", visitas[i].data);
            printf("ListaEmbaixadores: ");
            for (int j = 0; j < MAX_EMBAIXADORES_VISITA && visitas[i].listaEmbaixadores[j] != 0; j++) {
                printf("%d ", visitas[i].listaEmbaixadores[j]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Visita with IdVisita %d not found.\n", IdVisita);
    }
}

// Salvar visitas
void saveVisitas(Visita visitas[], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file to save data\n");
        return;
    }

    fprintf(file, "IdVisita,Estado,Local,Data,ListaEmbaixadores\n");
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }
        fprintf(file, "%d,%s,%s,%s,", visitas[i].IdVisita, visitas[i].estado, visitas[i].local, visitas[i].data);
        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            if (visitas[i].listaEmbaixadores[j] != 0) {
                fprintf(file, "%d ", visitas[i].listaEmbaixadores[j]);
            } else {
                break;
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Adicionar visita
void addVisita(Visita visitas[], Embaixador embaixador[], int *next_IdVisita, const char *filename) {
    int i;
    int numeroEstudante;
    char local[100];
    char data[20];
    int valid_input = 0;

    // Find the next empty slot
    for (i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }
    }

    if (i >= MAX_VISITAS) {
        printf("Maximum number of visitas reached.\n");
        return;
    }

    // Assign automatic IdVisita
    visitas[i].IdVisita = *next_IdVisita;
    (*next_IdVisita)++;

    // Assign default estado
    strcpy(visitas[i].estado, "em planeamento");

    // Get and validate local
    printf("Enter local: ");
    while (getchar() != '\n');  // Clear the input buffer
    fgets(local, sizeof(local), stdin);
    local[strcspn(local, "\n")] = '\0';  // Remove the newline character
    strcpy(visitas[i].local, local);

    // Get and validate data
    printf("Enter data (format: DD/MM/YYYY): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';  // Remove the newline character
    strcpy(visitas[i].data, data);

    // Show list of embaixadores
    printf("Available Embaixadores:\n");
    showEmbaixadores(embaixador);

    // Get and validate listaEmbaixadores
    printf("Enter up to 9 NumeroEstudante for listaEmbaixadores (0 to end):\n");
    for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
        printf("NumeroEstudante %d: ", j + 1);
        if (scanf("%d", &numeroEstudante) != 1 || numeroEstudante == 0) {
            visitas[i].listaEmbaixadores[j] = 0;
            break;
        }
        visitas[i].listaEmbaixadores[j] = numeroEstudante;
    }

    // Save visitas to file
    saveVisitas(visitas, filename);
}

// Autorizar visita
void authorizeVisita(Visita visitas[]) {
    int IdVisita, escolha, valid_input = 0;
    const char *estados[] = {"autorizada", "cancelada", "realizada"};
    int num_estados = sizeof(estados) / sizeof(estados[0]);
    int found = 0;
    int i;

    printf("Enter the IdVisita of the visita to authorize: ");
    scanf("%d", &IdVisita);
    while (getchar() != '\n');  // Clear the input buffer

    for (i = 0; i < MAX_VISITAS && visitas[i].IdVisita != -1; i++) {
        if (visitas[i].IdVisita == IdVisita) {
            // Display estado options
            printf("Select new estado:\n");
            for (int j = 0; j < num_estados; j++) {
                printf("%d. %s\n", j + 1, estados[j]);
            }

            // Get user selection with validation
            valid_input = 0;
            while (!valid_input) {
                printf("Enter choice (1-%d): ", num_estados);
                if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > num_estados) {
                    printf("Invalid input. Please enter a number between 1 and %d.\n", num_estados);
                    while (getchar() != '\n');  // Clear the input buffer
                } else {
                    valid_input = 1;
                }
            }
            strcpy(visitas[i].estado, estados[escolha - 1]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Visita with IdVisita %d not found.\n", IdVisita);
    } else {
        printf("Visita %d status updated to %s.\n", IdVisita, visitas[i].estado);
    }
}
