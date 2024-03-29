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
   width_ = 800;
   height_ = 600;
   maxHeight_ = 20;
}

/*************************************************/
FontManager::~FontManager() {
   fontTexture_.dispose();
}

/*************************************************/
bool FontManager::initialize(const std::string &fontImage, const std::string &fontData, const std::string &shaderFilename) {

   LOGGL();
   width_ = GameEngine::get().getWidth();
   height_ = GameEngine::get().getHeight();

   // load the shaders
   std::string vertFilename = shaderFilename + ".vert";
   std::string fragFilename = shaderFilename + ".frag";
   shader_.loadShaderFromFile(vertFilename, fragFilename);

   // load the image
   Image img;
   ImageLoader::loadImage(fontImage, img);
   LOGGL();
   fontTexture_.setImage(img);
   LOGGL();
   fontTexture_.apply();
   LOGGL();

   // set the texture wrapping/filtering options (on the currently bound texture object)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // unbind the texture
   glBindTexture( GL_TEXTURE_2D, 0);
   LOGGL();

   // set the projection
   glm::mat4 proj(1);
   glm::vec4 col(0, 0, 0, 1);
   proj = glm::ortho(0.0f, (float)width_, 0.0f, (float)height_, -1.0f, 1.0f);
   LOGD("proj " << proj);
   shader_.use();
   LOGGL();
   shader_.setMatrix4("u_projection", proj);
   LOGGL();
   shader_.setVec4("u_color", col);
   LOGGL();

   // load the font data file
   std::ifstream in;
   in.open(fontData.c_str());

   // open the file
   if (in.is_open()) {
      std::string line;
      fontData_.clear();
      maxHeight_ = 0;

      // get each line
      while (std::getline(in, line)) {
         FontData data;
         if (line.size() < 4) {
            LOGW("Invalid line: " << line);
         } else {
            // parse the line. the first char characters are the char '<char>'
            std::vector<std::string> parts = StringUtility::split(line.substr(3), " ");

            if (parts.size() != 10) {
               LOGW("Expecting 10 columns after the character " << line);
            } else {
               try {
                  data.character = std::stoi(parts[0]);
                  data.sizeX = std::stoi(parts[1]);
                  data.sizeY = std::stoi(parts[2]);
                  data.bearingX = std::stoi(parts[3]);
                  data.bearingY = std::stoi(parts[4]);
                  data.advance = std::stoi(parts[5]);

                  data.u1 = std::stod(parts[6]);
                  data.v1 = std::stod(parts[7]);
                  data.u2 = std::stod(parts[8]);
                  data.v2 = std::stod(parts[9]);

                  // save the data
                  fontData_[data.character] = data;

                  // find the max height of the letters
                  // this will be used for new lines
                  if (maxHeight_ < data.sizeY) {
                     maxHeight_ = data.sizeY;
                  }

               } catch (std::exception &e) {
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
void FontManager::update() {

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glm::mat4 proj(1);
   proj = glm::ortho(0.0f, (float)GameEngine::get().getWidth(), 0.0f, (float)GameEngine::get().getHeight(), -1.0f, 1.0f);

   shader_.use();
   LOGGL();
   shader_.setMatrix4("u_projection", proj);
   LOGGL();

   fontTexture_.apply();

   for (auto pair : fonts_) {
      // set the color
      shader_.setVec4("u_color", pair.second.getColor());

      // render
      pair.second.render();
   }
}

/*************************************************/
void FontManager::resize(uint width, uint height) {

   width_ = width;
   height_ = height;

   for (auto pair : fonts_) {
      pair.second.resize(fontData_, width, height);
   }
}

/*************************************************/
void FontManager::setFont(const std::string &id,
      const std::string &text,
      uint x, uint y,
      uint depth,
      float scale,
      const glm::vec4 &color) {

   fonts_[id].initialize(fontData_, text, x, y, depth, scale, color, maxHeight_ * scale, width_, height_);
}

} /* namespace bsk */
