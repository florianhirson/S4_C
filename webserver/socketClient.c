
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
  		
  } else{ /* Pere */
    if (close(socket_client) < 0){
      perror(" close ");
    }    
  }  
  return socket_client;
}



void traiterRequeteClient(char * messageClient,FILE * fp) {     
  char * messageAcceuil="Welcome to Babushka's basement ! Have some kompot kamarad ! ☭☭☭☭\n";
  int code;
  int ligne = 0;
  http_request *request = malloc(1024);

  while(fgets_or_exit(messageClient,512,fp)!=NULL) {  
    if (ligne == 0) {	
      code = parse_http_request(messageClient, request);
      printf("code etat 1 : %d\n", code);
      if(code == 0)
	break;
    } else {
      
    }
    ligne++;
  }

  if (code == 0) {
    printf("code : %d\n",code);
    send_response (fp, 400, " Bad Request ", " Bad request \r \n ");
  } else if (request->method == HTTP_UNSUPPORTED)
    send_response (fp, 405, " Method Not Allowed ", " Method Not Allowed \r \n ");
  else if (strcmp(request->target, "/" ) == 0)
    send_response(fp, 200, " OK ", messageAcceuil);
  else
    send_response(fp, 404, " Not Found ", " Not Found \r \n ");
  fclose(fp);
}

char *fgets_or_exit (char* buffer, int size, FILE* stream) {
  //char * tmp = buffer;
  char * retour = fgets(buffer, size, stream);
  /*
  if(retour == NULL) {
      send_response(stream,400,"Bad Request","Bad Request (Line Separator Not Found)\r\n");
    }
    exit(EXIT_SUCCESS);
    }*/
  return retour;
}

/**
 * Analyse la premiere ligne de la requete du client
 * const char* request_line 1ere ligne de la requete du client
 * structure de la requete http
 * Retourne 0 si invalie et 1 sinon
 **/
int parse_http_request(const char* request_line, http_request* request) {
  char *requestMethod, *resourceLink, *protocolVersion;
  int rl_minor_version, rl_major_version;

  char *cp;
  cp = strdup(request_line);
  requestMethod = strtok(cp, " ");
  resourceLink = strtok(NULL, " ");
  protocolVersion = strtok(NULL, "/");
  
  rl_major_version = (int) protocolVersion[5] - 48;
  rl_minor_version = (int) protocolVersion[7] - 48;

  if (strcmp(requestMethod, "GET") == 0){
    request->method=HTTP_GET;
    printf("Erreur de methode get\n");
  } else {
    printf("Erreur non supporté\n");
    request->method=HTTP_UNSUPPORTED;
    printf(requestMethod);
    free(cp);
    return 0;
  }

  request->major_version = rl_major_version;  
  request->minor_version = rl_minor_version;
  printf("minor version : %d\n",rl_minor_version);
  printf("major version : %d\n",rl_major_version);
 
  if (rl_major_version != 1 || rl_minor_version < 0 || rl_minor_version > 1) {
    printf("Erreur de version\n");
    return 0;    
  }
  
  request -> target=resourceLink;
  
  if (request->target[0]!='/') {
    printf("Erreur de cible\n");
    return 0;
  }
  
  return 1;
}

void skip_headers(FILE *clients) {
  char buffer[1024];
  while(fgets_or_exit(buffer, sizeof(buffer), clients)!=NULL && (strncmp(buffer, "\r\n", 2) != 0)) {

  }
}

void send_status( FILE * client , int code , const char * reason_phrase ) {
  fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
  if(code != 200) {
    fprintf(client, "Connection: close\r\n");
  }

}

void send_response(FILE *client, int code, const char *reason_phrase, const char *message_body) {
  send_status(client,code, reason_phrase);
  if(code != 200){
    fprintf(client, "Content-Length: %zd\r\n\r\n%s", strlen(message_body), message_body);
    printf("Content-Length: %zd\r\n\r\n%s", strlen(message_body), message_body);
  } else {
    fprintf(client, "%s", message_body);
  }
  
  fflush(client);

}



