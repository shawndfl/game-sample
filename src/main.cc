#include <iostream>

#include "BskDisplay.h"
#include "BskLogging.h"
#include "BskRender.h"
#include "BskHttpServer.h"

//TODO Test json content using cJSON

void Handler(ClientContext* clientContext, void* userdata) {
//   std::shared_ptr<Render> render = std::shared_ptr<Render>((Render*)userdata);

   LOGI("uri: %s", clientContext->request.getUri().c_str());
   LOGI("uriPath: %s", clientContext->request.getUriPath().c_str());
   LOGI("uriQuery: %s", clientContext->request.getUriQuery().c_str());

   std::string body = "<html><head><title>Testing</title></head><body> <b> Hello!!</b><br>";

   for (size_t i = 0; i < clientContext->request.getQueryParameters().size(); i++) {
      KeyValue pair = clientContext->request.getQueryParameters().at(i);

      //LOGI("%d: \"%s\" == \"%s\"", i, pair.key.c_str(), pair.value.c_str());
      body += pair.key + " = " + pair.value + "<br>";
   }

   body += "</body></html>";

   clientContext->response.statusCode = Response::CODE200;

   clientContext->response.appendHeader("Content-Type", "text/html; charset=ISO-8859-1");
   clientContext->response.body = body;
   clientContext->SendResponse();

   //LOGI("Is render initialized %i", render->isInitialized());

}

int main(int argc, char *argv[]) {

   std::shared_ptr<Render> render = std::shared_ptr<Render>(new Render());

   render->initialize();

   BskHttpServer server;
   server.StartServer(8080);
   server.setRequestHandler(&Handler);

   server.setUserData(render.get());

   server.JoinAcceptThread();
   //display disp;
   //disp.createWindow(1280, 1024, render.get());

   LOGI("Exit ");

   return 0;
}
