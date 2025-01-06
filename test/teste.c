#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Limites para embaixadores e visitas
#define MAX_EMBAIXADORES 100
#define MAX_VISITAS 1000
#define MAX_EMBAIXADORES_POR_VISITA 9

// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[5];
    char nomeCompleto[150];
    int nif;
} Embaixador;

// Estrutura da visita
typedef struct {
    int idVisita;
    int listaEmbaixadores[MAX_EMBAIXADORES_POR_VISITA];
    char estado[25];
    char local[50];
    char data[10];
} Visita;


// Prot�tipo de fun��es do embaixador
void listarEmbaixadores(Embaixador embaixador[], int count);
void consultarEmbaixador(Embaixador embaixador[], int count);
void adicionarEmbaixador(Embaixador embaixador[], int *count, char *ficheiro);
void alterarInfoEmbaixador(Embaixador embaixador[], int count);
void eliminarEmbaixador(Embaixador embaixador[], int *count);

// Prot�tipo de fun��es da visita
void listarVisitas(Visita visita[], int count);
void consultarVisita(Visita visita[], int count);
void adicionarVisita(Visita visita[], int *count, char *ficheiro);
void autorizarVisita(Visita visita[], int count);
void cancelarVisita(Visita visita[], int count);
void confirmarVisita(Visita visita[], int count);
void alterarInfoVisita(Visita visita[], int count);
void eliminarVisita(Visita visita[], int *count);

// Prot�tipo de fun��es adicionais
void mostrarMenu();
void sairMenu();
void cls();
int validarInteiro(const char *argumento);
void carregarEmbaixadores(Embaixador embaixador[], int *count, char *ficheiro);
void carregarVisitas(Visita visita[], int *count, char *ficheiro);
void gravarEmbaixadores(Embaixador embaixador[], int count, char *ficheiro);
void gravarVisitas(Visita visita[], int count, char *ficheiro);


int validarNumeroEstudante();  // Ensure the prototype of this function is declared
int validarInteiro(const char *mensagem);
void validarString(const char *mensagem, char *input, int tamanho);
void validarData(char *data);



int main() {
    // Ficheiros de dado
    char ficheiroEmbaixador[] = "embaixador.csv";
    char ficheiroVisita[] = "visita.csv";

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];
    Visita visita[MAX_VISITAS];

    int embaixadorCount = 0;
    int visitaCount = 0;

    carregarEmbaixadores(embaixador, &embaixadorCount, ficheiroEmbaixador);
    carregarVisitas(visita, &visitaCount, ficheiroVisita);

    int escolha;

    while (true) {
        cls();
        mostrarMenu();

        printf("Selecione a opcao: ");
        escolha = validarInteiro("");

        switch (escolha) {
            case 1:
                listarVisitas(visita, visitaCount);
                break;
            case 2:
                listarEmbaixadores(embaixador, embaixadorCount);
                break;
            case 3:
                consultarVisita(visita, visitaCount);
                break;
            case 4:
                consultarEmbaixador(embaixador, embaixadorCount);
                break;
            case 5:
                adicionarVisita(visita, &visitaCount, ficheiroVisita);
                break;
            case 6:
                adicionarEmbaixador(embaixador, &embaixadorCount, ficheiroEmbaixador);
                break;
            case 7:
                autorizarVisita(visita, visitaCount);
                break;
            case 8:
                cancelarVisita(visita, visitaCount);
                break;
            case 9:
                confirmarVisita(visita, visitaCount);
                break;
            case 10:
                alterarInfoVisita(visita, visitaCount);
                break;
            case 11:
                alterarInfoEmbaixador(embaixador, embaixadorCount);
                break;
            case 12:
                eliminarVisita(visita, &visitaCount);
                break;
            case 13:
                eliminarEmbaixador(embaixador, &embaixadorCount);
                break;
            case 14:
                gravarVisitas(visita, visitaCount, ficheiroVisita);
                printf("Visitas gravadas com sucesso.\n");
                break;
            case 15:
                gravarEmbaixadores(embaixador, embaixadorCount, ficheiroEmbaixador);
                printf("Embaixadores gravados com sucesso.\n");
                break;
            case 16:
                gravarVisitas(visita, visitaCount, ficheiroVisita);
                gravarEmbaixadores(embaixador, embaixadorCount, ficheiroEmbaixador);
                sairMenu();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n');
    }

    return 0;
}


int validarNumeroEstudante() {
    return validarInteiro("Numero de estudante: ");
}


