#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
  const char *message_bienvenue = "                                    xxxxxxx\n                               x xxxxxxxxxxxxx x\n                            x     xxxxxxxxxxx     x\n                                   xxxxxxxxx\n                         x          xxxxxxx          x\n                                     xxxxx\n                        x             xxx             x\n                                       x\n                       xxxxxxxxxxxxxxx   xxxxxxxxxxxxxxx\n                        xxxxxxxxxxxxx     xxxxxxxxxxxxx\n                         xxxxxxxxxxx       xxxxxxxxxxx\n                          xxxxxxxxx         xxxxxxxxx\n                            xxxxxx           xxxxxx\n                              xxx             xxx\n                                  x         x\n                                       x\n";
  write(socket_client, message_bienvenue, strlen(message_bienvenue));

  return socket_client;
}
