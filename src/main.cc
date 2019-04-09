#include <iostream>

#include "BskDisplay.h"
#include "BskLogging.h"
#include "BskRender.h"
#include "BskHttpServer.h"

int main(int argc, char *argv[]) {

   std::shared_ptr<Render> render = std::shared_ptr<Render>(new Render());

   render->initialize();

   BskHttpServer server;
   server.StartServer(8080);

   //display disp;
   //disp.createWindow(1280, 1024, render.get());

   LOGI("Exit ");

   return 0;
}
