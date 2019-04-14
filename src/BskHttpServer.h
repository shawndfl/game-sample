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

#define HTTP_VERSION "HTTP/1.1"

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
   enum StatusCode {
      CODE100,
      CODE101,
      CODE200,
      CODE201,
      CODE202,
      CODE203,
      CODE204,
      CODE205,
      CODE206,
      CODE300,
      CODE301,
      CODE302,
      CODE303,
      CODE304,
      CODE305,
      CODE307,
      CODE400,
      CODE401,
      CODE402,
      CODE403,
      CODE404,
      CODE405,
      CODE406,
      CODE407,
      CODE408,
      CODE409,
      CODE410,
      CODE411,
      CODE412,
      CODE413,
      CODE414,
      CODE415,
      CODE416,
      CODE417,
      CODE426,
      CODE500,
      CODE501,
      CODE502,
      CODE503,
      CODE504,
      CODE505,
   };

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
   StatusCode statusCode;

   /**
    * Gets the status code followed by the reason.
    */
   std::string getStatusCodeAndReason() const;

   /**
    * Fills in any headers that user did not fill in.
    */
   bool PrepareHeaders();

   /**
    * Headers
    */
   std::vector<KeyValue> headers;

   /**
    * appends a header line
    */
   void appendHeader(const std::string& key, const std::string& value);

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
class Request {
public:
   enum ParseState {
      NewRequest, IncompleteStartLine, IncompleteHeader, IncompleteMessage, Complete, ParseError
   };

   Request();

   /**
    * gets the size of the body based on the
    */
   int getBodySize() const;

   /**
    * Starts the request parsing process. This function will call
    * ParseRequestLine(), ParseHeaderLine(), and AppendToBody()
    */
   void ParseRequest(const char* buffer, size_t size);

   const std::string& getBody() const;
   const std::vector<KeyValue>& getHeaders() const;
   const std::string& getHttpVersion() const;
   const std::string& getMethod() const;
   const std::vector<KeyValue>& getParameters() const;
   const std::string& getParsedLine() const;
   ParseState getParsedState() const;
   int getParseErrorCode() const;
   const std::string& getUri() const;

private:
   /**
    * Parses the request line. This is the first line in
    * the request. Its format is:
    *    method SP request-target SP HTTP-version CRLF
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool ParseRequestLine(const std::string& line);
   /**
    * Parse header. This will parse a single line.
    * it should be in the form of:
    *    field-name: field-value
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool ParseHeaderLine(const std::string& line);

   /**
    * This will append a chunk to the message
    * body.
    *
    * NOTE: Don't call directory ParseRequest()
    * calls this.
    */
   bool AppendToBody(const std::string& chunk);

   /**
    * This error code can be set when parsing
    * the request. If invalid characters are found
    * this will be set and a response will be sent
    * to the client with this number.
    */
   int parseErrorCode;

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

};

/**
 * The context of the client connect.
 * The user should fill out the response structure
 * and call the SendResponse() function.
 */
typedef struct ClientContext {

   ClientContext(BskHttpServer* server, int clientfd) :
         clientfd(clientfd), thread(0), server(server) {

   }

   int clientfd = -1;
   pthread_t thread = 0;
   BskHttpServer* server = nullptr;

   /**
    * This will be filled in by the server.
    */
   struct Request request;

   /**
    * The response from the server
    */
   struct Response response;

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

typedef void (*RequestHandler)(ClientContext* clientContext, void* userData);

/**
 * The main server class used to start the server
 */
class BskHttpServer {
public:

   BskHttpServer();
   virtual ~BskHttpServer();

   /**
    * Starts the server listening on the givne port.
    * This will spin up an accept thread. As clients connect
    * they will each get their own thread.
    */
   bool StartServer(int port);

   /**
    * Parses what we just got from the client.
    * This may not be a complete message.
    *
    * Returns - The function will return false if it detects an incomplete message
    */
   void ParseRequest(const char* buffer, size_t size, struct Request& outRequest);

   /**
    * Sets a user call back that handles the http request.
    * The handler will need to fill in the response structure then call
    * SendResponse().
    *
    * NOTE: The request handler is called on the client thread. Thread synchronization
    *       will be required when accessing shared resources.
    */
   void setRequestHandler(RequestHandler handler);

   /**
    * User data that is passed to the handler.
    */
   void setUserData(void* userData);

   /**
    * Gets the user data for the request handler.
    */
   void* getUserData() const;

   /**
    * Joins with the accept thread
    */
   void JoinAcceptThread();

   /**
    * Gets the request handler
    */
   RequestHandler getRequestHandler() const;

private:

   pthread_t _acceptThread;

   ServerContext _serverContext;
   std::vector<ClientContext*> _clients;

   RequestHandler _requestHandler;                  /// a callback that handles the http requests
   void* _userData;
};

#endif /* SRC_BSKHTTPSERVER_H_ */
