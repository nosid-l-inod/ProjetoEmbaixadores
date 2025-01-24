// Ficheiro: visita.c
// Descrição: Contém funções da visita
// Data: 22-01-2025

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "../include/visita.h"
#include "../include/embaixador.h"
#include "../include/utils.h"


// Inicializar visita
void inicializarVisita(Visita visita[]) {
    for (int i = 0; i < MAX_VISITAS; i++) {
        visita[i].IdVisita = -1;
    }
}

// Adicionar visita
void adicionarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro) {
    int i, j;
    char continuar;

    do {
        // Encontrar o slot vazio
        for (i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == -1) {
                break;
            }
        }

        // Verificar o limite de visitas
        if (i >= MAX_VISITAS) {
            printf("O limite de visitas foi atingido.\n");
            return;
        }

        // Atribuir id automático
        int novoId = (i == 0) ? 1 : visitas[i - 1].IdVisita + 1;
        visitas[i].IdVisita = novoId;

        // Estado da visita
        strcpy(visitas[i].estado, "Em planeamento");

        // Selecionar embaixadores
        printf("Selecione os embaixadores para a visita. (Max. 9)\n");
        listarEmbaixadores(embaixador);

        for (j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            int numeroEstudante = validarNumeroEstudante(embaixador, "Numero do estudante (pressione 0 para parar)");

            if (numeroEstudante <= 0) {
                break;
            }
            visitas[i].listaEmbaixadores[j] = numeroEstudante;
        }

        for (; j < MAX_EMBAIXADORES_VISITA; j++) {
            visitas[i].listaEmbaixadores[j] = -1;
        }

        // Local da visita
        validarPalavra(visitas[i].local, "\nLocal da visita");
        
        // Data
        char data[20];
        validarData(data, "\nData da visita");
        strcpy(visitas[i].data, data);

        // Reservar o próximo slot
        if (i + 1 < MAX_VISITAS) {
            visitas[i + 1].IdVisita = -1;
        }

        // Salvar os dados
        FILE *file = fopen(ficheiro, "w");

        if (file == NULL) {
            printf("Nao e possivel abrir o ficheiro\n");
            return;
        }

        for (int i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == -1) {
                break;
            }
            fprintf(
                file, 
                "%d, %s, %s, %s", 
                visitas[i].IdVisita, 
                visitas[i].estado, 
                visitas[i].local, 
                visitas[i].data
            );

            for (j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                if (visitas[i].listaEmbaixadores[j] == -1) {
                    break;
                }
                fprintf(file, ",%d", visitas[i].listaEmbaixadores[j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("\nVisita adicionada com sucesso.\n");

        // Adicionar mais visitas ou não
        printf("\nDeseja adicionar mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');
        cls();

    } while (continuar == 's' || continuar == 'S');
}

// Listar visitas
void listarVisitas(Visita visita[]) {

    // Ordenar visita por ID em ordem decrescente
    qsort(visita, MAX_VISITAS, sizeof(Visita), compararVisitasPorID);

    int totalVisitas = 0;
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    printf("| %-6s | %-19s | %-20s | %-19s | %-17s |\n", "ID", "Estado", "Local", "Data", "Embaixadores");
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");

    // Iterar sobre todas as visita
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visita[i].IdVisita == -1) {
            break;
        }

        totalVisitas++;
        printf("| %-6d | %-19s | %-20s | %-19s | ", 
            visita[i].IdVisita, 
            visita[i].estado, 
            visita[i].local, 
            visita[i].data
        );

        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            if (visita[i].listaEmbaixadores[j] == -1) {
                break;
            }
            printf("%d ", visita[i].listaEmbaixadores[j]);
        }
        printf("|\n");
        printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    }

    // Imprimir total de visita por estado
    printf("\nTotal de visita: %d\n", totalVisitas);

    // Contar visita por estado
    int visitasPlanejamento = 0;
    int visitasConcluidas = 0;

    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visita[i].IdVisita == -1) {
            break;
        }
        if (strcmp(visita[i].estado, "Em planeamento") == 0) {
            visitasPlanejamento++;
        } else if (strcmp(visita[i].estado, "Concluida") == 0) {
            visitasConcluidas++;
        }
    }

    printf("\nVisitas em planeamento: %d\n", visitasPlanejamento);
    printf("Visitas concluídas: %d\n", visitasConcluidas);
}

