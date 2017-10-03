#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

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
    if (pid == 0) { /* Fils */
      FILE *fp = fdopen(socket_client, "w+");

      char message_client [512];

      /* On peut maintenant dialoguer avec le client */
      char *message_bienvenue = "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn\n\nPRAISE LORD CTHULHU ^(;,;)^\n\n\0";
      fprintf(fp, "<Pawnee>\n%s", message_bienvenue);
    
      if(fgets(message_client,512,fp)!=NULL) {
	puts("Message client :\0");
	puts(message_client);
      }
      fprintf(fp, "%s\n", message_client);


      
      fclose(fp);
      exit(EXIT_SUCCESS);
  		
    } else { /* Pere */
      if (close(socket_client) < 0){
	perror(" close ");
      }
    
    }
  
  
  return socket_client;
}
