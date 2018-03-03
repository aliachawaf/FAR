#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#define NB_THREADS 500 
int somme=0;
void * Fils(void *t) {
	int i= (long)t;	
	int tmp = somme;
	tmp ++;
	somme = tmp;
	printf("Fils %d : somme = %d \n", i, somme); 
	pthread_exit(0);
}

int main() {
	long i;
	pthread_t thread[NB_THREADS]; 
	for (i=0;i<NB_THREADS;i++)
		pthread_create(&thread[i], NULL, Fils, (void *)i); 
	for (i=0;i<NB_THREADS;i++) 
		pthread_join(thread[i], NULL); 
	printf("Pere : somme = %d \n", somme); return 0;
}