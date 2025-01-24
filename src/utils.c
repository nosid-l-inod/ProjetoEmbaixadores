// Ficheiro: utils.c
// Descrição: Contém funções utilitárias
// Data: 22-01-2025

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "../include/embaixador.h"
#include "../include/utils.h"


// Validar palavra
void validarPalavra(char *nome, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("%s: ", input);
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) == 0) {
            printf("Input invalido\n");
            continue;
        }

        valido = 1;
        for (int i = 0; nome[i] != '\0'; i++) {
            if (!isalpha(nome[i]) && nome[i] != ' ') {
                printf("Nome invalido. Insira um nome sem numeros ou caracteres especiais.\n");
                valido = 0;
                break;
            }
        }
    }
}

// Validar data
void validarData(char *data, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("%s (DD/MM/YYYY): ", input);
        fgets(data, 20, stdin);
        data[strcspn(data, "\n")] = '\0';

        // Verificar o formato "DD/MM/YYYY" ou "DD-MM-YYYY"
        if (strlen(data) != 10 || !(data[2] == '/' || data[2] == '-') || !(data[5] == '/' || data[5] == '-')) {
            printf("Formato invalido. Insira a data no formato DD/MM/YYYY ou DD-MM-YYYY.\n");
            continue;
        }

        // Extrair dia, mês e ano
        int dia, mes, ano;
        char delimitador = data[2];
        sscanf(data, "%d%c%d%c%d", &dia, &delimitador, &mes, &delimitador, &ano);

        // Verificar a validade do mês e dia
        if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
            printf("Data invalida. Verifique se o dia e o mes estao corretos.\n");
            continue;
        }

        // Verificar dias adequados para cada mês
        bool anoBissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        int diasNoMes[] = {31, 28 + (anoBissexto ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia > diasNoMes[mes - 1]) {
            printf("Data invalida para o mes especificado.\n");
            continue;
        }

        // Verificar se a data não é anterior à data atual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        int anoAtual = tm->tm_year + 1900;
        int mesAtual = tm->tm_mon + 1;
        int diaAtual = tm->tm_mday;

        if (ano < anoAtual || (ano == anoAtual && mes < mesAtual) || (ano == anoAtual && mes == mesAtual && dia < diaAtual)) {
            printf("Data invalida. Nao e permitido uma data anterior a data atual.\n");
            continue;
        }

        // Se passar todas as validações, a data é válida
        valido = 1;
    }
}

// Validar número de estudantes
int validarNumeroEstudante(Embaixador embaixador[], const char *input) {
    int numero;
    int resultado;
    int valido = 0;
    
    while (!valido) {
        printf("%s: ", input);
        resultado = scanf("%d", &numero);
        while (getchar() != '\n');
        
        // O loop continua se o valor inserido não for um número
        if (resultado != 1) {
            printf("%s invalido.\n\n", input);
        }
        else if (numero > 0 && !embaixadorExiste(embaixador, numero)) {
            printf("O numero de estudante %d nao esta associado a nenhum embaixador.\n\n", numero);
        }
        else {
            valido = 1;
        }
    }
    return numero;
}

// Limpar ecrã
void cls() {
    system("cls");
}

// Sair
void sair() {
    char sair;
    
    printf("Pretende sair? (S/N): ");
    scanf(" %c", &sair);
    while (getchar() != '\n');

    if (sair == 's' || sair == 'S') {
        printf("A sair da aplicacao.\n");
        exit(0);
    }
    else {
        printf("Opcao invalida.\n");
    }
}

// Capitalizar o nome
void capitalizarNome(char *nome) {
    int palavras = 0;
    
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!palavras && isalpha(nome[i])) {
            nome[i] = toupper(nome[i]);
            palavras = 1;
        }
        else if (palavras && isalpha(nome[i])) {
            nome[i] = tolower(nome[i]);
        } 
        else {
            palavras = 0;
        }
    }
}

// Validar NIF
void validarNif(Embaixador embaixador[], char *nif, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("\n%s: ", input);

        if (fgets(nif, 10, stdin) == NULL) {

            printf("Erro ao ler o input. Tente novamente.\n");
            nif[strlen(nif) - 1] = '\0';
            // while (getchar() != '\n' && getchar() != EOF);
            continue;
        }

        nif[strcspn(nif, "\n")] = '\0';

        // Verificar se está vazio
        if (strlen(nif) == 0) {
            printf("O input nao pode estar vazio. Por favor, insira um NIF.");
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }

        valido = 1;

        // Verificar se o NIF já está registado
        for (int i = 0; i < MAX_EMBAIXADORES; i++) {
            if (strcmp(embaixador[i].nif, nif) == 0) {
                printf("O NIF %s esta associado a outro embaixador.\n", nif);
                valido = 0;
                break;
            }
        }

        if (valido) {
            if (strlen(nif) != 9) {
                printf("NIF invalido. Por favor, insira um NIF com exatamente 9 numeros.\n");
                valido = 0;
            } 
            else {
                for (int i = 0; nif[i] != '\0'; i++) {
                    if (!isdigit(nif[i])) {
                        printf("O NIF e invalido. Insira apenas numeros.\n");
                        valido = 0;
                        break;
                    }
                }
            }
        }
    }
}

// Validar número
int validarNumero(Embaixador embaixador[], const char *input) {
    int numero;
    int resultado;
    int valido = 0;
    
    while (!valido) {
        printf("%s: ", input);
        resultado = scanf("%d", &numero);
        while (getchar() != '\n');

        
        // O loop continua se o valor inserido não for um número
        if (resultado != 1) {
            printf("%s invalido.\n\n", input);
            while (getchar() != '\n');
        }
        else {
            valido = 1;

            // Verificar se o número já está registado
            for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                if (embaixador[i].numeroEstudante == numero) {
                    printf("O numero de estudante %d ja esta associado a outro embaixador.\n\n", numero);
                    valido = 0;
                    break;
                }
            }
        }
    }
    return numero;
}
