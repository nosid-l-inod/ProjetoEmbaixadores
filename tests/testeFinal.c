// Teste final

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_EMBAIXADORES 100
#define MAX_VISITAS 1000
#define MAX_EMBAIXADORES_VISITA 9

// Estrutura do embaixador
typedef struct {
    int numeroEstudante;
    char escola[5];
    char nomeCompleto[150];
    char nif[10];
} Embaixador;

// Estrutura da visita
typedef struct {
    int IdVisita;
    int listaEmbaixadores[MAX_EMBAIXADORES_VISITA];
    char estado[20];
    char local[100];
    char data[20];
} Visita;

// Protótipos de funções do embaixador
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void listarEmbaixadores(Embaixador embaixador[]);
void listarEmbaixadoresIndex(Embaixador embaixador[]);
void consultarEmbaixador(Embaixador embaixador[]);
void alterarInfoEmbaixador(Embaixador embaixador[], const char *ficheiro);
void eliminarEmbaixador(Embaixador embaixador[], const char *ficheiro);

// Protótipo de funções da visita
void adicionarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro);
void listarVisitas(Visita visitas[]);
void consultarVisita(Visita visitas[], Embaixador embaixador[]);


// Protótipos adicionais
void inicializarEmbaixador(Embaixador embaixador[]);
void inicializarVisita(Visita visitas[]);

// Prototipos para validar dados
int validarNumero(Embaixador embaixador[], const char *input);
void validarPalavra(char *name, const char *input);
void validarNif(Embaixador embaixador[], char *nif, const char *input);
void validarData(char *data, const char *input);

// Gerir dados do ficheiro
void carregarEmbaixador(Embaixador embaixador[], const char *ficheiro);
void carregarVisita(Visita visita[], const char *ficheiro);
void sair();
// void salvarDados(Embaixador embaixador[], const char *ficheiro);

// Protótipos adicionais
void cls();
void capitalizarNome(char *nome);
void ordenarEmbaixadoresNome(Embaixador embaixador[]);

// Protótipo de funções do menu
void mostrarMenu();


// Main
int main() {
    
    // Ficheiros de dados
    const char *ficheiroEmbaixador = "embaixador.csv";
    const char *ficheiroVisita = "visita.csv";

    // Vetores
    Embaixador embaixador[MAX_EMBAIXADORES];
    Visita visita[MAX_VISITAS];

    // Inicializar vetores
    inicializarEmbaixador(embaixador);
    inicializarVisita(visita);

    // Carregar dados do ficheiro para o vetor
    carregarEmbaixador(embaixador, ficheiroEmbaixador);
    carregarVisita(visita, ficheiroVisita);

    int opcao;
    int continuar;

    while (1) {
        cls();
        mostrarMenu();

        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        cls();

        Sleep(250);

        switch (opcao) {
            case 1:
                listarVisitas(visita);
                break;
            case 2:
                listarEmbaixadores(embaixador);
                break;
            case 4:
                consultarEmbaixador(embaixador);
                break;
            case 5:
                adicionarVisita(visita, embaixador, ficheiroVisita);
                break;
            case 6:
                do {
                    cls();
                    adicionarEmbaixador(embaixador, ficheiroEmbaixador);

                    printf("\n\nAdicionar mais embaixadores? (S/N): ");
                    scanf(" %c", &continuar);
                    while (getchar() != '\n');
                }
                while (continuar == 's' || continuar == 'S');

                break;
            case 11:
                alterarInfoEmbaixador(embaixador, ficheiroEmbaixador);
                break;
            case 13:
                eliminarEmbaixador(embaixador, ficheiroEmbaixador);
                break;
            case 15:
                sair();
                break;
            default:
                printf("Opcao invalida.\n");
        }

        printf("..");
        getchar();
    }

    return 0;
}


// MENU.C
// Mostrar menu
void mostrarMenu() {

    // Items do menu
    const char menu[][100] = {
        "+------------------------------------------------+",
        "|                      Menu                      |",
        "|------------------------------------------------|",
        "|                                                |",
        "|      1. Listar Visitas                         |",
        "|      2. Listar Embaixadores                    |",
        "|      4. Consultar Embaixador                   |",
        "|      5. Adicionar Visita                       |",
        "|      6. Adicionar Embaixador                   |",
        "|      11. Alterar Informacoes do Embaixador     |",
        "|      13. Remover Embaixador                    |",
        "|      15. Sair                                  |",
        "|                                                |",
        "+------------------------------------------------+"
    };

    // tamanho do menu
    int tamanhoMenu = sizeof(menu) / sizeof(menu[0]);

    for (int i = 0; i < tamanhoMenu; i++) {
        printf("%s\n", menu[i]);
    }
}


