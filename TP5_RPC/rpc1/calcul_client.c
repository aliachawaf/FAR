/* CHAWAF _ MISSOUM */

#include "calcul.h"


void
calcul_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *calcul_null_1_arg;
	reponse  *result_2;
	data  calcul_addition_1_arg;

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
	result_2 = calcul_addition_1(&calcul_addition_1_arg, clnt);
	if (result_2 == (reponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

CLIENT *clnt;

int addition (int a, int b) {
 reponse *resultat;
 data parametre;
 parametre.arg1 = a;
 parametre.arg2 = b;
 resultat = calcul_addition_1 (&parametre, clnt);
 return resultat->somme;
}//addition


int
main (int argc, char *argv[])
{
	char *host;
	int a, b;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	clnt = clnt_create (host, CALCUL, VERSION_UN, "tcp");
	printf("Entier 1 : ");
	scanf("%d", &a);
	printf("Entier 2 : ");
	scanf("%d", &b);
	printf("Somme = %d\n", addition(a, b));
	calcul_1 (host);
	exit (0);
}
