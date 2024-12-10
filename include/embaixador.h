// Filename: embaixador.h
// Description: Program to define the structure for embaixadores

#ifndef EMBAIXADOR_H
#define EMBAIXADOR_H

#include <stdbool.h>

// Define constants
#define MAX_EMBAIXADORES 100
#define MAX_VISITAS 1000

// Define the structure of Embaixador
typedef struct {
    int numeroEstudante;
    char escola[10];
    char nomeCompleto[100];
    char nif[10];
    int numeroVisitas;
} Embaixador;

// Function prototypes
bool adicionarEmbaixador(const char *filename);
void listarEmbaixadores(const char *filename);
void consultarEmbaixador(int numeroEstudante, const char *filename);
void editarEmbaixador();    
void eliminarEmbaixador();
int getValidatedInt(const char *prompt); // Add this line
void getValidatedString(const char *prompt, char *str, int size); // Add this line

#endif
