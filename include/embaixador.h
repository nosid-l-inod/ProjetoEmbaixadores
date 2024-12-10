// Filename: embaixador.h
// Description: Program to define the structure for embaixadores

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

// Definir a estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[10];
    char nomeCompleto[100];
    char nif[10];
} Embaixador;


// Protótipos de função
void adicionarEmbaixador(const char *filename);
void listarEmbaixador(const char *filename); // Mostrar a lista de todos os embaixadores e as suas informações
void consultarEmbaixador(int numeroEstudante, const char *filename); // Procurar por Numero de estudante e editar os dados
void editarEmbaixador();    // Editar informações do embaixador pelo numero de estudante
void eliminarEmbaixador();  // Eliminar embaixador


#endif
