/* CHAWAF _ MISSOUM */

#include "heure.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *
calcul_null_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	return (void *) &result;
}

reponse *
calcul_my_time_1_svc(data *argp, struct svc_req *rqstp)
{
	static reponse  result;

	struct sockaddr_in sin;

	/* Création de la socket */
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Configuration de la connexion TCP */    
	sin.sin_addr.s_addr = inet_addr(argp->ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(argp->port);
	 
	/* Tentative de connexion TCP sur l'IP */   
	connect(sock, (struct sockaddr*)&sin, sizeof(sin));
	  
	printf("Connexion a time-c-g.nist.gov sur le port %d\n", htons(sin.sin_port));
	printf("\n");
  
	//on utilise une variable buffer qui valera la reponse recue 
	char* buffer;

	/* on alloue de la mémoire pour le buffer et concat */
	buffer = malloc(50*sizeof(char));
	result.message = malloc(50*sizeof(char));
        printf("\n");

        //Reception reponse 
	recv(sock, buffer, 1024, 0);	
	printf("\n");

	strcpy(result.message, buffer); // => message = buffer
	printf("\n");

	//on libère la memoire allouée
	free(buffer);

	/* Fermeture de la socket client */
	close(sock);

	return &result;
}
