#ifndef CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_BASE_HPP_INC

#include <map>

#include <glm/ext.hpp>

#include <cw/Enforce.hpp>

#include <cw/core/Logger.hpp>
#include <cw/graph/View.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/ShaderResourceLocator.hpp>
#include <cw/opengl/Plane.hpp>

namespace cw
{
  namespace opengl
  {
    // TODO big and messy class, refactor somehow
    template<class ModelType>
    class OpenGlViewBase : public graph::View
    {
      protected:
        enum AttrIndex
        {
          POSITION = 0,
          COORD    = 1,
          NORMAL   = 2
        };
        typedef OpenGlViewBase<ModelType> BaseType;
        OpenGlViewBase( Ref<ModelType> model, ProjectionView & projView )
          : m_model( model )
          , m_programId( projView.getProgramId() )
          , m_projView( projView )
          , m_shaderResourceLocator( projView.getProgramId() )
        {
          m_colorUniformId = m_shaderResourceLocator.getUniform( "currentColor" );
          glGenVertexArrays(1, &m_vaoId);
          glBindVertexArray( m_vaoId );
          initializeVBOs();
        }

        void setUpDraw()
        {
          glBindVertexArray( m_vaoId );
        }

        void sendMVP( const glm::mat4 & model )
        {
          glm::mat4 normalMatrix = glm::transpose( glm::inverse( model ) );
          // TODO use ShaderResourceLocator
          auto normalMatrixId = m_shaderResourceLocator.getUniform( "normalMatrix" );
          glUniformMatrix4fv(normalMatrixId, 1, GL_FALSE, &normalMatrix[0][0]);
          m_projView.sendMVP( model );
        }

        void setModelVertices( std::initializer_list< GLfloat > vertices )
        {
          m_vertexBuffer.assign( vertices );
          storeDataInGPU( m_vertexBufferId, m_vertexBuffer );
          glEnableVertexAttribArray( POSITION );
          glVertexAttribPointer( POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }

        void computeNormals()
        {
          ENFORCE( !m_vertexBuffer.empty(), "setModelVertices should be called first!" );
          ENFORCE( m_vertexBuffer.size() % 3 == 0, "Vertices must be 3-element vectors" );
          ENFORCE( m_vertexBuffer.size() % 9 == 0, "Triangles must consist of vertices" );

          std::vector< GLfloat > vertexNormals; // will be sent to 'inNormal'

          // for each triangle ( 1 triangle == 3 vertices, 1 vertex == 3 float )
          for ( auto it = m_vertexBuffer.begin(); m_vertexBuffer.end() != it; it += 9 )
          {
            Plane plane( createVec3( it ),
                         createVec3( it + 3 ),
                         createVec3( it + 6 ) );
            auto normal = plane.getNormal();
            // Need to be added 3 times, for each vertex. Inefficient use of GPU memory,
            // but shader implementation is more simple, and ready for Gouraud shading.
            addNormal( vertexNormals, normal );
            addNormal( vertexNormals, normal );
            addNormal( vertexNormals, normal );
          }
          storeDataInGPU( m_normalBufferId, vertexNormals );
          glEnableVertexAttribArray( AttrIndex::NORMAL );
          glVertexAttribPointer( AttrIndex::NORMAL, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }

        void sendColor( float r, float g, float b )
        {
          glUseProgram( m_programId );
          glUniform4f(m_colorUniformId, r, g, b, 0.0f); // TODO use ShaderResourceLocator
        }

        auto getNumberOfVertices() -> std::vector<GLfloat>::size_type
        {
          // each vertex has 3 element: x,y,z
          return m_vertexBuffer.size() / 3;
        }

        Ref<ModelType> m_model;
        GLuint m_programId;
      private:

        // TODO utility function, move to common place
        template<typename Iterator>
        glm::vec3 createVec3(Iterator iter) const
        {
          glm::vec3 ret;
          ret.x = *(iter);
          ret.y = *(iter + 1);
          ret.z = *(iter + 2);
          return ret;
        }

        // TODO utility function, move to common place
        template<typename Coord>
        static void addNormal( std::vector<GLfloat> & vertexNormals, Coord normal )
        {
          vertexNormals.push_back( normal.x );
          vertexNormals.push_back( normal.y );
          vertexNormals.push_back( normal.z );
        }

        // TODO utility function, move to common place
        static void storeDataInGPU( GLuint bufferId, const std::vector< GLfloat > & what )
        {
          glBindBuffer(GL_ARRAY_BUFFER, bufferId);
          glBufferData(GL_ARRAY_BUFFER,
                       what.size() * sizeof(what[0]),
                       &what[0],
                       GL_STATIC_DRAW );
        }

        void initializeVBOs()
        {
          glGenBuffers(1, &m_vertexBufferId);
          glGenBuffers(1, &m_normalBufferId);
        }

        GLuint m_vertexBufferId;
        GLuint m_normalBufferId;
        ProjectionView & m_projView;
        GLint m_colorUniformId;
        std::vector< GLfloat > m_vertexBuffer;
        ShaderResourceLocator m_shaderResourceLocator;
        GLuint m_vaoId;
    };
  }
}

#endif