// Sair
void sair() {
    char sair;
    
    printf("Pretende sair? (S/N): ");
    scanf(" %c", &sair);
    while (getchar() != '\n');

    if (sair == 's' || sair == 'S') {
        printf("A sair da aplicacao.\n");
        exit(0);
    }
}


// UTILS.C
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



// EMBAIXADOR.C
// Inicializar embaixador
void inicializarEmbaixador(Embaixador embaixador[]) {
    int i;

    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        embaixador[i].numeroEstudante = -1;
    }
}

// Adicionar embaixador
void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    int i;

    // Encontrar o slot vazio
    for (i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
    }

    // Verificar o limite de embaixadores
    if (i >= MAX_EMBAIXADORES) {
        printf("O limite de embaixadores foi atingido.\n");
        return;
    }

    // Numero de estudaante
    int numeroEstudante;

    numeroEstudante = validarNumero(embaixador, "Numero de estudante");
    embaixador[i].numeroEstudante = numeroEstudante;

    // Escola
    const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
    int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);
    int escolha;

    // Mostrar escolas
    printf("\nEscolas disponiveis: \n");

    for (int j = 0; j < tamanhoEscola; j++) {
        printf("%d. %s\n", j + 1, escolas[j]);
    }
    
    // Selecionar escola
    int valido = 0;

    while (!valido) {
        printf("\nInsira a escola (1-%d): ", tamanhoEscola);

        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
            printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", tamanhoEscola);
            while (getchar() != '\n');
        } 
        else {
            valido = 1;
        }
    }

    // Adicionar escola
    strcpy(embaixador[i].escola, escolas[escolha - 1]);
    while (getchar() != '\n');

    //  Nome completo
    char nomeCompleto[150];

    // Validar e adicionar nome completo
    validarPalavra(nomeCompleto, "\nNome completo");

    capitalizarNome(nomeCompleto);
    strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

    // NIF
    char nif[10];

    // Validar e adicionar NIF
    validarNif(embaixador ,nif, "NIF");
    strcpy(embaixador[i].nif, nif);

    // Reservar o próximo slot
    if (i + 1 < MAX_EMBAIXADORES) {
        embaixador[i + 1].numeroEstudante = -1;
    }

    // Salvar os dados no ficheiro
    FILE *file = fopen(ficheiro, "w");

    if (file == NULL) {
        printf("Nao e possivel abrir o ficheiro\n");
        return;
    }

    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
        fprintf(
            file, 
            "%d, %s, %s, %s\n", 
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
    }
    fclose(file);
    
    printf("\n%s registado com sucesso.", embaixador[i].nomeCompleto);
}

// Listar embaixador
void listarEmbaixadores(Embaixador embaixador[]) {

    // Ordenar embaixadores por nome
    ordenarEmbaixadoresNome(embaixador);

    printf("+-----------------+--------+--------------------------------------------+-----------+\n");
    printf("| %-15s | %-6s | %-42s | %-9s |\n", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+-----------------+--------+--------------------------------------------+-----------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-15d | %-6s | %-42s | %-9s |\n", 
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        printf("+-----------------+--------+--------------------------------------------+-----------+\n");
    }
}

// Listar embaixador e posição no vetor
void listarEmbaixadoresIndex(Embaixador embaixador[]) {
    ordenarEmbaixadoresNome(embaixador);

    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
    printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

    for (int i = 0; i < MAX_EMBAIXADORES && embaixador[i].numeroEstudante != -1; i++) {
        printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
            i + 1,
            embaixador[i].numeroEstudante, 
            embaixador[i].escola, 
            embaixador[i].nomeCompleto, 
            embaixador[i].nif
        );
        printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
    }
}

