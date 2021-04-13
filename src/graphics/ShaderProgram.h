/*
 * ShaderProgram.h
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERPROGRAM_H_
#define SRC_SHADERPROGRAM_H_

#include "graphics/VertexAttribute.h"

namespace bsk {

/**
 * Abstract shader program used by Geometry to map vertex attributes
 */
class ShaderProgram {
public:
   ShaderProgram();
   virtual ~ShaderProgram();

   virtual int getNormal() const;
   virtual int getPosition() const;
   virtual int getTexture() const;
   virtual int getByteStride() const;

   virtual VertexAttributes getAttribute() const;

};

} /* namespace bsk */

#endif /* SRC_SHADERPROGRAM_H_ */
