// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void proc_exit(int sig) {
  int status;
  wait(&status);
}


int main(void) {
  
  /* Saisi du répertoire de reference */
  printf("Saisir le répertoire de reference (chemin DUR !) : \n");
  char repertoireRef[1024];
  fgets(repertoireRef, 1024, stdin);
  char *position = strchr(repertoireRef, '\n');
  *position = '\0';

  char repertoire[1024];
    
  /* Saisi du port */
  int PORT;
  printf("Saisir le port d'écoute (non réservé) : ");
  scanf("%d", &PORT);
    
  /* Pour éviter les zombies */
  signal(SIGCHLD, proc_exit);

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);

  /* Pour forker le moment venu */
  pid_t pid;
 
  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Démarrage du listage (mode server) */
  listen(sock, 5);

  for(;;) {
    /* Attente d'une connexion client */
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    printf("Un client se connecte avec la socket %d de %s:%d\n",
           csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

    pid = fork();

    if (pid == 0) {
      /* Envoi de données au client */
      char buffer[1024] = "Bonjour !";
      send(csock, buffer, 1024, 0);

      for(;;) {
        /* Reception de données du client */
        int res = recv(csock, buffer, 1024, 0);
        if (res == 0)
          break;
        
	printf("Recu de la socket %d de %s:%d : %s\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port), buffer);

	// verification du format de la requete GET
	char *tok = strtok(buffer, " ");
          
        char message[1024]="";

	if (strcmp(tok, "GET")==0) {
        
		// On récupère le nom du fichier
		char *fichier = strtok(NULL, " ");
		
		tok = strtok(NULL, "\t\n");

		strcpy(repertoire, repertoireRef);
	        strcat(repertoire, fichier);

		FILE* reponse = NULL;
		reponse = fopen(repertoire, "r+");
		
		if (reponse != NULL){

			fread(message, sizeof(char), 1024, reponse);
			printf("\n");
			send(csock, message, 1024, 0); printf("\n");
			fclose(reponse);
		
		} else {
			printf("Impossible d'ouvrir le fichier\n");
			
		  	}
        
	}else{ 
		send(csock, message, 1024, 0); 
		printf("Ce n'est pas une requete GET ! \n\n"); 
	     }
				
      }//for

      /* Fermeture de la socket dans les deux sens */
      shutdown(csock, 2);

      /* Fermeture de la socket client */
      close(csock);
      exit(0);

    }//if
  }//for

  /* Fermeture de la socket serveur */
  close(sock);

  return EXIT_SUCCESS;

}//main
