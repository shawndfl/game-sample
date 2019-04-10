/*
 * BskHttpServer.cc
 *
 *  Created on: Apr 9, 2019
 *      Author: user1
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#include "BskLogging.h"

#include "BskHttpServer.h"

static pthread_mutex_t messageLock = PTHREAD_MUTEX_INITIALIZER;
#define BACKLOG 50

void* acceptEvent(void * context);
void* readEvent(void * context);

typedef struct ListenContext {
   int port;
   BskHttpServer* server;
}ListenContext;

/*************************************************/
BskHttpServer::BskHttpServer() :
_acceptThread(0),
_serverSocket(-1) {

}

/*************************************************/
BskHttpServer::~BskHttpServer() {
   // TODO Auto-generated destructor stub
}

/*************************************************/
void* acceptEvent(void * context) {

   ListenContext* listenContext = (ListenContext*) context;
   volatile int serverSocket;

   // Creating socket file descriptor
   if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      LOGE("socket error");
      return nullptr;
   }

   // Forcefully attaching socket to the port 8080
   int opt = 1;
   if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
         sizeof(opt)) == -1) {
      int e = errno;
      LOGE("setsockopt error %d", e);
      return nullptr;
   }

   struct sockaddr_in address;
   //memset(&address, 0, sizeof(sockaddr_in));
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(listenContext->port);

   // Forcefully attaching socket to the port 8080
   if (bind(serverSocket, (struct sockaddr *) &address, sizeof(address)) < 0) {
      LOGE("Error binding to port %d", listenContext->port);
      return nullptr;
   }
   if (listen(serverSocket, BACKLOG) < 0) {
      LOGE("Error listen %d %d", serverSocket, errno);
      return nullptr;
   }

   LOGI("Listening on port %d", listenContext->port);

   while (true) {

      struct sockaddr clientAddr;
      socklen_t addrLen = sizeof(clientAddr);
      int clientfd = accept(serverSocket, &clientAddr, &addrLen);
      if (clientfd < 0) {
         LOGE("Error accept %d %d", clientfd, errno);
         exit(EXIT_FAILURE);
      }

      LOGI("Got a client %d", clientfd);
   }

   delete listenContext;
   return nullptr;
}

/*************************************************/
void* readEvent(void * context) {
   int socketfd = *(int*) context;

   while (true) {
      //valread = read(new_socket, buffer, 1024);
      //LOGI("Read %d bytes", valread);
      //LOGI("%s", buffer);

      //int len = strlen(hello);
      // LOGI("Sending %s %d", hello, len);
      // send(new_socket, hello, len, 0);
      //sleep(1);

      LOGI("listening on socket %d", socketfd);
      //close (server_fd);
      // close (new_socket);
   }
   return nullptr;
}

/*************************************************/
void BskHttpServer::StartServer(int port) {
   char buffer[1024] = { 0 };
   const char *hello = "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=ISO-8859-1\r\n"
         "Server: Mine\r\n"
         "Content-Length: 15\r\n\r\n"
         "Hello 99";

   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      LOGE("Cannot filter SIGPIPE");
   }

   ListenContext* context = new ListenContext();
   context->server = this;
   context->port = port;

   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_create(&_acceptThread, &attr, &acceptEvent, context);
   pthread_attr_destroy(&attr);

   int ret;
   int* retp = &ret;

   pthread_join(_acceptThread, (void**) &retp);

   LOGI("Join main thread %d", ret);
}

