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
#include <string>
#include <atomic>

class BskHttpServer;

/**
 * Simple key value pair. Used for headers and parameters.
 */
typedef struct KeyValue {
   std::string key;
   std::string value;

} KeyValue;

/**
 * This structure can handle a response.
 * see https://tools.ietf.org/html/rfc7230#section-3.1.2
 * Format is:
 *    HTTP-version SP status-code SP reason-phrase CRLF
 *    Headers
 *    Message Body
 */
struct Response {
   /**
    *  Status Line
    *  the http version
    */
   std::string httpVersion;

   /**
    * The 3 digit status code.
    * See https://tools.ietf.org/html/rfc7231#section-6
    *
    * 1xx (Informational): The request was received, continuing process
    * 2xx (Successful): The request was successfully received,
    *     understood, and accepted
    * 3xx (Redirection): Further action needs to be taken in order to
    *     complete the request
    * 4xx (Client Error): The request contains bad syntax or cannot be
    *     fulfilled
    * 5xx (Server Error): The server failed to fulfill an apparently
    *     valid request
    */
   std::string statusCode;

   /**
    *    Reason code Human readable reason.
    */
   std::string reasonPhase;

   /**
    * Headers
    */
   std::vector<KeyValue> headers;

   /**
    * Body
    */
   std::string body;

};

/**
 * The request from the client.
 *  See https://tools.ietf.org/html/rfc7230#section-3.1.1
 *  Format is:
 *    method SP request-target SP HTTP-version CRLF
 *    Headers
 *       key: value
 *    Body
 */
struct Request {
   enum ParseState {
      NewRequest,
      IncompleteStartLine,
      IncompleteHeader,
      IncompleteMessage,
      Complete
   };
   /**
    * The state of the request. It may be incomplete
    * due to tcp frames
    */
   ParseState parsedState;

   /**
    * The line that is being read from
    * the network. When The message is
    * complete this will be empty. Else
    * it will be the last line in the buffer.
    *
    * The next read will append to this and continue
    * parsing.
    */
   std::string parsedLine;

   /**
    *  The http version
    */
   std::string httpVersion;

   /**
    * The request method
    * See https://tools.ietf.org/html/rfc7231#section-4
    *     +---------+-------------------------------------------------+-------+
    *     | Method  | Description                                     | Sec.  |
    *     +---------+-------------------------------------------------+-------+
    *     | GET     | Transfer a current representation of the target | 4.3.1 |
    *     |         | resource.                                       |       |
    *     | HEAD    | Same as GET, but only transfer the status line  | 4.3.2 |
    *     |         | and header section.                             |       |
    *     | POST    | Perform resource-specific processing on the     | 4.3.3 |
    *     |         | request payload.                                |       |
    *     | PUT     | Replace all current representations of the      | 4.3.4 |
    *     |         | target resource with the request payload.       |       |
    *     | DELETE  | Remove all current representations of the       | 4.3.5 |
    *     |         | target resource.                                |       |
    *     | CONNECT | Establish a tunnel to the server identified by  | 4.3.6 |
    *     |         | the target resource.                            |       |
    *     | OPTIONS | Describe the communication options for the      | 4.3.7 |
    *     |         | target resource.                                |       |
    *     | TRACE   | Perform a message loop-back test along the path | 4.3.8 |
    *     |         | to the target resource.                         |       |
    *     +---------+-------------------------------------------------+-------+
    */
   std::string method;

   /**
    * URI used by the request
    */
   std::string uri;

   /**
    * Parameters used by the request. This is pulled out
    * of the Uri query.
    */
   std::vector<KeyValue> parameters;

   /**
    * Headers
    */
   std::vector<KeyValue> headers;

   /**
    * Body
    */
   std::string body;

   /**
    * gets the size of the body based on the
    */
   int getBodySize() const;

   /**
    * Parses the request line. This is the first line in
    * the request. Its format is:
    *    method SP request-target SP HTTP-version CRLF
    */
   bool ParseRequestLine(const std::string& line);
   /**
    * Parse header. This will parse a single line.
    * it should be in the form of:
    *    field-name: field-value
    */
   bool ParseHeaderLine(const std::string& line);

   bool AppendToBody(const std::string& chunk);

   /**
    * This error code can be set when parsing
    * the request. If invalid characters are found
    * this will be set and a response will be sent
    * to the client with this number.
    */
   int parseErrorCode;
};

/**
 * The context of the client connect.
 * The user should fill out the response structure
 * and call the SendResponse() function.
 */
typedef struct ClientContext {
   int clientfd = -1;
   pthread_t thread = 0;
   BskHttpServer* server = nullptr;

   /**
    * This will be filled in by the server.
    */
   struct Request* request;

   /**
    * The response from the server
    */
   struct Response* response;

   /**
    * Call this after Response is fill out
    */
   void SendResponse();

} ClientContext;

/**
 * The structure for the server connection
 */
typedef struct ServerContext {
   int port = 0;
   int serverfd = -1;
   BskHttpServer* server = nullptr;
   bool listening = false;

} ServerContext;

class BskHttpServer {
public:

   BskHttpServer();
   virtual ~BskHttpServer();

   bool StartServer(int port);

   void Poll();

   /**
    * Parses what we just got from the client.
    * This may not be a complete message.
    *
    * Returns - The function will return false if it detects an incomplete message
    */
   void ParseRequest(const char* buffer, size_t size,
         struct Request& outRequest);

private:

   pthread_t _acceptThread;

   ServerContext _serverContext;
   std::vector<ClientContext*> _clients;
};

#endif /* SRC_BSKHTTPSERVER_H_ */
