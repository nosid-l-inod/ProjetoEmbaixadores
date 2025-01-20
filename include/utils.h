// Ficheiro: utils.h
// Data: 10/01/2025
// Descrição: Define protótipo de funções adicionais para o projeto

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "embaixador.h"


// Prototipos para validar dados
int validarNumero(Embaixador embaixador[], const char *input);
void validarPalavra(char *name, const char *input);
int validarNumero(Embaixador embaixador[], const char *input);
void validarPalavra(char *name, const char *input);
void validarNif(Embaixador embaixador[], char *nif, const char *input);
void validarData(char *data, const char *input);

// Gerir dados do ficheiro
void carregarDados(Embaixador embaixador[], const char *ficheiro);
void salvarDados(Embaixador embaixador[], const char *ficheiro);

// Protótipos adicionais
void cls();
void capitalizarNome(char *nome);
void ordenarEmbaixadoresNome(Embaixador embaixador[]);
void sair();



#endif