
#include "Logging.h"
#include "GameEngine.h"
#include "Display.h"

int main(int argc, char *argv[]) {

   bsk::GameEngine game;
   bsk::Display display(game);

   display.runDisplay(600, 800);

   LOGI("Exit ");

   return 0;
}
