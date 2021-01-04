
#include "core/Logging.h"
#include "core/GameEngine.h"
#include "core/Display.h"
#include "level1/Level1.h"

int main(int argc, char *argv[]) {

   std::shared_ptr<bsk::IScene> scene = std::make_shared<bsk::Level1>();
   bsk::GameEngine::get().setScene(scene);

   bsk::Display::create(bsk::GameEngine::get());

   bsk::Display::get()->runDisplay(600, 800);

   LOGI("Exit ");

   return 0;
}
