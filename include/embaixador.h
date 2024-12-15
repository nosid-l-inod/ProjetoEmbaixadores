// Filename: embaixador.h
// Descrição: Estrutura do embaixador

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

#define MAX_EMBAIXADORES 100


// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[5];
    char nomeCompleto[100];
    char nif[10];
} Embaixador;


// Carregar/Salvar os dados do/para o ficheiro
void carregarDados(Embaixador embaixador[], const char *pFicheiro);
void salvarDados(Embaixador embaixador[], const char *pFicheiro);


// Protótipo de funções do embaixador
void adicionarEmbaixador(Embaixador embaixador[]);
void listarEmbaixador(Embaixador embaixador[]);
void consultarEmbaixador(Embaixador embaixador[]);


// Validação de dados
void validarNome();


#endif