// Consultar visita específica
void consultarVisita(Visita visitas[], Embaixador embaixador[]) {
    int idVisita;
    int encontrado = 0;

    // Mostrar a lista de visitas
    listarVisitas(visitas);

    printf("Insira o ID da visita que deseja consultar: ");
    scanf("%d", &idVisita);
    while (getchar() != '\n');

    // Procurar a visita por ID
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == idVisita) {
            encontrado = 1;

            printf("\nDetalhes da Visita:\n");
            printf("ID: %d\n", visitas[i].IdVisita);
            printf("Estado: %s\n", visitas[i].estado);
            printf("Local: %s\n", visitas[i].local);
            printf("Data: %s\n", visitas[i].data);
            printf("Embaixadores:\n");

            for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                if (visitas[i].listaEmbaixadores[j] == -1) {
                    break;
                }
                // Encontrar detalhes do embaixador correspondente
                for (int k = 0; k < MAX_EMBAIXADORES; k++) {
                    if (embaixador[k].numeroEstudante == visitas[i].listaEmbaixadores[j]) {
                        printf("  - %s (Número: %d, Escola: %s, NIF: %s)\n",
                            embaixador[k].nomeCompleto,
                            embaixador[k].numeroEstudante,
                            embaixador[k].escola,
                            embaixador[k].nif
                        );
                        break;
                    }
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("\nVisita com ID %d nao encontrada.\n", idVisita);
    }
}

// Autorizar visita
void autorizarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro) {
    int idVisita;
    int encontrado = 0;

    // Mostrar a lista de visitas
    listarVisitas(visitas);
    
    printf("Insira o ID da visita que deseja autorizar: ");
    scanf("%d", &idVisita);
    while (getchar() != '\n');

    // Procurar a visita com o ID fornecido
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == idVisita) {
            encontrado = 1;

            // Verificar se a visita está em em planeamento
            if (strcmp(visitas[i].estado, "Em planeamento") != 0) {
                printf("A visita nao está em planeamento e nao pode ser autorizada.\n");
                return;
            }

            // Contar o número de embaixadores atribuídos à visita
            int numEmbaixadores = 0;
            for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                if (visitas[i].listaEmbaixadores[j] != -1) {
                    numEmbaixadores++;
                }
            }

            // Verificar se a visita tem pelo menos 2 embaixadores
            if (numEmbaixadores < 2) {
                printf("A visita deve ter no minimo 2 embaixadores para ser autorizada.\n");
                return;
            }

            // Autorizar a visita
            strcpy(visitas[i].estado, "Autorizada");

            // Salvar as alterações no ficheiro
            FILE *file = fopen(ficheiro, "w");

            if (file == NULL) {
                printf("Nao e possivel abrir o ficheiro\n");
                return;
            }

            for (int i = 0; i < MAX_VISITAS; i++) {
                if (visitas[i].IdVisita == -1) {
                    break;
                }
                fprintf(
                    file, 
                    "%d, %s, %s, %s", 
                    visitas[i].IdVisita, 
                    visitas[i].estado, 
                    visitas[i].local, 
                    visitas[i].data
                );

                for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                    if (visitas[i].listaEmbaixadores[j] == -1) {
                        break;
                    }
                    fprintf(file, ",%d", visitas[i].listaEmbaixadores[j]);
                }
                fprintf(file, "\n");
            }
            fclose(file);

            printf("Visita com ID %d autorizada com sucesso.\n", idVisita);
            return;
        }
    }

    if (!encontrado) {
        printf("Visita com ID %d nao encontrada.\n", idVisita);
    }
}

// Cancelar visita
void cancelarVisita(Visita visitas[], const char *ficheiro) {
    int idVisita;
    int encontrado = 0;

    // Listar todas as visitas
    listarVisitas(visitas);

    printf("Insira o ID da visita que deseja cancelar: ");
    scanf("%d", &idVisita);
    while (getchar() != '\n');

    // Procurar a visita com o ID fornecido
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == idVisita) {
            encontrado = 1;

            // Verificar se a visita está em "Concluída"
            if (strcmp(visitas[i].estado, "Concluida") == 0) {
                printf("A visita não pode ser cancelada porque já foi concluída.\n");
                return;
            }

            // Cancelar a visita
            strcpy(visitas[i].estado, "Cancelada");

            // Salvar as alterações no ficheiro
            FILE *file = fopen(ficheiro, "w");
            if (file == NULL) {
                printf("Não é possível abrir o ficheiro\n");
                return;
            }
            for (int i = 0; i < MAX_VISITAS; i++) {
                if (visitas[i].IdVisita == -1) {
                    break;
                }
                fprintf(
                    file, 
                    "%d, %s, %s, %s", 
                    visitas[i].IdVisita, 
                    visitas[i].estado, 
                    visitas[i].local, 
                    visitas[i].data
                );

                for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                    if (visitas[i].listaEmbaixadores[j] == -1) {
                        break;
                    }
                    fprintf(file, ",%d", visitas[i].listaEmbaixadores[j]);
                }
                fprintf(file, "\n");
            }
            fclose(file);

            printf("Visita com ID %d cancelada com sucesso.\n", idVisita);
            return;
        }
    }

    if (!encontrado) {
        printf("Visita com ID %d não encontrada.\n", idVisita);
    }
}

