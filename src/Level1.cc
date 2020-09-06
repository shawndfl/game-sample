/*
 * Level1.cc
 *
 *  Created on: Sep 2, 2020
 *      Author: sdady
 */

#include "Level1.h"
#include "Joystick.h"

namespace bsk {

/*************************************************/
Level1::Level1() {

}

/*************************************************/
Level1::~Level1() {

}

/*************************************************/
void Level1::start() {
   character_.initialize();
}

/*************************************************/
void Level1::update(Milliseconds dt) {

   character_.update(dt);


}

} /* namespace bsk */
