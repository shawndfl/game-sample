/*
 * Render.h
 *
 *  Created on: Apr 7, 2019
 *      Author: user1
 */

#ifndef SRC_BSKRENDER_H_
#define SRC_BSKRENDER_H_

/**
 * This class is used to render the scene
 */
class Render {
public:
   Render();
   virtual ~Render();

   void initialize();

   void render();

   bool isInitialized() const;

private:
   bool _initialized;
};

#endif /* SRC_BSKRENDER_H_ */
