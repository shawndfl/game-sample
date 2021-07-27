/*
 * LevelLight.cc
 *
 *  Created on: Jul 14, 2021
 *      Author: shawn
 */

#include "LevelLight.h"
#include "core/Logging.h"
#include "graphics/Image.h"
#include "graphics/ImageLoader.h"

const char *vertexShaderSource1 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "ourColor = aColor;\n"
        "TexCoord = aTexCoord;\n"
    "}";
const char *fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"

    "uniform sampler2D ourTexture;\n"

    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor,1.0) ;\n"
    "}\n";

LevelLight::LevelLight() {

}

/*************************************************/
LevelLight::~LevelLight() {
}

/*************************************************/
bool LevelLight::start() {
    shader_.loadShaderFromMemory(vertexShaderSource1, fragmentShaderSource1);

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f    // top left
            };
    GLuint indices[] = {  // note that we start from 0!
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
    }

    return true;
}

/*************************************************/
void LevelLight::update(bsk::Milliseconds dt) {
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    shader_.use();

    texture_.apply();
    geometry_.makeActive();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

/*************************************************/
void LevelLight::resize(uint width, uint height) {
}

/*************************************************/
void LevelLight::keyEvent(int key, int scancode, int action, int mods) {
}

/*************************************************/
void LevelLight::dispose() {

}
