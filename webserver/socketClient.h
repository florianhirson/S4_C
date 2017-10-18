#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

enum http_method {
  HTTP_GET ,
  HTTP_UNSUPPORTED ,
};

typedef struct {
  enum http_method method ;
  int major_version ;
  int minor_version ;
  char * target ;
} http_request ;


int acceptConnection(int socket_serveur);
void traiterRequeteClient(char * message_client,FILE * fp);
void send_response(FILE *client, int code, const char *reason_phrase, const char *message_body);
void send_status( FILE * client , int code , const char * reason_phrase );
char *fgets_or_exit (char* buffer, int size, FILE* stream);
void skip_headers(FILE *clients);
int parse_http_request(const char* request_line, http_request* request);

