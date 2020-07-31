
#include "Logging.h"
#include "Render.h"
#include "Display.h"

int main(int argc, char *argv[]) {

   bsk::Render render;
   bsk::Display display(render);

   display.runDisplay(600, 800);

   LOGI("Exit ");

   return 0;
}
