/* CHAWAF _ MISSOUM */

#include "calcul.h"
#include "string.h"

void *
calcul_null_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	return (void *) &result;
}

reponse *
calcul_my_strcat_1_svc(data *argp, struct svc_req *rqstp)
{
	static reponse  result;

	//on utilise une variable buffer qui valera la concaténation des 2 arguments 
	char* buffer;

	/*size represente la taille du buffer en nb de caractères 
	(ajoute 1 pour le caractere de fin de chaine)*/
	int size = strlen(argp->arg1) + strlen(argp->arg2) + 1;

	/* on alloue de la mémoire pour le buffer et concat
	(multiplie le nb de caractere par sizefof(char) car l'allocation se fait selon les bits) */
	buffer = malloc(size*sizeof(char));
	result.concat = malloc(size*sizeof(char));
    
    //Concaténation
    strcpy(buffer, argp->arg1);	// => buffer = arg1
    strcat(buffer, argp->arg2);	// => buffer = arg1arg2
	strcpy(result.concat, buffer); // => concat = buffer
	
	//on libère la memoire allouée
	free(buffer);

	return &result;
}
