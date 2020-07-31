/*
 * Font.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Font.h"
#include "Logging.h"
#include "GLES2/gl2.h"

namespace bsk {


static const GLchar* vertexShaderSource =
    "#version 100\n"
    "attribute vec3 position;\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "}\n";

static const GLchar* fragmentShaderSource =
    "#version 100\n"
    "void main() {\n"
    "   gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
    "}\n";

static const GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
};

static const GLushort faces[] = {
        0, 1, 2,
        0, 2, 3
};

/*************************************************/
Font::Font() {
   screenX_  = 0;
   screenY_  = 0;

   fragment_ = 0;
   vertex_   = 0;
   program_  = 0;

   ib_       = 0;
   vb_       = 0;
}

/*************************************************/
Font::~Font() {
}

/*************************************************/
void Font::initialize(const std::string& text, uint screenX, uint screenY) {
   dispose();
   text_ = text;
   screenX_ = screenX;
   screenY_ = screenY;

   const uint  LOG_LEN = 1024;
   GLchar      infoLog[LOG_LEN];
   GLint       success;

   // Vertex Shader
   vertex_ = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_, 1, &vertexShaderSource, NULL);
   glCompileShader(vertex_);
   glGetShaderiv(vertex_, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(vertex_, LOG_LEN, NULL, infoLog);
      LOGD("Vertex compiler error: " <<  infoLog);
   }

   // Fragment Shader
   fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragment_);
   glGetShaderiv(fragment_, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(fragment_, LOG_LEN, NULL, infoLog);
      LOGD("Fragment compiler error: " <<  infoLog);
   }

   program_ = glCreateProgram();
   glAttachShader(program_, vertex_);
   glAttachShader(program_, fragment_);
   glLinkProgram (program_);
   glGetProgramiv(program_, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(program_, LOG_LEN, NULL, infoLog);
      LOGD("Program link error: " <<  infoLog);
   }

   glDeleteShader (vertex_);
   glDeleteShader (fragment_);

   // setup vertex buffer
   GLint vertexSize = sizeof(vertices);
   glGenBuffers(1, &vb_);
   glBindBuffer(GL_ARRAY_BUFFER, vb_);
   glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

   GLint size = 0;
   GLuint pos = glGetAttribLocation(program_, "position");
   glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
   glEnableVertexAttribArray (pos);
   glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
   if(vertexSize != size){
      glDeleteBuffers(1, &vb_);
      LOGD("Error creating vertex buffer with size of: " << vertexSize);
   }

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // setup index buffer
   GLint faceCount = sizeof(faces);
   glGenBuffers(1, &ib_);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceCount, 0, GL_STATIC_DRAW);
   glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, faceCount, faces);

   glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
   if(faceCount != size){
       glDeleteBuffers(1, &ib_);
       LOGD("Error creating index buffer with size of: " << faceCount);
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

/*************************************************/
void Font::render() {
   //LOGD("text: "<< text_ << " x:" <<  screenX_ << " y:" << screenY_);
   glUseProgram(program_);
   glBindBuffer(GL_ARRAY_BUFFER, vb_);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);

   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

/*************************************************/
void Font::dispose() {
   glDeleteBuffers(1, &ib_);
   ib_ = 0;

   glDeleteBuffers(1, &vb_);
   vb_ = 0;

   glDeleteProgram(program_);
   program_ = 0;
}

} /* namespace bsk */
