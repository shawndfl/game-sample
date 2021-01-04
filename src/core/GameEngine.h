/*
 * GameEngine.h
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#ifndef SRC_GAMEENGINE_H_
#define SRC_GAMEENGINE_H_

#include <memory>
#include "math/Timer.h"
#include "core/IScene.h"

namespace bsk {

class Render;
class FontManager;
class Joystick;
class Keyboard;

/**
 * The main game engine that processes
 * rendering input sound, etc.
 */
class GameEngine {
public:

   virtual ~GameEngine();

   void setScene(std::shared_ptr<bsk::IScene>& scene);

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

    /**
     * Called to raise a key event
     */
    void keyEvent(int key, int scancode, int action, int mods);

private:
   GameEngine();

   std::unique_ptr<Render>        render_;
   std::unique_ptr<FontManager>   fontManager_;
   std::unique_ptr<Joystick>      joy_;
   std::unique_ptr<Keyboard>      keyboard_;
   std::shared_ptr<IScene>        scene_;

   uint         height_;
   uint         width_;
   Timer        timer_;
};

}
#endif /* SRC_GAMEENGINE_H_ */
