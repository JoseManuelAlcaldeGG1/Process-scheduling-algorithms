#include <stdio.h>
#include <string.h>

#define NPROC 5 //N procesos

typedef struct params
{
    char nombre[10];
    int t_ejec;  //Tiempo de ejecucion Se introducen
    int t_lleg;  // Tiempo de llegada
    int t_com;   // Tiempo de computo Se calculan
    int t_fin;  // Fin de proceso +1
    int t_ret;  // Tiempo de estancia
    int t_esp;  // Tiempo de espera
    
} parametros;

void main(){
    
    int i, j, val=0, valAux=0, llegAux=0;


    //Datos de los procesos
    parametros procesos[NPROC];  
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 12;

    printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
    printf("-------------------------------------------------------\n");

//Hacemos que el tiempo de comienzo y de espera de los procesos sea -1 para poder comparar con los otros
    for(i=0; i<NPROC; i++) {
        procesos[i].t_com = -1;
        procesos[i].t_esp = -1;
    }

/* Definición de Variables
val guardará el valor de j para saber en que proceso estamos
valAux guardará el valor de val ya que esté volverá a ser 0 para poder compararse 
con los otros procesos
llegAux guardará el valor de j si el proceso ha llegado y su tiempo de finalizacion
es mayor o igual al tiempo de llegada para poder comparar entre los 5 procesos
*/
    for(i=0; i<NPROC; i++)  //for i para los procesos
    {
        valAux=val;
        val=0;  //Será cero en cada iteración para poder comprobar todos los procesos cual es el que tiene menor tiempo de ejecución
        
    /*For para la búsqueda del proceso con menor tiempo de ejecución y 
    QUE HAYA LLEGADO, ya que si no ha llegado no puede estar antes que otros que si*/
        for(j=0; j<NPROC; j++) {
            if((procesos[j].t_esp==-1)&&(procesos[valAux].t_fin >= procesos[j].t_lleg)) {
                llegAux=j;
                if(procesos[j].t_ejec<procesos[val].t_ejec)
                    val=j;
            }
        }
        
    /*Si el tiempo de espera del proceso es diferente de -1 entonces guardará 
    en val que proceso es el que debe imprimir, que en este caso es el proceso
    con mayor tiempo de computo, hacemos esto para que todos los procesos pasen 
    por la CPU sin repetirse, ya que A seguiría teniendo -1 y se volvería a 
    imprimir*/

        if(procesos[val].t_esp!=-1)
            val=llegAux;

        //Para el proceso A en el que el tiempo de comienzo es 0 siempre
        if(i==0) procesos[val].t_com = 0;
        //Si no estamos en el proceso A el tiempo de comienzo será el tiempo de finalización del proceso que acaba de salir de la CPU
        else procesos[val].t_com = procesos[valAux].t_fin;
    
        procesos[val].t_fin = procesos[val].t_com + procesos[val].t_ejec;
        procesos[val].t_ret = procesos[val].t_fin - procesos[val].t_lleg;
        procesos[val].t_esp = procesos[val].t_ret - procesos[val].t_ejec;
        
        printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[val].nombre,procesos[val].t_com, procesos[val].t_fin, procesos[val].t_ret, procesos[val].t_esp);
    }
}

/*HACEMOS EL EJERCICIO DE ESTA MANERA PORQUE SI SOLO TENEMOS EN CUENTA EL TIEMPO
DE EJECUCIÓN CUANDO CAMBIAMOS POR EJEMPLO EL TIEMPO DE LLEGADA DE EL PROCESO E
A 12, ESTE SE VUELVE A IMPRIMIR EL 2º LO CUAL ES ERRONEO PORQUE EN EL TIEMPO 8
EL NO HA LLEGADO AÚN POR LO CUAL SE DEBERÍA DE IMPRIMIR B*/