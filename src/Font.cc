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


static const GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f, 0.0, 0.0,
         0.5f,  0.5f, 0.0f, 1.0, 0.0,
         0.5f, -0.5f, 0.0f, 1.0, 1.0,
        -0.5f, -0.5f, 0.0f, 0.0, 1.0
};

static const GLushort faces[] = {
        0, 1, 2,
        0, 2, 3
};

/*************************************************/
Font::Font() {
   screenX_  = 0;
   screenY_  = 0;

   shader_.loadProgram();
   std::vector<float> verts;
   for (int i = 0; i < 20; i++) {
      verts.push_back(vertices[i]);
   }
   std::vector<GLushort> indices;
   for (int i = 0; i < 6; i++) {
      indices.push_back(faces[i]);
   }

   Texture diffused;
   Image img;
   ImageLoader::loadImage("assets/img/font.png", img);
   diffused.setImage(img);
   mat_.setDiffused(diffused);

   geometry_.initialize(verts, indices, Geometry::APos | Geometry::ATex1);
   if(!shader_.bindGeometry(geometry_)) {

   }
   if(!shader_.bindMaterial(mat_)){

   }
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
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

/*************************************************/
void Font::dispose() {

}

} /* namespace bsk */