// Consultar embaixador (Por Numero de estudante)
void consultarEmbaixador(Embaixador embaixador[]) {
    int index;
    int encontrado = 0;
    char continuar;

    do {
        cls();
        listarEmbaixadoresIndex(embaixador);

        printf("\nNumero do embaixador a consultar: ", MAX_EMBAIXADORES);
        scanf("%d", &index);
        cls();

        index = index - 1;

        printf("Detalhes do embaixador\n\n");
        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n",
                index + 1,
                embaixador[index].numeroEstudante,
                embaixador[index].escola,
                embaixador[index].nomeCompleto,
                embaixador[index].nif
            );
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            encontrado = 1;
        }
        else {
            printf("Embaixador nao encontrado.\n", index + 1);
        }

        printf("\n..");
        getchar();
        getchar();
        cls();

        printf("\nDeseja consultar mais embaixadores? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

// Editar embaixador
void alterarInfoEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    char continuar;

    do {
        // Mostrar embaixadores
        printf("Embaixadores:\n");
        listarEmbaixadoresIndex(embaixador);

        int index;
        printf("\nSelecione o embaixador (1-%d): ", MAX_EMBAIXADORES);
        scanf("%d", &index);
        while (getchar() != '\n');
        index -= 1;

        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {
            cls();

            printf("Detalhes do embaixador:\n");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
            printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
                index + 1,
                embaixador[index].numeroEstudante,
                embaixador[index].escola,
                embaixador[index].nomeCompleto,
                embaixador[index].nif
            );
            printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

            printf("\nDeseja alterar alguma informacao do/a %s? (S/N): ", embaixador[index].nomeCompleto);
            scanf(" %c", &continuar);

            if (continuar == 's' || continuar == 'S') {
                do {
                    printf("\nQual campo deseja alterar?\n");
                    printf("1. Numero de estudante\n");
                    printf("2. Escola\n");
                    printf("3. Nome completo\n");
                    printf("4. NIF\n");
                    printf("\nSelecione a informacao que deseja alterar: ");

                    int alterar;
                    scanf("%d", &alterar);
                    while (getchar() != '\n');
                    cls();

                    switch (alterar) {
                        case 1:
                            printf("Novo NumeroEstudante: ");
                            embaixador[index].numeroEstudante = validarNumero(embaixador, "NumeroEstudante");
                            break;
                        case 2: {
                            const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
                            int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);

                            printf("\nEscolas disponiveis:\n");
                            for (int j = 0; j < tamanhoEscola; j++) {
                                printf("%d. %s\n", j + 1, escolas[j]);
                            }

                            int escolha;
                            while (1) {
                                printf("\nSelecione a nova escola: ", tamanhoEscola);

                                if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
                                    printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", tamanhoEscola);
                                    while (getchar() != '\n');
                                } 
                                else {
                                    strcpy(embaixador[index].escola, escolas[escolha - 1]);
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            validarPalavra(embaixador[index].nomeCompleto, "Novo numero de estudante");
                            break;
                        case 4:
                            validarNif(embaixador, embaixador[index].nif, "Novo NIF");
                            break;
                        default:
                            printf("Escolha invalida.\n");
                            continue;
                    }

                    cls();
                    printf("Detalhes atualizados do embaixador com indice %d:\n", index + 1);
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
                    printf("| %-4s | %-15s | %-6s | %-42s | %-9s |\n", "No.", "NumeroEstudante", "Escola", "NomeCompleto", "NIF");
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");
                    printf("| %-4d | %-15d | %-6s | %-42s | %-9s |\n", 
                        index + 1,
                        embaixador[index].numeroEstudante,
                        embaixador[index].escola,
                        embaixador[index].nomeCompleto,
                        embaixador[index].nif
                    );
                    printf("+------+-----------------+--------+--------------------------------------------+-----------+\n");

                    printf("\nDeseja alterar mais alguma informacao? (S/N): ");
                    scanf(" %c", &continuar);
                } while (continuar == 's' || continuar == 'S');

                // Atualizar os dados no ficheiro
                FILE *file = fopen(ficheiro, "w");
                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                } 
                else {
                    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                        if (embaixador[i].numeroEstudante == -1) {
                            break;
                        }

                        fprintf(
                            file,
                            "%d, %s, %s, %s\n",
                            embaixador[i].numeroEstudante,
                            embaixador[i].escola,
                            embaixador[i].nomeCompleto,
                            embaixador[i].nif
                        );
                    }
                    fclose(file);
                }
                printf("Embaixador atualizado com sucesso\n");
            } 
            else {
                printf("Nenhuma informacao alterada.\n");
            }
        } 
        else {
            printf("Embaixador nao encontrado.\n");
        }

        printf("Deseja alterar outro embaixador? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
}

