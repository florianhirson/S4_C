
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
    traiterRequeteClient(message_client, fp);
    exit(EXIT_SUCCESS);
  		
  } else { /* Pere */
    if (close(socket_client) < 0){
      perror(" close ");
    }
    
  }
  
  
  return socket_client;
}

/**
   Verifie si l'entete de la requete est correct
   0 si correct
   -1 si requete incorrecte erreur 400 bad request
   -2 si le chemin est incorrect erreur 404 not found

 **/
int verifHeader(char* messageClient, char* cProtocole) {
  
  char *requete,*chemin,*protocole;
  char *cMessageClient = malloc(512*sizeof(char));
  strcpy(cMessageClient, messageClient);
  requete = strtok(cMessageClient, " ");
  
  if (strcmp(requete,"GET") == 0){
    if(! ((chemin=strtok(NULL, " ")) != NULL && (protocole=strtok(NULL, " ")) != NULL && strtok(NULL, " ") == NULL) ){
      return -1;
    }
  }else{
    return -1;
  }

  strcpy(cProtocole,protocole);
  
  if(!(strcmp(chemin,"/")==0))
    return -2 ;
  
  if(!(strcmp(protocole,"HTTP/1.0\r\n") == 0 || strcmp(protocole,"HTTP/1.1\r\n") == 0 )) {
    return -1;
  }
  return 0;
}

/**
   Verifie si il y a une ligne vide à la fin de la requete envoyée par le client
   0 si ligne vide
   -1 sinon
**/
int verifEndOfString(char* messageClient) {
  if(messageClient[strlen(messageClient)-1]=='\n'&&messageClient[strlen(messageClient)-2]=='\r'){
    return 0;
  }
  return -1;
}


void traiterRequeteClient(char * messageClient,FILE * fp) {     
  char * messageAcceuil="Welcome to Babushka's basement ! Have some kompot kamarad ! ☭☭☭☭\n";
  int code,codeFin;
  int ligne = 0;
  char * cProtocole=malloc(50*sizeof(char));
  
  while(fgets(messageClient,512,fp)!=NULL) {  
    if (ligne == 0) {	
	code=verifHeader(messageClient,cProtocole);
	if(code<0)
	  break;
      } else {
	codeFin=verifEndOfString(messageClient);
	if(codeFin<0)
	  break;
      }
    ligne++;
  }
  
  if( code<0 || codeFin<0){
    traitementErr(fp,messageClient,code);   
  }  else    {
    sendResponse (fp,200,"OK",messageAcceuil);
  }

  fclose(fp);
}

void sendResponse(FILE *client, int code, const char *reasonPhrase, const char *messageBody) {
  fprintf(client, "HTTP/1.1 %d %s\r\n", code, reasonPhrase);
  if(code != 200) {
    fprintf(client, "Connection: close\r\n");
  }
  fprintf(client, "Content-Length: %zd\r\n\r\n%s", strlen(messageBody), messageBody);
  fflush(client);
}

void traitementErr(FILE * fp, char * messageClient,int errorCode){
  while(fgets(messageClient,512,fp)!=NULL);
  if(errorCode<-1){
    sendResponse (fp,404,"Not Found","Not Found\r\n");  
  }else{
    sendResponse (fp,400,"Bad request","Bad request\r\n");
  }
}


