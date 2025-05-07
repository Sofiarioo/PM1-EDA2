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
typedef struct NodoEvento
{
    Evento evento;
    struct NodoEvento *sig;
} NodoEvento;

// LSO sin forzar dp. funcional
typedef struct LSOBB
{
    char fecha[11]; // formato: AAAA-MM-DD
    Evento evento;
} LSOBB;

// LSO forzando dp. funcional
typedef struct LSOBB_F
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

typedef struct ABB{
    NodoABB* cur;
    NodoABB* raiz;
    NodoABB* ant;
}ABB;

// ABB-F (forzando dependencia funcional): un conjunto de eventos por fecha
typedef struct NodoABB_F
{
    char fecha[11]; // formato: AAAA-MM-DD
    NodoEvento *listaEventos;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

typedef struct ABB_F{
    NodoABB_F* cur;
    NodoABB_F* raiz;
    NodoABB_F* ant;
}ABB_F;

// Prototipos
void menuPrincipal();
int Lectura_Operaciones();
void comparacionEstructuras();
NodoEvento* crearNodoLVO(Evento e);
void mostrarLSOBB();
void mostrarLSOBB_F();
int compararEventos();
void mostrarEvento();

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

    ABB arbol;
    arbol.raiz = NULL;
    arbol.cur = NULL;
    arbol.ant = NULL;
    int cargadosABB = 0;

    ABB_F arbol_f;
    arbol_f.raiz = NULL;
    arbol_f.cur = NULL;
    arbol_f.ant = NULL;
    int cargadosABB_F = 0;

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
            comparacionEstructuras(&arbol, &arbol_f, lista, lista_f, &cargadosLSO, &cargadosLSO_F, &cargadosABB);
            printf("Cargados lso: %d\n",cargadosLSO);
            printf("Cargados lso_f: %d\n",cargadosLSO_F);
            printf("Cargados abb: %d\n",cargadosABB);
            printf("Raiz: %s\n", arbol.raiz->fecha);
             if (arbol.raiz->izq) 
                printf("Raiz->izq: %s\n", arbol.raiz->izq->fecha);
             if (arbol.raiz->der) 
                printf("Raiz->der: %s\n", arbol.raiz->der->fecha);

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
                            mostrarLSOBB_F(lista_f,cargadosLSO_F);
                            break;
                        case 3:
                            system("cls");
                            printf("ARBOL BINARIO DE BUSQUEDA SIN FORZAR DEPENDENCIA FUNCIONAL\n");
                            printf("--------------AGENDA DE EVENTOS--------------\n");
                            mostrarABBPreorden(arbol.raiz);
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
        medio = (inf + sup + 1) / 2; //  (Sumando +1 para obtener techo, ya que C redondea al piso)
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
    system("cls"); 
    printf("LISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA SIN FORZAR DEPENDENCIA FUNCIONAL\n");
    printf("--------------AGENDA DE EVENTOS--------------\n");
    for(i=0; i<cargados; i+=5){
        for(mod=i; mod<i+5 && mod<cargados; mod++){
            printf("Fecha %s:\n", lista[mod].fecha);
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
        medio = (inf + sup + 1) / 2; // (Sumando +1 para obtener techo, ya que C redondea al piso)
        if (strcmp(lista[medio].fecha, fechaBuscada) < 0)
        {
            inf = medio + 1; // Buscamos a la derecha
        }
        else
        {
            sup = medio - 1; // Buscamos a la izquierda
        }
    }
    return inf; //devolvemos el testigo
}

int hayMasLSOBB_F(NodoEvento *listaEventos)
{
    if (listaEventos->sig != NULL)
    {
        return 1;
    }
    return 0;
}

// Localizar retorna: 1 si hay un evento en la fecha dada a esa hora, 0 si la fecha está y no hay evento a esa hora, -1 si NO esta la fecha.
int localizarLSOBB_F(LSOBB_F lista[], char fechaB[], Evento evBuscado, int total, int* pos, NodoEvento** cur, NodoEvento** ant)
{
    *pos = inicioLSOBB_F(lista, fechaB, total);

    if(*pos >= total || (strcmp(lista[*pos].fecha, fechaB) != 0)){
        return -1;  //No existe la fecha en la lista (ALTA de FECHA en lista[pos])
    }

    *cur = lista[*pos].listaEventos;           //cur apunta a la lvo de la fecha buscada
    *ant = *cur;

    while (hayMasLSOBB_F(*cur))
    {
        if((*cur)->evento.hora == evBuscado.hora){
            return 1;   // ya existe un evento a esa hora, estará apuntado por cur para darlo de baja eventualmente
        }
        *ant = *cur;
        *cur = (*cur)->sig; //deme otro
    }

    return 0; // no existe evento en esa hora, se insertará en lsobb_f[pos]->listaEventos ALTA
}

int altaLSOBB_F(LSOBB_F lsobb_F[], char fecha[], Evento ev, int *cargadosLSO_F){
    if(*cargadosLSO_F==MAX_EVENTOS_FORZANDO-1){
        return -1;                  // lista llena
    }    

    int pos=0;
    NodoEvento* cur = NULL;
    NodoEvento* ant = NULL;
    
    int resultadoLocalizar = localizarLSOBB_F(lsobb_F, fecha, ev, *cargadosLSO_F, &pos, &cur, &ant);
    if (resultadoLocalizar==1){
        return 0; //ya hay un evento a esa hora en la lista
    }
    
    if (resultadoLocalizar == -1){      //caso: Dar de alta FECHA y evento
        int i;
        for(i=*cargadosLSO_F-1; i>=pos; i--){
            lsobb_F[i+1]=lsobb_F[i];
        }
        strcpy(lsobb_F[pos].fecha,fecha); 
        lsobb_F[pos].listaEventos = crearNodoLVO(ev);
        *cargadosLSO_F+=1;        
    } 
    else                //caso: Dar de alta un evento en una fecha ya existente
    {
        NodoEvento* nuevo = crearNodoLVO(ev);
        nuevo->sig = lsobb_F[pos].listaEventos;
        lsobb_F[pos].listaEventos = nuevo;
    }

    return 1;
}

//Retorna 1 si se pudo eliminar, 0 si no se encontró el elemento a eliminar.
int eliminarLSOBB_F(LSOBB_F lsobb_F[], char fecha[], Evento ev, int *cargadosLSO_F){
    int pos = 0;
    NodoEvento* cur = NULL;
    NodoEvento* ant = NULL;
    if(localizarLSOBB_F(lsobb_F, fecha, ev, *cargadosLSO_F, &pos, &cur, &ant) == 1){
        if(compararEventos(ev,cur->evento)==1){
            if(ant != cur){ //si son diferentes, hay mas de 1 evento en la lista vinculada
                ant->sig = cur->sig;
                free((void*)cur);
            }
            else        //hay que dar de baja la fecha, ya que no tiene mas eventos asociados
            {
                free((void*)cur);
                int i=pos;
                for(i; i<(*cargadosLSO_F)-1; i++){
                    lsobb_F[i]=lsobb_F[i+1];
                }
                *cargadosLSO_F-=1;
            }
            return 1; //se elimino con exito
        }
    }
    return 0; //el elemento no esta en la lista
}

NodoEvento* evocacionLSOBB_F(LSOBB_F lsobb_F[], char fechaBuscada[], int cargadosLSO_F) {
    int pos = inicioLSOBB_F(lsobb_F, fechaBuscada, cargadosLSO_F);
    return lsobb_F[pos].listaEventos;
}

void mostrarLSOBB_F(LSOBB_F lista[], int cargados){
    int i;
    //MUESTRA TODOS LOS EVENTOS DE UNA FECHA   
    system("cls");
    printf("LISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA FORZANDO DEPENDENCIA FUNCIONAL\n");
    printf("--------------AGENDA DE EVENTOS--------------\n");
    for(i=0; i<cargados; i++){
        printf("Fecha %s:\n", lista[i].fecha);
        NodoEvento* cur = lista[i].listaEventos;
        while (cur != NULL) {
            mostrarEvento(cur->evento);
            printf("-------------------------------------------------\n");
            cur = cur->sig;
        }        
        system("pause");
    }
}


//--------------------------
// --- Operaciones de ABB
//--------------------------

//RETORNA NULL SI NO SE PUDO
NodoABB* crearnodoABB(char fecha[], Evento evento){
    NodoABB* nodo_nuevo = (NodoABB*)malloc(sizeof(NodoABB));
    if (nodo_nuevo == NULL) {
        return nodo_nuevo;// Error: no se pudo reservar memoria
    }

    strcpy(nodo_nuevo->fecha, fecha);
    nodo_nuevo->evento = evento;

    nodo_nuevo->izq=NULL;
    nodo_nuevo->der=NULL;
    return nodo_nuevo;
}

int inicioABB(ABB *arbol, char fecha[]){
    (arbol->cur) = (arbol->raiz);
    arbol->ant = arbol->cur;
    while(arbol->cur != NULL){
        if(strcmp((arbol->cur)->fecha,fecha)!=0){
            arbol->ant = arbol->cur; //actualizo el cursor del anterior

            if(strcmp((arbol->cur)->fecha, fecha) >= 0){
                arbol->cur = (arbol->cur)->izq;  // menor o igual → izquierda
            }
            else{
                arbol->cur = (arbol->cur)->der;  // mayor → derecha
            }            
        }
        else
        {
            break;
        }
    }
    if (arbol->cur == NULL){
        return 0;  // la fecha no está cargada
    }
    return 1; // se encontro la primer fecha
}

int hayMasABB(ABB *arbol, char fechaBuscada[]){    
    if(arbol->cur != NULL && strcmp(arbol->cur->fecha,fechaBuscada)==0){
        return 1;
    }
    return 0;
}

//retorna 0 si no hay fecha o si no hay evento a esa hora, 1 si ya hay evento a esa hora.
int localizarABB(ABB *arbol, char fecha[], Evento ev){
    if(inicioABB(arbol,fecha) == 0){
        return 0;   //no esta cargada la fecha
    }

    while(hayMasABB(arbol,fecha)){
        if(arbol->cur->evento.hora == ev.hora){
            return 1;   //Ya existe evento a esa hora
        }
        arbol->ant = arbol->cur;
        arbol->cur = arbol->cur->izq;
    }

    return 0;   //No existe evento a esa hora
}

//RETORNA 1 SI TUVO EXITO, 0 SI YA EXISTIA EVENTO A ESA HORA.
int altaABB(ABB* arbol, char fecha[], Evento evento, int *cantCargadosABB){
    if(arbol->raiz == NULL){                        //caso: alta de RAIZ
        NodoABB* nodo = crearnodoABB(fecha,evento); 

        if (nodo != NULL){
            arbol->raiz = nodo;
            *cantCargadosABB+=1;
            return 1;
        }
    }
    else{
        if(localizarABB(arbol,fecha,evento)==1){        //ya existe ev. a esa hora.
            return 0;
        }

        NodoABB* nodo = crearnodoABB(fecha,evento);

        if(strcmp((arbol->ant)->fecha, fecha) >= 0){     
            (arbol->ant)->izq = nodo;  // menor o igual → izquierda
        }
        else{                                          
            (arbol->ant)->der = nodo;  // mayor → derecha
        }
        
        *cantCargadosABB+=1;          
    }
    return 1;
}

//0 si no se encontro el elemento
int eliminarABB(ABB* arbol, char fecha[],Evento evento, int *cantCargadosABB){
    if (localizarABB(arbol, fecha,evento) == 0){
        return 0;
    }
    //ESTO DEBERIA IR DENTRO DE UN WHILE CON DAME OTRO
    if(compararEventos(evento,arbol->cur->evento)==1){
        // Caso sin hijos
        if ((arbol->cur)->izq == NULL && (arbol->cur)->der == NULL){
            if(arbol->cur == arbol->raiz){
                arbol->raiz = NULL;
            }
            else{
                if(arbol->ant->der == arbol->cur){
                    arbol->ant->der = NULL;
                }
                else{
                    arbol->ant->izq = NULL;
                }
            }
            free((void*)arbol->cur);
            *cantCargadosABB-=1;
        }
        // Caso con solo hijo derecho
        else if ((arbol->cur)->izq == NULL){
            if (arbol->cur == arbol->raiz){
                arbol->raiz = arbol->cur->der;
            }
            else if(arbol->ant->der == arbol->cur){
                arbol->ant->der = arbol->cur->der;
            }
            else{
                arbol->ant->izq = arbol->cur->der;
            }

            free((void*)arbol->cur);
            *cantCargadosABB-=1;
        }
        // Caso con solo hijo izquierdo
        else if ((arbol->cur)->der == NULL){
            if (arbol->cur == arbol->raiz){
                arbol->raiz = arbol->cur->izq;
            }
            else if(arbol->ant->der == arbol->cur){
                arbol->ant->der = arbol->cur->izq;
            }
            else{
                arbol->ant->izq = arbol->cur->izq;
            }

            free((void*)arbol->cur);
            *cantCargadosABB-=1;
        }
        // Caso con dos hijos
        else
        {
            NodoABB* actual = (arbol->cur)->izq;
            NodoABB* padre = (arbol->cur);
            while (actual->der != NULL)
            {
                padre = actual;
                actual = actual->der;
            }

            // Si el nodo mayor de los menores tiene un hijo izquierdo:
            if (actual->izq != NULL){
                if (padre->der == actual){
                    padre->der = actual->izq;
                }
                else{
                    padre->izq = actual->izq;
                }
            }
            else{
                if (padre->der == actual){
                    padre->der = NULL;
                }
                else{
                    padre->izq = NULL;
                }
            }

            strcpy(arbol->cur->fecha,actual->fecha);
            (arbol->cur)->evento = actual->evento;
            free((void*)actual);
            *cantCargadosABB -= 1;
        }
        return 1;
    }
    return 0;
}

//PASAR LA RAIZ AL LLAMAR LA FUNCION
void mostrarABBPreorden(NodoABB* nodo) {
    if (nodo != NULL) {
        printf("Fecha nodo: %s\n", nodo->fecha);
        mostrarEvento(nodo->evento);

        if (nodo->izq != NULL) {
            printf("  Hijo izquierdo: %s\n", nodo->izq->fecha);
        }
        if (nodo->der != NULL) {
            printf("  Hijo derecho: %s\n", nodo->der->fecha);
        }
        printf("-------------------------------------------------\n");

        // Recorremos hijo izquierdo
        mostrarABBPreorden(nodo->izq);

        // Recorremos hijo derecho
        mostrarABBPreorden(nodo->der);
    }
}


// todos los eventos en listaEventos tienen la misma fecha, que se puede obtener de:
// ------------- >    nodo.fecha
// y se puede acceder a un evento en particular asi
// ------------->    nodo->listaEventos->evento (->sig , .lugar , .hora , .evento)

//------------------------------

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
int Lectura_Operaciones(ABB *arbol, ABB_F *arbol_f, LSOBB lista[], LSOBB_F lista_f[], int *totalLSOBB, int *totalLSOBB_F, int* totalABB)
{
    FILE *fp;
    int codigoOperador;
    Evento aux;
    char fechaAux[11]; 

    if ((fp = fopen("OperacionesACOTADO.txt", "r")) == NULL)
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
                printf("lso cargada\n"); system("pause");
                altaLSOBB_F(lista_f,fechaAux,aux,totalLSOBB_F);         
                printf("lsoF cargada\n"); system("pause");

                altaABB(arbol,fechaAux,aux,totalABB);         
                printf("abb cargado\n"); system("pause");
            }
            else
            { // BAJA
                printf("lso BAJA anterior\n"); system("pause"); 
                eliminarLSOBB(lista,evAux,totalLSOBB);            
                printf("lso BAJA\n"); system("pause");           

                eliminarLSOBB_F(lista_f,fechaAux,aux,totalLSOBB_F);         
                printf("lsoF BAJA\n"); system("pause");

                eliminarABB(arbol,fechaAux,aux,totalABB);         
                printf("abb BAJA\n"); system("pause");
            }
        }
        else if (codigoOperador == 3)
        {
            // Evocar en estructuras
            evocacionLSOBB(lista,fechaAux,*totalLSOBB);

            evocacionLSOBB_F(lista,fechaAux,*totalLSOBB_F);
        }
        else
        {
            printf(">> Código no reconocido: %d\n", codigoOperador);
        }
    }

    fclose(fp);
    return 1;
}

void comparacionEstructuras(ABB *arbol, ABB_F *arbol_f, LSOBB lista[], LSOBB_F lista_f[], int *totalLSOBB, int *totalLSOBB_F, int *totalABB)
{
    int i = 0;
    /* Limpiar Estructuras
    limpiarSublistasLSOBB_F(lista_f, *totalLSOBB_F);
    limpiarSublistasABB_F(*raiz_f);
    *raiz = NULL;
    *raiz_f = NULL;
    *totalLSOBB = 0;
    *totalLSOBB_F = 0;*/

    Lectura_Operaciones(arbol, arbol_f, lista, lista_f, totalLSOBB, totalLSOBB_F, totalABB);
}

//--------------------------------------

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