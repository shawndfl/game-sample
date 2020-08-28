/*
 * Geometry.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Geometry.h"
#include "Logging.h"

namespace bsk {

/*************************************************/
Geometry::Geometry() {
   ib_ = 0;
   vb_ = 0;
   attribute_ = APos;
   indexCount_ = 0;
}

/*************************************************/
Geometry::~Geometry() {
}

/*************************************************/
void Geometry::initialize(const std::vector<float>& verts, const std::vector<GLushort>& indice, Attributes attribute, bool dynamic) {

   dispose();

   attribute_ = attribute;
   indexCount_ = indice.size();

   GLint size;
   GLint byteSize;

   // setup vertex buffer
   byteSize = verts.size() * sizeof(float);
   glGenBuffers(1, &vb_);
   glBindBuffer(GL_ARRAY_BUFFER, vb_);
   glBufferData(GL_ARRAY_BUFFER, byteSize, verts.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
   glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
   if (byteSize != size) {
      glDeleteBuffers(1, &vb_);
      LOGD("Error creating vertex buffer with size of: " << byteSize);
   }

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // setup index buffer
   byteSize = indice.size() * sizeof(GLushort);
   glGenBuffers(1, &ib_);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, 0, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
   glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, byteSize, indice.data());

   glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
   if (byteSize != size) {
      glDeleteBuffers(1, &ib_);
      LOGD("Error creating index buffer with size of: " << byteSize);
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*************************************************/
void Geometry::dispose() {
   if (vb_ != 0) {
      glDeleteBuffers(1, &vb_);
      vb_ = 0;
   }

   if (ib_ != 0) {
      glDeleteBuffers(1, &ib_);
      ib_ = 0;
   }
}

/*************************************************/
void Geometry::makeActive() const {
   glBindBuffer(GL_ARRAY_BUFFER, vb_);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
}

/*************************************************/
GLuint Geometry::IndexCount() const {
    return indexCount_;
}

/*************************************************/
Geometry::Attributes Geometry::getAttribute() const {
   return attribute_;
}

} /* namespace bsk */
