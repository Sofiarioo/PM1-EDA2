#include <stdio.h>
#include <stdlib.h>
#include <string.h>//confirmacion de baja

#include <strings.h> //agregar ............................................................................

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

// LSO sin forzar dp. funcional
typedef struct {
    Evento evento;
} LSOBB;

//LSO forzando dp. funcional
typedef struct {
    Evento evento[MAX_EVENTOS_FECHA];
    int cantidadEventos;
} LSOBB_F;

// ABB sin dependencia funcional: múltiples eventos por fecha


// ABB-F (forzando dependencia funcional): un conjunto de eventos por fecha
typedef struct NodoABB_F {
    Evento eventos[MAX_EVENTOS_FECHA];
    int cantidadEventos;
    struct NodoABB_F *izq, *der;
} NodoABB_F;

//--------INICIALIZACION ESTRUCTURAS-----------

// LSO sin dependencia funcional
LSOBB agendaLSOBB[MAX_EVENTOS];
int totalLSOBB = 0;

// LSO con dependencia funcional
LSOBB_F agendaLSOBB_F[MAX_EVENTOS];
int totalLSOBB_F = 0;

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


int compararPrestador(Prestadores a, Prestadores b)
{
    if (a.DNI == b.DNI && strcasecmp(a.domicilio,b.domicilio)==0 && strcasecmp(a.mail,b.mail)==0 && strcasecmp(a.nombreApellido,b.nombreApellido)==0 && strcasecmp(a.servicios,b.servicios)==0 && strcasecmp(a.telefono,b.telefono)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**RETORNA 1 SI SON IGUALES 0 SI NO*/
int compararEventos(Evento evento1, Evento evento2){
    if((strcasecmp(evento1.evento,evento2.evento))==0 && evento1.hora==evento2.hora && (strcasecmp(evento1.fecha,evento2.fecha))==0 && (strcasecmp(evento1.lugar,evento2.lugar))==0){
        return 1;
    }
    else{
        return 0;
    }
}

void mostrarEvento(Evento e){
    printf("Evento: %s\n", e.evento);
    printf("Fecha: %s\n", e.fecha);
    printf("Hora: %d\n", e.hora);
    printf("Lugar: %s\n", e.lugar);
}

void cuadroComp(void){
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
    //AGREGAR CONTROLES NECESARIOS Y VARIABLES
    printf("||============================================================================||\n");
    system("pause");
    system("cls");
}

