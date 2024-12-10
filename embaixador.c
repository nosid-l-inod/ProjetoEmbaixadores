// Filename: embaixador.c
// Description: Functions related to embaixadores

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/embaixador.h"


void printEmbaixador(Embaixador embaixador) {
    printf("Numero de Estudante: %d\n", embaixador.numeroEstudante);
    printf("Escola: %s\n", embaixador.escola);
    printf("Nome Completo: %s\n", embaixador.nomeCompleto);
    printf("NIF: %s\n", embaixador.nif);
}

void adicionarEmbaixador(const char *filename) {
    Embaixador embaixador;

    printf("Numero do estudante: ");
    scanf("%d", &embaixador.numeroEstudante);
    getchar();

    printf("Insira a escola: ");
    fgets(embaixador.escola, sizeof(embaixador.escola), stdin);
    strtok(embaixador.escola, "\n");

    printf("Insira o nome completo: ");
    fgets(embaixador.nomeCompleto, sizeof(embaixador.nomeCompleto), stdin);
    strtok(embaixador.nomeCompleto, "\n"); // Remove newline character from the end of the string

    printf("Insira o NIF: ");
    fgets(embaixador.nif, sizeof(embaixador.nif), stdin);
    strtok(embaixador.nif, "\n"); // Remove newline character from the end of the string

    FILE *file = fopen(filename, "ab"); // Append mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return;
    }
    fwrite(&embaixador, sizeof(Embaixador), 1, file);
    fclose(file);
}

void listarEmbaixadores(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura\n");
        return;
    }

    Embaixador embaixador;
    while (fread(&embaixador, sizeof(Embaixador), 1, file)) {
        printEmbaixador(embaixador);
    }

    fclose(file);
}

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
        printf("Embaixador com numero de estudante %d nao encontrado.\n", numeroEstudante);
    }

    fclose(file);
}

void editarEmbaixador() {
    int numeroEstudante;
    printf("Insira o numero do estudante para editar: ");
    scanf("%d", &numeroEstudante);
    getchar(); // To consume the newline character left by scanf

    FILE *file = fopen("embaixador.dat", "rb+"); // Open for read/write
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura/escrita\n");
        return;
    }

    Embaixador embaixador;
    int found = 0;
    long pos;
    while ((pos = ftell(file)) != -1 && fread(&embaixador, sizeof(Embaixador), 1, file)) {
        if (embaixador.numeroEstudante == numeroEstudante) {
            printf("\nEmbaixador encontrado. Insira as novas informacoes:\n");
            printf("Insira a escola: ");
            fgets(embaixador.escola, sizeof(embaixador.escola), stdin);
            strtok(embaixador.escola, "\n"); // Remove newline character from the end of the string

            printf("Insira o nome completo: ");
            fgets(embaixador.nomeCompleto, sizeof(embaixador.nomeCompleto), stdin);
            strtok(embaixador.nomeCompleto, "\n"); // Remove newline character from the end of the string

            printf("Insira o NIF: ");
            fgets(embaixador.nif, sizeof(embaixador.nif), stdin);
            strtok(embaixador.nif, "\n"); // Remove newline character from the end of the string

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

void eliminarEmbaixador() {
    int numeroEstudante;
    printf("Insira o numero do estudante para eliminar: ");
    scanf("%d", &numeroEstudante);

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
