// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 80


int main(void){

  int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

 
  /* Demande de saisi du domaine et chemin du fichier */
    
  char domaine[32];
  printf("Entrer l'adresse du domaine désiré : \r\n");
  fgets(domaine, 32, stdin);
  char *position = strchr(domaine, '\n');
  *position = '\0';
 
  char chemin[32];
  printf("Entrer le chemin du fichier désiré : \r\n");
  fgets(chemin, 32, stdin);
  char *position2 = strchr(chemin, '\n');
  *position2 = '\0';
  
  
  /* Recupération de l'adresse IP de l'hote par appel DNS */

  struct hostent *hostinfo = gethostbyname(domaine);


 
  /* Configuration de la connexion TCP */
    
  sin.sin_addr = *( struct in_addr*)( hostinfo -> h_addr);
 
  sin.sin_family = AF_INET;

  sin.sin_port = htons(PORT);
 

 
  /* Tentative de connexion TCP sur l'IP trouvée */
    
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

    

  /* Mise en place de la requête GET de demande de fichier par concaténation */
    printf("debut concat : ");
  char buffer1[1024] = "GET ";
    
  strcat(buffer1, chemin);
  
  char buffer2[32] = "HTTP/1.1\r\n";
  
  strcat(buffer1, buffer2);
  
  sprintf(buffer2, "Host: ");
    
  strcat(buffer1, buffer2);
  strcat(buffer1, domaine);
  
  sprintf(buffer2, "\r\n\r\n");
  
  strcat(buffer1, buffer2);

printf("fin concat ");

    
  /* Envoi de la requête GET sur la connexion ouverte */
  send(sock,buffer1,strlen(buffer1),0);

    
    
  /* Reponse à la méthode GET envoyée */
  recv(sock, buffer1, 1024, 0);

  printf("\n%s", buffer1);

    
  /* Fermeture de la socket client */
  close(sock);

  return EXIT_SUCCESS;

}//main









