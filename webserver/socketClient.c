
#include "socketClient.h"

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
    traiterMessageClient(message_client, fp);
    exit(EXIT_SUCCESS);
  		
  } else { /* Pere */
    if (close(socket_client) < 0){
      perror(" close ");
    }
    
  }
  
  
  return socket_client;
}

void traiterMessageClient(char * message_client,FILE * fp) {
  int succes = -1, succes_http=-1;
  int ligne = 0;
  char * requete;
  char * chemin;
  char * protocole;
  char * copie = malloc(512*sizeof(char));// malloc de 512 characteres
  
  while(fgets(message_client,512,fp)!=NULL) {
      
    strcpy(copie,message_client);//copie la string pointée par message_client dans copie
    
    if (ligne == 0) {	
      requete = strtok(message_client, " ");// separe les mots dans la string
      
      if (strcmp(requete, "GET") == 0) { //compare la string requete a GET
	
	if ((chemin=strtok(NULL, " ")) != NULL && (protocole=strtok(NULL, " ")) != NULL
	    && strtok(NULL, " ") == NULL) { //check si les 3 mots de l'entetes ne sont pas null

	  succes = 0;
	}
      }
	
	  
      if (succes != 0) {	      
	printf("ERROR : Bad Request (%s) !\n", requete);
	break;
      }
      
     	  
      if(strcmp(protocole,"HTTP/1.0\r\n") == 0 || strcmp(protocole,"HTTP/1.1\r\n") == 0) {
	succes_http++;
      }
      else if(strcmp(protocole,"HTTP/1.0") == 0 || strcmp(protocole,"HTTP/1.1") ==0 ) {
	fprintf(fp,"%s : 400 Bad Request\r\n", protocole);
	break;
      }
      printf("%s", copie);
    }
      
    ligne += 1;
  }
  free(copie);
  fprintf(fp, "Connection: close\n");
  
  fclose(fp);


}