int validarInteiro(const char *mensagem) {
    int numero;
    char buffer[10];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &numero) == 1) {
                return numero;
            } else {
                printf("Entrada invalida. Por favor, insira um numero inteiro.\n");
            }
        }
    }
}



void validarString(const char *mensagem, char *input, int tamanho) {
    while (1) {
        printf("%s", mensagem);
        if (fgets(input, tamanho, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (strlen(input) > 0) {
                return;
            } else {
                printf("Entrada invalida. Por favor, insira uma string nao vazia.\n");
            }
        }
    }
}



void validarData(char *data) {
    while (1) {
        printf("Data (DD/MM/AAAA): ");
        if (fgets(data, 11, stdin) != NULL) {
            data[strcspn(data, "\n")] = '\0'; // Remove newline character
            if (strlen(data) == 10 &&
                isdigit(data[0]) && isdigit(data[1]) && data[2] == '/' &&
                isdigit(data[3]) && isdigit(data[4]) && data[5] == '/' &&
                isdigit(data[6]) && isdigit(data[7]) && isdigit(data[8]) && isdigit(data[9])) {
                return;
            } else {
                printf("Data invalida. Por favor, insira uma data no formato DD/MM/AAAA.\n");
            }
        }
    }
}



void listarEmbaixadores(Embaixador embaixador[], int count) {
    printf("Lista de Embaixadores:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %d, %s, %s, %d\n", i + 1, embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
    }
}


void consultarEmbaixador(Embaixador embaixador[], int count) {
    int numeroEstudante;
    printf("Numero de estudante para consultar: ");
    scanf("%d", &numeroEstudante);
    getchar(); // Clear the input buffer

    for (int i = 0; i < count; i++) {
        if (embaixador[i].numeroEstudante == numeroEstudante) {
            printf("Embaixador encontrado: %d, %s, %s, %d\n", embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
            return;
        }
    }
    printf("Embaixador nao encontrado.\n");
}



void adicionarEmbaixador(Embaixador embaixador[], int *count, char *ficheiro) {
    if (*count >= MAX_EMBAIXADORES) {
        printf("Limite de embaixadores atingido.\n");
        return;
    }
    Embaixador novoEmbaixador;

    // Numero de estudante
    novoEmbaixador.numeroEstudante = validarNumeroEstudante();

    // Escola
    char escolas[][10] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
    int tamanhoEscolas = sizeof(escolas) / sizeof(escolas[0]);
    int escolaSelecionada;

    printf("\nEscolas: \n");
    for (int i = 0; i < tamanhoEscolas; i++) {
        printf("%d. %s\n", i + 1, escolas[i]);
    }

    escolaSelecionada = validarInteiro("Selecione a escola: ");
    while (escolaSelecionada < 1 || escolaSelecionada > tamanhoEscolas) {
        printf("Opcao invalida. ");
        escolaSelecionada = validarInteiro("Selecione a escola: ");
    }

    strcpy(novoEmbaixador.escola, escolas[escolaSelecionada - 1]);

    // Nome completo
    validarString("Nome completo: ", novoEmbaixador.nomeCompleto, sizeof(novoEmbaixador.nomeCompleto));

    // Nif
    novoEmbaixador.nif = validarInteiro("NIF: ");

    // Adicionar embaixador � lista
    embaixador[*count] = novoEmbaixador;
    (*count)++;

    // Verificar os dados
    printf("\nDados inseridos: %d %s %s %d\n", novoEmbaixador.numeroEstudante, novoEmbaixador.escola, novoEmbaixador.nomeCompleto, novoEmbaixador.nif);

    // Gravar dados no ficheiro
    FILE *file = fopen(ficheiro, "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d\n", novoEmbaixador.numeroEstudante, novoEmbaixador.escola, novoEmbaixador.nomeCompleto, novoEmbaixador.nif);
        fclose(file);
        printf("Dados salvos com sucesso\n");
    } else {
        printf("Erro ao abrir o ficheiro.\n");
    }
}




void alterarInfoEmbaixador(Embaixador embaixador[], int count) {
    int numeroEstudante;
    printf("Numero de estudante para alterar informacao: ");
    scanf("%d", &numeroEstudante);
    getchar(); // Clear the input buffer

    for (int i = 0; i < count; i++) {
        if (embaixador[i].numeroEstudante == numeroEstudante) {
            printf("Informe a nova escola: ");
            fgets(embaixador[i].escola, sizeof(embaixador[i].escola), stdin);
            embaixador[i].escola[strlen(embaixador[i].escola) - 1] = '\0';

            printf("Informe o novo nome completo: ");
            fgets(embaixador[i].nomeCompleto, sizeof(embaixador[i].nomeCompleto), stdin);
            embaixador[i].nomeCompleto[strlen(embaixador[i].nomeCompleto) - 1] = '\0';

            printf("Informe o novo NIF: ");
            scanf("%d", &embaixador[i].nif);
            getchar(); // Clear the input buffer

            printf("Informacao do embaixador atualizada.\n");
            return;
        }
    }
    printf("Embaixador nao encontrado.\n");
}


void eliminarEmbaixador(Embaixador embaixador[], int *count) {
    int numeroEstudante;
    printf("Numero de estudante para eliminar: ");
    scanf("%d", &numeroEstudante);
    getchar(); // Clear the input buffer

    for (int i = 0; i < *count; i++) {
        if (embaixador[i].numeroEstudante == numeroEstudante) {
            for (int j = i; j < *count - 1; j++) {
                embaixador[j] = embaixador[j + 1];
            }
            (*count)--;
            printf("Embaixador eliminado.\n");
            return;
        }
    }
    printf("Embaixador nao encontrado.\n");
}


void listarVisitas(Visita visita[], int count) {
    printf("Lista de Visitas:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %d, %s, %s, %s, %s\n", i + 1, visita[i].idVisita, visita[i].listaEmbaixadores, visita[i].estado, visita[i].local, visita[i].data);
    }
}


