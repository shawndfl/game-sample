/*
 * FontManager.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_FONTMANAGER_H_
#define SRC_FONTMANAGER_H_

#include "Font.h"
#include <map>
#include <string>
#include <sstream>

#include <sys/types.h>

namespace bsk {

class FontManager {
public:
   FontManager();
   virtual ~FontManager();

   bool initialize();

   void update();

   void setFont(const std::string& id, const std::stringstream& text, float width, float height, float scale = 1.0);

private:
   std::map<std::string, Font>    fonts_;
   Image                          fontImg_;
   ShaderProgram                  shader_;
   Material                       mat_;

};

} /* namespace bsk */

#endif /* SRC_FONTMANAGER_H_ */
