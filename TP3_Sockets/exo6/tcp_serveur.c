// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define PORT 10000
#define NB_THREADS 5


void waitFunc(){
    wait(0);
}


void * Fils(void * csock_temporaire) {
    
 	int  csock=*(int*)csock_temporaire;
    
	/*envoi du message au client*/
	char buffer[32]="Bonjour !";
	send(csock,buffer,32,0);

	/*reception du message recu du client*/
	char buffer2[32]="";
	recv(csock,buffer2,32,0);
	printf("%s", buffer2);

	/*reception du 2eme message entré par l'utilisateur et recu du client*/
	char buffer3[32]="";

	while (recv(csock,buffer3,32,0) >0 ){
		printf("%s\n", buffer3);
	}

	/*Fermeture de la socket client*/
	shutdown(csock, 2);
	close(csock);	
	pthread_exit(0);
}


int main(void) {
    
  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);
 
  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Démarrage du listage (mode server) */
  listen(sock, 5);

  pthread_t *thread;
  pthread_attr_t attr;
  
  /* on accepte en boucle des connexions clients */
  while (1){

      /* Attente d'une connexion client */
      csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
      printf("Un client se connecte avec la socket %d de %s:%d\n",csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
    
      // Thread detaché
      pthread_attr_init(&attr);
      pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
      
      // Creation thread
      pthread_create(&thread, NULL, Fils, (void *)&csock);
        
  }

  /* Fermeture de la socket serveur */
  shutdown(sock, 2);
  close(sock);

  return EXIT_SUCCESS;

}//main
