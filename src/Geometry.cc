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
   vertexCount_ = 0;
   vao_ = 0;
}

/*************************************************/
Geometry::~Geometry() {
}

/*************************************************/
void Geometry::initialize(uint vertexCount, uint indexCount, Attributes attribute, bool dynamic) {

   dispose();

   attribute_ = attribute;
   indexCount_ = indexCount;
   vertexCount_ = vertexCount;

   glGenBuffers(1, &vb_);
   glGenBuffers(1, &ib_);

    GLint size;
    GLint byteSize;

    // setup vertex buffer
    byteSize = vertexCount_ * sizeof(float);

    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    if (byteSize != size) {
        glDeleteBuffers(1, &vb_);
        LOGD("Error creating vertex buffer with size of: " << byteSize);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // setup index buffer
    byteSize = indexCount_ * sizeof(GLushort);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    if (byteSize != size) {
        glDeleteBuffers(1, &ib_);
        LOGD("Error creating index buffer with size of: " << byteSize);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

/*************************************************/
void Geometry::setBuffers(const std::vector<float> &verts, const std::vector<GLushort> &indices) {

    uint vertCount = verts.size() > vertexCount_? vertexCount_ :  verts.size();
    uint indexCount = indices.size() > indexCount_? indexCount_ :  indices.size();

    uint vertBytes = vertCount * sizeof(float);
    uint indexBytes = indexCount * sizeof(GLushort);

    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertBytes, verts.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBytes, indices.data());
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

      // set our attributes
   long offset = 0;
   unsigned short stride = 5 * sizeof(float);

   if ((getAttribute() & Geometry::APos) > 0) {
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
      glEnableVertexAttribArray(0);
      offset += 3 * sizeof(float);
   }

   if ((getAttribute() & Geometry::ATex1) > 0) {
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
      glEnableVertexAttribArray(1);
      offset += 2 * sizeof(float);
   }

   if ((getAttribute() & Geometry::ANorm) > 0) {
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
      glEnableVertexAttribArray(2);
      offset += 3 * sizeof(float);
   }

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
