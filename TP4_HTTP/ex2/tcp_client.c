// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sock;

void close_exit (int n) {
  /* Fermeture de la socket client */
  shutdown(sock, 2);
  close(sock);
  exit(0);
}

int main(void) {
  
  struct sockaddr_in sin;

  /* Saisi du port */
  char port[32] = "";
  printf("Saisir le port (non réservé) : ");
  fgets(port, 32, stdin); 
  printf("\n");
  char *pos = strchr(port, '\n');
  *pos = '\0';

  int PORT = atoi(port);

  /* Rattraper le Ctrl-C */
  signal(SIGINT, close_exit);

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));


  /* Réception de données du serveur */
  char buffer[1024] = "";
  recv(sock, buffer, 1024, 0);
  printf("Recu : %s\n", buffer);

  char reponse[1024]="";
    
  for(;;) {
    /* Envoi de données au serveur */
    printf("Donnees a envoyer au serveur : ");
    fgets(buffer, 1024, stdin); 
    char *pos = strchr(buffer, '\n');
    *pos = '\0';
    send(sock, buffer, 1024, 0);

    /* reception reponse GET */ 
    if ( recv(sock,reponse, 1024,0) > 0){
      printf("\n%s ", reponse);
    }
    
  }//for

  return EXIT_SUCCESS;

}//main
