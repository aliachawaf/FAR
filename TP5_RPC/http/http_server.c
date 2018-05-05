/* CHAWAF _ MISSOUM */

#include "http.h"
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void *
http_null_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;
	return (void *) &result;
}


response *
http_request1_1_svc(data1 *argp, struct svc_req *rqstp)//analyse la requete et si elle est bonne recupere le descripteur du fichier
{
	static response  result;

	// Vérification du format de la requete GET
	char *token = strtok(argp->request, " ");

	if (strcmp(token, "GET")==0) {
        
		// On récupère le chemin du fichier
		char *chemin_fichier = strtok(NULL, " ");
		
		// On vérifie que l'on peut accéder au fichier et le lire
		if (access(chemin_fichier, F_OK | R_OK) == 0){

			//On ouvre le fichier en lecture seulement et récupère son descripteur
			int fd = open(chemin_fichier, O_RDONLY);
			result.fd = fd;

		} else {
			result.fd = -1; // -1 represente le cas d'erreur
			printf("Impossible d'ouvrir le fichier\n");
		}
        
	}else{ 
		result.fd = -1;  
		printf("Ce n'est pas une requete GET ! \n\n"); 
	}

	return &result;
}


 
response *
http_request2_1_svc(data2 *argp, struct svc_req *rqstp)
{
	static response  result;
	
	// On vide la chaine de caractère
	memset(result.char_read, 0, sizeof(result.char_read));

	// On lit les données du fichier grace au descripteur et on les enregistre dans char_read
	result.fd = argp->fd;
	result.byte_read_nbr = read(result.fd, result.char_read, BUFFER_SIZE);

	//Si on atteint la fin du fichier, on ne lit aucun byte et on ferme donc le fichier
	if (result.byte_read_nbr ==0) {
		close(argp->fd);
	} 

	return &result;
}
