/*
 * ShaderProgram.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERPROGRAM_H_
#define SRC_SHADERPROGRAM_H_

#include <string>
#include <vector>
#include <GLES2/gl2.h>

#include "Geometry.h"

namespace bsk {

class ShaderProgram {
public:

   ShaderProgram();

   virtual ~ShaderProgram();

   bool loadProgram(const char* vertexSource, const char* fragmentSource);

   void setTexture();

   void enableProgram();

   bool bindGeometry(const Geometry& geometry);

private:

   GLuint              program_;
   std::vector<GLuint> attributes_;
};

} /* namespace bsk */

#endif /* SRC_SHADERPROGRAM_H_ */
