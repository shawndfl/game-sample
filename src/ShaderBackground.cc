/*
 * ShaderBackground.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "ShaderBackground.h"
#include "Logging.h"

namespace bsk {

static const GLchar *vertexShaderSource =
        "#version 300 es                           \n"
        "precision mediump float;                  \n"
        "uniform vec4 u_color;               \n"
        "in vec3 a_pos;							   \n"
        "in vec2 a_tex;                           \n"
        "out vec2 v_tex;                          \n"
        "void main() {                             \n"
        "   gl_Position = vec4(a_pos, 1.0);        \n"
        "   v_tex = a_tex;                       \n"
        "}                                         \n"
        "                                          \n";

static const GLchar *fragmentShaderSource =
        "#version 300 es						            \n"
        "precision mediump float;                      \n"
        "in vec2 v_tex;                                \n"
        "uniform sampler2D u_diffused;               \n"
        "uniform vec4 u_color;               \n"
        "out vec4 FragColor;                       \n"
        "void main() {                             \n"
        "   FragColor = texture(u_diffused, v_tex) * u_color; \n"
        "}                                         \n"
        "                                          \n";

/*************************************************/
ShaderBackground::ShaderBackground() {
   program_ = 0;

   diffused_ = -1;
   overlay_= -1;
   color_= -1;
   uscale_= -1;
   vscale_= -1;
   uoffset_= -1;
   voffset_= -1;

   position_= -1;
   texture_= -1;
   normal_= -1;

   byteStride_ = 0;
}

/*************************************************/
ShaderBackground::~ShaderBackground() {
}

/*************************************************/
bool ShaderBackground::loadProgram() {
    const uint LOG_LEN = 1024;
    GLchar infoLog[LOG_LEN];
    GLint success;

    // Vertex Shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, LOG_LEN, NULL, infoLog);
        LOGD("Vertex compiler error: " << infoLog);
        return false;
    }

    // Fragment Shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, LOG_LEN, NULL, infoLog);
        LOGD("Fragment compiler error: " << infoLog);
        return false;
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex);
    glAttachShader(program_, fragment);
    glLinkProgram(program_);
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_, LOG_LEN, NULL, infoLog);
        LOGD("Program link error: " << infoLog);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // collect all the uniform variables
    diffused_ = getUniformLocation("u_diffused");
    color_ = getUniformLocation("u_color");

    // setup attributes
    position_ = getAttributeLocation("a_pos");
    texture_ = getAttributeLocation("a_tex");

    // pos + tex * float size
    byteStride_ = (3 + 2) * sizeof(float);

    // set defaults
    glUseProgram(program_);

    Vector4 colorValue(1,1,0,1);
    colorValue.setUniform(color_);

    glUniform1f(diffused_, 0);


    return true;
}

/*************************************************/
int ShaderBackground::getUniformLocation(const std::string& name) {
   int id = glGetUniformLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find uniform: " << name);
   }
   return id;
}

/*************************************************/
int ShaderBackground::getAttributeLocation(const std::string& name) {
   int id = glGetAttribLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find attribute: " << name);
   }
   return id;
}

/*************************************************/
void ShaderBackground::enableProgram() {
    // enable our shader program
    glUseProgram(program_);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/*************************************************/
bool ShaderBackground::bindMaterial(const Material &material) {

    material.apply();
    return true;
}

/*************************************************/
int ShaderBackground::getNormal() const {
   return normal_;
}

/*************************************************/
int ShaderBackground::getPosition() const {
   return position_;
}

/*************************************************/
int ShaderBackground::getTexture() const {
   return texture_;
}

/*************************************************/
int ShaderBackground::getByteStride() const {
   return byteStride_;
}

} /* namespace bsk */
