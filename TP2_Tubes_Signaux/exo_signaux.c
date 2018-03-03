#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void traitement(int n){

	printf("\nL'entier saisi est négatif. \n\n");
	
}


int main(void) { 
    
	pid_t pid ;
	int descr[2];
	pipe(descr); 
	int entier = 0; 
	pid = fork ();
	int r;


	/* Processus père */ 
	if (pid !=0 ){ 

		printf("Saisir un entier quelconque : ");				

		while(1){

			close(descr[0]);
			scanf("%d", &entier);
			write(descr[1], &entier, sizeof(int));
			signal(SIGUSR1, traitement);
	
			sleep(0.5);
			printf("En saisir un autre : ");
		}
	}


	/* Processus fils */
	if (pid == 0) { 

		do {
			close(descr[1]);
			r = read(descr[0], &entier, sizeof(int));

			if (entier<0){
				kill (getppid(), SIGUSR1);
			}
 
		} while (r!=0);

	}

	return EXIT_SUCCESS;
}

