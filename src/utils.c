// Ficheiro: utils.c
// Data: 10/01/2025
// Descrição: Contém funções adicionais para o projeto

#include "../include/utils.h"
#include "../include/embaixador.h"
#include "../include/visita.h"

// Limpar ecrã
void cls() {
    system("cls");
}

// Carregar embaixadores do ficheiro para o vetor
void carregarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Nao e possivel abrir o ficheiro\n");
        return;
    }

    char buffer[256];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) && i < MAX_EMBAIXADORES) {
        sscanf(
            buffer, 
            "%d, %[^,], %[^,], %s", 
            &embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        i++;
    }
    
    // Reservar o proximo slot
    if (i < MAX_EMBAIXADORES) {
        embaixador[i].numeroEstudante = -1;
    }
    
    fclose(file);
}

// Carregar visitas do ficheiro para o vetor
void carregarVisita(Visita visita[], const char *ficheiro) {
    FILE *file = fopen(ficheiro, "r");

    // Verificar se o ficheiro existe
    if (file == NULL) {
        printf("Nao e possivel abrir o ficheiro\n");
        return;
    }

    char buffer[256];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) && i < MAX_VISITAS) {
        // Carregar detalhes da visita
        sscanf(
            buffer,
            "%d, %[^,], %[^,], %[^,], %[^\n]",
            &visita[i].IdVisita,
            visita[i].estado,
            visita[i].local,
            visita[i].data
        );

        // Carregar lista de embaixadores da visita
        char *token = strtok(buffer, ",");
        token = strtok(NULL, ","); // Pular id, estado e local
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ","); // Pular data
        int j = 0;
        while (token != NULL && j < MAX_EMBAIXADORES_VISITA) {
            visita[i].listaEmbaixadores[j] = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }

    // Reservar o próximo slot
    if (i < MAX_VISITAS) {
        visita[i].IdVisita = -1;
    }

    fclose(file);
    printf("Visitas carregadas com sucesso.\n");
}


// Validar número
int validarNumero(Embaixador embaixador[], const char *input) {
    int numero;
    int resultado;
    int valido = 0;
    
    while (!valido) {
        printf("%s: ", input);
        resultado = scanf("%d", &numero);
        while (getchar() != '\n');

        
        // O loop continua se o valor inserido não for um número
        if (resultado != 1) {
            printf("%s invalido.\n\n", input);
            while (getchar() != '\n');
        }
        else {
            valido = 1;

            // Verificar se o número já está registado
            for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                if (embaixador[i].numeroEstudante == numero) {
                    printf("O numero de estudante %d ja esta associado a outro embaixador.\n\n", numero);
                    valido = 0;
                    break;
                }
            }
        }
    }
    return numero;
}

// Validar palavra
void validarPalavra(char *nome, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("%s: ", input);
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) == 0) {
            printf("Input invalido\n");
            continue;
        }

        valido = 1;
        for (int i = 0; nome[i] != '\0'; i++) {
            if (!isalpha(nome[i]) && nome[i] != ' ') {
                printf("Nome invalido. Insira um nome sem numeros ou caracteres especiais.\n");
                valido = 0;
                break;
            }
        }
    }
}

// Validar NIF
void validarNif(Embaixador embaixador[], char *nif, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("\n%s: ", input);

        if (fgets(nif, 10, stdin) == NULL) {

            printf("Erro ao ler o input. Tente novamente.\n");
            nif[strlen(nif) - 1] = '\0';
            // while (getchar() != '\n' && getchar() != EOF);
            continue;
        }

        nif[strcspn(nif, "\n")] = '\0';

        // Verificar se está vazio
        if (strlen(nif) == 0) {
            printf("O input nao pode estar vazio. Por favor, insira um NIF.");
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }

        valido = 1;

        // Verificar se o NIF já está registado
        for (int i = 0; i < MAX_EMBAIXADORES; i++) {
            if (strcmp(embaixador[i].nif, nif) == 0) {
                printf("O NIF %s esta associado a outro embaixador.\n", nif);
                valido = 0;
                break;
            }
        }

        if (valido) {
            if (strlen(nif) != 9) {
                printf("NIF invalido. Por favor, insira um NIF com exatamente 9 numeros.\n");
                valido = 0;
            } else {
                for (int i = 0; nif[i] != '\0'; i++) {
                    if (!isdigit(nif[i])) {
                        printf("O NIF é invalido. Insira apenas numeros.\n");
                        valido = 0;
                        break;
                    }
                }
            }
        }
    }
}

// Capitalizar o nome
void capitalizarNome(char *nome) {
    int palavras = 0;
    
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!palavras && isalpha(nome[i])) {
            nome[i] = toupper(nome[i]);
            palavras = 1;
        }
        else if (palavras && isalpha(nome[i])) {
            nome[i] = tolower(nome[i]);
        } 
        else {
            palavras = 0;
        }
    }
}

// Ordenar embaixadores por nome
void ordenarEmbaixadoresNome(Embaixador embaixador[]) {
    for (int i = 0; i < MAX_EMBAIXADORES - 1 && embaixador[i].numeroEstudante != -1; i++) {
        for (int j = i + 1; j < MAX_EMBAIXADORES && embaixador[j].numeroEstudante != -1; j++) {
            if (strcmp(embaixador[i].nomeCompleto, embaixador[j].nomeCompleto) > 0) {
                Embaixador temp = embaixador[i];
                embaixador[i] = embaixador[j];
                embaixador[j] = temp;
            }
        }
    }
}

// Validar data
void validarData(char *data, const char *input) {
    int valido = 0;

    while (!valido) {
        printf("%s (DD/MM/YYYY): ", input);
        fgets(data, 20, stdin);
        data[strcspn(data, "\n")] = '\0';

        // Verificar o formato "DD/MM/YYYY" ou "DD-MM-YYYY"
        if (strlen(data) != 10 || !(data[2] == '/' || data[2] == '-') || !(data[5] == '/' || data[5] == '-')) {
            printf("Formato inválido. Insira a data no formato DD/MM/YYYY ou DD-MM-YYYY.\n");
            continue;
        }

        // Extrair dia, mês e ano
        int dia, mes, ano;
        char delimitador = data[2];
        sscanf(data, "%d%c%d%c%d", &dia, &delimitador, &mes, &delimitador, &ano);

        // Verificar validade do mês e dia
        if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
            printf("Data inválida. Verifique se o dia e o mês estão corretos.\n");
            continue;
        }

        // Verificar dias adequados para cada mês
        bool anoBissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        int diasNoMes[] = {31, 28 + (anoBissexto ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia > diasNoMes[mes - 1]) {
            printf("Data inválida para o mês especificado.\n");
            continue;
        }

        // Verificar se a data não é anterior à data atual
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        int anoAtual = tm->tm_year + 1900;
        int mesAtual = tm->tm_mon + 1;
        int diaAtual = tm->tm_mday;

        if (ano < anoAtual || (ano == anoAtual && mes < mesAtual) || (ano == anoAtual && mes == mesAtual && dia < diaAtual)) {
            printf("Data inválida. Não é permitido inserir uma data anterior à data atual.\n");
            continue;
        }

        // Se passar todas as validações, a data é válida
        valido = 1;
    }
}
