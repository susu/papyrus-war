#ifndef CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC

#include <map>

#include <cw/graph/View.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/ShaderResourceLocator.hpp>

namespace cw
{
  namespace opengl
  {
    template<class ModelType>
    class OpenGlViewBase : public graph::View
    {
      protected:
        const static std::string VERTEXPOS_ATTR;
        typedef OpenGlViewBase<ModelType> BaseType;
        OpenGlViewBase( Ref<ModelType> model, ProjectionView & projView )
          : m_model( model )
          , m_programId( projView.getProgramId() )
          , m_projView( projView )
          , m_shaderResourceLocator( projView.getProgramId() )
        {
          m_colorUniformId = m_shaderResourceLocator.getUniform( "currentColor" );
        }

        GLuint loadVertexAttribute( const std::string & name )
        {
          return m_shaderResourceLocator.getAttrib( name.c_str() );
        }

        void sendMVP( const glm::mat4 & model )
        {
          m_projView.sendMVP( model );
        }

        GLuint getVertexAttribute( const std::string & name )
        {
          auto it = m_vertexAttributes.find(name);
          if ( it == m_vertexAttributes.end() )
          {
            auto result = m_vertexAttributes.emplace( name, loadVertexAttribute( name ) );
            it = result.first;
          }
          return it->second;
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
        GLuint m_programId;
      private:
        ProjectionView & m_projView;
        std::map< std::string, GLuint > m_vertexAttributes;
        GLint m_colorUniformId;
        std::vector< GLfloat > m_vertexBuffer;
        ShaderResourceLocator m_shaderResourceLocator;
    };
    template<class T>
    const std::string OpenGlViewBase<T>::VERTEXPOS_ATTR = "vertexPos_modelspace";
  }
}

#endif
