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

/*************************************************/
Font::Font() {
   screenX_  = 0;
   screenY_  = 0;
   const uint MAX_CH = 50;

   geometry_.initialize(MAX_CH * 4 * 5, MAX_CH * 6, Geometry::APos | Geometry::ATex1);
}

/*************************************************/
Font::~Font() {
}

/*************************************************/
void Font::initialize(const std::string& text, uint x, uint y, uint pixelSize, Vector4 color) {

    color_ = color;

    const int cols = 10;
    const int width = 1024;
    const int height = 1024;
    const float chWidth = 102.4;
    const float chHeight = 102.4;
    const float chStep = pixelSize;

    std::vector<float> verts;
    std::vector<GLushort> indices;
    uint xpos = x;
    uint ypos = y;
    float zpos = 0;
    int charCount = 0;

    for (uint i = 0; i < text.size(); i++) {
        unsigned char ch = text[i];

        if(ch =='\n') {
            ypos += chStep;
            xpos = x;
            continue;
        } else  if (ch < ' ' || ch > '~') {
            ch = '?';
        }

        unsigned char chXOffset1 = (ch - ' ') % cols;
        unsigned char chYOffset1 = (ch - ' ') / cols;
        unsigned char chXOffset2 = chXOffset1 + 1;
        unsigned char chYOffset2 = chYOffset1 + 1;

        //LOGD("offset " << (int)chXOffset1 << ", " << (int)chYOffset1 << ", " << (int)chXOffset2 << ", " << (int)chYOffset2);

        //float scaleX = chHeight * (float) chYOffset1;

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
        verts.push_back(ypos + chStep);
        verts.push_back(zpos);
        verts.push_back(tu2);
        verts.push_back(tv2);

        // bottom left
        verts.push_back(xpos);
        verts.push_back(ypos + chStep);
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

    geometry_.setBuffers(verts, indices);
}

/*************************************************/
void Font::render(const ShaderProgram& shader) {

   color_.setUniform(shader.getColor());

   geometry_.makeActive(shader);
   glDrawElements(GL_TRIANGLES, geometry_.IndexCount(), GL_UNSIGNED_SHORT, NULL);
}

/*************************************************/
void Font::dispose() {

}

/*************************************************/
const Geometry& Font::getGeometry() const {
    return geometry_;
}

} /* namespace bsk */
