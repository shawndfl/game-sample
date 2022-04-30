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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    shader_.loadShaderFromFile("assets/shaders/texture.vert", "assets/shaders/texture.frag");

    glm::mat4 model(1);
    glm::mat4 view(1);
    glm::mat4 proj(1);

    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader_.use();
    shader_.setMatrix4("model", model);
    shader_.setMatrix4("view", view);
    shader_.setMatrix4("proj", proj);

    float vertices[] = {
            // positions        // texture coords // colors 
           -0.5f,   0.5f, 0.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
            0.5f,   0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
            0.5f,  -0.5f, 0.0f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   // bottom left
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f    // top left
            };
    GLuint indices[] = {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
            };
    uint vertSize = sizeof(vertices) / sizeof(float);
    uint indSize = sizeof(indices) / sizeof(GLuint);
    bsk::VertexAttributes attribute = bsk::APos | bsk::AColor | bsk::ATex1;

    geometry_.initialize(vertSize, indSize, attribute, false);
    geometry_.setBuffers(vertices, vertSize, indices, indSize);

    // texture
    bsk::Image img;
    if (bsk::ImageLoader::loadImage("assets/img/Bricks.png", img)) {
        texture_.setImage(img);
        LOGGL();
    }

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

    // draw our first triangle
    shader_.use();
    glm::mat4 model(1);
    model = glm::rotate(model, glm::radians(clip_.evaluate()) , glm::vec3(1.0f, 0.0f, 0.0f));
    shader_.setMatrix4("model", model);

    texture_.apply();
    geometry_.makeActive();

    glDrawElements(GL_TRIANGLES, geometry_.getPrimitiveCount(), GL_UNSIGNED_INT, 0);


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

}

/*************************************************/
void LevelCamera::keyEvent(int key, int scancode, int action, int mods) {
}

/*************************************************/
void LevelCamera::dispose() {
}