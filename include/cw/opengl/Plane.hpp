#ifndef CW_OPENGL_PLANE_HPP_INC
#define CW_OPENGL_PLANE_HPP_INC

#include <glm/glm.hpp>

namespace cw
{
  namespace opengl
  {
    // represents a geometrical Plane
    class Plane
    {
      public:
        Plane( const glm::vec3& a,
               const glm::vec3& b,
               const glm::vec3& c );

        glm::vec3 getNormal() const;

      private:
        glm::vec3 m_A;
        glm::vec3 m_B;
        glm::vec3 m_C;
    };
  }
}

#endif