void consultarVisita(Visita visita[], int count) {
    int idVisita;
    printf("ID da visita para consultar: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < count; i++) {
        if (visita[i].idVisita == idVisita) {
            printf("Visita encontrada: %d, %s, %s, %s, %s\n", visita[i].idVisita, visita[i].listaEmbaixadores, visita[i].estado, visita[i].local, visita[i].data);
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}



void adicionarVisita(Visita visita[], int *count, char *ficheiro) {
    if (*count >= MAX_VISITAS) {
        printf("Limite de visitas atingido.\n");
        return;
    }
    Visita novaVisita;

    // ID da visita
    novaVisita.idVisita = *count + 1; // ID atribu�do automaticamente

    // Inicializar estado da visita
    strcpy(novaVisita.estado, "em planeamento");

    // Lista de embaixadores
    for (int i = 0; i < MAX_EMBAIXADORES_POR_VISITA; i++) {
        novaVisita.listaEmbaixadores[i] = -1; // Inicializando com -1 para indicar embaixadores n�o atribu�dos
    }

    // Local
    validarString("Local da visita: ", novaVisita.local, sizeof(novaVisita.local));

    // Data
    validarData(novaVisita.data);

    // Adicionar visita � lista
    visita[*count] = novaVisita;
    (*count)++;

    // Verificar os dados
    printf("\nDados inseridos: ID: %d, Estado: %s, Local: %s, Data: %s\n", novaVisita.idVisita, novaVisita.estado, novaVisita.local, novaVisita.data);

    // Gravar dados no ficheiro
    FILE *file = fopen(ficheiro, "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s\n", novaVisita.idVisita, novaVisita.listaEmbaixadores, novaVisita.estado, novaVisita.local, novaVisita.data);
        fclose(file);
        printf("Dados salvos com sucesso\n");
    } else {
        printf("Erro ao abrir o ficheiro.\n");
    }
}





void autorizarVisita(Visita visita[], int count) {
    int idVisita;
    printf("ID da visita para autorizar: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < count; i++) {
        if (visita[i].idVisita == idVisita) {
            if (strcmp(visita[i].estado, "em planeamento") == 0) {
                int embaixadoresCount = 0;
                for (int j = 0; j < MAX_EMBAIXADORES_POR_VISITA; j++) {
                    if (visita[i].listaEmbaixadores[j] != -1) {
                        embaixadoresCount++;
                    }
                }

                if (embaixadoresCount >= 2) {
                    strcpy(visita[i].estado, "autorizada");
                    printf("Visita autorizada.\n");
                } else {
                    printf("A visita precisa de pelo menos 2 embaixadores para ser autorizada.\n");
                }
            } else {
                printf("Visita nao pode ser autorizada. Estado atual: %s\n", visita[i].estado);
            }
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}


void cancelarVisita(Visita visita[], int count) {
    int idVisita;
    printf("ID da visita para cancelar: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < count; i++) {
        if (visita[i].idVisita == idVisita) {
            if (strcmp(visita[i].estado, "realizada") != 0) {
                strcpy(visita[i].estado, "cancelada");
                printf("Visita cancelada.\n");
            } else {
                printf("Visita ja realizada nao pode ser cancelada.\n");
            }
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}



void confirmarVisita(Visita visita[], int count) {
    int idVisita;
    printf("ID da visita para confirmar: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < count; i++) {
        if (visita[i].idVisita == idVisita) {
            if (strcmp(visita[i].estado, "autorizada") == 0) {
                printf("Data da visita (DD/MM/AAAA): ");
                char data[10];
                fgets(data, sizeof(data), stdin);
                data[strlen(data) - 1] = '\0';

                if (strcmp(visita[i].data, data) == 0) {
                    strcpy(visita[i].estado, "realizada");
                    printf("Visita confirmada.\n");
                } else {
                    printf("Data da visita nao corresponde. Confirmacao nao realizada.\n");
                }
            } else {
                printf("Visita nao pode ser confirmada. Estado atual: %s\n", visita[i].estado);
            }
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}


void alterarInfoVisita(Visita visita[], int count) {
    int idVisita;
    printf("ID da visita para alterar informacao: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < count; i++) {
        if (visita[i].idVisita == idVisita) {
            printf("Informe o novo estado: ");
            fgets(visita[i].estado, sizeof(visita[i].estado), stdin);
            visita[i].estado[strlen(visita[i].estado) - 1] = '\0';

            printf("Informe o novo local: ");
            fgets(visita[i].local, sizeof(visita[i].local), stdin);
            visita[i].local[strlen(visita[i].local) - 1] = '\0';

            printf("Informe a nova data (DD/MM/AAAA): ");
            fgets(visita[i].data, sizeof(visita[i].data), stdin);
            visita[i].data[strlen(visita[i].data) - 1] = '\0';

            printf("Informacao da visita atualizada.\n");
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}


void eliminarVisita(Visita visita[], int *count) {
    int idVisita;
    printf("ID da visita para eliminar: ");
    idVisita = validarInteiro("");

    for (int i = 0; i < *count; i++) {
        if (visita[i].idVisita == idVisita) {
            for (int j = i; j < *count - 1; j++) {
                visita[j] = visita[j + 1];
            }
            (*count)--;
            printf("Visita eliminada.\n");
            return;
        }
    }
    printf("Visita nao encontrada.\n");
}


void cls() {
    system("cls");
}


void mostrarMenu() {
    // Items do menu
    char menu[][100] = {
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
        "|      15. Gravar Embaixadores                     |",
        "|      16. Sair                                    |",
        "|                                                  |",
        "|__________________________________________________|",
    };

    // Tamanho do menu
    int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);

    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menu[i]);
    }
}


void sairMenu() {
    printf("Saindo do programa...\n");
    exit(0);
}


int validarNumeroEstudante() {
    int numeroEstudante;
    do {
        printf("\nNumero de estudante: ");
        scanf("%d", &numeroEstudante);
        while (getchar() != '\n');
    } while (!numeroEstudante);
    return numeroEstudante;
}


int validarInteiro(const char *argumento) {
    int numero;
    while (1) {
        printf("%s", argumento);
        if (scanf("%d", &numero) == 1) {
            while (getchar() != '\n'); // Clear the input buffer
            return numero;
        } else {
            printf("Dado invalido. Por favor insira um numero\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }
}


void carregarEmbaixadores(Embaixador embaixador[], int *count, char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s.\n", ficheiro);
        return;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%d\n", &embaixador[*count].numeroEstudante, embaixador[*count].escola, embaixador[*count].nomeCompleto, &embaixador[*count].nif) != EOF) {
        (*count)++;
    }
    fclose(file);
}


void carregarVisitas(Visita visita[], int *count, char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s.\n", ficheiro);
        return;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^\n]\n", &visita[*count].idVisita, visita[*count].listaEmbaixadores, visita[*count].estado, visita[*count].local, visita[*count].data) != EOF) {
        (*count)++;
    }
    fclose(file);
}


void gravarEmbaixadores(Embaixador embaixador[], int count, char *ficheiro) {
    FILE *file = fopen(ficheiro, "w");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s.\n", ficheiro);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%d\n", embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
    }
    fclose(file);
}



void gravarVisitas(Visita visita[], int count, char *ficheiro) {
    FILE *file = fopen(ficheiro, "w");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro %s.\n", ficheiro);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n", visita[i].idVisita, visita[i].listaEmbaixadores, visita[i].estado, visita[i].local, visita[i].data);
    }
    fclose(file);
}
