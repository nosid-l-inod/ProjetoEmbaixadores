// Ficheiro: embaixador.h
// Descrição: define a estrutura e os protótipos das funções relativas ao embaixador
// Data: 22-01-2025

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

#define MAX_EMBAIXADORES 100

// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[10];
    char nomeCompleto[150];
    char nif[10];
} Embaixador;

// Protótipo de funções do embaixador
void listarEmbaixadores(Embaixador embaixador[]);
void consultarEmbaixador(Embaixador embaixador[]);
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void alterarInfoEmbaixador(Embaixador embaixador[], const char *ficheiro);
void eliminarEmbaixador(Embaixador embaixador[], const char *ficheiro);

// Protótipos adicionais
void inicializarEmbaixador(Embaixador embaixador[]);
void carregarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void listarEmbaixadoresIndex(Embaixador embaixador[]);
void ordenarEmbaixadoresNome(Embaixador embaixador[]);
int embaixadorExiste(Embaixador embaixador[], int numeroEstudante);

#endif