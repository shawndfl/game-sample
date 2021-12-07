/*
 * ShaderFont.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "ShaderFont.h"

#include "core/Logging.h"
#include "math/mathCore.h"

namespace bsk {

static const GLchar *vertexShaderSource =
        "#version 100                                        \n"
        "precision mediump float;                            \n"
        "uniform mat4 u_projection;                          \n"
        "attribute vec3 a_pos;						   	     \n"
        "attribute vec2 a_tex;                               \n"
        "varying vec2 v_tex;                                 \n"
        "                                                    \n"
        "void main() {                                       \n"
        "   gl_Position = u_projection  * vec4(a_pos, 1.0);  \n"
        "   v_tex = a_tex;                                   \n"
        "}                                                   \n"
        "                                                    \n";

static const GLchar *fragmentShaderSource =
        "#version 100 						                     \n"
        "precision mediump float;                                \n"
        "varying vec2 v_tex;                                     \n"
        "uniform sampler2D u_texture;                            \n"
        "uniform vec4 u_color;                                   \n"
        "void main() {                                           \n"
        "   vec2 tex = v_tex;                                    \n "
        "   gl_FragColor = texture2D(u_texture, tex) * u_color;  \n"
        "}                                                       \n"
        "                                                        \n";

/*************************************************/
ShaderFont::ShaderFont() {
   program_ = 0;

   uProjection_ = -1;
   uTexture_ = -1;
   uColor_= -1;

   aPosition_= -1;
   aTexture_= -1;

   byteStride_ = 0;
}

/*************************************************/
ShaderFont::~ShaderFont() {
   dispose();
}

/*************************************************/
void ShaderFont::dispose() {
   if(program_ != 0) {
      LOGD("Disposing program: " << program_);
      glDeleteProgram(program_);
      program_ = 0;
   }
}

/*************************************************/
VertexAttributes ShaderFont::getAttribute() const {
   return APos | ATex1;
}

/*************************************************/
bool ShaderFont::loadProgram() {

    dispose();

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
    LOGD("Creating program: " << program_);

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
    uTexture_     = getUniformLocation("u_texture");
    uColor_       = getUniformLocation("u_color");
    uProjection_          = getUniformLocation("u_projection");


    // setup attributes
    aPosition_ = getAttributeLocation("a_pos");
    aTexture_ = getAttributeLocation("a_tex");

    // pos + tex * float size
    byteStride_ = (3 + 2) * sizeof(float);

    // set defaults
    glUseProgram(program_);

    Vector4 colorValue(1,1,1,1);
    setColor(colorValue);

    // set diffused map to texture channel 0
    glUniform1f(uTexture_, 0);

    // set the mvp to identity
    Matrix4 mat;
    setProjection(mat);

    LOGD("Creating Shader");

    return true;
}

/*************************************************/
int ShaderFont::getUniformLocation(const std::string& name) {
   int id = glGetUniformLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find uniform: " << name);
   }
   return id;
}

/*************************************************/
int ShaderFont::getAttributeLocation(const std::string& name) {
   int id = glGetAttribLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find attribute: " << name);
   }
   return id;
}

/*************************************************/
void ShaderFont::enableProgram() {
    // enable our shader program
    glUseProgram(program_);
    glEnable(GL_BLEND);
    texture_.apply(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/*************************************************/
bool ShaderFont::setTexture(const Texture& texture) {

    texture_ = texture;
    return true;
}

/*************************************************/
int ShaderFont::getPosition() const {
   return aPosition_;
}

/*************************************************/
int ShaderFont::getByteStride() const {
   return byteStride_;
}

/*************************************************/
int ShaderFont::getColor() const {
   return uColor_;
}

/*************************************************/
void ShaderFont::setColor(const Vector4& color) {
   color.setUniform(uColor_);
}

/*************************************************/
void ShaderFont::setProjection(const Matrix4& projection) {
   glUseProgram(program_);
   projection.setUniform(uProjection_);
}


} /* namespace bsk */
