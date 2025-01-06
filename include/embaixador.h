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
void listarEmbaixadores();
void consultarEmbaixador();
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void alterarInfoEmbaixador();
void eliminarEmbaixador();


// Validar dados
int validarNif();
int validarNumeroEstudante();


#endif
