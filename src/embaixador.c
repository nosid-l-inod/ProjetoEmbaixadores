// Ficheiro: embaixador.c
// Descrição: Contém funções do embaixador
// Data: 22-01-2025

#include <stdio.h>
#include <string.h>
#include "../include/embaixador.h"
#include "../include/utils.h"


// Listar embaixadores
void listarEmbaixadores(Embaixador embaixador[]) {
    // Ordenar embaixadores
    ordenarEmbaixadoresNome(embaixador);

    printf("+-----------------+--------+--------------------------------------------+-----------+\n");
    printf("| %-15s | %-6s | %-42s | %-9s |\n", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+-----------------+--------+--------------------------------------------+-----------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-15d | %-6s | %-42s | %-9s |\n", 
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        printf("+-----------------+--------+--------------------------------------------+-----------+\n");
    }
}

// Consultar embaixador (Por Numero de estudante)
void consultarEmbaixador(Embaixador embaixador[]) {
    int index;
    int encontrado = 0;
    char continuar;

    do {
        cls();
        listarEmbaixadoresIndex(embaixador);

        printf("\nNumero do embaixador a consultar: ");
        scanf("%d", &index);
        cls();

        index = index - 1;

        printf("Detalhes do embaixador\n\n");
        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n",
                index + 1,
                embaixador[index].numeroEstudante,
                embaixador[index].escola,
                embaixador[index].nomeCompleto,
                embaixador[index].nif
            );
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            encontrado = 1;
        }
        else {
            printf("Embaixador nao encontrado.\n");
        }

        printf("\nDeseja consultar mais embaixadores? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

// Adicionar embaixador
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    int i;

    // Encontrar o slot vazio
    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
    }

    // Verificar o limite de embaixadores
    if (i >= MAX_EMBAIXADORES) {
        printf("O limite de embaixadores foi atingido.\n");
        return;
    }

    // Numero de estudante
    int numeroEstudante;
    numeroEstudante = validarNumero(embaixador, "Numero de estudante");
    embaixador[i].numeroEstudante = numeroEstudante;

    // Escola
    const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
    int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);
    int escolha;

    // Mostrar escolas
    printf("\nEscolas disponiveis: \n");
    for (int j = 0; j < tamanhoEscola; j++) {
        printf("%d. %s\n", j + 1, escolas[j]);
    }
    
    // Selecionar escola
    int valido = 0;

    while (!valido) {
        printf("\nInsira a escola (1-%d): ", tamanhoEscola);

        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
            printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", tamanhoEscola);
            while (getchar() != '\n');
        } 
        else {
            valido = 1;
        }
    }

    // Adicionar escola
    strcpy(embaixador[i].escola, escolas[escolha - 1]);
    while (getchar() != '\n');

    // Nome completo
    char nomeCompleto[150];
    validarPalavra(nomeCompleto, "\nNome completo");
    capitalizarNome(nomeCompleto);
    strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

    // NIF
    char nif[10];
    validarNif(embaixador ,nif, "NIF");
    strcpy(embaixador[i].nif, nif);

    // Reservar o próximo slot
    if (i + 1 < MAX_EMBAIXADORES) {
        embaixador[i + 1].numeroEstudante = -1;
    }

    // Salvar os dados no ficheiro
    FILE *file = fopen(ficheiro, "w");

    if (file == NULL) {
        printf("Nao e possivel abrir o ficheiro\n");
        return;
    }

    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
        fprintf(
            file, 
            "%d, %s, %s, %s\n", 
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
    }
    fclose(file);
    
    printf("\n%s registado com sucesso.", embaixador[i].nomeCompleto);
}

