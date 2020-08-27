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
#include "Material.h"

namespace bsk {

/*
 * Shader program that will require a material and geometry
 */
class ShaderProgram {
public:

   ShaderProgram();

   virtual ~ShaderProgram();

   bool loadProgram();

   void enableProgram();

   bool bindGeometry(const Geometry& geometry);

   bool bindMaterial(const Material& material);

private:

   GLuint              program_;
   std::vector<GLuint> attributes_;

   // uniforms
   int                 diffusedTex1_;

};

} /* namespace bsk */

#endif /* SRC_SHADERPROGRAM_H_ */
