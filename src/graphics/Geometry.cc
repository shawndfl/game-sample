/*
 * Geometry.cc
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#include "Geometry.h"
#include "core/Logging.h"
#include "graphics/ShaderSprite.h"

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
void Geometry::initialize(uint vertexCount, uint indexCount, VertexAttributes attribute, bool dynamic) {

    dispose();
    LOGGL();

    attribute_ = attribute;
    indexCount_ = indexCount;
    vertexCount_ = vertexCount;

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vb_);
    glGenBuffers(1, &ib_);

    glBindVertexArray(vb_);
    LOGGL();

    GLint size;
    GLint byteSize;

    // setup vertex buffer
    byteSize = vertexCount_ * sizeof(float);

    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    LOGGL();
    if (byteSize != size) {
        glDeleteBuffers(1, &vb_);
        LOGD("Error creating vertex buffer with size of: " << byteSize);
    }
    LOGGL();

    // setup index buffer
    byteSize = indexCount_ * sizeof(GLuint);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    LOGGL();

    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    LOGGL();
    if (byteSize != size) {
        glDeleteBuffers(1, &ib_);
        LOGD("Error creating index buffer with size of: " << byteSize);
    }
    LOGGL();

    // set our attributes
    long offset = 0;
    unsigned short stride = getStride();

    // the shader must have a attribute position order of pos, color, texture, normal
    // the combinations are:
    //  pos, color
    //  pos, color, texture
    //  pos, color, texture, normal
    //  pos, color, texture, normal, biNormal
    //  pos, color, texture, normal, biNormal
    //  pos, color, texture, normal, biNormal, weight, index

    if ((getAttribute() & APos) > 0) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
        glEnableVertexAttribArray(0);
        offset += 3 * sizeof(float);
    }

    if ((getAttribute() & AColor) > 0) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
        glEnableVertexAttribArray(1);
        offset += 3 * sizeof(float);
    }

    if ((getAttribute() & ATex1) > 0) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
        glEnableVertexAttribArray(2);
        offset += 2 * sizeof(float);
    }

    if ((getAttribute() & ANorm) > 0) {
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) offset);
        glEnableVertexAttribArray(3);
        offset += 3 * sizeof(float);
    }
}

/*************************************************/
GLuint Geometry::getStride() const {
    int stride = 0;
    if ((getAttribute() & APos) > 0) {
        stride += 3;
    }
    if ((getAttribute() & ATex1) > 0) {
        stride += 2;
    }
    if ((getAttribute() & AColor) > 0) {
        stride += 3;
    }
    if ((getAttribute() & ANorm) > 0) {
        stride += 3;
    }
    return stride* sizeof(float);
}

/*************************************************/
void Geometry::setBuffers(std::vector<float>& verts, std::vector<GLuint>& indices) {
    setBuffers(&verts[0], verts.size(), &indices[0], indices.size());
}

/*************************************************/
void Geometry::setBuffers(float* verts, uint vertexCount, GLuint* indices, uint indexCount) {

    uint vCount = vertexCount > vertexCount_? vertexCount_ :  vertexCount;
    uint iCount = indexCount > indexCount_? indexCount_ :  indexCount;

    uint vertBytes = vCount * sizeof(float);
    uint indexBytes = iCount * sizeof(GLuint);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertBytes, &verts[0]);
    LOGGL();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBytes, &indices[0]);

    glBindVertexArray(0);

    LOGGL();
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

   if(vao_ != 0) {
       glDeleteBuffers(1, &vao_);
       vao_ = 0;
   }
}

/*************************************************/
void Geometry::makeActive() const {

   glBindVertexArray(vao_);
}

/*************************************************/
GLuint Geometry::vertexCount() const {
    return vertexCount_;
}

/*************************************************/
GLuint Geometry::IndexCount() const {
    return indexCount_;
}

/*************************************************/
VertexAttributes Geometry::getAttribute() const {
   return attribute_;
}

} /* namespace bsk */
