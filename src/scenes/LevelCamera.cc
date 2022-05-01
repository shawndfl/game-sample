/*
 * LevelCamera.cc
 *
 *  Created on: Jul 26, 2021
 *      Author: shawn
 */

#include "LevelCamera.h"
#include "core/Logging.h"
#include "graphics/Image.h"
#include "graphics/ImageLoader.h"
#include "core/GameEngine.h"
#include "graphics/Primitive.h"
#include <iomanip>

/*************************************************/
LevelCamera::LevelCamera() {
   frames_ = 0;
}

/*************************************************/
LevelCamera::~LevelCamera() {

}

/*************************************************/
bool LevelCamera::start(uint width, uint height) {

    float aspect = (float)width/height;

    camera_.initializeProj(45, aspect, .1, 1000);
    camera_.initializeView( glm::vec3(0.0f, 0.0f, -3.0f),
                            glm::vec3(0.0f, 0.0f, 1.0f),
                            glm::vec3(0.0f, 1.00f, 0));

    ground_ = std::make_shared<bsk::Ground>();
    ground_->initialize();
    root_.add(ground_);

    // ping pong
    clip_.addKey(0, 0);
    clip_.addKey(1000, 180);
    clip_.addKey(2000, 0);
    clip_.play(true);

    uint x = 0;
    uint y = 0;
    uint depth = 0;
    float scale = .2;
    glm::vec4 color(.2,1,.7,1);


    bsk::GameEngine::get().getFontManager().setFont("fps", "FPS: ", x, y, depth, scale, color);


    return true;
}

/*************************************************/
void LevelCamera::update(bsk::Milliseconds dt) {

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    clip_.update(dt);

    root_.updateMatrixWorld();

    ground_->render(camera_);

    if(fps_.getDelta() > 1000.0) {
       std::stringstream fps;
       fps << "FPS: " << std::fixed << std::setprecision(2) << (float)(frames_)/(fps_.getDelta()  * 0.001);
       uint x = 0;
       uint y = 10;
       uint depth = 0;
       float scale = .2;
       glm::vec4 color(.2,1,.7,1);

       bsk::GameEngine::get().getFontManager().setFont("fps", fps.str(), x, y, depth, scale, color);
       fps_.reset();
       frames_ = 0;
    }
    frames_++;
}

/*************************************************/
void LevelCamera::resize(uint width, uint height) {

   float aspect = (float)width/height;
   glm::mat4 proj(1);
   proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

   // adjust prospective
   camera_.initializeProj(45, aspect, .1f, 1000.0f);
}

/*************************************************/
void LevelCamera::keyEvent(int key, int scancode, int action, int mods) {
}

/*************************************************/
void LevelCamera::dispose() {
}
