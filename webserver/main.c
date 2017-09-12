#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <stdint.h>



int main(int argc, char **argv){
  if(argc != 2) {
    perror("trop de parametres");
    return -1;
  }

  if(creer_serveur((uintptr_t) argv[1]) == -1) {
    perror("creer_serveur");
    return -1;
  }
  return 0;
}
