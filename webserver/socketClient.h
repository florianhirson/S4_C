#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int acceptConnection(int socket_serveur);
void traiterRequeteClient(char * message_client,FILE * fp);
int verifHeader(char* messageClient, char* cProtocole);
void traiterRequeteClient(char * messageClient,FILE * fp);
void sendResponse(FILE *client, int code, const char *reasonPhrase, const char *messageBody);
void traitementErr(FILE * fp, char * messageClient,int errorCode);
char *fgets_or_exit (char* buffer, int size, FILE* stream);

enum http_method {
  HTTP_GET ,
  HTTP_UNSUPPORTED ,
};
typedef struct
{
  enum http_method method ;
  int major_version ;
  int minor_version ;
  char * target ;
} http_request ;
