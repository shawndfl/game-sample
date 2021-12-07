/*
 * FontManager.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "graphics/FontManager.h"
#include "graphics/ImageLoader.h"
#include "core/Logging.h"
#include "core/GameEngine.h"
#include "core/StringUtility.h"
#include <fstream>

namespace bsk {

/*************************************************/
FontManager::FontManager() {
}

/*************************************************/
FontManager::~FontManager() {
   fontTexture_.dispose();
}

/*************************************************/
void FontManager::update() {

   shader_.enableProgram();
   fontTexture_.apply();

   Matrix4 projection;
   projection.createOrthographic(0, GameEngine::get().getWidth(), 1, GameEngine::get().getHeight(), 0, 10);

   shader_.setProjection(projection);

   for(auto pair: fonts_) {
      pair.second.render(shader_);
   }
}

/*************************************************/
bool FontManager::initialize(const std::string& fontImage, const std::string& fontData ) {
    shader_.loadProgram();
    Image img;
    ImageLoader::loadImage(fontImage, img);
    fontTexture_.setImage(img);

    fontTexture_.apply();
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE0, 0);

    std::ifstream in;
    in.open(fontData.c_str());

    // open the file
    if(in.is_open()) {
        std::string line;
        fontData_.clear();

        // get each line
        while(std::getline(in, line)) {
            FontData data;
            if(line.size() < 4) {
                LOGW("Invalid line: " << line);
            } else {
                // parse the line. the first char characters are the char '<char>'
                std::vector<std::string> parts = StringUtility::split(line.substr(3), " ");

                if(parts.size() != 10) {
                    LOGW("Expecting 10 columns after the character " << line);
                } else {
                    try{
                        data.character  = std::stoi(parts[0]);
                        data.sizeX      = std::stoi(parts[1]);
                        data.sizeY      = std::stoi(parts[2]);
                        data.bearingX   = std::stoi(parts[3]);
                        data.bearingY   = std::stoi(parts[4]);
                        data.advance    = std::stoi(parts[5]);

                        data.u1         = std::stod(parts[6]);
                        data.v1         = std::stod(parts[7]);
                        data.u2         = std::stod(parts[8]);
                        data.v2         = std::stod(parts[9]);

                        // save the data
                        fontData_[data.character] = data;

                    } catch(std::exception& e) {
                        LOGE("Invalid number");
                    }

                }
            }
        }
    } else {
        LOGE("Cannot open "<< fontData);
    }

    return true;
}

/*************************************************/
void FontManager::resize(uint width, uint height) {

}

/*************************************************/
void FontManager::setFont(const std::string& id, const std::string& text, uint x, uint y, uint pixelSize, const glm::vec4& color) {
   fonts_[id].initialize(fontData_, text, x, y, pixelSize, color);
}

} /* namespace bsk */
