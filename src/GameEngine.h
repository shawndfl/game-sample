/*
 * GameEngine.h
 *
 *  Created on: Jul 30, 2020
 *      Author: sdady
 */

#ifndef SRC_GAMEENGINE_H_
#define SRC_GAMEENGINE_H_

#include <memory>

namespace bsk {

class Render;
class FontManager;

/**
 * The main game engine that processes
 * rendering input sound, etc.
 */
class GameEngine {
public:

   GameEngine();

   virtual ~GameEngine();

   bool initialize();

   bool start(uint width, uint height);

   void resize(uint width, uint height);

   bool update();

   void dispose();
private:
   std::unique_ptr<Render>        render_;
   std::unique_ptr<FontManager>   fontManager_;
};

}
#endif /* SRC_GAMEENGINE_H_ */
