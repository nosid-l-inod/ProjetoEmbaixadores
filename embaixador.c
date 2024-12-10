// Filename: embaixador.c
// Description: Functions related to embaixadores


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/embaixador.h"


// Validate integer inputs
int getValidatedInt(const char *prompt) {
    int value;
    char buffer[100];
    
    while (1) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
        printf("Tipo de dado inválido. Insira um número\n");
    }
}


// Validate string inputs
void getValidatedString(const char *prompt, char *str, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(str, size, stdin) != NULL) {
            strtok(str, "\n"); // Remove newline character
            if (strlen(str) > 0) {
                return;
            }
        }
        printf("Erro: Entrada invalida. Por favor, insira um texto valido.\n");
    }
}


// Print Embaixador
void printEmbaixador(Embaixador embaixador) {
    printf("Numero de Estudante: %d\n", embaixador.numeroEstudante);
    printf("Escola: %s\n", embaixador.escola);
    printf("Nome Completo: %s\n", embaixador.nomeCompleto);
    printf("NIF: %s\n", embaixador.nif);
    printf("Numero de Visitas: %d\n", embaixador.numeroVisitas);
}


// Contar embaixadores
int countEmbaixadores(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return 0;

    Embaixador embaixador;
    int count = 0;
    while (fread(&embaixador, sizeof(Embaixador), 1, file)) {
        count++;
    }

    fclose(file);

    return count;
}


// Adicionar Embaixador
bool adicionarEmbaixador(const char *filename) {

    // Verificar o limite de embaixadores
    if (countEmbaixadores(filename) >= MAX_EMBAIXADORES) {
        printf("Limite de embaixadores atingido\n");
        return false;
    }

    Embaixador embaixador;

    // Validar numero de estudante
    embaixador.numeroEstudante = getValidatedInt("Insira o numero do estudante: ");
    getValidatedString("Escola: ", embaixador.escola, sizeof(embaixador.escola));
    getValidatedString("Nome completo: ", embaixador.nomeCompleto, sizeof(embaixador.nomeCompleto));
    getValidatedString("NIF: ", embaixador.nif, sizeof(embaixador.nif));
    embaixador.numeroVisitas = getValidatedInt("Insira o numero de visitas: ");

    if ((embaixador.numeroVisitas < 0) || (embaixador.numeroVisitas > MAX_VISITAS)) {
        printf("Erro: Numero de visitas invalido. Deve ser entre 0 embaixador %d.\n", MAX_VISITAS);
        return false;
    }

    // Abrir e editar o ficheiro
    FILE *file = fopen(filename, "ab");

    if (file == NULL) {
        printf("Não é possível abrir o ficheiro\n");
        return false;
    }

    fwrite(&embaixador, sizeof(Embaixador), 1, file);
    fclose(file);

    return true;
}


// Listar embaixadores
void listarEmbaixadores(const char *filename) {

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Nãoe é possível abrir o ficheiro\n");
        return;
    }

    Embaixador embaixador;

    while (fread(&embaixador, sizeof(Embaixador), 1, file)) {
        printEmbaixador(embaixador);
    }

    fclose(file);
}


// Consultar dados de embaixador
void consultarEmbaixador(int numeroEstudante, const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura\n");
        return;
    }

    Embaixador embaixador;

    int found = 0;

    while (fread(&embaixador, sizeof(Embaixador), 1, file)) {
        if (embaixador.numeroEstudante == numeroEstudante) {
            printf("\nInformacoes do Embaixador:\n");
            printEmbaixador(embaixador);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("O embaixador nao foi encontrado ou nao existe.\n");
    }

    fclose(file);
}


// Editar embaixador
void editarEmbaixador() {
    int numeroEstudante = getValidatedInt("Insira o numero de estudante: ");
    
    FILE *file = fopen("embaixador.dat", "rb+");

    if (file == NULL) {
        printf("Não é possível abrir o ficheiro\n");
        return;
    }

    Embaixador embaixador;
    int found = 0;
    long pos;

    while ((pos = ftell(file)) != -1 && fread(&embaixador, sizeof(Embaixador), 1, file)) {
        if (embaixador.numeroEstudante == numeroEstudante) {
            printf("\nEmbaixador encontrado. Insira as novas informacoes:\n");
            getValidatedString("Insira a escola: ", embaixador.escola, sizeof(embaixador.escola));
            getValidatedString("Insira o nome completo: ", embaixador.nomeCompleto, sizeof(embaixador.nomeCompleto));
            getValidatedString("Insira o NIF: ", embaixador.nif, sizeof(embaixador.nif));
            embaixador.numeroVisitas = getValidatedInt("Insira o numero de visitas: ");

            if (embaixador.numeroVisitas < 0 || embaixador.numeroVisitas > MAX_VISITAS) {
                printf("Erro: Numero de visitas invalido. Deve ser entre 0 embaixador %d.\n", MAX_VISITAS);
                fclose(file);
                return;
            }

            fseek(file, pos, SEEK_SET); // Move back to the beginning of the current record
            fwrite(&embaixador, sizeof(Embaixador), 1, file);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Embaixador com numero de estudante %d nao encontrado.\n", numeroEstudante);
    }

    fclose(file);
}


// Eliminar embaixador
void eliminarEmbaixador() {
    int numeroEstudante = getValidatedInt("Insira o numero do estudante para eliminar: ");

    FILE *file = fopen("embaixador.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    Embaixador embaixador;
    int found = 0;
    while (fread(&embaixador, sizeof(Embaixador), 1, file)) {
        if (embaixador.numeroEstudante != numeroEstudante) {
            fwrite(&embaixador, sizeof(Embaixador), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("embaixador.dat");
        rename("temp.dat", "embaixador.dat");
        printf("Embaixador com numero de estudante %d eliminado.\n", numeroEstudante);
    } else {
        remove("temp.dat");
        printf("Embaixador com numero de estudante %d nao encontrado.\n", numeroEstudante);
    }
}