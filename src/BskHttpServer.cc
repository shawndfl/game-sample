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

#define BACKLOG 50

void* acceptEvent(void * context);
void* readEvent(void * context);
size_t readn(int fd, Request& request);
size_t writen(int fd, const void* buffer, size_t size);

/*************************************************/
//BskHttpServer
/*************************************************/
BskHttpServer::BskHttpServer() :
      _acceptThread(0), _requestHandler(nullptr), _userData(nullptr) {

}

/*************************************************/
BskHttpServer::~BskHttpServer() {
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
   if (bind(_serverContext.serverfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
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

   return true;
}

/*************************************************/
void BskHttpServer::JoinAcceptThread() {
   int ret;
   int* retp = &ret;

   pthread_join(_acceptThread, (void**) &retp);

   LOGI("Join main thread %d", ret);
}

/*************************************************/
RequestHandler BskHttpServer::getRequestHandler() const {
   return _requestHandler;
}

/*************************************************/
void BskHttpServer::setRequestHandler(RequestHandler handler) {
   _requestHandler = handler;
}

/*************************************************/
void* BskHttpServer::getUserData() const {
   return _userData;
}

/*************************************************/
void BskHttpServer::setUserData(void* userData) {
   _userData = userData;
}

/*************************************************/
// Client Context
/*************************************************/
void ClientContext::SendResponse() {

   std::string out;
   out = response.httpVersion + " " + response.getStatusCodeAndReason() + "\r\n";

   // Fill in the size of the content
   char buf[200] = { 0 };
   size_t size = response.body.size();
   sprintf(buf, "%zd", size);
   response.appendHeader("Content-Length", buf);

   // Write the headers
   for (size_t i = 0; i < response.headers.size(); i++) {
      KeyValue pair = response.headers.at(i);
      out += pair.key + ": " + pair.value + "\r\n";
   }

   // Done with headers
   out += "\r\n";

   // Write the body
   out += response.body;

   size_t bytesSent = writen(clientfd, out.c_str(), out.size());
   if (bytesSent < 0) {
      //EROFS
      LOGE("Error sending %d ", errno);
   }

   // TODO don't close this here. check to keep alive
   close(clientfd);

}

/*************************************************/
// Response
/*************************************************/
bool Response::PrepareHeaders() {

   return false;
}

/*************************************************/
void Response::appendHeader(const std::string& key, const std::string& value) {
   KeyValue pair;
   pair.key = key;
   pair.value = value;
   headers.push_back(pair);
}

/*************************************************/
std::string Response::getStatusCodeAndReason() const {

   switch (statusCode) {
   case CODE100:
      return "100 Continue";
   case CODE101:
      return "101 Switching Protocols";
   case CODE200:
      return "200 OK";
   case CODE201:
      return "201 Created";
   case CODE202:
      return "202 Accepted";
   case CODE203:
      return "203 Non-Authoritative Information";
   case CODE204:
      return "204 No Content";
   case CODE205:
      return "205 Reset Content";
   case CODE206:
      return "206 Partial Content";
   case CODE300:
      return "300 Multiple Choices";
   case CODE301:
      return "301 Moved Permanently";
   case CODE302:
      return "302 Found";
   case CODE303:
      return "303 See Other";
   case CODE304:
      return "304 Not Modified";
   case CODE305:
      return "305 Use Proxy";
   case CODE307:
      return "307 Temporary Redirect";
   case CODE400:
      return "400 Bad Request";
   case CODE401:
      return "401 Unauthorized";
   case CODE402:
      return "402 Payment Required";
   case CODE403:
      return "403 Forbidden";
   case CODE404:
      return "404 Not Found";
   case CODE405:
      return "405 Method Not Allowed";
   case CODE406:
      return "406 Not Acceptable";
   case CODE407:
      return "407 Proxy Authentication Required";
   case CODE408:
      return "408 Request Timeout";
   case CODE409:
      return "409 Conflict";
   case CODE410:
      return "410 Gone";
   case CODE411:
      return "411 Length Required";
   case CODE412:
      return "412 Precondition Failed";
   case CODE413:
      return "413 Payload Too Large";
   case CODE414:
      return "414 URI Too Long";
   case CODE415:
      return "415 Unsupported Media Type";
   case CODE416:
      return "416 Range Not Satisfiable";
   case CODE417:
      return "417 Expectation Failed";
   case CODE426:
      return "426 Upgrade Required";
   case CODE500:
      return "500 Internal Server Error";
   case CODE501:
      return "501 Not Implemented";
   case CODE502:
      return "502 Bad Gateway";
   case CODE503:
      return "503 Service Unavailable";
   case CODE504:
      return "504 Gateway Timeout";
   case CODE505:
      return "505 HTTP Version Not Supported";
   default:
      LOGE("Unknown return code: %d ", statusCode);
      return "500 Internal Server Error";
   }
}

/*************************************************/
// Request
/*************************************************/
Request::Request() :
      parseErrorCode(0), parsedState(Request::NewRequest) {

}

/*************************************************/
bool Request::ParseRequestLine(const std::string& line) {
   size_t i = 0;

   // Find method
   for (i = 0; i < line.size(); i++) {
      char ch = line.at(i);
      // done with method
      if (ch == ' ') {
         i++;
         break;
      }
      method += ch;
   }

   // Find uri
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      // done with uri
      if (ch == ' ') {
         i++;
         break;
      }
      uri += ch;
   }

   // Find httpVersion
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      // done with httpVersion. This char should not be here but
      // just in case
      if (ch == '\r') {
         i++;
         break;
      }
      httpVersion += ch;
   }

   return true;
}

