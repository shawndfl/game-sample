#include <iostream>

#include "Render.h"
#include "Logging.h"
#include "Display.h"

int main(int argc, char *argv[]) {

   std::shared_ptr<Render> render = std::shared_ptr<Render>(new Render());

   render->initialize();

   display disp;
   disp.createWindow(1280, 1024, render.get());

   LOGI("Exit ");
   return 0;
}
