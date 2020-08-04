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
bool ShaderProgram::loadProgram(const char* vertexSource, const char* fragmentSource) {
   const uint LOG_LEN = 1024;
   GLchar infoLog[LOG_LEN];
   GLint success;

   // Vertex Shader
   GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vertexSource, NULL);
   glCompileShader (vertex);
   glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(vertex, LOG_LEN, NULL, infoLog);
      LOGD("Vertex compiler error: " << infoLog);
      return false;
   }

   // Fragment Shader
   GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, &fragmentSource, NULL);
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

      glDeleteShader(vertex);
      glDeleteShader(fragment);
      return false;
   }
   glDeleteShader(vertex);
   glDeleteShader(fragment);


   return true;
}

/*************************************************/
void ShaderProgram::enableProgram() {
   // enable our shader program
   glUseProgram(program_);

   for( auto attr: attributes_) {
      glEnableVertexAttribArray(attr);
   }
}

/*************************************************/
bool ShaderProgram::bindGeometry(const Geometry& geometry) {
   // enable out geometry
   geometry.makeActive();

   // set our attributes
   long offset = 0;
   if ((geometry.getAttribute() & Geometry::APos) > 0) {
      GLint index = glGetAttribLocation(program_, "pos");
      if (index != -1) {
         glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
         attributes_.push_back(index);
         offset += 3 * sizeof(float);
      } else {
         LOGD("Cannot find \'pos\'");
         return false;
      }
   }

   if ((geometry.getAttribute() & Geometry::ATex1) > 0) {
      GLint index = glGetAttribLocation(program_, "tex1");
      if (index != -1) {
         glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
         attributes_.push_back(index);
         offset += 2 * sizeof(float);
      } else {
         LOGD("Cannot find \'tex1\'");
         return false;
      }
   }

   if ((geometry.getAttribute() & Geometry::ANorm) > 0) {
      GLint index = glGetAttribLocation(program_, "norm");
      if (index != -1) {
         glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
         attributes_.push_back(index);
         offset += 3 * sizeof(float);
      } else {
         LOGD("Cannot find \'norm\'");
         return false;
      }
   }

   if ((geometry.getAttribute() & Geometry::ATex2) > 0) {
      GLint index = glGetAttribLocation(program_, "tex2");
      if (index != -1) {
         glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) offset);
         attributes_.push_back(index);
         offset += 2 * sizeof(float);
      } else {
         LOGD("Cannot find \'tex2\'");
         return false;
      }
   }

   return true;
}

} /* namespace bsk */
