#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 744 //24 eventos al dia * 31 dias
#define MAX_EVENTOS_FECHA 24 // máximo 1 evento por hora

// -------------------------
// Estructuras auxiliares
// -------------------------
typedef struct
{
    int dia, mes, anio;
} Fecha;

typedef struct
{
    int hora;
    char evento[50];
    char lugar[50];
} Evento;

// LSO
typedef struct {
    Fecha fecha;
    Evento evento;
} LSOBB;

// LSO sin dependencia funcional
LSOBB agendaLSOBB[MAX_EVENTOS];
int totalLSOBB = 0;

// LSO con dependencia funcional
LSOBB agendaLSOBB_F[MAX_EVENTOS];
int totalLSOBB_F = 0;

// ABB-F (forzando dependencia funcional): un solo evento por fecha
typedef struct NodoABB_F {
    Fecha fecha;
    Evento evento;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

// ABB sin dependencia funcional: múltiples eventos por fecha
typedef struct NodoABB {
    Fecha fecha;
    Evento eventos[MAX_EVENTOS_FECHA];
    int cantidadEventos;
    struct NodoABB *izq, *der;
} NodoABB;

// Prototipos
void menuPrincipal();
int Lectura_Operaciones();

// -------------------------
int main()
{
    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    int opcion;

    do
    {
        printf("\n=== Agenda Mensual ===\n");
        printf("1. Comparación de Estructuras\n");
        printf("2. Administrar Estructura\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf(">> Comparacion de estructuras (a implementar)\n");
            break;
        case 2:
            printf(">> Administracion de estructura (a implementar)\n");
            break;
        case 0:
            printf(">> Saliendo...\n");
            break;
        default:
            printf(">> Opción invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

int LecturaOperaciones() {
    FILE *fp;
    int codigoOperador;
    Fecha auxFecha;
    Evento aux;

    if ((fp = fopen("Operaciones.txt", "rt")) == NULL) {
        printf("Error al abrir el archivo de operaciones.\n");
        return 0;
    }

    while (!feof(fp)) {
        if (fscanf(fp, "%d\n", &codigoOperador) != 1) break;

        if (codigoOperador == 1 || codigoOperador == 2) {
            // Leer fecha: formato AAAA-MM-DD
            fscanf(fp, "%d-%d-%d\n", &auxFecha.anio, &auxFecha.mes, &auxFecha.dia);

            // Leer evento (con espacios hasta fin de línea)
            fgets(aux.evento, sizeof(aux.evento), fp);
            aux.evento[strcspn(aux.evento, "\n")] = '\0'; // quitar salto de línea

            // Leer hora
            fscanf(fp, "%d\n", &aux.hora);

            // Leer lugar (con espacios hasta fin de línea)
            fgets(aux.lugar, sizeof(aux.lugar), fp);
            aux.lugar[strcspn(aux.lugar, "\n")] = '\0';

            if (codigoOperador == 1) {
                printf("[Alta] %04d-%02d-%02d %02dhs - %s @ %s\n",
                       auxFecha.anio, auxFecha.mes, auxFecha.dia,
                       aux.hora, aux.evento, aux.lugar);
                // Alta en estructuras...
            } else {
                printf("[Baja] %04d-%02d-%02d %02dhs - %s @ %s\n",
                       auxFecha.anio, auxFecha.mes, auxFecha.dia,
                       aux.hora, aux.evento, aux.lugar);
                // Baja en estructuras...
            }

        } else if (codigoOperador == 3) {
            // Leer solo la fecha para la evocación
            fscanf(fp, "%d-%d-%d\n", &auxFecha.anio, &auxFecha.mes, &auxFecha.dia);
            printf("[Evocar] %04d-%02d-%02d\n", auxFecha.anio, auxFecha.mes, auxFecha.dia);
            // Evocar en estructuras...
        } else {
            printf(">> Código no reconocido: %d\n", codigoOperador);
        }
    }

    fclose(fp);
    return 1;
}
