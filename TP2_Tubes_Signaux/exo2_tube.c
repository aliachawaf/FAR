#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

	pid_t pid ;

	//on crée 2 tubes pour pouvoir faire les aller-retours entre les processeurs
	int descr1[2];
	pipe(descr1);

	int descr2[2];
	pipe(descr2);
	pid = fork ();

	int entier = 0;



	// Processus père
	if (pid !=0 ){  

		printf("Entrer 5 entiers : \n");     

		for(int i=0; i<5; i++){

			close(descr1[0]);
			scanf("%d", &entier);
			write(descr1[1], &entier, sizeof(int));
		}

		wait(0);

		printf("\nVoici les entiers incrémentés et mis au carré : ");

		for(int i=0; i<5; i++){
			close(descr2[1]);
			read(descr2[0], &entier, sizeof(int));
			entier = entier*entier;

			printf("%d ", entier);
		}
		printf(".\n");
	}    



	// Processus fils
	if (pid == 0) { 

		for(int i=0; i<5; i++){

			close(descr1[1]);
			read(descr1[0], &entier, sizeof(int));
			entier = entier + 1;

			close(descr2[0]);
			write(descr2[1], &entier, sizeof(int));
		}
	}

	return EXIT_SUCCESS;
}
