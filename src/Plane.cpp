#include <cw/opengl/Plane.hpp>

#include <cw/core/Logger.hpp>
#include <cw/core/Pos3d.hpp>

namespace
{
  cw::core::Logger logger("opengl");
}

namespace cw
{
  namespace opengl
  {
Plane::Plane( const glm::vec3& a,
              const glm::vec3& b,
              const glm::vec3& c )
  : m_A(a)
  , m_B(b)
  , m_C(c)
{}

core::Pos3d toPos( glm::vec3 v )
{
  return core::Pos3d( v.x, v.y, v.z );
}

glm::vec3 Plane::getNormal() const
{
  return glm::normalize( glm::cross( m_C - m_A, m_B - m_A ) );
}

  }
}
