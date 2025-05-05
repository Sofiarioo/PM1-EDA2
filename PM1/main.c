#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 744         // 24 eventos al dia * 31 dias
#define MAX_EVENTOS_FORZANDO 31 // maximo 31 dias al mes
#define MAX_EVENTOS_FECHA 24    // máximo 1 evento por hora

// -------------------------
// Estructuras
// -------------------------
typedef struct
{
    int max, sumatoria, cantidad;
} Costos;

typedef struct
{
    int hora;
    char evento[81];
    char lugar[81];
} Evento;

// LVO aux
typedef struct
{
    Evento evento;
    struct NodoEvento *sig;
} NodoEvento;

// LSO sin forzar dp. funcional
typedef struct
{
    char fecha[11]; // formato: AAAA-MM-DD
    Evento evento;
} LSOBB;

// LSO forzando dp. funcional
typedef struct
{
    char fecha[11]; // formato: AAAA-MM-DD
    NodoEvento *listaEventos;
} LSOBB_F;

// ABB sin dependencia funcional: un evento por fecha (se puede repetir fecha)
typedef struct NodoABB
{
    char fecha[11]; // formato: AAAA-MM-DD
    Evento evento;
    struct NodoABB *izq, *der;
} NodoABB;

// ABB-F (forzando dependencia funcional): un conjunto de eventos por fecha
typedef struct NodoABB_F
{
    char fecha[11]; // formato: AAAA-MM-DD
    NodoEvento *listaEventos;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

// Prototipos
void menuPrincipal();
int Lectura_Operaciones();
void comparacionEstructuras();

// -------------------------

Costos cLSOevoc = {0, 0, 0};
Costos cLSOalta = {0, 0, 0};
Costos cLSObaja = {0, 0, 0};
Costos cLSO_Fevoc = {0, 0, 0};
Costos cLSO_Falta = {0, 0, 0};
Costos cLSO_Fbaja = {0, 0, 0};
Costos cABBevoc = {0, 0, 0};
Costos cABBalta = {0, 0, 0};
Costos cABBbaja = {0, 0, 0};
Costos cABB_Fevoc = {0, 0, 0};
Costos cABB_Falta = {0, 0, 0};
Costos cABB_Fbaja = {0, 0, 0};

int main()
{
    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    int opc, opcion, opcion2;
    NodoABB *raiz = NULL;
    NodoABB_F *raiz_f = NULL;
    LSOBB_F lista_f[MAX_EVENTOS];
    int cargadosLSO_F = 0;
    LSOBB lista[MAX_EVENTOS];
    int cargadosLSO = 0;

    do
    {
        system("cls");
        printf("=== Agenda Mensual ===\n");
        printf("1. Comparacion de Estructuras\n");
        printf("2. Administrar Estructuras\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            comparacionEstructuras(&raiz, &raiz_f, lista, lista_f, &cargadosLSO, &cargadosLSO_F);
            break;
        case 2:
            do
            {
                printf("\nADMINISTRAR ESTRUCTURA\n");
                printf("1. Mostrar Estructura.\n");
                printf("2. Evocar.\n");
                printf("0. Volver\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcion2);

                switch (opcion2)
                {
                case 1:
                    do
                    {
                        printf("\n1. Mostrar LSO sin forzar dependencia.\n");
                        printf("2. Mostrar LSO forzando dependencia.\n");
                        printf("3. Mostrar ABB sin forzar dependencia..\n");
                        printf("4. Mostrar ABB forzando dependencia.\n");
                        printf("0. Volver\n");
                        printf("Seleccione una opcion: ");
                        scanf("%d", &opcion);
                        switch (opcion)
                        {
                        case 1:
                            // mostrarLSOBB();
                            break;
                        case 2:
                            // mostrarLSOBB_F();
                            break;
                        case 3:
                            // mostrarABB();
                            break;
                        case 4:
                            // mostrarABB_F();
                            break;
                        case 0:
                            printf(">> Volviendo...\n");
                            break;
                        default:
                            printf(">> Opción invalida. Intente de nuevo.\n");
                        }
                    } while (opcion != 0);
                case 2:
                    // EVOCAR
                    break;
                case 0:
                    printf(">> Volviendo...\n");
                    break;
                default:
                    printf(">> Opción invalida. Intente de nuevo.\n");
                }
            } while (opcion2 != 0);
            break;
        case 0:
            printf(">> Saliendo...\n");
            break;
        default:
            printf(">> Opción invalida. Intente de nuevo.\n");
        }
    } while (opc != 0);
}

// --- Operaciones de LSO sin forzar dependencia ---
int inicioLSOBB(LSOBB lista[], char fechaBuscada[], int total)
{
    int inf = 0;
    int sup = total - 1;
    int medio;

    while (inf <= sup)
    {
        medio = (inf + sup + 1) / 2; // (REVISAR TECHO O PISO DE LA DIVISIÓN. Sumando +1 deberia quedar como techo, ya que C redondea al piso)
        if (strcmp(lista[medio].fecha, fechaBuscada) < 0)
        {
            inf = medio + 1; // Buscamos a la derecha
        }
        else
        {
            sup = medio - 1; // Buscamos a la izquierda
        }
    }
    return inf; //devolvemos el testigo, deberia ser donde comience la primer fecha
}

int hayMasLSOBB(LSOBB lista[], char fechaBuscada[], int pos, int total)
{
    if (pos < total && strcmp(lista[pos].fecha, fechaBuscada) == 0)
    {
        return 1;
    }
    return 0;
}

// Localizar retorna: 1 si el evento ya existe en la fecha dada, 0 si no existe el evento en la fecha dada.
int localizarLSOBB(LSOBB lista[], LSOBB evBuscado, int total, int *pos)
{
    *pos = inicioLSOBB(lista, evBuscado.fecha, total);
    int posAux = *pos;

    while (hayMasLSOBB(lista, evBuscado.fecha, posAux, total))
    {
        if (compararEventos(evBuscado.evento, lista[posAux].evento))
        {
            return 1; // ya existe el mismo evento en esa fecha.
        }
        posAux++; // deme otro
    }

    return 0; // el evento no existe, se insertará en lista[pos]
}

// --- Operaciones LSO FORZANDO dependencia ---

// --- Operaciones de ABB

// todos los eventos en listaEventos tienen la misma fecha, que se puede obtener de:
// ------------- >    nodo.fecha
// y se puede acceder a un evento en particular asi
// ------------->    nodo->listaEventos->evento (->sig , .lugar , .hora , .evento)

//------------------------------

void comparacionEstructuras(NodoABB **raiz, NodoABB_F **raiz_f, LSOBB lista[], LSOBB_F lista_f[], int *totalLSOBB, int *totalLSOBB_F)
{
    int i = 0;
    // Limpiar Estructuras
    limpiarSublistasLSOBB_F(lista_f, *totalLSOBB_F);
    limpiarSublistasABB_F(*raiz_f);

    *raiz = NULL;
    *raiz_f = NULL;
    *totalLSOBB = 0;
    *totalLSOBB_F = 0;

    Lectura_Operaciones(raiz, raiz_f, lista, lista_f, totalLSOBB, totalLSOBB_F);
}

void limpiarSublistasLSOBB_F(LSOBB_F lista_f[], int total)
{
    for (int i = 0; i < total; i++)
    {
        liberarSublistaEventos(lista_f[i].listaEventos);
        lista_f[i].listaEventos = NULL;
    }
}

void limpiarSublistasABB_F(NodoABB_F *nodo)
{
    if (nodo == NULL)
        return;

    limpiarSublistasABB_F(nodo->izq);
    limpiarSublistasABB_F(nodo->der);

    liberarSublistaEventos(nodo->listaEventos);
    nodo->listaEventos = NULL;
}

void liberarSublistaEventos(NodoEvento *cabeza)
{
    NodoEvento *aux;
    while (cabeza != NULL)
    {
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
}

int Lectura_Operaciones(NodoABB **raiz, NodoABB_F **raiz_f, LSOBB lista[], LSOBB_F lista_f[], int *totalLSOBB, int *totalLSOBB_F)
{
    FILE *fp;
    int codigoOperador;
    Evento aux;
    char fechaAux[11];

    if ((fp = fopen("Operaciones.txt", "r")) == NULL)
    {
        printf("Error al abrir el archivo de operaciones.\n");
        return 0;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d", &codigoOperador);
        fscanf(fp, " %[^\n]", fechaAux); // fecha: formato AAAA-MM-DD

        if (codigoOperador == 1 || codigoOperador == 2)
        {
            fscanf(fp, " %[^\n]", aux.evento);
            fscanf(fp, "%d", &aux.hora);
            fscanf(fp, " %[^\n]", aux.lugar);

            if (codigoOperador == 1)
            { // ALTA
            }
            else
            { // BAJA
            }
        }
        else if (codigoOperador == 3)
        {
            // Evocar en estructuras
        }
        else
        {
            printf(">> Código no reconocido: %d\n", codigoOperador);
        }
    }

    fclose(fp);
    return 1;
}

/**RETORNA 1 SI SON IGUALES 0 SI NO*/
int compararEventos(Evento evento1, Evento evento2)
{
    if ((strcasecmp(evento1.evento, evento2.evento)) == 0 && evento1.hora == evento2.hora && (strcasecmp(evento1.lugar, evento2.lugar)) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void mostrarEvento(Evento e)
{
    printf("Evento: %s\n", e.evento);
    printf("Hora: %d\n", e.hora);
    printf("Lugar: %s\n", e.lugar);
}

void cuadroComp(void)
{
    system("cls");
    system("color 03");
    printf("##======================================================================================================##\n");
    printf("||                                    COMPARACION DE ESTRUCTURAS                                        ||\n");
    printf("##======================================================================================================##\n");
    printf("||                      ||  COSTOS LSOBB   ||   COSTOS LSOBB_F   ||   COSTOS ABB    ||   COSTOS ABB_F   ||\n");
    printf("##======================================================================================================##\n");
    printf("|| MAX. EVOC. EX.       ||     %.3f     ||     %.3f     ||      %.3f     ||\n");

    printf("|| MED. EVOC. EX.       ||     %.3f     ||     %.3f     ||      %.3f     ||\n");

    printf("|| MAX. ALTA            ||     %.3f     ||     %.3f     ||      %.3f     ||\n");

    printf("|| MED. ALTA            ||     %.3f     ||     %.3f     ||      %.3f     ||\n");

    printf("|| MAX. BAJA            ||     %.3f     ||     %.3f     ||      %.3f     ||\n");

    printf("|| MED. BAJA            ||     %.3f     ||     %.3f     ||      %.3f     ||\n");
    // AGREGAR CONTROLES NECESARIOS Y VARIABLES
    printf("||============================================================================||\n");
    system("pause");
    system("cls");
}