// Alterar informações do embaixador
void alterarInfoEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    char continuar;

    do {
        // Mostrar embaixadores
        printf("Embaixadores:\n");
        listarEmbaixadoresIndex(embaixador);

        int index;
        printf("\nSelecione o embaixador (1-%d): ", MAX_EMBAIXADORES);
        scanf("%d", &index);
        while (getchar() != '\n');
        index -= 1;

        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {
            cls();

            printf("Detalhes do embaixador:\n");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
                index + 1,
                embaixador[index].numeroEstudante,
                embaixador[index].escola,
                embaixador[index].nomeCompleto,
                embaixador[index].nif
            );
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

            printf("\nDeseja alterar alguma informacao do/a %s? (S/N): ", embaixador[index].nomeCompleto);
            scanf(" %c", &continuar);

            if (continuar == 's' || continuar == 'S') {
                do {
                    printf("\nQual campo deseja alterar?\n");
                    printf("1. Numero de estudante\n");
                    printf("2. Escola\n");
                    printf("3. Nome completo\n");
                    printf("4. NIF\n");
                    printf("\nSelecione a informacao que deseja alterar: ");

                    int alterar;
                    scanf("%d", &alterar);
                    while (getchar() != '\n');
                    cls();

                    switch (alterar) {
                        case 1:
                            embaixador[index].numeroEstudante = validarNumero(embaixador, "Novo numero de estudante");
                            break;
                        case 2: {
                            const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
                            int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);

                            printf("\nEscolas disponiveis:\n");
                            for (int j = 0; j < tamanhoEscola; j++) {
                                printf("%d. %s\n", j + 1, escolas[j]);
                            }

                            int escolha;

                            while (1) {
                                printf("\nSelecione a nova escola: ");

                                if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
                                    printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", tamanhoEscola);
                                    while (getchar() != '\n');
                                } 
                                else {
                                    strcpy(embaixador[index].escola, escolas[escolha - 1]);
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            validarPalavra(embaixador[index].nomeCompleto, "Novo nome completo");
                            capitalizarNome(embaixador[index].nomeCompleto);
                            break;
                        case 4:
                            validarNif(embaixador, embaixador[index].nif, "Novo NIF");
                            break;
                        default:
                            printf("Escolha invalida.\n");
                            continue;
                    }

                    cls();
                    printf("Detalhes atualizados do embaixador:\n");
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
                    printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
                    printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
                        index + 1,
                        embaixador[index].numeroEstudante,
                        embaixador[index].escola,
                        embaixador[index].nomeCompleto,
                        embaixador[index].nif
                    );
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

                    printf("\nDeseja alterar mais alguma informacao? (S/N): ");
                    scanf(" %c", &continuar);
                } while (continuar == 's' || continuar == 'S');

                // Atualizar os dados no ficheiro
                FILE *file = fopen(ficheiro, "w");

                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                } 
                else {
                    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                        if (embaixador[i].numeroEstudante == -1) {
                            break;
                        }

                        fprintf(
                            file,
                            "%d, %s, %s, %s\n",
                            embaixador[i].numeroEstudante,
                            embaixador[i].escola,
                            embaixador[i].nomeCompleto,
                            embaixador[i].nif
                        );
                    }
                    fclose(file);
                }
                printf("Embaixador atualizado com sucesso\n");
            } 
            else {
                printf("Nenhuma informacao alterada.\n");
            }
        } 
        else {
            printf("Embaixador nao encontrado.\n");
        }

        printf("Deseja alterar outro embaixador? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
}

// Eliminar embaixador
void eliminarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    int index, found = 0;
    char continuar;
    char confirmar;

    do {
        listarEmbaixadoresIndex(embaixador);

        printf("\nNumero do embaixador a remover: ");
        scanf("%d", &index);
        while (getchar() != '\n');
        index -= 1;

        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {

            printf("Remover este embaixador? (S/N): ");
            scanf(" %c", &confirmar);
            while (getchar() != '\n');

            if (confirmar == 's' || confirmar == 'S') {
                for (int i = index; i < MAX_EMBAIXADORES - 1 && embaixador[i].numeroEstudante != -1; i++) {
                    embaixador[i] = embaixador[i + 1];
                }

                embaixador[MAX_EMBAIXADORES - 1].numeroEstudante = -1;
                found = 1;

                // Salvar as alterações no ficheiro
                FILE *file = fopen(ficheiro, "w");
                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                } 
                else {
                    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                        if (embaixador[i].numeroEstudante == -1) {
                            break;
                        }
                        fprintf(
                            file,
                            "%d, %s, %s, %s\n",
                            embaixador[i].numeroEstudante,
                            embaixador[i].escola,
                            embaixador[i].nomeCompleto,
                            embaixador[i].nif
                        );
                    }
                    fclose(file);
                    printf("\nEmbaixador removido com sucesso.\n");
                }
            } 
            else {
                printf("Embaixador nao removido\n");
            }
        } 
        else {
            printf("Embaixador nao encontrado.\n");
        }

        printf("Deseja remover outro embaixador? (S/N): ");
        scanf(" %c", &continuar);
        cls();

    } while (continuar == 's' || continuar == 'S');

    if (!found) {
        printf("Nenhum embaixador foi removido.\n");
    }
}

// Inicializar embaixador
void inicializarEmbaixador(Embaixador embaixador[]) {
    int i;

    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        embaixador[i].numeroEstudante = -1;
    }
}

// Carregar embaixadores do ficheiro para o vetor
void carregarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Nao e possivel abrir o ficheiro\n");
        return;
    }

    char buffer[256];
    int i = 0;

    // Carregar os dados
    while (fgets(buffer, sizeof(buffer), file) && i < MAX_EMBAIXADORES) {
        sscanf(
            buffer, 
            "%d, %[^,], %[^,], %s", 
            &embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        i++;
    }
    
    // Reservar o proximo slot
    if (i < MAX_EMBAIXADORES) {
        embaixador[i].numeroEstudante = -1;
    }
    
    fclose(file);
}

// Listar embaixador e posição no vetor
void listarEmbaixadoresIndex(Embaixador embaixador[]) {

    // Ordenar embaixador por nome
    ordenarEmbaixadoresNome(embaixador);

    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
    printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
            i + 1,
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
    }
}

// Ordenar embaixadores por nome
void ordenarEmbaixadoresNome(Embaixador embaixador[]) {
    for (int i = 0; i < MAX_EMBAIXADORES - 1 && embaixador[i].numeroEstudante != -1; i++) {
        for (int j = i + 1; j < MAX_EMBAIXADORES && embaixador[j].numeroEstudante != -1; j++) {
            if (strcmp(embaixador[i].nomeCompleto, embaixador[j].nomeCompleto) > 0) {
                Embaixador temp = embaixador[i];
                embaixador[i] = embaixador[j];
                embaixador[j] = temp;
            }
        }
    }
}

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
