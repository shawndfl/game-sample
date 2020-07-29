/*
 * Display.cc
 *
 *  Created on: Apr 8, 2019
 *      Author: user1
 */

#include "BskDisplay.h"

#include "BskLogging.h"
#include "BskRender.h"

/*************************************************/
display::display() :
      _width(600), _height(800), _onDraw(nullptr) {

}

/*************************************************/
display::~display() {

}

/*************************************************/
void display::createWindow(int width, int height, Render* renderer) {

}

/*************************************************/
int display::getHeight() const {
   return _height;
}

/*************************************************/
int display::getWidth() const {
   return _width;
}
