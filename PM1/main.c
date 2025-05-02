#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 744 //24 eventos al dia * 31 dias
#define MAX_EVENTOS_FECHA 24 // máximo 1 evento por hora

// -------------------------
// Estructuras 
// -------------------------
typedef struct
{
    char fecha[11]; //formato: AAAA-MM-DD
    int hora;
    char evento[81];
    char lugar[81];
} Evento;

//LVO aux
typedef struct {
    Evento evento;
    struct NodoEvento* sig;
} NodoEvento;

// LSO sin forzar dp. funcional
typedef struct {
    Evento evento;
} LSOBB;

//LSO forzando dp. funcional
typedef struct {
    NodoEvento* listaEventos;
    int cantidadEventos;
} LSOBB_F;

// ABB sin dependencia funcional: múltiples eventos por fecha
typedef struct NodoABB {
    Evento evento;
    struct NodoABB *izq, *der;
} NodoABB;

// ABB-F (forzando dependencia funcional): un conjunto de eventos por fecha
typedef struct NodoABB_F {
    NodoEvento* listaEventos;
    int cantidadEventos;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

// Prototipos
void menuPrincipal();
int Lectura_Operaciones();
void menuMostrarEstructuras();
void menuAdministrarEstructuras();

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
        printf("1. Comparacion de Estructuras\n");
        printf("2. Administrar Estructuras\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf(">> Comparacion de estructuras (a implementar)\n");
            menuMostrarEstructuras();
            break;
        case 2:
            printf(">> Administracion de estructura (a implementar)\n");
            menuAdministrarEstructuras();
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
    Evento aux;

    if ((fp = fopen("Operaciones.txt", "r")) == NULL) {
        printf("Error al abrir el archivo de operaciones.\n");
        return 0;
    }

    while (!feof(fp)) {
        fscanf(fp, "%d", &codigoOperador);        
        fscanf(fp, " %[^\n]", aux.fecha); // fecha: formato AAAA-MM-DD

        if (codigoOperador == 1 || codigoOperador == 2) {                       
            fscanf(fp, " %[^\n]", aux.evento);
            fscanf(fp, "%d", &aux.hora);
            fscanf(fp, " %[^\n]", aux.lugar);

            if (codigoOperador == 1) { //ALTA
            //    printf("[Alta] %04d-%02d-%02d %02dhs - %s @ %s\n",
            //           auxFecha.anio, auxFecha.mes, auxFecha.dia,
            //           aux.hora, aux.evento, aux.lugar);                
            } else { //BAJA
            //    printf("[Baja] %04d-%02d-%02d %02dhs - %s @ %s\n",
            //           auxFecha.anio, auxFecha.mes, auxFecha.dia,
            //           aux.hora, aux.evento, aux.lugar);
            }

        } else if (codigoOperador == 3) {            
            // Evocar en estructuras
        } else {
            printf(">> Código no reconocido: %d\n", codigoOperador);
        }
    }

    fclose(fp);
    return 1;
}