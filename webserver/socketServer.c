#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int createServerSocket(){

  int socket_serveur;

  socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serveur == -1){
    /* traitement de l'erreur */
    perror("socket_serveur");
  }
  /*utilisation de la socket serveur */
  return socket_serveur;
}

void confServerSocket(int socket_serveur, int port) {
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET; /* Socket ipv4 */
  saddr.sin_port = htons(port); /*Port d'écoute */
  saddr.sin_addr.s_addr = INADDR_ANY; /*écoute sur toutes les interfaces */

  int optval = 1;
  if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, & optval, sizeof (int)) == -1) {
    perror ("Can not set SO_REUSEADDR option");
  }

  if (bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
    perror("bind socket_serveur");
    /* traitement de l'erreur */
  }
}

void startWaitingConnections(int socket_serveur) {
  if (listen(socket_serveur, 10) == -1) {
    perror("listen socket_serveur");
    /* traitement d'erreur */
  }
}
