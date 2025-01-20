//  Ficheiro: visita.h
// Data: 10-01-2025
// Descrição: Define a estrutura e protótipos de funções da visita

#ifndef VISITA_H
#define VISITA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "../include/embaixador.h"

#define MAX_VISITAS 1000
#define MAX_EMBAIXADORES_VISITA 9


// Estrutura da visita
typedef struct {
    int IdVisita;
    int listaEmbaixadores[MAX_EMBAIXADORES_VISITA];
    char estado[20];
    char local[100];
    char data[20];
} Visita;


// Protótipo de funções da visita
void adicionarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro);
void listarVisitas(Visita visitas[]);
void consultarVisita(Visita visitas[], Embaixador embaixador[]);

// Inicializar visita
void inicializarVisita(Visita visitas[]);


#endif 
#define VISITA_H