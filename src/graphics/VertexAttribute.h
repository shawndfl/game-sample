/*
 * VertexAttribute.h
 *
 *  Created on: Apr 12, 2021
 *      Author: sdady
 */

#ifndef SRC_GRAPHICS_VERTEXATTRIBUTE_H_
#define SRC_GRAPHICS_VERTEXATTRIBUTE_H_
#include <ostream>

namespace bsk {
/**
 * Vertex attributes for geometry and shaders
 */
enum VertexAttributes: char {
         ANone    = 0x00,
         APos     = 0x01,
         AColor   = 0x02,
         ATex1    = 0x04,
         ANorm    = 0x08,
         ASkin    = 0x10,
   };

}

/*************************************************/
inline std::ostream& operator<<(std::ostream& stream, const bsk::VertexAttributes a) {
   stream << "[";
   if ((a & bsk::APos) > 0) {
      stream << "Pos ";
   }
   if ((a & bsk::ATex1) > 0) {
      stream << "Tex ";
   }
   if ((a & bsk::ANorm) > 0) {
      stream << "Normal ";
   }
   stream << "]";

   return stream;
}

/*************************************************/
inline bsk::VertexAttributes operator|(bsk::VertexAttributes a, bsk::VertexAttributes b) {
    return static_cast<bsk::VertexAttributes>(static_cast<char>(a) | static_cast<char>(b));
}
#endif /* SRC_GRAPHICS_VERTEXATTRIBUTE_H_ */
