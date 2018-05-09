#include <stdio.h>
#include <string.h>

#define NPROC 5


//se introduce un tiempo de ejecucion auxiliar.
typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;
	int t_ejec_aux;
    
} parametros;

void main(){
    
    int i=NPROC, j, quantum=3, tiempo=0, k;
    
    // Inicialización de los datos de procesos
    parametros procesos[NPROC];    
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;
	procesos[0].t_ejec_aux=procesos[0].t_ejec;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;
	procesos[1].t_ejec_aux=procesos[1].t_ejec;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;
	procesos[2].t_ejec_aux=procesos[2].t_ejec;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;
	procesos[3].t_ejec_aux=procesos[3].t_ejec;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 4;
	procesos[4].t_ejec_aux=procesos[4].t_ejec;


	//cuando un proceso acabe, se restará 1 a i. Cuando todos acaben, se sale del bucle
	while (i > 0){


		//bucle que recorre el vector de procesos
		for(j=0; j<NPROC; j++){
			//solo entran aquellos que no han acabado
			if(procesos[j].t_ejec_aux!= 0){

				procesos[j].t_com=tiempo;

				
				for(k=0; k < quantum  && procesos[j].t_ejec_aux > 0; k++){
					tiempo++;
					procesos[j].t_ejec_aux--; 
				}
				    
				procesos[j].t_fin=tiempo;

				if (procesos[j].t_ejec_aux == 0){
					i--;
				}
				 

			}
	
		}

	}

	printf("\n  Proceso  |  t_retorno  |  t_espera\n");
	printf("----------------------------------------\n");

	for(i=0; i<NPROC; i++) {

		procesos[i].t_fin = procesos[i].t_com + procesos[i].t_ejec;
        procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
        procesos[i].t_esp = procesos[i].t_ret - procesos[i].t_ejec;
        
        printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
   }
}}
}