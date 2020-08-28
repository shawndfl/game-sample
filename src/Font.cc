/*
 * Font.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Font.h"
#include "Logging.h"
#include "GameEngine.h"
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
void Font::initialize(const std::string& text, float screenX, float screenY, float scale) {

    const int rows = 10;
    const int cols = 10;
    const int width = 1024;
    const int height = 1024;
    const float chWidth = 102.4;
    const float chHeight = 102.4;
    const float chStep = scale * .1;

    const int screenWidth = GameEngine::get().getWidth();
    const int screenHeight = GameEngine::get().getHeight();

    std::vector<float> verts;
    std::vector<GLushort> indices;
    float xpos = screenX;
    float ypos = screenY;
    float zpos = 0;
    int charCount = 0;

    for (uint i = 0; i < text.size(); i++) {
        unsigned char ch = text[i];

        if(ch =='\n') {
            ypos -= chStep;
            xpos = screenX;
            continue;
        } else  if (ch < ' ' || ch > '~') {
            ch = '?';
        }

        unsigned char chXOffset1 = (ch - ' ') % cols;
        unsigned char chYOffset1 = (ch - ' ') / cols;
        unsigned char chXOffset2 = chXOffset1 + 1;
        unsigned char chYOffset2 = chYOffset1 + 1;

        //LOGD("offset " << (int)chXOffset1 << ", " << (int)chYOffset1 << ", " << (int)chXOffset2 << ", " << (int)chYOffset2);

        float scaleX = chHeight * (float) chYOffset1;
        LOGD("scaleX "<< scaleX);

        float tu1 = (float) (chWidth * (float) chXOffset1) / (float) width;
        float tv1 = (float) (chHeight * (float) chYOffset1) / (float) height;

        float tu2 = (float) (chWidth * (float) chXOffset2) / (float) width;
        float tv2 = (float) (chHeight * (float) chYOffset2) / (float) height;

        // top left
        verts.push_back(xpos);
        verts.push_back(ypos);
        verts.push_back(zpos);
        verts.push_back(tu1);
        verts.push_back(tv1);

        // top right
        verts.push_back(xpos + chStep);
        verts.push_back(ypos);
        verts.push_back(zpos);
        verts.push_back(tu2);
        verts.push_back(tv1);

        // bottom right
        verts.push_back(xpos + chStep);
        verts.push_back(ypos - chStep);
        verts.push_back(zpos);
        verts.push_back(tu2);
        verts.push_back(tv2);

        // bottom left
        verts.push_back(xpos);
        verts.push_back(ypos - chStep);
        verts.push_back(zpos);
        verts.push_back(tu1);
        verts.push_back(tv2);

        indices.push_back(charCount * 4 + 0);
        indices.push_back(charCount * 4 + 1);
        indices.push_back(charCount * 4 + 2);

        indices.push_back(charCount * 4 + 0);
        indices.push_back(charCount * 4 + 2);
        indices.push_back(charCount * 4 + 3);

        charCount++;
        xpos += chStep;
    }

    //for (int i = 0; i < verts.size(); i++) {
    //    LOGD("vert " << i << ":  " << verts[i]);
    //}

    //for (int i = 0; i < indices.size(); i++) {
    //    LOGD("indices " << i << ":  " << indices[i]);
    //}

    geometry_.initialize(verts, indices, Geometry::APos | Geometry::ATex1);
    if(!shader_.bindGeometry(geometry_)) {

    }
}

/*************************************************/
void Font::render() {
   //LOGD("text: "<< text_ << " x:" <<  screenX_ << " y:" << screenY_);

   shader_.enableProgram();
   glDrawElements(GL_TRIANGLES, geometry_.IndexCount(), GL_UNSIGNED_SHORT, NULL);
}

/*************************************************/
void Font::dispose() {

}

} /* namespace bsk */
