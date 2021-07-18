
#include <levels/LevelSquare.h>
#include "Level1.h"
#include "core/Logging.h"
#include "core/GameEngine.h"
#include "core/Display.h"

int main(int argc, char *argv[]) {

   std::shared_ptr<bsk::IScene> scene = std::make_shared<LevelSquare>();
   bsk::GameEngine::get().setScene(scene);

   bsk::Display::create(bsk::GameEngine::get());

   bsk::Display::get()->runDisplay(600, 800);

   LOGI("Exit ");

   return 0;
}
