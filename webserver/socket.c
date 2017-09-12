#include "socketServer.h"
#include "socketClient.h"

int creer_serveur(int port) {
  int socket_serveur = createServerSocket();
  confServerSocket(socket_serveur,port);
  startWaitingConnections(socket_serveur);


  return 0;
}