// Eliminar embaixador
void eliminarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
    int index, found = 0;
    char continuar;
    char confirmar;

    do {
        listarEmbaixadoresIndex(embaixador);

        printf("\nNumero do embaixador a remover: ", MAX_EMBAIXADORES);
        scanf("%d", &index);
        while (getchar() != '\n');
        index -= 1;

        if (index >= 0 && index < MAX_EMBAIXADORES && embaixador[index].numeroEstudante != -1) {

            printf("Remover este embaixador? (S/N): ");
            scanf(" %c", &confirmar);
            while (getchar() != '\n');

            if (confirmar == 's' || confirmar == 'S') {
                for (int i = index; i < MAX_EMBAIXADORES - 1 && embaixador[i].numeroEstudante != -1; i++) {
                    embaixador[i] = embaixador[i + 1];
                }

                embaixador[MAX_EMBAIXADORES - 1].numeroEstudante = -1;
                found = 1;

                // Salvar as alterações no ficheiro
                FILE *file = fopen(ficheiro, "w");
                if (file == NULL) {
                    printf("Nao e possivel abrir o ficheiro\n");
                } else {
                    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
                        if (embaixador[i].numeroEstudante == -1) {
                            break;
                        }
                        fprintf(
                            file,
                            "%d, %s, %s, %s\n",
                            embaixador[i].numeroEstudante,
                            embaixador[i].escola,
                            embaixador[i].nomeCompleto,
                            embaixador[i].nif
                        );
                    }
                    fclose(file);
                    printf("\nEmbaixador removido com sucesso.\n");
                }
            } 
            else {
                printf("Embaixador nao removido\n");
            }
        } 
        else {
            printf("Embaixador nao encontrado.\n");
        }

        printf("Deseja remover outro embaixador? (S/N): ");
        scanf(" %c", &continuar);
        cls();

    } while (continuar == 's' || continuar == 'S');

    if (!found) {
        printf("Nenhum embaixador foi removido.\n");
    }
}


// VISITA.H
// Inicializar visita
void inicializarVisita(Visita visitas[]) {
    for (int i = 0; i < MAX_VISITAS; i++) {
        visitas[i].IdVisita = -1;
    }
}

// Adicionar visita
// Verificar se o número do estudante existe
int embaixadorExiste(Embaixador embaixador[], int numeroEstudante) {
    for (int i = 0; i < MAX_EMBAIXADORES; i++) {
        if (embaixador[i].numeroEstudante == -1) {
            break;
        }
        if (embaixador[i].numeroEstudante == numeroEstudante) {
            return 1; // Embaixador existe
        }
    }
    return 0; // Embaixador não existe
}

