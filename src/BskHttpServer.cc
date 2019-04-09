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

#include "BskLogging.h"

#include "BskHttpServer.h"

/*************************************************/
BskHttpServer::BskHttpServer() {

}

/*************************************************/
BskHttpServer::~BskHttpServer() {
   // TODO Auto-generated destructor stub
}

/*************************************************/
void BskHttpServer::StartServer(int port) {
   int server_fd, new_socket, valread;
   struct sockaddr_in address;
   int opt = 1;
   int addrlen = sizeof(address);
   char buffer[1024] = { 0 };
   const char *hello = "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=ISO-8859-1\r\n"
         "Server: Mine\r\n"
         "Content-Length: 15\r\n\r\n"
         "Hello 99";

   // Creating socket file descriptor
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      LOGE("socket error");
      return;
   }

   // Forcefully attaching socket to the port 8080
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
         sizeof(opt))) {
      LOGE("setsockopt error");
      return;
   }
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(port);

   // Forcefully attaching socket to the port 8080
   if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
      LOGE("Error binding to port %d", port);
      return;
   }
   if (listen(server_fd, 3) < 0) {
      LOGE("Error listening %d", port);
      exit(EXIT_FAILURE);
   }
   if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
         (socklen_t*) &addrlen)) < 0) {
      LOGE("Error accept");
      exit(EXIT_FAILURE);
   }

   //while (true) {
      valread = read(new_socket, buffer, 1024);
      LOGI("Read %d bytes", valread);
      LOGI("%s", buffer);

      int len = strlen(hello);
      LOGI("Sending %s %d", hello, len);
      send(new_socket, hello, len, 0);
      sleep(1);

      LOGI("Sent Message");
      close(server_fd);
      close(new_socket);
   //}
}
