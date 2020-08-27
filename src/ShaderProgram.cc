/*
 * ShaderProgram.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "ShaderProgram.h"
#include "Logging.h"

namespace bsk {

static const GLchar *vertexShaderSource =
        "#version 300 es                           \n"
        "precision mediump float;                  \n"
        "in vec3 a_pos;							   \n"
        "in vec2 a_tex1;                           \n"
        "out vec2 v_tex1;                          \n"
        "void main() {                             \n"
        "   gl_Position = vec4(a_pos, 1.0);        \n"
        "   v_tex1 = a_tex1;                       \n"
        "}                                         \n"
        "                                          \n";

static const GLchar *fragmentShaderSource =
        "#version 300 es						   \n"
        "precision mediump float;                  \n"
        "in vec2 v_tex1;                           \n"
        "uniform sampler2D u_diffused;               \n"
        "out vec4 FragColor;                       \n"
        "void main() {                             \n"
        "   FragColor = texture(u_diffused, v_tex1); \n"
        "}                                         \n"
        "                                          \n";

/*************************************************/
ShaderProgram::ShaderProgram() {
    program_ = 0;
    diffusedTex1_ = 0;
}

/*************************************************/
ShaderProgram::~ShaderProgram() {
}

/*************************************************/
bool ShaderProgram::loadProgram() {
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

    diffusedTex1_ = glGetUniformLocation(program_, "u_diffused");
    glUniform1f(diffusedTex1_, 0);

    return true;
}

/*************************************************/
void ShaderProgram::enableProgram() {
    // enable our shader program
    glUseProgram(program_);

    for (auto attr : attributes_) {
        glEnableVertexAttribArray(attr);
    }
}

/*************************************************/
bool ShaderProgram::bindGeometry(const Geometry &geometry) {
    // enable out geometry
    geometry.makeActive();

    // set our attributes
    long offset = 0;
    unsigned short stride = 5 * sizeof(float);

    if ((geometry.getAttribute() & Geometry::APos) > 0) {
        GLint index = glGetAttribLocation(program_, "a_pos");
        if (index != -1) {
            glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride,
                    (GLvoid*) offset);
            attributes_.push_back(index);
            offset += 3 * sizeof(float);
        } else {
            LOGD("Cannot find \'a_pos\'");
            return false;
        }
    }

    LOGD("offset " << offset);

    if ((geometry.getAttribute() & Geometry::ATex1) > 0) {
        GLint index = glGetAttribLocation(program_, "a_tex1");
        if (index != -1) {
            glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride,
                    (GLvoid*) offset);
            attributes_.push_back(index);
            offset += 2 * sizeof(float);
        } else {
            LOGD("Cannot find \'a_tex1\'");
            return false;
        }
    }
    LOGD("offset " << offset);

    if ((geometry.getAttribute() & Geometry::ANorm) > 0) {
        GLint index = glGetAttribLocation(program_, "a_norm");
        if (index != -1) {
            glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride,
                    (GLvoid*) offset);
            attributes_.push_back(index);
            offset += 3 * sizeof(float);
        } else {
            LOGD("Cannot find \'a_norm\'");
            return false;
        }
    }

    if ((geometry.getAttribute() & Geometry::ATex2) > 0) {
        GLint index = glGetAttribLocation(program_, "a_tex2");
        if (index != -1) {
            glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride,
                    (GLvoid*) offset);
            attributes_.push_back(index);
            offset += 2 * sizeof(float);
        } else {
            LOGD("Cannot find \'a_tex2\'");
            return false;
        }
    }

    return true;
}

/*************************************************/
bool ShaderProgram::bindMaterial(const Material &material) {

    material.apply();
    return true;
}

} /* namespace bsk */
