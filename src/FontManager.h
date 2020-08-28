/*
 * FontManager.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_FONTMANAGER_H_
#define SRC_FONTMANAGER_H_

#include "Font.h"
#include <vector>
#include <string>

#include <sys/types.h>

namespace bsk {

class FontManager {
public:
   FontManager();
   virtual ~FontManager();

   void update();

   void addFont(const std::string& text, float width, float height, float scale = 1.0);

private:
   std::vector<Font>    fonts_;
   Image                fontImg_;

};

} /* namespace bsk */

#endif /* SRC_FONTMANAGER_H_ */
