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

namespace bsk {

class Geometry {
public:
   enum Attributes {
         APos     = 0x01,
         ATex1    = 0x02,
         ANorm    = 0x04,
         ATex2    = 0x08,
         ASkin    = 0x10,
   };

   Geometry();

   virtual ~Geometry();

   void initialize(const std::vector<float>& verts, const std::vector<GLushort>& indice, Attributes attribute);

   void dispose();

   void makeActive() const;

   Attributes getAttribute() const;

protected:

   GLuint    vb_;
   GLuint    ib_;

   Attributes             attribute_;
   std::vector<GLuint>    attributeIndex_;

};

} /* namespace bsk */

#endif /* SRC_GEOMETRY_H_ */
