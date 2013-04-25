#ifndef CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC

#include <cw/graph/View.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/ProjectionView.hpp>

namespace cw
{
  namespace opengl
  {
    template<class ModelType>
    class OpenGlViewBase : public graph::View
    {
      protected:
        typedef OpenGlViewBase<ModelType> BaseType;
        OpenGlViewBase( Ref<ModelType> model, ProjectionView & projView )
          : m_model( model )
          , m_programId( projView.getProgramId() )
          , m_projView( projView )
        {
          loadVertexPosModelSpaceId();

          m_colorUniformId = glGetUniformLocation(m_programId, "currentColor" );
          if ( -1 == m_colorUniformId )
          {
            throw GlException( "Uniform location 'currentColor': does not exist. "
                "It may can be optimized out!");
          }
        }

        void loadVertexPosModelSpaceId()
        {
          int attrLoc = glGetAttribLocation(m_projView.getProgramId(), "vertexPos_modelspace");
          if (attrLoc == -1) throw GlException( "vertexPos_modelspace is not a valid attrib!" );
          m_vertexPositionModelSpaceId = attrLoc;
        }

        void sendMVP( const glm::mat4 & model )
        {
          m_projView.sendMVP( model );
        }

        GLuint getVertexPosModelSpaceId() const
        {
          return m_vertexPositionModelSpaceId;
        }

        void setModelVertices( std::initializer_list< GLfloat > vertices )
        {
          m_vertexBuffer.assign( vertices );
          glGenBuffers(1, &m_vertexBufferId);
          glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
          glBufferData(GL_ARRAY_BUFFER,
                       m_vertexBuffer.size() * sizeof(m_vertexBuffer[0]),
                       &m_vertexBuffer[0],
                       GL_STATIC_DRAW );
        }

        void sendColor( float r, float g, float b )
        {
          glUseProgram( m_programId );
          glUniform4f(m_colorUniformId, r, g, b, 0.0f);
        }

        Ref<ModelType> m_model;
        GLuint m_vertexBufferId;
        const GLint m_programId;
      private:
        ProjectionView & m_projView;
        GLuint m_vertexPositionModelSpaceId;
        GLint m_colorUniformId;
        std::vector< GLfloat > m_vertexBuffer;
    };
  }
}

#endif
