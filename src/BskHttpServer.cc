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

static pthread_mutex_t clientLock = PTHREAD_MUTEX_INITIALIZER;

#define BACKLOG 50

void* acceptEvent(void * context);
void* readEvent(void * context);
size_t readn(int fd, void* buffer, size_t size);
size_t writen(int fd, const void* buffer, size_t size);

/*************************************************/
BskHttpServer::BskHttpServer() :
      _acceptThread(0) {

}

/*************************************************/
BskHttpServer::~BskHttpServer() {
   // TODO Auto-generated destructor stub
}

void BskHttpServer::Poll() {

}

/*************************************************/
void* acceptEvent(void * context) {

   ServerContext* serverContext = (ServerContext*) context;

   while (true) {

      struct sockaddr clientAddr;
      socklen_t addrLen = sizeof(clientAddr);
      volatile int clientfd = accept(serverContext->serverfd, &clientAddr,
            &addrLen);
      if (clientfd < 0) {
         LOGE("Error accept %d %d", clientfd, errno);
         exit(EXIT_FAILURE);
      }

      LOGI("Got a client %d", clientfd);

      ClientContext* receiveContext = new ClientContext();
      receiveContext->active.store(true);
      receiveContext->clientfd = clientfd;

      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_create(&receiveContext->thread, &attr, &readEvent,
            receiveContext);
      pthread_attr_destroy(&attr);
   }

   return nullptr;
}

/*************************************************/
size_t readn(int fd, void* buffer, size_t size) {
   char* chBuffer = (char*)buffer;
   size_t totalBytesRead = 0;
   size_t bytesRead = 0;
   while (totalBytesRead < size) {

      bytesRead = read(fd, chBuffer, size - totalBytesRead);
      // EOF
      if (bytesRead == 0) {
         return totalBytesRead;

         // Error of some kind
      } else if (bytesRead == (size_t)-1) {

         // Interrupted restart
         if (errno == EINTR) {
            continue;
         } else {
            LOGE("Error reading %d ", errno);
            return -1;
         }
      }
      totalBytesRead += bytesRead;
      chBuffer += bytesRead;
   }
   return totalBytesRead;
}

/*************************************************/
size_t writen(int fd, const void* buffer, size_t size) {
   char* chBuffer = (char*)buffer;
   size_t totalBytesWrote = 0;
   size_t bytesWrote = 0;
   while (totalBytesWrote < size) {

      bytesWrote = write(fd, chBuffer, size - totalBytesWrote);
      // EOF
      if (bytesWrote <= 0) {
         // Interrupted restart
         if (bytesWrote == (size_t)-1 && errno == EINTR) {
            continue;
         } else {
            LOGE("Error writing %d ", errno);
            return -1;
         }
      }
      totalBytesWrote += bytesWrote;
      chBuffer += bytesWrote;
   }
   return totalBytesWrote;
}

/*************************************************/
void* readEvent(void * context) {
   ClientContext* receiveContext = (ClientContext*) context;

   LOGI("Got a client %d", receiveContext->clientfd);

   char buffer[1024] = { 0 };
   const char *hello = "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=ISO-8859-1\r\n"
         "Server: Mine\r\n"
         "Content-Length: 8\r\n\r\n"
         "Hello 99";

   while (true) {

      int bytesRead = readn(receiveContext->clientfd, buffer, 1024);
      LOGI("Read %d bytes", bytesRead);
      LOGI("%s", buffer);

      int len = strlen(hello);
      LOGI("Sending %s %d", hello, len);

      int totalByteSent = 0;
      while (totalByteSent < len) {

         int bytesSent = writen(receiveContext->clientfd, hello, len);
         if (bytesSent < 0) {
            //EROFS
            LOGE("Error sending %d ", errno);
            break;
         }
         totalByteSent += bytesSent;
      }

      //sleep(1);
      // TODO Check to keep alive
      close(receiveContext->clientfd);
      break;
   }
   return nullptr;
}

void Parse(std::string request) {

}

/*************************************************/
bool BskHttpServer::StartServer(int port) {

   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      LOGE("Cannot filter SIGPIPE");
      return false;
   }

   _serverContext.server = this;
   _serverContext.port = port;

   // Creating socket file descriptor
   if ((_serverContext.serverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      LOGE("socket error: %d", errno);
      return false;
   }

   // Forcefully attaching socket to the port 8080
   int opt = 1;
   if (setsockopt(_serverContext.serverfd, SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   if (setsockopt(_serverContext.serverfd, SOL_SOCKET,
   SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      LOGE("setsockopt error: %d", errno);
      return false;
   }

   struct sockaddr_in address;
   //memset(&address, 0, sizeof(sockaddr_in));
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(_serverContext.port);

   // Forcefully attaching socket to the port 8080
   if (bind(_serverContext.serverfd, (struct sockaddr *) &address,
         sizeof(address)) < 0) {
      LOGE("Error binding to port %d", _serverContext.port);
      return false;
   }

   if (listen(_serverContext.serverfd, BACKLOG) < 0) {
      LOGE("Error listen %d %d", _serverContext.serverfd, errno);
      return false;
   }

   LOGI("Listening on port %d", _serverContext.port);

   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_create(&_acceptThread, &attr, &acceptEvent, &_serverContext);
   pthread_attr_destroy(&attr);

   int ret;
   int* retp = &ret;

   pthread_join(_acceptThread, (void**) &retp);

   LOGI("Join main thread %d", ret);
   return true;
}

