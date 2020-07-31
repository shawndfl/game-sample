
#include "Logging.h"
#include "GameEngine.h"
#include "Display.h"

int main(int argc, char *argv[]) {

   bsk::GameEngine game;
   bsk::Display::create(game);

   bsk::Display::get()->runDisplay(600, 800);

   LOGI("Exit ");

   return 0;
}
