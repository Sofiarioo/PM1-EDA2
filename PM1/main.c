#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 744 //24 eventos al dia * 31 dias
#define MAX_EVENTOS_FECHA 24 // máximo 1 evento por hora

///pedo

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
} LSOBB_F;

// ABB sin dependencia funcional: múltiples eventos por fecha
typedef struct NodoABB {
    Evento evento;
    struct NodoABB *izq, *der;
} NodoABB;

// ABB-F (forzando dependencia funcional): un conjunto de eventos por fecha
typedef struct NodoABB_F {
    NodoEvento* listaEventos;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

// Prototipos
void menuPrincipal();
int Lectura_Operaciones();
void menuAdministrarEstructuras();
void comparacionEstructuras();

// -------------------------
int main()
{
    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    int opcion;
    NodoABB* raiz = NULL;
    NodoABB_F* raiz_f = NULL;
    LSOBB_F lista_f[MAX_EVENTOS];
    int cargadosLSO_F = 0;
    LSOBB lista[MAX_EVENTOS];
    int cargadosLSO = 0;

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
            // comparacionEstructuras(NodoABB** raiz, NodoABB_F** raiz_f, LSOBB lista[], LSOBB_F lista_f[], int* totalLSOBB, int* totalLSOBB_F){
            comparacionEstructuras(&raiz, &raiz_f,lista, lista_f,&cargadosLSO,&cargadosLSO_F);
            break;
        case 2:
            printf(">> Administracion de estructura (a implementar)\n");
           // menuAdministrarEstructuras();
            break;
        case 0:
            printf(">> Saliendo...\n");
            break;
        default:
            printf(">> Opción invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}


// --- Operaciones de LSO


// --- Operaciones de ABB

// todos los eventos en listaEventos tienen la misma fecha, que se puede obtener de:
// ------------- >    nodo->listaEventos->evento.fecha


//------------------------------

void comparacionEstructuras(NodoABB** raiz, NodoABB_F** raiz_f, LSOBB lista[], LSOBB_F lista_f[], int* totalLSOBB, int* totalLSOBB_F){
    int i = 0;
    // Limpiar Estructuras
    while(lista_f[i].listaEventos != NULL && i < *totalLSOBB_F) {
        lista_f[i].listaEventos = NULL;
        i++;
    }

    *raiz = NULL;
    *raiz_f = NULL;
    *totalLSOBB = 0;
    *totalLSOBB_F = 0;
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
