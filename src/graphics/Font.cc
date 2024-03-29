/*
 * Font.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Font.h"
#include "core/Logging.h"
#include "core/GameEngine.h"

namespace bsk {

/*************************************************/
Font::Font() {
   posX_  = 0;
   posY_  = 0;
   depth_ = 0;
   maxHeight_ = 0;
   scale_ = 1.0;
   const uint MAX_CH = 50;

   geometry_.initialize(MAX_CH * 4 * 5, MAX_CH * 6, APos | ATex1);
}

/*************************************************/
Font::~Font() {
}

/*************************************************/
void Font::createBuffers(const std::map<char, FontData>& charData, uint width, uint height) {

    std::vector<float> verts;
    std::vector<GLuint> indices;
    float originX = posX_;
    float originY = height - posY_ - maxHeight_;
    float offsetX = originX;
    float offsetY = originY;
    float xpos1 = offsetX;
    float ypos1 = offsetY;
    float xpos2 = offsetX;
    float ypos2 = offsetY;

    float zpos = depth_;
    int charCount = 0;
    //LOGD("position " << originX << ", " << originY);
    for (uint i = 0; i < text_.size(); i++) {
        unsigned char ch = text_[i];
        if (ch == '\n') {
            offsetY -= (float)maxHeight_;
            offsetX = originX;
            continue;
        } else if (ch < ' ' || ch > '~') {
            ch = '?';
        }

        auto index = charData.find(ch);
        if (index == charData.end()) {
            LOGD("Don't have data for ch: " << (int) ch);
        }

        FontData data = (*index).second;

        xpos1 = offsetX + scale_ * (float)(data.bearingX);
        ypos1 = offsetY - scale_ * (float)(data.sizeY - data.bearingY);      // bottom of the letter

        xpos2 = offsetX + scale_ * (float)(data.advance);
        ypos2 = offsetY + scale_ * (float)(data.bearingY); // top of the letter

        offsetX = xpos2;

        //LOGD("Character " << (int) ch << " = " <<ch);
        //LOGD("offset " << xpos1 << ", " << ypos1 << " to " << xpos2 << ", " << ypos2);

        float tu1 = data.u1;
        float tv1 = data.v2;

        float tu2 = data.u2;
        float tv2 = data.v1;

        //LOGD("texture " << tu1 << ", " << tv1 << " to " << tu2 << ", " << tv2);

        // top left
        verts.push_back(xpos1);
        verts.push_back(ypos1);
        verts.push_back(zpos);
        verts.push_back(tu1);
        verts.push_back(tv1);

        // top right
        verts.push_back(xpos2);
        verts.push_back(ypos1);
        verts.push_back(zpos);
        verts.push_back(tu2);
        verts.push_back(tv1);

        // bottom right
        verts.push_back(xpos2);
        verts.push_back(ypos2);
        verts.push_back(zpos);
        verts.push_back(tu2);
        verts.push_back(tv2);

        // bottom left
        verts.push_back(xpos1);
        verts.push_back(ypos2);
        verts.push_back(zpos);
        verts.push_back(tu1);
        verts.push_back(tv2);

        indices.push_back(charCount * 4 + 0);
        indices.push_back(charCount * 4 + 1);
        indices.push_back(charCount * 4 + 3);

        indices.push_back(charCount * 4 + 1);
        indices.push_back(charCount * 4 + 2);
        indices.push_back(charCount * 4 + 3);

        charCount++;
    }

    geometry_.setBuffers(verts, indices);
}

/*************************************************/
void Font::initialize(const std::map<char, FontData>& charData,
      const std::string& text,
        int x, int y,
        int depth,
        float scale,
        const glm::vec4& color,
        int maxHeight,
        uint width,
        uint height) {

    color_ = color;
    text_ = text;
    posX_ = x;
    posY_ = y;
    depth_ = depth;
    scale_ = scale;
    maxHeight_ = maxHeight;

    createBuffers(charData, width, height);

}

/*************************************************/
void Font::render() {

   geometry_.makeActive();
   glDrawElements(GL_TRIANGLES, geometry_.getPrimitiveCount(), GL_UNSIGNED_INT, NULL);
}

/*************************************************/
void Font::resize(const std::map<char, FontData>& charData, uint width, uint height) {
    createBuffers(charData, width, height);
}

/*************************************************/
void Font::dispose() {

}

/*************************************************/
const Geometry& Font::getGeometry() const {
    return geometry_;
}

/*************************************************/
const glm::vec4& Font::getColor() const {
   return color_;
}

} /* namespace bsk */
