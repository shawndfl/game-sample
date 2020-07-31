/*
 * ShaderProgram.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "ShaderProgram.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
ShaderProgram::ShaderProgram() {
   program_ = 0;
}

/*************************************************/
ShaderProgram::~ShaderProgram() {
}

/*************************************************/
bool ShaderProgram::loadProgram(const std::string& vertexSource, const std::string& fragmentSource) {
   const uint LOG_LEN = 1024;
   GLchar infoLog[LOG_LEN];
   GLint success;

   // Vertex Shader
   GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, (const GLchar *const*) vertexSource.c_str(), NULL);
   glCompileShader (vertex);
   glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(vertex, LOG_LEN, NULL, infoLog);
      LOGD("Vertex compiler error: " << infoLog);
      return false;
   }

   // Fragment Shader
   GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, (const GLchar *const*)fragmentSource.c_str(), NULL);
   glCompileShader (fragment);
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
      return false;
   }

   glDeleteShader(vertex);
   glDeleteShader(fragment);

   return true;
}

/*************************************************/
void ShaderProgram::enableProgram() {
   glUseProgram(program_);

   for(auto attr: attributeId_) {
      glEnableVertexAttribArray(attr);
   }
}

/*************************************************/
void ShaderProgram::attachGeometry(const Geometry& geometry) {
   GLint index = glGetAttribLocation(program_, "position");
   if (index != -1) {
      glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
      attributeId_.push_back(index);
   }
}

} /* namespace bsk */