// Adicionar visita
void adicionarVisita(Visita visitas[], Embaixador embaixador[], const char *ficheiro) {
    int i, j;
    char continuar;

    do {
        // Encontrar o slot vazio
        for (i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == -1) {
                break;
            }
        }

        // Verificar o limite de visitas
        if (i >= MAX_VISITAS) {
            printf("O limite de visitas foi atingido.\n");
            return;
        }

        // Atribuir id automático
        int novoId = (i == 0) ? 1 : visitas[i - 1].IdVisita + 1;
        visitas[i].IdVisita = novoId;

        // Estado da visita
        strcpy(visitas[i].estado, "Em planeamento");

        // Selecionar embaixadores
        printf("Selecione os embaixadores para a visita (max %d). Pressione 0 para parar.\n", MAX_EMBAIXADORES_VISITA);
        listarEmbaixadoresIndex(embaixador);

        for (j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            int indiceEmbaixador;
            
            printf("Selecione o embaixador %d: ", j + 1);
            scanf("%d", &indiceEmbaixador);
            while (getchar() != '\n'); // Limpar o buffer

            if (indiceEmbaixador == 0) {
                break;
            }

            indiceEmbaixador -= 1; // Ajustar para índice baseado em 0

            // Verificar se o índice do embaixador é válido
            if (indiceEmbaixador < 0 || indiceEmbaixador >= MAX_EMBAIXADORES || embaixador[indiceEmbaixador].numeroEstudante == -1) {
                printf("Índice de embaixador inválido. Tente novamente.\n");
                j--; // Permitir que o usuário tente novamente
            } else {
                visitas[i].listaEmbaixadores[j] = embaixador[indiceEmbaixador].numeroEstudante;
            }
        }

        for (; j < MAX_EMBAIXADORES_VISITA; j++) {
            visitas[i].listaEmbaixadores[j] = -1;
        }

        // Local da visita
        printf("Local da visita: ");
        fgets(visitas[i].local, sizeof(visitas[i].local), stdin);
        visitas[i].local[strcspn(visitas[i].local, "\n")] = '\0';

        // Data
        char data[20];
        validarData(data, "Data da visita");
        strcpy(visitas[i].data, data);

        // Reservar o próximo slot
        if (i + 1 < MAX_VISITAS) {
            visitas[i + 1].IdVisita = -1;
        }

        // Salvar os dados no ficheiro
        FILE *file = fopen(ficheiro, "w");

        if (file == NULL) {
            printf("Não é possível abrir o ficheiro\n");
            return;
        }

        for (int i = 0; i < MAX_VISITAS; i++) {
            if (visitas[i].IdVisita == -1) {
                break;
            }
            fprintf(
                file, 
                "%d, %s, %s, %s", 
                visitas[i].IdVisita, 
                visitas[i].estado, 
                visitas[i].local, 
                visitas[i].data
            );

            for (j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                if (visitas[i].listaEmbaixadores[j] == -1) {
                    break;
                }
                fprintf(file, ",%d", visitas[i].listaEmbaixadores[j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);

        printf("\nVisita adicionada com sucesso.\n");

        // Perguntar se deseja adicionar mais visitas
        printf("\nDeseja adicionar mais visitas? (S/N): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); // Limpar o buffer

    } while (continuar == 's' || continuar == 'S');
}

// Listar visita
int compararVisitasPorID(const void *a, const void *b) {
    Visita *visitaA = (Visita *)a;
    Visita *visitaB = (Visita *)b;

    return visitaB->IdVisita - visitaA->IdVisita;
}

// Listar visitas
void listarVisitas(Visita visitas[]) {
    // Ordenar visitas por ID em ordem decrescente
    qsort(visitas, MAX_VISITAS, sizeof(Visita), compararVisitasPorID);

    int totalVisitas = 0;
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    printf("| %-6s | %-19s | %-20s | %-19s | %-17s |\n", "ID", "Estado", "Local", "Data", "Embaixadores");
    printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");

    // Iterar sobre todas as visitas
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }

        totalVisitas++;
        printf("| %-6d | %-19s | %-20s | %-19s | ", 
            visitas[i].IdVisita, 
            visitas[i].estado, 
            visitas[i].local, 
            visitas[i].data
        );

        for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
            if (visitas[i].listaEmbaixadores[j] == -1) {
                break;
            }
            printf("%d ", visitas[i].listaEmbaixadores[j]);
        }
        printf("|\n");
        printf("+--------+---------------------+----------------------+---------------------+-------------------+\n");
    }

    // Imprimir total de visitas por estado
    printf("\nTotal de visitas: %d\n", totalVisitas);

    // Contar visitas por estado
    int visitasPlanejamento = 0;
    int visitasConcluidas = 0;

    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == -1) {
            break;
        }
        if (strcmp(visitas[i].estado, "Em planeamento") == 0) {
            visitasPlanejamento++;
        } else if (strcmp(visitas[i].estado, "Concluída") == 0) {
            visitasConcluidas++;
        }
    }

    printf("\nVisitas em planeamento: %d\n", visitasPlanejamento);
    printf("Visitas concluídas: %d\n", visitasConcluidas);
}

// Consultar visita específica
void consultarVisita(Visita visitas[], Embaixador embaixador[]) {
    int idVisita;
    int encontrado = 0;

    printf("Digite o ID da visita que deseja consultar: ");
    scanf("%d", &idVisita);
    while (getchar() != '\n'); // Limpar o buffer

    // Procurar a visita com o ID fornecido
    for (int i = 0; i < MAX_VISITAS; i++) {
        if (visitas[i].IdVisita == idVisita) {
            encontrado = 1;

            printf("\nDetalhes da Visita:\n");
            printf("ID: %d\n", visitas[i].IdVisita);
            printf("Estado: %s\n", visitas[i].estado);
            printf("Local: %s\n", visitas[i].local);
            printf("Data: %s\n", visitas[i].data);
            printf("Embaixadores:\n");

            for (int j = 0; j < MAX_EMBAIXADORES_VISITA; j++) {
                if (visitas[i].listaEmbaixadores[j] == -1) {
                    break;
                }
                // Encontrar detalhes do embaixador correspondente
                for (int k = 0; k < MAX_EMBAIXADORES; k++) {
                    if (embaixador[k].numeroEstudante == visitas[i].listaEmbaixadores[j]) {
                        printf("  - %s (Número: %d, Escola: %s, NIF: %s)\n",
                            embaixador[k].nomeCompleto,
                            embaixador[k].numeroEstudante,
                            embaixador[k].escola,
                            embaixador[k].nif
                        );
                        break;
                    }
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("\nVisita com ID %d não encontrada.\n", idVisita);
    }
}
