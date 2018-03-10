// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define PORT 10000

void  traitement (int sock) {	
	shutdown(sock, 2);	
	close(sock);
	
	printf("\nSocket convenablement fermée !\n");
	
	exit(0);	
}


int main(void) {

  int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

  /*reception du message recu du serveur*/
  char buffer[32]="";
  recv(sock,buffer,32,0);
  printf("%s\n", buffer);
  
  /*envoi du message au serveur*/
  char buffer2[32]="Merci beaucoup !\n";
  send(sock,buffer2,32,0);


  while (1){
  	/*envoie un 2eme message au serveur*/

  	//saisi du message par l'utilisateur
	char buffer3[32];
	printf("entrer votre message : ");
	fgets(buffer3, 32, stdin);
	char *position = strchr(buffer3, '\n');
	*position = '\0';
	
	//envoi du message saisi
	send(sock,buffer3,32,0);

	//on rattrape le Ctrl-C pour qu'il ferme la socket
	signal(SIGINT , traitement );
  }

  /* Fermeture de la socket client */
  shutdown(sock, 2);
  close(sock);


  return EXIT_SUCCESS;

}//main
