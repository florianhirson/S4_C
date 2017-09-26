#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int acceptConnection(int socket_serveur){

  int socket_client;
  printf("tentative de connexion ...\n");
  socket_client = accept(socket_serveur,NULL,NULL);
  printf("connecté !\n");
  
  if (socket_client == -1){
    perror("accept\n");
    /*traitement d'erreur*/
  }

  int pid = fork();
  if (pid == 0) {
     
    /* On peut maintenant dialoguer avec le client */
    const char *message_bienvenue = "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn\n\n PRAISE LORD CTHULHU ^(;,;)^\n\n";
    write(socket_client, message_bienvenue, strlen(message_bienvenue));
  } else {
    if (close(socket_client) < 0)
      {
	perror(" close ");
      }
  }

  return socket_client;
}
