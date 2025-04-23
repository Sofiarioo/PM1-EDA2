#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 500
#define MAX_EVENTOS_FECHA 24  // máximo 1 evento por hora

// -------------------------
// Estructuras auxiliares
// -------------------------
typedef struct {
    int dia, mes, anio;
} Fecha;

typedef struct {
    int hora;
    char evento[50];
    char lugar[50];
} Evento;

typedef struct {
    Fecha fecha;
    Evento evento;
} RegistroLSOBB;  // sin dependencia funcional

typedef struct {
    Fecha fecha;
    Evento eventos[MAX_EVENTOS_FECHA];
    int cantidadEventos;
} RegistroLSOBB_F;  // forzando dependencia funcional


// LSO sin dependencia funcional
RegistroLSOBB agendaLSOBB[MAX_EVENTOS];
int totalLSOBB = 0;

// LSO con dependencia funcional
RegistroLSOBB_F agendaLSOBB_F[MAX_EVENTOS];
int totalLSOBB_F = 0;

// ABB sin dependencia funcional
typedef struct NodoABB {
    Fecha fecha;
    Evento evento;
    struct NodoABB* izq;
    struct NodoABB* der;
} NodoABB;

// ABB con dependencia funcional
typedef struct NodoABB_F {
    Fecha fecha;
    Evento eventos[MAX_EVENTOS_FECHA];  // un evento por hora
    int cantidadEventos;
    struct NodoABB_F* izq;
    struct NodoABB_F* der;
} NodoABB_F;

// Prototipos
void menuPrincipal();

// -------------------------
int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;

    do {
        printf("\n=== Agenda Mensual ===\n");
        printf("1. Comparación de Estructuras\n");
        printf("2. Administrar Estructura\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf(">> Comparación de estructuras (a implementar)\n");
                break;
            case 2:
                printf(">> Administración de estructura (a implementar)\n");
                break;
            case 0:
                printf(">> Saliendo...\n");
                break;
            default:
                printf(">> Opción inválida. Intente de nuevo.\n");
        }
    } while(opcion != 0);
}
