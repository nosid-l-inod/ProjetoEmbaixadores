// void validarNif(Embaixador embaixador[], char *nif, const char *input) {
//     int valido = 0;

//     while (!valido) {
//         printf("\n%s: ", input);

//         if (fgets(nif, 10, stdin) == NULL) {
//             printf("Erro ao ler o input. Tente novamente.\n");
//             // Clear the input buffer
//             while (getchar() != '\n' && getchar() != EOF);
//             continue;
//         }

//         nif[strcspn(nif, "\n")] = '\0';

//         // Verificar se está vazio
//         if (strlen(nif) == 0) {
//             printf("O input nao pode estar vazio. Por favor, insira um NIF.\n");
//             // Clear the input buffer
//             while (getchar() != '\n' && getchar() != EOF);
//             continue;
//         }

//         valido = 1;

//         // Verificar se o NIF já está registado
//         for (int i = 0; i < MAX_EMBAIXADORES; i++) {
//             if (strcmp(embaixador[i].nif, nif) == 0) {
//                 printf("O NIF %s esta associado a outro embaixador.\n", nif);
//                 valido = 0;
//                 break;
//             }
//         }

//         if (valido) {
//             if (strlen(nif) != 9) {
//                 printf("NIF invalido. Por favor, insira um NIF com exatamente 9 numeros.\n");
//                 valido = 0;
//             } else {
//                 for (int i = 0; nif[i] != '\0'; i++) {
//                     if (!isdigit(nif[i])) {
//                         printf("O NIF é invalido. Insira apenas numeros.\n");
//                         valido = 0;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
// }


// // Adicionar embaixador
// void adicionarEmbaixador(Embaixador embaixador[], const char *ficheiro) {
//     int i;

//     // Encontrar o slot vazio
//     for (i = 0; i < MAX_EMBAIXADORES; i++) {
//         if (embaixador[i].numeroEstudante == -1) {
//             break;
//         }
//     }

//     // Verificar o limite de embaixadores
//     if (i >= MAX_EMBAIXADORES) {
//         printf("O limite de embaixadores foi atingido.\n");
//         return;
//     }

//     // Numero de estudaante
//     int numeroEstudante;

//     // Validar e adicionar número de estudante
//     // numeroEstudante = validarNumero(embaixador, "Numero de estudante");
//     printf("Numero de estudante: ");
//     scanf("%d", &numeroEstudante);
//     fflush(stdin);
//     embaixador[i].numeroEstudante = numeroEstudante;

//     // Escola
//     const char *escolas[] = {"ESTS", "ESTB", "ESE", "ESCE", "ESS"};
//     int tamanhoEscola = sizeof(escolas) / sizeof(escolas[0]);
//     int escolha;

//     // Mostrar escolas
//     printf("\nEscolas disponiveis: \n");

//     for (int j = 0; j < tamanhoEscola; j++) {
//         printf("%d. %s\n", j + 1, escolas[j]);
//     }
    
//     // Selecionar escola
//     int valido = 0;

//     while (!valido) {
//         printf("\nInsira a escola (1-%d): ", tamanhoEscola);

//         if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > tamanhoEscola) {
//             printf("Escolha invalida. Selecione um numero entre 1 e %d.\n", tamanhoEscola);
//             while (getchar() != '\n');
//         } 
//         else {
//             valido = 1;
//         }
//     }

//     // Adicionar escola
//     strcpy(embaixador[i].escola, escolas[escolha - 1]);
//     while (getchar() != '\n');

//     //  Nome completo
//     char nomeCompleto[150];

//     // Validar e adicionar nome completo
//     // validarPalavra(nomeCompleto, "\nNome completo");
//     printf("Nome completo: ");
//     fgets(nomeCompleto, 100, stdin);
//     nomeCompleto[strlen(nomeCompleto) - 1] = '\0';
//     // capitalizarNome(nomeCompleto);
//     strcpy(embaixador[i].nomeCompleto, nomeCompleto);   

//     // NIF
//     char nif[10];

//     // Validar e adicionar NIF
//     // validarNif(nif, "NIF");
//     printf("Insira o nif: ");
//     fgets(nif, 10, stdin);
//     nif[strlen(nif) - 1] = '\0';

//     strcpy(embaixador[i].nif, nif);

//     // Reservar o próximo slot
//     if (i + 1 < MAX_EMBAIXADORES) {
//         embaixador[i + 1].numeroEstudante = -1;
//     }

//     // Salvar os dados no ficheiro
//     FILE *file = fopen(ficheiro, "a");

//     if (file == NULL) {
//         printf("Nao e possivel abrir o ficheiro\n");
//         return;
//     }

//     for (int i = 0; i < MAX_EMBAIXADORES; i++) {
//         if (embaixador[i].numeroEstudante == -1) {
//             break;
//         }
//         fprintf(
//             file, 
//             "%d, %s, %s, %s\n", 
//             embaixador[i].numeroEstudante, 
//             embaixador[i].escola, 
//             embaixador[i].nomeCompleto, 
//             embaixador[i].nif
//         );
//     }
//     fclose(file);
    
//     printf("\n%s registado com sucesso.", embaixador[i].nomeCompleto);
// }





