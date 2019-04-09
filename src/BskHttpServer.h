/*
 * BskHttpServer.h
 *
 *  Created on: Apr 9, 2019
 *      Author: user1
 */

#ifndef SRC_BSKHTTPSERVER_H_
#define SRC_BSKHTTPSERVER_H_

class BskHttpServer {
public:
   BskHttpServer();
   virtual ~BskHttpServer();

   void StartServer(int port);

};

#endif /* SRC_BSKHTTPSERVER_H_ */
