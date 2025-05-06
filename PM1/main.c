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
NodoEvento* crearNodoLVO(Evento e);
void mostrarLSOBB();

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
            printf("Cargados: %d\n",cargadosLSO);
            system("pause");
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
                            mostrarLSOBB(lista,cargadosLSO);
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
    printf("INICIO BB li: %d, ls: %d\n", inf,sup);
    //system("pause");
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

// Localizar retorna: 1 si hay un evento en la fecha dada a esa hora, 0 si no existe.
int localizarLSOBB(LSOBB lista[], LSOBB evBuscado, int total, int *pos)
{
    *pos = inicioLSOBB(lista, evBuscado.fecha, total);
    int posAux = *pos;
    while (hayMasLSOBB(lista, evBuscado.fecha, posAux, total))
    {
        if (evBuscado.evento.hora == lista[posAux].evento.hora)
        {
            *pos = posAux;
            return 1; // ya existe un evento en esa hora, se debería dar de BAJA en lista[posAux]
        }
        posAux++; // deme otro
    }

    return 0; // el evento no existe, se insertará en lista[pos] ALTA
}

NodoEvento* evocacionLSOBB(LSOBB lsobb[], char fechaBuscada[], int cargadosLSO) {
    NodoEvento *listaEventos = NULL, *ultimo = NULL;
    int pos = inicioLSOBB(lsobb, fechaBuscada, cargadosLSO);

    while (pos < cargadosLSO && strcmp(lsobb[pos].fecha, fechaBuscada) == 0) {
        NodoEvento* nuevo = crearNodoLVO(lsobb[pos].evento);

        if (listaEventos == NULL) {
            listaEventos = nuevo;
        } else {
            ultimo->sig = nuevo;
        }

        ultimo = nuevo;
        pos++;
    }

    return listaEventos;
}

//Retorna 1 si se insertó, -1 si está llena y 0 si ya estaba
int altaLSOBB(LSOBB lsobb[], LSOBB elem, int *cargadosLSO){
    if(*cargadosLSO==MAX_EVENTOS-1){
        return -1;                  // lista llena
    }    

    int pos=0;
    if ((localizarLSOBB(lsobb, elem, *cargadosLSO, &pos))==1){
        return 0; //ya hay un evento a esa hora en la lista
    }
            printf("pos: %d\n", pos);
            //system("pause");
    int i;
    for(i=*cargadosLSO-1; i>=pos; i--){
        lsobb[i+1]=lsobb[i];
    }
    lsobb[pos] = elem;
    *cargadosLSO+=1;
    return 1;
}

//Retorna 1 si se pudo eliminar, 0 si no se encontró el elemento a eliminar.
int eliminarLSOBB(LSOBB lsobb[], LSOBB elem, int *cargadosLSO){
    int pos = 0;
    if(localizarLSOBB(lsobb, elem, *cargadosLSO, &pos) == 1){
        if(compararEventos(elem.evento,lsobb[pos].evento)==1){ 
            int i=pos;
            for(i; i<(*cargadosLSO)-1; i++){
                lsobb[i]=lsobb[i+1];
            }
            *cargadosLSO-=1;
            return 1; //se elimino con exito
        }
    }
    return 0; //el elemento no esta en la lista
}

void mostrarLSOBB(LSOBB lista[], int cargados){
    int i, mod;
    //PARA QUE VAYA MOSTRANDO DE A 5    
    printf("LISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA SIN FORZAR DEPENDENCIA FUNCIONAL\n");
    printf("--------------AGENDA DE EVENTOS--------------\n");
    for(i=0; i<cargados; i+=5){
        for(mod=i; mod<i+5 && mod<cargados; mod++){
            printf("Fecha %s:\n", lista[mod].fecha);
            printf("Evento:\n");
            mostrarEvento(lista[mod].evento);
            printf("-------------------------------------------------\n");
        }
        system("pause");
    }
}

// ----
// --- Operaciones LSO FORZANDO dependencia ---
// ----
int inicioLSOBB_F(LSOBB_F lista[], char fechaBuscada[], int total)
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

int hayMasLSOBB_F(NodoEvento *listaEventos)
{
    if (listaEventos->sig != NULL)
    {
        return 1;
    }
    return 0;
}
/*
// Localizar retorna: 1 si hay un evento en la fecha dada a esa hora, 0 si la fecha está y no hay evento a esa hora, -1 si NO esta la fecha.
int localizarLSOBB_F(LSOBB_F lista[], LSOBB evBuscado, int total, int* pos, NodoEvento* cur, NodoEvento* ant)
{
    *pos = inicioLSOBB_F(lista, evBuscado.fecha, total);
    int posAux = *pos;

    if(posAux >= total || (strcmp(lista[posAux].fecha, evBuscado.fecha) != 0)){
        return -1;  //No existe la fecha en la lista (ALTA de FECHA)
    }

    cur = lista[posAux].listaEventos;           //cur apunta a la lvo de la fecha buscada
    ant = cur;

    while (hayMasLSOBB_F(cur))
    {
        if(cur->evento.hora == evBuscado.evento.hora){
            return 1;   // ya existe un evento a esa hora, estará apuntado por cur para darlo de baja eventualmente
        }
        ant = cur;
        cur = cur->sig; //deme otro
    }

    return 0; // no existe evento en esa hora, se insertará en lsobb_f[pos]->listaEventos ALTA
}
*/

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
    //limpiarSublistasLSOBB_F(lista_f, *totalLSOBB_F);
    //limpiarSublistasABB_F(*raiz_f);

    *raiz = NULL;
    *raiz_f = NULL;
    *totalLSOBB = 0;
    *totalLSOBB_F = 0;

    Lectura_Operaciones(raiz, raiz_f, lista, lista_f, totalLSOBB, totalLSOBB_F);
}
/*
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
*/
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

            LSOBB evAux;
            evAux.evento = aux;
            strcpy(evAux.fecha,fechaAux);

            if (codigoOperador == 1)
            { // ALTA
                altaLSOBB(lista,evAux,totalLSOBB);
                printf("ALTA. Cargados: %d\n",*totalLSOBB);
                //system("pause");
            }
            else
            { // BAJA
                eliminarLSOBB(lista,evAux,totalLSOBB);
                printf("BAJA. Cargados: %d\n",*totalLSOBB);
                //system("pause");
            }
        }
        else if (codigoOperador == 3)
        {
            // Evocar en estructuras
            evocacionLSOBB(lista,fechaAux,*totalLSOBB);
            printf("EVOCACION.");
        }
        else
        {
            printf(">> Código no reconocido: %d\n", codigoOperador);
        }
    }

    fclose(fp);
    return 1;
}

NodoEvento* crearNodoLVO(Evento e)
{
    NodoEvento* nuevoNodo = (NodoEvento*)malloc(sizeof(NodoEvento));
    if (!nuevoNodo)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    nuevoNodo->evento = e;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

//RETORNA 1 SI SON IGUALES 0 SI NO
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