#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 256
#define PORT "52111"
#define TEST_IP "127.0.0.1"

void error_check(int i, char *s);
int client_listen();
int client_accept(int sd);
int client_connect(char * other_client);


#endif
