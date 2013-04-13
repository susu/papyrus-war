#ifndef CW_OPENGL_PROJECTION_VIEW_HPP_INC
#define CW_OPENGL_PROJECTION_VIEW_HPP_INC

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace cw
{
  namespace opengl
  {
    class Program;
    /**
     * Contains the PROJECTION and VIEW matrices
     *   computing MVP and sends to shaders
     */
    class ProjectionView
    {
      public:
        ProjectionView( const Program & p );

        GLuint getProgramId() const
        { return m_programId; }

        void setViewMatrix( const glm::mat4& view );

        void sendMVP( const glm::mat4 & model = glm::mat4(1.0) );

        const glm::mat4 & getProjectionMatrix() const
        { return m_projectionMatrix; }

        const glm::mat4 & getViewMatrix() const
        { return m_viewMatrix; }

      private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;

        GLuint m_programId;
        GLuint m_mvpMatrixId;
    };
  }
}

#endif
