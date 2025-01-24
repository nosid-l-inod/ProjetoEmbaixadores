// Ficheiro: visita.h
// Descrição: Define a estrutura e os protótipos das funções relativas à visita
// Data: 22-01-2025

#ifndef VISITA_H
#define VISITA_H

#include "embaixador.h"

#define MAX_VISITAS 100
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
void autorizarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro);
void cancelarVisita(Visita visitas[], const char *ficheiro);
void confirmarRealizacaoVisita(Visita visitas[], const char *ficheiro);
void alterarInformacaoVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro);
void eliminarVisita(Visita visitas[], const char *ficheiro);

// Protótipos adicionais
void inicializarVisita(Visita visita[]);
void carregarVisita(Visita visita[], const char *ficheiro);
int validarDataAnterior(const char *data);
int compararVisitasPorID(const void *a, const void *b);

#endif