/*************************************************/
bool Request::ParseHeaderLine(const std::string& line) {
   size_t i = 0;
   KeyValue pair;

   // Find field name
   for (i = 0; i < line.size(); i++) {
      char ch = line.at(i);
      // done with key
      if (ch == ':') {
         i++;
         break;
      }
      pair.key += ch;
   }

   // Trim white space
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      if (ch != ' ') {
         break;
      }
   }

   // Find field value
   for (/*continue from last loop*/; i < line.size(); i++) {
      char ch = line.at(i);
      // done with httpVersion. This char should not be here but
      // just in case
      if (ch == '\r') {
         i++;
         break;
      }
      pair.value += ch;
   }

   headers.push_back(pair);

   return true;
}

/*************************************************/
bool Request::AppendToBody(const std::string& chunk) {
   return true;
}

/*************************************************/
void Request::ParseRequest(const char* buffer, size_t size) {

   const char* ch = buffer;
   std::string token;
   size_t i = 0;

   while (parsedState != Request::Complete) {

      // there was an error some where
      if (parseErrorCode > 0)
         return;

      switch (parsedState) {

      case Request::IncompleteStartLine:
      case Request::NewRequest:
         // There is nothing to read
         // and the message is not complete
         if (i == size)
            return;

         // Parse Start Line
         for (i = 0; i < size; /* increment inside loop*/) {
            // End of line
            if (i + 1 < size && ch[i] == '\r' && ch[i + 1] == '\n') {
               ParseRequestLine(parsedLine);
               parsedState = Request::IncompleteHeader;
               parsedLine.clear(); // reset the parsed line
               i += 2; // Consume 2 chars
               break;
            } else {
               parsedState = Request::IncompleteStartLine;
               parsedLine += ch[i];
               i++; // Consume 1 char
            }
         }
         break;

      case Request::IncompleteHeader:
         // There is nothing to read
         // and the message is not complete
         if (i == size)
            return;

         // Headers
         for (/* Continue from last loop*/; i < size; /* increment inside loop*/) {
            // End of header
            if (i + 3 < size && ch[i] == '\r' && ch[i + 1] == '\n' && ch[i + 2] == '\r' && ch[i + 3] == '\n') {
               ParseHeaderLine(parsedLine);
               parsedState = Request::IncompleteMessage;
               parsedLine.clear(); // reset the parsed line
               i += 4; // Consume 4 chars
               break;
               // End of one header
            } else if (i + 1 < size && ch[i] == '\r' && ch[i + 1] == '\n') {
               ParseHeaderLine(parsedLine);
               parsedLine.clear(); // reset the parsed line
               i += 2; // Consume 2 chars
            } else {
               parsedState = Request::IncompleteHeader;
               if (ch[i] == '\0') {
                  LOGI("Found null at %zd", i);
               }
               parsedLine += ch[i];
               i++; // Consume 1 char
            }
         }

         break;
      case Request::IncompleteMessage:
         //TODO get the message length or chunk and parse it
         // Message
         for (; i < size; i++) {

         }

         parsedState = Request::Complete;

         break;
      default:
         LOGE("Unknown parse state: %d ", parsedState);
      }
   }
}

