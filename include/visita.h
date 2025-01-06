// Visita.h

#ifndef VISITA_H
#define VISITA_H

#define MAX_VISITAS 100
#define MAX_EMBAIXADOR_POR_VISITA 9


// Estrutura da visita
typedef struct {
    int idVisita;
    int listaEmbaixadores[MAX_EMBAIXADOR_POR_VISITA];
    char estadoVisita[25];
    char local[75];
    char data[10];
} Visita;


// Protótipo de funções da visita



// Validar dados



#endif
