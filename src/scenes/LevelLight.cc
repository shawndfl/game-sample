/*
 * LevelLight.cc
 *
 *  Created on: Jul 14, 2021
 *      Author: shawn
 */

#include "LevelLight.h"

const char *vertexShaderSource = "#version 330 core\n"
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
const char *fragmentShaderSource = "#version 330 core\n"
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

LevelLight::~LevelLight() {
}

bool LevelLight::start() {
    //geometry_
    return true;
}

void LevelLight::update(bsk::Milliseconds dt) {
}

void LevelLight::resize(uint width, uint height) {
}

void LevelLight::keyEvent(int key, int scancode, int action, int mods) {
}

void LevelLight::dispose() {
}
