#ifndef CW_OPENGL_CAMERA_HPP_INC
#define CW_OPENGL_CAMERA_HPP_INC

#include <glm/glm.hpp>

namespace cw
{
  namespace opengl
  {
    class ProjectionView;
    class Camera
    {
      public:
        enum Orientation
        {
          HEADS_UP
        };
        Camera( ProjectionView & );

        void setPos( float x, float y, float z );
        glm::vec3 getPos() const
        { return m_pos; }

        void lookAt( float x, float y, float z );
        glm::vec3 getLookAt() const
        { return m_lookAt; }

        void orientation(Orientation orient);
      private:
        void sendViewMatrix();
        ProjectionView & m_projView;

        glm::vec3 m_pos;
        glm::vec3 m_lookAt;
        glm::vec3 m_orientation;
    };
  }
}

#endif
