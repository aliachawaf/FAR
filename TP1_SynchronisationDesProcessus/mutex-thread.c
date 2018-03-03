#define _POSIX_SOURCE 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//#include <sys/types.h> // for gettid() (linux)

int NB_THREADS = 10;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variable globale = partagee par tous les threads. 
int somme = 0;

// Run by each thread
void *Fils (void *t) {
  // Nombres aleatoires
  //sur LINUX : srand(time(NULL) ^ (gettid()<<16));
  srand(time(NULL) ^ ((int)pthread_self()<<16)); // sur Mac
  int i= (long)t; 
  int randomTime;
  int tmp = somme;
  tmp ++;
  // Pour faire attendre le processus
  randomTime = rand() % 3;
  sleep(randomTime);
  somme = tmp;
  printf("Fils %d : somme = %d \n", i, somme); 
  // ends the thread so that it doesn't come back in the main
  pthread_exit(0);
}

int main (int argc, char ** argv) {
  	pthread_t tid;
  	pthread_t Threads_id [NB_THREADS] ;
    int i;
    // Valeur du compteur avant de lancer les threads:
    printf ("Père : somme = %d\n", somme);
    //
  	for (i=0;i<NB_THREADS;i++) { 
		if  (pthread_create (&tid, NULL, Fils,NULL) != 0) {
      		printf("pthread_create\n"); exit (1);
 	    }
 	    else {Threads_id[i] = tid;}
    }
    // Main thread itself could access the shared variable
    // with mutex manipulation:
    // ...


    // Waits for all launched threads
	  for (i=0;i<NB_THREADS;i++) { 
    	pthread_join (Threads_id[i], NULL);     
 	}
  printf ("Père : somme = %d\n", somme);
       
  return EXIT_SUCCESS;
}

