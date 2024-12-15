// Filename: embaixador.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "include/embaixador.h"


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



// Validar inteiros
int validarInteiro(const char *argumento) {
    
    int valido = 0;
    int numero;

    // Pedir os dados enquanto forem inválidos
    while (!valido) {
        printf("%s", argumento);

        if (scanf("%d", &numero) != 1) {
            printf("Dado invalido. Por favor insira um numero\n");
            while (getchar() != "\n");
        }
        else {
            valido = 1;
        }
    }
    return numero;
}



// Rever este, não funciona muito bem
// Validar nome
void validarNome(char *nome, const char *valor) {

    int valido = 0;

    while (!valido) {
        printf("%s", valor);

        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = "\0";

        valido = 1;

        for (int i = 0; nome[i] != "\0"; i++) {
            if (!isalpha(nome[i]) && nome[i] != ' ') {
                printf("O nome e invalido. \nPor favor insira um numero sem numero or caracteres especiais");
                valido = 0;
                break;
            }
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
    numeroEstudante = getValidInteger("Numero de estudante: ");
    embaixador[i].numeroEstudante = numeroEstudante;

    // Mostar as escolas disponiveis
    printf("Selecione a escola:\n");
    for (int j = 0; j < tamanhoEscola; j++) {
        printf("%d. %s\n", j + 1, escolas[j]);
    }

    // Pedir a escola
    valid_input = 0;

    while (!valid_input) {
        printf("Enter choice (1-%d): ", tamanhoEscola);
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

    // Pedir e validar o nome
    printf("Insira o nome completo: ");
    fgets(nomeCompleto, 100, stdin);
    nomeCompleto[strcspn(nomeCompleto, "\n")] = '\0';

    // Capitalizar e inserir o nome na estrutura
    capitalizeName(nomeCompleto);
    strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

    // Pedir e validar NIF
    getValidNIF(nif, "Insira o NIF: ");
    strcpy(embaixador[i].nif, nif);

    if (i + 1 < MAX_EMBAIXADORES) {
        embaixador[i + 1].numeroEstudante = -1;
    }
}










