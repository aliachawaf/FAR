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

void
calcul_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *calcul_null_1_arg;
	reponse  *result_2;
	data  calcul_my_time_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCUL, VERSION_UN, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = calcul_null_1((void*)&calcul_null_1_arg, clnt);
	if (result_1 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = calcul_my_time_1(&calcul_my_time_1_arg, clnt);
	if (result_2 == (reponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

CLIENT *clnt; 

char* fuseauHoraire(char* ip, int port){

	reponse *resultat;
 	data parametre;

	parametre.ip = ip;
	parametre.port = port;

	resultat = calcul_my_time_1(&parametre, clnt);
	return resultat->message;

}



int
main (int argc, char *argv[])
{
	char *host;
	char *ip;
	int port = 13; 

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	clnt = clnt_create(host, CALCUL, VERSION_UN, "tcp");

	
	//on alloue de la memoire
	ip = malloc(32); 

	sprintf(ip, "%s", "129.6.15.30"); 

	//on affiche la concaténation des chaines

	printf("Date et heure du fuseau horaire : \n%s\n", fuseauHoraire(ip, port) );

	calcul_1 (host); 

	//on libère la mémoire allouée
	free(ip);

	calcul_1 (host);
exit (0);
}
