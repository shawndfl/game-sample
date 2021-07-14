/*
 * Level3DCube.cc
 *
 *  Created on: Jul 6, 2021
 *      Author: shawn
 */

#include "Level3DCube.h"

/*************************************************/
Level3DCube::Level3DCube() {

}

/*************************************************/
Level3DCube::~Level3DCube() {
}

/*************************************************/
bool Level3DCube::start() {
    //camera_.
    cube_.initialize();
    camera_.initializeView(bsk::vec3Back, bsk::vec3Zero, bsk::vec3Up);
    camera_.initializeProj(45.0, (double)4/3, .1, 1000);

    return true;
}

/*************************************************/
void Level3DCube::update(bsk::Milliseconds dt) {
    cube_.render(camera_);
}

/*************************************************/
void Level3DCube::resize(uint width, uint height) {
    camera_.initializeProj(45.0, (double)width/ height, .1, 1000);
}

/*************************************************/
void Level3DCube::keyEvent(int key, int scancode, int action, int mods) {
}

/*************************************************/
void Level3DCube::dispose() {
}
