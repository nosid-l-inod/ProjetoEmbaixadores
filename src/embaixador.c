// Filename: embaixador.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/embaixador.h"


// Carregar dados do ficheiro
void carregarDados(Embaixador embaixador[], const char *pFicheiro) {

    // Abrir o ficheiro
    FILE *file = fopen(pFicheiro, "r");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro");
        return;
    }
    else {

        // Criar variavel para guardar cada linha no ficheiro
        char linha[255];
        int i = 0;

        // Saltar o cabeçalho
        fgets(linha, sizeof(linha), file);

        // Carregar os dados para a estrutura de dados
        while (fgets(linha, sizeof(linha), file) != NULL) {
            sscanf(linha, "%d, %[^,], %[^,], %s", &embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
            i++;
        }

        if (i < MAX_EMBAIXADORES) {
            embaixador[i].numeroEstudante = -1;
        }

        fclose(file);
    }
     
}


// Salvar dados no ficheiro
void salvarDados(Embaixador embaixador[], const char *pFicheiro) {

    // Abrir ficheiro
    FILE *file = fopen(pFicheiro, "a");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");
    }
    else {

        for (int i = 0; i < MAX_EMBAIXADORES; i++) {

            // Parar se não houver conteúdos para ler
            if (embaixador[i].numeroEstudante == -1) {
                break;
            }
            
            // Êscrever os dados no ficheiro
            fprintf(file, "%d, %s, %s, %s\n", embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
        }
    }

    fclose(file);
}


// Validar numeros
int validarInteiro(const char *argumento) {
    
    int valido = 0;
    int numero;

    // Pedir os dados enquanto forem inválidos
    while (!valido) {
        printf("%s", argumento);

        if (scanf("%d", &numero) != 1) {
            printf("Dado invalido. Por favor insira um numero\n");
            while (getchar() != '\n');
        }
        else {
            valido = 1;
        }
    }
    return numero;
}


// Validar nome
void validarNome(char *nome, const char *prompt) {
    int valido = 0;

    while (!valido) {
        printf("%s", prompt);

        // Read the input
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';  // Remove the newline character

        valido = 1;
        for (int i = 0; nome[i] != '\0'; i++) {
            if (!isalpha(nome[i]) && nome[i] != ' ') {
                printf("O nome e invalido. Por favor insira um nome sem numeros ou caracteres especiais.\n");
                valido = 0;
                break;
            }
        }

        if (strlen(nome) == 0) {
            printf("O nome e invalido. O nome nao pode ser vazio.\n");
            valido = 0;
        }
    }
}


// Validar NIF
void validarNif(char *nif, const char *valor) {

    int valido = 0;
    
    while (!valido) {
        printf("%s", valor);

        fgets(nif, 10, stdin);
        nif[strcspn(nif, "\n")] = '\0';

        valido = 1;

        // Verificar se o tamanho
        if (strlen(nif) != 9) {
            valido = 0;
            printf("O NIF e invalido. Por favor insira um  valido, com 9 caracteres.\n");
        } 
        else {
            for (int i = 0; nif[i] != '\0'; i++) {
                if (!isdigit(nif[i])) {
                    printf("Nif inválido. Insira apenas numeros.\n");
                    valido = 0;
                    break;
                }
            }
        }
    }
}


// Capitalizar os nomes
void capitalizarNomes(char *name) {

    int palavras = 0;
    
    for (int i = 0; name[i] != '\0'; i++) {
        if (!palavras && isalpha(name[i])) {
            name[i] = toupper(name[i]);
            palavras = 1;
        } 
        else if (palavras && isalpha(name[i])) {
            name[i] = tolower(name[i]);
        }
        else {
            palavras = 0;
        }
    }
}


// Ordenar embaixadores por nome
void ordenarEmbaixadores(Embaixador embaixador[]) {

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


// AdicionarEmbaixador
void adicionarEmbaixador(Embaixador embaixador[]) {
    
    int i, escolha, numeroEstudante;
    char nomeCompleto[100];
    char nif[10];
    int valid_input = 0;

    // Escolas disponiveis
    const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
    int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);

    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
    }

    // Verificar o limite de embaixadores
    if (i >= MAX_EMBAIXADORES) {
        printf("O limite de embaixadores foi atingido\n");
        return;
    }

    // Pedir numero de estudante
    numeroEstudante = validarInteiro("Numero de estudante: ");
    embaixador[i].numeroEstudante = numeroEstudante;

    // Mostar as escolas disponiveis
    printf("\nEscolas:\n");
    for (int j = 0; j < tamanhoEscola; j++) {
        printf("%d. %s\n", j + 1, escolas[j]);
    }

    // Pedir a escola
    valid_input = 0;

    while (!valid_input) {
        printf("\nSelecione a escola: (1-%d): ", tamanhoEscola);
        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
            printf("Opcao invalida. Por favor escolha um numero entre 1 and %d.\n", tamanhoEscola);
            while (getchar() != '\n');
        } else {
            valid_input = 1;
        }
    }

    // Inserir escola no vetor 
    strcpy(embaixador[i].escola, escolas[escolha - 1]);
    while (getchar() != '\n');

    // Nome completo
    printf("Nome completo: ");
    fgets(nomeCompleto, 100, stdin);
    nomeCompleto[strcspn(nomeCompleto, "\n")] = '\0';
    capitalizarNomes(nomeCompleto);
    strcpy(embaixador[i].nomeCompleto, nomeCompleto);

    // Capitalizar e inserir o nome na estrutura
    capitalizarNomes(nomeCompleto);
    strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

    // Pedir e validar NIF
    validarNif(nif, "\nInsira o NIF: ");
    strcpy(embaixador[i].nif, nif);

    if (i + 1 < MAX_EMBAIXADORES) {
        embaixador[i + 1].numeroEstudante = -1;
    }
}


// Mostrar  embaixador
void listarEmbaixador(Embaixador embaixador[]) {
    ordenarEmbaixadores(embaixador); 
    printf("Embaixadores\n");
    printf("+-----------------+-------+--------------------+---------+\n");
    printf("| %-15s | %-5s | %-18s | %-9s |\n", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+-----------------+-------+--------------------+---------+\n");
    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-15d | %-5s | %-18s | %-9s |\n", embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
        printf("+-----------------+-------+--------------------+---------+\n");
    }
}


//  Consultar detalhes do embaixador
void consultarEmbaixador(Embaixador embaixador[]) {
    int numero_estudante, found = 0;

    // Mostrar os embaixadores disponíveis
    listarEmbaixador(embaixador);

    printf("\nInsira o numero de estudante para ver os seus detalhes: ");
    scanf("%d", &numero_estudante);

    // Mostrar os detalhes
    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        if (embaixador[i].numeroEstudante == numero_estudante) {
            printf("Detalhes do embaixador: \n\n");
            printf("\nNumero de estudante %d:\n", numero_estudante);
            printf("Nome Completo: %s\n", embaixador[i].nomeCompleto);
            printf("Escola: %s\n", embaixador[i].escola);
            printf("NIF: %s\n", embaixador[i].nif);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("O embaixador com o numero %d nao foi encontrado\n", numero_estudante);
    }
}








