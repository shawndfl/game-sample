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
    float originY = posY_;
    float offsetX = originX / width;
    float offsetY = originY / height;
    float xpos1 = offsetX  / width;
    float ypos1 = offsetY  / height;
    float xpos2 = offsetX  / width;
    float ypos2 = offsetY  / height;

    float scale = 1;

    float zpos = depth_;
    int charCount = 0;
    LOGD("position " << originX << ", " << originY);
    for (uint i = 0; i < text_.size(); i++) {
        unsigned char ch = text_[i];
        if (ch == '\n') {
            offsetY -= (float)maxHeight_ / height;
            offsetX = originX / width;
            continue;
        } else if (ch < ' ' || ch > '~') {
            ch = '?';
        }

        auto index = charData.find(ch);
        if (index == charData.end()) {
            LOGD("Don't have data for ch: " << (int) ch);
        }

        FontData data = (*index).second;

        xpos1 = offsetX + (float)(data.bearingX) / width;
        ypos1 = offsetY - (float)((data.sizeY - data.bearingY)) / height;      // bottom of the letter

        xpos2 = offsetX + (float)(data.advance) / width;
        ypos2 = offsetY + (float)(data.bearingY) / height; // top of the letter

        offsetX = xpos2;

        LOGD("Character " << (int) ch << " = " <<ch);
        LOGD("offset " << xpos1 << ", " << ypos1 << " to " << xpos2 << ", " << ypos2);

        float tu1 = data.u1;
        float tv1 = data.v2;

        float tu2 = data.u2;
        float tv2 = data.v1;

        LOGD("texture " << tu1 << ", " << tv1 << " to " << tu2 << ", " << tv2);

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
void Font::initialize(const std::map<char, FontData>& charData, const std::string& text,
        uint x, uint y, uint depth, const glm::vec4& color) {

    color_ = color;
    text_ = text;
    posX_ = x;
    posY_ = y;
    depth_ = depth;
    maxHeight_ = 0;
    for(auto pair: charData) {
       if( maxHeight_ < pair.second.sizeY) {
          maxHeight_ = pair.second.sizeY;
       }
    }

    createBuffers(charData);

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
