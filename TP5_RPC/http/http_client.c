/* CHAWAF _ MISSOUM */


#include "http.h"
 
CLIENT *clnt;
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int request1(char* request) {
	response *resultat;
	data1 argp;

	strcpy(argp.request, request);

	//Appel a la fct du serveur qui traite la requete
	resultat = http_request1_1(&argp, clnt);

	//On retourne le descripteur du fichier
	return resultat->fd;
}


void request2(int fd) {
	response *resultat;
	data2 argp;
	argp.fd = fd;
	
	printf("\n *************** Debut du fichier *************** \n\n\n");
	
	do {
	//appel a la fct du serveur qui lit les donnees
	resultat = http_request2_1(&argp, clnt);

	argp.fd = resultat->fd;

	printf("%s", resultat->char_read);//On affiche le paquet lu

	} while(resultat->byte_read_nbr !=0);//On s'arrete quand il n'y a plus rien a lire 
		

	//Quand on atteint la fin
	if(resultat->byte_read_nbr == 0){
		printf("\n\n *************** Fin du fichier *************** \n\n");
	}
}

 
int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	clnt = clnt_create(host, HTTP, VERSION_UN, "tcp");


	//Demande de saisi de la requete
	printf("Saisir votre requete (mettre le chemin en dur pour accéder au fichier) : \n");
	char requete[1024];
	fgets(requete, 1024, stdin);
	char *pos = strchr(requete, '\n');
	*pos = '\0';

	//On récupère le descripteur du fichier grace a la fct du client
	int fd = request1(requete);
	
	if (fd != -1) { 	//Si pas d'erreur
		request2(fd);	//On fait appel a la fonction du client qui lit le fichier désiré

	} else {
		printf("Fichier non trouvé\n");
	}

exit (0);
}
