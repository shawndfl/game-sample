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
#include "math/Math.h"

namespace bsk {

/**
 * Shader program is used to load shaders from file or from memory.
 * Once they are loaded uniform values can be set using the set functions
 * call use to make the program active.
 */
class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    /**
     * Load from memory
     */
    bool loadShaderFromMemory(const std::string& vertexCode, const std::string& fragmentCode);

    /**
     * Load from a file
     */
    bool loadShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath);

    /**
     * Make this program active.
     */
    void use() const;

    void setBool(const std::string& name, bool value) const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;

    void setMatrix4(const std::string& name, const glm::mat4& value) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;

    void setVec4(const std::string& name, const glm::vec4& value) const;

private:
   unsigned int program_;
   std::string vertexPath_;
   std::string fragmentPath_;
};

} /* namespace bsk */

#endif /* SRC_SHADERPROGRAM_H_ */