/*************************************************/
const std::string& Request::getBody() const {
   return body;
}

/*************************************************/
const std::vector<KeyValue>& Request::getHeaders() const {
   return headers;
}

/*************************************************/
const std::string& Request::getHttpVersion() const {
   return httpVersion;
}

/*************************************************/
const std::string& Request::getMethod() const {
   return method;
}

/*************************************************/
const std::vector<KeyValue>& Request::getParameters() const {
   return parameters;
}

/*************************************************/
const std::string& Request::getParsedLine() const {
   return parsedLine;
}

/*************************************************/
Request::ParseState Request::getParsedState() const {
   return parsedState;
}

/*************************************************/
int Request::getParseErrorCode() const {
   return parseErrorCode;
}

/*************************************************/
const std::string& Request::getUri() const {
   return uri;
}

/*************************************************/
// Helper functions
/*************************************************/
void* acceptEvent(void * context) {

   ServerContext* serverContext = (ServerContext*) context;

   while (true) {

      struct sockaddr clientAddr;
      socklen_t addrLen = sizeof(clientAddr);
      int clientfd = accept(serverContext->serverfd, &clientAddr, &addrLen);
      if (clientfd < 0) {
         LOGE("Error accept %d %d", clientfd, errno);
         exit(EXIT_FAILURE);
      }

      //TODO add ip address of client
      LOGI("Got a client %d", clientfd);

      ClientContext* receiveContext = new ClientContext(serverContext->server, clientfd);

      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_create(&receiveContext->thread, &attr, &readEvent, receiveContext);
      pthread_attr_destroy(&attr);
   }

   return nullptr;
}

/*************************************************/
size_t readn(int fd, Request& request) {

   size_t totalBytesRead = 0;

   // There is a chance that our buffer is too small for the
   // request. This look will allow us to keep reading until we
   // get a complete request or an error.
   while (request.getParsedState() != Request::Complete) {

      // Handle parse errors
      if (request.getParseErrorCode() > 0) {
         return -1;
      }

      const size_t size = 4096;
      char buffer[size] = { 0 };
      char* chBufer = buffer;
      volatile size_t bufferBytesRead = 0;
      volatile size_t bytesRead = 0;
      while (bufferBytesRead < size) {

         bytesRead = read(fd, chBufer, size - bufferBytesRead);
         if (bytesRead == (size_t) -1) {

            // Interrupted restart
            if (errno == EINTR) {
               continue;
            } else {
               LOGE("Error reading %d ", errno);
               return -1;
            }
         }

         // EOF
         if (bytesRead == 0) {
            return bufferBytesRead;
         }

         // Parse the request
         request.ParseRequest(chBufer, bytesRead);

         // All done. Got the full request.
         if (request.getParsedState() == Request::Complete) {
            break;
         }
         bufferBytesRead += bytesRead;
         chBufer += bytesRead;
         totalBytesRead += bytesRead;
      }
   }
   return totalBytesRead;
}

/*************************************************/
size_t writen(int fd, const void* buffer, size_t size) {
   char* chBuffer = (char*) buffer;
   size_t totalBytesWrote = 0;
   size_t bytesWrote = 0;
   while (totalBytesWrote < size) {

      bytesWrote = write(fd, chBuffer, size - totalBytesWrote);

      // EOF
      if (bytesWrote <= 0) {
         // Interrupted restart
         if (bytesWrote == (size_t) -1 && errno == EINTR) {
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
   ClientContext* clientContext = (ClientContext*) context;

   LOGI("Got a client %d", clientContext->clientfd);

   while (true) {

      // Read the request
      int bytesRead = readn(clientContext->clientfd, clientContext->request);

      // TODO move this to a initialize response function
      // Set the http version
      clientContext->response.httpVersion = HTTP_VERSION;

      // Fillin the date header
      char buf[200];
      time_t now = time(0);
      struct tm tm = *gmtime(&now);
      // Sun, 06 Nov 1994 08:49:37 GMT
      strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
      clientContext->response.appendHeader("Date", std::string(buf));

      // Fill in the server Header
      clientContext->response.appendHeader("Server", "Embedded");

      // Let the user handle the request
      if (clientContext->server->getRequestHandler() != nullptr) {
         clientContext->server->getRequestHandler()(clientContext, clientContext->server->getUserData());
      } else {
         LOGW("No request handler. Call BskHttpServer::setRequestHandler()");
      }

      break;
   }
   return nullptr;
}
