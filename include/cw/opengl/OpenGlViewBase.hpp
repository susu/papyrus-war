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
          , m_projView( projView )
        {
          loadVertexPosModelSpaceId();
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

        Ref<ModelType> m_model;
        GLuint m_vertexBufferId;
      private:
        ProjectionView & m_projView;
        GLuint m_vertexPositionModelSpaceId;
    };
  }
}

#endif
