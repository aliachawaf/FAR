/* CHAWAF _ MISSOUM */

#include "calcul.h"

void *
calcul_null_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;
	return (void *) &result;
}

reponse *
calcul_addition_1_svc(data *argp, struct svc_req *rqstp)
{
	static reponse result;

	result.somme = argp->arg1 + argp -> arg2;

	return &result;
}
