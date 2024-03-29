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

/**
 * Geometry class that holds the vertex, index and vertex buffer array
 */
class Geometry {
public:

   Geometry();

   virtual ~Geometry();

   /**
    * Create geometry buffer using the given inputs
    */
   void initialize(uint vertexCount, uint indexCount, VertexAttributes attribute, bool dynamic = false);

   void setBuffers(std::vector<float>& verts, std::vector<GLuint>& indices);

   void setBuffers(float* verts, uint vertexCount, GLuint* indices, uint indexCount);

   void dispose();

   void makeActive() const;

   GLuint IndexCount() const;

   GLuint vertexCount() const;

   VertexAttributes getAttribute() const;

   GLuint getStride() const;

   GLuint getPrimitiveCount() const;

protected:

   GLuint    vb_;
   GLuint    ib_;
   GLuint    vao_;

   GLuint     indexCount_;              /// How big is the index buffer
   GLuint     vertexCount_;             /// How big is the vertex buffer
   GLuint     primitiveCount_;          /// How many indices are we drawing

   VertexAttributes       attribute_;
   std::vector<GLuint>    attributeIndex_;

};

} /* namespace bsk */


#endif /* SRC_GEOMETRY_H_ */
