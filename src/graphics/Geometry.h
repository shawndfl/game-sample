/*
 * Geometry.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_GEOMETRY_H_
#define SRC_GEOMETRY_H_

#include <vector>
#include <sys/types.h>
#include "graphics/VertexAttribute.h"
#include "glad/glad.h"

namespace bsk {

class ShaderProgram;

class Geometry {
public:

   Geometry();

   virtual ~Geometry();

   void initialize(uint vertexCount, uint indexCount, VertexAttributes attribute, bool dynamic = false);

   void setBuffers(const std::vector<float>& verts, const std::vector<GLushort>& indice);

   void dispose();

   void makeActive(const ShaderProgram& shader) const;

   GLuint IndexCount() const;

   VertexAttributes getAttribute() const;

protected:

   GLuint    vb_;
   GLuint    ib_;
   GLuint    vao_;

   uint       indexCount_;
   uint       vertexCount_;

   VertexAttributes             attribute_;
   std::vector<GLuint>    attributeIndex_;

};

} /* namespace bsk */


#endif /* SRC_GEOMETRY_H_ */
