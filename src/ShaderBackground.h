/*
 * ShaderBackground.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERBACKGROUND_H_
#define SRC_SHADERBACKGROUND_H_

#include <string>
#include <vector>
#include <GLES2/gl2.h>

#include "Geometry.h"
#include "Material.h"

namespace bsk {

/*
 * Shader program that will require a material and geometry
 */
class ShaderBackground {
public:

   ShaderBackground();

   virtual ~ShaderBackground();

   bool loadProgram();

   void enableProgram();

   bool bindMaterial(const Material& material);

   int getUniformLocation(const std::string& name);

   int getAttributeLocation(const std::string& name);
   int getNormal() const;
   int getPosition() const;
   int getTexture() const;
   int getByteStride() const;

private:

   GLuint         program_;

   // uniforms
   int          diffused_;
   int          overlay_;
   int          color_;
   int          uscale_;
   int          vscale_;
   int          uoffset_;
   int          voffset_;

   // attributes
   int          position_;
   int          texture_;
   int          normal_;

   int          byteStride_;

};

} /* namespace bsk */

#endif /* SRC_SHADERBACKGROUND_H_ */
