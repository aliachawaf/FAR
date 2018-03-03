#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    
	pid_t pid;
	int descr [2]; 
	pipe(descr);
	pid = fork();

	int entier, somme = 0;
	int nb_entiers_saisis = -1;
	int encore = 1;
	int r; 

    	/* Processus fils */
	if (pid == 0) { 

		while(encore){
			printf("Entrer un entier : ");
			scanf("%d", &entier);
			close(descr[0]);
			write(descr[1], &entier, sizeof(int));

			printf("\nVoulez-vous effectuer une autre saisie ? (1 : oui, 0 : non) ");
			scanf("%d", &encore);
		}
	}


	/* Processus père */ 
	if (pid !=0 ){ 

		wait(0);

		do{ 
			close(descr[1]);
			somme = somme + entier;
			nb_entiers_saisis += 1;
			r = read(descr[0], &entier, sizeof(int));
		} while (r!=0); 

		printf("\nLa moyenne des entiers saisis vaut %f\n", (float)somme/nb_entiers_saisis);       
	}

	return EXIT_SUCCESS;
}













