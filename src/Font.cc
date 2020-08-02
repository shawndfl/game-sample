/*
 * Font.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Font.h"
#include "Logging.h"
#include <GLES2/gl2.h>

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

   shader_.loadProgram(vertexShaderSource, fragmentShaderSource);
   std::vector<float> verts;
   for (int i = 0; i < 12; i++) {
      verts.push_back(vertices[i]);
   }
   std::vector<GLushort> indices;
   for (int i = 0; i < 6; i++) {
      indices.push_back(faces[i]);
   }
   geometry_.initialize(verts, indices, Geometry::APos);
   shader_.attachGeometry(geometry_);
}

/*************************************************/
Font::~Font() {
}

/*************************************************/
void Font::initialize(const std::string& text, uint screenX, uint screenY) {

   dispose();
}

/*************************************************/
void Font::render() {
   //LOGD("text: "<< text_ << " x:" <<  screenX_ << " y:" << screenY_);

   shader_.enableProgram();
   geometry_.makeActive();
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