// Confirmar realização da visita
void confirmarRealizacaoVisita(Visita visitas[], const char *ficheiro) {
    int idVisita;
    int encontrado;
    char continuar;

    do {
        encontrado = 0;
        listarVisitas(visitas);

        printf("Insira o ID da visita que deseja confirmar como realizada: ");
        scanf("%d", &idVisita);
        while (getchar() != '\n');

        // Procurar a visita com o ID fornecido
        for (int i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == idVisita) {
                encontrado = 1;

                // Verificar se a visita está autorizada
                if (strcmp(visitas[i].estado, "Autorizada") != 0) {
                    printf("A visita nao esta autorizada e nao pode ser confirmada como realizada.\n");
                    continue;
                }

                // Verificar se a data da visita é anterior à data atual
                if (!validarDataAnterior(visitas[i].data)) {
                    printf("A data da visita nao e anterior a data atual.\n");
                    continue;
                }

                // Confirmar a realização da visita
                strcpy(visitas[i].estado, "Concluida");

                // Salvar as alterações no ficheiro
                FILE *file = fopen(ficheiro, "w");

                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                    return;
                }

                for (int i = 0; i < MAX_VISITAS; i++) {
                    if (visitas[i].IdVisita == -1) {
                        break;
                    }
                    fprintf(
                        file, 
                        "%d, %s, %s, %s", 
                        visitas[i].IdVisita, 
                        visitas[i].estado, 
                        visitas[i].local, 
                        visitas[i].data
                    );

                    for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                        if (visitas[i].listaEmbaixadores[j] == -1) {
                            break;
                        }
                        fprintf(file, ",%d", visitas[i].listaEmbaixadores[j]);
                    }
                    fprintf(file, "\n");
                }
                fclose(file);

                printf("Visita com ID %d confirmada como realizada com sucesso.\n", idVisita);
                break;
            }
        }

        if (!encontrado) {
            printf("Visita com ID %d nao encontrada.\n", idVisita);
        }

        printf("\nDeseja confirmar a realizacao de mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');

    } while (continuar == 's' || continuar == 'S');
}

// Alterar informação da visita
void alterarInformacaoVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro) {
    int idVisita;
    int encontrado = 0;
    char continuar;

    do {
        // Listar todas as visitas
        listarVisitas(visitas);

        printf("Insira o ID da visita que deseja alterar: ");
        scanf("%d", &idVisita);
        while (getchar() != '\n');

        // Procurar a visita com o ID fornecido
        for (int i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == idVisita) {
                encontrado = 1;

                // Mostrar as opções para alterar a visita
                int opcao;

                printf("Escolha o que deseja alterar:\n");
                printf("1. Lista de embaixadores\n");
                printf("2. Estado da visita\n");
                printf("3. Local\n");
                printf("4. Data\n");
                printf("5. Sair\n");
                printf("Opção: ");
                scanf("%d", &opcao);
                while (getchar() != '\n');

                switch (opcao) {
                    case 1:
                        // Alterar lista de embaixadores
                        printf("Selecione os embaixadores para a visita. (Max. 9)\n");
                        listarEmbaixadores(embaixador);

                        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                            int numeroEstudante = validarNumeroEstudante(embaixador, "Numero do estudante (pressione 0 para parar)");

                            if (numeroEstudante <= 0) {
                                break;
                            }

                            visitas[i].listaEmbaixadores[j] = numeroEstudante;
                        }

                        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                            visitas[i].listaEmbaixadores[j] = -1;
                        }
                        break;

                    case 2:
                        // Alterar estado da visita
                        printf("Estados disponiveis: Em planeamento, Autorizada, Cancelada, Concluida\n");
                        printf("Insira o novo estado da visita: ");

                        char estado[20];
                        validarPalavra(estado, "Estado da visita");
                        strcpy(visitas[i].estado, estado);
                        break;

                    case 3:
                        // Alterar local da visita
                        validarPalavra(visitas[i].local, "\nNovo local da visita");
                        break;

                    case 4:
                        // Alterar data da visita
                        {
                            char data[20];
                            validarData(data, "\nNova data da visita");
                            strcpy(visitas[i].data, data);
                        }
                        break;

                    case 5:
                        // Sair
                        return;

                    default:
                        printf("Opcao invalida.\n");
                        continue;
                }

                // Salvar as alterações no ficheiro
                FILE *file = fopen(ficheiro, "w");
                if (file == NULL) {
                    printf("Nao e possível abrir o ficheiro\n");
                    return;
                }
                for (int k = 0; k < MAX_VISITAS; k++) {
                    if (visitas[k].IdVisita == -1) {
                        break;
                    }
                    fprintf(
                        file, 
                        "%d, %s, %s, %s", 
                        visitas[k].IdVisita, 
                        visitas[k].estado, 
                        visitas[k].local, 
                        visitas[k].data
                    );

                    for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                        if (visitas[k].listaEmbaixadores[j] == -1) {
                            break;
                        }
                        fprintf(file, ",%d", visitas[k].listaEmbaixadores[j]);
                    }
                    fprintf(file, "\n");
                }
                fclose(file);

                printf("Informacao da visita com ID %d alterada com sucesso.\n", idVisita);
                break;
            }
        }

        if (!encontrado) {
            printf("Visita com ID %d não encontrada.\n", idVisita);
        }

        printf("\nDeseja alterar a informação de mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); 

    } while (continuar == 's' || continuar == 'S');
}

