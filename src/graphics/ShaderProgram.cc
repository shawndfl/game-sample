/*
 * ShaderProgram.cc
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#include "ShaderProgram.h"
#include "core/Logging.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

namespace bsk {

/*************************************************/
ShaderProgram::ShaderProgram() {
    program_ = -1;
}

/*************************************************/
ShaderProgram::~ShaderProgram() {
}

/*************************************************/
void ShaderProgram::use() const {
    LOGGL();
    glUseProgram(program_);
    LOGGL();
}

/*************************************************/
void ShaderProgram::setBool(const std::string& name, bool value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if(loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniform1i(loc, (int)value);
    }
}

/*************************************************/
void ShaderProgram::setInt(const std::string& name, int value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniform1i(loc, value);
    }
}

/*************************************************/
void ShaderProgram::setFloat(const std::string& name, float value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniform1f(loc, (int) value);
    }
}

/*************************************************/
void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniformMatrix4fv(loc, 1, false,  glm::value_ptr(value));
    }
}

/*************************************************/
void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniform3fv(loc, 1, &value[0]);
    }
}

/*************************************************/
void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const {
    int loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        LOGE("Cannot find " << name << " in shader " << vertexPath_ << " or " << fragmentPath_);
    } else {
        glUniform4fv(loc, 1, &value[0]);
    }
}

/*************************************************/
bool ShaderProgram::loadShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vertexPath_ = vertexPath;
    fragmentPath_ = fragmentPath;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return loadShaderFromMemory(vertexCode, fragmentCode);
}

/*************************************************/
bool ShaderProgram::loadShaderFromMemory(const std::string& vertexCode, const std::string& fragmentCode) {

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    const uint LOG_LEN = 1024;
    GLchar infoLog[LOG_LEN];
    GLint success;

    // Vertex Shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, LOG_LEN, NULL, infoLog);
        LOGD("Vertex compiler error: " << infoLog);
        return false;
    }

    // Fragment Shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
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
    return true;
}

} /* namespace bsk */
