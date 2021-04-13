/*
 * ShaderSprite.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "ShaderSprite.h"

#include "core/Logging.h"
#include "math/math.h"

namespace bsk {

static const GLchar *vertexShaderSource =
        "#version 100                                 \n"
        "precision mediump float;                     \n"
        "uniform vec4 u_color;                        \n"
        "uniform mat4 u_mvp;                          \n"
        "attribute vec3 a_pos;							   \n"
        "attribute vec2 a_tex;                        \n"
        "varying vec2 v_tex;                          \n"
        "                                             \n"
        "void main() {                                \n"
        "   gl_Position = u_mvp  * vec4(a_pos, 1.0);  \n"
        "   v_tex = a_tex;                            \n"
        "}                                            \n"
        "                                             \n";

static const GLchar *fragmentShaderSource =
        "#version 100 						            \n"
        "precision mediump float;                  \n"
        "varying vec2 v_tex;                       \n"
        "uniform sampler2D u_diffused;             \n"
        "uniform vec2 u_scale;                     \n"
        "uniform vec2 u_offset;                    \n"
        "uniform vec4 u_color;                     \n"
        "void main() {                             \n"
        "   vec2 tex = u_offset + v_tex * u_scale; \n "
        "   gl_FragColor = texture2D(u_diffused, tex) * u_color; \n"
        "}                                         \n"
        "                                          \n";

/*************************************************/
ShaderSprite::ShaderSprite() {
   program_ = 0;

   mvp_ = -1;
   diffused_ = -1;
   screen_ = -1;
   overlay_= -1;
   ucolor_= -1;
   uscale_= -1;
   uoffset_= -1;

   aPosition_= -1;
   aTexture_= -1;

   byteStride_ = 0;
}

/*************************************************/
ShaderSprite::~ShaderSprite() {
   dispose();
}

/*************************************************/
void ShaderSprite::dispose() {
   if(program_ != 0) {
      LOGD("Disposing program: " << program_);
      glDeleteProgram(program_);
      program_ = 0;
   }
}

/*************************************************/
VertexAttributes ShaderSprite::getAttribute() const {
   return APos | ATex1;
}

/*************************************************/
bool ShaderSprite::loadProgram() {

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
    diffused_     = getUniformLocation("u_diffused");
    ucolor_       = getUniformLocation("u_color");
    mvp_          = getUniformLocation("u_mvp");
    uscale_       = getUniformLocation("u_scale");
    uoffset_      = getUniformLocation("u_offset");


    // setup attributes
    aPosition_ = getAttributeLocation("a_pos");
    aTexture_ = getAttributeLocation("a_tex");

    // pos + tex * float size
    byteStride_ = (3 + 2) * sizeof(float);

    // set defaults
    glUseProgram(program_);

    Vector4 colorValue(1,1,1,1);
    setColor(colorValue);

    Vector2 offset(0,0);
    setOffset(offset);

    Vector2 scale(1,1);
    setScale(scale);

    // set diffused map to texture channel 0
    glUniform1f(diffused_, 0);

    // set the mvp to identity
    Matrix4 mat;
    setMVP(mat);

    LOGD("Creating Shader");

    return true;
}

/*************************************************/
int ShaderSprite::getUniformLocation(const std::string& name) {
   int id = glGetUniformLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find uniform: " << name);
   }
   return id;
}

/*************************************************/
int ShaderSprite::getAttributeLocation(const std::string& name) {
   int id = glGetAttribLocation(program_, name.c_str());
   if(id == -1) {
      LOGD("Cannot find attribute: " << name);
   }
   return id;
}

/*************************************************/
void ShaderSprite::enableProgram() {
    // enable our shader program
    glUseProgram(program_);
    glEnable(GL_BLEND);
    texture_.apply(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/*************************************************/
bool ShaderSprite::setTexture(const Texture& texture) {

    texture_ = texture;
    return true;
}

/*************************************************/
int ShaderSprite::getPosition() const {
   return aPosition_;
}

/*************************************************/
int ShaderSprite::getTexture() const {
   return aTexture_;
}

/*************************************************/
int ShaderSprite::getByteStride() const {
   return byteStride_;
}

/*************************************************/
int ShaderSprite::getColor() const {
   return ucolor_;
}

/*************************************************/
int ShaderSprite::getDiffused() const {
   return diffused_;
}

/*************************************************/
int ShaderSprite::getUoffset() const {
   return uoffset_;
}

/*************************************************/
int ShaderSprite::getUscale() const {
   return uscale_;
}

/*************************************************/
void ShaderSprite::setScreenSize(uint width, uint height) {
   glUseProgram(program_);

   Vector2 size(width, height);
   size.setUniform(screen_);

}

/*************************************************/
void ShaderSprite::setColor(const Vector4& color) {
   color.setUniform(ucolor_);
}

/*************************************************/
void ShaderSprite::setOffset(const Vector2& offset) {
   offset.setUniform(uoffset_);
}

/*************************************************/
void ShaderSprite::setScale(const Vector2& scale) {
   scale.setUniform(uscale_);
}

/*************************************************/
void ShaderSprite::setMVP(const Matrix4& mvp) {
   glUseProgram(program_);
   mvp.setUniform(mvp_);
}


} /* namespace bsk */
