/*
 * Primitive.cc
 *
 *  Created on: Apr 30, 2022
 *      Author: shawn
 */

#include "graphics/Primitive.h"
#include <math.h>

namespace bsk {

/*************************************************/
Primitive::Primitive() {
}

/*************************************************/
Primitive::~Primitive() {
}

/*************************************************/
Geometry Primitive::createQuad() {
   Geometry geometry;

   float vertices[] = {
         // positions          // text       // colors
         -0.5f,  0.5f, 0.0f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   // top right
          0.5f,  0.5f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   // bottom right
          0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   // bottom left
         -0.5f, -0.5f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f    // top left
         };
   GLuint indices[] = {
         0, 1, 3,  // first Triangle
         1, 2, 3   // second Triangle
         };

   uint vertSize = sizeof(vertices) / sizeof(float);
   uint indSize = sizeof(indices) / sizeof(GLuint);
   bsk::VertexAttributes attribute = bsk::APos | bsk::AColor | bsk::ATex1;

   geometry.initialize(vertSize, indSize, attribute, false);
   geometry.setBuffers(vertices, vertSize, indices, indSize);

   return geometry;
}

/*************************************************/
Geometry Primitive::createPlane(const glm::vec2 &size, uint widthSegments, uint heightSegments) {
   float widthHalf = size.x / 2.0;
   float heightHalf = size.y / 2.0;

   uint gridX = widthSegments;
   uint gridY = heightSegments;

   uint gridX1 = gridX + 1;
   uint gridY1 = gridY + 1;

   float segmentWidth = size.x / gridX;
   float segmentHeight = size.y / gridY;

   std::vector<uint> indices;
   std::vector<posTxtNorm> vertices;

   for (uint iy = 0; iy < gridY1; iy++) {

      float  y = iy * segmentHeight - heightHalf;

      for (uint ix = 0; ix < gridX1; ix++) {

         float x = ix * segmentWidth - widthHalf;

         posTxtNorm vert;
         vert.pos = glm::vec3(x, -y, 0);
         vert.txt = glm::vec2((float)ix / gridX, 1.0 - ((float)iy / gridY));
         vert.norm = glm::vec3(0, 0, 1);

         vertices.push_back(vert);
      }

   }

   for (uint iy = 0; iy < gridY; iy++) {

      for (uint ix = 0; ix < gridX; ix++) {

         uint a = ix + gridX1 * iy;
         uint b = ix + gridX1 * ( iy + 1 );
         uint c = ( ix + 1 ) + gridX1 * ( iy + 1 );
         uint d = ( ix + 1 ) + gridX1 * iy;

         indices.push_back(a);
         indices.push_back(b);
         indices.push_back(d);

         indices.push_back(b);
         indices.push_back(c);
         indices.push_back(d);

      }
   }

   Geometry geometry;
   uint vertSize = sizeof(posTxtNorm) / sizeof(float) * vertices.size();
   uint indSize = sizeof(uint) / sizeof(GLuint) * indices.size();
   bsk::VertexAttributes attribute = bsk::APos | bsk::AColor | bsk::ATex1;

   geometry.initialize(vertSize, indSize, attribute, false);
   geometry.setBuffers((float*)vertices.data(), vertSize, indices.data(), indSize);
   return geometry;
}

} /* namespace bsk */
