/*
 * Cube.c
 *
 *  Created on: Mar 29, 2021
 *      Author: sdady
 */

#include "Cube.h"

namespace bsk {

/*************************************************/
Cube::Cube() {

}

/*************************************************/
Cube::~Cube() {
}

/*************************************************/
void Cube::initialize() {

   float v[] = {
         // front face
         -1,  1,  1,
          1,  1,  1,
          1, -1,  1,
         -1  -1,  1,
         // back face
         -1,  1, -1,
          1,  1, -1,
          1, -1, -1,
         -1  -1, -1};

   ushort f[] = {
         // front
         0, 1, 2,
         0, 2, 3,
         // right
         1, 5, 6,
         1, 6, 2,
         // back
         5, 4, 7,
         5, 7, 6,
         // left
         4, 0, 3,
         4, 3, 7,
   };

   std::vector<float> verts(v, v+ sizeof(v) / sizeof(float));
   std::vector<ushort> faces(f, f+ sizeof(f) / sizeof(ushort));

//   geometry_.initialize(8, )

}

/*************************************************/
void Cube::render() {
}

}