// Eliminar visita
void eliminarVisita(Visita visitas[], const char *ficheiro) {
    int idVisita;
    int encontrado = 0;
    char continuar;

    do {
        // Listar visitas
        listarVisitas(visitas);

        printf("Insira o ID da visita que deseja eliminar: ");
        scanf("%d", &idVisita);
        while (getchar() != '\n'); 

        // Procurar a visita com o ID fornecido
        for (int i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == idVisita) {
                encontrado = 1;

                // Verificar se a visita está em "Concluída"
                if (strcmp(visitas[i].estado, "Concluida") == 0) {
                    printf("A visita nao pode ser eliminada porque ja foi concluida.\n");
                    continue;  
                }

                // Eliminar a visita (marcar como removida)
                visitas[i].IdVisita = -1;
                strcpy(visitas[i].estado, "");
                strcpy(visitas[i].local, "");
                strcpy(visitas[i].data, "");
                for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                    visitas[i].listaEmbaixadores[j] = -1;
                }

                // Salvar as alterações no ficheiro
                FILE *file = fopen(ficheiro, "w");
                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                    return;
                }
                for (int k = 0; k < MAX_VISITAS; k++) {
                    if (visitas[k].IdVisita == -1) {
                        continue;
                    }
                    fprintf(
                        file, 
                        "%d, %s, %s, %s", 
                        visitas[k].IdVisita, 
                        visitas[k].estado, 
                        visitas[k].local, 
                        visitas[k].data
                    );

                    for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                        if (visitas[k].listaEmbaixadores[j] == -1) {
                            break;
                        }
                        fprintf(file, ",%d", visitas[k].listaEmbaixadores[j]);
                    }
                    fprintf(file, "\n");
                }
                fclose(file);

                printf("Visita com ID %d eliminada com sucesso.\n", idVisita);
                break;
            }
        }

        if (!encontrado) {
            printf("Visita com ID %d não encontrada.\n", idVisita);
        }

        printf("\nDeseja eliminar mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); // Limpar o buffer

    } while (continuar == 's' || continuar == 'S');
}

// Validar data da visita
int validarDataAnterior(const char *data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    struct tm tm_visita = {0};
    tm_visita.tm_mday = dia;
    tm_visita.tm_mon = mes - 1;
    tm_visita.tm_year = ano - 1900; 

    time_t t = time(NULL);
    struct tm *tm_atual = localtime(&t);

    if (mktime(&tm_visita) < mktime(tm_atual)) {
        return 1;
    }
    return 0;
}

// Comparar visitas por ID (para ordenação)
int compararVisitasPorID(const void *a, const void *b) {
    Visita *visitaA = (Visita *)a;
    Visita *visitaB = (Visita *)b;

    return visitaB->IdVisita - visitaA->IdVisita;
}

// Carregar visitas do ficheiro para o vetor
void carregarVisita(Visita visitas[], const char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Não é possível abrir o ficheiro\n");
        return;
    }

    char buffer[256];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // Ignorar linhas vazias
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            continue;
        }

        // Limpar o buffer de embaixadores
        memset(visitas[i].listaEmbaixadores, -1, sizeof(visitas[i].listaEmbaixadores));

        sscanf(
            buffer, 
            "%d, %[^,], %[^,], %[^,]", 
            &visitas[i].IdVisita, 
            visitas[i].estado, 
            visitas[i].local, 
            visitas[i].data
        );

        char *token = strtok(buffer, ",");
        int j = 0;
        
        // Ignorar os primeiros 4 tokens (IdVisita, estado, local, data)
        for (int k = 0; k < 4 && token != NULL; k++) {
            token = strtok(NULL, ",");
        }

        // Adicionar embaixadores à lista
        while (token != NULL && j < MAX_EMBAIXADORES_VISITA) {
            visitas[i].listaEmbaixadores[j] = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;

        // Verificar o limite de visitas
        if (i >= MAX_VISITAS) {
            break;
        }
    }

    // Reservar o próximo slot
    if (i < MAX_VISITAS) {
        visitas[i].IdVisita = -1;
    }

    fclose(file);
}

