#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------
// Definiciones de tipos
// -------------------------
typedef struct {
    int dia, mes, anio;
} Fecha;

typedef struct {
    int hora;           // una hora por evento
    char evento[50];
    char lugar[50];
} Evento;

// -------------------------
// Estructuras sin dependencia funcional
// -------------------------
typedef struct NodoLSOBB {
    Fecha fecha;
    Evento evento;
    struct NodoLSOBB* sig;
} NodoLSOBB;

typedef struct NodoABB {
    Fecha fecha;
    Evento evento;
    struct NodoABB* izq;
    struct NodoABB* der;
} NodoABB;

// -------------------------
// Estructuras con dependencia funcional
// -------------------------
typedef struct EventoLista {
    Evento evento;
    struct EventoLista* sig;
} EventoLista;

typedef struct NodoLSOBB_F {
    Fecha fecha;
    EventoLista* listaEventos;
    struct NodoLSOBB_F* sig;
} NodoLSOBB_F;

typedef struct NodoABB_F {
    Fecha fecha;
    EventoLista* listaEventos;
    struct NodoABB_F* izq;
    struct NodoABB_F* der;
} NodoABB_F;

// -------------------------
// Prototipos
// -------------------------
void menuPrincipal();

// -------------------------
// Función principal
// -------------------------
int main() {
    menuPrincipal();
    return 0;
}

// -------------------------
// Menú principal
// -------------------------
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
