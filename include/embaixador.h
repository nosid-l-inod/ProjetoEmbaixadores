//  Ficheiro: Embaixador.h
// Data: 10-01-2025
// Descrição: Define a estrutura e protótipos de funções do embaixador

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_EMBAIXADORES 100


// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[5];
    char nomeCompleto[150];
    char nif[10];
} Embaixador;


// Protótipos de funlções do embaixador
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void listarEmbaixadores(Embaixador embaixador[]);
void listarEmbaixadoresIndex(Embaixador embaixador[]);
void consultarEmbaixador(Embaixador embaixador[]);
void alterarInfoEmbaixador(Embaixador embaixador[], const char *ficheiro);
void eliminarEmbaixador(Embaixador embaixador[], const char *ficheiro);

// Protótipos adicionais
void inicializarEmbaixador(Embaixador embaixador[]);


#endif 
#define EMBAIXADOR_H