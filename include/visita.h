// Filename: visita.h
// Description: Program to define the structure for visitas

#ifndef VISITA_H
#define VISITA_H


// Definir a estrutura da visita
typedef struct {
    int idVisita;
    char estadoVisita[20];
    char localVisita[10]; // ESTS, ESTB, ESE, ESCE ou ESS
    char dataVisita[11];
} Visita;


#endif // !VISITA_H