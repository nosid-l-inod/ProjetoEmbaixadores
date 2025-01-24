// Ficheiro: utils.h
// Descrição: Define protótipos de funções utilitárias
// Data: 22-01-2025

#ifndef UTILS_H
#define UTILS_H

#include "embaixador.h"

// Validação de dados
void validarPalavra(char *palavra, const char *input);
void validarData(char *data, const char *input);
int validarNumeroEstudante(Embaixador embaixador[], const char *input);
void validarNif(Embaixador embaixador[], char *nif, const char *input);
int validarNumero(Embaixador embaixador[], const char *input);

// Protótipos adicionais
void capitalizarNome(char *nome);
void cls();
void sair();


#endif
