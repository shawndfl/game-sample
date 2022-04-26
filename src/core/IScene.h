/*
 * IScene.h
 *
 *  Created on: Jan 3, 2021
 *      Author: sdady
 */

#ifndef SRC_CORE_ISCENE_H_
#define SRC_CORE_ISCENE_H_

#include "math/Timer.h"
#include <sys/types.h>

namespace bsk {

/**
 * Extend this class to create a 3D or 2D scene
 */
class IScene {
public:
   IScene();

   virtual ~IScene();

   virtual bool start(uint width, uint height) = 0;

   virtual void update(Milliseconds dt) = 0;

   virtual void resize(uint width, uint height) = 0;

   virtual void keyEvent(int key, int scancode, int action, int mods) = 0;

   virtual void dispose() = 0;
};

} /* namespace bsk */

#endif /* SRC_CORE_ISCENE_H_ */
