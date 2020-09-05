/*
 * GameEngine.h
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#ifndef SRC_GAMEENGINE_H_
#define SRC_GAMEENGINE_H_

#include <memory>
#include "Timer.h"

namespace bsk {

class Render;
class FontManager;
class Joystick;
class Level1;

/**
 * The main game engine that processes
 * rendering input sound, etc.
 */
class GameEngine {
public:

   virtual ~GameEngine();

   bool start(uint width, uint height);

   void resize(uint width, uint height);

   bool update();

   bool updateFixed();

   void dispose();

   static GameEngine& get();

   uint getWidth();

   uint getHeight();

    FontManager& getFontManager();
    Joystick& getJoy();
    Render& getRender();

private:
   GameEngine();

   std::unique_ptr<Render>        render_;
   std::unique_ptr<FontManager>   fontManager_;
   std::unique_ptr<Joystick>      joy_;
   std::unique_ptr<Level1>        level1_;
   uint         height_;
   uint         width_;
   Timer        timer_;
};

}
#endif /* SRC_GAMEENGINE_H_ */
