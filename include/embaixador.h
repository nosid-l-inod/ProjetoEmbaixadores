// Embaixador.h

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

#define MAX_EMBAIXADORES 100


// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[5];
    char nomeCompleto[100];
    int nif;
} Embaixador;


// Protótipo de funções do embaixador
void listarEmbaixadores(Embaixador embaixador[]);
void consultarEmbaixador();
void adicionarEmbaixador(Embaixador embaixador[], const char *pFicheiro);
void alterarInfoEmbaixador();
void eliminarEmbaixador();

// Gerir dados
void carregarEmbaixador(Embaixador embaixador[], const char *pFicheiro);
void salvarEmbaixador(Embaixador embaixador[], const char *pFicheiro);

// Validar dados
int validarNif();
int validarNumeroEstudante();

// Funções adicionais
void inicializarEmbaixador(Embaixador embaixador[]);


#endif
