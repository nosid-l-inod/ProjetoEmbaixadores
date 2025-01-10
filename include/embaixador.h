#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H


// Estrutura do embaixador
typedef struct {
    int numero_estudante;
    char escola[5];
    char nomeCompleto[100];
    char nif[10];
} Embaixador;


// Protótipos de funlções do embaixador
void adicionarEmbaixador(Embaixador embaixador, const char *ficheiro);

// Protótipo para a gerir a validar dados
int validarNumero(const char *numero);
void validarNome(char *nome, const char *input);
void validarNif(char *nif, const char *input);
void capitalizarNome(char *nome);


#endif 
#define EMBAIXADOR_H