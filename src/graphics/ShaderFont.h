/*
 * ShaderFont.h
 *
 *  Created on: Jul 31, 2020
 *      Author: sdady
 */

#ifndef SRC_ShaderFont_H_
#define SRC_ShaderFont_H_

#include <string>
#include <vector>

#include "ShaderProgram.h"
#include "Geometry.h"
#include "Material.h"
#include "math/mathCore.h"
#include "math/Matrix4.h"
#include "math/Vector4.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

namespace bsk {

/*
 * Shader program that will require a material and geometry
 */
class ShaderFont : public ShaderProgram {
public:

   ShaderFont();

   virtual ~ShaderFont();

   bool loadProgram();

   void enableProgram();

   bool setTexture(const Texture& texture);

   void setScreenSize(uint width, uint height);

   void setProjection(const Matrix4& projection);
   void setColor(const Vector4& color);

   virtual int getPosition() const;
   virtual int getByteStride() const;

   VertexAttributes getAttribute() const;
   int getColor() const;

   void dispose();

private:
   int getUniformLocation(const std::string& name);

   int getAttributeLocation(const std::string& name);
private:

   Texture        texture_;
   GLuint         program_;

   // uniforms
   int          uProjection_;
   int          uTexture_;
   int          uColor_;

   // attributes
   int          aPosition_;
   int          aTexture_;

   int          byteStride_;

};

} /* namespace bsk */

#endif /* SRC_ShaderFont_H_ */
