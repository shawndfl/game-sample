/*
 * Render.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_RENDER_H_
#define SRC_RENDER_H_

/**
 * This class is used to render the scene
 */
class Render {
public:
   Render();
   virtual ~Render();

   void initialize();

   void render();
};

#endif /* SRC_RENDER_H_ */
