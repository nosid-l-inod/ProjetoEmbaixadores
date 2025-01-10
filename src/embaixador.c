// Embaixador.c

    
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/embaixador.h"


// carregar dados do ficheiro
void carregarEmbaixador(Embaixador embaixador[], const char *pFicheiro) {

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
            sscanf(
                linha, 
                "%d, %[^,], %[^,], %s", 
                &embaixador[i].numeroEstudante, 
                embaixador[i].escola, 
                embaixador[i].nomeCompleto, 
                embaixador[i].nif
            );
            i++;
        }

        if (i < MAX_EMBAIXADORES) {
            embaixador[i].numeroEstudante = -1;
        }

        fclose(file);
    }
     
}


// Salvar dados no ficheiro
void salvarEmbaixador(Embaixador embaixador[], const char *pFicheiro) {

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
            fprintf(
                file, 
                "%d, %s, %s, %s\n", 
                embaixador[i].numeroEstudante, 
                embaixador[i].escola, 
                embaixador[i].nomeCompleto, 
                embaixador[i].nif
            );
        }
    }

    fclose(file);
}


// Inicializar o vetor ambaixador
void inicializarEmbaixador(Embaixador embaixador[]) {
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        embaixador[i].numeroEstudante = -1;
    }
}


// Listar Embaixadores
void listarEmbaixadores(Embaixador embaixador[]) {
    printf("Embaixadores\n");
    printf("+-----------------+-------+--------------------+---------+\n");
    printf("| %-15s | %-5s | %-18s | %-9s |\n", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+-----------------+-------+--------------------+---------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-15d | %-5s | %-18s | %-9s |\n", embaixador[i].numeroEstudante, embaixador[i].escola, embaixador[i].nomeCompleto, embaixador[i].nif);
        printf("+-----------------+-------+--------------------+---------+\n");
    }
}