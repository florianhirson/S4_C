#include <stdio.h>
#include <string.h>
#include "socket.h"
#include "socketClient.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void initialiser_signaux(void) {
  if(signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
  }
}

int main(int argc, char **argv){
  if(argc != 2) {
    perror("trop de parametres");
    return -1;
  }

  printf("creation serveur ...\n");
  int server = creer_serveur(atoi(argv[1]));
  if(server == -1) {
    perror("creer_serveur");
    return -1;
  }
  printf("serveur cree !\n");
  initialiser_signaux();
  
  while(acceptConnection(server) != -1){
      sleep(1);
      printf("ok\n");
  }
 

  printf("ENDED\n");
return 0;
}


