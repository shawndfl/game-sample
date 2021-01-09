/*
 * Geometry.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_GEOMETRY_H_
#define SRC_GEOMETRY_H_

#include <GLES2/gl2.h>
#include <vector>
#include <sys/types.h>

namespace bsk {

class ShaderProgram;

class Geometry {
public:
   enum Attributes: char {
         APos     = 0x01,
         ATex1    = 0x02,
         ANorm    = 0x04,
         ATex2    = 0x08,
         ASkin    = 0x10,
   };

   Geometry();

   virtual ~Geometry();

   void initialize(uint vertexCount, uint indexCount, Attributes attribute, bool dynamic = false);

   void setBuffers(const std::vector<float>& verts, const std::vector<GLushort>& indice);

   void dispose();

   void makeActive(const ShaderProgram& shader) const;

   GLuint IndexCount() const;

   Attributes getAttribute() const;

protected:

   GLuint    vb_;
   GLuint    ib_;
   GLuint    vao_;

   uint       indexCount_;
   uint       vertexCount_;

   Attributes             attribute_;
   std::vector<GLuint>    attributeIndex_;

};

} /* namespace bsk */

inline bsk::Geometry::Attributes operator|(bsk::Geometry::Attributes a, bsk::Geometry::Attributes b)
{
    return static_cast<bsk::Geometry::Attributes>(static_cast<char>(a) | static_cast<char>(b));
}

#endif /* SRC_GEOMETRY_H_ */