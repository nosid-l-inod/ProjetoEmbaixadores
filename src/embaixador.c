// Embaixador.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/embaixador.h"


// adicionar Embaixador
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    
    // Número de estudante
    int numeroEstudante;
    
    

}

// Validar número de estudante
int validarNumeroEstudante(int numeroEstudante) {
    
    do {
        printf("Insira o numero");
        scanf("%d", &numeroEstudante);

        if (!numeroEstudante) {
            printf("Insira um numero valido.");
        }
    }
    while (!numeroEstudante);

    return numeroEstudante;
}

// Validar nif


// alterar Infoormações do  Embaixador


// eliminar Embaixador