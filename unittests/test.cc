#include <cstring>
#include "UnitTest++/UnitTest++.h"
#include "BskHttpServer.h"
#include "BskLogging.h"

TEST(Sanity) {
   BskHttpServer server;
   struct Request request;
   const char* testRequest =
         "GET /test?x=1&y=2 HTTP/1.1\r\n"
               "Host: localhost:8080\r\n"
               "Connection: keep-alive\r\n"
               "Cache-Control: max-age=0\r\n"
               "Upgrade-Insecure-Requests: 1\r\n"
               "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.75 Safari/537.36\r\n"
               "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n"
               "Accept-Encoding: gzip, deflate, br\r\n"
               "Accept-Language: en-US,en;q=0.9\r\n"
               "\r\n"
               "\r\n";

   server.ParseRequest(testRequest, strlen(testRequest), request);

   CHECK_EQUAL("HTTP/1.1", request.httpVersion.c_str());
   CHECK_EQUAL("GET", request.method.c_str());
   CHECK_EQUAL("/test?x=1&y=2", request.uri.c_str());

   LOGI("httpVersion = \'%s\'", request.httpVersion.c_str());
   LOGI("method = \'%s\'", request.method.c_str());
   LOGI("uri = \'%s\'", request.uri.c_str());

   for (size_t i = 0; i < request.headers.size(); i++) {
      KeyValue pair = request.headers[i];
      LOGI("\'%s\' = \'%s\'", pair.key.c_str(), pair.value.c_str());
   }

}
