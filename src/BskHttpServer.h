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

class BskHttpServer {
public:
   struct Message {
      void* message;
      long size;
   };

   BskHttpServer();
   virtual ~BskHttpServer();

   void StartServer(int port);

private:
   std::queue<BskHttpServer::Message> _messages;
   pthread_t _acceptThread;
   int _serverSocket;
};

#endif /* SRC_BSKHTTPSERVER_H_ */
