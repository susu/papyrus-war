#ifndef CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC
#define CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <cw/core/Types.hpp>

#include <cw/graph/View.hpp>
#include <cw/graph/Types.hpp>

namespace cw
{
  namespace opengl
  {
    class ProjectionView;
    class PaperBoatView : public graph::View
    {
      public:
        PaperBoatView( core::PaperBoatRef model, ProjectionView & projView );

        virtual void show() override;
      private:
        core::PaperBoatRef m_paperBoatModel;
        GLuint m_vertexBuffer;
        GLuint m_vertexPositionModelSpaceId;
        std::vector< GLfloat > m_model;
        ProjectionView & m_projView;
    };
  }
}

#endif
