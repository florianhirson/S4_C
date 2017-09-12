#include <stdio.h>

int createServerSocket(){

  int socket_serveur;

  socket_serveur = socket(AF_INET, SOCK_STREAM, O);
  if (socket_serveur == -1){
    /* traitement de l'erreur */
    perror("socket_serveur");
  }
  /*utilisation de la socket serveur */
}
