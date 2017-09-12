#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int acceptConnection(int socket_serveur){

  int socket_client;
  printf("tentative de connexion ...\n");
  socket_client = accept(socket_serveur,NULL,NULL);
  printf("connecté !\n");
  
  if (socket_client == -1){
    perror("accept\n");
    /*traitement d'erreur*/
  }
  
  /* On peut maintenant dialoguer avec le client */
  const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
  write(socket_client, message_bienvenue, strlen(message_bienvenue));

  return socket_client;
}
