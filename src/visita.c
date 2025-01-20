// Filename: visita.c

#include "../include/visita.h"
#include "../include/embaixador.h"
#include "../include/utils.h"

// Inicializar visita
void inicializarVisita(Visita visitas[]) {
    for (int i = 0; i < MAX_VISITAS; i++) {
        visitas[i].IdVisita = -1;
    }
}

// Adicionar visita
// Verificar se o número do estudante existe
int embaixadorExiste(Embaixador embaixador[], int numeroEstudante) {
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
        if (embaixador[i].numeroEstudante == numeroEstudante) {
            return 1; // Embaixador existe
        }
    }
    return 0; // Embaixador não existe
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
        printf("Selecione os embaixadores para a visita (max %d). Pressione 0 para parar.\n", MAX_EMBAIXADORES_VISITA);
        listarEmbaixadoresIndex(embaixador);

        for (j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            int indiceEmbaixador;
            
            printf("Selecione o embaixador %d: ", j + 1);
            scanf("%d", &indiceEmbaixador);
            while (getchar() != '\n'); // Limpar o buffer

            if (indiceEmbaixador == 0) {
                break;
            }

            indiceEmbaixador -= 1; // Ajustar para índice baseado em 0

            // Verificar se o índice do embaixador é válido
            if (indiceEmbaixador < 0 || indiceEmbaixador >= MAX_EMBAIXADORES || embaixador[indiceEmbaixador].numeroEstudante == -1) {
                printf("Índice de embaixador inválido. Tente novamente.\n");
                j--; // Permitir que o usuário tente novamente
            } else {
                visitas[i].listaEmbaixadores[j] = embaixador[indiceEmbaixador].numeroEstudante;
            }
        }

        for (; j < MAX_EMBAIXADORES_VISITA; j++) {
            visitas[i].listaEmbaixadores[j] = -1;
        }

        // Local da visita
        printf("Local da visita: ");
        fgets(visitas[i].local, sizeof(visitas[i].local), stdin);
        visitas[i].local[strcspn(visitas[i].local, "\n")] = '\0';

        // Data
        char data[20];
        validarData(data, "Data da visita");
        strcpy(visitas[i].data, data);

        // Reservar o próximo slot
        if (i + 1 < MAX_VISITAS) {
            visitas[i + 1].IdVisita = -1;
        }

        // Salvar os dados no ficheiro
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

        // Perguntar se deseja adicionar mais visitas
        printf("\nDeseja adicionar mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); // Limpar o buffer

    } while (continuar == 's' || continuar == 'S');
}

// Listar visita
int compararVisitasPorID(const void *a, const void *b) {
    Visita *visitaA = (Visita *)a;
    Visita *visitaB = (Visita *)b;

    return visitaB->IdVisita - visitaA->IdVisita;
}

// Listar visitas
void listarVisitas(Visita visitas[]) {
    // Ordenar visitas por ID em ordem decrescente
    qsort(visitas, MAX_VISITAS, sizeof(Visita), compararVisitasPorID);

    int totalVisitas = 0;
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    printf("| %-6s | %-19s | %-20s | %-19s | %-17s |\n", "ID", "Estado", "Local", "Data", "Embaixadores");
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");

    // Iterar sobre todas as visitas
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }

        totalVisitas++;
        printf("| %-6d | %-19s | %-20s | %-19s | ", 
            visitas[i].IdVisita, 
            visitas[i].estado, 
            visitas[i].local, 
            visitas[i].data
        );

        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            if (visitas[i].listaEmbaixadores[j] == -1) {
                break;
            }
            printf("%d ", visitas[i].listaEmbaixadores[j]);
        }
        printf("|\n");
        printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    }

    // Imprimir total de visitas por estado
    printf("\nTotal de visitas: %d\n", totalVisitas);

    // Contar visitas por estado
    int visitasPlanejamento = 0;
    int visitasConcluidas = 0;

    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }
        if (strcmp(visitas[i].estado, "Em planeamento") == 0) {
            visitasPlanejamento++;
        } else if (strcmp(visitas[i].estado, "Concluída") == 0) {
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

    printf("Digite o ID da visita que deseja consultar: ");
    scanf("%d", &idVisita);
    while (getchar() != '\n'); // Limpar o buffer

    // Procurar a visita com o ID fornecido
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
        printf("\nVisita com ID %d não encontrada.\n", idVisita);
    }
}
