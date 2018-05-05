/* CHAWAF _ MISSOUM */

#include "calcul.h"
#include "string.h"

CLIENT *clnt;

void
calcul_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *calcul_null_1_arg;
	reponse  *result_2;
	data  calcul_my_strcat_1_arg;

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
	result_2 = calcul_my_strcat_1(&calcul_my_strcat_1_arg, clnt);
	if (result_2 == (reponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


char* concatenation (char* a, char* b) {
 
 reponse *resultat;
 data parametre;

 parametre.arg1 = a;
 parametre.arg2 = b;

 resultat = calcul_my_strcat_1(&parametre, clnt);
 return resultat->concat;
}//concatenation


int
main (int argc, char *argv[])
{
	char *host; 
	char *a;
	char *b; 

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	clnt = clnt_create(host, CALCUL, VERSION_UN, "tcp");

	//on alloue de la memoire aux chaines a concaténer
	a = malloc(100*sizeof(char)); 
	b = malloc(100*sizeof(char));

	//on demande la saisi des chaines
	printf("Chaine 1 (100 caractères max) : ");
	fgets(a, 100, stdin);
	char *pos = strchr(a, '\n');
	*pos = '\0';

	printf("Chaine 2 (100 caractères max) : ");
	fgets(b, 100, stdin);
	pos = strchr(b, '\n');
	*pos = '\0';

	//on affiche la concaténation des chaines
	printf("Concatenation : %s\n", concatenation(a,b));

	calcul_1 (host); 

	//on libère la mémoire allouée
	free(a);
	free(b);

	exit (0);
}
