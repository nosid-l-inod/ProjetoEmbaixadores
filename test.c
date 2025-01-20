#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validarNumeroDezDigitos(const char *inputPrompt) {
    int valido = 0;
    char numeroTemporario[12];  // Buffer to hold the input string
    int numeroEstudante = 0;

    while (!valido) {
        printf("\n%s: ", inputPrompt);
        fflush(stdout); // Ensure the prompt is displayed immediately

        if (fgets(numeroTemporario, sizeof(numeroTemporario), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        // Remove newline character if present
        size_t length = strlen(numeroTemporario);
        if (length > 0 && numeroTemporario[length - 1] == '\n') {
            numeroTemporario[length - 1] = '\0';
        }

        // Validate the length
        length = strlen(numeroTemporario);
        valido = 1;

        if (length != 10) {
            printf("Invalid number. Please enter a number with 10 digits.\n");
            valido = 0;
        } else {
            for (int i = 0; numeroTemporario[i] != '\0'; i++) {
                if (!isdigit(numeroTemporario[i])) {
                    printf("Invalid number. Please enter only digits.\n");
                    valido = 0;
                    break;
                }
            }
        }

        if (valido) {
            // Manually convert the valid string to an integer
            numeroEstudante = 0;
            for (int i = 0; i < length; i++) {
                numeroEstudante = numeroEstudante * 10 + (numeroTemporario[i] - '0');
            }
        }
    }

    return numeroEstudante;
}

int main() {
    int numero = validarNumeroDezDigitos("Enter your 10-digit number");
    printf("Valid number: %d\n", numero);
    return 0;
}


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