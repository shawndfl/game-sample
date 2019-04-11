/*
 * BskHttpServer.h
 *
 *  Created on: Apr 9, 2019
 *      Author: user1
 */

#ifndef SRC_BSKHTTPSERVER_H_
#define SRC_BSKHTTPSERVER_H_

#include <queue>
#include <pthread.h>

class BskHttpServer;

typedef struct ClientContext {
   int clientfd = -1;
   pthread_t thread = 0;
   BskHttpServer* server = nullptr;

}ClientContext;

typedef struct ServerContext {
   int port = 0;
   int serverfd = -1;
   BskHttpServer* server = nullptr;
   bool listening = false;

}ServerContext;

class BskHttpServer {
public:
   struct Message {
      void* message;
      long size;
   };

   BskHttpServer();
   virtual ~BskHttpServer();

   bool StartServer(int port);

   void Poll();

private:
   std::queue<BskHttpServer::Message> _messages;
   pthread_t _acceptThread;

   ServerContext _serverContext;
   std::vector<ClientContext*>  _clients;
};

#endif /* SRC_BSKHTTPSERVER_H_ */
