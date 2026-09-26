#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Pumpkin::Core {

using PEVec2 = glm::vec2;
using PEVec3 = glm::vec3;
using PEVec4 = glm::vec4;
using PEMat4 = glm::mat4;

namespace Math {

inline PEMat4 Ortho(float left, float right, float bottom, float top,
                    float zNear, float zFar) {
  return glm::ortho(left, right, bottom, top, zNear, zFar);
}

inline PEMat4 Translate(const PEMat4 &m, const PEVec3 &v) {
  return glm::translate(m, v);
}

inline PEMat4 Scale(const PEMat4 &m, const PEVec3 &v) {
  return glm::scale(m, v);
}

inline const float *ValuePtr(const PEMat4 &m) { return glm::value_ptr(m); }

} // namespace Math

} // namespace Pumpkin::Core
