/*
 * Display.h
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <memory>

// forward

class Render;

typedef void (*OnDraw)();

class display {
public:
   display();
   virtual ~display();

   void createWindow(int width, int height, Render* renderer);

   int getHeight() const;
   int getWidth() const;

private:
   int _width;
   int _height;
   OnDraw _onDraw;
   std::shared_ptr<Render> _renderer;
};

#endif /* SRC_DISPLAY_H_ */
