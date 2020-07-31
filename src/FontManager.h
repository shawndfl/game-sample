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

   void addFont(const std::string& text, uint width, uint height);

private:
   std::vector<Font>    fonts_;

};

} /* namespace bsk */

#endif /* SRC_FONTMANAGER_H_ */
