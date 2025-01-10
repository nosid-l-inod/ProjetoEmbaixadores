#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define NAME_LEN 50

// Structures for Embaixadores and Visitas
typedef struct {
    int id;
    char name[NAME_LEN];
} Embaixador;

typedef struct {
    int id;
    int embaixadorId;
    char date[11]; // Format: YYYY-MM-DD
    char location[NAME_LEN];
} Visita;

// Global arrays to store data
Embaixador embaixadores[MAX];
Visita visitas[MAX];
int embaixadorCount = 0;
int visitaCount = 0;

// Function prototypes
void saveData();
void loadData();
void addEmbaixador();
void listEmbaixadores();
void editEmbaixador();
void deleteEmbaixador();
void addVisita();
void listVisitas();
void menu();

int main() {
    loadData(); // Load data on startup
    menu();     // Display menu
    saveData(); // Save data on exit
    return 0;
}

// Save data to files
void saveData() {
    FILE *fEmbaixadores = fopen("embaixadores.csv", "w");
    FILE *fVisitas = fopen("visitas.csv", "w");

    if (!fEmbaixadores || !fVisitas) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < embaixadorCount; i++) {
        fprintf(fEmbaixadores, "%d,%s\n", embaixadores[i].id, embaixadores[i].name);
    }

    for (int i = 0; i < visitaCount; i++) {
        fprintf(fVisitas, "%d,%d,%s,%s\n", visitas[i].id, visitas[i].embaixadorId, visitas[i].date, visitas[i].location);
    }

    fclose(fEmbaixadores);
    fclose(fVisitas);
}

// Load data from files
void loadData() {
    FILE *fEmbaixadores = fopen("embaixadores.csv", "r");
    FILE *fVisitas = fopen("visitas.csv", "r");

    if (fEmbaixadores) {
        while (fscanf(fEmbaixadores, "%d,%49[^\n]", &embaixadores[embaixadorCount].id, embaixadores[embaixadorCount].name) != EOF) {
            embaixadorCount++;
        }
        fclose(fEmbaixadores);
    }

    if (fVisitas) {
        while (fscanf(fVisitas, "%d,%d,%10[^,],%49[^\n]", &visitas[visitaCount].id, &visitas[visitaCount].embaixadorId, visitas[visitaCount].date, visitas[visitaCount].location) != EOF) {
            visitaCount++;
        }
        fclose(fVisitas);
    }
}

// Add a new embaixador
void addEmbaixador() {
    Embaixador e;
    e.id = embaixadorCount + 1;

    printf("Enter the name of the embaixador: ");
    scanf(" %49[^\n]", e.name);

    embaixadores[embaixadorCount++] = e;
    printf("Embaixador added successfully!\n");
}

// List all embaixadores
void listEmbaixadores() {
    printf("\n--- Embaixadores ---\n");
    for (int i = 0; i < embaixadorCount; i++) {
        printf("ID: %d, Name: %s\n", embaixadores[i].id, embaixadores[i].name);
    }
}

// Edit an embaixador
void editEmbaixador() {
    int id;
    printf("Enter the ID of the embaixador to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < embaixadorCount; i++) {
        if (embaixadores[i].id == id) {
            printf("Enter the new name for embaixador %d: ", id);
            scanf(" %49[^\n]", embaixadores[i].name);
            printf("Embaixador updated successfully!\n");
            return;
        }
    }
    printf("Embaixador not found!\n");
}

// Delete an embaixador
void deleteEmbaixador() {
    int id;
    printf("Enter the ID of the embaixador to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < embaixadorCount; i++) {
        if (embaixadores[i].id == id) {
            for (int j = i; j < embaixadorCount - 1; j++) {
                embaixadores[j] = embaixadores[j + 1];
            }
            embaixadorCount--;
            printf("Embaixador deleted successfully!\n");
            return;
        }
    }
    printf("Embaixador not found!\n");
}

// Add a new visita
void addVisita() {
    Visita v;
    v.id = visitaCount + 1;

    printf("Enter the embaixador ID for this visita: ");
    scanf("%d", &v.embaixadorId);
    printf("Enter the date of the visita (YYYY-MM-DD): ");
    scanf("%s", v.date);
    printf("Enter the location of the visita: ");
    scanf(" %49[^\n]", v.location);

    visitas[visitaCount++] = v;
    printf("Visita added successfully!\n");
}

// List all visitas
void listVisitas() {
    printf("\n--- Visitas ---\n");
    for (int i = 0; i < visitaCount; i++) {
        printf("ID: %d, Embaixador ID: %d, Date: %s, Location: %s\n",
               visitas[i].id, visitas[i].embaixadorId, visitas[i].date, visitas[i].location);
    }
}

// Display the menu
void menu() {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Add Embaixador\n");
        printf("2. List Embaixadores\n");
        printf("3. Edit Embaixador\n");
        printf("4. Delete Embaixador\n");
        printf("5. Add Visita\n");
        printf("6. List Visitas\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmbaixador(); break;
            case 2: listEmbaixadores(); break;
            case 3: editEmbaixador(); break;
            case 4: deleteEmbaixador(); break;
            case 5: addVisita(); break;
            case 6: listVisitas(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}
