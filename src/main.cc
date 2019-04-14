#include <iostream>

#include "BskDisplay.h"
#include "BskLogging.h"
#include "BskRender.h"
#include "BskHttpServer.h"

//TODO Test json content using cJSON

void Handler(ClientContext* clientContext, void* userdata) {
//   std::shared_ptr<Render> render = std::shared_ptr<Render>((Render*)userdata);

   clientContext->response.statusCode = Response::CODE200;

   clientContext->response.appendHeader("Content-Type", "text/html; charset=ISO-8859-1");
   clientContext->response.body="<html><head><title>Testing</title></head><body> <b> Hello!! </b> </body></html>";
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
