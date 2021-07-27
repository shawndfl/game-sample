/*
 * ShaderProgram.h
 *
 *  Created on: Dec 27, 2020
 *      Author: sdady
 */

#ifndef SRC_SHADERPROGRAM_H_
#define SRC_SHADERPROGRAM_H_

#include "graphics/VertexAttribute.h"
#include <string>
#include "glm/glm.hpp"

namespace bsk {

/**
 * Abstract shader program used by Geometry to map vertex attributes
 */
class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    void use() const;

    void setBool(const std::string& name, bool value) const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;

    void setMatrix4(const std::string& name, const glm::mat4& value) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;

    void setVec4(const std::string& name, const glm::vec4& value) const;

    bool loadShaderFromMemory(const std::string& vertexCode, const std::string& fragmentCode);
    bool loadShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath);

private:
   unsigned int program_;
   std::string vertexPath_;
   std::string fragmentPath_;
};

} /* namespace bsk */

#endif /* SRC_SHADERPROGRAM_H_ */
